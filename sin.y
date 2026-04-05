%{
#include <math.h>
#include <stdio.h>
#include <string.h>
#include "ts.h" 
#include "token.h"
#include "errores.h"
#include "colores.h"
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

input:  /*vacio*/
        | input line          {}
;
line:   
        '\n'
        | exp ';' '\n'        {}
        | exp '\n'            {printf(VERDE ">> %g\n" RESET, $1);}
        | error '\n'          {yyerrok;}
;
exp:    
        | NUM                 {$$ = $1;}
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
        | FNCT '(' exp ')'    {$$ = (*($1->value.fnctptr))($3);}
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
        | exp '^' exp         {$$ = pow ($1, $3);}
        | '(' exp ')'         {$$ = $2;}
%%

