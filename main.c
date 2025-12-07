#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main() {
    Libro biblioteca[MAX_LIBROS];
    int numLibros = 0;
    int opcion;

    printf("========================================\n");
    printf("  BIENVENIDO AL SISTEMA DE BIBLIOTECA\n");
    printf("========================================\n");

    do {
        mostrarMenu();

        if (scanf("%d", &opcion) != 1) {
            printf("\n[ERROR] Opcion invalida. Intente nuevamente.\n");
            limpiarBuffer();
            continue;
        }
        limpiarBuffer();

        switch (opcion) {
            case 1:
                registrarLibro(biblioteca, &numLibros);
                break;
            case 2:
                mostrarLibros(biblioteca, numLibros);
                break;
            case 3:
                buscarLibro(biblioteca, numLibros);
                break;
            case 4:
                actualizarEstado(biblioteca, numLibros);
                break;
            case 5:
                eliminarLibro(biblioteca, &numLibros);
                break;
            case 6:
                printf("\n[INFO] Gracias por usar el sistema de biblioteca. Hasta pronto =)!\n");
                break;
            default:
                printf("\n[ERROR] Opcion invalida. Seleccione una opcion del 1 al 6.\n");
        }

    } while (opcion != 6);

    return 0;
}
