#ifndef MAPAS_H
#define MAPAS_H

typedef struct {
    char nombre[100];
    char tipo[100];
    char direccion[100];
    char horario[100];
    char descripcion[100];
} PuntoInteres; 

typedef struct {
    char pasaporte[100];
    char nombre[100];
    char pais[100];
    char lugaresFavoritos[100][100]; 
    int numLugaresFavoritos;
} Turista;

typedef struct nodo {
    Turista turista;
    struct nodo *siguiente;
} Nodo;

void registrarPuntoInteres();
void mostrarPuntoInteres();
void eliminarPuntoInteres();
void registrarTurista();
void agregarLugarFavorito();
void mostrarTuristasPorPais();
void mostrarPuntosInteresPorTipo();
void importarDesdeCSV(char* nombre_archivo_puntos, char* nombre_archivo_turistas);
void exportarACSV(char* nombre_archivo_puntos, char* nombre_archivo_turistas);

#endif