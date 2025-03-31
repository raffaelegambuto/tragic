#include <stdio.h>
#include <stdlib.h> // per utilizzare srand() e rand()
#include "gamelib.h" /*per utilizzare time() La funzione time() restituisce il numero di secondi trascorsi dal 1 gennaio 1970 (Epoch Time).
		Il parametro &t è un puntatore a una variabile time_t, in cui viene salvato il valore restituito.*/
#include <time.h>



static struct Mago mago1;
static struct Mago mago2;
static unsigned short n_carte_mazzo = 0;
static void scegli_classe(struct Mago* mago);
static enum Tipo_carta tipo_casuale();
static void inserisci_carta(struct Mago* pmago, int numero_carta, int n_carte_mazzo);
static void riempi_mano(struct Mago* pmago);
static void stampa_mazzo(struct Mago* mago);
static char* stampa_tipo(enum Tipo_carta tipo);



void stampa_mazzo(struct Mago* pmago){
	if(pmago-> inizio_mazzo == NULL)
		printf("Non ci sono carte nel mazzo");
	else {
	struct Carta* ptemp = pmago -> inizio_mazzo;
	while(ptemp!= NULL){
		printf(" CARTA -> PV : %d TIPO : %s ", ptemp->pv , stampa_tipo(ptemp->tipo));
		ptemp = ptemp -> carta_successiva;
	
	}
	
	
	
	}

}





int imposta_gioco(){
	time_t t; /* inizializza il generatore di numeri casuali utilizzando il campo attuale */
	srand((unsigned) time(&t)); // funzione da chiamare una volta sola nel programma perché se usi solo rand(), otterrai sempre la stessa sequenza di numeri ad ogni esecuzione del programma.
	
	mago1.punti_vita = 20;
	mago2.punti_vita = 20;
	
	printf("Dammi il nome del MAGO1 🪄\n");
	fgets(mago1.nome_mago, 256, stdin);
	printf("Classe del mago: %d\n", mago1.classe);
	
	printf("Dammi il nome del MAGO2 🪄 \n");
	fgets(mago2.nome_mago, 256, stdin);
	
	
	//scegli_classe(&mago1);
  	//scegli_classe(&mago2);
	
	mago1.inizio_mazzo = NULL;    //mago non ha ancora carte nel mazzo
  	mago2.inizio_mazzo = NULL;

	printf("Dammi il numero di carte da inserire nel mazzo\n");
	scanf("%hu", &n_carte_mazzo);
	while (getchar() != '\n');
	printf("Hai inserito %hu carte nel mazzo", n_carte_mazzo);
	
	for(int i = 0; i<n_carte_mazzo; i++)
		inserisci_carta(&mago1, i, n_carte_mazzo);
	
	for(int i = 0; i<n_carte_mazzo; i++)
		inserisci_carta(&mago2, i, n_carte_mazzo);
		
		
	printf("Mazzo giocatore 1:\n");
	
	return 1;
	
	
	
}
	



static enum Tipo_carta tipo_casuale(){
	int random_number = rand() %100;
	if ( random_number < 40) {
	return CREATURA;
	} else if ( random_number < 65){
	return RIMUOVI_CREATURA;
	} else if (random_number < 85){
	return INFLIGGI_DANNO;
	} else return GUARISCI_DANNO;
}


 void inserisci_carta(struct Mago* pmago, int numero_carta, int n_carte_mazzo) {
	struct Carta* nuova_carta = (struct Carta*) (malloc(sizeof(struct Carta)));

	int n_rand = (rand() % 3 )-1;
	nuova_carta -> pv = ((7*(n_carte_mazzo - numero_carta))/ n_carte_mazzo) +1 +n_rand;
	nuova_carta -> pv = (nuova_carta -> pv <= 0 || nuova_carta -> pv >8 ) ? nuova_carta -> pv -n_rand : nuova_carta -> pv;
	nuova_carta -> tipo = tipo_casuale();
	nuova_carta -> carta_successiva = NULL; // perché per ora sarà l'ultima del mazzo
	
	
	switch (pmago->classe){
		 case VITA:
		 if(nuova_carta -> tipo == CREATURA){
		 	nuova_carta -> pv += nuova_carta -> pv/2; //+50%
		 }
		 break;
		  
		 case TENEBRE:
		 if(nuova_carta-> tipo == INFLIGGI_DANNO){
		 	nuova_carta -> pv += nuova_carta -> pv*2; // metà dei punti vita
		 }
		 break;
		 
		 case LUCE:
		 if(nuova_carta -> tipo = GUARISCI_DANNO){
		 	nuova_carta -> pv += (int)(3.5*nuova_carta -> pv); //tre volte e mezzo i punti vita
		 
		 }
		 break;
	}
	
}
	
	
	
	char* stampa_tipo(enum Tipo_carta tipo){
		switch (tipo) {
		
		case CREATURA:
		return "creatura";
		break;
		
		case RIMUOVI_CREATURA:
		return "rimuovi_creatura";
		break;
		
		case INFLIGGI_DANNO:
		return "infliggi_danno";
		break;
		
		case GUARISCI_DANNO:
		return "guarisci_danno";
		break;
		
		}
	
	
	}
	

	/*static void riempi_mano(struct Mago pmago){
		int i = 0;
		for (i = 0; i<6; i++
			pesca_carta(mano);}*/
		
		

	
	
	






int combatti(){

	return 1;
}



void termina_gioco(){
	printf("addio👋\n");
	



}
