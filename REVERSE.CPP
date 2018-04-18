/*
P.T.I. Juan Carlos Madrigal González
12/Sep/2007
Lenguaje C++
*/
#include <stdio.h>
#include <conio.h>
#include <string.h>

void main(){
 char array[50] = {"Esta es una oracion que se vera al reves"};
 char Nuevo_array[50] = {'\x0'};
 char temporal;
 int tamanio_array, i, j, LimiteSuperior, LimiteInferior, tamanio_nuevo_array, espacios = 0;
 LimiteSuperior = strlen(array);
 clrscr();
 printf("\nORIGINAL: ");
 for(i = 0; i < LimiteSuperior; i++)
	printf("%c",array[i]);
 for(i = LimiteSuperior-1; i >= 0; i--){
	tamanio_nuevo_array = strlen(Nuevo_array);
	Nuevo_array[tamanio_nuevo_array] = array[i];
	Nuevo_array[tamanio_nuevo_array+1] = '\x0';
 }
 LimiteInferior = 0;
 for(i = 0; i <= strlen(Nuevo_array); i++){
	if(Nuevo_array[i]==' ' || Nuevo_array[i]=='\x0'){
		LimiteSuperior = i;
		for(j = 0; j < (LimiteSuperior-LimiteInferior)/2; j++){
			temporal = Nuevo_array[LimiteInferior + j];
			Nuevo_array[LimiteInferior + j] = Nuevo_array[LimiteSuperior - 1 - j];
			Nuevo_array[LimiteSuperior - 1 - j] = temporal;
		}
		LimiteInferior = LimiteSuperior + 1;
	}
 }
 printf("\nREVERSE:  ");
 for(i=0;i<strlen(Nuevo_array);i++)
	printf("%c",Nuevo_array[i]);
 getch();
}