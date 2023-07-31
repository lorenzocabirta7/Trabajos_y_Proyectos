#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "kronos.h"
#include "increidle.h"

#define CONTRASENIA_CORRECTA_MAX 10

int main(){
    juego_t juego1;

    char CONTRASENIA_CORRECTA [CONTRASENIA_CORRECTA_MAX];
    strcpy(CONTRASENIA_CORRECTA,"KRONOS");

    srand ((unsigned)time(NULL));

    char contrasenia_adivinada[MAX_CONTRASENIA];
    bool contrasenia_completa = false;
    char movimiento = ' ';
    void adivinar_contrasenia(char contrasenia_adivinada[MAX_CONTRASENIA]);

    if (strcmp(contrasenia_adivinada, CONTRASENIA_CORRECTA) == 0)
    {
        contrasenia_completa = true;
    }else contrasenia_completa = false;

    inicializar_juego(&juego1, contrasenia_completa);
    do{
    imprimir_terreno(juego1);
    realizar_jugada(&juego1, movimiento);
    imprimir_terreno(juego1);

    }while(estado_juego(juego1) == 0);

    
    return 0;
}
