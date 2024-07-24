#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "lib.h"


void inizializzaGriglia(Cella grigliaGiocatore[][COLONNE])
{
    int i = 0, j = 0;

    for (i = 0; i < RIGHE; i++) {
        for (j = 0; j < COLONNE; j++) {
            grigliaGiocatore[i][j].simbolo = ACQUA;
            grigliaGiocatore[i][j].posizione.riga = i;
            grigliaGiocatore[i][j].posizione.colonna = j;
        }
    }
}

void stampaGriglia(Cella grigliaGiocatore[][COLONNE], int giocatore, int piazzando)
{
    int i = 0, j = 0;
    char carattereRiga = 'A';

    printf("\n  1 2 3 4 5 6 7 8 9 10\n");

    for (i = 0; i < RIGHE; i++) {
        printf("%c ", carattereRiga);

        for (j = 0; j < COLONNE; j++) {
            if (piazzando == 1) {
                printf("%c ", grigliaGiocatore[i][j].simbolo);
            } else {
                if (grigliaGiocatore[i][j].simbolo == COLPITO || grigliaGiocatore[i][j].simbolo == MANCATO) {
                    printf("%c ", grigliaGiocatore[i][j].simbolo);
                } else {
                    printf("%c ", ACQUA);
                }
            }
        }
        printf("\n");
        carattereRiga++;
    }
    printf("\n");
}

void piazzaNaviManualmente(Cella grigliaGiocatore[][COLONNE], Nave *navi)
{
    int i = 0, riga = 0, colonna = 0, direzione = 0, flag = 0;
    char car;

    for (i = 0; i < NUM_NAVI; i++) {
        stampaGriglia(grigliaGiocatore, GIOCATORE1, 1);
        printf("Piazzando %s (lunghezza: %d)\n", navi[i].nome, navi[i].lunghezza);

        do {
            flag = 0;
            while(getchar() !='\n');
            printf("Scrivi le coordinate di partenza (riga colonna, A1): ");
            scanf("%c %d", &car, &colonna);

            riga = toupper(car) - 'A';
            colonna--;

            do{
                printf("Scegli la direzione (0 -> ORIZZONTALE / 1 -> VERTICALE): ");
                scanf("%d", &direzione);
            }while(direzione != 0 && direzione != 1);

            if (controllaSovrapposizione(grigliaGiocatore, riga, colonna, direzione, navi[i].lunghezza)) {
                printf("Posizionamento non valido! E' gia' presente una nave o si e' sovrapposta con un'altra. Riprova.\n");
                flag = 1;
            } else {
                inserisciNavi(grigliaGiocatore, &navi[i], riga, colonna, direzione);
                flag = 0;
            }
        } while (flag == 1);
    }
}

void inserisciNavi(Cella grigliaGiocatore[][COLONNE], Nave *nave, int riga, int colonna, int direzione)
{
    int i = 0;
    nave->coord.colonna = colonna;
    nave->coord.riga = riga;

    if (direzione == ORIZZONTALE) {
        for (i = colonna; i < colonna + nave->lunghezza; i++) {
            grigliaGiocatore[riga][i].simbolo = nave->simbolo;
        }
    } else if (direzione == VERTICALE) {
        for (i = riga; i < riga + nave->lunghezza; i++) {
            grigliaGiocatore[i][colonna].simbolo = nave->simbolo;
        }
    }
}

void piazzaNaviRandom(Cella grigliaGiocatore[][COLONNE], Nave *navi)
{
    int i = 0, riga = 0, colonna = 0, direzione = 0;

    for (i = 0; i < NUM_NAVI; i++) {
        do {
            riga = rand() % RIGHE;
            colonna = rand() % COLONNE;
            direzione = rand() % 2;
        } while (controllaSovrapposizione(grigliaGiocatore, riga, colonna, direzione, navi[i].lunghezza) == 1);

        navi[i].direzione = direzione;

        inserisciNavi(grigliaGiocatore, &navi[i], riga, colonna, direzione);
    }
}

int controllaSovrapposizione(Cella grigliaGiocatore[][COLONNE], int riga, int colonna, int direzione, int lunghezza)
{
    int i = 0, flag = 0;

    if (direzione == ORIZZONTALE && (colonna + lunghezza) > COLONNE) {
        flag = 1;
    } else if (direzione == VERTICALE && (riga + lunghezza) > RIGHE) {
        flag = 1;
    }

    if (direzione == ORIZZONTALE) {
        for (i = colonna; i < colonna + lunghezza; i++) {
            if (grigliaGiocatore[riga][i].simbolo != ACQUA) {
                flag = 1;
            }
        }
    } else if (direzione == VERTICALE) {
        for (i = riga; i < riga + lunghezza; i++) {
            if (grigliaGiocatore[i][colonna].simbolo != ACQUA) {
                flag = 1;
            }
        }
    }

    if(flag == 1)
        return 1; // Sovrapposizione
    else
        return 0; // Nessuna sovrapposizione
}

Coordinate generaCoordinateRandom()
{
    Coordinate coord;

    coord.riga = rand() % RIGHE;
    coord.colonna = rand() % COLONNE;

    return coord;
}

