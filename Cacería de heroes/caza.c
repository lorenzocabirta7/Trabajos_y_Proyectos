#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_NOMBRE 50
#define ESCRITURA "%i;%s;%i;%c\n"
#define LECTURA "%i;%[^;];%i;%c\n"
const char VIVO = 'V';
const char MUERTO = 'M';
const int MAX_EDAD = 100;
const int MIN_EDAD = 1;
const int MIN_ID = 0;
const int ARGUMENTOS_LISTAR = 3;
const int ARGUMENTOS_CONTACTAR = 4;
const int ARGUMENTOS_MODIFICAR = 6;
const int ARGUMENTOS_AGREGAR = 7;
const int ELEMENTOS_A_LEER = 4;
const int ARGV_POSICION_DOS = 2;
const int ARGV_POSICION_TRES = 3;
const int ARGV_POSICION_CUATRO = 4;
const int ARGV_POSICION_CINCO = 5;
const int ARGV_POSICION_SEIS = 6;

typedef struct superheroe
{
    int id;
    char nombre[MAX_NOMBRE];
    int edad;
    char estado;
} superheroe_t;

// PRE:
// POST: Verifica si el ID recibido existe.
bool existe_id(int id_recibido, int id_leido, FILE **archivo_original, FILE **archivo_auxiliar)
{
    if (id_recibido == id_leido)
    {
        fclose(*archivo_original);
        fclose(*archivo_auxiliar);
        remove("aux.csv");
        printf("El ID ingresado, ya existe, por favor agregar uno diferente.\n");
        return true;
    }
    return false;
}

// PRE:
// POST: Verifica que el ID recibido este en el rango correcto.
bool id_valido(int id)
{
    if (id < MIN_ID)
    {
        return false;
    }
    return true;
}

// PRE:
// POST: Verifica que la edad recibida este dentro del rango correspondiente.
bool edad_valida(int edad)
{
    if (edad < MIN_EDAD || edad > MAX_EDAD)
    {
        return false;
    }
    return true;
}

// PRE:
// POST: Verifica que el estado tenga un formato valido.
bool estado_valido(char *estado)
{
    if (strcmp(estado, "vivo") == 0 || strcmp(estado, "muerto") == 0)
    {
        return true;
    }
    return false;
}

// PRE:
// POST: Convierte un char a un string según corresponda.
void cambiar_estado_de_caracter_a_string(char estado_en_char, char estado_en_string[MAX_NOMBRE])
{
    if (estado_en_char == VIVO)
    {
        strcpy(estado_en_string, "Vivo");
    }
    else if (estado_en_char == MUERTO)
    {
        strcpy(estado_en_string, "Muerto");
    }
}

// PRE:
// POST: Convierte un string a un char según corresponda.
char cambiar_estado_de_string_a_caracter(char *estado_en_char, char estado_en_string[MAX_NOMBRE])
{
    if (strcmp(estado_en_string, "vivo") == 0)
    {
        *estado_en_char = VIVO;
    }
    else if (strcmp(estado_en_string, "muerto") == 0)
    {
        *estado_en_char = MUERTO;
    }
    return *estado_en_char;
}

// PRE: El archivo debe existir.
// POST: Imprime todos los superheroes presentes en el archivo por pantalla.
int listar_superheroes(char *archivo)
{
    FILE *heroes = fopen(archivo, "r");
    if (heroes == NULL)
    {
        perror("No se pudo abrir el archivo :(\n");
        return -1;
    }
    superheroe_t superheroe;
    int elementos_leidos = fscanf(heroes, LECTURA, &superheroe.id, superheroe.nombre, &superheroe.edad, &superheroe.estado);
    printf("- A continuación se muestran los superhéroes presentes y sus datos -\n\n");
    while (elementos_leidos == ELEMENTOS_A_LEER)
    {
        char heroe_vivo_o_muerto[MAX_NOMBRE];
        cambiar_estado_de_caracter_a_string(superheroe.estado, heroe_vivo_o_muerto);
        printf("ID | NOMBRE | EDAD | ESTADO \n");
        printf("%i;%s;%i;%s\n\n", superheroe.id, superheroe.nombre, superheroe.edad, heroe_vivo_o_muerto);
        elementos_leidos = fscanf(heroes, LECTURA, &superheroe.id, superheroe.nombre, &superheroe.edad, &superheroe.estado);
    }
    return 0;
}

