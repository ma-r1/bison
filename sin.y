%code requires{
  #include "token.h"
}

%{
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "ts.h" 
#include "token.h"
#include "errores.h"
#include "colores.h"

extern FILE * archivo_top;
extern void abrir_archivo(FILE * archivo);
%}

%union{
  double val;
  TOKEN *tptr;
  char *lexema;
}

%token <val> NUM
%token <tptr> VAR CONST
%token <tptr> FNCT_0 FNCT_1 FNCT_2 FNCT_VAR FNCT_FNCT FNCT_STR
%token <lexema> CADENA ID_NO_DEF

%type <val> exp
%type <tptr> funcion

%right '='
%left '-' '+'
%left '*' '/'
%left NEG
%right '^'
 
%destructor { free($$); } <lexema>

%%



input:    /*vacio*/
          | input line          {}
;
line:   
          '\n'
          | exp ';' '\n'        {if (archivo_top != NULL){
                                  abrir_archivo(archivo_top);
                                  archivo_top = NULL;
                                }}
          | exp '\n'            {if(!isnan($1)) printf(VERDE ">> %g\n" RESET, $1);
                                if (archivo_top != NULL){
                                  abrir_archivo(archivo_top);
                                  archivo_top = NULL;
                                }}
          | error '\n'          {yyerrok;}
;
exp:      NUM                   {$$ = $1;}
          | VAR                 {$$ = $1->value.var;}
          | CONST               {$$ = $1->value.var;}
          | ID_NO_DEF           {printf(ROJO "Error, variable '%s' no declarada.\n" RESET, $1);
                                free($1);
                                $$=NAN; /*detenemos el análisis de la línea*/
                                }
          | VAR '=' exp         {$$ = $3; 
                                $1->value.var=$3;
                                actualizar_variable($1->name, $3);}
          | CONST '=' exp       { printf(ROJO "Error semántico: no se puede modificar el valor de una constante\n" RESET);
                                $$=NAN;
                                }
          | ID_NO_DEF '=' exp   {$$ = $3; 
                                TOKEN * nuevo = insertar_ts($1, VAR);
                                nuevo->value.var=$3;
                                free($1);}
          | FNCT_0 '(' ')'      {$$=(*($1->value.fnctptr))();}
          | FNCT_1 '(' exp ')'  {$$=(*($1->value.fnctptr))($3);}
          | FNCT_2 '(' exp ',' exp ')'  {$$=(*($1->value.fnctptr))($3, $5);}
          | FNCT_VAR '(' VAR ')'    {$$=(*($1->value.fnctptr))($3->name);}
          | FNCT_FNCT '(' funcion ')'   {$$=(*($1->value.fnctptr))($3->name);}
          | FNCT_FNCT '(' ID_NO_DEF ')'   {
                                          printf(ROJO "Error: La función '%s' no existe en el sistema.\n" RESET, $3);
                                          free($3);
                                          $$=NAN;
                                        }
          | FNCT_VAR '(' ID_NO_DEF ')'  {
                                          printf(ROJO "Error: La variable '%s' no existe en el sistema.\n" RESET, $3);
                                          free($3);
                                          $$=NAN;
                                        }
          | FNCT_STR '(' CADENA ')'     {
                                          $$ = ((double (*)(char*))($1->value.fnctptr))($3);
                                          free($3);
                                        }
          | FNCT_STR '(' exp ')'        {
                                          printf(ROJO "Error, la función %s requiere una ruta de archivo entre comillas.\n" RESET, $1->name);
                                          $$=NAN;
                                        }
          | exp '+' exp         {$$ = $1 + $3;}
          | exp '-' exp         {$$ = $1 - $3;}
          | exp '*' exp         {$$ = $1 * $3;}
          | exp '/' exp         { if ($3 == 0.0) {
                                    printf(ROJO "Error semántico: División por cero.\n" RESET);
                                    $$=NAN;
                                  } else {
                                      $$ = $1 / $3; 
                                  }
                                }
          | '-' exp %prec NEG   {$$ = -$2;}
          | '(' exp ')'         {$$ = $2;}

funcion:
          FNCT_0                {$$=$1;}
          | FNCT_1              {$$=$1;}
          | FNCT_2              {$$=$1;}
          | FNCT_VAR            {$$=$1;}
          | FNCT_FNCT           {$$=$1;}
          | FNCT_STR            {$$=$1;}

%%

