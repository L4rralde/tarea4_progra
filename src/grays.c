// src/grays.c
/*
Autor: Emmanuel Alejandro Larralde Ortiz | emmanuel.larralde@cimat.mx
Descripción:
    Modifica la cantidad de niveles de grises de una imagen pgm

Compilacion:
    gcc src/grays.c include/pgm1/pgm1.c -o output/pgm1.o
    chmod +x output/pgm1.o

Uso:
    output/pgm1.o <path_img_in> <path_img_out> <bits>
*/
#include <stdlib.h>
#include <stdio.h>
#include "../include/pgm1/pgm1.h"

unsigned char **new_gray_scale(unsigned char **, int, int, int);

int main(int argc, char **argv){
    //arg parse: img_in
    char *path_img_in;
    path_img_in = argc > 1? argv[1]: "images/fractal_tree_ascii.pgm";
    //arg parse: img_out
    char *path_img_out;
    path_img_out = argc > 2? argv[2] : "images/image_out.pgm";
    //arg parse: bits
    int bits;
    bits = argc > 3? atoi(argv[3]) : 8;

    //Carga imagen de entrada
    int ok, rows, cols;
    unsigned char **image;
    image = pgmRead(path_img_in, &rows, &cols);
    if (image == NULL) {
        printf("Error pgmRead\n");
        exit(1);
    }
    
    //Modifica escala de grises
    unsigned char **new_img;
    new_img = new_gray_scale(image, rows, cols, bits);

    //Archivo de salida
    ok = pgmWrite(path_img_out, rows, cols, new_img, NULL);

    //Libera memoria dinámica
    free(new_img[0]);
    free(new_img);
    free(image[0]);
    free(image);

    return 0;
}

//Modifica la cantidad de niveles de escala de grises de una imagen.
//La cantidad de niveles es 2^(bits) con bits < 8.
unsigned char **new_gray_scale(unsigned char **img, int rows, int cols, int bits){
    //Instanciacion de la nueva imagen
    unsigned char *aux_ptr, **new_img;
    new_img = (unsigned char **)malloc(rows * sizeof(unsigned char *));
    if (new_img == NULL){
        printf("Failure to allocate room for pointers\n");
        return NULL;
    }
    aux_ptr = (unsigned char *) malloc(rows * cols * sizeof(unsigned char));
    if(aux_ptr == NULL){
        printf("Failure to allocate room for pointers\n");
        return NULL;
    }
    for(int i=0; i<rows; ++i)
        new_img[i] = aux_ptr + i*cols;

    //conversión de niveles de grises.
    const float factor = 255.0/((1 << bits) - 1.0);
    const int rshifts = 8 - bits;
    for(int i=0; i<rows; ++i)
        for(int j=0; j<cols; j++)
            new_img[i][j] = (img[i][j] >> rshifts)*factor;

    return new_img;
}
