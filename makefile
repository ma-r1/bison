#opciones de compilacion, muestra todos los warnings (-Wall)
CC=gcc -Wall -I $(HEADER_FILES_DIR)

#carpeta de las cabeceras
HEADER_FILES_DIR = ./headerFiles
#opciones de compilacion, indica donde estan los archivos .h

#nombre del ejecutable o archivo de salida
OUTPUT = main

#archivo fuente de flex
FLEX_FILE = lex.l

#archivo fuente de bison
BISON_FILE = sin.y

#ficheros .h
HEADERS = $(HEADER_FILES_DIR)/token.h $(HEADER_FILES_DIR)/abb.h $(HEADER_FILES_DIR)/definiciones.h $(HEADER_FILES_DIR)/errores.h $(HEADER_FILES_DIR)/ts.h $(HEADER_FILES_DIR)/comandos.h $(HEADER_FILES_DIR)/colores.h $(HEADER_FILES_DIR)/sin.tab.h

#archivos .c necesarios
SRCS = abb.c errores.c main.c ts.c comandos.c lex.yy.c sin.tab.c

#todos los .o con un analogo .c en SRCS
OBJS = $(SRCS:.c=.o)

#REGLA 1: genera el ejecutable, dependencia de los .o 
$(OUTPUT): $(OBJS)
	$(CC) -o $(OUTPUT) $(OBJS) -lfl -lm

#REGLA 2: genera los .o cuando es necesario, dependencia de los .c y .h
#solo genera los .o necesarios por cambios en los .c o .h
%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< 

#REGLA 3: 
lex.yy.c: $(FLEX_FILE)
	flex $(FLEX_FILE)

#REGLA 4
sin.tab.c $(HEADER_FILES_DIR)/sin.tab.h: $(BISON_FILE)
	bison $(BISON_FILE) --defines=$(HEADER_FILES_DIR)/sin.tab.h  -o sin.tab.c

#REGLA 5: borra el ejecutable (prerrequisito: clean)
cleanall: clean
	rm -f $(OUTPUT) 

#REGLA 6: borra los ficheros .o y los de backup
clean:
	rm -f *.o *~
