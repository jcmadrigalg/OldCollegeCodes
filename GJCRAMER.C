#include <stdio.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
void marco2(int id){
 int i = 0;
 textcolor(WHITE);
 for(i=1;i<80;i++){
	gotoxy(i,3);cprintf("-");
	gotoxy(i,20);cprintf("-");
 }
 if(id == 0){
	gotoxy(20,2);cprintf("S O L U C I à N     D E     M A T R I C E S");
 }
 if(id == 1){
	gotoxy(26,2);cprintf("R E G L A     D E     C R A M E R");
 }
 if(id == 2){
	gotoxy(13,2);cprintf("E L I M I N A C I à N     D E     G A U S S - J O R D A N");
 }
}
void marco(int limX,int limY,int id){
 int i = 0, j = 0;
 char *literales = "abcde";
 char *igualdad = "Igualdad";
 marco2(id);
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
//////////////////////////// REGLA DE CRAMER //////////////////////////
float Determinante(float matrizDeterminante[][11],int limX){
 int i = 0,j = 0, n = 0;
 float numero = 1, resultado = 0, numRes = 1, r2 = 0;
 clrscr();
 for(j=0;j<limX;j++){
	n = 0;
	numero = 1;
	i = j;
	while(n<limX){
		if(i == j)
			numRes = matrizDeterminante[n][j];
		else
			numRes = matrizDeterminante[n][i];
		numero = numero*numRes;
		n++;
		i++;
	}
	resultado = resultado + numero;
 }
 for(j=0;j<limX;j++){
	n = limX-1;
	numero = 1;
	i = j;
	while(n>=0){
		if(i == j)
			numRes = matrizDeterminante[n][j];
		else
			numRes = matrizDeterminante[n][i];
		numero = numero*numRes;
		n--;
		i++;
	}
	r2 = r2 - numero;
	resultado = resultado - numero;
 }
 return resultado;
}
void extenderMatriz(float matrizDeterminante[][11],float matriz[][6],int limX){
 int i = 0, j = 0, k = 0;
 for(i=0;i<limX;i++){
	for(j=0;j<limX;j++)
		matrizDeterminante[i][j] = matriz[i][j];
	for(k=0;k<(limX-1);k++)
		matrizDeterminante[i][j+k] = matriz[i][k];
 }
}
float Determinante_2variables(float matriz[][6]){
 float resultado = 0;
 resultado = matriz[0][0]*matriz[1][1] - matriz[1][0]*matriz[0][1];
 return resultado;
}
void Cramer(float matriz[][6],int limX,int limY){
 int i = 0,j = 0, k = 0;
 float matrizDeterminante[5][11] = {0};
 float matrizTemp[5][6] = {0};
 float determinante = 0, determinanteIncognita = 0;
 float valoresResueltos[5] = {0};
 char *literales = "abcde";
 if(limX != 2){
	extenderMatriz(matrizDeterminante,matriz,limX);
	determinante = Determinante(matrizDeterminante,limX);
 }
 else
	determinante = Determinante_2variables(matriz);
 if(determinante != 0){
	for(k=0;k<limX;k++){
		for(i=0;i<limX;i++)
			for(j=0;j<limX;j++){
				if(j == k)
					matrizTemp[i][j] = matriz[i][limY-1];
				else
					matrizTemp[i][j] = matriz[i][j];
			}
		if(limX != 2){
			extenderMatriz(matrizDeterminante,matrizTemp,limX);
			determinanteIncognita = Determinante(matrizDeterminante,limX);
		}
		else
			determinanteIncognita = Determinante_2variables(matrizTemp);
		valoresResueltos[k] = determinanteIncognita/determinante;
	}
	clrscr();
	marco2(1);
	textcolor(GREEN);
	gotoxy(3,5);cprintf("Determinate Principal:");
	textcolor(WHITE);
	gotoxy(26,2);cprintf("R E G L A     D E     C R A M E R");
	gotoxy(26,5);cprintf("%.4f",determinante);
	for(i=0;i<limX;i++){
		gotoxy(5,7+i);cprintf("%c = %.6f",literales[i],valoresResueltos[i]);
	}
	getch();
 }
 else{
	clrscr();
	marco2(1);
	gotoxy(26,2);cprintf("R E G L A     D E     C R A M E R");
	gotoxy(3,5);cprintf("       Determinante Principal provoca Divisi¢n entre Cero.");textcolor(RED);
	gotoxy(3,5);cprintf("ERROR:");textcolor(WHITE);
	gotoxy(3,6);cprintf("       Matriz sin soluci¢n.");
	getch();
 }
}
////////////////////// ELIMINACIàN DE GAUSS - JORDAN //////////////////
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
			if(fabs(matriz[i][j]) > fabs(mayor1)){
				mayor1 = matriz[i][j];
				fila = i;
			}
	}

 if(fila!=0 && mayor1!=0){
	for(i=0;i<limY;i++)
		temp[i] = matriz[fila][i];
	for(i=0;i<limY;i++)
		matriz[fila][i] = matriz[lim][i];
	for(i=0;i<limY;i++){
		matriz[lim][i] = temp[i];
		fila = lim;
	}
 }
 if(mayor1 != 0)
	return fila;
 else
	return (-1);
}
void cerosMatriz(float matriz[][6],int limX,int limY, int *ceros){
 int i = 0, j = 0;
 (*ceros) = 1;
 for(i=0;i<limX;i++)
	for(j=0;j<limY-1;j++)
		if(i != j){
			if(matriz[i][j]==0 && (*ceros)==1)
				(*ceros) = 1;
			if(matriz[i][j] != 0)
				(*ceros) = 0;
		}
}
void Jordan(float matriz[][6],int limX,int limY){
 int i = 0,j = 0, ceros = 0, modificar = 0, limite = 0, k = 0, contador = 0;
 int pivote = 0, conteoX = 0, conteoY = 0, id = 0, entrar = 0, closerUp = 0;
 int closerDown = 0;
 char tecla;
 float numerador = 0, denominador = 0, fila = 0;
 do{
	fila = mayor(matriz,limX,limY,limite);
	if(fila != -1){
	limite++;
	denominador = matriz[pivote][pivote];
	for(i=0;i<limX;i++){
		for(j=pivote;j<(pivote+1);j++){
		if(entrar == 0){
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
				numerador = matriz[i][j];
				for(k=0;k<limY;k++){
					if(denominador!=0 && entrar==0){
						matriz[i][k] = matriz[fila][k]*(-1)*(numerador/denominador) + matriz[i][k];
						entrar = 0;
					}
					if(denominador == 0)
						entrar = 1;
				}
			}
		} //if(entrar == 0)
		} //for(j=pivote;j<(pivote+1);j++)
	} //for(i=0;i<limX;i++)
	if(pivote < limY)
		pivote++;
	contador++;
	} //if(fila != -1)
	else{
		clrscr();
		marco2(2);
		textcolor(RED);
		gotoxy(3,5);cprintf("ERROR:");
		textcolor(WHITE);
		gotoxy(10,5);cprintf("Matriz provoca Divisi¢n entre Cero");
		gotoxy(10,6);cprintf("Matriz sin Soluci¢n");
		contador = limY;
		ceros = 0;
		id = 1;
		getch();
	}
 }while((contador+1)<limY);
 for(i=0;i<limX;i++)
	for(j=0;j<limY-1;j++){
		if(i != j){
			closerUp = fabs(ceil(matriz[i][j]));
			closerDown = fabs(floor(matriz[i][j]));
			if(closerUp==0 || closerDown==0){
				matriz[i][j] = 0;
			}
		}
	}
 cerosMatriz(matriz,limX,limY,&ceros);
 if(ceros == 0){
	if(id == 0){
		fflush(stdin);
		clrscr();
		marco2(2);
		textcolor(RED);
		gotoxy(3,5);cprintf("ERROR:");
		textcolor(WHITE);
		gotoxy(12,5);cprintf("Matriz sin soluci¢n.");
		getch();
	}
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
	marco(limX,limY,2);
	for(i=5;i<limX+5;i++)
		for(j=1;j<limY+1;j++){
			if(conteoX == conteoY){
				textcolor(WHITE);
				gotoxy(j*10+2,i*2-4);cprintf("%.5f",matriz[i-5][j-1]);
			}
			else{
				if((j+1) == (limY+1)){
					textcolor(WHITE);
					gotoxy(j*10+2,i*2-4);cprintf("%.5f",matriz[i-5][j-1]);
				}
				else{
					textcolor(LIGHTGRAY);
					gotoxy(j*10+2,i*2-4);cprintf("%.5f",matriz[i-5][j-1]);
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
void Captura(float matriz[][6],int limX,int limY,int id){
 int i = 0, j = 0, minus = 0, point = 0, numero = 0/*, verificar=1, verificar2 = 1*/;
 int conteoX = 0, conteoY = 0, posicion = 0, Flechas = 0, salida_Matriz = 1;
 char cadena[10] = {'\x0'};
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
		marco(limX,limY,id);
		textcolor(RED);
		gotoxy(3,18);cprintf("Nota:");
		textcolor(WHITE);
		gotoxy(9,18);cprintf("Presione ESC para salir de la Captura de la Matriz");
		textcolor(BLACK);
		gotoxy((conteoX+1)*10+2,(conteoY+1)*2+4);cprintf("       ",cadena);
		textcolor(WHITE);
		gotoxy((conteoX+1)*10+2,(conteoY+1)*2+4);cprintf("%s",cadena);
		tecla = getch();
		if(tecla == '\x0')
			Flechas = 1;
		else
		if(Flechas == 0 && posicion<8){
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
		if(minus==1 && numero==0)
			tecla = '\x1B';
	}while(tecla!='\xD' || strlen(cadena)==0);
	if(salida_Matriz == 1){
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
	if(id == 1)
		Cramer(matriz,limX,limY);
	if(id == 2)
		Jordan(matriz,limX,limY);
 } // if(salida_Matriz == 1)
}
void menu3(){
 float matriz[5][6] = {0};
 int salida = 0;
 char tecla;
 do{
	clrscr();
	marco2(2);
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
			Captura(matriz,2,3,2);
			salida = 0;break;
		case '2':
			Captura(matriz,3,4,2);
			salida = 0;break;
		case '3':
			Captura(matriz,4,5,2);
			salida = 0;break;
		case '4':
			Captura(matriz,5,6,2);
			salida = 0;break;
		case '\x1B':
			salida = 1;break;
		default:
			salida = 0;break;
	}
 }while(salida == 0);
}
void menu2(){
 float matriz[5][6] = {0};
 int salida = 0;
 char tecla;
 do{
	clrscr();
	marco2(1);
	textcolor(GREEN);
	gotoxy(24,10);cprintf("Elegir Tama¤o de la Matriz Aumentada");
	textcolor(WHITE);
	gotoxy(23,11);cprintf("       1.- 2 Inc¢gnitas (2 x 3)");
	gotoxy(23,12);cprintf("       2.- 3 Inc¢gnitas (3 x 4)");
	textcolor(GREEN);
	gotoxy(21,17);cprintf("Presione ESC para poder salir del programa");
	tecla = getch();
	switch(tecla){
		case '1':
			Captura(matriz,2,3,1);
			salida = 0;break;
		case '2':
			Captura(matriz,3,4,1);
			salida = 0;break;
		case '\x1B':
			salida = 1;break;
		default:
			salida = 0;break;
	}
 }while(salida == 0);
}
void menu(){
 int salida = 0;
 char tecla;
 do{
	clrscr();
	marco2(0);
	textcolor(GREEN);
	gotoxy(24,10);cprintf("Elegir M‚todo para Soluci¢n de Matrices");
	textcolor(WHITE);
	gotoxy(23,11);cprintf("       1.- Regla de Cramer");
	gotoxy(23,12);cprintf("       2.- Eliminaci¢n de Gauss - Jordan");
	textcolor(GREEN);
	gotoxy(21,17);cprintf("Presione ESC para poder salir del programa");
	tecla = getch();
	switch(tecla){
		case '1':
			menu2();
			salida = 0;break;
		case '2':
			menu3();
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