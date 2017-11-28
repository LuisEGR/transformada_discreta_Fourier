PROJECT=tdf # Este nombre se le dará al ejecutable
LIBS_SOURCES := $(wildcard libs/*.c) # Busco todos los archivos .c en lib/
LIBS_OBJECTS := $(LIBS_SOURCES:.c=.o) # Reemplazo las extensiones .c a .o

all: $(PROJECT)

$(PROJECT): clibs
	gcc -Wall -c main.c -o main.o -w -lm
	gcc -Wall main.o $(LIBS_OBJECTS) -o $(PROJECT) -lm
	gcc -Wall -c tonos.c -o tonos.o -w -lm
	gcc -Wall tonos.o $(LIBS_OBJECTS) -o tonos -lm

clibs: $(LIBS_OBJECTS)
	cd libs; make

clean:
	rm -f *.o $(PROJECT)
	cd libs; make clean