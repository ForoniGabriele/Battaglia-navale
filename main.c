#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "lib.h"


int main() {
    srand(time(NULL));

    Cella grigliaGiocatore1[RIGHE][COLONNE];
    Cella grigliaGiocatore2[RIGHE][COLONNE];
    Cella grigliaComputer[RIGHE][COLONNE];

    Nave navi[NUM_NAVI] = {
        {'p', 5, "Portaerei", {0, 0}, ORIZZONTALE},
        {'c', 4, "Corazzata", {0, 0}, ORIZZONTALE},
        {'r', 3, "Crociera", {0, 0}, ORIZZONTALE},
        {'s', 3, "Sottomarino", {0, 0}, ORIZZONTALE},
        {'a', 2, "Assalto", {0, 0}, ORIZZONTALE}
    };

    int modalita;

    do {
        printf("BATTAGLIA NAVALE\n");
        printf("1. Giocatore 1 vs Giocatore 2\n");
        printf("2. Giocatore vs Computer\n");
        printf("\nScelta: ");
        scanf("%d", &modalita);
    } while (modalita < 1 || modalita > 2);

    inizializzaGriglia(grigliaGiocatore1);
    inizializzaGriglia(grigliaGiocatore2);
    inizializzaGriglia(grigliaComputer);

    switch (modalita) {
        case 1:
            giocatoreVsGiocatore(grigliaGiocatore1, grigliaGiocatore2, navi);
            break;
        case 2:
            giocatoreVsComputer(grigliaGiocatore1, grigliaComputer, navi);
    }

    return 0;
}
