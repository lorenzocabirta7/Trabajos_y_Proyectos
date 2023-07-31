import random
from random import randint
import os
import copy

CANTIDAD_DE_FILAS = 20
CANTIDAD_DE_COLUMNAS = 20

#PRE: 
#POST: Verifica que el parametro recibido este en la lista.
def letra_invalida(letra: str) -> bool:
    return letra not in ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"]

#PRE: 
#POST: Verifica que el parametro recibido este en la lista.
def numero_invalido(numero: int) -> bool:
    return numero not in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]

#PRE: Se recibe una lista de tuplas (compuesta por palabra y definición)
#POST: Devuelve una lista de 12 palabras elegidas aleatoriamente.
def eleccion_de_palabras(palabras_elegidas: list) -> list:
    palabras_elegidas = list(random.sample(palabras_elegidas, 12))
    return palabras_elegidas

#PRE: Se recibe una lista de 12 tuplas (compuesta por palabra y definicion) y un diccionario previamente cargado.
#POST: Imprime por pantalla las 12 definiciones.
def imprimir_definiciones(palabras_elegidas: list, diccionario_hasta_l: dict) -> None:
    for i in range(12):
        print(f"{i+1} ({diccionario_hasta_l[i]})- {palabras_elegidas[i][1]}")

#PRE: Se recibe una matriz ya creada y una lista de 12 tuplas (compuesta por palabra y definicion)
#POST: Carga en la matriz la letra de referencia de cada palabra en una posicion random y con espacios en blanco rellena el resto de los espacios según la cantidad de letras de cada palabra.
def cargar_letras_de_referencia_y_espacios_en_matriz(palabras_elegidas: list, tablero: list, lista_de_coordenadas: list, diccionario_hasta_l: dict)-> None:
    #Cargo verticales
    lista_de_columnas = []
    lista_de_filas = []
    #Se cargan las palabras verticales.
    for i in range(6):
        coordenadas_de_verticales = []
        fila_vertical_random = randint(0, 5)
        columna_vertical_random = randint(0, 19)
        while(columna_vertical_random in lista_de_columnas):
            columna_vertical_random = randint(0, 19)
        lista_de_columnas.append(columna_vertical_random)
        coordenadas_de_verticales.append(fila_vertical_random)
        coordenadas_de_verticales.append(columna_vertical_random)
        lista_de_coordenadas.append(coordenadas_de_verticales)
        tablero[fila_vertical_random][columna_vertical_random] = diccionario_hasta_l[i]
        fila_vertical_random += 1
        for x in range(1, len(palabras_elegidas[i][0])):
            tablero[fila_vertical_random][columna_vertical_random] = " "
            fila_vertical_random += 1
    #Se cargan las palabras horizontales.
    for j in range(6, len(palabras_elegidas)):
        coordenadas_de_horizontales = []
        fila_horizontal_random = randint(10, 19)
        columna_horizontal_random = randint(0, 14)
        while(fila_horizontal_random in lista_de_filas):
            fila_horizontal_random = randint(11, 19)
        lista_de_filas.append(fila_horizontal_random)
        coordenadas_de_horizontales.append(fila_horizontal_random)
        coordenadas_de_horizontales.append(columna_horizontal_random)
        lista_de_coordenadas.append(coordenadas_de_horizontales)
        tablero[fila_horizontal_random][columna_horizontal_random] = diccionario_hasta_l[j]
        columna_horizontal_random += 1
        for y in range(1, len(palabras_elegidas[j][0])):
            tablero[fila_horizontal_random][columna_horizontal_random] = " "
            columna_horizontal_random += 1

#PRE: Las listas recibidas deben estar previamente cargadas.
#POST: Actualiza la matriz según las palabras sean adivinadas o no.
def actualizar_tablero(palabras_elegidas: list, tablero: list, palabras_adivinadas: list, lista_de_coordenadas: list, indice_de_palabra: int) ->None:
    lista_de_coordenadas_auxiliar = copy.deepcopy(lista_de_coordenadas)
    for j in range(len(palabras_elegidas[indice_de_palabra][0])):
        tablero[lista_de_coordenadas_auxiliar[indice_de_palabra][0]][lista_de_coordenadas_auxiliar[indice_de_palabra][1]] = palabras_elegidas[indice_de_palabra][0][j]
        #Si es palabra vertical se aumenta la fila.
        if(indice_de_palabra <= 5):
            lista_de_coordenadas_auxiliar[indice_de_palabra][0] += 1
        #Si es palabra horizontal se aumenta la columna.
        elif(indice_de_palabra >= 6):
            lista_de_coordenadas_auxiliar[indice_de_palabra][1] += 1

