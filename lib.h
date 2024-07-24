#define RIGHE 10
#define COLONNE 10

#define NUM_NAVI 5

#define ORIZZONTALE 0
#define VERTICALE 1

#define GIOCATORE1 0
#define GIOCATORE2 1
#define COMPUTER 2

#define ACQUA '~'
#define COLPITO '*'
#define MANCATO 'm'

#define PORTAEREI 'p'
#define CORAZZATA 'c'
#define CROCIERA 'r'
#define SOTTOMARINO 's'
#define ASSALTO 'a'

typedef struct {
    int riga;
    int colonna;
} Coordinate;

typedef struct {
    char simbolo;
    int lunghezza;
    char nome[20];
    Coordinate coord;
    int direzione;
} Nave;

typedef struct {
    char simbolo;
    Coordinate posizione;
} Cella;

void inizializzaGriglia(Cella grigliaGiocatore[][COLONNE]);
void stampaGriglia(Cella grigliaGiocatore[][COLONNE], int giocatore, int piazzando);
void piazzaNaviManualmente(Cella grigliaGiocatore[][COLONNE], Nave *navi);
void inserisciNavi(Cella grigliaGiocatore[][COLONNE], Nave *nave, int riga, int colonna, int direzione);
void piazzaNaviRandom(Cella grigliaGiocatore[][COLONNE], Nave *navi);
int controllaSovrapposizione(Cella grigliaGiocatore[][COLONNE], int riga, int colonna, int direzione, int lunghezza);
Coordinate generaCoordinateRandom();
void giocatoreVsGiocatore(Cella grigliaGiocatore1[][COLONNE], Cella grigliaGiocatore2[][COLONNE], Nave *navi);
void giocatoreVsComputer(Cella grigliaGiocatore[][COLONNE], Cella grigliaComputer[][COLONNE], Nave *navi);
void turnoGiocatore(Cella grigliaGiocatore[][COLONNE], Cella grigliaAvversario[][COLONNE], Nave *navi, char *nomeGiocatore);
void turnoComputer(Cella grigliaGiocatore[][COLONNE], Cella grigliaAvversario[][COLONNE], Nave *navi);
int controllaNaviAffondate(Cella grigliaGiocatore[][COLONNE], Nave *navi, char simbolo);
int controllaVincita(Cella grigliaGiocatore[][COLONNE], Nave *navi);
