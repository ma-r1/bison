#ifndef COMANDOS_H
#define COMANDOS_H

void salir();
double clean_total();
double clean_variable(char * name);
double mostrar_ayuda();
double mostrar_ayuda_comando(char * comando);
double workspace();
double load(char * ruta);
double clear();
#endif /* COMANDOS_H */