%{
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "ts.h" 
#include "token.h"
#include "errores.h"
#include "colores.h"

extern int yylex(void);
extern void yyerror(const char *s);
%}

%union{
  double val;
  TOKEN *tptr;
  char *lexema;
}

%token <val> NUM
%token <tptr> VAR FNCT CONST
%token <lexema> ID_NO_DEF
%type <val> exp

%right '='
%left '-' '+'
%left '*' '/'
%left NEG
%right '^'

%%

input:    /*vacio*/
          | input line          {}
;
line:   
          '\n'
          | exp ';' '\n'        {}
          | exp '\n'            {printf(VERDE ">> %g\n" RESET, $1);}
          | error '\n'          {yyerrok;}
;
exp:      NUM                   {$$ = $1;}
          | VAR                 {$$ = $1->value.var;}
          | CONST               {$$ = $1->value.var;}
          | ID_NO_DEF           {
                                printf(ROJO "Error, variable '%s' no declarada.\n" RESET, $1);
                                free($1);
                                YYERROR; /*detenemos el análisis de la línea*/
                                }
          | VAR '=' exp         {$$ = $3; 
                                $1->value.var=$3;
                                actualizar_variable($1->name, $3);}
          | ID_NO_DEF '=' exp   {$$ = $3; 
                                TOKEN * nuevo = insertar_ts($1, VAR);
                                nuevo->value.var=$3;
                                free($1);}
          | ID_NO_DEF '(' ')'   { char nombre_completo[256];
                                sprintf(nombre_completo, "%s_void", $1);
                                TOKEN *fun = buscar_ts(nombre_completo);
                                if (fun == NULL){
                                  printf(ROJO "Error: la función '%s()' no existe o requiere argumentos.\n" RESET, $1);
                                  YYERROR;
                                } else $$ = (*(fun->value.fnctptr))();
                                free($1);}
          | ID_NO_DEF '(' exp ')'   { char nombre_completo[256];
                                sprintf(nombre_completo, "%s_num", $1);
                                TOKEN *fun = buscar_ts(nombre_completo);
                                if (fun == NULL){
                                  printf(ROJO "Error: la función '%s(double)' no existe o los argumentos no son correctos.\n" RESET, $1);
                                  YYERROR;
                                } else $$ = (*(fun->value.fnctptr))($3);
                                free($1);}
          | ID_NO_DEF '(' exp ',' exp ')'   { char nombre_completo[256];
                                sprintf(nombre_completo, "%s_num_num", $1);
                                TOKEN *fun = buscar_ts(nombre_completo);
                                if (fun == NULL){
                                  printf(ROJO "Error: la función '%s(double, double)' no existe o los argumentos no son correctos.\n" RESET, $1);
                                  YYERROR;
                                } else $$ = (*(fun->value.fnctptr))($3, $5);
                                free($1);}
          | ID_NO_DEF '(' '&' VAR ')'   { char nombre_completo[256];
                                sprintf(nombre_completo, "%s_var", $1);
                                TOKEN *fun = buscar_ts(nombre_completo);
                                if (fun == NULL){
                                  printf(ROJO "Error: la función '%s(variable)' no existe o los argumentos no son correctos.\n" RESET, $1);
                                  YYERROR;
                                } else $$ = (*(fun->value.fnctptr))($4->name);
                                free($1);}
          | exp '+' exp         {$$ = $1 + $3;}
          | exp '-' exp         {$$ = $1 - $3;}
          | exp '*' exp         {$$ = $1 * $3;}
          | exp '/' exp         { if ($3 == 0.0) {
                                    printf(ROJO "Error matemático: División por cero.\n" RESET);
                                    YYERROR; /* BOTÓN DEL PÁNICO: Abortamos el cálculo */
                                  } else {
                                      $$ = $1 / $3; 
                                  }
                                }
          | '-' exp %prec NEG   {$$ = -$2;}
          | '(' exp ')'         {$$ = $2;}

%%

 