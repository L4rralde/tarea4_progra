// src/comparar_strs.c
/*
Autor: Emmanuel Alejandro Larralde Ortiz | emmanuel.larralde@cimat.mx
Descripcion:
    Compara lexicográficamente dos palabras.

Compilación:
    gcc src/comparar_strs.c include/code_format/format.c -o output/comparar_strs.o
    chmod +x output/comparar_strs.o

Uso:
    output/comparar_strs.o <palabra_1> <palabra_2>
*/
#include <stdio.h>
#include "../include/code_format/format.h"

int main(int argc, char **argv){
    char *str1 = argv[1];
    char *str2 = argv[2];
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    
    int diff;
    diff = compara_str(str1, str2);
    //Imprime resultado de la comparacion
    if(diff == 0){
        printf("'%s' y '%s' son iguales\n", str1, str2);
    }else if(diff > 0){
        printf("'%s' > '%s'\n", str1, str2);
    }else{
        printf("'%s' > '%s'\n", str2, str1);
    }
    return 0;
}
