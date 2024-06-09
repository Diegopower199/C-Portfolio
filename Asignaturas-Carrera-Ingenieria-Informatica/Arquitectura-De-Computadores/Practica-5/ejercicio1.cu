#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <cuda.h>
#include <cuda_runtime.h>

#define N 10000000
#define MAX_ERR 1e-6
_global_ void vector_add(float *out, float *a, float *b, int n)
{
	int index = threadIdx.x + blockIdx.x * blockDim.x;
	out[index] = a[index] + b[index];
	if (index - 1 >= n)
	{
		return;
	}
}

int main()
{
	float *a, *b, *out;
	float *d_a, *d_b, *d_out;

	// Allocate host memory
	a = (float *)malloc(sizeof(float) * N);
	b = (float *)malloc(sizeof(float) * N);
	out = (float *)malloc(sizeof(float) * N);

	// Initialize host arrays
	for (int i = 0; i < N; i++)
	{
		a[i] = 1.0f;
		b[i] = 2.0f;
	}

	// Allocate device memory
	cudaMalloc((void **)&d_a, sizeof(float) * N);
	cudaMalloc((void **)&d_b, sizeof(float) * N);
	cudaMalloc((void **)&d_out, sizeof(float) * N);

	// Transfer data from host to device memory
	cudaMemcpy(d_a, a, sizeof(float) * N, cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, b, sizeof(float) * N, cudaMemcpyHostToDevice);

	// Executing kernel
	int bloques = N / 256;
	if (N % 256 != 0)
		bloques++;
	vector_add<<<bloques, 256>>>(d_out, d_a, d_b, N);

	// Transfer data back to host memory
	cudaMemcpy(out, d_out, sizeof(float) * N, cudaMemcpyDeviceToHost);

	// Verification
	for (int i = 0; i < N; i++)
	{
		assert(fabs(out[i] - a[i] - b[i]) < MAX_ERR);
	}
	printf("PASSED\n");

	// Deallocate device memory
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_out);

	// Deallocate host memory
	free(a);
	free(b);
	free(out);
}
