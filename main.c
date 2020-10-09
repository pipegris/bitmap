#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmp_milton.h"
#include "bmp_agris.h"

#define ext ".bmp"
#define ext2 ".txt"



int main() {
    int fc[3], c, tm, i, j;
    char nombre1[64], nombre2[64];
    //-----------------memoria dinamica
    // filas y columnas
    int m = 1000, n = 1000;
    int **mat = NULL;
    mat = Matrix_Alloc(mat, m, n);

    int function = 1;
    
    //-----------------------------------

    printf("Ingrese archivo orígen:");
    scanf("%s", nombre1);

    strcat(nombre1, ext);
    c = bmp256(nombre1, mat, fc);  //fc[fil,col,numero de ceros]
    if (c == 0) {
        printf("No se pudo abrir el archivo!! \n");
        return 0;
    }

    // Función para capturar el tipo de operación y sus respectivos parámetros
    readFunction(&function);

    ///
    printf("Ingrese archivo destino: ");
    scanf("%s", nombre2);

    for (i = 0; i < fc[0]; i++) {
        for (j = 0; j < fc[1]; j++) {
            // Calcula el valor del pixel dependiendo del operador seleccionado
            mat[i][j] = getTransformedPixel(mat[i][j], function);
        }
    }
    ///////////////////////////////////////////////////////////////////////////////

    strcat(nombre2, ext);

    salvar(nombre1, nombre2, mat, fc);

    printf("Finalizado....\n");
    getchar();
    Matrix_Free(mat, m);
    return 1;
}
