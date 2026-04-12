#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "colores.h"
#include "ts.h"

//NOTA poner ; en los comandos no impide que impriman cosas, solo sirve para ocultar su resultado (es siempre 0)
extern int yylex_destroy(void);
extern void yyrestart(FILE *input_file);
extern void limpiar_pila(void);
extern FILE * yyin;

FILE * archivo_top = NULL;

void salir(){
  destruir_ts();
  if (archivo_top!=NULL) fclose(archivo_top);
  limpiar_pila();
  yylex_destroy();
  printf(AMARILLO "FIN DE LA EJECUCIÓN\n" RESET);
  exit(0);
}

double clean_total(){
  vaciar_todas_variables();
  return 0;
}
//TODO poner que q una función devuelva 0 es q todo ok
double clean_variable(char * name){
  vaciar_variable(name);
  return 0;
}

double mostrar_ayuda() {
  printf(MAGENTA "========== MENÚ DE AYUDA ==========\n");
  printf("* El lenguaje usa el salto de línea como delimitador final de una isntrucción.\n" \
"* Se imprime el resultado de cada instrucción en verde. Esto se puede omitir añadiendo ';' al final de la instrucción.\n" \
"* Cuando la entrada no es la estándar se imprime el comando de entrada en azul.\n" \
"* Las variables se crean automáticamente cuando se les asigna un valor por primera vez.\n" \
"* Incluye las siguientes operaciones matemáticas básicas: suma, resta, multiplicación, división, potencia y negación.\n" \
"* Incluye las siguientes funciones matemáticas: sin(x), cos(x), atan(x), ln(x), log(x), log10(x), exp(x), sqrt(x), pow(x, y).\n" \
"* Incluye las siguientes constantes matemáticas: PI, E, LOG2E, LN2, SQRT2, SQRT1_2\n" \
"* Incluye los siguientes comandos del sistema:\n" \
  "- workspace() -> muestra una lista de todas las variables creadas y su valor actual.\n" \
  "- clean() -> elimina todas las variables.\n" \
  "- clean_var(&nombre_variable) -> elimina una variable específica.\n" \
  "- load(\"ruta_archivo\") -> pausa la ejecución actual, lee y ejecuta un script externo y luego vuelve a la ejecución original.\n" \
  "- clear() -> limpia la terminal.\n" \
  "- help() -> despliega el menú principal de ayuda.\n" \
  "- help_fun(comando) -> muestra la documentación específica de una función concreta.\n" \
  "- exit() -> libera toda l amemoria dinámica y cierra el program de forma segura.\n" \
  RESET);
  return 0;
}

double mostrar_ayuda_comando(char * comando) {
  printf(MAGENTA ">> Ayuda para '%s': " RESET, comando);
  
  if (!strcmp(comando, "help")) {
      printf(MAGENTA "Muestra el menú de ayuda general con todos los comandos y sintaxis.\n" RESET);
  } 
  else if (!strcmp(comando, "help_fun")) {
      printf(MAGENTA "Muestra ayuda detallada sobre un comando específico. Uso: help_fun(nombre_funcion)\n" RESET);
  } 
  else if (!strcmp(comando, "clean")) {
      printf(MAGENTA "Vacía por completo la Tabla de Símbolos, eliminando todas las variables guardadas.\n" RESET);
  } 
  else if (!strcmp(comando, "clean_var")) {
      printf(MAGENTA "Elimina una variable concreta de la memoria. Requiere paso por referencia usando '&'. Ejemplo: clean_var(&x)\n" RESET);
  } 
  else if (!strcmp(comando, "workspace")) {
      printf(MAGENTA "Imprime una lista con todas las variables que has declarado en la sesión actual y sus valores.\n" RESET);
  } 
  else if (!strcmp(comando, "load")) {
      printf(MAGENTA "Lee y ejecuta un archivo externo línea por línea. Requiere que la ruta vaya entre comillas. Ejemplo: load(\"script.txt\")\n" RESET);
  } 
  else if (!strcmp(comando, "clear")) {
      printf(MAGENTA "Limpia la pantalla de la consola (equivalente al comando 'clear' de Linux/Mac).\n" RESET);
  } 
  else if (!strcmp(comando, "exit")) {
      printf(MAGENTA "Termina la ejecución del programa de forma segura, liberando la memoria.\n" RESET);
  } 
  
  else if (!strcmp(comando, "sin") || !strcmp(comando, "cos") || !strcmp(comando, "atan")) {
      printf(MAGENTA "Función trigonométrica. Toma un único argumento numérico (en radianes).\n" RESET);
  }
  else if (!strcmp(comando, "ln") || !strcmp(comando, "log") || !strcmp(comando, "log10")) {
      printf(MAGENTA "Función logarítmica. Toma un único argumento numérico mayor que 0.\n" RESET);
  }
  else if (!strcmp(comando, "exp")) {
      printf(MAGENTA"Calcula la exponencial (e^x) del número proporcionado.\n" RESET);
  }
  else if (!strcmp(comando, "sqrt")) {
      printf(MAGENTA"Calcula la raíz cuadrada de un número positivo.\n" RESET);
  }
  else if (!strcmp(comando, "pow")) {
      printf(MAGENTA"Eleva un número a una potencia. Requiere dos argumentos numéricos. Ejemplo: pow(2, 3) devuelve 8.\n" RESET);
  }
  else {
      printf(ROJO "No hay ayuda disponible.\n" RESET);
  }
  return 0;
}

double workspace(){
  imprimir_ts(1);
  return 0;
}

double load(char * ruta){
  archivo_top = fopen(ruta, "r");
  if (archivo_top == NULL) {
    printf(ROJO "Error no se pudo abrir el archivo %s.\n", ruta);
    return -1;
  }
  return 0;
}

double clear(){
  system("clear");
  return 0;
}