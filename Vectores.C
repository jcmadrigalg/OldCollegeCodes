/*
Pr ctica No. 1 - Repaso de Vectores en C
Autor: Juan Carlos Madrigal Gonz lez 002/57303
Descripci¢n:
1.- Llenar un vector con n n£meros enteros (n lo selecciona el usuario)
2.- Generar una tabla de frecuencias. Los datos deben estar claramente
    indicados: NO 1-7, 3-5, 9, 10
    si no en forma de tabla
    1 - 7
    3 - 5
    9 - 10
    , etc.
3.- Agregar datos al vector. Validar!
4.- Eliminar datos del vector
5.- Calcular promedio de los datos.
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void autor(){
clrscr();
gotoxy(26,10);printf("            AUTOR");
gotoxy(26,11);printf("Madrigal Gonz lez Juan Carlos");
getch();
}
/////////////////////// VOLVER A CAPTURAR ///////////////////

int vuelveCapturar(){
 int out = 0;
 char tecla;
 do{
	 printf("\n¨Desea capturar otro dato? S/N");tecla=getch();
	 if(isalpha(tecla)){
		if(toupper(tecla) == 'S' || toupper(tecla) == 'N'){
			if(toupper(tecla) == 'S')
				out = 0;
			if(toupper(tecla) == 'N')
				out = 1;
		}
		else
			out = 2;
	 }
	 else
		out = 2;
 }while(out == 2);
 return out;
}
//////////////////////// ANALIZAR UNA CADENA ///////////////////

int analizarCadena(char cad[30]){
 int numero = 0, i = 0, positivo = 1;
 if(strlen(cad) < 30){
	 for(i=0;i<(strlen(cad));i++){
		 if(isdigit(cad[i]) && positivo == 1)
			positivo = 1;
		 else
			positivo = 0;
	 }
	 if(positivo == 1)
		numero = atoi(cad);
	 else
		numero = -1;
 }
 else
	numero = -1;
 return numero;
}
///////////////////// CAPTURA DEL TAMA¥O DEL VECTOR ///////////////////

int capturaTamVector(){
 char cadena[30];
 int n = 0, i = 0;
 do{
	 clrscr();
	 gotoxy(25,2);printf("G E N E R A R     V E C T O R");
	 for(i=1;i<80;i++){
		gotoxy(i,3);printf("-");
		gotoxy(i,20);printf("-");
	 }
	 gotoxy(3,5);printf("Tama¤o del Vector: ");gets(cadena);
	 n = analizarCadena(cadena);
 }while(n<1 || n>20);
 return n;
}
/////////////////////// GENERADOR EL VECTOR ///////////////////

void generador(int vector[],int *tam){
  int columnas = 0,z = 0, i = 0;
  clrscr();
  for(i=1;i<80;i++){
	gotoxy(i,3);printf("-");
	gotoxy(i,20);printf("-");
  }
  gotoxy(25,2);printf("G E N E R A R     V E C T O R");
  *tam = capturaTamVector();
  randomize();
  columnas = 1;
  z = 0;
  for(i=0;i<*tam;i++){
	vector[i] = rand()%11;
	if(z%5 == 0){
		z = 0;
		columnas++;
		gotoxy((10*columnas),7);printf("%d\n",vector[i]);
//		z++;
	}
	else{
		gotoxy((10*columnas),(z+7));printf("%d\n",vector[i]);
	}
	z++;
  }
  getch();
}
/////////////////// TABLA DE FRECUENCIA DEL VECTOR ///////////////////

void Tabla_de_Frecuencias(int vector[],int n){
 int Valor_repetido[20];
 int i=0,j=0,k=0,repetido=0,contador=0,z=0,impresionRepetir=0;
 clrscr();
 for(i=1;i<80;i++){
	gotoxy(i,3);printf("-");
	gotoxy(i,20);printf("-");
 }
 gotoxy(35,1);printf("TABLA  DE  FRECUENCIAS");
 gotoxy(20,2);printf("Elemento");
 gotoxy(60,2);printf("No. Veces");
 if(n > 0){
	 for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(vector[j] == vector[i]){
				repetido++;
			}
		}
		if(k > 0){
			for(z=0;z<k;z++){
				if(Valor_repetido[z] == vector[i])
					contador++;
			}
			if(contador == 0){
				Valor_repetido[k] = vector[i];
				k++;
			}
		}
		if(k == 0){
			Valor_repetido[k] = vector[i];
			k++;
		}
		if(impresionRepetir < k){
			gotoxy(23,5+impresionRepetir);printf("%d",Valor_repetido[k-1]);
			gotoxy(63,5+impresionRepetir);printf("%d",repetido);
			impresionRepetir++;
		}
		repetido = contador = 0;
	 }
 }
 else{
	gotoxy(3,5);printf("No hay elementos en el Vector");
 }
 getch();
}
/////////////////////// AGREGAR ELEMENTOS AL VECTOR ///////////////////

int agregar_Datos_Vector(){
 char cadena[10];
 int dato=0,i=0;
 do{
	clrscr();
	 gotoxy(30,2);printf("AGREGAR   DATOS  AL  VECTOR");
	 for(i=1;i<80;i++){
		gotoxy(i,3);printf("-");
		gotoxy(i,20);printf("-");
	 }
	gotoxy(3,5);printf("Nuevo Numero: ");gets(cadena);
	dato = analizarCadena(cadena);
 }while(dato<0 || dato>10);
 return dato;
}
void add_Elementos_Vector(int vector[],int *tam){
  int new_data = 0, out_adddel = 0, i = 0;
  if(*tam < 20){
	  do{
		  new_data = agregar_Datos_Vector();
		  vector[*tam] = new_data;
		  (*tam)++;
		  if(*tam < 20)
			out_adddel = vuelveCapturar();
		  new_data = 0;
	  }while(out_adddel == 0);
  }
  else{
	clrscr();
	gotoxy(30,2);printf("AGREGAR   DATOS  AL  VECTOR");
	for(i=1;i<80;i++){
		gotoxy(i,3);printf("-");
		gotoxy(i,20);printf("-");
	}
	gotoxy(3,5);printf("Vector Lleno: No se pueden agregar mas datos");
	getch();
  }
}
/////////////////////// ELIMINAR ELEMENTOS AL VECTOR ///////////////////

int capturaBorrarVector(){
 char cadena[10];
 int dato=0,i=0;
 do{
	clrscr();
	gotoxy(30,2);printf("ELIMINAR   DATOS  AL  VECTOR");
	for(i=1;i<80;i++){
		gotoxy(i,3);printf("-");
		gotoxy(i,20);printf("-");
	}
	gotoxy(3,5);printf("Numero a Borrar: ");gets(cadena);
	dato = analizarCadena(cadena);
 }while(dato<0 || dato>10);
 return dato;
}
int eliminar_Datos_Vector(int vector[],int *n,int valor){
 int posicion = 0, i = 0, encontrado = 0;
 for(i=0;i<*n;i++){
	if(vector[i] == valor && encontrado == 0){
		posicion = i;
		encontrado = 1;
	}
 }
 if(encontrado == 0){
	posicion = -1;
 }
 return posicion;
}
void del_Elementos_Vector(int vector[],int *tam){
  int vectorTemp[20] = {0};
  int del_data = 0, del_pos_data = 0, i = 0,j = 0,out_adddel = 0;
  do{
	if(*tam > 0){
		j = 0;
		del_data = capturaBorrarVector();
		del_pos_data = eliminar_Datos_Vector(vector,tam,del_data);
		if(del_pos_data == -1){
			clrscr();
			gotoxy(30,2);printf("ELIMINAR   DATOS  AL  VECTOR");
			for(i=1;i<80;i++){
				gotoxy(i,3);printf("-");
				gotoxy(i,20);printf("-");
			}
			gotoxy(3,5);printf("Eliminaci¢n Imposible: Numero No Encontrado\n");
			out_adddel = vuelveCapturar();
		}
		if(del_pos_data >= 0){
			for(i=0;i<*tam;i++)
				if(del_pos_data != i){
					vectorTemp[j] = vector[i];
					j++;
				}
			for(i=0;i<20;i++)
				vector[i] = 0;
			for(i=0;i<*tam-1;i++)
				vector[i] = vectorTemp[i];
			(*tam)--;
			out_adddel = vuelveCapturar();
		}
	}
	else{
		clrscr();
		gotoxy(30,2);printf("ELIMINAR   DATOS  AL  VECTOR");
		for(i=1;i<80;i++){
			gotoxy(i,3);printf("-");
			gotoxy(i,20);printf("-");
		}
		gotoxy(3,5);printf("Vector Vacio: No se pueden eliminar mas elementos");
		out_adddel = 1;
		getch();
	}
  }while(out_adddel == 0);
}
/////////////////////// CALCULO DE PROMEDIO DEL VECTOR ///////////////////

void promedio_Vector(int vector[20],int n){
 int i = 0;
 float sumatoria = 0.0000,promedio = 0.0000;
 if(n > 0){
	 for(i=0;i<n;i++){
		sumatoria = sumatoria + vector[i];
	 }
	 promedio = (sumatoria/n);
	 clrscr();
	 gotoxy(30,2);printf("AGREGAR   DATOS  AL  VECTOR");
	 for(i=1;i<80;i++){
		gotoxy(i,3);printf("-");
		gotoxy(i,20);printf("-");
	 }
	 gotoxy(3,5);printf("Calculo del Promedio del Vector: %f",promedio);
	 getch();
 }
 else{
	 clrscr();
	 gotoxy(30,2);printf("AGREGAR   DATOS  AL  VECTOR");
	 for(i=1;i<80;i++){
		gotoxy(i,3);printf("-");
		gotoxy(i,20);printf("-");
	 }
	 gotoxy(3,5);printf("Calculo Imposible: No hay elementos en el Vector");
	 getch();
 }
}
////////////////////////// MENU DEL PROGRAMA ///////////////////

void menu(){
 int vectorGeneral[20];
 int salida = 0,tamanio = 0, i = 0;
 char tecla;
 do{
	 clrscr();
	 for(i=1;i<80;i++){
		gotoxy(i,3);printf("-");
		gotoxy(i,20);printf("-");
	 }
	 gotoxy(20,10);printf("1.- Generar Nuevo Vector");
	 gotoxy(20,11);printf("2.- Tabla de Frecuencias");
	 gotoxy(20,12);printf("3.- Agregar Datos al Vector");
	 gotoxy(20,13);printf("4.- Eliminar Datos del Vector");
	 gotoxy(20,14);printf("5.- Calcular Promedio de Datos del Vector");
	 gotoxy(20,15);printf("6.- Salida del Programa");
	 tecla=getch();
	 clrscr();
	 if(isdigit(tecla)){
		switch(tecla){
			case '1':
				generador(vectorGeneral,&tamanio);
				salida = 0;break;
			case '2':
				Tabla_de_Frecuencias(vectorGeneral,tamanio);
				salida = 0;break;
			case '3':
				add_Elementos_Vector(vectorGeneral,&tamanio);
				salida = 0;break;
			case '4':
				del_Elementos_Vector(vectorGeneral,&tamanio);
				salida = 0;break;
			case '5':
				promedio_Vector(vectorGeneral,tamanio);
				salida = 0;break;
			case '6':
				salida = 1;break;
			default:
				salida = 0;break;
		}
	 }
	 else
		salida = 0;
 }while(salida == 0);
 autor();
}
void main(){
 menu();
}