// PRE: El archivo y el ID deben existir.
// POST: Imprime por pantalla los datos del superheroe contactado en caso de que este exista.
int contactar_superheroes(char *id, char *archivo)
{
    FILE *heroes = fopen(archivo, "r");
    if (heroes == NULL)
    {
        perror("No se pudo abrir el archivo :(\n");
        return -1;
    }
    FILE *archivo_auxiliar = fopen("auxiliar", "w");
    if (archivo_auxiliar == NULL)
    {
        perror("No se pudo abrir el archivo :(\n");
        fclose(heroes);
        return -1;
    }
    int id_heroe = atoi(id);
    bool existe_id = false;
    superheroe_t superheroe;
    int elementos_leidos = fscanf(heroes, LECTURA, &superheroe.id, superheroe.nombre, &superheroe.edad, &superheroe.estado);
    while (elementos_leidos == ELEMENTOS_A_LEER)
    {
        if (id_heroe != superheroe.id)
        {
            fprintf(archivo_auxiliar, ESCRITURA, superheroe.id, superheroe.nombre, superheroe.edad, superheroe.estado);
        }
        else if (id_heroe == superheroe.id)
        {
            char heroe_vivo_o_muerto[MAX_NOMBRE];
            cambiar_estado_de_caracter_a_string(superheroe.estado, heroe_vivo_o_muerto);
            printf("Contactaste correctamente para que te ayude en una mision a ID: %i | Nombre: %s | Edad: %i | Estado: %s\n", superheroe.id, superheroe.nombre, superheroe.edad, heroe_vivo_o_muerto);
            existe_id = true;
        }
        elementos_leidos = fscanf(heroes, LECTURA, &superheroe.id, superheroe.nombre, &superheroe.edad, &superheroe.estado);
    }
    if (!existe_id)
    {
        printf("El ID es inexistente, no se pudo contactar al superhéroe.\n");
    }
    fclose(heroes);
    fclose(archivo_auxiliar);
    rename("auxiliar", archivo);
    return 0;
}

// PRE: El archivo y el ID deben existir.
// POST: Modifica la edad y el estado del personaje.
int modificar_status(char *id, char *edad, char *estado, char *archivo)
{
    int edad_heroe_recibida = atoi(edad);
    int id_heroe_recibido = atoi(id);
    if (edad_valida(edad_heroe_recibida) == true && id_valido(id_heroe_recibido) == true && estado_valido(estado) == true)
    {
        FILE *heroes = fopen(archivo, "r");
        if (heroes == NULL)
        {
            perror("No se pudo abrir el archivo :(\n");
            return -1;
        }
        FILE *auxiliar = fopen("aux.csv", "w");
        if (auxiliar == NULL)
        {
            fclose(heroes);
            perror("No se pudo abrir el archivo :(\n");
            return -1;
        }
        char heroe_vivo_o_muerto = cambiar_estado_de_string_a_caracter(&heroe_vivo_o_muerto, estado);
        superheroe_t superheroe;
        int elementos_leidos = fscanf(heroes, LECTURA, &superheroe.id, superheroe.nombre, &superheroe.edad, &superheroe.estado);
        bool id_encontrado = false;
        while (elementos_leidos == ELEMENTOS_A_LEER)
        {
            if (id_heroe_recibido != superheroe.id)
            {
                fprintf(auxiliar, ESCRITURA, superheroe.id, superheroe.nombre, superheroe.edad, superheroe.estado);
            }
            else if (id_heroe_recibido == superheroe.id)
            {
                superheroe.edad = edad_heroe_recibida;
                superheroe.estado = heroe_vivo_o_muerto;
                fprintf(auxiliar, ESCRITURA, superheroe.id, superheroe.nombre, superheroe.edad, superheroe.estado);
                id_encontrado = true;
                printf("Modificaste correctamente a ID: %i | Nombre: %s | Edad: %i | Estado: %c. \n", superheroe.id, superheroe.nombre, superheroe.edad, heroe_vivo_o_muerto);
            }
            elementos_leidos = fscanf(heroes, LECTURA, &superheroe.id, superheroe.nombre, &superheroe.edad, &superheroe.estado);
        }
        if (!id_encontrado)
        {
            printf("No se encontró el superhéroe");
        }
        fclose(heroes);
        fclose(auxiliar);
        rename("aux.csv", archivo);
    }
    else
    {
        printf("Algo no está bien, revisa la linea de comandos. Si necesitas ayuda ejecutá lo siguiente -> ./caza ayuda\n");
    }
    return 0;
}

