#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    FILE *leer = fopen("leer.txt", "r");
    FILE *escribir = fopen("escribir2.txt", "w");

    int contCaracteres = 0;
    char caract;
    while ((caract = fgetc(leer)) != EOF)
    {
        contCaracteres++;
    }

    char *buffer = malloc(contCaracteres * sizeof(char));
    rewind(leer);

    fread(buffer, sizeof(char), contCaracteres, leer);
    fwrite(buffer, sizeof(char), contCaracteres, escribir);

    printf("%s", buffer);
    free(buffer);

    fclose(leer);
    fclose(escribir);

    return 0;
}
