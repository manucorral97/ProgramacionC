#ifndef __EstacionesCercanas_h__
#define __EstacionesCercanas_h__
struct sEstacionCercana
{
    char nombreEstacion[50];
    char nombreProvincia[30];
    float distancia;
};

struct sListaEstacionesCercanas
{
    int numeroElementos;
    struct sEstacionCercana *lista;
};

void buscaEstacionesCercanas();
float distanciaEntreEstaciones(struct sEstacion estacion1, struct sEstacion estacion2);
void grabaListaEstacionesCercanas(struct sListaEstacionesCercanas listaEstacionesCercanas);
void inicListaEstacionesCercanas(struct sListaEstacionesCercanas *plEstaciones);

#endif
