#include<stdio.h>
#include<stdlib.h>
#include"gamelib.h"
#include <time.h>





static struct Giocatore* giocatori=NULL;
static unsigned short quest_da_finire;
static struct Stanza* stanza_inizio=NULL;
static struct elenco_stanze* ptr_primo_elem_lista_stanze=NULL;
struct elenco_stanze* ptr_elenco_stanze=NULL;
struct elenco_stanze* ptr_ultimo_lista=NULL;

struct elenco_stanze{
  struct Stanza* posizione_stanza;
  struct elenco_stanze* next;
};

int n_giocatori=0;
int impostori=0;
int astronauti=0;
int esito_funzione=0;
int abilita_uso_botole=0;

const char* colore_giocatore (enum Nome_giocatore Nome)
{
  switch(Nome){
    case rosso: return "rosso";
    break;
    case verde: return "verde";
    break;
    case giallo: return "giallo";
    break;
    case ciano: return "ciano";
    break;
    case arancione: return "arancione";
    break;
    case bianco: return "bianco";
    break;
    case nero: return "nero";
    break;
    case rosa: return "rosa";
    break;
    case blu: return "blu";
    break;
    case marrone: return "marrone";
    break;
  }
}

const char* Stato_giocatore (enum Stato_giocatore Stato)
{
  switch(Stato){
    case astronauta: return "astronauta";
    break;
    case impostore: return "impostore";
    break;
    case assassinato: return "assassinato";
    break;
    case defenestrato: return "defenestrato";
    break;

  }
}

static  struct Stanza* Creazione_stanza(struct Stanza* stanza_di_provenienza){
  int random=0;
  struct Stanza* stanza_da_creare;

  ptr_elenco_stanze = (struct elenco_stanze*) malloc(sizeof(struct elenco_stanze));//viene allocata la lista delle stanze
  if(stanza_di_provenienza==NULL){//prima stanza
    stanza_inizio = (struct Stanza*) malloc(sizeof(struct Stanza));//viene allocata prima stanza
    ptr_primo_elem_lista_stanze = ptr_elenco_stanze;
    ptr_elenco_stanze -> posizione_stanza = stanza_inizio;
    stanza_da_creare = stanza_inizio;
  }
  else{
    ptr_elenco_stanze -> posizione_stanza = (struct Stanza*) malloc(sizeof(struct Stanza));//allocazione nuova stanza
    abilita_uso_botole=1;//vedi riga 615
    ptr_ultimo_lista -> next = ptr_elenco_stanze;
    stanza_da_creare = ptr_elenco_stanze -> posizione_stanza;
  }
  ptr_elenco_stanze -> next = NULL;//inserimento in coda
  ptr_ultimo_lista = ptr_elenco_stanze;

  //ogni stanza appena creata ha i puntatori di direzione a NULL
  stanza_da_creare -> avanti= NULL;
  stanza_da_creare -> destra= NULL;
  stanza_da_creare -> sinistra= NULL;
  stanza_da_creare -> emergenza_chiamata= falso;
  stanza_da_creare -> stanza_precedente=stanza_di_provenienza;

  random = rand() %100;
  if(random<25){//si assegna alla nuova stanza il suo tipo
    stanza_da_creare -> Tipo = botola;
  }
  else if(random>24 && random<40){
    stanza_da_creare -> Tipo = quest_complicata;
  }
  else if(random>39 && random<70){
    stanza_da_creare -> Tipo = quest_semplice;
  }
  else{
    stanza_da_creare -> Tipo = vuota;
  }
return stanza_da_creare;
}


static void stampa_giocatori(int tipo_stampa){
  if (tipo_stampa == 1){//per far stampare sia nomi che stato
  for(int i=0; i<n_giocatori; i++){
    printf("\nIl giocatore %d è ", i+1);
    printf("%s", colore_giocatore(giocatori[i].Nome));//vedi riga 28
    printf(" ed il suo stato è %s", Stato_giocatore(giocatori[i].Stato));//vedi riga 54
  }}
  else//fa stampare solo nomi
  for(int i=0; i<n_giocatori; i++){
    printf("\n giocatore %d: ", i+1);
    printf("%s", colore_giocatore(giocatori[i].Nome));

}
}

