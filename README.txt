- - - INFORMACIÓN
* Versión de GCC usada: 13.3.0
* Versión de Ubuntu usada: Ubuntu 24.04.4 LTS
* Versión de FLEX usada: flex 2.6.4
* Versión de BISON usada: bison (GNU Bison) 3.8.2

- - - INSTRUCCIONES DE COMPILACIÓN
Para la compilación del código fuente se usa el makefile. 
* Para crear el ejecutable se usa la regla predeterminada:
  $> make
* Para eliminar los ficheros .o se usa la regla clean:
  $> make clean
* Para eliminar los ficheros .o y el ejecutable se usa la regla cleanall:
  $> make cleanall

- - - INSTRUCCIONES DE EJECUCIÓN
El ejecutable creado con el make file se llama 'main'.
* Tiene un único argumento de ejecución, que es la ruta del archivo con el código fuente a analizar.
  $> ./main ./codigo_fuente.d
* Si no se especifica este argumento, se tomará como entrada aquella escrita por el teclado. 
En este caso, para enviar un comando a analizar se debe presionar ENTER.
  $>./main

-- SOBRE EL LENGUAJE IMPLEMENTADO 
* El lenguaje usa '\n' como delimitador final de una isntrucción.
* Se imprime el resultado de cada instrucción en verde. Esto se puede omitir añadiendo ';' al final de la instrucción.
* Las variables se crean automáticamente cuando se les asigna un valor por primera vez.
* Incluye las siguientes operaciones matemáticas básicas: suma, resta, multiplicación, división, potencia y negación.
* Incluye las siguientes funciones matemáticas: sin(x), cos(x), atan(x), ln(x), log(x), log10(x), exp(x), sqrt(x), pow(x, y).
* Incluye las siguientes constantes matemáticas: PI, E, LOG2E, LN2, SQRT2, SQRT1_2
* Incluye los siguientes comandos del sistema:
  - workspace() -> muestra una lista de todas las variables creadas y su valor actual.
  - clean() -> elimina todas las variables.
  - clean_var(&nombre_variable) -> elimina una variable específica.
  - load("ruta_archivo") -> pausa la ejecución actual, lee y ejecuta un script externo y luego vuelve a la ejecución original.
  - clear() -> limpia la terminal.
  - help() -> despliega el menú principal de ayuda.
  - help_fun(comando) -> muestra la documentación específica de una función concreta.
  - exit() -> libera toda l amemoria dinámica y cierra el program de forma segura.
