/*
Programa Final - Snake
Autor: Juan Carlos Madrigal Gonz lez	002/57303
Descripci¢n:
	El programa es el juego cl sico para los celulares, en donde una
	cola de cuadros se va moviendo conforme lo ordena el jugador y
	cuando encuentra u cuadro, la cola crece.
	Cuando la cola choca con la pared o consigo mismo acaba el juego.
*/
#include <dos.h>
#include <stdio.h>
#include <conio.h>
#include <alloc.h>
#include <stdlib.h>
struct nodo{
 int posx;
 int posy;
 struct nodo * siguiente;
};
void marco(){
 int i = 0;
 textcolor(12); // LIGHTRED
 gotoxy(35,2);cprintf("S N A K E");
 textcolor(WHITE);
 for(i=1;i<80;i++){
	gotoxy(i,3);cprintf("-");
	gotoxy(i,20);cprintf("-");
 }
}
struct nodo* nuevoNodo(int x, int y){
 struct nodo * nodo;
 nodo = (struct nodo*) malloc(sizeof (struct nodo) );
 nodo->posx = x;
 nodo->posy = y;
 nodo->siguiente = NULL;
 return nodo;
}
void insertarNodo(struct nodo *nodoInicio, int x, int y){
 struct nodo *p, *nuevo, *q;
 nuevo = nuevoNodo(x,y);
 p = nodoInicio;
 while(p != NULL){
	q = p;
	p = p->siguiente;
 }
 q->siguiente = nuevo;
}
void pintar(struct nodo* inicio, int x, int y){
// ALT + 223 = ß
// ALT + 220 = Ü
// ALT + 254 = þ
 struct nodo *aux;
 clrscr();
 marco();
 aux = inicio;
 textcolor(10);
 gotoxy(aux->posx,aux->posy);cprintf("þ");
 textcolor(WHITE);
 aux = aux->siguiente;
 do{
	gotoxy(aux->posx,aux->posy);cprintf("þ");
	textcolor(CYAN);
	gotoxy(x,y);cprintf("þ");
	textcolor(GREEN);
	gotoxy(1,21);cprintf("ESC:");
	gotoxy(15,21);cprintf("PAUSE:");
	textcolor(WHITE);
	gotoxy(6,21);cprintf("Exit");
	gotoxy(22,21);cprintf("Space Bar");
	gotoxy(79,23);
	aux = aux->siguiente;
 }while(aux);
}
void modificar(struct nodo *inicio, int right, int left, int up, int down){
 int x = 0, y = 0;
 int xAnterior = 0, yAnterior = 0;
 struct nodo *nodo = NULL;
 nodo = inicio;
 x = xAnterior = nodo->posx;
 y = yAnterior = nodo->posy;
 if(right == 1)
	x++;
 if(left == 1)
	x--;
 if(up == 1)
	y--;
 if(down == 1)
	y++;
 nodo->posx = x;
 nodo->posy = y;
 nodo = nodo->siguiente;
 x = nodo->posx;
 y = nodo->posy;
 while(nodo != NULL){
	nodo->posx = xAnterior;
	nodo->posy = yAnterior;
	xAnterior = x;
	yAnterior = y;
	nodo = nodo->siguiente;
	if(nodo != NULL){
		x = nodo->posx;
		y = nodo->posy;
	}
 }
}
void nuevoPuntoAleatorio(struct nodo *inicio, int *x, int *y){
 int salida = 0, entrada = 1;
 struct nodo *p = NULL;
 randomize();
 do{
	p = inicio;
	entrada = 1;
	(*x) = rand()%61;
	(*y) = rand()%11;
	(*x) = (*x) + 5;
	(*y) = (*y) + 5;
	while(p != NULL){
		if((*x)!=p->posx && (*y)!=p->posy && entrada==1)
			salida = 1;
		else{
			salida = 0;
			entrada = 0;
		}
		p = p->siguiente;
	}
 }while(salida == 0);
}
void insertarComida(struct nodo *nodoInicio){
 struct nodo *p, *nuevo, *q;
 int x = 0, y = 0;
 nuevo = nuevoNodo(0,0);
 p = nodoInicio;
 while(p != NULL){
	q = p;
	x = q->posx;
	y = q->posy;
	p = p->siguiente;
 }
 q->siguiente = nuevo;
 nuevo->posx = x-1;
 nuevo->posy = y;
}
int verificarLimites(struct nodo *inicio){
 int lose = 0;
 struct nodo *nodo = NULL;
 nodo = inicio;
 if((nodo->posx)>=1 && (nodo->posx)<=79)
	lose = 0;
 else
	lose = 1;
 if(lose == 0){
	if((nodo->posy)>=4 && (nodo->posy)<=19)
		lose = 0;
	else
		lose = 1;
 }
 if(lose == 0){
	nodo = nodo->siguiente;
	while(nodo != NULL){
		if(inicio->posx==nodo->posx && inicio->posy==nodo->posy){
			lose = 1;
		}
		else
			if(lose == 0)
				lose = 0;
		nodo = nodo->siguiente;
	}
 }
 return lose;
}
void freeMemory(struct nodo *inicio){
 struct nodo *p = inicio, *q = NULL;
 while(inicio != NULL){
	p = inicio;
	while(p->posx!=inicio->posx && p!=NULL){
		q = p;
		p = p->siguiente;
	}
	if(q == NULL){
		inicio = p->siguiente;
		free(p);
	}
 }
}
void Snake(struct nodo *nodoInicio, int nivel){
 int x = 0, y = 0, nuevo = 1, loser = 0;
 int derecha = 1, izquierda = 0, arriba = 0, abajo = 0;
 int time = 100 - nivel;
 struct nodo *nodo;
 char tecla;
 char teclaPause;
 nodo = nodoInicio;
 do{
	do{
		pintar(nodo,x,y);
		delay(time);
		modificar(nodoInicio,derecha,izquierda,arriba,abajo);
		loser = verificarLimites(nodoInicio);
		if(nuevo == 1){
			nuevoPuntoAleatorio(nodoInicio,&x,&y);
			nuevo = 0;
		}
		if((nodoInicio->posx)==x && (nodo->posy)==y){
			insertarComida(nodoInicio);
			nuevo = 1;
			if(time > 20)
				time--;
		}
	}while(!kbhit() && loser==0);
	if(loser == 0){
	tecla = getch();
	switch(tecla){
		case '\x0':
			tecla = getch();
			switch(tecla){
				case '\x4B': // Izquierda
					if(derecha == 0){
						izquierda = 1;
						arriba = abajo = 0;
					}
					break;
				case '\x4D': // Derecha
					if(izquierda == 0){
						derecha = 1;
						arriba = abajo = 0;
					}
					break;
				case '\x48': // Arriba
					if(abajo == 0){
						arriba = 1;
						derecha = izquierda = 0;
					}
					break;
				case '\x50': // Abajo
					if(arriba == 0){
						abajo = 1;
						derecha = izquierda = 0;
					}
					break;
			} // switch(tecla) secundario
			break;
		case '\x1B':
			loser = 1;
			break;
		case ' ':
			do{
				teclaPause = getch();
			}while(teclaPause != ' ');
	} //switch(tecla) principal
	} // if(loser == 0)
 }while(loser == 0);
 if(tecla != '\x1B'){
	gotoxy(1,21);cprintf("                               ");
	textcolor(RED);
	gotoxy(33,21);cprintf("Y O U     L O S E");
	textcolor(WHITE);
	getch();
 }
 freeMemory(nodoInicio);
}
void Menu(){
 char tecla;
 int i = 0;
 struct nodo *nodoInicio = NULL;
 do{
	clrscr();
	marco();
	textcolor(GREEN);
	gotoxy(24,10);cprintf("Elegir Nivel de Juego");
	textcolor(WHITE);
	gotoxy(23,11);cprintf("       1.- Principiante");
	gotoxy(23,12);cprintf("       2.- Intermedio");
	gotoxy(23,13);cprintf("       3.- Experto");
	textcolor(GREEN);
	gotoxy(21,17);cprintf("Presione ESC para poder salir del programa");
	tecla = getch();
	switch(tecla){
		case '1':
			nodoInicio = nuevoNodo(5,8);
			for(i=4;i>2;i--)
				insertarNodo(nodoInicio,i,8);
			Snake(nodoInicio,0);
			nodoInicio = NULL;break;
		case '2':
			nodoInicio = nuevoNodo(8,8);
			for(i=7;i>2;i--)
				insertarNodo(nodoInicio,i,8);
			Snake(nodoInicio,30);
			nodoInicio = NULL;break;
		case '3':
			nodoInicio = nuevoNodo(10,8);
			for(i=9;i>2;i--)
				insertarNodo(nodoInicio,i,8);
			Snake(nodoInicio,60);
			nodoInicio = NULL;break;
	}
 }while(tecla != '\x1B');
}
void main(){
 Menu();
}