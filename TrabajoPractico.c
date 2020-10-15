#include <stdio.h>      // libreria estandar
#include <stdlib.h>     // para usar exit y funciones de la libreria standard
#include <string.h>
#include <pthread.h>    // para usar threads
#include <semaphore.h>  // para usar semaforos
#include <unistd.h>


#define LIMITE 50

int bandera;
sem_t salero;
sem_t plancha;
sem_t horno;


//creo estructura de semaforos 
struct semaforos {
    	sem_t sem_mezclar;
	sem_t sem_salarEquipo;
	sem_t sem_armarMedallones;
	sem_t sem_cocinarEquipo;
	sem_t sem_cortarTL;
	sem_t sem_horneado;
	sem_t sem_armar;
	//poner demas semaforos aqui
};

//creo los pasos con los ingredientes
struct paso {
   char accion [LIMITE];
   char ingredientes[4][LIMITE];
   
};


//creo los parametros de los hilos 
struct parametro {

 	int equipo_param;
  	struct semaforos semaforos_param;
 	struct paso pasos_param[8];
};

void* imprimirAccion(void *data, char *accionIn) {
	FILE*archivo;
	archivo = fopen ("vacio.txt", "a");
	char equipo[3];
	char cadena[50];
	
	struct parametro *mydata = data;
	//calculo la longitud del array de pasos 
	int sizeArray = (int)( sizeof(mydata->pasos_param) / sizeof(mydata->pasos_param[0]));
	//indice para recorrer array de pasos 
	int i;
	for(i = 0; i < sizeArray; i ++){
		//pregunto si la accion del array es igual a la pasada por parametro (si es igual la funcion strcmp devuelve cero)
		if(strcmp(mydata->pasos_param[i].accion, accionIn) == 0){
		printf("\tEquipo %d - accion %s \n " , mydata->equipo_param, mydata->pasos_param[i].accion);
		snprintf(equipo, sizeof(equipo), "%d", mydata->equipo_param);
		strcat(cadena, "\tEquipo: ");
		strcat(cadena, equipo);
		strcat(cadena," - ");
		strcat(cadena, mydata->pasos_param[i].accion);
		strcat(cadena, "\n");
		fputs(cadena, archivo);
		
		//calculo la longitud del array de ingredientes
		int sizeArrayIngredientes = (int)( sizeof(mydata->pasos_param[i].ingredientes) / sizeof(mydata->pasos_param[i].ingredientes[0]) );
		//indice para recorrer array de ingredientes
		int h;
		printf("\tEquipo %d -----------ingredientes : ----------\n",mydata->equipo_param);
		strcpy(cadena, "");
		strcat(cadena,"\tEquipo: ");
		strcat(cadena,equipo);
		strcat(cadena," ------------ingredientes :-----------\n");
		fputs(cadena, archivo);
		 
			for(h = 0; h < sizeArrayIngredientes; h++) {
				//consulto si la posicion tiene valor porque no se cuantos ingredientes tengo por accion 
				if(strlen(mydata->pasos_param[i].ingredientes[h]) != 0) {
							printf("\tEquipo %d ingrediente  %d : %s \n",mydata->equipo_param,h,mydata->pasos_param[i].ingredientes[h]);
							strcpy(cadena,"");
							strcat(cadena,"\tEquipo ");
							strcat(cadena,equipo);
							strcat(cadena," ");
							strcat(cadena,"ingrediente: ");
							strcat(cadena, mydata->pasos_param[i].ingredientes[h]);
							strcat(cadena,"\n");
							fputs(cadena,archivo);
				}
			}
		}
	}
	fclose(archivo);
}

void* cortarTomateLechuga(void *data) {
        //creo el nombre de la accion de la funcion
        char *accion = "cortarTomateLechuga";
        //creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
        struct parametro *mydata = data;
        //llamo a la funcion imprimir le paso el struct y la accion de la funcion
        imprimirAccion(mydata,accion);
        //uso sleep para simular que que pasa tiempo
        usleep( 9000000 );
        //doy la señal a la siguiente accion (cortar me habilita mezclar)
	sem_post(&mydata->semaforos_param.sem_cortarTL);

    pthread_exit(NULL);
}


void* hornear(void *data) {
	sem_wait(&horno);
        //creo el nombre de la accion de la funcion
        char *accion = "hornear";
        //creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
        struct parametro *mydata = data;
        //llamo a la funcion imprimir le paso el struct y la accion de la funcion
        imprimirAccion(mydata,accion);
        //uso sleep para simular que que pasa tiempo
        usleep( 9000000 );
        //doy la señal a la siguiente accion (cortar me habilita mezclar)
	sem_post(&horno);
        sem_post(&mydata->semaforos_param.sem_horneado);
    pthread_exit(NULL);
}


