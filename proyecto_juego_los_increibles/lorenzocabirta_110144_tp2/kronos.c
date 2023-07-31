#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "kronos.h"

const char ROBOT = 'R';
const char LASER = 'L';
const char PINZA = 'P';
const char SUPERTRAJE = 'T';
const char SALIDA = 'S';
const char MRINCREIBLE = 'I';
const char VIOLETA = 'V';
const char DASH = 'D';
const char ELASTICGIRL = 'E';

const char ABAJO = 'S';
const char ARRIBA = 'W';
const char IZQUIERDA = 'A';
const char DERECHA = 'D';
const char ACTIVAR_SUPERPODER = 'C';

const int CANTIDAD_DE_ROBOTS = 4;
const int CANTIDAD_DE_PINZAS = 16;
const int CANTIDAD_DE_PERSONAJES = 4;
const int CANTIDAD_DE_TRAJES = 4;

const int PRIMER_CUADRANTE = 1;
const int SEGUNDO_CUADRANTE = 2;
const int TERCER_CUADRANTE = 3;
const int CUARTO_CUADRANTE = 4;
const int MOVIMIENTOS_CON_PODER = 5;
const int MOVIMIENTOS_ELASTIC_GIRL = 25;
const int MOVIMIENTOS_VIOLETA = 30;
const int MOVIMIENTOS_DASH = 20;
const int MOVIMIENTOS_INCREIBLE = 15;

const int CUATRO = 4;
const int CERO = 0;
const int TRES = 3;
const int CINCO = 5;
const int SEIS = 6;
const int DIEZ = 10;

const char VACIO = '.';

#define TAMANIO_MAX_TABLERO 100
#define TOPE_FILAS_MATRIZ 20
#define TOPE_COLUMNAS_MATRIZ 20

//PRE: -
//POST: Devuelve un par ordenado aleatorio, dependiendo del cuadrante recibido.
coordenada_t posicion_random(int cuadrante){
        coordenada_t coordenada;
                if(cuadrante == 1){
                    coordenada.fila = rand() % 9;
                    coordenada.columna = rand() % 9;
                }else if(cuadrante == 2){
                    coordenada.fila = rand() % 9 + 10;
                    coordenada.columna = rand() % 9 + 10;
                }else if(cuadrante == 3){
                    coordenada.fila = rand() % 9 + 10;
                    coordenada.columna = rand() % 9;
                }else if(cuadrante == 4){
                    coordenada.fila = rand() % 9;
                    coordenada.columna = rand() % 9 + 10;
                }
        return coordenada;
}


//PRE: 
//POST:
void lasers_posicion_0(robot_t robots[MAX_ROBOTS], int numero_de_robot, int* longitud_laser){
        for(int i = 0; i < *longitud_laser; i++){
            robots[numero_de_robot].lasers[i].fila = robots[numero_de_robot].posicion.fila - (i+1);
            robots[numero_de_robot].lasers[i].columna = robots[numero_de_robot].posicion.columna;
        }
        for(int j = *longitud_laser; j < *longitud_laser*2; j++){
            robots[numero_de_robot].lasers[j].columna = robots[numero_de_robot].posicion.columna + (j+1-*longitud_laser);
            robots[numero_de_robot].lasers[j].fila = robots[numero_de_robot].posicion.fila;
        }
}

//PRE: 
//POST:
void lasers_posicion_1(robot_t robots[MAX_ROBOTS], int numero_de_robot, int* longitud_laser){
        for(int i = 0; i < *longitud_laser; i++){
            robots[numero_de_robot].lasers[i].fila = robots[numero_de_robot].posicion.fila + (i+1);
            robots[numero_de_robot].lasers[i].columna = robots[numero_de_robot].posicion.columna;
        }
        for(int j = *longitud_laser; j < *longitud_laser*2; j++){
            robots[numero_de_robot].lasers[j].columna = robots[numero_de_robot].posicion.columna + (j+1-*longitud_laser);
            robots[numero_de_robot].lasers[j].fila = robots[numero_de_robot].posicion.fila;
        }
}

