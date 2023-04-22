#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


#define N 50

typedef struct{
	char name[N];
	char tipo[N];
	int cantidadVida;
	int puntosAtaque;
	int puntosDefensa;
	
}Guardian;

typedef struct nodo{
	Guardian dato;
    struct nodo *sig;
}Nodo;

//Funcion para cargar los datos
Nodo* loadGame(char*nombreArchivo){
	//cracion dee variables archivo, guardianes y nodo (para la lista de guardianes) 
	FILE *archivo;
	Guardian guardianes;
	Nodo *listaGuardianes = NULL;
	
	char strings[N];
	
	//Abrir el archivo
	archivo = fopen(nombreArchivo, "r");
	
	if(archivo == NULL){
		printf("Error al abrir el archivo\n");
		return NULL;
	}
	
	while(fgets(strings,sizeof(strings), archivo)){
		sscanf(strings, "%s %s %d %d %d", guardianes.name, guardianes.tipo, &guardianes.cantidadVida, &guardianes.puntosAtaque, &guardianes.puntosDefensa);
		
		//Crear un nuevo nodo y cargar su puntero
		Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
		//Cargar struct guardianes een nodo
		nuevoNodo->dato = guardianes;
		nuevoNodo->sig = listaGuardianes;
		listaGuardianes = nuevoNodo;

	}
	
	fclose(archivo);
	return listaGuardianes;
}


//Funcion para imprimir listas
void printStructList(Nodo *lista){
	int cont = 0;
	//Asignale el valor de la lista a un nuevo nodo
	Nodo *nodoActual = lista;
	
	while(nodoActual != NULL){
		printf("Guardian %d: %s\n  >> Tipo: %s \n\  >> Cantidad de Vida: %d \n  >> Puntos de ataque: %d \n  >> Puntos de defensa %d\n\n", cont+1, nodoActual->dato.name, nodoActual->dato.tipo, nodoActual->dato.cantidadVida, nodoActual->dato.puntosAtaque, nodoActual->dato.puntosDefensa);
		nodoActual = nodoActual->sig;
		cont++;
	}
}


int selectCharacter(Nodo *lista, Guardian *point, Nodo **head){
	int guardianPosInt;
	Nodo *nodoAux = lista;
	int cont = 0, i;
	//cargar un personaje 
	printf("|====| PERSONAJES DISPONIBLES |====|\n");
	printStructList(lista); //mostrar los personajes
	printf("\nIngrese el numero del guardian que desee ocupar: "); //pedir que se escoja personaje
	scanf("%d", &guardianPosInt);
	guardianPosInt = guardianPosInt-1;
	//encontrar el guardian
	i = 0;
	while(nodoAux != NULL && i < guardianPosInt){
		nodoAux = nodoAux->sig;
		i++;
	}
	
	//llenado del guardian a la lista de jugadores
	
	strcpy(point[0].name, nodoAux->dato.name);
	strcpy(point[0].tipo, nodoAux->dato.tipo);
	point[0].cantidadVida = nodoAux->dato.cantidadVida;
	point[0].puntosAtaque = nodoAux->dato.puntosAtaque;
	point[0].puntosDefensa = nodoAux->dato.puntosDefensa;
	
	//eliminar ese elemento
	if(guardianPosInt == 0){//si se encuentra en la primera posicion
		Nodo *aux = *head;
		*head = (*head)->sig;
		free(aux);
		
	}else{
		Nodo *nodoAnt = *head;
		Nodo *nodoAct = (*head)->sig;
		for(i = 1; i < guardianPosInt; i++){
			nodoAnt = nodoAct;
			nodoAct = nodoAct->sig;
		}
		nodoAnt->sig = nodoAct->sig;	
		free(nodoAct);
	}
	
	return  0 ;
}


