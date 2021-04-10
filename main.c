#include<stdio.h>
#include<stdlib.h>
#include "gamelib.h"

int main(){
system("clear");
  printf("BENVENUTO IN ...");

  printf("\n               +----------------------------------------------------------------+\n");
  printf("               |          _______                                               |\n");
  printf("               |         |__   __|                                 _            |\n");
  printf("               |            | |                                   (_)           |\n");
  printf("               |            | |  _ __   __ _  _ __   _ __    ___   _            |\n");
  printf("               |            | | | '__| / _` || '_ \\ | '_ \\  / _ \\ | |           |\n");
  printf("               |            | | | |   | (_| || | | || | | |( |_| )| |           |\n");
  printf("               |            |_| |_|    \\__,_||_| |_||_| |_| \\___/ |_|           |\n");
  printf("               +----------------------------------------------------------------+\n");
  printf("\nUn gruppo di astronauti si trova in viaggio sull’astronave Skelt. Il loro obiettivo è riuscire a completare tutte le attività previste\n(le quest) per il mantenimento della nave, arrivando così a destinazione.Tra di loro si celano però anche degli impostori, il cui scopo è\neliminare di nascosto gli astronauti senza farsi scoprire da essi. Riusciranno ad arrivare a destinazione prima di essere decimati?\n");

  printf("\npremere INVIO per continuare\n");
  while(getchar() != '\n');//con questo loop si blocca il testo fino a che il giocatore non preme invio

  int scelta=0;
  int blocco=0;//con questa variabile si "blocca" la funziona Gioca() se prima non si è impostato il gioco
  system("clear");
do{
  printf("\n                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
  printf("\n                +                                                      +");
  printf("\n                +                   MENÙ PRINCIPALE                    +");
  printf("\n                +                                                      +");
  printf("\n                ++++++++++++++++++++++++++++++++++++++++++++++++++++++++");

  printf("\n\nInserisci 1) se vuoi impostare la partita.\nInserisci 2) se vuoi iniziare a giocare.\nInserisci 3) se vuoi uscire dal gioco.\n\n");
  printf("Inserire la propria scelta: ");
   scanf("%d", &scelta);
  switch(scelta)
  {
     case 1:
      Imposta_Gioco();
      blocco=1;
     break;
     case 2:
     if(blocco != 0){
      Gioca();}
     else{
      system("clear");
      printf("\nPrima di giocare devi impostare la partita.");
     }
     break;
     case 3:
      Termina_Gioco();
      break;
     default:
      system("clear");
      printf("\nValore non valido");
      while(getchar() != '\n');//se viene inserito un valore sbagliato (ad esempio una lettera) viene ripulito il buffer
  }
}while(scelta != 3);//si esce dal ciclo del menù principale solo se si vuole terminare il gioco (scelta=3)
return 0;
}
