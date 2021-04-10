
enum Stato_giocatore {astronauta, impostore, assassinato, defenestrato};
enum Nome_giocatore {rosso, verde, giallo, ciano, arancione, bianco, nero, rosa, blu, marrone};
enum Tipo_stanza{vuota, quest_semplice, quest_complicata, botola};
enum emergenza_chiamata{vero, falso};

 struct Giocatore{
  struct Stanza* posizione;
  enum Stato_giocatore Stato;
  enum Nome_giocatore Nome;
};

struct Stanza {
  struct Stanza* avanti;
  struct Stanza* destra;
  struct Stanza* sinistra;
  struct Stanza* stanza_precedente;
  enum Tipo_stanza Tipo;
  enum emergenza_chiamata emergenza_chiamata;
};

void Imposta_Gioco();
void Gioca();
void Termina_Gioco();