//PRE: 
//POST:
void lasers_posicion_2(robot_t robots[MAX_ROBOTS], int numero_de_robot, int* longitud_laser){
        for(int i = 0; i < *longitud_laser; i++){
            robots[numero_de_robot].lasers[i].fila = robots[numero_de_robot].posicion.fila + (i+1);
            robots[numero_de_robot].lasers[i].columna = robots[numero_de_robot].posicion.columna;
        }
        for(int j = *longitud_laser; j < *longitud_laser*2; j++){
            robots[numero_de_robot].lasers[j].columna = robots[numero_de_robot].posicion.columna - (j+1-*longitud_laser);
            robots[numero_de_robot].lasers[j].fila = robots[numero_de_robot].posicion.fila;
        }
}

//PRE: 
//POST:
void lasers_posicion_3(robot_t robots[MAX_ROBOTS], int numero_de_robot, int* longitud_laser){
        for(int i = 0; i < *longitud_laser; i++){
            robots[numero_de_robot].lasers[i].fila = robots[numero_de_robot].posicion.fila - (i-1);
            robots[numero_de_robot].lasers[i].columna = robots[numero_de_robot].posicion.columna;
        }
        for(int j = *longitud_laser; j < *longitud_laser*2; j++){
            robots[numero_de_robot].lasers[j].columna = robots[numero_de_robot].posicion.columna - (j+1-*longitud_laser);
            robots[numero_de_robot].lasers[j].fila = robots[numero_de_robot].posicion.fila;
        }
}


//PRE: -
//POST: Inicializa aleatoriamente un robot en cada cuadrante.
void inicializar_robots(robot_t robots[MAX_ROBOTS], int* tope_robots, bool contrasenia_completa, int* longitud_laser){
        *tope_robots = CANTIDAD_DE_ROBOTS;
        
        for(int j = 0; j < robots->tope_lasers; j++){
            if(contrasenia_completa){
                robots->tope_lasers = SEIS;
            }else robots->tope_lasers = DIEZ;
        }

        for(int i = 0; i < *tope_robots; i++){
            robots[i].posicion = posicion_random(i+1);
            /*int numero_random = rand() % 3;
            if(numero_random == 0){
                lasers_posicion_0(robots, i, longitud_laser);
            }else if(numero_random == 1){
                lasers_posicion_1(robots, i, longitud_laser);
            }else if(numero_random == 2){
                lasers_posicion_2(robots, i, longitud_laser);
            }else if(numero_random == 3){
                lasers_posicion_3(robots, i, longitud_laser);
            }*/
        }
}