const char* stanza_tipo (enum Tipo_stanza Tipo)
{
  switch(Tipo){
    case vuota: return "vuota";
    break;
    case quest_semplice: return "quest_semplice";
    break;
    case quest_complicata: return "quest_complicata";
    break;
    case botola: return "botola";
    break;
  }
}

static void avanza(int i){
  int scelta=0;
  do{
  printf("\nIn quale direzione vuoi avanzare?\n1)avanti\n2)destra\n3)sinistra\n4)rimani fermo\n\nInserire la propria scelta: ");
  scanf("%d", &scelta);
  switch(scelta){
    case 1:  if(giocatori[i].posizione->avanti==NULL)//se non è stata creata una stanza in questa direzione in precedenza, viene fatto
              giocatori[i].posizione -> avanti = Creazione_stanza(giocatori[i].posizione);
             giocatori[i].posizione = giocatori[i].posizione -> avanti;
    break;
    case 2:  if(giocatori[i].posizione->destra==NULL)//se non è stata creata una stanza in questa direzione in precedenza, viene fatto
              giocatori[i].posizione -> destra = Creazione_stanza(giocatori[i].posizione);
             giocatori[i].posizione = giocatori[i].posizione -> destra;
    break;
    case 3: if(giocatori[i].posizione->sinistra==NULL)//se non è stata creata una stanza in questa direzione in precedenza, viene fatto
              giocatori[i].posizione -> sinistra = Creazione_stanza(giocatori[i].posizione);
             giocatori[i].posizione = giocatori[i].posizione -> sinistra;
    break;
    case 4: //rimane fermo
    break;
    default: system("clear");
            printf("\nValore non valido");
            while(getchar() != '\n');//se viene inserito un valore sbagliato (ad esempio una lettera) viene ripulito il buffer

  }
}while(scelta>4 || scelta<1);
}


static void esegui_quest(int i){
  if(giocatori[i].posizione->Tipo==quest_semplice)//se è una stanza di tipo quest semplice verrà eseguita solo una quest
   quest_da_finire--;
  else{                                           //altrimenti verranno eseguite 2 quest
   if(quest_da_finire==1)
    quest_da_finire--;
   else
    quest_da_finire = quest_da_finire-2;}
    giocatori[i].posizione->Tipo=vuota;
}

static void chiamata_emergenza(int i){
printf("\nÈ stata chiamata un'emergenza!");
  int astr=0;
  int imp=0;
  int random=0;
  random = rand() % 100;
for(int j=0; j<n_giocatori; j++){//ciclo che conta quanti astronauti e quanti impostori sono presenti nella stanza
  if(giocatori[i].posizione==giocatori[j].posizione){
    if(giocatori[j].Stato==0)
    astr++;
    else if(giocatori[j].Stato==1)
    imp++;}}

  int probabilita[n_giocatori];
  for(int j=0; j<n_giocatori; j++){//ciclo che assegna ad ogni giocatore la probabilità di essere defenestrato
    if(giocatori[i].posizione==giocatori[j].posizione){
      if(giocatori[j].Stato==0)
       probabilita[j] = 30+(20*imp)-(30*(astr-1));
      else if(giocatori[j].Stato==1)
       probabilita[j] = 30+(20*astr)-(30*(imp-1));
    }
  }

  int blocco=0;
  for(int j=0; j<n_giocatori; j++){
    if(giocatori[i].posizione==giocatori[j].posizione){
      if(random<probabilita[j]){
        if(giocatori[j].Stato==1){
          impostori--;
        }
        else if(giocatori[j].Stato==0){
          astronauti--;
        }
        giocatori[j].Stato = 3;//il giocatore estratto viene defenestrato
        printf("\nIl giocatore %s è stato defenestrato!", colore_giocatore(giocatori[j].Nome));
        blocco=1;
        giocatori[i].posizione->emergenza_chiamata=vero;//non potrà essere più chiamata un'emergenza in questa stanza
        break;
      }
    }
  }
    if(blocco==0)
     printf("\nNessun giocatore è stato defenestrato");
}

