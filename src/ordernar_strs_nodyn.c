// src/ordenar_strs_nodyn.c
/*
Autor: Emmanuel Alejandro Larralde Ortiz | emmanuel.larralde@cimat.mx
Descripcion:
    Ordena una lista de palabras de manera lexicografica.
Compilacion:
    gcc src/ordernar_strs_nodyn.c include/code_format/format.c -o output/ordenar.o
    chmod +x output/ordenar.o
Uso:
    ./output/ordenar.o <lista de palabras ordenados por espacios>
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/code_format/format.h"

int compare(const void *, const void *);
char **create_arrs(char **);
void str_ordena(char **, int);

int main(int argc, char **argv){
    int n = argc - 1;
    char **arrs;
    arrs = create_arrs(argv);

    //Imprime palabras escritas.
    printf("Palabras ingresadas:\n");
    for(int i=0; i<n; ++i)
        printf("%d. %s\n", i+1, *(arrs + i));
    
    str_ordena(arrs, n); //Ordenar arreglo de arreglos.
    //Imprime arreglos ordenados
    printf("-------------------------------\n");
    printf("Palabras ordenadas:\n");
    for(int i=0; i<n; ++i)
        printf("%d. %s\n", i+1, *(arrs + i));

    return 0;
}

//Crea un arreglo de arreglos con las palabras ingresadas por la terminal.
char **create_arrs(char** argv){
    return argv + 1;
}

//Interfaz para pasar mi funcion compara_str a qsort.
int compare(const void *arg1, const void *arg2){
    return compara_str( * ( char** ) arg1, * ( char** ) arg2 );
}

//Ordena el arreglo de strs
void str_ordena(char **arrs, int n){
    qsort((void *) arrs, n, sizeof(char *), compare);
};