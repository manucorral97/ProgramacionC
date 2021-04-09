#include <stdbool.h>
void gotoxy(int x, int y);
void gotox(int x);
void setColorTexto(WORD colors);
bool leeItem(char cadena[], char separador, FILE* ptr);
int scanCarpeta(char lista[][10], char rutaCarpeta[]);
void ventanaPequena();
bool comparaNPosiciones(const char cadena1[], char cadena2[], int numeroPosiciones);
void copiarNPosiciones(char cadena1[], char cadena2[], int numeroPosiciones);
