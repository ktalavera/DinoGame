#include <pthread.h>
#include <stdio.h>
#include <conio.h>
//#include <curses.h>   //equivalente a conio en linux
//#include <ncurses.h>    // incluye stdio.h
#include <stdlib.h>
#include <unistd.h>
#include "gotoxy.h"

pthread_mutex_t count_mutex     = PTHREAD_MUTEX_INITIALIZER;


void *Header(void *arg){
    pthread_mutex_lock( &count_mutex );
    system("color F2");
    system("mode con: lines=29 cols=90");
    gotoxy(11,1);
    printf("+-----------------------------------------+");
    gotoxy(12,2);
    printf("Precione X para salir. Saltar con espacio");
    gotoxy(11,3);
    printf("+-----------------------------------------+");
    gotoxy(64,1);
    printf("+----------+");
    gotoxy(65,2);
    printf("Puntaje: ");
    gotoxy(64,3);
    printf("+----------+");
    gotoxy(11,2);
    printf("|");
    gotoxy(53,2);
    printf("|");
    gotoxy(75,2);
    printf("|");
    gotoxy(64,2);
    printf("|");
    gotoxy(1,25);
    for(int x=0;x<79;x++)
    printf(" ");

    pthread_mutex_unlock( &count_mutex );
}
//Dinosaurio
int PosENY;
void dino(int jump=0){

    static int a=1;
    if(jump==0)         //si se recibe 0, dino se queda en su lugar
        PosENY=0;
    else if(jump==2){
        PosENY--;       //si se recibe 2 sube (- + - = +)
    }else{
        PosENY++;       //baja el dino (+ - + = -)
    }
    //imprimir dino dependiendo de poseny
    gotoxy(2,15-PosENY);
    printf("                 ");
    gotoxy(2,16-PosENY);
    printf("         млпллллм");
    gotoxy(2,17-PosENY);
    printf("         лллллллл");
    gotoxy(2,18-PosENY);
    printf("         лллллппп");
    gotoxy(2,19-PosENY);
    printf(" л      мллллппп ");
    gotoxy(2,20-PosENY);
    printf(" ллм  мллллллммм ");
    gotoxy(2,21-PosENY);
    printf(" пллллллллллл  п ");
    gotoxy(2,22-PosENY);
    printf("   плллллллп     ");
    gotoxy(2,23-PosENY);
    if(jump==1 || jump==2){
    printf("    ллп пл       ");
    gotoxy(2,24-PosENY);
    printf("    лм   лм      ");
    }
    //mover las piernas
    else if(a==1)    {
    printf("    пллп  ппп    ");
    gotoxy(2,24-PosENY);
    printf("      лм         ");
    a=2;
    }
    else if(a==2){
    printf("     плм пл      ");
    gotoxy(2,24-PosENY);
    printf("          лм     ");
    a=1;
    }
    gotoxy(2,25-PosENY);
    if(jump!=0){
        printf("                ");
    }
    Sleep(40);
    //delay(speed);
}
//Obstaculo: dibujo de obs
void obs(){

    static int PosEnX=0,scr=0;
    if(PosEnX==56 && PosENY<4){                  //si llega a la posición
    scr=0;                                      //score en 0
    gotoxy(36,8);
    printf("\033[1;31mGame Over\033[0m\n");     //muestra mensaje
    getch();
    gotoxy(36,8);
    printf("         ");
    }
    //imprimir cactus moviendose de derecha a izquierda
    gotoxy(74-PosEnX,20);
    printf("л    л ");
    gotoxy(74-PosEnX,21);
    printf("л    л ");
    gotoxy(74-PosEnX,22);
    printf("лммммл ");
    gotoxy(74-PosEnX,23);
    printf("  л    ");
    gotoxy(74-PosEnX,24);
    printf("  л  " );
    PosEnX++;

    if(PosEnX==73){
    PosEnX=0;
    scr++;                  //sumas la puntuacion
    gotoxy(73,2);
    printf("  ");
    gotoxy(73,2);
    printf("%d",scr);
    }
}

void * bg(){

    //crea nube y se mueve de derecha a izquierda
    static int PosNUBE=0;
     gotoxy(65-PosNUBE,5);
    printf("  **** ");
    gotoxy(64-PosNUBE,6);
    printf("  * ");
    gotoxy(69-PosNUBE,6);
    printf("  * ");
    gotoxy(65-PosNUBE,7);
    printf("  **** ");

    //Borra nube vieja de la consola
     gotoxy(15-PosNUBE,5);
    printf("     ");
    gotoxy(15-PosNUBE,6);
    printf("     ");
    gotoxy(15-PosNUBE,7);
    printf("     ");
    gotoxy(15-PosNUBE,8);
    printf("      ");
    gotoxy(15-PosNUBE,9);
    printf("    ");
    gotoxy(10-PosNUBE,10);
    printf("    ");
      PosNUBE++;
    if(PosNUBE==63){   //Si nuebe esta en esta posicion que mueva
    PosNUBE=1;
    if(speed>40)
        speed++;
    }

}
void * juego (void *arg){
pthread_mutex_lock( &count_mutex );
 char capturar;
    int i;

    while(true){
        while(!kbhit()){            //si hay algun input
            dino();
            obs();
        }
      pthread_mutex_unlock( &count_mutex );
        capturar=getch();           //capturar input
        if(capturar==' '){
            for(i=0;i<10;i++){
            dino(1);
            obs();
            bg();
            }
            for(i=0;i<10;i++){
            dino(2);
            obs();
            bg();
            }
        }
        else if (capturar=='x')
            return(0);
    }
    pthread_mutex_unlock( &count_mutex );
}

int main(){

    pthread_t thread_header, thread_juego,thread_bg;

        pthread_create(&thread_header, NULL, &Header, NULL);
         pthread_create(&thread_juego, NULL, &juego, NULL);
         pthread_create(&thread_bg, NULL, &bg, NULL);


        pthread_join( thread_header, NULL);
        pthread_join( thread_juego, NULL);
        pthread_join( thread_bg, NULL);

    pthread_exit(NULL);
}
