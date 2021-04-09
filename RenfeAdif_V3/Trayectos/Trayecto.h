#ifndef __Trayectos_h__
    #define __Trayectos_h__
    #include "../main/config.h"
        struct sTrayecto
    {
        char id[DIM_ID_TRAYECTO];
        char tipo[DIM_TIPO];
        char e_origen[DIM_NOM_ESTACION];
        char e_destino[DIM_NOM_ESTACION];
        char h_salida[DIM_HORA];
        char h_llegada[DIM_HORA];
        int duracion;
        float precio;
        char frecuencia[8];
    };
    bool scanTrayectoCSV(struct sTrayecto *pTrayecto, FILE *ptr);
    void agregaTrayecto(void);
    bool existeTrayecto(char *id);
    void muestraTrayecto(struct sTrayecto trayecto);
    void muestraGrupoArchivosTrayecto(char listaArchivos[][10], int inic, int num);
    bool seleccionaArchivoTrayecto(char* nombreArchivo);
    void agregaTrayectoABin(struct sTrayecto trayecto);
    bool queTrayecto(const char* IDSelec, struct sTrayecto *pTrayecto);


#endif
