//derivative.c
/*
Autor: Emmanuel Alejandro Larralde Ortiz
Descripcion:
    Resalta los bordes de una imagen por el método de Sobel o Gradiente.

Compilacion:
    gcc src/derivative.c include/pgm1/pgm1.c -o output/derivative.o
    chmod +x output/derivative.o

Uso:
    ./output/derivative.o <path_img_in> <path_img_out> <sel>

        -sel: 0=Gradiente, 1:Sobel. default=0
*/
#include <stdlib.h>
#include <stdio.h>
#include "../include/pgm1/pgm1.h"


typedef unsigned char **(*Function)(unsigned char **, int, int);
unsigned char **derivative(unsigned char **, Function, int, int);

int main(int argc, char **argv){
    //Arg parse: img_in
    char *path_img_in;
    path_img_in = argc > 1? argv[1]: "images/fractal_tree_ascii.pgm";

    //Arg parse: img_out
    char *path_img_out;
    path_img_out = argc > 2? argv[2] : "images/image_out.pgm";

    //Carga imagen de entrada
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

    //Realiza el procesamiento
    unsigned char **new_img;
    switch (sel){
        case 0:
            new_img = derivative(image, gradient, rows, cols);
            break;
        case 1:
            new_img = derivative(image, sobel, rows, cols);
            break;
        default:
            printf("Argumento invalido. <sel> = [0, 1]\n");
            return 0;
    }

    //Escribe img_out
    ok = pgmWrite(path_img_out, rows - 2, cols - 2, new_img, NULL);
    
    //Libera memoria dinámica.
    free(image[0]);
    free(image);
    free(new_img[0]);
    free(new_img);

    return 0;
}

unsigned char **derivative(unsigned char **in, Function f, int rows, int cols){
    return f(in, rows, cols);
}