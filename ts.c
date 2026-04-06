#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ts.h"
#include "math.h"
#include "token.h"
#include "definiciones.h"
#include "abb.h"
#include "sin.tab.h"
#include "comandos.h"

static TS ts; //Almacena el abb

struct init_fun{
  char * name;
  int type;
  double (*fncptr)();
};

struct init_cnst{
  char * name;
  int type;
  double var;
};

void inicializar_ts() {
  crearAbb(&ts);

  struct init_fun funciones_iniciales[] = {
    {"sin_num", FNCT, &sin},
    {"cos_num", FNCT, &cos},
    {"atan_num", FNCT, &atan},
    {"ln_num", FNCT, &log},
    {"exp_num", FNCT, &exp},
    {"sqrt_num", FNCT, &sqrt},
    {"log_num", FNCT, &log},
    {"pow_num_num", FNCT, &pow},
    {"log10_num", FNCT, &log10},
    {"exit", FNCT, (double (*)()) &salir},
    {"clear", FNCT, (double (*)()) &clean_total},
    {"clear_var", FNCT, (double (*)()) &clean_variable},
    {"help", FNCT, (double (*)()) &mostrar_ayuda},
    {"help_fnct", FNCT, (double (*)()) &mostrar_ayuda_comando},
    {0, 0, 0}
  };

  struct init_cnst constantes[] = {
    {"PI", CONST, M_PI},
    {"E", CONST, M_E},
    {"LOG2E", CONST, M_LOG2E},
    {"LN2", CONST, M_LN2},
    {"SQRT2", CONST, M_SQRT2},
    {"SQRT1_2", CONST, M_SQRT1_2},
    {0, 0, 0}
  };


  for (int i=0; funciones_iniciales[i].name != 0; i++){
    TOKEN actual;
    actual.name=funciones_iniciales[i].name;
    actual.type=funciones_iniciales[i].type;
    actual.value.fnctptr=funciones_iniciales[i].fncptr;
    insertarElementoAbb(&ts, actual);
  }

  for (int i=0; constantes[i].name != 0; i++){
    TOKEN actual;
    actual.name=constantes[i].name;
    actual.type=constantes[i].type;
    actual.value.var=constantes[i].var;
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
  printf("TS | No encontré %s.\n", name);
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

    if(token.type==VAR || token.type==CONST) printf("|  %d  |  %s  |  %f\n", token.type, token.name, token.value.var);
    if(token.type==FNCT) printf("|  %d  |  %s\n", token.type, token.name);

    _imprimir_recursivo(derAbb(a));
  }
}

void imprimir_ts(){
  _imprimir_recursivo(ts);
}

int _borrar_variable_recursivo(TS a, char * name){
  if (!esAbbVacio(a)){
    TOKEN token;
    leerElementoAbb(a, &token);
    if(token.type==VAR && (strcmp(name, token.name) == 0 || strcmp(name, "")==0)){
      suprimirElementoAbb(&ts, token);
      return 1;
    }
    if (_borrar_variable_recursivo(izqAbb(a), name) == 1) return 1;
    if (_borrar_variable_recursivo(derAbb(a), name) == 1) return 1;
    return 0;
  } 
  return 0;
}

void vaciar_todas_variables(){
  while (_borrar_variable_recursivo(ts, "")==1);
}

void vaciar_variable(char * name){
  _borrar_variable_recursivo(ts, name);
}

