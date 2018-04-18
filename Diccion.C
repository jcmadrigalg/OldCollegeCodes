#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
void marco2(){
 int i = 0;
 textcolor(WHITE);
 for(i=1;i<80;i++){
	gotoxy(i,3);cprintf("-");
	gotoxy(i,20);cprintf("-");
 }
}
/////////////////////// VOLVER A CAPTURAR ///////////////////
int vuelveCapturar(int cuenta){
 int out = 0;
 char tecla;
 do{
	 if(cuenta<20)
		printf("\n¨Desea repetir operaci¢n? S/N");
	 else{
		clrscr();
		marco2();
		textcolor(WHITE);
		gotoxy(3,4);cprintf("\n¨Desea repetir operaci¢n? S/N");
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
//////////////////////// BUSQUEDA INTERPOLADA /////////////////////
////////////////////////// CAPTURA DE NUMERO //////////////////////
int capturarNumero(){
 int pos = 0,Flecha = 0,cantidad = 0, salida = 0;
 char tecla;
 char cad[5] = {'\x0'};
 do{
	clrscr();
	gotoxy(25,2);printf("BUSCAR POSICION DE UN ELEMENTO");
	marco2();
	gotoxy(3,5);printf("Encontrar N£mero: %s",cad);
	tecla = getch();
	if(cantidad>-1 && cantidad < 5){
	if(tecla=='\x0'){
		Flecha = 1;
	}
	else{
	if(Flecha == 0){
		if(isdigit(tecla) && tecla!=' ' && tecla!='\xD' && tecla!='\x1B' && Flecha==0){
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
	}//if cantidad < 5
	else{
		if(cantidad > -1)
		if(tecla == '\x8'){
			pos = strlen(cad);
			cad[pos-1] = '\x0';
			cantidad--;
		}
	}
	if(tecla == '\xD')
		if(strlen(cad)==0)
			salida = 0;
		else
			salida = 1;
 }while(salida==0);
 return atoi(cad);
}
/////////////////////// BUSQUEDA INTERPOLADA //////////////////////
void Busqueda_Interpolada(int vector[]){
 int llave = 0, centro = 0, izquierdo = 0, derecho = 20;
 int salida = 0;
 do{
 clrscr();
 marco2();
 textcolor(WHITE);
 llave = capturarNumero();
 if(llave<0){
	gotoxy(3,7);cprintf("ERROR: N£mero Fuera de Rango");
	getch();
 }
 }while(llave<0);
 if(llave > vector[19]){
	gotoxy(3,7);cprintf("El N£mero no existe");
 }
 else
 do{
	centro = izquierdo + ((derecho-izquierdo)*(llave-vector[izquierdo]))/(vector[derecho]-vector[izquierdo]);
	if(llave == vector[centro]){
		cprintf("\n\n\rN£mero: %d -> Posici¢n: %d",llave,centro);
		salida = 1;
	}
	else{
		if((izquierdo+derecho)/2 == derecho){
			cprintf("\n\n\rEl N£mero no existe");
			salida = 1;
		}
		else{

			if(llave > vector[centro])
				izquierdo = centro+1;
			if(llave < vector[centro])
				derecho = centro-1;
		}
	}
 }while(salida == 0);
 getch();
}
//////////////////////// GENERAR VECTOR ////////////////////
void Generar_Vector(int vector[]){
 int i = 0, j = 0, temp = 0,columna = 10, renglon = 0;
 randomize();
 for(i=0;i<20;i++)
	vector[i] = rand()%21;
 for(i=0;i<19;i++)
	for(j=(i+1);j<20;j++)
		if(vector[i] > vector[j]){
			temp = vector[i];
			vector[i] = vector[j];
			vector[j] = temp;
		}
 textcolor(WHITE);
 clrscr();
 marco2();
 gotoxy(20,2);cprintf("GENERAR NUEVO VECTOR");
 for(i=0;i<20;i++){
	if(i == 10){
		columna = columna + 30;
		renglon = 0;
	}
	gotoxy(columna,5+renglon);cprintf("\n%d",vector[i]);
	renglon++;
 }
 getch();
}
///////////////////////// MOSTRAR VECTOR //////////////////
void Mostrar_Vector(int vector[]){
 int i = 0,columna = 10, renglon = 0;
 textcolor(WHITE);
 clrscr();
 marco2();
 textcolor(WHITE);
 if(vector[0] == -1)
	printf("\nNo se ha Generado el Vector a£n");
 else{
	gotoxy(20,2);cprintf("MUESTRA DE VECTOR");
	for(i=0;i<20;i++){
		if(i == 10){
			columna = columna + 30;
			renglon = 0;
		}
		gotoxy(columna,5+renglon);cprintf("\n%d",vector[i]);
		renglon++;
	}
 }
 getch();
}
/////////////////// FIN DE BUSQUEDA INTERPOLADA /////////////////

/////////////////////////// DICCIONARIO /////////////////////////
////////////////////////// ANALIZAR CADENA //////////////////////
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
/////////////////////// CAPTURAR NUEVA PALABRA ///////////////////
void capturar(char cad[],char traduccion[],int id){
 int pos = 0,Flecha = 0,cantidad = 0, salida = 0;
 char tecla;
 do{
	clrscr();
	textcolor(WHITE);
	gotoxy(30,2);cprintf("AGREGAR NUEVA PALABRA");
	marco2();
	if(id == 1){
		gotoxy(3,7);cprintf("Traducci¢n: %s",traduccion);
		gotoxy(3,5);cprintf("Palabra: %s",cad);
	}
	if(id == 2){
		gotoxy(3,5);cprintf("Palabra: %s",cad);
		gotoxy(3,7);cprintf("Traducci¢n: %s",traduccion);
	}
	if(id == 3){
		clrscr();
		textcolor(BLACK);
		gotoxy(30,2);cprintf("AGREGAR NUEVA PALABRA");
		textcolor(WHITE);
		gotoxy(30,2);cprintf("BUSCAR PALABRA DEL DICCIONARIO");
		marco2();
		gotoxy(3,5);cprintf("Buscar: %s",cad);
	}
	tecla = getch();
	if(cantidad>-1 && cantidad < 30){
	if(tecla=='\x0'){
		Flecha = 1;
		cprintf("Flechas");
	}
	else{
	if(Flecha == 0){
		if(isalpha(tecla) && tecla!=' ' && tecla!='\xD' && tecla!='\x1B' && Flecha==0){
			if(id==1 || id==3){
				pos = strlen(cad);
				cad[pos] = tecla;
				cad[pos+1] = '\x0';
				cantidad++;
			}
			else{
				pos = strlen(traduccion);
				traduccion[pos] = tecla;
				traduccion[pos+1] = '\x0';
				cantidad++;
			}
		}
		if(tecla == '\x8'){
			if(cantidad>0){
				if(id==1 || id==3){
					pos = strlen(cad);
					cad[pos-1] = '\x0';
					cantidad--;
				}
				else{
					pos = strlen(traduccion);
					traduccion[pos-1] = '\x0';
					cantidad--;
				}
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
	if(tecla == '\xD'){
		if(strlen(cad)==0 && id==1)
			salida = 0;
		else
			if(strlen(traduccion)==0 && id==2)
				salida = 0;
			else
				salida = 1;
	}
 }while(salida==0);
}
/////////////////////// AGREGAR NUEVA PALABRA ///////////////////
void Agregar_Palabra_Significado(char matrizPalabras[][50],int *tam){
 char cadenaGeneral[30] = {'\x0'};
 char cadenaGeneral2[30] = {'\x0'};
 int entrarOtraVez = 0,entrarOtraVez2 = 0, i = 0, salida = 0, existe = 0;
 int j = 0;
 do{
	if(*tam<5){
		for(i=0;i<30;i++)
			cadenaGeneral[i] = cadenaGeneral2[i] = '\x0';
		do{
			clrscr();
			existe = 0;
			textcolor(WHITE);
			gotoxy(30,2);cprintf("AGREGAR NUEVA PALABRA");
			marco2();
			gotoxy(3,5);cprintf("Palabra: ");capturar(cadenaGeneral,cadenaGeneral2,1);
			gotoxy(3,7);cprintf("Traducci¢n: ");capturar(cadenaGeneral,cadenaGeneral2,2);
			entrarOtraVez = analizar_Cadena(cadenaGeneral);
			entrarOtraVez2 = analizar_Cadena(cadenaGeneral2);
		 }while(entrarOtraVez==0 && entrarOtraVez2==0);
		 for(i=0; i<strlen(cadenaGeneral); i++){
			if(i == 0)
				cadenaGeneral[i] = toupper(cadenaGeneral[i]);
			else
				cadenaGeneral[i] = tolower(cadenaGeneral[i]);
		 }
		 cadenaGeneral[i] = ';';
		 for(j=0; j<(strlen(cadenaGeneral2)+1);j++){
			if(j == 0)
				cadenaGeneral[j+i+1] = toupper(cadenaGeneral2[j]);
			else
				cadenaGeneral[j+i+1] = tolower(cadenaGeneral2[j]);
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
			textcolor(WHITE);
			gotoxy(25,2);cprintf("AGREGAR NUEVA PALABRA");
			marco2();
			gotoxy(3,5);cprintf("Operaci¢n Imposible: \"%s\"  ya existe en la Lista de Palabras\n",cadenaGeneral);
			salida = vuelveCapturar(7);
			existe = 0;
		 }
	}
	else{
		clrscr();
		gotoxy(25,2);printf("AGREGAR NUEVA PALABRA");
		marco2();
		gotoxy(3,5);printf("Operaci¢n Imposible: Llegaste al n£mero m ximo de palabras");
		salida = 1;
		getch();
	}
 }while(salida == 0);
}
///////////////// MOSTRAR PALABRAS ORDENADAS ////////////
void Mostrar_Palabras_Ordenadas(char matriz[][50],int tam,int id){
 int i = 0, j = 0;
 char definicion1[50] = {'\x0'};
 char definicion2[50] = {'\x0'};
 char temp1[50] = {'\x0'};
 char temp2[50] = {'\x0'};
 char palabra1[50] = {'\x0'};
 char palabra2[50] = {'\x0'};
 clrscr();
 textcolor(WHITE);
 for(i=0;i<(9+tam);i++)
	for(j=(i+1);j<(10+tam);j++){
		strcpy(temp1,matriz[i]);
		strcpy(temp2,matriz[j]);
		strcpy(palabra1,strtok(temp1,";"));
		strcpy(definicion1,strtok(NULL,";"));
		strcpy(palabra2,strtok(temp2,";"));
		strcpy(definicion2,strtok(NULL,";"));
		if(strcmp(palabra1,palabra2) > 0){
			strcpy(definicion1,matriz[i]);
			strcpy(matriz[i],matriz[j]);
			strcpy(matriz[j],definicion1);
		}
	}
 if(id == 1){
	clrscr();
	textcolor(WHITE);
	gotoxy(20,2);cprintf("MUESTREO DE PALABRAS EN EL DICCIONARIO");
	marco2();
	for(i=0;i<(10+tam);i++){
		gotoxy(3,5+i);cprintf("%d.- %s",i+1,matriz[i]);
	}
	getch();
 }
}
////////////////// BUSQUEDA PALABRAS EN MODO BINARIO //////////////
void Busqueda_Palabras_MODO_BINARIO(char matriz[][50],int tamanio){
 int tam = 9+tamanio;
 int izquierdo = 0, derecho = tam, centro = 0, salida = 0;
 char elementoBuscado[50] = {'\x0'};
 char temp[50] = {'\x0'};
 char definicion[50] = {'\x0'};
 char palabra[50] = {'\x0'};
 Mostrar_Palabras_Ordenadas(matriz,tamanio,2);
 clrscr();
 marco2();
 textcolor(WHITE);
 capturar(elementoBuscado," ",3);
 do{
	centro = (izquierdo + derecho)/2;
	strcpy(temp,matriz[centro]);
	strcpy(palabra,strtok(temp,";"));
	strcpy(definicion,strtok(NULL,";"));
	if(strcmp(strlwr(elementoBuscado),strlwr(palabra)) == 0){
		cprintf("\n\n\r%s.- %s",strupr(elementoBuscado),definicion);
		salida = 1;
	}
	else{
		if(centro==derecho){
			cprintf("\n\n\rLa palabra no existe en este Diccionario");
			salida = 1;
		}
		else{
			if(strcmp(elementoBuscado,palabra) > 0)
				izquierdo = centro+1;
			if(strcmp(elementoBuscado,palabra) < 0)
				derecho = centro-1;
		}
	}
 }while(salida == 0);
 getch();
}
//////////////////////// FIN DE DICCIONARIO ///////////////////
///////////////////////////////////////////////////////////////
void Menu_Busqueda_Interpolada(){
 int salida = 0, i = 0;
 int vector[20];
 char tecla;
 for(i=0;i<20;i++)
	vector[i] = -1;
 do{
	clrscr();
	marco2();
	textcolor(GREEN);
	gotoxy(24,10);cprintf("Elegir Operaci¢n:");
	textcolor(WHITE);
	gotoxy(28,2);cprintf("P R µ C T I C A     No. 7");
	gotoxy(23,11);cprintf("       1.- Generar Vector de 20 Elementos");
	gotoxy(23,12);cprintf("       2.- Mostrar Vector");
	gotoxy(23,13);cprintf("       3.- Encontrar posici¢n de un elemento");
	textcolor(GREEN);
	gotoxy(21,17);cprintf("Presione ESC para regresar salir del programa");
	tecla = getch();
	switch(tecla){
		case '1':
			Generar_Vector(vector);
			salida = 0;break;
		case '2':
			Mostrar_Vector(vector);
			salida = 0;break;
		case '3':
			Busqueda_Interpolada(vector);
			salida = 0;break;
		case '\x1B':
			salida = 1;break;
		default:
			salida = 0;break;
	}
 }while(salida == 0);
}
void Menu_Diccionario(){
 int salida = 0, tamanio = 0;
 char tecla;
 char matrizGeneral[15][50] = {"Computadora;Computer","Escritorio;Desktop",
				"Oficina;Office","Guerra;War","Barco;Ship",
				"Calculadora;Calculator","Pluma;Pen",
				"Agua;Water","Silla;Chair","Fuego;Fire"};
 do{
	clrscr();
	marco2();
	textcolor(GREEN);
	gotoxy(24,10);cprintf("Elegir Operaci¢n");
	textcolor(WHITE);
	gotoxy(29,2);cprintf("D I C C I O N A R I O");
	gotoxy(23,11);cprintf("       1.- Agregar Palabra y Significado");
	gotoxy(23,12);cprintf("       2.- Mostrar Palabras Ordenadas");
	gotoxy(23,13);cprintf("       3.- Buscar una palabra");
	textcolor(GREEN);
	gotoxy(21,17);cprintf("Presione ESC para regresar salir del programa");
	tecla = getch();
	switch(tecla){
		case '1':
			Agregar_Palabra_Significado(matrizGeneral,&tamanio);
			salida = 0;break;
		case '2':
			Mostrar_Palabras_Ordenadas(matrizGeneral,tamanio,1);
			salida = 0;break;
		case '3':
			Busqueda_Palabras_MODO_BINARIO(matrizGeneral,tamanio);
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
	gotoxy(24,10);cprintf("Elegir Operaci¢n:");
	textcolor(WHITE);
	gotoxy(28,2);cprintf("P R µ C T I C A     No. 7");
	gotoxy(23,11);cprintf("       1.- Diccionario");
	gotoxy(23,12);cprintf("       2.- B£squeda Interpolada");
	textcolor(GREEN);
	gotoxy(21,17);cprintf("Presione ESC para regresar salir del programa");
	tecla = getch();
	switch(tecla){
		case '1':
			Menu_Diccionario();
			salida = 0;break;
		case '2':
			Menu_Busqueda_Interpolada();
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