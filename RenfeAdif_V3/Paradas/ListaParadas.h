#ifndef __ListaParadas_h__
    #define __ListaParadas_h__
    #include "../main/config.h"
    struct sListaParadas
    {
        int num;
        struct sParada *lista;
    };

    void muestraGrupoParadas(struct sListaParadas listaParadas, int inic, int num);
    void navegaListaParadas(struct sListaParadas listaParadas);
    void scanParadaEnTrayecto(char IDTray[], struct sListaParadas *plParadas, FILE* ptr);
    void grabaParadasTrayecto(struct sListaParadas lParadas);
    void agregaAListaParadasBin(struct sListaParadas listaParadas);
    bool existeEstacionListaParadas (char nombreEstacion[]);
    void muestraParadasTrayectos(const char IDTray[]);
    void grabaListaParadas(struct sListaParadas plParadas, char archivo[]);
    void eliminaParadasTrayecto (const char IDTray[]);
    void cargaListaParadas(struct sListaParadas *plParadas, char archivo[]);
    void inicListaParadas(struct sListaParadas *plParadas);

#endif
