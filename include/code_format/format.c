#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "format.h"

//Convierte un carácter de ASCII simple a una letra del alfabeto español.
int simple_char_to_letter(uint8_t c){
    //Detección de letras mayúsculas en ascii simple
    if(c >= 65 && c <= 90)
        return c - 'A';
    //Detección de letras minúsculas en ascii simple
    if(c >= 97 && c <= 122)
        return c - 'a';

    return -1; //No es una letra del ascii simple
}

//Convierte un carácter de ASCII extendido a una letra del alfabeto español.
int char_to_letter(uint8_t c){
    if(
        c == 65 || c == 97 || (c >= 131 && c <= 134) || c == 142 || c == 143 ||
        c == 160 || c == 166 || (c >= 181 && c <= 183) || c == 198 || c == 199
    )
        return 'A'-'A';
    //Todas las variantes de B se encuentran en ascii simple
    if(c == 67 || c == 99 || c == 128 || c == 135)
        return 'C'-'A';
    if(c == 68 || c == 100 || c == 208 || c == 209)
        return 'D'-'A';
    if(c == 69 || c == 101 || c == 130 || (c >= 136 && c <= 138) || c == 144 || (c >= 210 && c <= 212))
        return 'E'-'A';
    //Todas las variantes de F, G, H se enceuntran en ascii simple
    if(c == 73 || c == 105 || (c >= 139 && c <= 141) || c == 161 || (c >= 214 && c <= 216) || c == 222)
        return 'I'-'A'; 
    //Todas J, K, L, M, N están en ascii simple.
    if(c == 164 || c == 165) //Ñ
        return 26;
    if(
        c == 79 || c == 111 || (c >= 147 && c <= 149) || c == 153 || c == 155 ||
        c == 157 || c == 162 || c == 167 || c == 224 || (c >= 226 && c <= 229)
    )
        return 'O'-'A';
    //Todas P, Q, R, S, T están ascii simple.
    if(
        c == 85 || c == 117 || c == 129 || c == 150 || c == 151 ||
        c == 154 ||c == 163 || (c >= 233 && c <= 235)
    )
        return 'U'-'A';
    //Todas V, W, X están en ascii simple
    if(c == 89 || c == 121 || c == 152 || c == 236 || c == 237)
        return 'Y'-'A';
    //Todas Z estan en ascii simple

    //Detección de letras mayúsculas en ascii simple
    if(c >= 65 && c <= 90)
        return c - 'A';
    //Detección de letras minúsculas en ascii simple
    if(c >= 97 && c <= 122)
        return c - 'a';

    return -1; //No es una letra.
}

//Convierte un carácter de ISO_8859_1 a una letra del alfabeto español.
int char_to_letter_ISO_8859_1(uint8_t c){
    if(c == 65 || c == 97 || c == 170 || (c >= 192 && c <= 197) || (c >= 224 && c <= 229))
        return 'A'-'A';
    //todas las variantes de B se encuentran en ascii simple.
    if(c == 67 || c == 99 || c == 199 || c == 231)
        return 'C'-'A';
    if(c == 68 || c == 100 || c == 208 || c == 240)
        return 'D'-'A';
    if(c == 69 || c == 101 || (c >= 200 && c <= 203 || (c >= 232 && c <= 235)))
        return 'E'-'A';
    //Todas las variantes de F, G, H están en ascii simple.
    if(c == 73 || c == 105 || (c >= 204 && c <= 207) || (c >= 236 && c <= 239))
        return 'I'-'A'; 
    //Todas J, K, L, M, N están en ascii simple.
    if(c == 209 || c == 241) //Ñ
        return 26;
    if(
        c == 79 || c == 111 || c == 186 || (c >= 210 && c <= 214) ||
        c == 216 || (c >= 242 && c <= 246) || c == 248
    )
        return 'O'-'A';
    //Todas P, Q, R están en ascii simple
    if(c == 83 || c == 15 || c == 138 || c == 154)
        return 'S'-'A';
    //Todas T están en ascii simple
    if(c == 85 || c == 117 || (c >= 217 && c <= 220) || (c >= 249 && c <= 252))
        return 'U'-'A';
    //Todas V, W, X son ascii simple
    if(c == 89 || c == 121 || c == 159 || c == 221 || c == 253 || c == 255)
        return 'Y'-'A';
    if(c == 90 || c == 122 || c == 142 || c == 158)
        return 'Z' - 'A';

    //Detección de letras mayúsculas en ascii simple
    if(c >= 65 && c <= 90)
        return c - 'A';
    //Detección de letras minúsculas en ascii simple
    if(c >= 97 && c <= 122)
        return c - 'a';

    return -1; //No es una letra.
}

//Compara lexicograficamente dos strings.
int compara_str(char *str1, char *str2){
    int diff = 0;
    unsigned char curr1, curr2;
    for(int i=0; 1; ++i){//Ciclo infinito
        curr1 = *(str1 + i);
        curr2 = *(str2 + i);
        if(curr1 == '\0' && curr2 == '\0') //Si ambos apuntan al fin, son iguales.
            return 0;
        if(curr1 == '\0'){
            //Si curr1 llega antes al fin, str1 es lexicograficamente menor
            //Aparece antes en el diccionario
            return -simple_char_to_letter(curr2) - 1;
        }
        if(curr2 == '\0') //Si termina antes curr2, str1 es lexicograficamente mayor
            return simple_char_to_letter(curr1) + 1;
        //Si aun hay caracteres a comparar. Comparalos.
        diff = simple_char_to_letter(curr1) - simple_char_to_letter(curr2);
        if(diff != 0)
            return diff;
    }
}
