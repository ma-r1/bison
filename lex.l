%{
  #include <math.h>
  #include "definiciones.h"
  #include "ts.h"
  #include "errores.h"
  #include "sin.tab.h"
%}

DIGITO    [0-9]
VARIABLE   [a-z]

  /*OPCIONES DE FLEX*/
  /*yylineno hace que flex cuente automáticamente los saltos de línea*/
%option yylineno
  /*stack activa la pila de estados interna, que se usa para analizar los comentarios anidados*/
%option stack

%%


  /*Ignora espacios en blanco*/
[ \t]+                      {}

  /*Inserta IDs nuevos en la ts o devuelve el componente léxico del ID o keyword en la ts*/
{VARIABLE} {
  TOKEN * buscar = buscar_ts(yytext);
  if (buscar == NULL) {
    buscar = insertar_ts(yytext, VAR);
  }
  yylval.tptr=buscar;
  return buscar->type;
}

{DIGITO}+                   {yylval.val=atof(yytext); return NUM;}
{DIGITO}+"."{DIGITO}+       {yylval.val=atof(yytext); return NUM;}
"."{DIGITO}+                {yylval.val=atof(yytext); return NUM;}

[;()[\]{},\-*<>\\=+/\.'\n'] {return yytext[0];}

"exit"                      {return EOF;}
.                           {alex_error_caracter(yytext[0]);}

%%