//PRE: -
//POST: Un numero random entre 0 y 3 determina la direccion de los lasers, para que luego estos sean inicializados.
void inicializar_lasers(juego_t* juego, bool contrasenia_completa){
        for(int i = 0; i < CANTIDAD_DE_ROBOTS; i++){
            if(contrasenia_completa){
                juego->robots[i].tope_lasers = SEIS;
            }else juego->robots[i].tope_lasers = DIEZ;
        }

        for(int g = 0; g < juego->tope_robots; g++){
            int numero_aleatorio = rand() % 3;

            //DIRECCIÓN 1//
            if(numero_aleatorio == 0){
                for(int i = 0; i < juego->longitud_laser; i++){
                    juego->robots[g].lasers[i].fila = juego->robots[g].posicion.fila + (i+1);
                    juego->robots[g].lasers[i].columna = juego->robots[g].posicion.columna;    
                }
                for(int j = juego->longitud_laser; j < juego->longitud_laser * 2; j++){
                    juego->robots[g].lasers[j].columna = juego->robots[g].posicion.columna + (j+1-juego->longitud_laser);
                    juego->robots[g].lasers[j].fila = juego->robots[g].posicion.fila;
                }
            }
            //DIRECCIÓN 2//
            else if(numero_aleatorio == 1){
                for(int i = 0; i < juego->longitud_laser; i++){
                    juego->robots[g].lasers[i].fila = juego->robots[g].posicion.fila - (i+1);
                    juego->robots[g].lasers[i].columna = juego->robots[g].posicion.columna;
                }
                for(int j = juego->longitud_laser; j < juego->longitud_laser * 2; j++){
                    juego->robots[g].lasers[j].columna = juego->robots[g].posicion.columna + (j+1-juego->longitud_laser);
                    juego->robots[g].lasers[j].fila = juego->robots[g].posicion.fila;
                }
            }
            //DIRECCIÓN 3//
            else if(numero_aleatorio == 2){
                for(int i = 0; i < juego->longitud_laser; i++){
                    juego->robots[g].lasers[i].fila = juego->robots[g].posicion.fila + (i+1);
                    juego->robots[g].lasers[i].columna = juego->robots[g].posicion.columna;
                }
                for (int j = juego->longitud_laser; j < juego->longitud_laser * 2; j++){
                    juego->robots[g].lasers[j].columna = juego->robots[g].posicion.columna - (j+1-juego->longitud_laser);
                    juego->robots[g].lasers[j].fila = juego->robots[g].posicion.fila;
                }
            }
            //DIRECCIÓN 4//
            else if(numero_aleatorio == 3){
                for (int i = 0; i < juego->longitud_laser; i++){
                    juego->robots[g].lasers[i].fila = juego->robots[g].posicion.fila - (i-1);
                    juego->robots[g].lasers[i].columna = juego->robots[g].posicion.columna;
                }
                for(int j = juego->longitud_laser; j < juego->longitud_laser * 2; j++){
                    juego->robots[g].lasers[j].columna = juego->robots[g].posicion.columna - (j+1-juego->longitud_laser);
                    juego->robots[g].lasers[j].fila = juego->robots[g].posicion.fila;
                }
            }
}
}


//PRE: -
//POST: Inicializa 4 pinzas en cada cuadrante.
void inicializar_pinzas(coordenada_t pinzas[MAX_PINZAS], int* tope_pinzas){
        *tope_pinzas = CUATRO;

        for(int i = 0; i < *tope_pinzas; i++){
            pinzas[i] = posicion_random(PRIMER_CUADRANTE);
        }


        for(int i = *tope_pinzas; i < *tope_pinzas*2; i++){
            pinzas[i] = posicion_random(SEGUNDO_CUADRANTE);
        } 

        for(int i = *tope_pinzas*2; i < *tope_pinzas*3; i++){
            pinzas[i] = posicion_random(TERCER_CUADRANTE);
        }

        for(int i = *tope_pinzas*3; i < *tope_pinzas*4; i++){
            pinzas[i] = posicion_random(CUARTO_CUADRANTE);
        }
}

//PRE: -
//POST: Inicializa cada supertraje en su respectivo cuadrante, con las variables de recolectado y usado en falso.
void inicializar_supertrajes(supertraje_t supertrajes[MAX_SUPERTRAJES], int* tope_supertraje){
        *tope_supertraje = CANTIDAD_DE_TRAJES;

        for(int i = 0; i < *tope_supertraje; i++){
            supertrajes[i].recolectado = false;
            supertrajes[i].usado =false;
            supertrajes[i].cuadrante = i + 1;
            supertrajes[i].posicion = posicion_random(supertrajes[i].cuadrante);
        }
}

