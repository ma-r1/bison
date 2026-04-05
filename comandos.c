#include <stdlib.h>
#include <stdio.h>
#include "colores.h"

void salir(){
  destruir_ts();
  yylex_destroy();
  printf(AMARILLO "FIN DE LA EJECUCIÓN\n" RESET);
  exit(0);
}