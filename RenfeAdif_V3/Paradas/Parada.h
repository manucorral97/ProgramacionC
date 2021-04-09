#ifndef __Parada_h__
    #define __Parada_h__
    #include "../main/config.h"
    struct sParada
    {
        char id[DIM_ID_PARADA];
        char estacion[DIM_NOM_ESTACION];
        char h_llegada[DIM_HORA];
        char h_salida[DIM_HORA];
    };

    void muestraParada(struct sParada parada);

#endif