#PRE: La lista recibida debe estar previamente cargada.
#POST: Devuelve la cantidad de elementos en True.
def cantidad_de_palabras_adivinadas(palabras_adivinadas: list) -> int:
    numero_de_palabras_adivinadas = 0
    for i in palabras_adivinadas:
        if(i == True):
            numero_de_palabras_adivinadas += 1
    return numero_de_palabras_adivinadas

#PRE: Todas las listas que se reciben, incluido el tablero, deben estar previamente cargados.
#POST: En el caso de que al menos una palabra haya sido adivinada, se la elimina de la lista de palabras elegidas y del tablero, y se la reemplaza en dichas ubicaciones por una nueva.
def dado_uno_o_dos(palabras_elegidas: list, palabras_adivinadas: list, palabras_y_definiciones: list, tablero: list, lista_de_coordenadas: list, diccionario_hasta_l: dict) ->None:
    hay_palabras_adivinadas = cantidad_de_palabras_adivinadas(palabras_adivinadas)
    if(hay_palabras_adivinadas > 0):
        indice_a_modificar = palabras_adivinadas.index(True)
        palabra_eliminada = str(palabras_elegidas[indice_a_modificar][0])
        palabras_elegidas.pop(indice_a_modificar)
        palabras_adivinadas[indice_a_modificar] = False
        indice_palabra_nueva = randint(0, 50)
        palabra_nueva = palabras_y_definiciones[indice_palabra_nueva]
        while(palabra_nueva in palabras_elegidas or len(palabra_nueva[0]) != len(palabra_eliminada)):
            indice_palabra_nueva = randint(0, 50)
            palabra_nueva = palabras_y_definiciones[indice_palabra_nueva]
        palabras_elegidas.insert(indice_a_modificar, palabra_nueva)
        fila_a_reemplazar = int(lista_de_coordenadas[indice_a_modificar][0])
        columna_a_reemplazar = int(lista_de_coordenadas[indice_a_modificar][1])
        #Actualizar si la palabra es vertical.
        if(indice_a_modificar < 6):
            tablero[fila_a_reemplazar][columna_a_reemplazar] = diccionario_hasta_l[indice_a_modificar]
            fila_a_reemplazar += 1
            for x in range(1, len(palabra_nueva[0])):
                tablero[fila_a_reemplazar][columna_a_reemplazar] = " "
                fila_a_reemplazar += 1
        #Actualizar si la palabra es horizontal.
        elif(indice_a_modificar >= 6):
            tablero[fila_a_reemplazar][columna_a_reemplazar] = diccionario_hasta_l[indice_a_modificar]
            columna_a_reemplazar += 1
            for y in range(1, len(palabra_nueva[0])):
                tablero[fila_a_reemplazar][columna_a_reemplazar] = " "
                columna_a_reemplazar += 1

#PRE: Las listas recibidas deben estar cargadas previamente.
#POST: Revela todas las vocales de las 12 palabras en el tablero.
def dado_tres_o_cuatro(tablero: list, palabras_elegidas: list, vocales: list, lista_de_coordenadas: list, palabras_adivinadas: list) ->None:
    for i in range(len(palabras_elegidas)):
        for j in range(len(palabras_elegidas[i][0])):
            if(i < 6):
                if(palabras_elegidas[i][0][j] in vocales):
                    tablero[lista_de_coordenadas[i][0]+j][lista_de_coordenadas[i][1]] = palabras_elegidas[i][0][j]
            elif(i >= 6):
                if(palabras_elegidas[i][0][j] in vocales):
                    tablero[lista_de_coordenadas[i][0]][lista_de_coordenadas[i][1]+j] = palabras_elegidas[i][0][j]

