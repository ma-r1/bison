#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colores.h"
#include "ts.h"

//NOTA poner ; en los comandos no impide que impriman cosas, solo sirve para ocultar su resultado (es siempre 0)
extern int yylex_destroy(void);
extern void yyrestart(FILE *input_file);
extern FILE * yyin;

FILE * archivo_top = NULL;

void salir(){
  destruir_ts();
  yylex_destroy();
  printf(AMARILLO "FIN DE LA EJECUCIÓN\n" RESET);
  exit(0);
}

double clean_total(){
  vaciar_todas_variables();
  return 0;
}
//TODO poner que q una función devuelva 0 es q todo ok
double clean_variable(char * name){
  vaciar_variable(name);
  return 0;
}

double mostrar_ayuda(){
  printf(AMARILLO "Comandos disponibles:\n\
     help() -> ayuda.\n\
     help(&comando_argumentos) -> ayuda sobre el comando. Debes incluir el número de argumentos que tiene tras unas '_'. Por ejemplo clear_var\n\
     clear() -> elimina todas las variables.\n\
     clear(variable) -> elimina la variable.\n\
     exit() -> salir.\n\
  *****Los comandos devuelven 0 cuando finalizan correctamente*****\n\
  ");
  return 0;
}

double mostrar_ayuda_comando(char * comando){
  if (!strcmp(comando, "help")) printf(AMARILLO "Muestra ayuda sobre todos los comandos. Con un argumento muestra ayuda sobre un comando en específico.\n" RESET);
  else if (!strcmp(comando, "clear")) printf(AMARILLO "Elimina todas las variables. Con un argumento elimina dicha variable si existe.\n" RESET);
  else if (!strcmp(comando, "exit")) printf(AMARILLO "Sale del programa.\n" RESET);
  else printf(ROJO "No hay ayuda disponible para esa función.\n");
  return 0;
}

double workspace(){
  imprimir_ts(1);
  return 0;
}

double load(char * ruta){
  archivo_top = fopen(ruta, "r");
  if (archivo_top == NULL) {
    printf(ROJO "Error no se pudo abrir el archivo %s.\n", ruta);
    return -1;
  }
  return 0;
}