CC = gcc
COMPILER_FLAGS = -std=c99 -fstack-protector-all
LINKER_FLAGS = -lm 
EXEC_NAME = siguel
OBJECTS = main.o parametros.o arquivo_geo.o arquivos_saida.o arquivo_qry.o header.h

all: $(EXEC_NAME)

siguel: $(OBJECTS) 
		$(CC) $(OBJECTS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(EXEC_NAME)

clean:
		rm -rf *.o siguel 
