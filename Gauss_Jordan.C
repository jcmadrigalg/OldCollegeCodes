#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
void marco2(){
 int i = 0;
 textcolor(WHITE);
 for(i=1;i<80;i++){
	gotoxy(i,3);cprintf("-");
	gotoxy(i,20);cprintf("-");
 }
 gotoxy(13,2);cprintf("E L I M I N A C I à N     D E     G A U S S - J O R D A N");
}
void marco(int limX,int limY){
 int i = 0, j = 0;
 char *literales = "abcde";
 char *igualdad = "Igualdad";
 marco2();

 textcolor(RED);
 for(i=0;i<limX;i++)
	for(j=0;j<1;j++){
		gotoxy(j+5,6+2*i);cprintf("R%d",i+1);
	}
 for(j=0;j<limY;j++){
	if(j == 0){
		gotoxy(15,4);cprintf("%c",literales[j]);
	}
	else{
		if((j+1) < limY){
			gotoxy(10*(j+1)+5,4);cprintf("%c",literales[j]);
		}
		else{
			gotoxy(10*(j+1)+1,4);cprintf("%s",igualdad);
		}
	}
 }
 textcolor(GREEN);
 for(i=0;i<6;i++)
	for(j=10;j<71;j++){
		gotoxy(j,5+2*i);cprintf("Ü");
	}
 for(i=1;i<8;i++)
	for(j=6;j<16;j++){
		gotoxy(10*i,j);cprintf("Û");
 }
 textcolor(WHITE);
}
int verificarMatriz(float matriz[][6],int limX,int limY){
 int i=0,j=0,contadorCeros = 0, valida = 1,Ecuaciones = 0;
 int validaTemp = 0;
 float numero[6] = {0};
 for(i=0;i<limX;i++){
	contadorCeros = 0;
	for(j=0;j<limY-1;j++){
		if(i == 0){
			numero[j] = matriz[i][j];
			if(matriz[i][j] == 0 || matriz[i][j]==(-0.00))
				contadorCeros++;
		}
		else{
			if(matriz[i][j] == 0 || matriz[i][j]==(-0.00))
				contadorCeros++;
			if(numero[j] == matriz[i][j] && validaTemp==0)
				validaTemp = 0;
			else
				validaTemp = 1;
		}
	}
	if(validaTemp == 0){
		Ecuaciones = 2;
		valida = 0;
	}
	else{
		Ecuaciones = 0;
		valida = 1;
	}
	if(contadorCeros==limY){
		Ecuaciones = 2;
		valida = 0;
	}
	else{
		if(valida == 1){
			if(Ecuaciones == 0)
				valida = 1;
			if(Ecuaciones == 2)
				valida = 0;
		}
		else
			valida = 0;
	}
 }
 return valida;
}
int verificarMatriz2(float matriz[][6],int limX,int limY){
 int i = 0, j = 0, sirve = 0, verificado = 1;
// if(matriz[0][0] == 0){
	sirve = 0;
	for(i=0;i<limX;i++)
		for(j=i;j<limY-1;j++)
			if(matriz[i][j] == 0)
				sirve++;
	if(sirve == limX)
		verificado = 0;
	else{
		for(i=0;i<limX;i++)
			for(j=0;j<limY;j++){
				matriz[i][j] = matriz[i][j]*(-1);
			}
		verificado = 1;
	}
/* }
 else{
	sirve = 0;
	for(i=0;i<limX;i++)
		if(matriz[i][0] == 0)
			sirve = limX;
	if(sirve == limX)
		verificado = 0;
	else{
		for(i=0;i<limX;i++)
			for(j=0;j<limY;j++){
				matriz[i][j] = matriz[i][j]*(-1);
			}
		verificado = 1;
	}
 }*/
 return verificado;
}
float mayor(float matriz[][6],int limX,int limY,int limite){
 int i = 0,j = 0;
 float temp[6];
 float mayor1 = 0, fila = 0, lim = limite;
 for(i=limite;i<limX;i++)
	for(j=limite;j<(limite+1);j++){
		if(i == limite){
			mayor1 = matriz[i][j];
			fila = i;
		}
		else
			if(matriz[i][j] > mayor1){
				mayor1 = matriz[i][j];
				fila = i;
			}
	}
 if(fila != 0){
	for(i=0;i<limY;i++)
		temp[i] = matriz[fila][i];
	for(i=0;i<limY;i++)
		matriz[fila][i] = matriz[lim][i];
	for(i=0;i<limY;i++){
		matriz[lim][i] = temp[i];
		fila = lim;
	}
 }
 return fila;
}
void cerosMatriz(float matriz[][6],int limX,int limY, int *ceros){
 int i = 0, j = 0;
 (*ceros) = 1;
 for(i=0;i<limX;i++)
	for(j=0;j<limY-1;j++)
		if(i != j){
			if(matriz[i][j] == 0 && (*ceros)==1)
				(*ceros) = 1;
			if(matriz[i][j] != 0)
				(*ceros) = 0;
		}
}
void Jordan(float matriz[][6],int limX,int limY){
 int i = 0,j = 0, ceros = 0, modificar = 0, limite = 0, k = 0, contador = 0;
 int pivote = 0, conteoX = 0, conteoY = 0;
 char tecla;
 float numerador = 0, denominador = 0, fila = 0;
 do{
	fila = mayor(matriz,limX,limY,limite);
	limite++;
	denominador = matriz[pivote][pivote];
	for(i=0;i<limX;i++){
		for(j=pivote;j<(pivote+1);j++){
			if(i != j){
				if(matriz[i][j] == 0)
					modificar = 0;
				else
					modificar = 1;
			}
			else
				modificar = 0;
			if(i==j){
				denominador = matriz[pivote][pivote];
				modificar = 0;
			}
			if(modificar == 1){
				if(numerador == 0){
					numerador = matriz[i][j];
				for(k=0;k<limY;k++)
					matriz[i][k] = matriz[fila][k]*(-1)*(numerador/denominador) + matriz[i][k];
				}
			}
		}
		numerador = 0;
	}
	if(pivote < limY)
		pivote++;
	clrscr();
	marco(limX,limY);
	for(i=5;i<limX+5;i++)
		for(j=1;j<limY+1;j++){
			gotoxy(j*10+2,i*2-4);cprintf("%.2f",matriz[i-5][j-1]);
		}
	contador++;
	cerosMatriz(matriz,limX,limY,&ceros);
 }while((contador+1)<limY);
 if(ceros == 0){
	fflush(stdin);
	clrscr();
	marco2();
	textcolor(RED);
	gotoxy(3,5);cprintf("ERROR:");
	textcolor(WHITE);
	gotoxy(12,5);cprintf("Matriz sin soluci¢n.");
	getch();
 }
 else{
	for(i=0;i<limX;i++)
		for(j=0;j<limY-1;j++)
			if(i == j){
				denominador = matriz[i][j];
				for(k=j;k<limY;k++)
					matriz[i][k] = matriz[i][k]/denominador;
			}
	clrscr();
	for(i=0;i<limX;i++)
		for(j=0;j<limY;j++){
			if(matriz[i][j] == (-0.00))
				matriz[i][j] = 0.00;
			else{
				if(j != limY-1)
					if(matriz[i][j] != 1)
						matriz[i][j] = 0.00;
			}
		}
	marco(limX,limY);
	for(i=5;i<limX+5;i++)
		for(j=1;j<limY+1;j++){
			if(conteoX == conteoY){
				textcolor(WHITE);
				gotoxy(j*10+2,i*2-4);cprintf("%.2f",matriz[i-5][j-1]);
			}
			else{
				if((j+1) == (limY+1)){
					textcolor(WHITE);
					gotoxy(j*10+2,i*2-4);cprintf("%.2f",matriz[i-5][j-1]);
				}
				else{
					textcolor(LIGHTGRAY);
					gotoxy(j*10+2,i*2-4);cprintf("%.2f",matriz[i-5][j-1]);
				}
			}
			if(conteoX < limX)
				conteoX++;
			else{
				conteoX = 0;
				if(conteoY < limY)
					conteoY++;
			}
		}
	getch();
  } // else de if(ceros == 0)
}
void Captura(float matriz[][6],int limX,int limY){
 int i = 0, j = 0, minus = 0, point = 0, numero = 0, verificar=1, verificar2 = 1;
 int conteoX = 0, conteoY = 0, posicion = 0, Flechas = 0, salida_Matriz = 1;
 char cadena[6] = {'\x0'};
 char tecla;
 for(i=0;i<limX;i++)
	for(j=0;j<limY;j++)
		matriz[i][j] = 0.00;
 posicion = strlen(cadena);
 clrscr();
 textcolor(WHITE);
 do{
	minus = point = posicion = numero = 0;
	for(i=0;i<6;i++)
		cadena[i] = '\x0';
	do{
		marco(limX,limY);
		textcolor(RED);
		gotoxy(3,18);cprintf("Nota:");
		textcolor(WHITE);
		gotoxy(9,18);cprintf("Presione ESC para salir de la Captura de la Matriz");
		textcolor(BLACK);
		gotoxy((conteoX+1)*10+2,(conteoY+1)*2+4);cprintf("      ",cadena);
		textcolor(WHITE);
		gotoxy((conteoX+1)*10+2,(conteoY+1)*2+4);cprintf("%s",cadena);
		tecla = getch();
		if(tecla == '\x0')
			Flechas = 1;
		else
		if(Flechas == 0 && posicion<6){
			if(tecla == '-' && minus==0){
				minus = 1;
				posicion = strlen(cadena);
				cadena[posicion] = tecla;
				cadena[posicion+1] = '\x0';
			}
			if(tecla == '.' && point==0){
				minus = point = 1;
				posicion = strlen(cadena);
				cadena[posicion] = tecla;
				cadena[posicion+1] = '\x0';
			}
			if(isdigit(tecla) && numero<5){
				minus = 1;
				numero++;
				posicion = strlen(cadena);
				cadena[posicion] = tecla;
				cadena[posicion+1] = '\x0';
			}
			if(tecla == '\x8' && posicion>-1){
				posicion = strlen(cadena);
				if(cadena[posicion-1] == '.')
					point = 0;
				if(isdigit(cadena[posicion-1]))
					numero--;
				cadena[posicion-1] = '\x0';
				textcolor(BLACK);
				gotoxy((conteoX+1)*10+2,(conteoY+1)*2+4);cprintf("%s",cadena);
				textcolor(WHITE);
				posicion = strlen(cadena);
				if(posicion == 0)
					minus = 0;
			}
			if(tecla == '\x1B'){
				salida_Matriz = 0;
				if(strlen(cadena) == 0){
					posicion = strlen(cadena);
					cadena[posicion] = '1';
					cadena[posicion+1] = '\x0';
				}
				tecla = '\xD';
			}
		} // if Flechas == 0
		Flechas = 0;
	}while(tecla!='\xD' || strlen(cadena)==0);
	if(salida_Matriz == 1){
		posicion = strlen(cadena);
		if(strlen(cadena) == 1)
			if(cadena[posicion-1] == '-'){
				cadena[posicion] = '1';
				cadena[posicion+1] = '\x0';
			}
		matriz[conteoY][conteoX] = atof(cadena);
		if(conteoX < limX)
			conteoX++;
		else{
			conteoX = 0;
			if(conteoY < limY)
				conteoY++;
		}
	} // if(salida_Matriz == 1)
	else{
		conteoX = limY;
		conteoY = limX;
	}
 }while(conteoX<limY && conteoY<limX);
 if(salida_Matriz == 1){
	for(i=5;i<limX+5;i++)
		for(j=1;j<limY+1;j++){
			gotoxy(j*10+2,i*2-4);cprintf("%.2f",matriz[i-5][j-1]);
		}
	verificar = verificarMatriz(matriz,limX,limY);
	if(verificar == 1){
		verificar2 = verificarMatriz2(matriz,limX,limY);
		if(verificar2 == 1)
			Jordan(matriz,limX,limY);
		else{
			clrscr();
			marco2();
			textcolor(RED);
			gotoxy(3,5);cprintf("ERROR:");
			textcolor(WHITE);
			gotoxy(10,5);cprintf("Matriz sin soluci¢n.");
			getch();
		}
	}
	else{
		clrscr();
		marco2();
		gotoxy(3,5);cprintf("       Ecuaciones Iguales ¢ con Ceros solamente en Filas o Columnas.");textcolor(RED);
		gotoxy(3,5);cprintf("ERROR:");textcolor(WHITE);
		gotoxy(3,6);cprintf("       Matriz sin soluci¢n.");
		getch();
	 } // else de if(verificar == 1)
 } // if(salida_Matriz == 1)
}
void menu(){
 float matriz[5][6] = {0.00};
 int limX = 0, limY = 0, salida = 0;
 char tecla;
 do{
	clrscr();
	marco2();
	textcolor(GREEN);
	gotoxy(24,10);cprintf("Elegir Tama¤o de la Matriz Aumentada");
	textcolor(WHITE);
	gotoxy(23,11);cprintf("       1.- 2 Inc¢gnitas (2 x 3)");
	gotoxy(23,12);cprintf("       2.- 3 Inc¢gnitas (3 x 4)");
	gotoxy(23,13);cprintf("       3.- 4 Inc¢gnitas (4 x 5)");
	gotoxy(23,14);cprintf("       4.- 5 Inc¢gnitas (5 x 6)");
	textcolor(GREEN);
	gotoxy(21,17);cprintf("Presione ESC para poder salir del programa");
	tecla = getch();
	switch(tecla){
		case '1':
			limX = 2; limY = 3;
			Captura(matriz,limX,limY);
			salida = 0;break;
		case '2':
			limX = 3; limY = 4;
			Captura(matriz,limX,limY);
			salida = 0;break;
		case '3':
			limX = 4; limY = 5;
			Captura(matriz,limX,limY);
			salida = 0;break;
		case '4':
			limX = 5; limY = 6;
			Captura(matriz,limX,limY);
			salida = 0;break;
		case '\x1B':
			salida = 1;break;
		default:
			salida = 0;break;
	}
 }while(salida == 0);
}
void main(){
 menu();
}