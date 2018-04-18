/*
Pr ctica No. 6 - Recursividad
Implemente un algoritmo recursivo para determinar las minas adyacentes en una matriz en la que previamente se han insertado 20 minas en forma Aleatoria
-No se aceptaran algoritmos implementados con Ciclos
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
void marco(){
 int i = 0;
 textcolor(WHITE);
 for(i=1;i<80;i++){
	gotoxy(i,3);cprintf("-");
	gotoxy(i,20);cprintf("-");
 }
}
void marco2(){
 int i = 0,j = 0;
 textcolor(GREEN);
 for(i=0;i<11;i++)
	for(j=15;j<66;j++){
		gotoxy(j,4+2*i);cprintf("Ü");
	}
 for(i=1;i<12;i++)
	for(j=5;j<25;j++){
		gotoxy(5*i+10,j);cprintf("Û");
	}
}
int recorrer_Matriz(int matriz[][10],int i,int j,int id){
 int conteo = 0;
 if(i<10){
	if(j<10){
		if(id == 1)
			if(matriz[i][j] == -1)
				matriz[i][j] = 0;
		if(id == 2)
			if(matriz[i][j] == 1){
				gotoxy(5*j+17,5+2*i);cprintf("x");
			}
		if(id == 3){
			if(matriz[i][j] == 0){
				if((j+1) < 10)
					conteo = conteo + matriz[i][j+1];
				if((i+1)<10 && (j+1)<10)
					conteo = conteo + matriz[i+1][j+1];
				if((i+1) < 10)
					conteo = conteo + matriz[i+1][j];
				if((i+1)<10 && (j-1)>=0)
					conteo = conteo + matriz[i+1][j-1];
				if((j-1) >= 0)
					conteo = conteo + matriz[i][j-1];
				if((i-1)>=0 && (j-1)>=0)
					conteo = conteo + matriz[i-1][j-1];
				if((i-1) >= 0)
					conteo = conteo + matriz[i-1][j];
				if((i-1)>=0 && (j+1)<10)
					conteo = conteo + matriz[i-1][j+1];
				textcolor(WHITE);
				if(conteo != 0){
					gotoxy(5*j+17,5+2*i);cprintf("%d",conteo);
				}
			} // if(matriz[i][j] == 0)
			else{
				textcolor(RED);
				gotoxy(5*j+17,5+2*i);cprintf("x");
			}
		} // if(id == 3)
	} // if(j<10)
	else{
		j = -1;
		i++;
	}
	return recorrer_Matriz(matriz,i,j+1,id);
 } // if(i<10)
 else
	return 0;
}
void asignar_Minas(int matriz[][10]){
 int numeroMinas = 0, i = 0, j = 0;
 while(numeroMinas < 20){
	i = rand()%10;
	j = rand()%10;
	if(matriz[i][j]==-1){
		matriz[i][j] = 1;
		numeroMinas++;
	}
 }
 recorrer_Matriz(matriz,0,0,1);
}
void Generar_Matriz(int matriz[][10]){
 int i = 0, j = 0;
 randomize();
 for(i=0;i<10;i++)
	for(j=0;j<10;j++)
		matriz[i][j] = -1;
 asignar_Minas(matriz);
 clrscr();
 textcolor(RED);
 gotoxy(3,5);cprintf("Acci¢n Realizada:");
 textcolor(WHITE);
 marco();
 gotoxy(20,2);cprintf("G E N E R A R     N U E V A     M A T R I Z");
 gotoxy(22,5);cprintf("Se ha generado Nueva Matriz.");
 getch();
}
void Muestreo_de_Matriz(int matriz[][10]){
 int i = 0;
 clrscr();
 textcolor(WHITE);
 gotoxy(22,2);cprintf("M U E S T R E O     D E     M I N A S");
 if(matriz[0][0] == -1){
	marco();
	textcolor(RED);
	gotoxy(3,5);cprintf("Operaci¢n Imposible:");
	textcolor(WHITE);
	gotoxy(24,5);cprintf("A£n no se ha Generado una Nueva Matriz");
 }
 else{
	for(i=1;i<80;i++){
		gotoxy(i,3);cprintf("-");
	}
	marco2();
	textcolor(WHITE);
	recorrer_Matriz(matriz,0,0,2);
 } // else de if(matriz[i][j] == -1)
 getch();
}
void Conteo_de_Matriz(int matriz[][10]){
 int i = 0;
 clrscr();
 textcolor(WHITE);
 gotoxy(23,2);cprintf("C O N T E O     D E     M I N A S");
 if(matriz[0][0] == -1){
	marco();
	textcolor(RED);
	gotoxy(3,5);cprintf("Operaci¢n Imposible:");
	textcolor(WHITE);
	gotoxy(24,5);cprintf("A£n no se ha Generado una Nueva Matriz");
 }
 else{
	for(i=1;i<80;i++){
		gotoxy(i,3);cprintf("-");
	}
	marco2();
	textcolor(WHITE);
	recorrer_Matriz(matriz,0,0,3);
 } // else de if(matriz[i][j] == -1)
 getch();
}
void menu(){
 int matriz[10][10] = {-1};
 int salida = 0, flechas = 0;
 char tecla;
 do{
	clrscr();
	marco();
	textcolor(GREEN);
	gotoxy(24,10);cprintf("Elija Operaci¢n:");
	gotoxy(21,17);cprintf("Presione ESC para poder salir del programa");
	textcolor(WHITE);
	gotoxy(28,2);cprintf("R E C U R S I V I D A D");
	gotoxy(23,11);cprintf("       1.- Generar la Matriz");
	gotoxy(23,12);cprintf("       2.- Muestreo de Minas");
	gotoxy(23,13);cprintf("       3.- Conteo de Minas");
	tecla = getch();
	if(tecla == '\x0')
		flechas = 1;
	else{
		if(flechas == 0){
			switch(tecla){
				case '1':
					Generar_Matriz(matriz);
					salida = 0;break;
				case '2':
					Muestreo_de_Matriz(matriz);
					salida = 0;break;
				case '3':
					Conteo_de_Matriz(matriz);
					salida = 0;break;
				case '\x1B':
					salida = 1;break;
			}
		}
		flechas = 0;
	}
 }while(salida == 0);
 fflush(stdin);
}
void main(){
 menu();
}