void giocatoreVsGiocatore(Cella grigliaGiocatore1[][COLONNE], Cella grigliaGiocatore2[][COLONNE], Nave *navi)
{
    int turn = GIOCATORE1, flag = 0;

    printf("Giocatore 1, piazza le tue navi:\n");
    piazzaNaviManualmente(grigliaGiocatore1, navi);
    system("cls");

    printf("Giocatore 2, piazza le tue navi:\n");
    piazzaNaviManualmente(grigliaGiocatore2, navi);
    system("cls");

    while (flag == 0) {
        if (turn == GIOCATORE1 && flag == 0) {
            printf("Turno del giocatore 1:\n");
            turnoGiocatore(grigliaGiocatore1, grigliaGiocatore2, navi, "Player One");
            stampaGriglia(grigliaGiocatore2, GIOCATORE2, 0);

            if (controllaVincita(grigliaGiocatore2, navi) == 1) {
                printf("Il giocatore 1 ha vinto!\n");
                flag = 1;
            }

            turn = GIOCATORE2;
        } else if (turn == GIOCATORE2 && flag == 0) {
            printf("Turno del giocatore 2:\n");
            turnoGiocatore(grigliaGiocatore2, grigliaGiocatore1, navi, "Player Two");
            stampaGriglia(grigliaGiocatore1, GIOCATORE1, 0);

            if (controllaVincita(grigliaGiocatore1, navi) == 1) {
                printf("Il giocatore 2 ha vinto!\n");
                flag = 1;
            }

            turn = GIOCATORE1;
        }
    }
}

void giocatoreVsComputer(Cella grigliaGiocatore[][COLONNE], Cella grigliaComputer[][COLONNE], Nave *navi)
{
    int flag = 0;

    printf("Giocatore, piazza le tue navi:\n");
    piazzaNaviManualmente(grigliaGiocatore, navi);

    printf("Il computer stab piazzando le sue navi...\n");
    piazzaNaviRandom(grigliaComputer, navi);

    do{
        flag = 0;
        if(flag == 0){
            printf("Turno del giocatore:\n");
            turnoGiocatore(grigliaGiocatore, grigliaComputer, navi, "Giocatore");
            stampaGriglia(grigliaComputer, COMPUTER, 0);

            if (controllaVincita(grigliaComputer, navi) == 1) {
                printf("Il giocatore ha vinto!\n");
                flag = 1;
            }
        }

        if(flag == 0){
            printf("Turno del computer:\n");
            turnoComputer(grigliaComputer, grigliaGiocatore, navi);
            stampaGriglia(grigliaGiocatore, GIOCATORE1, 0);

            if (controllaVincita(grigliaGiocatore, navi) == 1) {
                printf("Il computer ha vinto!\n");
                flag = 1;
            }
        }
    } while(flag == 0);
}

void turnoGiocatore(Cella grigliaGiocatore[][COLONNE], Cella grigliaAvversario[][COLONNE], Nave *navi, char *nomeGiocatore)
{
    char carattereRiga;
    int riga = 0, colonna = 0, flag = 0;

    do {
        printf("%s, immetti le coordinate (riga colonna, A1): ", nomeGiocatore);

        while(getchar() != '\n');
        scanf("%c%d", &carattereRiga, &colonna);

        riga = toupper(carattereRiga) - 'A';
        colonna--;

        if (riga < 0 || riga >= RIGHE || colonna < 0 || colonna >= COLONNE) {
            printf("Coordinate non valide! Riprova.\n");
        } else if (grigliaAvversario[riga][colonna].simbolo == COLPITO || grigliaAvversario[riga][colonna].simbolo == MANCATO) {
            printf("Hai gia' mirato questa cella! Riprova.\n");
        } else {
            flag = 1;
        }
    } while (flag == 0);

    if (grigliaAvversario[riga][colonna].simbolo == ACQUA) {
        printf("MANCATO!\n");
        grigliaAvversario[riga][colonna].simbolo = MANCATO;
    } else {
        printf("COLPITO!\n");
        grigliaAvversario[riga][colonna].simbolo = COLPITO;
    }
}

void turnoComputer(Cella grigliaGiocatore[][COLONNE], Cella grigliaAvversario[][COLONNE], Nave *navi)
{
    Coordinate target;
    int riga = 0, colonna = 0;

    do {
        target = generaCoordinateRandom();
        riga = target.riga;
        colonna = target.colonna;
    } while (grigliaAvversario[riga][colonna].simbolo == COLPITO || grigliaAvversario[riga][colonna].simbolo == MANCATO);

    printf("Il computer mira a %c%d: ", 'A' + riga, colonna + 1);

    if (grigliaGiocatore[riga][colonna].simbolo == ACQUA) {
        printf("MANCATO!\n");
        grigliaAvversario[riga][colonna].simbolo = MANCATO;
    } else {
        printf("COLPITO!\n");
        grigliaAvversario[riga][colonna].simbolo = COLPITO;
    }
}

int controllaNaviAffondate(Cella grigliaGiocatore[][COLONNE], Nave *navi, char simbolo)
{
    int i = 0, j = 0, contColpiti = 0, numAffondate = 0;
    int row = 0, col = 0;

    for (i = 0; i < NUM_NAVI; i++) {
        contColpiti = 0;
        row = navi[i].coord.riga;
        col = navi[i].coord.colonna;


        for (j = 0; j < navi[i].lunghezza; j++) {
            if (COLPITO == grigliaGiocatore[row][col].simbolo) {
                contColpiti++;
            }

            if (navi[i].direzione == ORIZZONTALE) {
                col++;
            } else if (navi[i].direzione == VERTICALE) {
                row++;
            }
        }

        if (contColpiti == navi[i].lunghezza) {
            numAffondate++;
        }
    }

    return numAffondate;
}

int controllaVincita(Cella grigliaGiocatore[][COLONNE], Nave *navi)
{
    int i = 0;

    for (i = 0; i < NUM_NAVI; i++) {
        if (controllaNaviAffondate(grigliaGiocatore, navi, navi[i].simbolo) == 5) {
            return 1;
        }
    }

    return 0;
}