//Funcion menu
int menuOptions(Nodo *lista, Guardian *point, Nodo **head){
	int valor = 1;
	char stringAux[N];
	int opcionNivel;
	
	//Asignale el valor de la lista a un nuevo nodo
	Nodo *nodoActual = lista;
	
	int opcion, i, opcionTipo;

	
	printf("Ingrese una opcion: \n\t>> 1 para cargar un personaje existente \n\t>> 2 para crear un nuevo personaje\n");
	scanf("%d", &opcion);
	system("cls");
	
	while(valor == 1){
		
		if(opcion == 1){
			valor = selectCharacter(lista, point, head);
			
		}else if(opcion == 2){
			//crear un personaje
			printf("Ingrese el nombre de su personaje: ");
			scanf("%s", &stringAux);
			strcpy(point[0].name, stringAux);
			
			printf("Ingrese el numero del tipo al que corresponde su personaje \n\t>> 1 para mage \n\t>> 2 para beast \n\t>> 3 para viking \n\t>> 4 para nigromante\n");
			scanf("%d", &opcionTipo);
			
			if(opcionTipo == 1){
				char stringAux[N] = "mage";
			}else if(opcionTipo == 2){
				char stringAux[N] = "beast";
			}else if(opcionTipo == 3){
				char stringAux[N] = "viking";
			}else{
				char stringAux[N] = "nigromante";
			}
			strcpy(point[0].name, stringAux);
			
			printf("Ingrese la cantidad de vida de su personaje: ");
			scanf("%d", &point[0].cantidadVida);
			
			printf("Ingrese los puntos de ataque de su personaj: ");
			scanf("%d", &point[0].puntosAtaque);
			
			printf("Ingrese los puntos de defensa de su personaje: ");
			scanf("%d", &point[0].puntosDefensa);
			
			valor = 0;
			
		}else{
			printf("La opcion ingresada es incorrecta");
		}
		
		//Escoger nivel
		valor = 1;
		while(valor == 1){
			printf("Ingrese una opcion de cuantos guardianes desea derrotar: \n\t>> 1 para nivel 1: 3 guardianes \n\t>> 2 para nivel 2: 5 guardianes \n\t>> 3 para nivel 3: 7 guardianes \n");
			scanf("%d", &opcionNivel);
			
			if(opcionNivel == 1){
				opcionNivel = 3;
				valor = 0;
			}else if (opcionNivel == 2){
				opcionNivel = 5;
				valor = 0;
			} else if (opcionNivel == 3){
				opcionNivel = 7;
				valor = 0;
			}else{
				printf("La opcion ingresada es incorrecta\n");
			}
		}
		
		return opcionNivel;
	}
	
}

//funcion para reorganizar la lista
void shuffleLista(Nodo **listaGuardianes){
	srand(time(NULL));
	
	int listext = 0;//extencion de la lista
	int i, k;
	
	//contar cuantos elementos en la lista hay
	Nodo *nodoContar = *listaGuardianes;
	
	while(nodoContar != NULL){
		nodoContar = nodoContar->sig;
		listext++;
	}
	
	for (i = listext - 1; i > 0; i--) {
	    // Generar un número aleatorio entre 0 y i
	    int ran;
		ran = rand() % (i + 1);
	
	    // Intercambiar el elemento en la posición i con el elemento en la posición j
	    Nodo *nodo_i = *listaGuardianes;
	    for(k = 0; k < i; k++) {
	    	nodo_i = nodo_i->sig;
	    }
	
	    Nodo *nodo_j = *listaGuardianes;
	    for (k = 0; k < ran; k++) {
	      nodo_j = nodo_j->sig;
	    }
	
	    Guardian aux = nodo_i->dato;
	    nodo_i->dato = nodo_j->dato;
	    nodo_j->dato = aux;
	}
}
//Funcoion para llenar el array de los guardiaens en juego
void llenadoGuardianes(Nodo *lista, Guardian *point, int opcionNivel, Nodo **head){
	int i , k;
	
	//Contar la extencion de la lista
	int listExt = 0;	
	Nodo *nodoGuardianesOponentes = lista;
	for(i = 1; i < opcionNivel+1; i++){
		strcpy(point[i].name, nodoGuardianesOponentes->dato.name);
		strcpy(point[i].tipo, nodoGuardianesOponentes->dato.tipo);
		point[i].cantidadVida = nodoGuardianesOponentes->dato.cantidadVida;
		point[i].puntosAtaque = nodoGuardianesOponentes->dato.puntosAtaque;
		point[i].puntosDefensa = nodoGuardianesOponentes->dato.puntosDefensa;
		
		nodoGuardianesOponentes = nodoGuardianesOponentes->sig;
	}
	head = nodoGuardianesOponentes;
	
}

void llenadoStructOponentesJugador(Guardian *point, Nodo **oponentes, Nodo **jugadores, int nivel){
	int i, k;
	//oponentes
	Nodo *actualO = *oponentes;
	for(i = 1; i < nivel + 1; i++){
		Nodo *newNodoO = (Nodo*) malloc(sizeof(Nodo));
		newNodoO->dato = point[i];
		newNodoO->sig = NULL;
		
		if(actualO == NULL){
			*oponentes = newNodoO;
			actualO = *oponentes;
		}else{
			actualO->sig = newNodoO;
			actualO = actualO->sig;
		}
	}
}

