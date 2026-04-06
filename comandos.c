#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colores.h"
#include "ts.h"

extern int yylex_destroy(void);

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
  if (!strcmp(comando, "clear")) printf(AMARILLO "Elimina todas las variables. Con un argumento elimina dicha variable si existe.\n" RESET);
  if (!strcmp(comando, "exit")) printf(AMARILLO "Sale del programa.\n" RESET);
  else printf(ROJO "No hay ayuda disponible para esa función.\n");
  return 0;
}