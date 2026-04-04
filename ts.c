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

struct init {
  char *fname;
  double (*fnct)();
};

void inicializar_ts() {
  crearAbb(&ts);

  struct init arith_fncts[] = {
    {"sin", sin},
    {"cos", cos},
    {"atan", atan},
    {"ln", log},
    {"exp", exp},
    {"sqrt", sqrt},
    {0, 0}
  };

  for (int i=0; arith_fncts[i].fname != 0; i++){
    TOKEN actual;
    actual.name = arith_fncts[i].fname;
    actual.type = FNCT;
    actual.value.fnctptr = arith_fncts[i].fnct;
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