#include <stdio.h>
#include <stdlib.h>

#include "errores.h"
#include "token.h"
#include "ts.h"

extern int yylineno;
extern int yylex_destroy(void);

void alex_error_comentario_multilinea() {
  fprintf(stderr, "Línea %d: comentario multilínea sin cerrar.\n", yylineno);
}

void alex_error_comentario_anidado() {
  fprintf(stderr, "Línea %d comentario anidado sin cerrar.\n", yylineno);
}

void alex_error_string_sin_cerrar() {
  fprintf(stderr, "Línea %d: string sin cerrar.\n", yylineno);
}

void alex_error_caracter(char c) {
  fprintf(stderr, "Línea %d: carácter no reconocido '%c'.\n", yylineno, c);
}

void error_archivo_no_abierto(char * ruta){
  fprintf(stderr, "Error: no se pudo abrir el archivo '%s'.\n", ruta);
  destruir_ts(); //Destruimos la tabla de símbolos que inicializó el main
  yylex_destroy();
  exit(1); //Es un error grave, cerramos
}

void error_archivo_no_cerrado(){
  fprintf(stderr, "Error: no se pudo cerrar el archivo.\n");
  destruir_ts();
  yylex_destroy();
  exit(1); //Es un error grave, cerramos
}
