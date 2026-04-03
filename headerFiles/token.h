#ifndef TOKEN_H
#define TOKEN_H

/*
  Estructura para los tokens que intercambian el analizador lexico y el sintáctico.
*/
typedef struct {
    char * name;
    int type;
    union {
      double var;
      double (*fnctptr)();
    } value;
} TOKEN;

#endif /* TOKEN_H */