#include<stdio.h>
int main(int argc, char *argv[])
{
	int i = 0;
	//Definimos variables de conversion de string a int
	int Num1;
	int Num2;
	int Area;
	int Perimetro;
	for(i = 0; i < argc; i++){

	    printf("argv[%d] = %s\n",i,argv[i]);

	}
	//CALCULAMOS AREA
	if (strcmp(argv[1],"-a")==0){ //Verificamos si calcularemos area

	//Realizamos conversiones
		if(strcmp(argv[2],"-l")==0){//Verificamos la Longitud
			
		Num1 = atoi(argv[3]);
			if(strcmp(argv[2],"-l")==0){
				
				Num2 = atoi(argv[5]);
				//Calculamos Area
				Area = Num1*Num2;
				printf("Area = %d units\n",Area);
				return 0;
			}
			else{
			
			    printf("Error, falta especificar Anchura\n");
			
			}
		}
		else{
		    printf("Error, falta longitud\n");
		}	
	}
	//CALCULAMOS PERIMETRO	

	else if(strcmp(argv[1],"-p")==0){//Verificamos si calcularemos perimetro
	//Realizamos conversiones
		if(strcmp(argv[2],"-l")==0){//Verificamos la Longitud
			
		Num1 = atoi(argv[3]);
			
			if(strcmp(argv[2],"-l")==0){
				
				Num2 = atoi(argv[5]);
				//Calculamos Area
				Perimetro = 2*Num1+2*Num2;
				printf("Perimetro = %d units\n",Perimetro);
				return 0;
			}
			else{
			
			    printf("Error, falta especificar Anchura\n");
			
			}
		}
		else{
		    printf("Error, falta longitud\n");
		}
	}
	printf("Introduzca una opcion valida\n");
	return 0;   
}