#include <stdbool.h>
void buscaTrayectosDiarios();
int generaTrayectosDiarios(struct sListaTrayectos listaTrayectosActivos, struct sListaTrayectos *listaTrayectosDiarios, char diaSemana, char estacionIntroducida[]);
bool buscaDiaEnFrecuencia(char frecuencia[], char diaSemana);