#PRE: Las listas recibidas deben estar cargadas previamente.
#POST: Da por adivinada una palabra elegida según el indice que haya elegido el usuario. Si esta previamente habia sido descubierta, la función no tiene efecto.
def dado_cinco(palabras_adivinadas: list, palabras_elegidas: list, tablero: list, lista_de_coordenadas: list) ->None:
    print("¡Estas de suerte! Te toco el dado N°5, el cuál te permite elegir una palabra de las que te faltan para que se revele automáticamente.\n")
    print("Seleccioná un número de la lista de definiciones para que su palabra correspondiente se descubra. Debe ser una palabra que no se haya descubierto.\n")
    indice_elegido = input("INDÍCE ELEGIDO: ")
    while(not indice_elegido.isnumeric()):
        indice_elegido = input("Solo se pueden ingresar números del 1 al 12, intenta nuevamente: ")
    indice_elegido = int(indice_elegido) - 1
    while(numero_invalido(indice_elegido) or palabras_adivinadas[indice_elegido] == True):
        print("El índice elegido ya fue descubierto o ingresaste un formato erroneo, ingrese un número entre 1 y 12. ")
        indice_elegido = int(input("INDÍCE ELEGIDO: ")) - 1
    palabras_adivinadas[indice_elegido] = True
    print(f"¡Felicidades! Revelaste la palabra: '{palabras_elegidas[indice_elegido][0]}'\n")
    actualizar_tablero(palabras_elegidas, tablero, palabras_adivinadas, lista_de_coordenadas, indice_elegido)

#PRE:
#POST: Devuelve True.
def dado_seis() -> bool:
    return True

#PRE: Se reciben todas las listas previamente cargadas y un número previamente asignado.
#POST: Dependiendo del número, se llama a la función correspondiente.
def tirar_dados(palabras_elegidas: list, palabras_adivinadas: list, tablero: list, lista_de_coordenadas: list, vocales: list, diccionario_hasta_l: list, palabras_y_definiciones: list, resultado_dado: int) -> None:
    if(resultado_dado == 1 or resultado_dado == 2):
        print(f"Mala suerte, te tocó el dado {resultado_dado} y si habías descubierto una palabra, fue cambiada por una nueva :( ")
        dado_uno_o_dos(palabras_elegidas, palabras_adivinadas, palabras_y_definiciones, tablero, lista_de_coordenadas, diccionario_hasta_l)
    elif(resultado_dado == 3 or resultado_dado == 4):
        print(f"Estas de suerte, te tocó el dado {resultado_dado} y se revelan todas las vocales en el tablero")
        dado_tres_o_cuatro(tablero, palabras_elegidas, vocales, lista_de_coordenadas, palabras_adivinadas)
    elif(resultado_dado == 5):
        dado_cinco(palabras_adivinadas, palabras_elegidas, tablero, lista_de_coordenadas)

#PRE: Todas las listas recibidas deben estar cargadas previamente.
#POST: Valida la respuesta del usuario. Si es correcta, cambia el indice correspondiente a True en la lista de palabras adivinadas, si es incorrecta, se llama a la función que tira el dado.
def verificar_respuesta_usuario(palabras_elegidas: list, palabras_adivinadas: list, diccionario_hasta_l: dict, tablero: list, lista_de_coordenadas: list, vocales: list, palabras_y_definiciones: list, dado_de_la_muerte: bool) -> bool:
    letra_de_referencia = input("Ingrese la letra de referencia elegida (a-l): ").lower()
    while(letra_invalida(letra_de_referencia)):
        letra_de_referencia = input("Inválido, ingrese una letra de referencia de las que se muestren en el tablero (a-l): ").lower()
    numero_de_definicion = input("Ingrese el número de la definición elegida (1 a 12), teniendo en cuenta que debe coincidir en índice con la letra de referencia: ")
    while(not numero_de_definicion.isnumeric()):
        numero_de_definicion = input("Error, solamente pueden ingresarse números del 1 al 12: ")
    numero_de_definicion = int(numero_de_definicion) - 1
    while(numero_invalido(numero_de_definicion) or diccionario_hasta_l[numero_de_definicion] != letra_de_referencia):
        numero_de_definicion = int(input("Error, ingresaste un número incorrecto o este no coincide con la letra de referencia, ingrese nuevamente el número de la definición elegida (1 a 12): ")) - 1
    palabra_respuesta = input("Escriba la palabra completa que coincide con la definicion: ").lower()
    while(palabra_respuesta.isalpha() == False):
        palabra_respuesta = input("Formato inválido, escriba la palabra completa que coincide con la definicion: ").lower()
    if(palabras_elegidas[numero_de_definicion][0] == palabra_respuesta):
        palabras_adivinadas[numero_de_definicion] = True
        print(f"¡Felicidades! Revelaste la palabra: '{palabras_elegidas[numero_de_definicion][0]}'\n")
        actualizar_tablero(palabras_elegidas, tablero, palabras_adivinadas, lista_de_coordenadas, numero_de_definicion)
    else:
        resultado_dado = randint(1, 6)
        if(resultado_dado == 6):
            dado_de_la_muerte = dado_seis()
            print("☠️  Dado de la muerte, perdes el juego ☠️")
            return dado_de_la_muerte
        else:
            tirar_dados(palabras_elegidas, palabras_adivinadas, tablero, lista_de_coordenadas, vocales, diccionario_hasta_l, palabras_y_definiciones, resultado_dado)

