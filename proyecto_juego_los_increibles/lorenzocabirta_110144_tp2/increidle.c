#include <stdio.h>
#include <stdbool.h>
#include "increidle.h"

const char A_GENERICO = 'A';
const char B_GENERICO = 'B';
const char C_GENERICO = 'C';
const char D_GENERICO = 'D';

const char K_CONTRASENIA = 'K';
const char R_CONTRASENIA = 'R';
const char O_CONTRASENIA = 'O';
const char N_CONTRASENIA = 'N';
const char S_CONTRASENIA = 'S';
const char X_CONTRASENIA = 'X';

const char INICIALIZADOR_INCORRECTO = '0';

const char A_PREGUNTA_1 = 'A';

const char C_PREGUNTA_2 = 'C';

#define MAX_CANTIDAD_VECTOR_PREGUNTA_3 5

const int RESPUESTA_CORRECTA_PREGUNTA_4 = 95;

const char C_PREGUNTA_5 = 'C';


//VERIFICADOR DE CARACTER DENTRO DEL RANGO.
//PRE: -
//POST: Valida que el dato ingresado sea una letra que este dentro del rango.
bool es_respuesta_valida_letras(char validador_letras){
    return(validador_letras == A_GENERICO || validador_letras == B_GENERICO || validador_letras == C_GENERICO || validador_letras == D_GENERICO);
}

//VERIFICADOR DE NÚMERO DENTRO DEL RANGO.
//PRE: -
//POST: Valida que el dato ingresado sea un numero que este dentro del rango.
bool es_respuesta_valida_numero(int validador_numero){
    return(validador_numero >= 1 && validador_numero <= 100);
}

//VERIFICADOR DE NÚMEROS PRIMOS.
//PRE: -
//POST: Verifica si un numero es primo o no.
bool es_numero_primo(int numero){
    int contador = 0;
    for(int i = numero; i > 0; i--){
        if(numero % i == 0){
            contador++;
        }
    }
    if(contador == 2){
        return true;
    }else{
        return false;
    }

}


//PREGUNTA NÚMERO 1
//PRE: Debe recibir un caracter A, B, C o D.
//POST: Guarda un valor determinado en la variable correspondiente.
void pregunta_numero_1(char* respuesta_usuario_pregunta_1){
    printf("Pregunta número 1: ¿Cuál es el código de emergencia utilizado en Monsters Inc. cuando uno de los personajes tiene una media humana pegada a su cuerpo?\n");
    printf("OPCIONES: \n A)3312 \n B)3317 \n C)2312 \n D)2031 \n");
    printf("Su respuesta: ");
    scanf(" %c", respuesta_usuario_pregunta_1);

    while(!es_respuesta_valida_letras(*respuesta_usuario_pregunta_1)){
        printf("Por favor ingrese una respuesta válida (A, B, C o D): ");
        scanf(" %c", respuesta_usuario_pregunta_1);
    }

    if(*respuesta_usuario_pregunta_1 == A_PREGUNTA_1){
        *respuesta_usuario_pregunta_1 = K_CONTRASENIA;
    }else{
        *respuesta_usuario_pregunta_1 = X_CONTRASENIA;
    }
}

//PREGUNTA NÚMERO 2
//PRE: Debe recibir un caracter A, B, C o D.
//POST: Guarda un valor determinado en la variable correspondiente.
void pregunta_numero_2(char* respuesta_usuario_pregunta_2){
    printf("Pregunta número 2: ¿Cuál era el nombre del pez mascota de Lilo?\n");
    printf("OPCIONES: \n A)Stitch \n B)Pez \n C)Pato \n D)Aurelio \n");
    printf("Su respuesta: ");
    scanf(" %c", respuesta_usuario_pregunta_2);

    while(!es_respuesta_valida_letras(*respuesta_usuario_pregunta_2)){
        printf("Por favor ingrese una respuesta válida (A, B, C o D): ");
        scanf(" %c", respuesta_usuario_pregunta_2);
    }

    if(*respuesta_usuario_pregunta_2 == C_PREGUNTA_2){
        *respuesta_usuario_pregunta_2 = R_CONTRASENIA;
    }else{
        *respuesta_usuario_pregunta_2 = X_CONTRASENIA;
    }
}