void* cortar(void *data) {
        //creo el nombre de la accion de la funcion
        char *accion = "cortar";
        //creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
        struct parametro *mydata = data;
        //llamo a la funcion imprimir le paso el struct y la accion de la funcion
        imprimirAccion(mydata,accion);
        //uso sleep para simular que que pasa tiempo
        usleep( 9000000 );
        //doy la señal a la siguiente accion (cortar me habilita mezclar)
        sem_post(&mydata->semaforos_param.sem_mezclar);

    pthread_exit(NULL);
}

void* mezclar(void *data) {
        //creo el nombre de la accion de la funcion
        char *accion = "mezclar";
        //creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
        struct parametro *mydata = data;

	sem_wait(&mydata->semaforos_param.sem_mezclar);

        //llamo a la funcion imprimir le paso el struct y la accion de la funcion
        imprimirAccion(mydata,accion);
        //uso sleep para simular que que pasa tiempo
        usleep( 9000000 );
        //doy la señal a la siguiente accion (cortar me habilita mezclar)

	sem_post(&mydata->semaforos_param.sem_salarEquipo);    	

    pthread_exit(NULL);
}

void* salar(void *data) {
	sem_wait(&salero);
        //creo el nombre de la accion de la funcion
        char *accion = "salar";
        //creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
        struct parametro *mydata = data;
	
	sem_wait(&mydata->semaforos_param.sem_salarEquipo);
	
        //llamo a la funcion imprimir le paso el struct y la accion de la funcion
        imprimirAccion(mydata,accion);
        //uso sleep para simular que que pasa tiempo
        usleep( 9000000 );
        //doy la señal a la siguiente accion (cortar me habilita mezclar)
        sem_post(&salero);
	sem_post(&mydata->semaforos_param.sem_armarMedallones);

    pthread_exit(NULL);
}


void* armar(void *data) {
        //creo el nombre de la accion de la funcion
        char *accion = "armarMedallones";
        //creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
        struct parametro *mydata = data;

	sem_wait(&mydata->semaforos_param.sem_armarMedallones);
	
        //llamo a la funcion imprimir le paso el struct y la accion de la funcion
        imprimirAccion(mydata,accion);
        //uso sleep para simular que que pasa tiempo
        usleep( 9000000 );
        //doy la señal a la siguiente accion (cortar me habilita mezclar)
	sem_post(&mydata->semaforos_param.sem_cocinarEquipo);

    pthread_exit(NULL);
}

void* cocinar(void *data) {
	sem_wait(&plancha);
        //creo el nombre de la accion de la funcion
        char *accion = "cocinar";
        //creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
        struct parametro *mydata = data;

	 sem_wait(&mydata->semaforos_param.sem_cocinarEquipo);

        //llamo a la funcion imprimir le paso el struct y la accion de la funcion
        imprimirAccion(mydata,accion);
        //uso sleep para simular que que pasa tiempo
        usleep( 5000000 );
        //doy la señal a la siguiente accion (cortar me habilita mezclar)
	sem_post(&plancha);
	sem_post(&mydata->semaforos_param.sem_armar);

    pthread_exit(NULL);
}

void imprimirGanador(void *data){
	int orden[3];
	FILE*archivo;
        archivo = fopen ("vacio.txt", "a");
	char equipo[5];
	char cadena[50];
        struct parametro *mydata = data;
	if(bandera == 0){
		snprintf(equipo, sizeof(equipo), "%d", mydata->equipo_param);
        	printf("\tEquipo ganador: %d \n",mydata->equipo_param);
		strcat(cadena,"\tEquipo ganador: ");
		strcat(cadena,equipo);
		strcat(cadena,"\n");
		fputs(cadena,archivo);
		fclose(archivo);
		bandera++;
   	
	}
	else{
		snprintf(equipo, sizeof(equipo), "%d", mydata->equipo_param);
                printf("\tEquipo perdero: %d \n",mydata->equipo_param);
                strcat(cadena,"\tEquipo perdedor: ");
                strcat(cadena,equipo);
                strcat(cadena,"\n");
                fputs(cadena,archivo);
                fclose(archivo);

        }
}

void* armarHamburguesa(void *data) {
        //creo el nombre de la accion de la funcion
        char *accion = "armarHamburguesa";
        //creo el puntero para pasarle la referencia de memoria (data) del struct pasado por parametro (la cual es un puntero).
        struct parametro *mydata = data;
	sem_wait(&mydata->semaforos_param.sem_horneado);
	sem_wait(&mydata->semaforos_param.sem_cortarTL);
	sem_wait(&mydata->semaforos_param.sem_armar);
        //llamo a la funcion imprimir le paso el struct y la accion de la funcion
        imprimirAccion(mydata,accion);
        //uso sleep para simular que que pasa tiempo
        usleep( 9000000 );
	imprimirGanador(mydata);
        //doy la señal a la siguiente accion (cortar me habilita mezclar)

    pthread_exit(NULL);
}



