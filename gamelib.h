int imposta_gioco();
int combatti();
void termina_gioco();


enum Classe_mago {VITA,TENEBRE,LUCE};
enum Tipo_carta {CREATURA, RIMUOVI_CREATURA, INFLIGGI_DANNO, GUARISCI_DANNO};


struct Carta {
	enum Tipo_carta tipo;
	unsigned short pv;
	struct Carta* carta_successiva;

};


struct Mago {
	char nome_mago[256];
	unsigned short punti_vita;
	enum Classe_mago classe;
	struct Carta* inizio_mazzo;//pfirst
  //struct Carta* fine_mazzo; //plast
  	struct Carta* mano[6];
  	struct Carta* campo[4];
};

belin
