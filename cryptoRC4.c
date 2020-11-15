#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
typedef enum {false, true} bool;

int formatta(char *, int);

int main (void) {
  /* Define Variables */
  /* randomize using current time of execution */
  time_t toe;
  srand((unsigned)time(&toe));
  int maxlen = 128;
  int lk = 0;
  bool endp = false;

  char v1[2] = " ";
  char v2[2] = " ";
  char t1[1];
  char l1[5];
  char m[129];
  char k[129];
  char c[129];
  char h[129];
  char msg[80];


  while(endp==false){
    switch(*v1){
    // Show Main Menu
    case ' ':
      system("clear");
      printf("PROGRAMMA DI CIFRATURA RC4\n\n\nSeleziona una voce:\n\n1. Codifica una stringa di max %d caratteri\n2. Cambia lunghezza max\n9. Esci\n\n", maxlen);
      while(v1[0]!='1' && v1[0]!='2' && v1[0]!='9'){
        printf(" > ");
        scanf("%s", v1);
      }
      break;
    // Show Crypting Menu
    case '1':
      system("clear");
      printf("PROGRAMMA DI CIFRATURA RC4\n|-1. Codifica una stringa di max %d caratteri\n\n", maxlen);
      printf("Seleziona origine chiave cifratura:\n\n1. Utente\n2. Computer\n\n");
      while(v2[0]!='1' && v2[0]!='2'){
        printf(" > ");
        scanf("%s", v2);
      }
      // Per 1 e 2 chiede sempre la stringa M
      printf("Inserisci stringa da decodificare (M) - max %d caratteri\n\n", maxlen);
      strcpy(msg,"*");
      while((strcmp(msg," ")!=0)) {
        strcpy(msg," ");
        printf(" > ");
        //scanf("%s", m);
        while(getchar()!='\n');
        fgets(m,maxlen+2,stdin);
        // Using fgets instead of scanf allows bypass this test because
        // string is truncated
        //if ((strlen(m)-1)>(maxlen)){
        //  strcpy(msg,"* La stringa è troppo lunga\n");
        //}

        for (int i=0;i<(strlen(m)-1);i++){
          if ((int)m[i]<=31 || (int)m[i]>127) {
            strcpy(msg,"* La stringa contiene caratteri non ammessi\n");
          }
        }
        if ((strcmp(msg," ")!=0)) {
          printf("   %s",msg);
        }
      }

      switch(*v2){
      case '1':
        printf("Inserisci chiave di decodifica (k) - min %d max %d caratteri\n\n", (int)strlen(m)-1,maxlen);
        strcpy(msg,"*");
        while((strcmp(msg," ")!=0)) {
          strcpy(msg," ");
          printf(" > ");
          scanf("%s", k);
          if (strlen(k)>maxlen){
            strcpy(msg,"* La chiave è troppo lunga\n");
          }
          if (strlen(k)<(strlen(m)-1)){
            strcpy(msg,"* La chiave è troppo corta\n");
          }
          for (int i=0;i<(strlen(k)-1);i++){
            if ((int)k[i]<=31 || (int)k[i]>127) {
              strcpy(msg,"* La chiave contiene caratteri non ammessi\n");
            }
          }
          if ((strcmp(msg," ")!=0)) {
            printf("   %s",msg);
          }
        }
        lk = (int)strlen(k);
        break;
      // Generate random key k
      case '2':
        strcpy(k,"");
        for (int i=0;i<strlen(m);i++){
          k[i] = rand() % 128;
        }
        lk = (int)strlen(m)-1;
        break;
      }

      // Generate xor values
      strcpy(c,"");
      strcpy(h,"");
      for (int i=0;i<strlen(m);i++){
        c[i] = m[i] ^ k[i];
      }

      for (int i=0;i<strlen(m);i++){
        h[i] = (int)k[i] ^ (int)c[i];
      }

      // Print all output data: C, k, h, m
      printf("\n");
      printf("        +------------------+-------------------------------------------------+\n");
      printf("        | Stringa          |                                                 |\n");
      printf("        | Criptata *     C | ASCII in hex                                    |\n");
      printf("--------+------------------+-------------------------------------------------+\n");
      formatta(c, strlen(m)-1);
      printf("--------+------------------+-------------------------------------------------+\n");
      printf("\n");

      printf("        +------------------+-------------------------------------------------+\n");
      printf("        | Chiave           |                                                 |\n");
      if (v2[0]=='1'){
        printf("        | Utente         k | ASCII in hex                                    |\n");
      } else {
        printf("        | Computer *     k | ASCII in hex                                    |\n");
      }
      printf("--------+------------------+-------------------------------------------------+\n");
      formatta(k, lk);
      printf("--------+------------------+-------------------------------------------------+\n");
      printf("\n");

      printf("        +------------------+-------------------------------------------------+\n");
      printf("        | Stringa          |                                                 |\n");
      printf("        | Controllo      h | ASCII in hex                                    |\n");
      printf("--------+------------------+-------------------------------------------------+\n");
      formatta(h, strlen(m)-1);
      printf("--------+------------------+-------------------------------------------------+\n");
      printf("\n");

      printf("        +------------------+-------------------------------------------------+\n");
      printf("        | Stringa          |                                                 |\n");
      printf("        | Inserita       M | ASCII in hex                                    |\n");
      printf("--------+------------------+-------------------------------------------------+\n");
      formatta(m, strlen(m)-1);
      printf("--------+------------------+-------------------------------------------------+\n");
      printf("\n");
      printf("* I caratteri non stampabili sono sostituiti da .\n");

      printf("Uscire s/S?\n");
      scanf("%s", t1);
      strcpy(v1," ");
      strcpy(v2," ");
      if (t1[0]=='s' || t1[0]=='S'){endp=true;}
      break;
    // Show Page for max length change
    case '2':
      system("clear");
      printf("PROGRAMMA DI CIFRATURA RC4\n|-2. Cambia lunghezza max\n\nInserisci lunghezza max da 1 a 128 - attuale %d\n\n", maxlen);

      strcpy(msg,"*");
      while((strcmp(msg," ")!=0)) {
        strcpy(msg," ");
        strcpy(l1,"");
        printf(" > ");
        scanf("%s", l1);
        if (strlen(l1)>3){
          strcpy(msg,"* Valore troppo lungo\n");
        }
        if ((strcmp(msg," ")==0)) {
          for (int i=0;i<(strlen(l1));i++){
            if (isdigit(l1[i]) == 0) {
              strcpy(msg,"* Valore non numerico\n");
            }
          }
        }
        if ((strcmp(msg," ")==0)) {
          if (atoi(l1)<1 || atoi(l1)>128){
              strcpy(msg,"* Valore non ammesso\n");
          }
        }
        if ((strcmp(msg," ")!=0)) {
          printf("   %s",msg);
        }

      }
      maxlen = atoi(l1);
      strcpy(v1," ");
      endp=false;
      break;
    // Exit from program
    case '9':
      printf("\nPROGRAMMA TERMINATO\n");
      endp = true;
      break;

    }
  }
  return 0;
}
// Function for outpunt formatting in hexadecimal dump style
int formatta(char * ustr, int l){
  int i1, i2, x, y, righe, resto;

  righe = l / 16;
  resto = l % 16;
  if (resto>0) righe++;
  i1 = 0;
  i2 = 0;
  for (x=0;x<righe;x++){
    int a = x*16;
    int b = a+15;
    if (x == (righe -1) && resto>0){b = a+resto-1;}

    if(a<10) {printf("00%d:",a);} else {if(a<100) {printf("0%d:",a);} else {printf("%d:",a);}}
    if(b<10) {printf("00%d",b);} else {if(b<100) {printf("0%d",b);} else {printf("%d",b);}}

//printf("%d:",a);
    printf(" | ");
    for(y=0;y<16;y++)
    {
      if (i1<l){
        if ((int)ustr[i1]<=31 || (int)ustr[i1]>126) {
          printf(".");
        } else {
          printf("%c",ustr[i1]);
        }
      } else {
        printf(" ");
      }
      i1++;
    }
    printf(" | ");
    for(y=0;y<16;y++)
    {
      if (i2<l){
        if ((int)ustr[i2]>=0 && (int)ustr[i2]<=15)
        {
           printf("0%X ",ustr[i2]);
        } else {
          printf("%X ",ustr[i2]);
        }
      } else {
        printf("   ");
      }
      i2++;
    }

    printf("|\n");

  }
  return 0;
}
