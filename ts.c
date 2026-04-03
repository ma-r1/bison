#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ts.h"
#include "math.h"
#include "token.h"
#include "definiciones.h"
#include "abb.h"

static TS ts; //Almacena el abb

struct init {
  char *fname;
  double (*fnct)();
};

void inicializar_ts() {
  crearAbb(&ts);
  TOKEN *ptr;

  struct init arith_fncts[] = {
    "sin", sin,
    "cos", cos,
    "atan", atan,
    "ln", log,
    "exp", exp,
    "sqrt", sqrt,
    0, 0
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

int buscar_ts(char * name){
  TOKEN token;
  token.type = 0;
  buscarNodoAbb(ts, name, &token);
  if (token.type != 0) return token.type; //si se modificó el valor del componente léxico es que lo encontró en el abb, así que lo devolvemos
  return -1; //en caso contrario no se encontró en el abb
}

void insertar_ts(char * name, int type){
  TOKEN token;
  token.name = name;
  token.type = type;
  token.value.var = 0;
  insertarElementoAbb(&ts, token);
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

    printf("|  %d  |  %s  |  %f\n", token.type, token.name, token.value);

    _imprimir_recursivo(derAbb(a));
  }
}

void imprimir_ts(){
  _imprimir_recursivo(ts);
}