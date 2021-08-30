#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(int argc, char *argv[]){
//Variables
int i;		//Contador de command inputs
int size;	//Variable con el valor de la longitud
char Nombre[50];//Variable que guarda el nombre, maximo 50 letras
char ID[5];	//Variable que guarda el ID, maximo 5 numeros de longitud
char *nombreArchivo = "Datalog.txt";
char *modo = "w";
char respuesta[2] = "Y";
FILE *archivo = fopen(nombreArchivo,modo); //Modo "w", sobrescribe el archivo
int ayuda;
if(archivo == NULL){ //Verificamos si se abrio el archivo
	printf("Error abriendo el archivo %s\n",archivo);
	return 1;
}else if(archivo != NULL){
	//Read command inputs
	for(i = 0; i < argc; i++){
		printf("argv[%d] = %s\n",i,argv[i]);
	}
	if(strcmp(argv[1],"-s")==0){
		
		size = atoi(argv[2]);		 	   //Convertimos string de entrada a int
		
			for(int x = 0; x<size; x++){		 //Loop de lecturas de datos
				if(strcmp(respuesta,"Y")==0){	 //Verificamos que aun se quieran seguir guardando datos
			
					printf("ENTER NAME: \n");	 //Solicitamos Nombre
					scanf("%s",&Nombre);		 //Leemos nombre
						
					printf("ENTER ID: \n");	 	 //Solicitamos el ID
					scanf("%s",&ID);		 	 //Leemos el ID
					fprintf(archivo,"NAME: %s   ID: %s\n",&Nombre,&ID);//Imprimimos en el .txt
					if(x<size-1){
						//Preguntamos si se quiere continuar asignando nombres
						printf("Do you wish to add more? [Y/n]\n");
						//Leemos respuesta
						scanf("%s",&respuesta);
						
						if(strcmp(respuesta,"Y")!=0){	
							//Guardamos y cerramos
							printf("Students information stored in Datalog.txt\n");	//Desplegamos mensaje de finalizacion
							fclose(archivo);					//Cerramos el archivo
							return 0;	
						}
					}
				}
				
			}//for		
							printf("Students information stored in Datalog.txt\n");	//Desplegamos mensaje de finalizacion
							fclose(archivo);					//Cerramos el archivo
							return 0;	
	}
		else{
			printf("Falta especificar la dimension -s\n");
			return 0;	
		}
	}
}