#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mapas.h"

void menu(){

  printf("\n============ MENÚ ========== \n");
  printf("\n1. Registrar punto de interés\n");
  printf("2. Mostrar datos de punto de interés\n");
  printf("3. Eliminar punto de interés\n");
  printf("4. Registrar turista\n");
  printf("5. Agregar lugar favorito a turista\n");
  printf("6. Mostrar turistas por país\n");
  printf("7. Mostrar todos los puntos de interés de un tipo\n");
  printf("8. Importar puntos de interés y turistas desde archivos CSV\n");
  printf("9. Exportar puntos de interés y turistas a archivos CSV\n");
  printf("0. Salir\n");
  printf("\nSeleccione una opción: ");
}

int main() {
    int opcion;

    do {
      menu();
      if (scanf("%d", &opcion) != 1) {
            printf("\nOpción no válida. Por favor, ingrese un número válido.\n");
            while (getchar() != '\n'); // Limpiar el búfer de entrada
            continue; // Ignorar la opción no válida y volver a mostrar el menú
        }
      getchar();
        switch (opcion) {
           case 0:
              
                printf("has salido del menu");
                break;
          
            case 1:
                registrarPuntoInteres();
                break;
            case 2:
                mostrarPuntoInteres();
                break;
            case 3:
                eliminarPuntoInteres();
                break;
            case 4:
                registrarTurista();
                break;
            case 5:
                agregarLugarFavorito();
                break;
            case 6:
                mostrarTuristasPorPais();
                break;
            case 7:
                mostrarPuntosInteresPorTipo();
                break;
            case 8: {
                char nombre_archivo_puntos[100], nombre_archivo_turistas[100];
                
                printf("\nIngrese el nombre del archivo de puntos de interés: ");
                fgets(nombre_archivo_puntos, 100, stdin);
                
                printf("\nIngrese el nombre del archivo de turistas: ");
                fgets(nombre_archivo_turistas, 100, stdin);
                
                importarDesdeCSV(nombre_archivo_puntos, nombre_archivo_turistas);
                
                break;
            }
            case 9: {
                char nombre_archivo_puntos[100], nombre_archivo_turistas[100];
                
                printf("Ingrese el nombre del archivo de puntos de interés: ");
                fgets(nombre_archivo_puntos, 100, stdin);
                
                printf("Ingrese el nombre del archivo de turistas: ");
                fgets(nombre_archivo_turistas, 100, stdin);
                
                exportarACSV(nombre_archivo_puntos, nombre_archivo_turistas);
                
                break;
            }

          default :
            printf("\nOpción no válida. Por favor, elija una opción válida.\n");
        }
    } while (opcion != 10);

    return 0;
}