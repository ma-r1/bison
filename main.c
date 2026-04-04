#include <stdio.h>
#include <stdlib.h>

#include "errores.h"
#include "ts.h"

extern FILE * yyin;
extern int yylex_destroy(void);
extern int yyparse(void);

int main(int argc, char * argv[]) {
  inicializar_ts();
  imprimir_ts();

  yyin = stdin;

  yyparse();

  imprimir_ts();
  if(fclose(yyin)!=0){
    error_archivo_no_cerrado();
  }
  yylex_destroy();
  destruir_ts();
  return 0;
}


