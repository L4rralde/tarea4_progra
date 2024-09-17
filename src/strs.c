//strs.c
/*
Autor: Emmanuel Alejandro Larralde Ortiz | emmanuel.larralde@cimat.mx
Descripcion:
    Elimina todas las palabras que tienen letras repetidas de un string.

Compilacion:
    gcc src/strs.c include/code_format/format.c -o output/strs.o
    chmod +x output/strs.o

Ejemplo:
    $./output/strs.o
    <varias palabras ingresadas en la terminal>

Ejemplo de uso:
    $./output/strs.o
    $Hola de Emmanuel
    str1: Hola de Emmanuel
    str2: Hola de
*/
#include <stdlib.h>
#include <stdio.h>
#include "../include/code_format/format.h"

void no_rep(char *, char *);
void append(char*, int *, char*, int, int);

int main(){
    char str1[1000];
    //Recibe de la terminal una linea.
    fgets(str1, sizeof(str1), stdin);
    printf("str1: %s", str1);

    char str2[1000];
    no_rep(str1, str2); //Procesamiento
    printf("str2: %s\n", str2);

    return 0;
}

//Elimina las palabras repetidas de str1 y guarda el resultado en str2
void no_rep(char *str1, char *str2){
    //Cuenta número de caracteres ingresados
    int n = 0;
    for(char *ptr = str1; *(ptr) != '\0'; ptr++)
        n++;

    char chars[27]; //Registra la repeticion de letras
    for(int i=0; i<27; ++i)
        chars[i] = 0;
    //Registra el tamanio de str2. Apunta al ultimo elemento de la misma
    int str2_len = 0;

    int start, len;
    start = 0;
    len = 0;

    char current;
    int repeated = 0;
    int letter = 0;

    //Para cada elemento en str1
    for(int i=0; i<n; ++i){
        current = *(str1 + i);
        if(current != ' '){//Si no es espacio, es la continuacion de una palabra.
            if(repeated) //Si hay repeticion, continuamos hasta el proximo espacio
                continue;
            len++;
            letter = simple_char_to_letter(current);
            if(letter == -1)
                continue;
            chars[letter]++;
            repeated = chars[letter] == 2; //Hay repeticion
            continue;
        }
        //Si es un espacio, terminamos de leer una palabra
        if(len > 0 && !repeated) //Si en efecto se lee una palabra completa sin repeticiones
            append(str2, &str2_len, str1, start, start + len);
        //Reinicia variables de deteccion
        repeated = 0;
        len = 0;
        for(int i=0; i<27; ++i)
            chars[i] = 0;
        //Empezamos a analizar la prox palabra.
        start = i+1;
    }
    if(len > 0 && !repeated)
        append(str2, &str2_len, str1, start, start + len);
}

//Agrega src[init:end] a dst a partir de dst[dst_len]
void append(char *dst, int *dst_len, char *src, int src_init, int src_end){
    //Agrega un espacio si ya tiene palabras
    if((*dst_len) > 0){
        *(dst + *(dst_len)) = ' ';
        *(dst_len) = *(dst_len) + 1;
    }
    //Agrega la nueva palabra
    for(int i=src_init; i<src_end; ++i){
        *(dst + *(dst_len)) = *(src + i);
        *(dst_len) = *(dst_len) + 1;
    }
}