void printArray(Guardian *point, int opcionNivel){
	int i;
	for(i = 0; i < opcionNivel + 1; i++){
		printf("Guardian %d: %s \n  >> Tipo: %s \n  >> Cantidad de Vida: %d \n  >> Puntos de ataque: %d \n  >> Puntos de defensa %d\n\n", i+1, point[i].name, point[i].tipo, point[i].cantidadVida, point[i].puntosAtaque, point[i].puntosDefensa);
	}
}

//Funcion para atacar o defender segun el guardian que este jugando
void ataqueDefenza(Guardian *guardianesEnJuego, int opcionJuego, int iJ, int iO, int *dadoCont, int *turno){
	srand(time(NULL));
	int ranDado;
	float factor = 1;
	int dano;
	int sumaVida;
	int desgaste;
	
	ranDado = (rand() % 6)+1;//darle un vaor random a dado entre 1 y 6
	
	printf("Guardian %s a lanzado los dados, ha salido %d\n\n", guardianesEnJuego[iJ].name, ranDado);
	system ("pause");
	system("cls");
	
	if(opcionJuego == 1){
		//ataque
		if(ranDado % 2 == 0){
			//numero par;
			printf("El enemigo ha bloqueado al ataque... \n\n");
			system("pause");
			system("Cls");
		}else{
			//numero impar
			if(ranDado == 1){
				factor = 0.8;
			}else if(ranDado == 3){
				factor = 1;
			}else{
				factor = 1.3;	
			}
			dano = round((float)factor*guardianesEnJuego[iJ].puntosAtaque);//se aproxima e saño para poder trabajarcon el despues
			printf("Guardian %s ha atacado a guardian %s, daño inflingido: %d\n\n", guardianesEnJuego[iJ].name, guardianesEnJuego[iO].name, dano);
			guardianesEnJuego[iO].cantidadVida = guardianesEnJuego[iO].cantidadVida - dano;
			
			//se muestra e satus del guardian atacado
			printf("Guardian %s \n  >> Tipo: %s \n  >> Cantidad de Vida: %d \n  >> Puntos de ataque: %d \n  >> Puntos de defensa %d\n\n", guardianesEnJuego[iO].name, guardianesEnJuego[iO].tipo, guardianesEnJuego[iO].cantidadVida, guardianesEnJuego[iO].puntosAtaque, guardianesEnJuego[iO].puntosDefensa);
			
			system("pause");
			system("cls");
		}
		if(ranDado == 6 && *dadoCont == 0){
			printf("Como ha lanzado un 6 puede volver a jugar...\n\n");
			system("pause");
			system("cls");
			(*dadoCont)++;
		}else{
			*dadoCont = 0;
			*turno = (*turno) * -1;
		}
	}else{
		//defenza
		if(ranDado % 2 == 0){
			//numero par
			if(ranDado == 2){
				factor = 0.5;
			}else if(ranDado == 4){
				factor = 1;
			}else{
				factor = 1.2;	
			}
			sumaVida = round((float)factor*guardianesEnJuego[iJ].puntosDefensa);//se aproxima la vida para poder trabajarcon el despues
			printf("Guardian %s se ha curado, cura realizada: %d\n\n", guardianesEnJuego[iJ].name, sumaVida);
			
			//se muestra e satus del guardian atacado
			printf("Guardian %s \n  >> Tipo: %s \n  >> Cantidad de Vida: %d \n  >> Puntos de ataque: %d \n  >> Puntos de defensa %d\n\n", guardianesEnJuego[iJ].name, guardianesEnJuego[iJ].tipo, guardianesEnJuego[iJ].cantidadVida, guardianesEnJuego[iJ].puntosAtaque, guardianesEnJuego[iJ].puntosDefensa);
			
			system("pause");
			system("cls");
		}else{
			//numero impar
			printf("Guardian %s no se ha podido curar... \n\n", guardianesEnJuego[iJ].name);
			system("pause");
			system("Cls");
			
		}
		if(ranDado == 6 && *dadoCont == 0){
			printf("Como usted ha lanzado un 6 puede volver a jugar...\n\n");
			system("pause");
			system("cls");
			(*dadoCont)++;
		}else{
			*dadoCont = 0;
			*turno = (*turno) * -1;		
		}
		//Desgaste
		if(guardianesEnJuego[iJ].puntosDefensa > 30){//si el desgaste es mayor a 30
			desgaste = round((float)guardianesEnJuego[iJ].puntosDefensa*0.05);
			guardianesEnJuego[iJ].puntosDefensa = guardianesEnJuego[iJ].puntosDefensa - desgaste;
			printf("Los puntos de defensa del guardian %s se han desgastado, ahora sus puntos son: %d \n", guardianesEnJuego[iJ].name,guardianesEnJuego[iJ].puntosDefensa);
			
			system("pause");
			system("Cls");
		}
	}
}