static void uccidi_astronauta(int i){

 int a=0;
 int scelta=0;
 int bgiocatore[n_giocatori-1];
 int probabilita=0;
 int random=0;

 printf("\nChi vuoi assassinare?");
 for(int j=0; j<n_giocatori; j++){//stampa tutti gli astronauti nella stanza
  if(giocatori[i].posizione==giocatori[j].posizione)
   if(giocatori[j].Stato==0){
       bgiocatore[a] = j;//ad ogni astronauta nella stanza viene assegnato un numero
       a++;
       printf("\n%d)%s", a, colore_giocatore(giocatori[j].Nome));
   }
  }
printf("\n99)torna indietro(no assassinio)");
do{
 printf("\nInserire la propria scelta: ");
 scanf("\n%d", &scelta);
 if(scelta==99)
 break;
 if(scelta>a || scelta<1)
  printf("\nValore non valido");
 if(scelta==0){
   while(getchar() != '\n');//se viene inserito un valore sbagliato (ad esempio una lettera) viene ripulito il buffer
 }
}
while(scelta>a || scelta<1);
if(scelta==99)
 esito_funzione=1;//assassinio abortito
else{
 esito_funzione=0;
 giocatori[bgiocatore[scelta-1]].Stato = 2;//astronauta scelto viene ucciso
 astronauti--;
 printf("\nIl giocatore %s è stato assassinato!", colore_giocatore(giocatori[scelta-1].Nome));
 probabilita = 50 * (a-1);//calcolo della probabilità che l'impostore venga defenestrato
 for(int j=0; j<n_giocatori; j++){
   if(giocatori[j].posizione==giocatori[i].posizione->stanza_precedente)
    if(giocatori[j].Stato==0)
     probabilita = probabilita + 20;
  }
  random = rand() % 100;
  if(random<probabilita){
   giocatori[i].Stato = 3;//impostore defenestrato
   impostori--;
   printf("\nIl giocatore %s è stato defenestrato!", colore_giocatore(giocatori[i].Nome));
   }
 }

}

