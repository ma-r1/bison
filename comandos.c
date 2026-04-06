#include <stdlib.h>
#include <stdio.h>
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