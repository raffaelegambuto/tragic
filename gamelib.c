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
static int pesca_carta(struct Mago* pmago);
static void inserisci_mano(struct Mago* mago, struct Carta* carta_da_inserire);



static void inserisci_mano(struct Mago* pmago, struct Carta* carta_da_inserire) {
  int i= 0; //cerca un posto libero nella mano
  for (i = 0; i < 6; i++)   //la mano ha 6 carte scorrere tutti e 6 gli slot da i=0->5
    if (pmago->mano[i] == NULL) {  //se trova uno slot vuoto la inserisce ed esce con break
      pmago->mano[i] = carta_da_inserire; 
      break;
    }
  if (i == 6) {   //se la mano è piena distrugge la carta
    printf("mano finita, distruggo la carta");
    free(carta_da_inserire);
    }
}





void stampa_mazzo(struct Mago* pmago){
	if(pmago-> inizio_mazzo == NULL)
		printf("Non ci sono carte nel mazzo\n");
	else {
		struct Carta* ptemp = pmago -> inizio_mazzo;  // punta alla prima carta del mazzo
		while(ptemp!= NULL){						  // scorre tutte le carte fino all'ultima
		printf(" CARTA -> PV : %d TIPO : %s\n", ptemp->pv , stampa_tipo(ptemp->tipo));
		ptemp = ptemp -> carta_successiva; //spostiamo ptemp alla prossima carta del mazzo
	
		}
	
	}

}



static int pesca_carta(struct Mago* pmago) {
  struct Carta* ptemp = pmago -> inizio_mazzo;
  	if (ptemp == NULL){
      	printf("Il gioco finisce, vince chi ha più PV\n");
      	if (mago1.punti_vita > mago2.punti_vita){
          printf("Il mago %s ha vinto il duello\n", mago1.nome_mago);
      	} else if (mago1.punti_vita < mago2.punti_vita) {
          printf("Il mago %s ha vinto il duello\n", mago2.nome_mago);
     	 } else  {
          printf("Il duello si è concluso con un pareggio!\n");
     	 }
      	return 1;
  	}
  	
  	else
      if (ptemp -> carta_successiva == NULL) {  //mazzo ha una sola carta
        printf("Ultima carta nel mazzo\n");
        inserisci_mano(pmago, ptemp);
        pmago -> inizio_mazzo = NULL; // il mazzo diventa vuoto 
      }
      else {
        while ((ptemp -> carta_successiva) -> carta_successiva != NULL) //il mazzo ha più carte  ptemp inizia dalla prima carta (pmago->inizio_mazzo).
          ptemp = ptemp -> carta_successiva; // il ciclo scorre fino alla penultima carta del mazzo
        inserisci_mano(pmago, ptemp -> carta_successiva); //l'ultima carta viene spostata nella mano
        ptemp -> carta_successiva = NULL; // e l'ultima carta viene rimossa dal mazzo;
      }
    return 0;
}






int imposta_gioco(){
	time_t t; /* inizializza il generatore di numeri casuali utilizzando il campo attuale */
	srand((unsigned) time(&t)); // funzione da chiamare una volta sola nel programma perché se usi solo rand(), otterrai sempre la stessa sequenza di numeri ad ogni esecuzione del programma.
	
	mago1.punti_vita = 20;
	mago2.punti_vita = 20;
	
	printf("Dammi il nome del MAGO1 🪄\n");
	fgets(mago1.nome_mago, 256, stdin);
	
	
	printf("Dammi il nome del MAGO2 🪄 \n");
	fgets(mago2.nome_mago, 256, stdin);
	
	
	//scegli_classe(&mago1);
  	//scegli_classe(&mago2);
	
	mago1.inizio_mazzo = NULL;    //mago non ha ancora carte nel mazzo
  	mago2.inizio_mazzo = NULL;

	printf("Dammi il numero di carte da inserire nel mazzo\n");
	scanf("%hu", &n_carte_mazzo);
	while (getchar() != '\n');
	printf("Hai inserito %hu carte nel mazzo\n", n_carte_mazzo);
	
	for(int i = 0; i<n_carte_mazzo; i++)
		inserisci_carta(&mago1, i, n_carte_mazzo);
	
	for(int i = 0; i<n_carte_mazzo; i++)
		inserisci_carta(&mago2, i, n_carte_mazzo);
		
	riempi_mano (&mago1);
  	riempi_mano(&mago2);
		
		
	printf("Mazzo giocatore 1:\n");
	stampa_mazzo(&mago1);
	printf("Mano giocatore 1:\n");
	stampa_mazzo(&mago2);
	
	return 1;
	
	
	
}
	



static enum Tipo_carta tipo_casuale(){  
	int random_number = rand() %100;  //numero casuale da 0 a 99
	if ( random_number < 40) {    // 40%
	return CREATURA;
	} else if ( random_number < 65){  //25%
	return RIMUOVI_CREATURA;
	} else if (random_number < 85){    //20%
	return INFLIGGI_DANNO;
	} else return GUARISCI_DANNO;  //15%
}


 void inserisci_carta(struct Mago* pmago, int numero_carta, int n_carte_mazzo) {  //numero carta-> indice del numero di carta mentre lo costruisco
	struct Carta* nuova_carta = (struct Carta*) (malloc(sizeof(struct Carta))); 

	int n_rand = (rand() % 3 )-1;
	nuova_carta -> pv = ((7*(n_carte_mazzo - numero_carta))/ n_carte_mazzo) +1 +n_rand;
	nuova_carta -> pv = (nuova_carta -> pv <= 0 || nuova_carta -> pv >8 ) ? nuova_carta -> pv -n_rand : nuova_carta -> pv;
	nuova_carta -> tipo = tipo_casuale(); // sceglie casualmente se sarà creatura,rimuovi creatura , infliggi danno o guarisci danno
	nuova_carta -> carta_successiva = NULL; // perché per ora sarà l'ultima del mazzo
	
	
	switch (pmago->classe){
		 case VITA:
		 if(nuova_carta -> tipo == CREATURA){
		 	nuova_carta -> pv += nuova_carta -> pv/2; //se mago ha classe vita, le carte creatura hanno la metà di pv in più
		 }
		 break;
		  
		 case TENEBRE:
		 if(nuova_carta-> tipo == INFLIGGI_DANNO){
		 	nuova_carta -> pv += nuova_carta -> pv*2; // /se mago ha classe tenebre, le carte infliggi_danno hanno il doppio di pv in più
		 }
		 break;
		 
		 case LUCE:
		 if(nuova_carta -> tipo == GUARISCI_DANNO){
		 	nuova_carta -> pv += (int)(3.5*nuova_carta -> pv); //se mago ha classe luce, le carte guarisci_danno hanno tre volte e mezzo in più
		 
		 }
		 break;
	}
	
}
	
	
	
	char* stampa_tipo(enum Tipo_carta tipo){  //Questa funzione accetta un valore di tipo enum Tipo_carta e restituisce un puntatore a carattere charé , ovvero una stringa corrispondente.
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

	static void riempi_mano(struct Mago* pmago){  // mago di cui dobbiamo riempire la carta
		int i = 0;
		for (i = 0; i<6; i++)
			pesca_carta(pmago);
	
	} 
		
		

	
	
	






int combatti(){

	return 1;
}



void termina_gioco(){
	printf("addio👋\n");
	



} cosa mi stampa