#PRE: Debe recibirse un tablero previamente cargado.
#POST: Imprime el tablero por pantalla con sus valores correspondientes.
def imprimir_tablero(tablero: list) -> None:
    for i in range(len(tablero)):
        for j in range(len(tablero[i])):
            print(tablero[i][j], end = " ")
        print()

#PRE:
#POST: Da la bienvenida al usuario y explica brevemente las reglas y el desarollo del juego.
def bienvenida_y_aclaraciones() ->None:
    print("-BIENVENIDO AL CRUCIGRAMA- \n")
    print("A continuación se explican algunas reglas y aclaraciones del juego: ")
    print("🟢El juego consiste en descubrir 12 (6 horizontales y 6 verticales) palabras que son elegidas al azar, cada vez que se ejecuta desde el inicio el programa.")
    print("🟢Cada palabra esta referenciada con una letra (desde la A a la L) en el comienzo de la misma.")
    print("🟢Debajo del tablero se muestran marcadas del 1 al 12 las definiciones correspondientes a cada palabra, las cuales coinciden en orden con las letras de referencia del tablero. Es decir la definición 1 corresponde a la letra A, la 2 a la B, la 3 a la C y asi sucesivamente.")
    print("🟢Para anotar sus respuestas el juego le solicitará -> letra de referencia -> número de definición -> palabra completa que encajaría con la definición.")
    print("🟢Si su respuesta es correcta, la palabra se mostrará en el tablero y usted seguirá jugando, en cambio si erra, se tirará un dado, el cual tiene 4 posibles resultados. ")
    print("🟠Si el resultado de la tirada es 1 o 2, usted pierde una de las palabras que acertó previamente y se agrega al listado de palabras a adivinar una nueva palabra al azar.")
    print("🟠Si el resultado de la tirada es 3 o 4, se mostraran en el tablero todas las vocales de las palabras faltantes. ")
    print("🟠Si el resultado de la tirada es 5, usted puede elegir a gusto el número de una definición para que la palabra correspondiente sea revelada automáticamente.")
    print("🟠Si el resultado de la tirada es 6, usted pierde el juego y debe empezarlo nuevamente. ")
    print("🔵El juego termina cuando las 12 palabras han sido descubiertas o cuando el resultado de la tirada del dado es 6. ")
    print("🔵Esperamos que disfrute del juego de crucigrama. \n")   

