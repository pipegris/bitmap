#include <stdio.h>

int u;
int u1;
int u2;
int *ulist;
int nItems;

int getTransformedPixel(int p, int function) {
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
            if (p<=ulist[0]) {
                return 0; // Caso extremo inferior
            } else if (p>=ulist[nItems-1]) {
                return ulist[nItems-1]; // Caso extremo superior
            } else {
                for(i=1; i<(nItems-2); i++) {
                    if (p>ulist[i] && p<=ulist[i+1]) { // Casos intermedios
                        return ulist[i];
                    }
                }
            }
            break;
        default:
            return 0;
            break;
    }

    return p;
}

void readFunction(int *function) {
    int i;
    int lastU;

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
    scanf("%d", function);

    switch (*function) {
        case 3:
            printf("Ingrese el valor para el umbral [1-255]: ");
            scanf("%d", &u);
            break;
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            printf("Ingrese el valor inferior para el umbral [1-255]: ");
            scanf("%d", &u1);
            printf("Ingrese el valor superior para el umbral [%d-255]: ", u1);
            scanf("%d", &u2);
            break;
        case 9:
            printf("Ingrese la cantidad de umbrales: ");
            scanf("%d", &nItems);
            ulist = malloc(sizeof(int) * nItems);
            lastU = 1;
            for(i=0; i<nItems; i++) {
                printf("Ingrese el valor para el umbral %d [%d-255]: ", i, lastU);
                scanf("%d", &ulist[i]);
                lastU = ulist[i];
            }
            break;
        default:
            break;
    }
}