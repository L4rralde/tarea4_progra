//filters.c
/*
Autor: Emmanuel Alejandro Larralde Ortiz | emmanuel.larralde@cimat.mx
Descripcion:
    Aplica los siguientes filtros de suavizados a imágenes en formato pgm:
        - Gaussiano 3x3, 5x5, 7x7
        - Uniforme o promediador 3x3, 5x5, 7x7.

Compilación:
    gcc src/filters.c include/pgm1/pgm1.c -o output/filers.o
    chmod +x output/filers.o

Uso:
    ./output/filers.o <ruta_imagen_entrada> <ruta_imagen_salida> <selector_de_filtro>

        - <ruta_imagen_entrada>: default "images/fractal_tree_ascii.pgm"
        - <ruta_imagen_salida>: default "images/image_out.pgm"
        - <selector_de_filtro>: [0, 1, ... 5]. Default 0:
            - 0: Gauss 3x3
            - 1: Gauss 5x5
            - 2: Gauss 7x7
            - 3: Uniforme o pormediador 3x3
            - 4: Uniforme 5x5.
            - 5: Uniforme 7x7
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/pgm1/pgm1.h"

//Gauss 3x3
float G3[3][3]={
    {1.0/16, 2.0/16, 1.0/16},
    {2.0/16, 4.0/16, 2.0/16},
    {1.0/16, 2.0/16, 1.0/16}
};

//Gauss 5x5
float G5[5][5] = {
    {1.0/273, 4.0/273, 7.0/273, 4.0/273, 1.0/273},
    {4.0/273, 16.0/273, 26.0/273, 16.0/273, 4.0/273},
    {7.0/273, 26.0/273, 41.0/273, 26.0/273, 7.0/273},
    {4.0/273, 16.0/273, 26.0/273, 16.0/273, 4.0/273},
    {1.0/273, 4.0/273, 7.0/273, 4.0/273, 1.0/273}
};

//Gauss 7x7
float G7[7][7] = {
    {0.0/1003, 0.0/1003, 1.0/1003, 2.0/1003, 1.0/1003, 0.0/1003, 0.0/1003},
    {0.0/1003, 3.0/1003, 13.0/1003, 22.0/1003, 13.0/1003, 3.0/1003, 0.0/1003},
    {1.0/1003, 13.0/1003, 59.0/1003, 97.0/1003, 59.0/1003, 13.0/1003, 1.0/1003},
    {2.0/1003, 22.0/1003, 97.0/1003, 159.0/1003, 97.0/1003, 22.0/1003, 2.0/1003},
    {1.0/1003, 13.0/1003, 59.0/1003, 97.0/1003, 59.0/1003, 13.0/1003, 1.0/1003},
    {0.0/1003, 3.0/1003, 13.0/1003, 22.0/1003, 13.0/1003, 3.0/1003, 0.0/1003},
    {0.0/1003, 0.0/1003, 1.0/1003, 2.0/1003, 1.0/1003, 0.0/1003, 0.0/1003}
};

//Uniforme 3x3
float U3[3][3] = {
    {1.0/9, 1.0/9, 1.0/9},
    {1.0/9, 1.0/9, 1.0/9},
    {1.0/9, 1.0/9, 1.0/9}
};

//Uniforme 5x5
float U5[5][5] = {
    {1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25},
    {1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25},
    {1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25},
    {1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25},
    {1.0/25, 1.0/25, 1.0/25, 1.0/25, 1.0/25}
};

//Uniforme 7x7
float U7[7][7] = {
    {1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49},
    {1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49},
    {1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49},
    {1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49},
    {1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49},
    {1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49},
    {1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49, 1.0/49}
};


int main(int argc, char **argv){
    //arg parse: imagen de entrada
    char *path_img_in;
    path_img_in = argc > 1? argv[1]: "images/fractal_tree_ascii.pgm";

    //arg parse: imagen de salida.
    char *path_img_out;
    path_img_out = argc > 2? argv[2] : "images/image_out.pgm";

    //Carga imagen de entrada.
    int ok, rows, cols;
    unsigned char **image;
    image = pgmRead(path_img_in, &rows, &cols);
    if (image == NULL) {
        printf("Error pgmRead\n");
        exit(1);
    }

    //arg parse: selección de filtro
    int sel;
    sel = argc > 3? atoi(argv[3]): 0;
    int kns[] = {3, 5, 7, 3, 5, 7};
    int kn = kns[sel];

    //Conversion de Kernels de tipo de dato:
    //double [][] a double **
    unsigned char **new_img;
    float * kernels[] = {&G3[0][0], &G5[0][0], &G7[0][0], &U3[0][0], &U5[0][0], &U7[0][0]};
    float *kernel_ptrs[kn];
    for(int i=0; i<kn; ++i)
        kernel_ptrs[i] = kernels[sel] + i*kn;
    float **kernel = kernel_ptrs;

    //Operacion de convolucion/correlacion cruzada
    new_img = convolution(image, rows, cols, kernel, kn);

    // Archivo de salida
    ok = pgmWrite(path_img_out, rows - kn + 1, cols - kn + 1, new_img, NULL);

    //Liberacion de memoria dinamica
    free(new_img[0]);
    free(new_img);
    free(image[0]);
    free(image);

    return 0;
}
