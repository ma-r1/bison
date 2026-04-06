%{
  #include <math.h>
  #include <string.h>
  #include "definiciones.h"
  #include "colores.h"
  #include "ts.h"
  #include "errores.h"
  #include "sin.tab.h"

  char linea_actual[1024] = "";

  #define YY_USER_ACTION strcat(linea_actual, yytext);
%}

DIGITO    [0-9]
LETRA     [a-zA-Z]

  /*OPCIONES DE FLEX*/
  /*yylineno hace que flex cuente automáticamente los saltos de línea*/
%option yylineno
  /*stack activa la pila de estados interna, que se usa para analizar los comentarios anidados*/
%option stack

%%


  /*Ignora espacios en blanco*/
[ \t]+                      {}
\n {
  printf(AZUL "> %s" RESET, linea_actual);
  linea_actual[0] = '\0';
  return '\n';
}

  /*Inserta IDs nuevos en la ts o devuelve el componente léxico del ID o keyword en la ts*/
{LETRA}+ {
  TOKEN * buscar = buscar_ts(yytext);
  if (buscar != NULL){
    yylval.tptr = buscar;
    return buscar->type;
  } else{
    yylval.lexema = strdup(yytext);
    return ID_NO_DEF;
  }
}

{DIGITO}+                   {yylval.val=atof(yytext); return NUM;}
{DIGITO}+"."{DIGITO}+       {yylval.val=atof(yytext); return NUM;}
"."{DIGITO}+                {yylval.val=atof(yytext); return NUM;}

[;()[\]{},\-*<>\\=+/\.&]   {return yytext[0];}

<<EOF>> {
  if (linea_actual[0] != '\0') printf("> %s\n", linea_actual);
  return 0;
}
.                           {alex_error_caracter(yytext[0]);}

%%