// PRE:
// POST: Agrega un heroe en un archivo nuevo.
int agregar_en_nuevo_archivo(FILE **archivo, int id, char *nombre, int edad, char *estado)
{
    char heroe_vivo_o_muerto = cambiar_estado_de_string_a_caracter(&heroe_vivo_o_muerto, estado);
    fprintf(*archivo, ESCRITURA, id, nombre, edad, heroe_vivo_o_muerto);
    printf("Agregaste correctamente a ID: %i | Nombre: %s | Edad: %i | Estado: %s\n", id, nombre, edad, estado);
    fclose(*archivo);
    return 0;
}

// PRE:
// POST: Agrega un superhéroe al archivo indicado.
int agregar_superheroes(char *id, char *nombre, char *edad, char *estado, char *archivo)
{
    int id_heroe_recibido = atoi(id);
    int edad_heroe = atoi(edad);
    if (edad_valida(edad_heroe) == true && id_valido(id_heroe_recibido) == true && estado_valido(estado) == true)
    {
        FILE *heroes = fopen(archivo, "r");
        if (heroes == NULL)
        {
            FILE *heroes = fopen(archivo, "w");
            agregar_en_nuevo_archivo(&heroes, id_heroe_recibido, nombre, edad_heroe, estado);
            if (heroes == NULL)
            {
                perror("No se pudo abrir el archivo :( \n");
                return -1;
            }
            return 0;
        }
        FILE *auxiliar = fopen("aux.csv", "w");
        if (auxiliar == NULL)
        {
            fclose(heroes);
            perror("No se pudo abrir el archivo :(\n");
            return -1;
        }
        char estado_heroe_vivo_o_muerto = cambiar_estado_de_string_a_caracter(&estado_heroe_vivo_o_muerto, estado);
        superheroe_t heroe;
        bool heroe_agregado = false;
        int elementos_leidos = fscanf(heroes, LECTURA, &heroe.id, heroe.nombre, &heroe.edad, &heroe.estado);
        while (elementos_leidos == ELEMENTOS_A_LEER && heroe_agregado == false)
        {
            if (existe_id(id_heroe_recibido, heroe.id, &heroes, &auxiliar) == true)
            {
                return -2;
            }
            if (id_heroe_recibido < heroe.id)
            {
                fprintf(auxiliar, ESCRITURA, id_heroe_recibido, nombre, edad_heroe, estado_heroe_vivo_o_muerto);
                heroe_agregado = true;
                printf("Agregaste correctamente a ID: %i | Nombre: %s | Edad: %i | Estado: %s\n", id_heroe_recibido, nombre, edad_heroe, estado);
            }
            fprintf(auxiliar, ESCRITURA, heroe.id, heroe.nombre, heroe.edad, heroe.estado);
            elementos_leidos = fscanf(heroes, LECTURA, &heroe.id, heroe.nombre, &heroe.edad, &heroe.estado);
        }
        while (feof(heroes) && heroe_agregado == false)
        {
            if (existe_id(id_heroe_recibido, heroe.id, &heroes, &auxiliar) == true)
            {
                return -2;
            }
            if (id_heroe_recibido > heroe.id)
            {
                fprintf(auxiliar, ESCRITURA, id_heroe_recibido, nombre, edad_heroe, estado_heroe_vivo_o_muerto);
                heroe_agregado = true;
                printf("Agregaste correctamente a ID: %i | Nombre: %s | Edad: %i | Estado: %s\n", id_heroe_recibido, nombre, edad_heroe, estado);
            }
        }
        while (elementos_leidos == ELEMENTOS_A_LEER)
        {
            if (existe_id(id_heroe_recibido, heroe.id, &heroes, &auxiliar) == true)
            {
                return -2;
            }
            fprintf(auxiliar, ESCRITURA, heroe.id, heroe.nombre, heroe.edad, heroe.estado);
            elementos_leidos = fscanf(heroes, LECTURA, &heroe.id, heroe.nombre, &heroe.edad, &heroe.estado);
        }
        fclose(heroes);
        fclose(auxiliar);
        rename("aux.csv", archivo);
    }
    else
    {
        printf("Algo no está bien, revisa la linea de comandos. Si necesitas ayuda ejecutá lo siguiente -> ./caza ayuda\n");
    }
    return 0;
}