void* ejecutarReceta(void *i){

	sem_t sem_mezclar;
	sem_t sem_salarEquipo;
	sem_t sem_armarMedallones;
	sem_t sem_cocinarEquipo;
	sem_t sem_cortarTL;
	sem_t sem_horneado;
	sem_t sem_armar;

	pthread_t p1;
	pthread_t p2;
	pthread_t p3;
	pthread_t p4;
	pthread_t p5;
	pthread_t p6;
	pthread_t p7;
	pthread_t p8;

	int p = *((int *) i);

	printf("Ejecutando equipo %d \n", p);

	struct parametro *pthread_data = malloc(sizeof(struct parametro));

	pthread_data->equipo_param = p;

	pthread_data->semaforos_param.sem_mezclar = sem_mezclar;
	pthread_data->semaforos_param.sem_salarEquipo = sem_salarEquipo;
	pthread_data->semaforos_param.sem_armarMedallones = sem_armarMedallones;
	pthread_data->semaforos_param.sem_cocinarEquipo = sem_cocinarEquipo;
	pthread_data->semaforos_param.sem_cortarTL = sem_cortarTL;
	pthread_data->semaforos_param.sem_horneado = sem_horneado;
	pthread_data->semaforos_param.sem_armar = sem_armar;

 	FILE*archivo;
        archivo = fopen("RECETA.txt","r");
	char separador[]="," ;
	char cadena[50]; 
	int cont=0; 
	int indice1=0;
	int indice2=0;


	while(fgets(cadena,100,archivo) != NULL){
		char*token = strtok(cadena,separador);
		strcpy(pthread_data->pasos_param[indice1].accion, token);
		while(token != NULL){
			if(cont!=0){
				strcpy(pthread_data->pasos_param[indice1].ingredientes[indice2], token);
				token = strtok(NULL, separador);
				indice2++;
			}
			else{
				token = strtok(NULL, separador);
				cont++;
			}
		}
	cont=0;
	indice2=0;
	indice1++;
	}
	
	int fclose(FILE*archivo);

	sem_init(&(pthread_data->semaforos_param.sem_mezclar),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_salarEquipo),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_armarMedallones),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_cocinarEquipo),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_cortarTL),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_horneado),0,0);
	sem_init(&(pthread_data->semaforos_param.sem_armar),0,0);

	int rc;

	rc = pthread_create(&p1,NULL,cortar,pthread_data);
	rc = pthread_create(&p2,NULL,mezclar,pthread_data);
	rc = pthread_create(&p3,NULL,salar,pthread_data);
	rc = pthread_create(&p4,NULL,armar,pthread_data);
	rc = pthread_create(&p5,NULL,cocinar,pthread_data);
	rc = pthread_create(&p6,NULL,hornear,pthread_data);
	rc = pthread_create(&p7,NULL,cortarTomateLechuga,pthread_data);
	rc = pthread_create(&p8,NULL,armarHamburguesa,pthread_data);
	
	
	pthread_join (p1,NULL);
	pthread_join (p2,NULL);
	pthread_join (p3,NULL);
	pthread_join (p4,NULL);
	pthread_join (p5,NULL);
	pthread_join (p6,NULL);
	pthread_join (p7,NULL);
	pthread_join (p8,NULL);

	sem_destroy(&sem_mezclar);
	sem_destroy(&sem_salarEquipo);
	sem_destroy(&sem_armarMedallones);
	sem_destroy(&sem_cocinarEquipo);
	sem_destroy(&sem_cortarTL);
	sem_destroy(&sem_armar);

	 pthread_exit(NULL);
}





int main ()
{
	sem_init(&salero,0,1);
	sem_init(&plancha,0,1);
	sem_init(&horno,0,1);

	remove ("vacio.txt");
	int bandera = 0;
        int rc;

        int *equipoNombre1 =malloc(sizeof(*equipoNombre1));
	int *equipoNombre2 =malloc(sizeof(*equipoNombre2));
	int *equipoNombre3 =malloc(sizeof(*equipoNombre3));

        *equipoNombre1 = 1;
	*equipoNombre2 = 2;
	*equipoNombre3 = 3;

        pthread_t equipo1;
	pthread_t equipo2;
	pthread_t equipo3;

        rc = pthread_create(&equipo1,NULL,ejecutarReceta,equipoNombre1);
	rc = pthread_create(&equipo2,NULL,ejecutarReceta,equipoNombre2);
	rc = pthread_create(&equipo3,NULL,ejecutarReceta,equipoNombre3);

        pthread_join (equipo1,NULL);
	pthread_join (equipo2,NULL);
	pthread_join (equipo3,NULL);

        pthread_exit(NULL);

	sem_destroy(&salero);
	sem_destroy(&plancha);
	sem_destroy(&horno);

}

