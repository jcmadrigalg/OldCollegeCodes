/*
Pr ctica No. 2 - Juego del Ahorcado
Autor: Juan Carlos Madrigal Gonz lez - 002/57303
Descripci¢n del Funcionamiento del Programa:
 * Inicialmente se tendr n 10 palabras
 1.- Agregar Palabra
	- No aceptar n£meros
 2.- Jugar
	- Cuando adivine una letra, mostrar todas las apariciones
	  en la palabra (Opcional)
	- Las repeticiones cuentan como error
	- Mostrar las letras que ya se hayan utilizado
*/
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
/////////////////////// VOLVER A CAPTURAR ///////////////////

int vuelveCapturar(int cuenta){
 int out = 0,i = 0;
 char tecla;
 do{
	 if(cuenta<20)
		printf("\n¨Desea repetir operaci¢n? S/N");
	 else{
		clrscr();
		for(i=1;i<80;i++){
			gotoxy(i,3);printf("-");
			gotoxy(i,20);printf("-");
		}
		gotoxy(3,4);printf("\n¨Desea repetir operaci¢n? S/N");
		cuenta = 5;
	 }
	 tecla=getch();
	 if(isalpha(tecla)){
		if(toupper(tecla) == 'S' || toupper(tecla) == 'N'){
			if(toupper(tecla) == 'S')
				out = 0;
			if(toupper(tecla) == 'N'){
				out = 1;
				cuenta++;
			}
		}
		else{
			out = 2;
			cuenta++;
		}
	 }
	 else{
		out = 2;
		cuenta++;
	 }
 }while(out == 2);
 return out;
}
/////////////////////// ANALIZAR CADENA ///////////////////

int analizar_Cadena(char cad[]){
 int cadenaAceptada = 1,i = 0;
 if(strlen(cad)>0 && strlen(cad)<41){
	for(i=0;i<strlen(cad);i++){
		if(isalpha(cad[i]) && strcmp(cad," ")!=0 && cadenaAceptada==1)
			cadenaAceptada = 1;
		else
			cadenaAceptada = 0;
	}
 }
 else
	cadenaAceptada = 0;
 return cadenaAceptada;
}
//////////////////////////// DIBUJO /////////////////////////////

void dibujo(){
 gotoxy(67,7); printf("____________");
 gotoxy(67,8); printf("|        |");
 gotoxy(67,9); printf("|");
 gotoxy(67,10);printf("|");
 gotoxy(67,11);printf("|");
 gotoxy(67,12);printf("|");
}
////////////////////// PROGRAMACION DEL JUEGO ///////////////////

void juego(char matrizPalabras[][30],int tam){
 int salida = 0, i = 0, j = 0, k = 0, posFila = 0, contador = 0,error = 0;
 int repetido = 0, encontro = 0, gano = 0, entro = 0,Flechas_u_Otro = 0;
 char cadenaTemp[50];
 char letrasUsadas[30];
 char tecla;
 randomize();
 do{
	clrscr();
	dibujo();
	error = 0;
	j = 0;
	contador = 0;
	gotoxy(33,2);printf("JUEGO DEL AHORCADO");
	for(i=1;i<80;i++){
		gotoxy(i,3);printf("-");
		gotoxy(i,20);printf("-");
	}
	posFila = rand()%(10+tam);
	strcpy(cadenaTemp,matrizPalabras[posFila]);
	gotoxy(3,5);printf("Adivina la palabra secreta, suerte!");
	for(i=0;i<strlen(cadenaTemp);i++){
		gotoxy(1+i,10);printf("_");
	}
	do{
		tecla = getch();
		if(tecla=='\x0')
			Flechas_u_Otro = 1;
		else{
		if(Flechas_u_Otro == 0){
		if(isalpha(tecla)){
		if(j > 0){
			for(k=0;k<j;k++)
				if(tolower(tecla) == letrasUsadas[k])
					repetido++;
		}
		else
			repetido = 0;
		for(i=0;i<strlen(cadenaTemp);i++){
			if(repetido == 0){
				if(tolower(tecla) == cadenaTemp[i]){
					gotoxy(1+i,10);printf("%c",cadenaTemp[i]);
					contador++;
					encontro = 1;
				}
			}
			else{
				if(entro == 0){
					error++;
					entro++;
					encontro = 2;
				}
			}
		}
		if(encontro == 0)
			error++;
		if(j == 0){
			letrasUsadas[0] = tolower(tecla);
			gotoxy(25,12);printf("%c",letrasUsadas[0]);
			j++;
		}
		else{
			if(repetido == 0 && j>0){
				letrasUsadas[j] = tecla;
				j++;
			}
		}
		gotoxy(10,12);printf("Letras Usadas:");
		for(i=0;i<j;i++){
			gotoxy(25+i,12);printf("%c",letrasUsadas[i]);
		}
		if(contador == strlen(cadenaTemp))
			gano = 1;
		else
			gano = 0;
		if(error > 0 && gano==0){
		switch(error){
			case 1:
				gotoxy(67,9); printf("|        0");
				break;
			case 2:
				gotoxy(67,10);printf("|        |");
				break;
			case 3:
				gotoxy(67,10);printf("|       /|");
				break;
			case 4:
				gotoxy(67,10);printf("|       /|\\");
				break;
			case 5:
				gotoxy(67,11);printf("|       / ");
				break;
			case 6:
				gotoxy(67,11);printf("|       / \\");
				gotoxy(1,10);printf("%s",cadenaTemp);
				gotoxy(35,15);printf("GAME OVER");
				gano = 0;
				break;
			}
		}
		repetido = encontro = entro= 0;
		}
		}
		Flechas_u_Otro = 0;
		}
	}while(error<6 && gano==0);
			if(gano == 1){
				gotoxy(25,15);printf("Felicidades, Adivinaste la Palabra");
			}
			salida = vuelveCapturar(16);
 }while(salida == 0);
}
/////////////////////// CAPTURAR NUEVA PALABRA ///////////////////