//PREGUNTA NÚMERO 3
//PRE: Debe recibir 5 números, los cuales deben estar entre 1 y 100. El tope del vector debe ser 0.
//POST: Guarda 5 números en un vector. Guarda un valor determinado en la variable correspondiente.
void pregunta_numero_3(int vector_pregunta_3[MAX_CANTIDAD_VECTOR_PREGUNTA_3], int* tope_vector_pregunta_3, char* respuesta_usuario_pregunta_3){
    printf("Pregunta número 3: Tadashi necesita que lo ayudes con unos cálculos. Ingrese 5 números, todos deben ser primos.\n");
    
    for(; *tope_vector_pregunta_3 < MAX_CANTIDAD_VECTOR_PREGUNTA_3; (*tope_vector_pregunta_3)++){
        printf("Ingrese un número primo entre 1 y 100: ");
        scanf("%i", &vector_pregunta_3[*tope_vector_pregunta_3]);

        while(!es_respuesta_valida_numero(vector_pregunta_3[*tope_vector_pregunta_3])){
            printf("Por favor ingrese una respuesta válida (Número entre 1 y 100): ");
            scanf("%i", &vector_pregunta_3[*tope_vector_pregunta_3]);
        }
    }
        if(es_numero_primo(vector_pregunta_3[0]) == true
            && es_numero_primo(vector_pregunta_3[1]) == true
            && es_numero_primo(vector_pregunta_3[2]) == true
            && es_numero_primo(vector_pregunta_3[3]) == true
            && es_numero_primo(vector_pregunta_3[4]) == true)
        {
            *respuesta_usuario_pregunta_3 = O_CONTRASENIA;
        }else{
            *respuesta_usuario_pregunta_3 = X_CONTRASENIA;
        }
    
    

}

//PREGUNTA NÚMERO 4
//PRE: Debe recibir un número, el cual debe estar entre 1 y 100.
//POST: Guarda un valor determinado en la variable correspondiente.
void pregunta_numero_4(char* respuesta_usuario_pregunta_4, int* numero_del_rayo_usuario){
    printf("Pregunta número 4: ¿Qué número lleva el Rayo McQueen?\n");
    printf("La respuesta debe ser un número del 1 al 100.\n");
    printf("Su respuesta: ");
    scanf("%i", numero_del_rayo_usuario);

    while(!es_respuesta_valida_numero(*numero_del_rayo_usuario)){
        printf("Por favor ingrese una respuesta válida (Número entre 1 y 100): ");
        scanf("%i", numero_del_rayo_usuario);
    }

    if(*numero_del_rayo_usuario == RESPUESTA_CORRECTA_PREGUNTA_4){
        *respuesta_usuario_pregunta_4 = N_CONTRASENIA;
    }else{
        *respuesta_usuario_pregunta_4 = X_CONTRASENIA;
    }
}

//PREGUNTA NÚMERO 5
//PRE: Debe recibir un caracter A, B, C o D.
//POST: Guarda un valor determinado en la variable correspondiente.
void pregunta_numero_5(char* respuesta_usuario_pregunta_5){
    printf("Pregunta número 5: ¿Cómo se llama el tigre de la princesa Jazmín?\n");
    printf("OPCIONES: \n A)Zafiro \n B)Abú \n C)Rajah \n D)Jafar \n");
    printf("Su respuesta: ");
    scanf(" %c", respuesta_usuario_pregunta_5);

    while(!es_respuesta_valida_letras(*respuesta_usuario_pregunta_5)){
        printf("Por favor ingrese una respuesta válida (A, B, C o D): ");
        scanf(" %c", respuesta_usuario_pregunta_5);
    }

    if(*respuesta_usuario_pregunta_5 == C_PREGUNTA_5){
        *respuesta_usuario_pregunta_5 = S_CONTRASENIA;
    }else{
        *respuesta_usuario_pregunta_5 = X_CONTRASENIA;
    }
}


void adivinar_contrasenia(char contrasenia_adivinada[MAX_CONTRASENIA]){
    char respuesta_usuario_pregunta_1 = INICIALIZADOR_INCORRECTO;
    pregunta_numero_1(&respuesta_usuario_pregunta_1);

    char respuesta_usuario_pregunta_2 = INICIALIZADOR_INCORRECTO;
    pregunta_numero_2(&respuesta_usuario_pregunta_2);

    int vector_pregunta_3[MAX_CANTIDAD_VECTOR_PREGUNTA_3];
    int tope_vector_pregunta_3 = 0;
    char respuesta_usuario_pregunta_3 = INICIALIZADOR_INCORRECTO;
    pregunta_numero_3(vector_pregunta_3, &tope_vector_pregunta_3, &respuesta_usuario_pregunta_3);

    char respuesta_usuario_pregunta_4 = INICIALIZADOR_INCORRECTO;
    int numero_del_rayo_usuario = 0;
    pregunta_numero_4(&respuesta_usuario_pregunta_4, &numero_del_rayo_usuario);

    char respuesta_usuario_pregunta_5 = INICIALIZADOR_INCORRECTO;
    pregunta_numero_5(&respuesta_usuario_pregunta_5);

        
        contrasenia_adivinada[0] = respuesta_usuario_pregunta_1;
        contrasenia_adivinada[1] = respuesta_usuario_pregunta_2;
        contrasenia_adivinada[2] = respuesta_usuario_pregunta_3;
        contrasenia_adivinada[3] = respuesta_usuario_pregunta_4;
        contrasenia_adivinada[4] = respuesta_usuario_pregunta_3;
        contrasenia_adivinada[5] = respuesta_usuario_pregunta_5;

}