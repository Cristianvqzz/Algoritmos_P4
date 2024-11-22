#Daniel Ortiz Sierra daniel.ortiz@udc.es
#Cristian Vázquez Seijas cristian.vazquez.seijas@udc.es
# Compilador
CC = gcc

# Opciones del compilador
CFLAGS = -Wall

# Librerías
LIBS = -lm

# Archivos fuente
SRCS = main.c tiempos.c monticulos.c

# Archivos objeto
OBJS = main.o tiempos.o monticulos.o

# Nombre del ejecutable
TARGET = algP4

# Regla por defecto: compilar el programa
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

# Regla para compilar main.o
main.o: main.c tiempos.h monticulos.h
	$(CC) $(CFLAGS) -c main.c

# Regla para compilar tiempo.o
tiempo.o: tiempos.c tiempos.h monticulos.h
	$(CC) $(CFLAGS) -c tiempos.c

monticulos.o: monticulos.c monticulos.h
	$(CC) $(CFLAGS) -c monticulos.c

# Regla para limpiar archivos generados
clean:
	rm -f $(OBJS) $(TARGET)