//PRE: -
//POST: Inicializa cada personaje en el cuadrante correspondiente, asigna la cantidad de movimientos maxima de los personajes, la cantidad de movimientos con poder y el cuadrante inicial. Las variables de poder activado y tiene supertraje empiezan en falso.
void inicializar_personajes(personaje_t personajes[MAX_PERSONAJES], int* tope_personajes){
        *tope_personajes = CANTIDAD_DE_PERSONAJES;

        for(int i = 0; i < *tope_personajes; i++){
            personajes[i].poder_activado = false;
            personajes[i].tiene_supertraje = false;
            personajes[i].cuadrante_inicial = i+1;
            personajes[i].movimientos_con_poder = MOVIMIENTOS_CON_PODER;
            personajes[i].posicion = posicion_random(personajes[i].cuadrante_inicial);
        }

        personajes[0].movimientos = MOVIMIENTOS_ELASTIC_GIRL;
        personajes[1].movimientos = MOVIMIENTOS_VIOLETA;
        personajes[2].movimientos = MOVIMIENTOS_DASH;
        personajes[3].movimientos = MOVIMIENTOS_INCREIBLE;
}

//PRE: -
//POST: Realiza el llamado a las funciones correspondientes para inicializar cada elemento. Dependiendo de que la contrasenia este completa o no, asigna un valor determinado a la longitud de los lasers. Inicializa el id de jugador actual en 1.
void inicializar_juego(juego_t* juego, bool contrasenia_completa){
        juego->id_personaje_actual = 1;
        
        if(contrasenia_completa == true){
            juego->longitud_laser = TRES;
        }else{
            juego->longitud_laser = CINCO;
        }

        inicializar_robots(juego->robots, &juego->tope_robots, contrasenia_completa, &juego->longitud_laser);
        inicializar_lasers(juego, contrasenia_completa);
        inicializar_pinzas(juego->pinzas, &juego->tope_pinzas);
        inicializar_supertrajes(juego->supertrajes, &juego->tope_supertraje);
        inicializar_personajes(juego->personajes, &juego->tope_personajes);
}

//PRE: Recibe la matriz, con sus maximos. Los elementos deben estar previamente inicializados.
//POST: Asigna en cada coordenada de la matriz el valor de cada elemento.
void inicializar_terreno(juego_t juego, char matriz_terreno[TAMANIO_MAX_TABLERO][TAMANIO_MAX_TABLERO]){
    //LUGARES VACIOS//
        for(int a = 0; a < TOPE_FILAS_MATRIZ; a++){
            for(int b = 0; b < TOPE_COLUMNAS_MATRIZ;b ++){
                matriz_terreno[a][b] = VACIO;
            }
        }

    //ROBOTS//
        for(int r = 0; r < juego.tope_robots; r++){
            matriz_terreno[juego.robots[r].posicion.fila][juego.robots[r].posicion.columna] = ROBOT;
        }

    //LASERS//
        for(int i = 0; i < juego.tope_robots; i++){
            for(int j = 0; j < juego.robots[i].tope_lasers; j++){
                if((juego.robots[i].lasers[j].fila >= 0 || juego.robots[i].lasers[j].fila < TOPE_FILAS_MATRIZ) && 
                (juego.robots[i].lasers[j].columna >= 0 || juego.robots[i].lasers[j].columna < TOPE_COLUMNAS_MATRIZ)){
                    matriz_terreno[juego.robots[i].lasers[j].fila][juego.robots[i].lasers[j].columna] = LASER;
                }
            }
        }

    //PINZAS//
        for(int p = 0; p < juego.tope_personajes*4; p++){
            matriz_terreno[juego.pinzas[p].fila][juego.pinzas[p].columna] = PINZA;
        }

    //SUPERTRAJES//
        for(int s = 0; s < juego.tope_supertraje; s++){
            if(juego.supertrajes[s].recolectado == false){
                matriz_terreno[juego.supertrajes[s].posicion.fila][juego.supertrajes[s].posicion.columna] = SUPERTRAJE;
            }else{matriz_terreno[juego.supertrajes[s].posicion.fila][juego.supertrajes[s].posicion.columna] = VACIO;
        }
    }

    //PERSONAJES//
        matriz_terreno[juego.personajes[0].posicion.fila][juego.personajes[0].posicion.columna] = ELASTICGIRL;
        matriz_terreno[juego.personajes[1].posicion.fila][juego.personajes[1].posicion.columna] = VIOLETA;
        matriz_terreno[juego.personajes[2].posicion.fila][juego.personajes[2].posicion.columna] = DASH;
        matriz_terreno[juego.personajes[3].posicion.fila][juego.personajes[3].posicion.columna] = MRINCREIBLE;

    //SALIDA//
        matriz_terreno[0][19] = SALIDA;
}

