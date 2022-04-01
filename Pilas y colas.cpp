#include <stdio.h>
#include <string>
#include<fstream>
#include<iostream>

using namespace std;

//Llamar archivo
const char *nombe_archivo = "Alumnos.dat";

//estructura de datos
typedef struct{
	int codigo;
	char nombre[20];
	char apellido[20];
	char direccion[20];
	int telefono;
}Alumnos;


//Declaracion de Scope clases
void pedirDatos(Alumnos *alumno);
void ingresoDatos();
void leerDatos();
void borrarDatos();
void actualizarDatos();

int main(){
	int opcion;
	
		cout<<"------ MENU ------"<<endl;
		cout<<"1. Ingresar"<<endl;
		cout<<"2. Listado"<<endl;
		cout<<"3. Actualizar"<<endl;
		cout<<"4. Eliminar"<<endl;
		cout<<"5.Salir"<<endl;
		cin>>opcion;
		
		switch(opcion){
			case 1:{
				ingresoDatos();
				break;
				}
			
			case 2:{
				leerDatos();	
				break;
				}
				
			case 3:{
				actualizarDatos();	
				break;
				}
				
			case 4:{
				borrarDatos();	
				break;
				}
			
			case 5:{
				exit(0);
				break;
				}
			}
	
	return 0;
}

void pedirDatos(Alumnos *alumno){
	fflush( stdin );
	printf("Introduzca el Codigo:\n");
	scanf("%i", &alumno->codigo);
	fflush( stdin );
	printf("Introduzca el Nombre:\n");
	scanf("%s", &alumno->nombre);
	fflush( stdin );
	printf("Introduzca el Apellido:\n");
	scanf("%100s", &alumno->apellido);
	fflush( stdin );
	printf("Introduzca el Direccion:\n");
	scanf("%100s", &alumno->direccion);
	fflush( stdin );
	printf("Introduzca el Telefono:\n");
	scanf("%i", &alumno->telefono);
}

void ingresoDatos(){
	system("cls");
	char continuar;
	FILE* archivo = fopen(nombe_archivo, "ab");
	
	do{
		system("cls");
		Alumnos alumno;
		pedirDatos(&alumno);
		fwrite(&alumno, sizeof(Alumnos), 1, archivo );
		 

		fflush( stdin );
		printf("Desea inglesar otro alumno s/n:\n");
		scanf("%c", &continuar);
	}while((continuar =='s') || (continuar=='S'));
};

void leerDatos(){
	system("cls");
	
	FILE* archivo = fopen(nombe_archivo, "rb");
	if(!archivo) {
		archivo = fopen(nombe_archivo, "w+b");
	}
	
	Alumnos alumno;
	int registro=0;
	fread ( &alumno, sizeof(Alumnos), 1, archivo );
	do{
	   printf("Id: %i Codigo: %i Nombre: %s Apellido: %s Direccion: %s Telefono: %i \n",registro,alumno.codigo , alumno.nombre, alumno.apellido, alumno.direccion, alumno.telefono);  
	     
		fread ( &alumno, sizeof(Alumnos), 1, archivo );
		registro += 1;	
	} while (feof( archivo ) == 0);
};



void borrarDatos(){
	system("cls");
	const char *nombre_archivo_temp = "archivo_temp.dat";
	Alumnos alumno;
	FILE* archivo = fopen(nombe_archivo, "rb");
	FILE* archivo_temp=fopen(nombre_archivo_temp,"w+b");
	int id=0,i=0;
	cout<<"Ingrese el ID del estudiante que desea eliminar:"<<endl; 
	cin>>id;                                                   
		while(fread(&alumno,sizeof(Alumnos),1,archivo)){
			if (i != id){
				fwrite(&alumno,sizeof(Alumnos),1,archivo_temp);
			} 
			
			i++; 
		}
	                
		fclose(archivo_temp); 
		fclose(archivo); 
	                
		archivo_temp=fopen(nombre_archivo_temp,"rb"); 
		archivo=fopen(nombe_archivo,"wb"); 
	 
		while(fread(&alumno,sizeof(Alumnos),1, archivo_temp)){ 
			fwrite(&alumno,sizeof(Alumnos),1, archivo); 
		}
	                
	fclose(archivo_temp); 
	fclose(archivo); 
	system("PAUSE");
}

void actualizarDatos(){
	system("cls");
	FILE* archivo = fopen(nombe_archivo, "r+b");
	
		int id;
		string nombre,apellido;	
    	Alumnos alumno;
    
		cout << "Ingrese el ID que desea Modificar: ";
    	cin >> id;
    	fseek ( archivo, id * sizeof(Alumnos), SEEK_SET );
	
		pedirDatos(&alumno);
		
		fwrite( &alumno, sizeof(Alumnos), 1, archivo );
		
	fclose(archivo);
	system("PAUSE");
}
