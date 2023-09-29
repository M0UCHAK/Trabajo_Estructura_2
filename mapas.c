#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mapas.h"

Nodo *listaTuristas = NULL;

// cuando ingresamos el punto de interés utilizamos "a" que nos ayuda a que si ingresamos un dato que ya esté dentro lo ponga a el final 
void registrarPuntoInteres() {
    PuntoInteres punto;
    FILE *file = fopen("puntos_interes.csv", "a");

// Se ingresan los datos a través del teclado, con su respectivo mensaje
    printf("\nIngrese el nombre del punto de interés: ");
    fgets(punto.nombre, sizeof(punto.nombre), stdin);
    punto.nombre[strcspn(punto.nombre, "\n")] = '\0';
    
    printf("Ingrese el tipo del punto de interés: ");
    fgets(punto.tipo, sizeof(punto.tipo), stdin);
    punto.tipo[strcspn(punto.tipo, "\n")] = '\0'; 
    
    printf("Ingrese la dirección del punto de interés: ");
    fgets(punto.direccion, sizeof(punto.direccion), stdin);
    punto.direccion[strcspn(punto.direccion, "\n")] = '\0';
    
    printf("Ingrese el horario del punto de interés: ");
    fgets(punto.horario, sizeof(punto.horario), stdin);
    punto.horario[strcspn(punto.horario, "\n")] = '\0';
    
    printf("Ingrese la descripción del punto de interés: ");
    fgets(punto.descripcion, sizeof(punto.descripcion), stdin);
    punto.descripcion[strcspn(punto.descripcion, "\n")] = '\0'; 
  
    // Escribe los datos del punto de interés en el archivo CSV.
    fprintf(file, "%s,%s,%s,%s,%s\n", punto.nombre, punto.tipo, punto.direccion, punto.horario, punto.descripcion);
    printf("\nSe registró exitosamente el punto de interés\n");
    fclose(file);
}

void mostrarPuntoInteres() {
  char nombre[100];
    
  printf("\nIngrese el nombre del punto de interés: ");
  fgets(nombre, sizeof(nombre), stdin);
    
  size_t len = strlen(nombre);
  if (len > 0 && nombre[len - 1] == '\n') nombre[len - 1] = '\0';  
  
  // utilizamos "r" ya que ingresamos en modo lectura.
  
  FILE *file = fopen("puntos_interes.csv", "r");
  if (file == NULL) {
    printf("Error al abrir el archivo de puntos de interés.\n");
    return;
  }
    
  PuntoInteres punto;
  int encontrado = 0;

  // Se inicia un bucle para leer cada línea del archivo CSV hasta el final del archivo (EOF).
  
  while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", punto.nombre, punto.tipo, punto.direccion, punto.horario, punto.descripcion) != EOF) {
    if (strcmp(nombre, punto.nombre) == 0) {
      printf("\nNombre: %s\nTipo: %s\nDirección: %s\nHorario: %s\nDescripción: %s\n", 
                   punto.nombre, punto.tipo, punto.direccion, punto.horario, punto.descripcion);
      encontrado = 1;
      break;
    }
  }
  fclose(file);
  if (!encontrado) printf("No se encontró el punto de interés con el nombre '%s'.\n", nombre);
}


void eliminarPuntoInteres() {
    char nombre[100];
    PuntoInteres punto; // recordar que "punto" ya está declarado como variable de tipo interes
    int encontrado = 0;

    FILE *file = fopen("puntos_interes.csv", "r");
    FILE *temp = fopen("temp.csv", "w");

    printf("\nIngrese el nombre del punto de interés: ");
    fgets(nombre, 100, stdin);
    nombre[strcspn(nombre, "\n")] = 0;

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", punto.nombre, punto.tipo, punto.direccion, punto.horario, punto.descripcion) != EOF) {
        if (strcmp(nombre, punto.nombre) != 0) {

          // Si el nombre no coincide con el punto de interés a eliminar, se escribe en el archivo temporal
            fprintf(temp, "%s,%s,%s,%s,%s\n", punto.nombre, punto.tipo, punto.direccion, punto.horario, punto.descripcion);
        } else encontrado = 1;
    }

    fclose(file);
    fclose(temp);

    if (encontrado) {
        remove("puntos_interes.csv"); // Si se encontró y eliminó un punto de interés, se elimina el archivo original
        rename("temp.csv", "puntos_interes.csv");  // Se renombra el archivo temporal como el archivo original
        printf("\nEl punto de interés '%s' ha sido eliminado.\n", nombre);
    } else {
        remove("temp.csv");
        printf("\nEl punto de interés '%s' no se encontró.\n", nombre);
    }
}