//PRE: -
//POST: Realiza el llamado a la funcion de inicializacion del terreno e imprime el tablero de juego con sus elementos.
void imprimir_terreno(juego_t juego){
        char matriz_terreno [TAMANIO_MAX_TABLERO][TAMANIO_MAX_TABLERO];

        inicializar_terreno(juego, matriz_terreno);
        system ("clear");
        for(int i = 0; i < TOPE_FILAS_MATRIZ; i++){
            for(int j = 0; j < TOPE_COLUMNAS_MATRIZ; j++){
                printf("%c ", matriz_terreno[i][j]);
            }
            printf("\n");
        }
}

//PRE: -
//POST: Verifica que la letra que ingresa el usuario sea valida.
bool es_accion_valida(char respuesta_valida){
        return(respuesta_valida == ARRIBA || respuesta_valida == ABAJO || respuesta_valida == DERECHA || respuesta_valida == IZQUIERDA || respuesta_valida == ACTIVAR_SUPERPODER);
}

//PRE:
//POST: Elasticgirl avanza 3 posiciones utilizando un movimiento.
void poder_elasticgirl(juego_t* juego, char movimiento){
        if(juego->personajes[0].poder_activado == true){ 
            do{printf("Tenes el poder de elasticgirl activado, a donde queres moverte?\n");
            scanf(" %c", &movimiento);

            if(movimiento == ARRIBA){
                (juego->personajes[0].posicion.fila) - 3;
                juego->personajes[0].movimientos --;
            }else if(movimiento == ABAJO){
                (juego->personajes[0].posicion.fila) + 3;
                juego->personajes[0].movimientos --;            
            }else if(movimiento == DERECHA){
                (juego->personajes[0].posicion.columna) +3;
                juego->personajes[0].movimientos --;
            }else if(movimiento == IZQUIERDA){
                (juego->personajes[0].posicion.columna) - 3;
                juego->personajes[0].movimientos --;
            }
            juego->personajes[0].movimientos_con_poder --;
        }while(juego->personajes[0].movimientos_con_poder > 0);

        juego->personajes[0].tiene_supertraje = false;
        juego->personajes[0].poder_activado = false;
    }
    
}

//PRE:
//POST
void poder_violeta(juego_t* juego){
    if(juego->personajes[1].poder_activado == true){
        {
            

        }
    }
}

//PRE:
//POST: Dash cambia su posicion a una posicion aleatoria en el cuarto cuadrante.
void poder_dash(juego_t* juego, char movimiento){
        if(juego->personajes[2].poder_activado == true){
            juego->personajes[2].posicion = posicion_random(CUATRO);
            juego->personajes[2].movimientos_con_poder = CERO;
            juego->personajes[2].poder_activado = false;
            juego->personajes[2].tiene_supertraje = false;
        }
}

//PRE:
//POST:
void poder_mister_increible(juego_t* juego){
    if(juego->personajes[3].poder_activado == true){

    }

}

//PRE: -
//POST: Verifica si la posicion del jugador coincide coincide con la posicion del supertraje de su cuadrante.
void tiene_supertraje(juego_t* juego){
        for(int i = 0; i < juego->tope_personajes; i++){
            if(juego->personajes[i].posicion.fila == juego->supertrajes[i].posicion.fila
                && juego->personajes[i].posicion.columna == juego->supertrajes[i].posicion.columna){
                    juego->personajes[i].tiene_supertraje = true;
            }else juego->personajes[i].tiene_supertraje = false;
        }
}

