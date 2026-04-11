/*
Fundamentalmente ha de contener dos funciones imprescindibles: 
1) una función de búsqueda que permita recorrer la tabla de símbolos para no 
replicar innecesariamente el mismo componente léxico; 
2) una función de inserción que permita almacenar un nuevo 
componente léxico encontrado.
*/

#ifndef TS_H
#define TS_H

#include "abb.h"
#include "token.h"

typedef TABB TS;

/*
  Inicializa el ABB e inserta las keywords.
*/

void inicializar_ts();

/*
  Busca un lexema concreto en la tabla de símbolos.
  Devuelve el componente léxico de dicho lexema si lo encuentra o -1 en caso contrario.
*/
TOKEN * buscar_ts(char * lexema);

/*
  Inserta un nuevo identificador en la tabla de símbolos con el lexema especificado.
*/
TOKEN * insertar_ts(char * name, int type);

/*
  Libera la memoria reservada para el abb.
*/
void destruir_ts();

/*
  Recorre y muestra por consola todo el contenido de la tabla de símbolos
*/
void imprimir_ts(int filtrar);

void actualizar_variable(char * name, float valor);

void vaciar_todas_variables();

void vaciar_variable(char * name);

#endif	// TS_H