void startFigth(int opcionNivel, Guardian *guardianesEnJuego, int *oponenteCont){
	int opcionJuego;
	int turno = 1;
	int contDadoRep = 0;
	int valor = *oponenteCont;
	
	while(valor <= opcionNivel){
		printf("El oponente numero %d es: %s\n", *oponenteCont, guardianesEnJuego[*oponenteCont].name);	
		system("pause");
		system("cls");
		
		contDadoRep = 0;
		while(contDadoRep < 2){
			printf("|====| Guardian %s vs Guardian %s |====|\n\n", guardianesEnJuego[0].name, guardianesEnJuego[*oponenteCont].name);
			if(turno > 0){
				printf("Es el turno del guardian %s... \n\n", guardianesEnJuego[0].name);
				//turno jugador
				printf("Ingrese una opcion: \n  >> 1 para atacar \n  >> 2 para defender\n");
				scanf("%d", &opcionJuego);
				system("cls");
				ataqueDefenza(guardianesEnJuego, opcionJuego, 0, *oponenteCont, &contDadoRep, &turno);
				
				//verificar estado del guadian oponente
				if(guardianesEnJuego[*oponenteCont].cantidadVida <= 0){
					//jugador ha muerto
					system("cls");
					printf("El guardian oponente %s ha decidido ha perdido... \n\n", guardianesEnJuego[*oponenteCont].name);
					
					system("pause");
					system("cls");
					
					(*oponenteCont)++;
					valor++;
					contDadoRep = 3;
				}
			}else{
				//turno jugadr 2
				if(guardianesEnJuego[*oponenteCont].cantidadVida > 0){
					printf("Es turno del guardian oponente %s... \n", guardianesEnJuego[*oponenteCont].name);
				
					//Hacer que si e guardian tien menos de 100 de vida se cure sino sera random
					if(guardianesEnJuego[*oponenteCont].cantidadVida <= 100){
						opcionJuego = 2;//defender
					}else{
						opcionJuego = (rand()%2) + 1;
					}
					if(opcionJuego == 1){
						printf("El guardian oponente %s ha decidido atacar... \n\n", guardianesEnJuego[*oponenteCont].name);
					}else{
						printf("El guardian oponente %s ha decidido defenderse... \n\n", guardianesEnJuego[*oponenteCont].name);
					}
					system("pause");
					system("cls");
					
					ataqueDefenza(guardianesEnJuego, opcionJuego, *oponenteCont, 0, &contDadoRep, &turno);
					
					//verificar estado del guadian
					if(guardianesEnJuego[0].cantidadVida <= 0){
						//jugador ha muerto
						system("cls");
						printf("Lamentablemente has perdido \n\n");
						valor = 10;
						contDadoRep = 3;	
					}
				
				}
			}
		}
		
	}
	return;
}
void historial(Guardian *pointEnJuego, int nivel, Guardian *point){
	int i;
	
	printf("|====| Oponentes derrotados |====|\n");
	for(i = 0; i < 15 + 1; i++){
		if(point[i].puntosAtaque != 0 && point[i].puntosDefensa != 0 && point[i].cantidadVida != 0){
			printf("Oponente numero %d: %s\n", i+1, point[i].name);
		}
	}
	printf("\n");
	system("pause");
	system("cls");
}
void llenadoHistorial(Guardian *pointEnJuego, int nivel, Guardian *point){
	int i;
	int index; 
	
	if(point[0].puntosAtaque == 0 && point[0].puntosDefensa == 0 && point[0].cantidadVida == 0){
		for(i = 1; i < nivel + 1; i++){
			point[i-1] = pointEnJuego[i];
		}
	}else{
		for(i = 0; i < 15 + 1; i++){
			if(point[i].puntosAtaque == 0 && point[i].puntosDefensa == 0 && point[i].cantidadVida == 0){
				index = i;
				break;
			}
		}
		for(i = 1; i < nivel + 1; i++){
			point[i-1+index] = pointEnJuego[i];
		}	
	}
}