//PRE: -
//POST: Pregunta al usuario a donde quiere moverse o si desea activar su superpoder. Realiza los movimientos indicados.
void realizar_movimiento(juego_t* juego, char movimiento){
        tiene_supertraje(juego);
        printf("Elegí a que dirección queres moverte o activa tu supertraje. / Movimientos disponibles = %i\n", juego->personajes[juego->id_personaje_actual - 1].movimientos);
        scanf(" %c", &movimiento);
            while(!es_accion_valida(movimiento)){
                printf("Por favor realiza una accion valida (W,A,S,D o C): ");
                scanf(" %c", &movimiento);
            }
            if(movimiento == ARRIBA){
                juego->personajes[juego->id_personaje_actual - 1].posicion.fila --;
                juego->personajes[juego->id_personaje_actual - 1].movimientos --;
            }else if(movimiento == ABAJO){
                juego->personajes[juego->id_personaje_actual - 1].posicion.fila ++;
                juego->personajes[juego->id_personaje_actual -1].movimientos --;
            }else if(movimiento == DERECHA){
                juego->personajes[juego->id_personaje_actual - 1].posicion.columna ++;
                juego->personajes[juego->id_personaje_actual - 1].movimientos --;
            }else if (movimiento == IZQUIERDA){
                juego->personajes[juego->id_personaje_actual - 1].posicion.columna --;
                juego->personajes[juego->id_personaje_actual - 1].movimientos --;
            }else if(movimiento == ACTIVAR_SUPERPODER){
                /*if(juego->id_personaje_actual == 1 && juego->personajes[0].tiene_supertraje == true){
                    juego->personajes[0].poder_activado = true;
                    poder_elasticgirl(juego, movimiento);
                }else*/ if(juego->id_personaje_actual == 2 && juego->personajes[1].tiene_supertraje == true){
                    /*******/
                    juego->personajes[1].poder_activado = true;
                    //poder violeta
                }else if(juego->id_personaje_actual == 3 && juego->personajes[2].tiene_supertraje == true){
                    juego->personajes[2].poder_activado = true;
                    poder_dash(juego, movimiento);
                }else if(juego->id_personaje_actual == 4 && juego->personajes[3].tiene_supertraje == true){
                    /******/
                    juego->personajes[3].poder_activado = true;
                    //poder increible
                }else{
                printf("Para usar tu superpoder, primero debes recolectar tu supertraje :(\n");
                }
            }
}


bool personaje_pisa_laser(juego_t* juego){
        bool pisa_laser = false;
        for(int i = 0; i < juego->tope_robots; i++){
            for(int j = 0; j < juego->robots[i].tope_lasers; j++){
                if(juego->personajes[juego->id_personaje_actual - 1].posicion.fila == juego->robots[i].lasers[j].fila
                    && juego->personajes[juego->id_personaje_actual - 1].posicion.columna == juego->robots[i].lasers[j].columna){
                        pisa_laser = true;
                    }
            }
        }return pisa_laser;
}

//PRE: -
//POST: Verifica si el personaje actual esta pisando un robot y cambia el valor de la variable segun corresponda.
bool personaje_pisa_robot(juego_t* juego){
        bool pisa_robot = false;
        for(int i = 0; i < juego->tope_robots; i++){
            if(juego->personajes[juego->id_personaje_actual - 1].posicion.columna == juego->robots[i].posicion.columna
            && juego->personajes[juego->id_personaje_actual - 1].posicion.fila == juego->robots[i].posicion.fila){
                pisa_robot = true;
            }
        }
        return pisa_robot;
}

