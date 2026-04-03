%{
  #include <math.h>
  #include "definiciones.h"
  #include "ts.h"
  #include "errores.h"
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
[ \t\n]+                {}

  /*Inserta IDs nuevos en la ts o devuelve el componente léxico del ID o keyword en la ts*/
{VARIABLE} {
  int buscar = buscar_ts(yytext);
  if (buscar == -1) {
    insertar_ts(yytext);
    return ID;
  }
  return buscar;
}


{DIGITO}+               {return DECIMAL;}
{DIGITO}+"."{DIGITO}+   {return DECIMAL;}
"."{DIGITO}+            {return DECIMAL;}

[;()[\]{},\-*<>\\=+/\.] {return yytext[0];}

.                       {alex_error_caracter(yytext[0]);}

%%
