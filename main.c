#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bmp_milton.h"

#define ext ".bmp"
#define ext2 ".txt"

int getTransformedPixel(int, int);

int main() {
    int fc[3], c, tm, i, j;
    char nombre1[12], nombre2[12];
    //-----------------memoria dinamica
    // filas y columnas
    int m = 1000, n = 1000;
    //long int **mat; //matriz para la imagen
    int **mat = NULL;
    mat = Matrix_Alloc(mat, m, n);

    int function = 1;
    //-----------------------------------

    printf("ingrese archivo:");
    scanf("%s", nombre1);

    //concatenar(nombre1,ext);
    strcat(nombre1, ext);
    c = bmp256(nombre1, mat, fc);  //fc[fil,col,numero de ceros]
    if (c == 0) {
        printf("no se pudo abrir el archivo!! \n");
        return 0;
    }


    printf("Ingrese # función:\n");
    printf("1. Identidad\n");
    printf("2. Inversión\n");
    printf("3. Umbral\n");
    printf("4. Intervalo Umbral binario\n");
    printf("5. Intervalo Umbral binario invertido\n");
    printf("6. Umbral escala de grises\n");
    printf("7. Umbral escala de grises invertido\n");
    printf("8. Extensión\n");
    printf("9. Reducción del nivel de gris\n");
    printf("[1-9]: ");
    scanf("%d", &function);

    ///
    printf("ingrese archivo destino: ");
    scanf("%s", nombre2);
    //modificar para que nombre 1 sea diferente de nombre2
    //operaciones a relizar
    //modificar el siguiente codigo para
    //-aplicar brillo y contraste
    //-umbralizar

    for (i = 0; i < fc[0]; i++) {
        for (j = 0; j < fc[1]; j++) {
            mat[i][j] = getTransformedPixel(mat[i][j], function);
        }
    }
    ///////////////////////////////////////////////////////////////////////////////

    strcat(nombre2, ext);
    //juntar(nombre2,ext);
    salvar(nombre1, nombre2, mat, fc);

    printf("Finalizado....\n");
    getchar();
    Matrix_Free(mat, m);
    return 1;
}

/**
 * Retorna el pixel transformado de acuerdo a la función seleccionada
 * 1. Identidad
 * 2. Inversión
 * 3. Umbral
 * 4. Intervalo Umbral binario
 * 5. Intervalo Umbral binario invertido
 * 6. Umbral escala de grises
 * 7. Umbral escala de grises invertido
 * 8. Extensión
 * 9. Reducción del nivel de gris
 *
 * @param p pixel a transformar
 * @param function número de operador de acuerdo al listado anterior
 * @return
 */
int getTransformedPixel(int p, int function) {
    int u = 150;
    int u1 = 50;
    int u2 = 150;
    int ulist[] = {10, 30, 50, 80, 150, 180, 210, 220, 240, 250};
    int i;

    switch (function) {
        case 1:
            p = p;
            break;
        case 2:
            p = 255 - p;
            break;
        case 3:
            p = p > u ? 255 : 0;
            break;
        case 4:
            p = (p <= u1 || p >= u2) ? 255 : 0;
            break;
        case 5:
            p = (p <= u1 || p >= u2) ? 0 : 255;
            break;
        case 6:
            p = (p <= u1 || p >= u2) ? 255 : p;
            break;
        case 7:
            p = (p <= u1 || p >= u2) ? 255 : 255-p;
            break;
        case 8:
            p = (p <= u1 || p >= u2) ? 0 : 255*(p-u1)/(u2-u1);
            break;
        case 9:
            for(i=0; i<10; i++) {
                if (p>i) {

                } else {
                    continue;
                }
            }
            p = (p <= u1 || p >= u2) ? 255 : p;
            break;
        default:
            return 0;
            break;
    }
     // 4. Umbral binario

    return p;
}