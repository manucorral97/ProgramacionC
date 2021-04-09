#ifndef __Estacion_h__
    #define __Estacion_h

    #include <stdbool.h>
    #include "../main/config.h"
    struct sEstacion
    {
        char id[DIM_ID_ESTACION];
        char nombre[DIM_NOM_ESTACION];
        char provincia[DIM_PROV_ESTACION];
        double latitud;
        double longitud;
    };

    bool existeEstacion(char nombreEstacion[]);
    bool agregaEstacionViaArchivo(char *nombreEstacion);
    void muestraEstacion(struct sEstacion estacion);
    bool scanEstacionCSV(struct sEstacion *pEstacion, FILE *ptr);




#endif