void capturar(char cad[]){
 int i = 0, pos = 0,Flecha = 0,cantidad = 0;
 char tecla;
 cad[0] = '\x0';
 do{
	clrscr();
	gotoxy(30,2);printf("AGREGAR NUEVA PALABRA");
	for(i=1;i<80;i++){
		gotoxy(i,3);printf("-");
		gotoxy(i,20);printf("-");
	}
	gotoxy(3,5);printf("Agregar Nueva Palabra: %s",cad);
	tecla = getch();
	if(cantidad>-1 && cantidad < 30){
//	tecla = getch();
	if(tecla=='\x0'){
		Flecha = 1;
		printf("Flechas");
	}
	else{
	if(Flecha == 0){
		if(isalpha(tecla) && tecla!=' ' && tecla!='\xD' && tecla!='\x1B' && Flecha==0){
			pos = strlen(cad);
			cad[pos] = tecla;
			cad[pos+1] = '\x0';
			cantidad++;
		}
		if(tecla == '\x8'){
			if(cantidad>0){
			pos = strlen(cad);
			cad[pos-1] = '\x0';
			cantidad--;
			}
		}
	}
	Flecha = 0;
	}
	}//if cantidad < 30
	else{
		if(cantidad > -1)
		if(tecla == '\x8'){
			pos = strlen(cad);
			cad[pos-1] = '\x0';
			cantidad--;
		}
	}
 }while(tecla != '\xD');
}
/////////////////////// AGREGAR NUEVA PALABRA ///////////////////

void agregar_Palabra(char matrizPalabras[][30],int *tam){
 char cadenaGeneral[30];
 int entrarOtraVez = 0, i = 0, salida = 0, existe = 0;
 do{
	if(*tam<5){
		do{
			clrscr();
			existe = 0;
			gotoxy(30,2);printf("AGREGAR NUEVA PALABRA");
			for(i=1;i<80;i++){
				gotoxy(i,3);printf("-");
				gotoxy(i,20);printf("-");
			}
			gotoxy(3,5);printf("Agregar Nueva Palabra: ");capturar(cadenaGeneral);
			entrarOtraVez = analizar_Cadena(cadenaGeneral);
		 }while(entrarOtraVez == 0);
		 for (i=0; i<strlen(cadenaGeneral); i++){
			cadenaGeneral[i] = tolower(cadenaGeneral[i]);
		 }
		 for(i=0;i<(10+(*tam));i++){
			if(strcmp(cadenaGeneral,matrizPalabras[i]) == 0)
				existe = 1;
			else
				if(existe == 0)
					existe = 0;
		 }
		 if(existe == 0){
			 strcpy(matrizPalabras[10+(*tam)],cadenaGeneral);
			(*tam)++;
			salida = vuelveCapturar(7);
		 }
		 else{
			clrscr();
			gotoxy(25,2);printf("AGREGAR NUEVA PALABRA");
			for(i=1;i<80;i++){
				gotoxy(i,3);printf("-");
				gotoxy(i,20);printf("-");
			}
			gotoxy(3,5);printf("Operaci¢n Imposible: \"%s\"  ya existe en la Lista de Palabras\n",cadenaGeneral);
			salida = vuelveCapturar(7);
			existe = 0;
		 }
	}
	else{
		clrscr();
		gotoxy(25,2);printf("AGREGAR NUEVA PALABRA");
		for(i=1;i<80;i++){
			gotoxy(i,3);printf("-");
			gotoxy(i,20);printf("-");
		}
		gotoxy(3,5);printf("Operaci¢n Imposible: Llegaste al n£mero m ximo de palabras");
		salida = 1;
		getch();
	}
 }while(salida == 0);
}
/////////////////////// MENU PRINCIPAL ///////////////////

void menu(){
 char matrizGeneral[15][30] = {"topologia","aeropuerto","telescopio","sagitario",
				"homerun","astronomia","submarino",
				"waterpolo","saxofon","vector"};
 char tecla;
 int salida = 0,tamanio = 0,i = 0;
 do{
	clrscr();
	for(i=1;i<80;i++){
		gotoxy(i,3);printf("-");
		gotoxy(i,20);printf("-");
	}
	gotoxy(9,10);printf("1.- Agregar Nueva Palabra");
	gotoxy(9,11);printf("2.- Jugar");
	gotoxy(9,12);printf("3.- Salida");
	tecla = getch();
	switch(tecla){
		case '1':
			agregar_Palabra(matrizGeneral,&tamanio);
			salida = 0;break;
		case '2':
			juego(matrizGeneral,tamanio);
			salida = 0;break;
		case '3':
			salida = 1;break;
		default:
			salida = 0;break;
	}
 }while(salida == 0);
}
void main(){
 menu();
}