void registrarTurista() {
    char pasaporte[100], nombreLugar[100];
    Turista turista;
    FILE *file = fopen("turistas.csv", "a");

    printf("\nIngrese el pasaporte del turista: ");
    fgets(turista.pasaporte, 100, stdin);
    printf("Ingrese el nombre del turista: ");
    fgets(turista.nombre, 100, stdin);
    printf("Ingrese el país del turista: ");
    fgets(turista.pais, 100, stdin);

    turista.pasaporte[strcspn(turista.pasaporte, "\n")] = '\0';
    turista.nombre[strcspn(turista.nombre, "\n")] = '\0';
    turista.pais[strcspn(turista.pais, "\n")] = '\0';

    // Escribe la información del turista en el archivo CSV.
    fprintf(file, "%s,%s,%s\n", turista.pasaporte, turista.nombre, turista.pais);

   // Crea un nuevo nodo para la lista enlazada que contiene la información del turista.
    Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
    nuevoNodo->turista = turista;
    nuevoNodo->siguiente = listaTuristas;
    listaTuristas = nuevoNodo; // Actualiza el puntero de listaTuristas al nuevo nodo.

    fclose(file);
}

void agregarLugarFavorito() {
    char pasaporte[100], nombreLugar[100],buffer[1000];
    
    printf("\nIngrese el pasaporte del turista: ");
    fgets(pasaporte, sizeof(pasaporte), stdin);
    pasaporte[strcspn(pasaporte, "\n")] = '\0'; 
    
    printf("Ingrese el nombre del lugar favorito: ");
    fgets(nombreLugar, sizeof(nombreLugar), stdin);
    nombreLugar[strcspn(nombreLugar, "\n")] = '\0';
  
    FILE *file = fopen("turistas.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    
    int encontrado = 0;
    
    while (fgets(buffer, sizeof(buffer), file)) {
        char bufferPasaporte[100], bufferNombre[100], bufferPais[100], bufferLugaresFavoritos[700];

      // Analiza la línea del archivo en sus componentes
        sscanf(buffer, "%[^,],%[^,],%[^,],%[^\n]\n", bufferPasaporte, bufferNombre, bufferPais, bufferLugaresFavoritos);

       // Si el pasaporte coincide con el ingresado, agregar el lugar favorito
        if (strcmp(bufferPasaporte, pasaporte) == 0) {
            strcat(bufferLugaresFavoritos, ";");
            strcat(bufferLugaresFavoritos, nombreLugar);
            fprintf(temp, "%s,%s,%s,%s\n", bufferPasaporte, bufferNombre, bufferPais, bufferLugaresFavoritos);
            encontrado = 1;
        } else fprintf(temp, "%s", buffer);  // Si no coincide, escribir la línea original en el archivo temporal
    }
    fclose(file);
    fclose(temp);
    
    if (encontrado) { // Si se encontró al turista, reemplazar el archivo original con el archivo temporal
        remove("turistas.csv");
        rename("temp.csv", "turistas.csv");
        printf("Lugar favorito agregado al turista.\n");
    } else {
        printf("No se encontró el turista.\n");  // Si no se encontró al turista, eliminar el archivo temporal
        remove("temp.csv");
    }
}

void mostrarTuristasPorPais() {
    char pais[100];
    char buffer[1000];
    char *registro[5], *ptr;
    
    printf("\nIngrese el país: ");
    fgets(pais, 100, stdin);
    pais[strcspn(pais, "\n")] = 0;
    
    FILE *file = fopen("turistas.csv", "r");
    
    while (fgets(buffer, 1024, file)) {
        if (strlen(buffer) > 1) { // Verificar que la línea no esté vacía
            int i = 0;
            ptr = strtok(buffer,",");

          // Parsear la línea en registros utilizando comas como delimitadores
            while(ptr != NULL){
              
                registro[i++] = ptr;
                ptr = strtok(NULL,",");
            }
// Si el país del registro coincide con el país ingresado por el usuario, imprimir la información
            if (strcmp(registro[2], pais) == 0) {
                printf("\nPasaporte: %s\nNombre: %s\nPaís: %s\n", 
                       registro[0],
                       registro[1],
                       registro[2]);
                printf("Lugares Favoritos: %s\n", registro[3]);
            }
        }
    }
    fclose(file);
}

void mostrarPuntosInteresPorTipo() {
    char tipo[100];
    PuntoInteres punto;
    
    printf("\nIngrese el tipo de punto de interés: ");
    fgets(tipo, 100, stdin);
    tipo[strcspn(tipo, "\n")] = 0;
    FILE *file = fopen("puntos_interes.csv", "r");
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", punto.nombre, punto.tipo, punto.direccion, punto.horario, punto.descripcion) != EOF) {

// Compara el tipo ingresado por el usuario con el tipo del punto de interés actual.
        if (strcmp(tipo, punto.tipo) == 0) {
// Si coinciden los tipos, muestra la información del punto de interés.
            printf("\nNombre: %s\nTipo: %s\nDirección: %s\nHorario: %s\nDescripción: %s\n", 
                   punto.nombre, punto.tipo, punto.direccion, punto.horario, punto.descripcion);
        }
    }
    fclose(file);
}