//PRE: -
//POST: Si un personaje pisa una pinza, se traslada aleatoriamente a una de las 8 posiciones posibles alrededor del robot de su cuadrante inicial.
void personaje_pisa_pinza(juego_t* juego){
        for(int i = 0; i < CANTIDAD_DE_PINZAS; i++){ 
            if(juego->personajes[juego->id_personaje_actual -1].posicion.fila == juego->pinzas[i].fila 
                && juego->personajes[juego->id_personaje_actual-1].posicion.columna == juego->pinzas[i].columna){
                int numero_aleatorio = rand() % 9;

                if(numero_aleatorio == 0){
                    juego->personajes[juego->id_personaje_actual - 1].posicion.fila = juego->robots[juego->id_personaje_actual - 1].posicion.fila + 1;
                    juego->personajes[juego->id_personaje_actual - 1].posicion.columna = juego->robots[juego->id_personaje_actual - 1].posicion.columna;
                }else if(numero_aleatorio == 1){
                    juego->personajes[juego->id_personaje_actual - 1].posicion.fila = juego->robots[juego->id_personaje_actual - 1].posicion.fila - 1;
                    juego->personajes[juego->id_personaje_actual - 1].posicion.columna = juego->robots[juego->id_personaje_actual - 1].posicion.columna;
                }else if(numero_aleatorio == 2){
                    juego->personajes[juego->id_personaje_actual - 1].posicion.fila = juego->robots[juego->id_personaje_actual - 1].posicion.fila;
                    juego->personajes[juego->id_personaje_actual - 1].posicion.columna = juego->robots[juego->id_personaje_actual - 1].posicion.columna + 1;
                }else if(numero_aleatorio == 3){
                    juego->personajes[juego->id_personaje_actual - 1].posicion.fila = juego->robots[juego->id_personaje_actual - 1].posicion.fila;
                    juego->personajes[juego->id_personaje_actual - 1].posicion.columna = juego->robots[juego->id_personaje_actual - 1].posicion.columna - 1;
                }else if(numero_aleatorio == 4){
                    juego->personajes[juego->id_personaje_actual - 1].posicion.fila = juego->robots[juego->id_personaje_actual - 1].posicion.fila + 1;
                    juego->personajes[juego->id_personaje_actual - 1].posicion.columna = juego->robots[juego->id_personaje_actual - 1].posicion.columna + 1;
                }else if(numero_aleatorio == 5){
                    juego->personajes[juego->id_personaje_actual - 1].posicion.fila = juego->robots[juego->id_personaje_actual - 1].posicion.fila + 1;
                    juego->personajes[juego->id_personaje_actual - 1].posicion.columna = juego->robots[juego->id_personaje_actual - 1].posicion.columna - 1;
                }else if (numero_aleatorio == 6){
                    juego->personajes[juego->id_personaje_actual - 1].posicion.fila = juego->robots[juego->id_personaje_actual - 1].posicion.fila - 1;
                    juego->personajes[juego->id_personaje_actual - 1].posicion.columna = juego->robots[juego->id_personaje_actual - 1].posicion.columna + 1;
                }else if(numero_aleatorio == 7){
                    juego->personajes[juego->id_personaje_actual - 1].posicion.fila = juego->robots[juego->id_personaje_actual - 1].posicion.fila - 1;
                    juego->personajes[juego->id_personaje_actual - 1].posicion.columna = juego->robots[juego->id_personaje_actual - 1].posicion.columna - 1;
                }
            }   
        }   
}

//PRE: -
//POST:
void cambiar_de_personaje(juego_t* juego){
        if(juego->personajes[juego->id_personaje_actual - 1].posicion.fila == juego->personajes[juego->id_personaje_actual].posicion.fila
            && juego->personajes[juego->id_personaje_actual - 1].posicion.columna == juego->personajes[juego->id_personaje_actual].posicion.columna){
                juego->id_personaje_actual++;
            }
}

void realizar_jugada(juego_t* juego, char movimiento){
        personaje_pisa_pinza(juego);
        personaje_pisa_laser(juego);
        personaje_pisa_robot(juego);
        realizar_movimiento(juego, movimiento);
    }

int estado_juego(juego_t juego){
        if(juego.personajes[3].posicion.fila == 0 && juego.personajes[3].posicion.columna == 19){
            return  1;
        }else if(juego.personajes[juego.id_personaje_actual - 1].movimientos == 0 || personaje_pisa_robot(&juego) == true || personaje_pisa_laser(&juego) == true){
            return -1;
        }
        return 0;
}

