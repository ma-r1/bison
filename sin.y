%{
#include <math.h>
#include <stdio.h>
#include "ts.h" 
#include "token.h"
#include "errores.h"
#include "colores.h"
%}

%union{
  double val;
  TOKEN *tptr;
}

%token <val> NUM
%token <tptr> VAR FNCT
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
exp:    NUM                   {$$ = $1;}
        | VAR                 {$$ = $1->value.var;}
        | VAR '=' exp         {$$ = $3; 
                              $1->value.var=$3;
                              actualizar_variable($1->name, $3);}
        | FNCT '(' exp ')'    {$$ = (*($1->value.fnctptr))($3);}
        | exp '+' exp         {$$ = $1 + $3;}
        | exp '-' exp         {$$ = $1 - $3;}
        | exp '*' exp         {$$ = $1 * $3;}
        | exp '/' exp         {$$ = $1 / $3;}
        | '-' exp %prec NEG   {$$ = -$2;}
        | exp '^' exp         {$$ = pow ($1, $3);}
        | '(' exp ')'         {$$ = $2;}
%%