int main(){
	//lista principal de gruardianes
	Nodo *listaGuardianes = NULL;
	int i;
	
	//lista para guardas datos
	Nodo *listaOponentes = NULL; //lista para guardar a os oponentes
	Nodo *istaJugadores = NULL; //lista para guardr a los jugadores
	Nodo *listaDerrotdos = NULL; //lista para guardar a los guardianes derrotados
	
	//Preguntar si quiere cargar dtos o introducirlos el usuarui
	int opcionLoadFile;
	
	listaGuardianes = loadGame("DATOS.txt");
	
	
	
	Guardian *guardianesEnJuego = (Guardian *)malloc(8 *sizeof(Guardian));
	Guardian *guardianesHisotrial = (Guardian *)malloc(15 *sizeof(Guardian));
	//inicializaicon de guardianHistorial
	for(i = 0; i < 15; i++){
		strcpy(guardianesHisotrial[i].name , "0");
		strcpy(guardianesHisotrial[i].tipo ,"0");
		guardianesHisotrial[i].cantidadVida = 0;
		guardianesHisotrial[i].puntosAtaque = 0;
		guardianesHisotrial[i].puntosDefensa = 0;
	}
	
	int opcionNivel;
	
	//Inicio
	printf("====| BIENVENIDO A THE GUARDIANS TOURNAMENT |====|\n");
	printf("\nPrimero usted debe escoger un guardian\n");
	
	//menu
	opcionNivel = menuOptions(listaGuardianes, guardianesEnJuego, &listaGuardianes);
	
	//Inicio de juego; 	
	//Llenado de demas guardianes
	shuffleLista(&listaGuardianes);//primero se reorganizan la lista de guardianes
	llenadoGuardianes(listaGuardianes, guardianesEnJuego, opcionNivel, &listaGuardianes);	
	
	system("cls");
	printf("|====| BIENVENIDO %s |====|\n\n", guardianesEnJuego[0].name);
	
	//primer torneo
	int valorVida = 0;
	int oponenteCont = 1;
	startFigth(opcionNivel, guardianesEnJuego, &oponenteCont);
	
	//comprobar si e jugador tiene vida
	if(guardianesEnJuego[0].cantidadVida <= 0){
		valorVida = 1;
	}
	//siguiente torneo
	int opcionSig;
	int valor = 0;
	while(valor == 0 && valorVida == 0){
		printf("Ha derrotado a todos los oponentes de este nivel, seleccione una opcion\n  >> 1 para conocer el historial del torneo anterior\n  >> 2 para seguir con el siguiente torneo\n  >> 3 para salir\n");
		scanf("%d", &opcionSig);
		llenadoHistorial(guardianesEnJuego, opcionNivel,guardianesHisotrial);
		if(opcionSig == 1){
			//historial
			historial(guardianesEnJuego, opcionNivel,guardianesHisotrial);
			
		}else if(opcionSig == 2){
			//siguiete torneo 
			if(opcionNivel == 3){
				
				opcionNivel = 5;
				shuffleLista(&listaGuardianes);//primero se reorganizan la lista de guardianes
				llenadoGuardianes(listaGuardianes, guardianesEnJuego, opcionNivel, &listaGuardianes);
				oponenteCont = 1;
				startFigth(opcionNivel, guardianesEnJuego, &oponenteCont);
				
			}else if(opcionNivel == 5){
				opcionNivel == 7;
				shuffleLista(&listaGuardianes);//primero se reorganizan la lista de guardianes
				llenadoGuardianes(listaGuardianes, guardianesEnJuego, opcionNivel, &listaGuardianes);
				oponenteCont = 1;
				startFigth(opcionNivel, guardianesEnJuego, &oponenteCont);
				
			}else{
				printf("Usted ya a derrotado a todos los enemigos\n");
				valor = 1;
			}
			
			
		}else if(opcionSig == 3){
			break;
		}
		
	}
	printf("|====| USTED HA FINALIZADO EL JUEGO |====|");
	free(listaGuardianes);
	free(guardianesHisotrial);
	free(guardianesEnJuego);
	return 0;
}
