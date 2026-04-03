#ifndef ERRORES_H
#define ERRORES_H

#include "token.h"

/*
  Las siguientes funciones imprimen un error por pantalla indicando la línea del código fuente donde occure.
*/

void alex_error_comentario_multilinea();
void alex_error_comentario_anidado();
void alex_error_string_sin_cerrar();
void alex_error_caracter(char c); //c es el caracter no reconocido que provoca el error


/*
  Estos errores son fatales y finalizan la ejecución del programa (tras liberar la memoria reservada hasta el momento).
*/
void error_archivo_no_abierto(char * ruta); //Toma como argumento la ruta del archivo que no se consiguió abrir
void error_archivo_no_cerrado();

#endif /* ERRORES_H */