// PRE:
// POST: Le explica al usuario como funciona el programa, detallando cada comando.
void ayuda_usuario()
{
    printf("Hola! A continuación te explico como usar este programa y como funcionan sus comandos. \n\n");
    printf("-LISTAR-\n Esta función te muestra todos los superhéroes, junto con su ID, nombre, edad y estado.\n Se ejecuta con la siguiente linea de comandos -> ./ejecutable listar archivo.csv\n\n");
    printf("-CONTACTAR-\n Con esta función podrás contactar al superhéroe que desees para que te ayude en una misión.\n Se ejecuta con la siguiente linea de comandos -> ./ejecutable contactar ID archivo.csv\n\n");
    printf("-MODIFICAR-\n Se actualiza la edad y el estado del superhéroe.\n Se ejecuta con la siguiente linea de comandos -> ./ejecutable modificar ID EDAD ESTADO archivo.csv\n\n");
    printf("-AGREGAR-\n Si el archivo.csv existe, el superhéroe deseado se agrega a la lista, en caso de que el archivo no exista, este es creado y el superhéroe es agregado.\n Se ejecuta con la siguiente linea de comandos -> ./ejecutable agregar ID NOMBRE EDAD ESTADO archivo.csv\n\n");
    printf("-ACLARACIONES GENERALES-\n El ID debe ser mayor a 0, el NOMBRE tiene un máximo de 50 caracteres, la EDAD debe ser mayor a 1, o menor o igual a 100, el ESTADO del superhéroe debe ser vivo o muerto.\n");
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printf("Algo no está bien, revisa la linea de comandos. Si necesitas ayuda ejecutá lo siguiente -> ./caza ayuda\n");
        return -1;
    }
    else if (strcmp(argv[1], "listar") == 0 && argc == ARGUMENTOS_LISTAR)
    {
        listar_superheroes(argv[ARGV_POSICION_DOS]);
    }
    else if (strcmp(argv[1], "contactar") == 0 && argc == ARGUMENTOS_CONTACTAR)
    {
        contactar_superheroes(argv[ARGV_POSICION_DOS], argv[ARGV_POSICION_TRES]);
    }
    else if (strcmp(argv[1], "modificar") == 0 && argc == ARGUMENTOS_MODIFICAR)
    {
        modificar_status(argv[ARGV_POSICION_DOS], argv[ARGV_POSICION_TRES], argv[ARGV_POSICION_CUATRO], argv[ARGV_POSICION_CINCO]);
    }
    else if (strcmp(argv[1], "agregar") == 0 && argc == ARGUMENTOS_AGREGAR)
    {
        agregar_superheroes(argv[ARGV_POSICION_DOS], argv[ARGV_POSICION_TRES], argv[ARGV_POSICION_CUATRO], argv[ARGV_POSICION_CINCO], argv[ARGV_POSICION_SEIS]);
    }
    else if (strcmp(argv[1], "ayuda") == 0)
    {
        ayuda_usuario();
    }
    else
    {
        printf("Algo no está bien, revisa la linea de comandos. Si necesitas ayuda ejecutá lo siguiente -> ./caza ayuda\n");
        return -1;
    }
    return 0;
}