static void usa_botola(int i){

struct elenco_stanze* ptr_primo_elem_lista_stanze_botola=NULL;
struct elenco_stanze*ptr_elenco_stanze_botola=NULL;
struct elenco_stanze*ptr_ultimo_elem_lista_stanze_botola=NULL;
struct elenco_stanze* ptr=NULL;
struct elenco_stanze* ptr2=NULL;

int nr_stanze=0;
int random=0;
int ctr=0;

ptr=ptr_primo_elem_lista_stanze;

while(ptr!=NULL){                                //si scorrono tutte le stanze create fino ad ora
if(ptr->posizione_stanza!=giocatori[i].posizione)//diverse da quella attuale
 if(ptr->posizione_stanza->Tipo==botola){
   ptr_elenco_stanze_botola = (struct elenco_stanze*) malloc(sizeof(struct elenco_stanze));//viene allocata lista di stanze con botola
   if(ptr_primo_elem_lista_stanze_botola==NULL){//se è la prima stanza con botola della lista viene messa in testa
    ptr_primo_elem_lista_stanze_botola = ptr_elenco_stanze_botola;
   }
   else{//se non è la prima stanza con botola
    ptr_ultimo_elem_lista_stanze_botola -> next = ptr_elenco_stanze_botola;}//inserimento in coda
   ptr_elenco_stanze_botola->posizione_stanza = ptr->posizione_stanza;
   ptr_elenco_stanze_botola->next = NULL;
   ptr_ultimo_elem_lista_stanze_botola = ptr_elenco_stanze_botola;//ultimo elemento inserito viene messo in coda
 }
ptr = ptr->next;//per scorrere tutte le stanze
}


ptr = ptr_primo_elem_lista_stanze_botola;
while(ptr!=NULL){//si scorre la lista con tutte le stanze con botola
// if(ptr->posizione_stanza!=giocatori[i].posizione)
   nr_stanze++;//si contano le stanze con botola diverse da quella attuale
 ptr=ptr->next;
}

//ptr=ptr_primo_elem_lista_stanze_botola;

if(nr_stanze>0){//se c'è almeno un'altra stanza con botola
 random=1 + rand() %nr_stanze;//si estrae un numero a caso da 1 a nr_stanze(con botola)
 ptr = ptr_primo_elem_lista_stanze_botola;
 while(ptr!=NULL){//si scorrono le stanze
  ctr++;
  if(ctr==random){//fino a che non si trova la stanza "estratta"
    giocatori[i].posizione = ptr->posizione_stanza;//si cambia la posizione del giocatore con quella della stanza estratta
    break;
  }
  ptr=ptr->next;
 }
}
else{//se non ci sono stanze con botola utili
 ptr = ptr_primo_elem_lista_stanze;
 while(ptr!=NULL){//si scorrono tutte le altre stanze
  if (ptr->posizione_stanza!=giocatori[i].posizione)
   nr_stanze++;//si contano quante sono le stanze in totale esclusa quella attuale
  ptr=ptr->next;
 }
 random=1 + rand() %nr_stanze;//si estrae un numero da 1 a nr_stanze
 ptr = ptr_primo_elem_lista_stanze;
 while(ptr!=NULL){//si scorrono tutte le stanze
  if (ptr->posizione_stanza!=giocatori[i].posizione){//esclusa quella attuale
   ctr++;
   if(ctr==random){//fino a che non si trova quella "estratta"
    giocatori[i].posizione = ptr->posizione_stanza;
    break;
   }
  }
  ptr=ptr->next;
 }
}
 ptr = ptr_primo_elem_lista_stanze_botola;
 while(ptr!=NULL){//se viene creata una lista per le stanze con botola essa viene deallocata a fine funzione
   ptr2 = ptr->next;
   free(ptr);
   ptr=ptr2;
 }
}

static void sabotaggio(int i){
  giocatori[i].posizione->Tipo=vuota;//la stanza passa da tipo quest a tipo vuota
}


void libera_memoria(){

struct elenco_stanze* ptr=NULL;
struct elenco_stanze* ptr2=NULL;

ptr = ptr_primo_elem_lista_stanze;

while(ptr!=NULL){
  free(ptr->posizione_stanza);
  ptr2 = ptr->next;
  free(ptr);
  ptr=ptr2;
}
free(giocatori);
}