void importarDesdeCSV(char* nombre_archivo_puntos, char* nombre_archivo_turistas) {
    PuntoInteres punto;
    Turista turista;
    FILE *file = fopen(nombre_archivo_puntos, "r");
    
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", nombre_archivo_puntos);
        return;
    }
    
    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^\n]\n", punto.nombre, punto.tipo, punto.direccion, punto.horario, punto.descripcion) != EOF) {
//Se han leído los datos de una línea del archivo CSV y se han almacenado en la estructura 'punto'.
    }   
    fclose(file);
  
    file = fopen(nombre_archivo_turistas, "r");
    
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", nombre_archivo_turistas);
        return;
    }

  // Este bucle se ejecuta mientras fscanf pueda leer con éxito
    while (fscanf(file, "%[^,],%[^,],%[^,\n]\n", turista.pasaporte, turista.nombre, turista.pais) != EOF) {

        Nodo *nuevoNodo = (Nodo *)malloc(sizeof(Nodo));
        if (nuevoNodo == NULL) {
            printf("No se pudo asignar memoria para un nuevo nodo\n");
            fclose(file);
            return;
        }
      // Se asigna la estructura 'turista' al nodo recién creado.
        nuevoNodo->turista = turista; 

      // El nuevo nodo apunta al nodo que antes era el primero en la lista.
        nuevoNodo->siguiente = listaTuristas;  

      /* La cabeza de la lista (listaTuristas) ahora se actualiza para        
       apuntar al nuevo nodo, convirtiéndolo en el nuevo primer nodo de la 
       lista.
      */
        listaTuristas = nuevoNodo;
    }
    printf("Se importó exitosamente el archivo csv\n");
    fclose(file);
}


// exportar archivos se utiliza "W" ya que es modo escritura
void exportarACSV(char* nombre_archivo_puntos, char* nombre_archivo_turistas) {
    PuntoInteres punto;
    FILE *file = fopen(nombre_archivo_puntos, "w");
    fclose(file);
    file = fopen(nombre_archivo_turistas, "w");
  
   // Obtiene un puntero al primer nodo de la lista de turistas.
    Nodo *nodoActual = listaTuristas;
    while (nodoActual != NULL) {
        fprintf(file, "%s,%s,%s\n", nodoActual->turista.pasaporte,
                                    nodoActual->turista.nombre,
                                    nodoActual->turista.pais);
        
        for (int i = 0; i < nodoActual->turista.numLugaresFavoritos; i++) {
            fprintf(file, "%s,", nodoActual->turista.lugaresFavoritos[i]);
        }
        fprintf(file,"\n");
        nodoActual = nodoActual->siguiente;
    }
    printf("Se exporto exitosamente el archivo csv");
    fclose(file);
}