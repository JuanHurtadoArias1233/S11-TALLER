#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "funciones.h"

// Función para limpiar el buffer de entrada
void limpiarBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Función para mostrar el menú principal
void mostrarMenu() {
    printf("\n========================================\n");
    printf("   SISTEMA DE GESTION DE BIBLIOTECA\n");
    printf("========================================\n");
    printf("1. Registrar libro\n");
    printf("2. Mostrar todos los libros\n");
    printf("3. Buscar libro\n");
    printf("4. Actualizar estado de libro\n");
    printf("5. Eliminar libro\n");
    printf("6. Salir\n");
    printf("========================================\n");
    printf("Seleccione una opcion: ");
}

// Función para validar que el ID sea único
int validarID(Libro libros[], int numLibros, int id) {
    for (int i = 0; i < numLibros; i++) {
        if (libros[i].id == id) {
            return 0; // ID ya existe
        }
    }
    return 1; // ID es único
}

// Función para registrar un nuevo libro
void registrarLibro(Libro libros[], int *numLibros) {
    if (*numLibros >= MAX_LIBROS) {
        printf("\n[ERROR] No se pueden agregar mas libros. Limite alcanzado (10 libros).\n");
        return;
    }

    Libro nuevoLibro;
    int idTemp;

    printf("\n--- REGISTRAR NUEVO LIBRO ---\n");

    // Validar ID único
    do {
        printf("Ingrese ID del libro (numero entero): ");
        if (scanf("%d", &idTemp) != 1) {
            printf("[ERROR] Entrada invalida. Debe ingresar un numero.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();

        if (idTemp <= 0) {
            printf("[ERROR] El ID debe ser un numero positivo.\n");
            continue;
        }

        if (!validarID(libros, *numLibros, idTemp)) {
            printf("[ERROR] El ID %d ya existe. Ingrese un ID unico.\n", idTemp);
        } else {
            nuevoLibro.id = idTemp;
            break;
        }
    } while (1);

    // Ingresar título
    printf("Ingrese titulo del libro (max 100 caracteres): ");
    fgets(nuevoLibro.titulo, MAX_TITULO, stdin);
    nuevoLibro.titulo[strcspn(nuevoLibro.titulo, "\n")] = 0; // Eliminar salto de línea

    if (strlen(nuevoLibro.titulo) == 0) {
        printf("[ERROR] El titulo no puede estar vacio.\n");
        return;
    }

    // Ingresar autor
    printf("Ingrese autor del libro (max 50 caracteres): ");
    fgets(nuevoLibro.autor, MAX_AUTOR, stdin);
    nuevoLibro.autor[strcspn(nuevoLibro.autor, "\n")] = 0;

    if (strlen(nuevoLibro.autor) == 0) {
        printf("[ERROR] El autor no puede estar vacio.\n");
        return;
    }

    // Ingresar año de publicación
    do {
        printf("Ingrese anio de publicacion (1000-2025): ");
        if (scanf("%d", &nuevoLibro.anio) != 1) {
            printf("[ERROR] Entrada invalida. Debe ingresar un numero.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();

        if (nuevoLibro.anio < 1000 || nuevoLibro.anio > 2025) {
            printf("[ERROR] Anio invalido. Debe estar entre 1000 y 2025.\n");
        } else {
            break;
        }
    } while (1);

    // Estado por defecto
    strcpy(nuevoLibro.estado, "Disponible");

    // Agregar el libro al arreglo
    libros[*numLibros] = nuevoLibro;
    (*numLibros)++;

    printf("\n[EXITO] Libro registrado correctamente.\n");
}

// Función para mostrar todos los libros en formato tabla
void mostrarLibros(Libro libros[], int numLibros) {
    if (numLibros == 0) {
        printf("\n[INFO] No hay libros registrados en la biblioteca.\n");
        return;
    }

    printf("\n========================================================================================================\n");
    printf("                                    LISTA DE LIBROS\n");
    printf("========================================================================================================\n");
    printf("%-5s %-35s %-25s %-10s %-15s\n", "ID", "TITULO", "AUTOR", "AÑO", "ESTADO");
    printf("--------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < numLibros; i++) {
        printf("%-5d %-35s %-25s %-10d %-15s\n",
               libros[i].id,
               libros[i].titulo,
               libros[i].autor,
               libros[i].anio,
               libros[i].estado);
    }

    printf("========================================================================================================\n");
    printf("Total de libros: %d/%d\n", numLibros, MAX_LIBROS);
}

// Función para buscar un libro por ID o título
void buscarLibro(Libro libros[], int numLibros) {
    if (numLibros == 0) {
        printf("\n[INFO] No hay libros registrados en la biblioteca.\n");
        return;
    }

    int opcion;
    printf("\n--- BUSCAR LIBRO ---\n");
    printf("1. Buscar por ID\n");
    printf("2. Buscar por titulo\n");
    printf("Seleccione una opcion: ");

    if (scanf("%d", &opcion) != 1) {
        printf("[ERROR] Opcion invalida.\n");
        limpiarBuffer();
        return;
    }
    limpiarBuffer();

    int encontrado = 0;

    if (opcion == 1) {
        int idBuscar;
        printf("Ingrese el ID del libro: ");
        if (scanf("%d", &idBuscar) != 1) {
            printf("[ERROR] ID invalido.\n");
            limpiarBuffer();
            return;
        }
        limpiarBuffer();

        for (int i = 0; i < numLibros; i++) {
            if (libros[i].id == idBuscar) {
                printf("\n--- LIBRO ENCONTRADO ---\n");
                printf("ID: %d\n", libros[i].id);
                printf("Titulo: %s\n", libros[i].titulo);
                printf("Autor: %s\n", libros[i].autor);
                printf("Anio: %d\n", libros[i].anio);
                printf("Estado: %s\n", libros[i].estado);
                encontrado = 1;
                break;
            }
        }
    } else if (opcion == 2) {
        char tituloBuscar[MAX_TITULO];
        printf("Ingrese el titulo del libro: ");
        fgets(tituloBuscar, MAX_TITULO, stdin);
        tituloBuscar[strcspn(tituloBuscar, "\n")] = 0;

        for (int i = 0; i < numLibros; i++) {
            if (strstr(libros[i].titulo, tituloBuscar) != NULL) {
                printf("\n--- LIBRO ENCONTRADO ---\n");
                printf("ID: %d\n", libros[i].id);
                printf("Titulo: %s\n", libros[i].titulo);
                printf("Autor: %s\n", libros[i].autor);
                printf("Anio: %d\n", libros[i].anio);
                printf("Estado: %s\n", libros[i].estado);
                encontrado = 1;
            }
        }
    } else {
        printf("[ERROR] Opcion invalida.\n");
        return;
    }

    if (!encontrado) {
        printf("\n[INFO] No se encontro el libro.\n");
    }
}

// Función para actualizar el estado de un libro
void actualizarEstado(Libro libros[], int numLibros) {
    if (numLibros == 0) {
        printf("\n[INFO] No hay libros registrados en la biblioteca.\n");
        return;
    }

    int idBuscar;
    printf("\n--- ACTUALIZAR ESTADO DE LIBRO ---\n");
    printf("Ingrese el ID del libro: ");

    if (scanf("%d", &idBuscar) != 1) {
        printf("[ERROR] ID invalido.\n");
        limpiarBuffer();
        return;
    }
    limpiarBuffer();

    int encontrado = 0;
    for (int i = 0; i < numLibros; i++) {
        if (libros[i].id == idBuscar) {
            encontrado = 1;
            printf("\nLibro: %s\n", libros[i].titulo);
            printf("Estado actual: %s\n", libros[i].estado);

            if (strcmp(libros[i].estado, "Disponible") == 0) {
                strcpy(libros[i].estado, "Prestado");
                printf("[EXITO] Estado actualizado a: Prestado\n");
            } else {
                strcpy(libros[i].estado, "Disponible");
                printf("[EXITO] Estado actualizado a: Disponible\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("\n[INFO] No se encontro el libro con ID %d.\n", idBuscar);
    }
}

// Función para eliminar un libro
void eliminarLibro(Libro libros[], int *numLibros) {
    if (*numLibros == 0) {
        printf("\n[INFO] No hay libros registrados en la biblioteca.\n");
        return;
    }

    int idBuscar;
    printf("\n--- ELIMINAR LIBRO ---\n");
    printf("Ingrese el ID del libro a eliminar: ");

    if (scanf("%d", &idBuscar) != 1) {
        printf("[ERROR] ID invalido.\n");
        limpiarBuffer();
        return;
    }
    limpiarBuffer();

    int encontrado = 0;
    for (int i = 0; i < *numLibros; i++) {
        if (libros[i].id == idBuscar) {
            encontrado = 1;
            printf("\nLibro a eliminar: %s\n", libros[i].titulo);

            // Confirmar eliminación
            char confirmacion;
            printf("Esta seguro de eliminar este libro? (S/N): ");
            scanf("%c", &confirmacion);
            limpiarBuffer();

            if (toupper(confirmacion) == 'S') {
                // Desplazar todos los libros siguientes una posición hacia atrás
                for (int j = i; j < *numLibros - 1; j++) {
                    libros[j] = libros[j + 1];
                }
                (*numLibros)--;
                printf("[EXITO] Libro eliminado correctamente.\n");
            } else {
                printf("[INFO] Operacion cancelada.\n");
            }
            break;
        }
    }

    if (!encontrado) {
        printf("\n[INFO] No se encontro el libro con ID %d.\n", idBuscar);
    }
}