void Imposta_Gioco(){

 if(giocatori!=NULL){//se è stata impostata una partita precedentemente rilascia memoria allocata
   libera_memoria();//(vedi riga 365)
 }

system("clear");
srand(time(0));
printf("\n                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
printf("\n                +                                                      +");
printf("\n                +                     IMPOSTAZIONI                     +");
printf("\n                +                                                      +");
printf("\n                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++");



  do{
    printf("\n\nNumero giocatori (min 4 max 10): ");//viene richiesto il numero dei giocatori
    scanf("%d", &n_giocatori);
    if(n_giocatori==0){
      printf("\nValore non valido");
      while(getchar() != '\n');//se viene inserito un valore sbagliato(ad esempio una lettera) viene ripulito il buffer
    }
    if(n_giocatori>10){
      printf("\nERRORE: troppi giocatori.");
    }
    else if(n_giocatori<4 && n_giocatori!=0){
      printf("\nERRORE: giocatori insufficienti.");
    }
  } while(n_giocatori<4 || n_giocatori>10);//se i giocatori sono più di 10 o meno
                                           //di 4 viene richiesto il numero dei giocatori
  int nomi[n_giocatori];

  for(int i=0; i<n_giocatori; i++){//ciclo che genera 10 numeri casualmente e senza ripetizioni
    nomi[i] = rand() % 10;
    for(int j=0; j<i; j++){
     if(nomi[i]==nomi[j]){
      i--;
      break;
     }
    }
  }
 giocatori = (struct Giocatore*) calloc(n_giocatori, sizeof(struct Giocatore));

int random1=0;
do{//ciclo per assegnare casualmente i ruoli(stato=0:astronauta stato=1:impostore)
for(int i=0; i<n_giocatori; i++){
  if(impostori==3)//non possono esserci più di 3 impostori
  {
    break;
  }
  random1 = rand() % 100;
  if(n_giocatori<7)
  {
   if(random1 < 25)
   {
    giocatori[i].Stato = 1;
    impostori++;
   }
   else
    giocatori[i].Stato = 0;
  }
  else if(n_giocatori<9)
  {
   if(random1 < 50)
   {
     giocatori[i].Stato = 1;
     impostori++;
   }
   else
     giocatori[i].Stato = 0;
  }
  else if(n_giocatori < 11)
  {
    if(random1 < 75)
    {
      giocatori[i].Stato = 1;
      impostori++;
    }
    else
      giocatori[i].Stato = 0;
  }
}
} while(impostori<1);//ciclo si ripete fino a che non si ha almeno un impostore

astronauti = n_giocatori-impostori;

do{
  printf("\nNumero quest da completare : ");//viene richiesto il numero di quest
  scanf("%hd", &quest_da_finire);
  if(quest_da_finire==0){
    printf("\nValore non valido");
    while(getchar() != '\n');//se viene inserito un valore sbagliato(ad esempio una lettera) viene ripulito il buffer
  }
  if(astronauti>quest_da_finire && quest_da_finire!=0)
   printf("\nERRORE: le quest da completare devono essere pari minimo al numero di astronauti");
  else if(astronauti*2<quest_da_finire)
   printf("\nERRORE: le quest da completare possono essere massimo 2 per ogni astronauta");
}while(astronauti>quest_da_finire || quest_da_finire>astronauti*2);//numero di quest deve essere alemo pari a quello degli astronauti ma non il doppio

Creazione_stanza(NULL);//vedi riga 69
for(int i=0; i<n_giocatori; i++){//ciclo per assegnare nome e posizione ad ogni giocatore
  giocatori[i].posizione = stanza_inizio;
  giocatori[i].Nome=nomi[i];
}
int scelta=0;
do{
  printf("\n\nInserisci 1) se vuoi visualizzare tutte le informazioni relative ad ogni giocatore\nInserisci 2) se vuoi salvare le impostazioni e tornare al menù principale");
  printf("\n\nInserire la propria scelta: ");
  scanf("%d", &scelta);
  switch(scelta)
  {
    case 1: stampa_giocatori(1);//vedi riga 113
    break;
    case 2: system("clear");//pulisce schermo
    break;
    default: printf("\nValore non valido");
               while(getchar() != '\n');//se viene inserito un valore sbagliato(ad esempio una lettera) viene ripulito il buffer
  }
}while(scelta!=2);
}

void Gioca(){
int scelta=0;
int blocco=0;
int scelta_uccidi=0;
int astr=0;
 system("clear");
 printf("I turni sono i seguenti: ");
 stampa_giocatori(2);//vedi riga 113
while(getchar() != '\n');
do{
  printf("\nPremere invio per iniziare il giro");
while(getchar() != '\n');
system("clear");
for(int i=0; i<n_giocatori; i++){//ciclo che gestisce i turni
  if(giocatori[i].Stato==0||giocatori[i].Stato==1){//non permette ai giocatori assassinati o defenestrati(stato=2 e stato=3) di giocare
   printf("Giocatore %s (%s) è il tuo turno!\n Ti trovi in una stanza di tipo %s", colore_giocatore(giocatori[i].Nome),Stato_giocatore(giocatori[i].Stato), stanza_tipo(giocatori[i].posizione->Tipo));//vedi riga 128
   printf("\nIn questa stanza sono presenti i seguenti giocatori:");
   for(int j=0; j<n_giocatori; j++){
    if(giocatori[i].Stato==0){
     if(giocatori[i].posizione == giocatori[j].posizione){
      if(giocatori[j].Stato==1||giocatori[j].Stato==0)//stampa tutti i giocatori vivi presenti nella stanza
        printf("\n %s", colore_giocatore(giocatori[j].Nome));
      else if(giocatori[j].Stato==2)//stampa i cadaveri presenti nella stanza
        printf("\n %s(cadavere)", colore_giocatore(giocatori[j].Nome));
     }
    }
    if(giocatori[i].Stato==1){
     if(giocatori[i].posizione == giocatori[j].posizione){
      if(giocatori[j].Stato==0)
        printf("\n %s", colore_giocatore(giocatori[j].Nome));
      else if(giocatori[j].Stato==2)
        printf("\n %s(cadavere)", colore_giocatore(giocatori[j].Nome));
      else if(giocatori[j].Stato==1)//nel caso in cui il giocatore che sta giocando sia un impostore vengono stampati gli impostori presenti nella sua stanza
        printf("\n %s(impostore)", colore_giocatore(giocatori[j].Nome));
     }
    }
   }
   printf("\nNumero quest rimaste: %d", quest_da_finire);

   if(giocatori[i].Stato==0){//turno di un astronauta
    do{
     blocco=0;
     printf("\nChe cosa vuoi fare?\n1)avanza\n2)esegui quest\n3)chiama emergenza\nInserire la propria scelta: ");
     scanf("%d", &scelta);
     switch(scelta){
      case 1: avanza(i);//vedi riga 142
              blocco++;
      break;
      case 2: if(giocatori[i].posizione->Tipo==quest_semplice||giocatori[i].posizione->Tipo==quest_complicata){//solo se si trova in una stanza di tipo quest
               esegui_quest(i);//vedi riga 171
               blocco++;}
              else
               printf("\nIn questa stanza non ci sono quest da fare!");
      break;
      case 3: if(giocatori[i].posizione->emergenza_chiamata==falso){//potrà essere chiamata un'emergenza solo se non è stata chiamata in prcedenza in quella stanza
               for(int j=0; j<n_giocatori;j++){
                if(giocatori[i].posizione==giocatori[j].posizione)
                 if(giocatori[j].Stato==2)                             //e se ci sarà un cadavere
                  blocco++;
               }
               if(blocco!=0){
                chiamata_emergenza(i);//vedi riga 182
               }
               else
                printf("\nNon ci sono cadaveri in questa stanza!");
              }
              else
               printf("\nÈ stata già chiamata un'emergenza in questa stanza!");
      break;
      default: printf("\nValore non valido");
               while(getchar() != '\n');//se viene inserito un valore sbagliato (ad esempio una lettera) viene ripulito il buffer
     }
    }while(blocco==0);//se blocco=0 significa che non è stata eseguita nessuna azione quindi si ripete il ciclo
   }
   else if(giocatori[i].Stato==1){//turno di un impostore
    do{
     blocco=0;
     printf("\nChe cosa vuoi fare?\n1)avanza\n2)uccidi astronauta\n3)chiama emergenza\n4)usa botola\n5)sabota\nInserire la propria scelta: ");
     scanf("%d", &scelta);
     switch(scelta){
      case 1: avanza(i);//vedi riga 142
            blocco++;
      break;
      case 2:  astr=0;
               for(int j=0; j<n_giocatori; j++){//ciclo che conta gli astronauti presenti nella stanza
                if(giocatori[i].posizione==giocatori[j].posizione){
                 if(giocatori[j].Stato==0)
                  astr++;
                }
               }
               if(astr==0)//se non ci sono astronauti non si può uccidere nessuno
                printf("\nNon ci sono astronauti in questa stanza!");
               else{
                uccidi_astronauta(i);//vedi riga 226
                if(esito_funzione==0)//esito=0:uccisione confermata.
                  blocco++;         //esito=1:assassinio abortito.
               }
      break;
      case 3: if(giocatori[i].posizione->emergenza_chiamata==falso){
               for(int j=0; j<n_giocatori;j++){
                if(giocatori[i].posizione==giocatori[j].posizione)
                 if(giocatori[j].Stato==2)
                  blocco++;
                }
                 if(blocco!=0)
                  chiamata_emergenza(i);//vedi riga 182
                 else
                  printf("\nNon ci sono cadaveri in questa stanza!");
              }
              else
               printf("\nÈ stata già chiamata un'emergenza in questa stanza!");
       break;
       case 4: if(abilita_uso_botole!=0){//permette di usare la funzione solo se sono state create più di una stanza
                if(giocatori[i].posizione->Tipo==botola){//si può usare una botola solo se si è in una stanza botola
                 usa_botola(i);//vedi riga 280
                 blocco++;
                }
                else
                printf("\nQuesta stanza non è di tipo botola!");}
               else{
                 printf("\nPer usare una botola devono essere create altre stanze!");
               }
       break;
       case 5: if(giocatori[i].posizione->Tipo==quest_semplice||giocatori[i].posizione->Tipo==quest_complicata){//si può sabotare solo se si è in una stanza di tipo quest
                sabotaggio(i);//vedi riga 360
                blocco++;}
               else
                printf("\nPuoi sabotare solo stanze di tipo quest!");
       break;
       default: printf("\nValore non valido");
                while(getchar() != '\n');//se viene inserito un valore sbagliato (ad esempio una lettera) viene ripulito il buffer
     }
    }while(blocco==0);
   }//if impostore
   printf("\nPremere invio per continuare");
   while(getchar() != '\n');
   while(getchar() != '\n');

 }//if impostore o austronata

 system("clear");

 if(quest_da_finire==0)//il gioco finisce se le quest vengono finite
  break;
 if(impostori==0)//il gioco finisce se vengono defenestrati tutti gli impostori
  break;
 if(astronauti==0)//il gioco finisce se tutti gli astronauti vengono uccisi
  break;

}//for
if(quest_da_finire==0){
  system("clear");
  printf("\n                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  printf("\n                +                                                      +");
  printf("\n                +                 VITTORIA ASTRONAUTI                  +");
  printf("\n                +                                                      +");
  printf("\n                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

  printf("\n\n               Gli astronauti sono riusciti a finire tutte le quest!");
  printf("\n\nPremere invio per tornare al menù principale");
  while(getchar() != '\n');
  break;
}
if(impostori==0){
  system("clear");
  printf("\n                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  printf("\n                +                                                      +");
  printf("\n                +                 VITTORIA ASTRONAUTI                  +");
  printf("\n                +                                                      +");
  printf("\n                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

  printf("\n\n               Tutti gli impostori sono stati defenestrati!");
  printf("\n\nPremere invio per tornare al menù principale");
  while(getchar() != '\n');
  break;
}
if(astronauti==0){
  system("clear");
  printf("\n                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  printf("\n                +                                                      +");
  printf("\n                +                  VITTORIA IMPOSTORI                  +");
  printf("\n                +                                                      +");
  printf("\n                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

  printf("\n\n               Tutti gli astronauti sono stati eliminati!");
  printf("\n\nPremere invio per tornare al menù principale");
  while(getchar() != '\n');
  break;
}
}while(1);
 system("clear");
}//gioca()


void Termina_Gioco(){
  libera_memoria();//vedi riga 365

}
