#include <stdio.h>

#include "gamelib.h"

int main(void){
	
	int scelta;
	int gioco_impostato = 0;
	
	do{
	printf("\nPer continuare fai una scelta:\n");
	printf("\n");
    printf(" ╔═══════════════════════════════════╗\n");
    printf(" ║  🎴 TRAGIC: IL GIOCO DI CARTE 🎴  ║\n");
    printf(" ╠═══════════════════════════════════╣\n");
    printf(" ║  1️⃣  Imposta Gioco                 ║\n");
    printf(" ║  2️⃣  Combatti                      ║\n");
    printf(" ║  3️⃣  Termina Gioco                 ║\n");
    printf(" ╚═══════════════════════════════════╝\n");
    
    scanf("%d", &scelta);
    
    while((getchar()) != '\n' ); // pulizia buffer di lettura dopo la scanf
    
    switch (scelta){
    		
    	case 1:
    	
    	gioco_impostato = imposta_gioco();
    	break;
    	
    	case 2:
    	if(gioco_impostato){
    		combatti();
    	
    	} else {
    	
    	printf(" ⚠️⚠️ Devi prima impostare il gioco per poter continuare ⚠️⚠️");
    	
    	
    	}
    	  
    	
    	break;
    	
    	case 3:
    	printf("\n\nChiusura del gioco in corso...\n");
   		termina_gioco();
    	break;
    	
    	default:
    	printf("\n\n❌❌❌ Inserisci una scelta valida ❌❌❌\n");
    	break;
    		
    }
}	while (scelta != 3);



}
