#include <stdio.h>
#include <stdlib.h>

#include "errores.h"
#include "colores.h"
#include "ts.h"

extern FILE * yyin;
extern int yylex_destroy(void);
extern int yyparse(void);

int main(int argc, char * argv[]) {
  inicializar_ts();
  imprimir_ts(0);

  if (argc < 2) {
    yyin = stdin;
  } else if ((yyin = fopen(argv[1], "r")) == NULL) error_archivo_no_abierto(argv[1]);

  printf(AMARILLO "Escriba 'help()' para recibir ayuda.\n" RESET);
  yyparse();

  imprimir_ts(0);
  if(fclose(yyin)!=0){
    error_archivo_no_cerrado();
  }
  yylex_destroy();
  destruir_ts();
  return 0;
}


