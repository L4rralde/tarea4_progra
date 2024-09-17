// src/ordenar_str.c
/*
Autor: Emmanuel Alejandro Larralde Ortiz | emmanuel.larralde@cimat.mx
Descripcion:
    Ordena lexicograficamente n palabras.

Compilacion:
    gcc src/ordernar_strs.c include/code_format/format.c -o output/ordenar.o
    chmod +x output/ordenar.o

Uso:
    $./output/ordenar.o <numero_de_palabras>
    $ <palabras separadas>
*/
#include <stdlib.h>
#include <stdio.h>
#include "../include/code_format/format.h"

char **create_arrs(int);
int compare(const void *, const void *);
void str_ordena(char **, int);

int main(int argc, char **argv){
    int n = atoi(argv[1]);
    char **arrs;

    arrs = create_arrs(n);
    printf("Palabras leidas:\n");
    for(int i=0; i<n; ++i)
        printf("%d. %s\n", i+1, *(arrs + i));
    str_ordena(arrs, n);
    printf("----------------------------------------\n");
    printf("Palabras ordenadas:\n");
    for(int i=0; i<n; ++i)
        printf("%d. %s\n", i+1, *(arrs + i));

    free(arrs[0]);
    free(arrs);
    return 0;
}

//Crea un arreglo de n palabras ingresadas desde la terminal
char **create_arrs(int n){
    char **arrs = (char **) malloc(n * sizeof(char *));
    if(arrs == NULL){
        printf("Couldn't allocate memory\n");
    }
    char *buffer, c;
    int len;
    for(int i=0; i<n; ++i){
        len = 0;
        buffer = (char *) malloc(32 * sizeof(char));
        if(buffer == NULL){
            printf("Couldn't allocate memory\n");
        }
        while(1){
            c = getchar();
            if(c == '\0' || c == ' ' || c == '\n' || c == EOF){//Si terminó la palabra
                *(buffer + len) = '\0';//Añade un caracter nulo.
                break;
            }
            *(buffer + len) = c;
            len++;
        }
        //Redimensiona el buffer para que use solo la memoria necesaria
        buffer = (char *) realloc(buffer, (len + 1) * sizeof(char));
        if(buffer == NULL){
            printf("Couldn't resize dynamically allocated memory\n");
            exit(0);
        }
        *(arrs + i) = buffer;
    }
    return arrs;
}

//Interfaz para pasar mi funcion compara_str a qsort.
int compare(const void *arg1, const void *arg2){
    return compara_str( * ( char** ) arg1, * ( char** ) arg2 );
}

//Ordena el arreglo de strs
void str_ordena(char **arrs, int n){
    qsort((void *) arrs, n, sizeof(char *), compare);
};