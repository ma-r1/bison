#include <stdio.h>
#include <stdlib.h>

extern char  * yytext;
extern int yylex();

void imprimir_componentes_lexicos() {
  //se van pidiendo tokens hasta encontrar el EOF
  while (1) {
    int comp = yylex();
    if (comp == 0) break;
    printf("<%d, %s>\n", comp, yytext);
  }
}
