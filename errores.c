#include <stdio.h>
#include <stdlib.h>

#include "errores.h"
#include "token.h"
#include "ts.h"
#include "colores.h"

extern int yylineno;
extern int yylex_destroy(void);

void alex_error_comentario_multilinea() {
  fprintf(stderr, ROJO "Línea %d: comentario multilínea sin cerrar.\n" RESET, yylineno);
}

void alex_error_comentario_anidado() {
  fprintf(stderr, ROJO "Línea %d comentario anidado sin cerrar.\n" RESET, yylineno);
}

void alex_error_string_sin_cerrar() {
  fprintf(stderr, ROJO "Línea %d: string sin cerrar.\n" RESET, yylineno);
}

void alex_error_caracter(char c) {
  fprintf(stderr, ROJO "Línea %d: carácter no reconocido '%c'.\n" RESET, yylineno, c);
}

void error_archivo_no_abierto(char * ruta){
  fprintf(stderr, ROJO "Error: no se pudo abrir el archivo '%s'.\n" RESET, ruta);
  destruir_ts(); //Destruimos la tabla de símbolos que inicializó el main
  yylex_destroy();
  exit(1); //Es un error grave, cerramos
}

void error_archivo_no_cerrado(){
  fprintf(stderr, ROJO "Error: no se pudo cerrar el archivo.\n" RESET);
  destruir_ts();
  yylex_destroy();
  exit(1); //Es un error grave, cerramos
}

void yyerror(char * s) {
  printf(ROJO "ERROR sintáctico: %s\n" RESET, s);
}