def main() -> None:
    palabras_y_definiciones = [("mesa", "Mueble para comer o trabajar."), ("gato", "Animal doméstico que ronronea."), ("perro", "Animal doméstico que ladra."),
            ("cama", "Mueble para dormir."), ("taza", "Recipiente para beber."), ("pato", "Animal acuático que hace cuac."), 
            ("pez", "Animal acuático que nada."), ("techo", "Parte superior de una construcción."), ("llave", "Objeto para abrir cerraduras."),
            ("raton", "Animal pequeño que come queso."), ("rojo", "Color como el de la sangre."), ("silla", "Mueble para sentarse."),
            ("huevo", "Alimento de forma ovalada."), ("arbol","Planta de gran tamaño."), ("oro", "Elemento químico de símbolo Au y número atómico 79."),
            ("lago", "Gran masa de agua rodeada de tierra."), ("vino", "Bebida alcohólica obtenida por la fermentación del zumo de uva."),
            ("sol", "Estrella que se encuentra en el centro del sistema planetario y que es el origen de la luz y el calor que llegan a la Tierra."),
            ("rio", "Corriente natural de agua que fluye por un cauce y desemboca en el mar, en un lago o en otro río."),
            ("mar", "Gran extensión de agua salada que cubre la mayor parte de la superficie terrestre."), ("luna", "Satélite natural de la Tierra, que gira alrededor de ella y refleja la luz del Sol."),
            ("bici", "Vehículo de dos ruedas que se impulsa con los pies sobre los pedales."), ("nido", "Estructura que construyen algunos animales para poner sus huevos o criar a sus crías."),
            ("aire", "Mezcla gaseosa que constituye la atmósfera terrestre y que los seres vivos respiran."),
            ("cielo", "Espacio que se encuentra sobre la Tierra y en el que se ven las estrellas, el Sol y la Luna."),
            ("oveja", "Animal mamífero rumiante, de cuerpo cubierto de lana y con patas cortas."), ("puma", "Mamífero carnívoro de cuerpo esbelto y musculoso, cabeza pequeña y pelaje corto y suave."),
            ("bote", "Embarcación pequeña que se impulsa con remos."), ("flor", "Órgano reproductor de las plantas, que se caracteriza por sus colores vistosos y su fragancia"),
            ("pila", "Dispositivo que transforma la energía química en energía eléctrica."), ("lapiz", "Instrumento de escritura con una mina de grafito."),
            ("niño", " Ser humano en la etapa de la infancia."), ("risa", "Acto de reírse en voz alta y con alegría."), 
            ("tren", "Medio de transporte compuesto de vagones que se enganchan entre sí."), ("goma", "Material elástico utilizado para borrar o para fabricar objetos."),
            ("vela", "Objeto alargado y flexible utilizado para dar luz."), ("lupa", "Instrumento óptico utilizado para ampliar la imagen de los objetos."),
            ("uva", "Fruto de la vid utilizado para hacer vino o para comer."), ("cafe", "Bebida caliente hecha a partir de granos molidos y agua caliente."),
            ("oso", "Un animal grande y peludo con garras afiladas."), ("rueda", "Un objeto circular que gira alrededor de un eje y se utiliza para transportar objetos."),
            ("miel", "Un líquido dulce y viscoso producido por las abejas a partir del néctar de las flores."),
            ("auto", "Vehículo de transporte motorizado con capacidad para transportar personas o carga."), 
            ("tiza", "Objeto cilíndrico hecho de yeso o carbonato de calcio, que se utiliza para escribir o dibujar en pizarras."),
            ("jugo", "Líquido obtenido al exprimir o triturar frutas."), ("mono", "Un animal con cuerpo cubierto de pelo y cola prensil que se encuentra principalmente en los árboles."),
            ("abeja", "Un insecto polinizador que produce miel."), ("agua", "Una sustancia incolora, inodora e insípida esencial para la vida."),
            ("lobo", "Un animal carnívoro que vive en manadas y se asemeja a un perro salvaje."), ("arroz", "Se trata de un cereal considerado alimento básico en muchas gastronomías del mundo.")]
    tablero = [["▇" for i in range(CANTIDAD_DE_FILAS)] for j in range(CANTIDAD_DE_COLUMNAS)]
    diccionario_hasta_l = {0 : "a", 1 : "b", 2 : "c", 3 : "d", 4 : "e", 5 : "f", 6 : "g", 7 : "h", 8 : "i", 9 : "j", 10 : "k", 11 : "l"}
    palabras_elegidas = eleccion_de_palabras(palabras_y_definiciones)
    palabras_adivinadas = [False for i in range(12)]
    vocales = ["a", "e", "i", "o", "u"]
    lista_de_coordenadas = []
    dado_de_la_muerte = False
    contador_palabras_adivinadas = cantidad_de_palabras_adivinadas(palabras_adivinadas)
    bienvenida_y_aclaraciones()
    cargar_letras_de_referencia_y_espacios_en_matriz(palabras_elegidas, tablero, lista_de_coordenadas, diccionario_hasta_l)
    inicio = input("Presione enter para comenzar a jugar.")
    while(not dado_de_la_muerte and contador_palabras_adivinadas < 12):
        os.system("cls")
        print("➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖")
        print("➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖")
        imprimir_tablero(tablero)
        print("➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖")
        imprimir_definiciones(palabras_elegidas, diccionario_hasta_l)
        print("➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖➖")
        dado_de_la_muerte = verificar_respuesta_usuario(palabras_elegidas, palabras_adivinadas, diccionario_hasta_l, tablero, lista_de_coordenadas, vocales, palabras_y_definiciones, dado_de_la_muerte)
        contador_palabras_adivinadas = cantidad_de_palabras_adivinadas(palabras_adivinadas)
        continuar = input("Para continuar presione enter.")
        os.system("cls")
    if(contador_palabras_adivinadas == 12):
        imprimir_tablero(tablero)
        print("🎉🎉🎉 ¡Felicidades! Completaste el juego 🎉🎉🎉")

main()



