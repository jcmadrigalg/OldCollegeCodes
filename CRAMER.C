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
	marco2();
	textcolor(GREEN);
	gotoxy(3,5);cprintf("Determinate Principal:");
	textcolor(WHITE);
	gotoxy(26,2);cprintf("R E G L A     D E     C R A M E R");
	gotoxy(26,5);cprintf("%.4f",determinante);
	for(i=0;i<limX;i++){
		gotoxy(5,7+i);cprintf("%c = %.4f",literales[i],valoresResueltos[i]);
	}
	getch();
 }
 else{
	clrscr();
	marco2();
	gotoxy(26,2);cprintf("R E G L A     D E     C R A M E R");
	gotoxy(3,5);cprintf("       Determinante Principal provoca Divisi¢n entre Cero.");textcolor(RED);
	gotoxy(3,5);cprintf("ERROR:");textcolor(WHITE);
	gotoxy(3,6);cprintf("       Matriz sin soluci¢n.");
	getch();
 }
}
void Captura(float matriz[][6],int limX,int limY){
 int i = 0, j = 0, minus = 0, point = 0, numero = 0/*, verificar=1, verificar2 = 1*/;
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
		gotoxy(26,2);cprintf("R E G L A     D E     C R A M E R");
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
		if(minus==1 && numero==0)
			tecla = '\x1B';
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
	Cramer(matriz,limX,limY);
 } // if(salida_Matriz == 1)
}
void multiplicacion(){
 int fila = 3, fila2 = 3, columna = 3, columna2 = 3, resultado = 0;
 int i = 0, j = 0, k = 0, z = 0, producto = 0;
 int matriz[5][5] = {0};
 int matriz2[5][5] = {0};
 int productoMatriz[5][5] = {0};
 textcolor(WHITE);
 do{
	clrscr();
	marco2();
	textcolor(WHITE);
	gotoxy(25,2);cprintf("MULTIPLICACIàN DE MATRICES");
	textcolor(RED);
	gotoxy(2,4);cprintf("Primera Matriz");
	textcolor(WHITE);
	gotoxy(3,5);cprintf("Fila: ");scanf("%d",&fila);
	gotoxy(3,6);cprintf("Columna: ");scanf("%d",&columna);
	textcolor(RED);
	gotoxy(2,8);cprintf("Segunda Matriz");
	textcolor(WHITE);
	gotoxy(3,9);cprintf("Fila2: ");scanf("%d",&fila2);
	gotoxy(3,10);cprintf("Columna2: ");scanf("%d",&columna2);
 }while(fila>5 || columna>5 || fila2>5 || columna2>5);
 clrscr();
 if((fila==fila2 && columna==columna2) && (fila==columna2)){
	textcolor(GREEN);
	cprintf("Matriz 1");
	textcolor(WHITE);
	k = 0;
	for(i=0;i<fila;i++)
		for(j=0;j<columna;j++){
			gotoxy(5,2+k);cprintf("Elemento[%d][%d]: ",i,j);scanf("%d",&matriz[i][j]);
			k++;
		}
	clrscr();
	textcolor(GREEN);
	cprintf("Matriz 2");
	textcolor(WHITE);
	k = 0;
	for(i=0;i<fila2;i++)
		for(j=0;j<columna2;j++){
			gotoxy(5,2+k);cprintf("Elemento[%d][%d]: ",i,j);scanf("%d",&matriz2[i][j]);
			k++;
		}
	for(k=0;k<fila;k++)
		for(z=0;z<columna;z++){
			resultado = 0;
			for(i=0;i<columna;i++){
				producto = matriz[k][i]*matriz2[i][z];
				resultado = resultado + producto;
			}
			productoMatriz[k][z] = resultado;
		}
	clrscr();
	marco2();
	gotoxy(15,2);cprintf("R E S U L T A D O S");
	gotoxy(1,5);
	for(i=0;i<fila;i++){
		for(j=0;j<columna;j++){
			textcolor(WHITE);
			cprintf("%d",productoMatriz[i][j]);
			textcolor(GREEN);
			cprintf(" | ");
		}
		printf("\n");
	}
	getch();
 }
 else{
	clrscr();
	marco2();
	textcolor(RED);
	gotoxy(3,5);cprintf("ERROR:");
	textcolor(WHITE);
	gotoxy(25,2);cprintf("MULTIPLICACIàN DE MATRICES");
	gotoxy(10,5);cprintf("No se puede multiplicar matrices de diferente dimensi¢n.");
	getch();
 }
}
void menu2(){
 float matriz[5][6] = {0};
 int limX = 0, limY = 0, salida = 0;
 char tecla;
 do{
	clrscr();
	marco2();
	textcolor(GREEN);
	gotoxy(24,10);cprintf("Elegir Tama¤o de la Matriz Aumentada");
	textcolor(WHITE);
	gotoxy(26,2);cprintf("R E G L A     D E     C R A M E R");
	gotoxy(23,11);cprintf("       1.- 2 Inc¢gnitas (2 x 3)");
	gotoxy(23,12);cprintf("       2.- 3 Inc¢gnitas (3 x 4)");
	textcolor(GREEN);
	gotoxy(21,17);cprintf("Presione ESC para regresar al Menu Principal");
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
	marco2();
	textcolor(GREEN);
	gotoxy(24,10);cprintf("Elegir Opci¢n");
	textcolor(WHITE);
	gotoxy(33,2);cprintf("MENé PRINCIPAL");
	gotoxy(23,11);cprintf("       1.- Multiplicaci¢n de Matrices");
	gotoxy(23,12);cprintf("       2.- Regla de Cramer");
	textcolor(GREEN);
	gotoxy(21,17);cprintf("Presione ESC para poder salir del programa");
	tecla = getch();
	switch(tecla){
		case '1':
			multiplicacion();
			salida = 0;break;
		case '2':
			menu2();
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