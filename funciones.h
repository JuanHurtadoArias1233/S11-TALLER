#ifndef FUNCIONES_H
#define FUNCIONES_H

#define MAX_LIBROS 10
#define MAX_TITULO 100
#define MAX_AUTOR 50
#define MAX_ESTADO 20

// Estructura para representar un libro
typedef struct {
    int id;
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int anio;
    char estado[MAX_ESTADO];
} Libro;

// Funciones de la biblioteca
void mostrarMenu();
void registrarLibro(Libro libros[], int *numLibros);
void mostrarLibros(Libro libros[], int numLibros);
void buscarLibro(Libro libros[], int numLibros);
void actualizarEstado(Libro libros[], int numLibros);
void eliminarLibro(Libro libros[], int *numLibros);
int validarID(Libro libros[], int numLibros, int id);
void limpiarBuffer();

#endif
