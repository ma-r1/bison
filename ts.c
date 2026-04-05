#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ts.h"
#include "math.h"
#include "token.h"
#include "definiciones.h"
#include "abb.h"
#include "sin.tab.h"

static TS ts; //Almacena el abb

struct init_fun{
  char * name;
  int type;
  double (*fncptr)();
};

void inicializar_ts() {
  crearAbb(&ts);

  struct init_fun arith_fncts[] = {
    {"sin", FNCT, &sin},
    {"cos", FNCT, &cos},
    {"atan", FNCT, &atan},
    {"ln", FNCT, &log},
    {"exp", FNCT, &exp},
    {"sqrt", FNCT, &sqrt},
    {"log", FNCT, &log},
    {"log10", FNCT, &log10},
    {0, 0, 0}
  };

  for (int i=0; arith_fncts[i].name != 0; i++){
    TOKEN actual;
    actual.name=arith_fncts[i].name;
    actual.type=arith_fncts[i].type;
    actual.value.fnctptr=arith_fncts[i].fncptr;
    insertarElementoAbb(&ts, actual);
  }
  return;
}

TOKEN * buscar_ts(char * name){
  TOKEN * token = buscarNodoAbb(ts, name);
  if (token != NULL){ 
    printf("TS | Encontrado %s\n", token->name);
    return token;
  } 
  return NULL;
}

TOKEN * insertar_ts(char * name, int type){
  TOKEN token;
  token.name = name;
  token.type = type;
  token.value.var = 0;
  insertarElementoAbb(&ts, token);
  printf("TS | Insertado %s %d\n", token.name, token.type);
  return (buscar_ts(name));
}

void actualizar_variable(char * name, float valor){
  TOKEN * token = buscarNodoAbb(ts, name);
  token->value.var = valor;
  modificarElementoAbb(ts, *token);
}

void destruir_ts(){
  destruirAbb(&ts);
}

/*
  Función privada.
  Permite imprimir el abb sin tener que poner la TS como argumento de la función pública (así la variable de la ts puede ser privada a este archivo)
*/
void _imprimir_recursivo(TS a){
  if(!esAbbVacio(a)){
    TOKEN token;

    _imprimir_recursivo(izqAbb(a));

    leerElementoAbb(a, &token);

    if(token.type==VAR) printf("|  %d  |  %s  |  %f\n", token.type, token.name, token.value.var);
    if(token.type==FNCT) printf("|  %d  |  %s\n", token.type, token.name);

    _imprimir_recursivo(derAbb(a));
  }
}

void imprimir_ts(){
  _imprimir_recursivo(ts);
}