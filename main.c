#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define anioactual 2023

/*
typedef struct fecha {
    int dia, mes, anio;};
    */

typedef struct unidades {
    int id,dia,mes,anio;
    char zona[20];
    char ciudad[20];
    int dormitorios;
    int banios;
    float superficieT;
    float superficieC;
    float precio;
    char moneda[10];
    char tipo[20];
    char operacion[20];
    int activo;
};

// ir a una línea determinada
void goy(int y) {
	// Obtener handle de la consola
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// Establecer posición del nuevo cursor
	COORD pos;
	pos.X = 0;
	pos.Y = y;
	// Colocar el cursor en el nuevo sitio
	SetConsoleCursorPosition(hConsole, pos);
}

//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

// 1-Creamos un if que si el archivo existe, no lo crea nuevamente borrando lo ya hecho
// Y si no existe, lo crea.
void crearStock(FILE * pA){
    pA = fopen("propiedades.dat", "r");
     if (pA == NULL) {
        // El archivo no existe, así que lo creamos
        pA = fopen("propiedades.dat", "w");
        } else{
        // El archivo existe, lo cerramos
        fclose(pA);
        printf("El archivo propiedades.dat ya existe\n");
        }
}

int corroborar(int hoy){
    if(hoy==1 || hoy == 3 || hoy ==5 || hoy==7 || hoy==8 || hoy==10 || hoy==12){
        return 31;
    }else if(hoy==4 || hoy==6 || hoy==9 || hoy==11){
        return 30;
    }else return 28;
}

//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

// 2-Ingresar una propiedad nueva
void productoNuevo(FILE * pA){
struct unidades prop;
//struct fecha fechaHoy;
    pA=fopen("propiedades.dat","r+b");
    //chequeamos que se ingrese correctamente el ID
    do{
    printf("");
    printf("Ingrese el ID del articulo: ");
    scanf("%d",&prop.id);
    fflush(stdin);
    if (prop.id<0){printf("\nNumero fuera de rango\n");}
    }while(prop.id<0);
    //ingresamos mes primero para que le día no se pase de rango luego
    do{
    printf("Ingrese el mes: ");
    scanf("%d",&prop.mes);
    fflush(stdin);
    if(prop.mes <= 0 || prop.mes > 12){printf("Fuera de rango, ingrese nuevamente\n");}
    }while(prop.mes <= 0 || prop.mes > 12);

    int veodia = corroborar(prop.mes); //devuelvo a veodia el numero de mes para comparar en el siguiente

    do{
    printf("Ingrese el dia: ");
    scanf("%d",&prop.dia);
    fflush(stdin);
    //Lo mismo, comparo para no ingresar numeros pasados de rango
    if (prop.dia<0 || prop.dia>veodia) {
            printf("Dia fuera de rango\n");    }
    }while(prop.dia>veodia || prop.dia < 0);

    do{
    printf("\nIngrese el a%co: ",164);
    scanf("%d",&prop.anio);
    fflush(stdin);
    if (prop.anio != anioactual){printf("\nAño fuera de rango, ingrese nuevamente");}
    }while(prop.anio != anioactual);

    printf("Ingrese la Zona del articulo: ");
    scanf("%s",&prop.zona);
    fflush(stdin);

    printf("Ingrese la Ciudad del articulo: ");
    scanf("%s",&prop.ciudad);
    fflush(stdin);

    printf("Ingrese la cantidad de Dormitorios del articulo: ");
    scanf("%d",&prop.dormitorios);
    fflush(stdin);

    printf("Ingrese la cantidad de banos del articulo: ");
    scanf("%d",&prop.banios);
    fflush(stdin);

    printf("Ingrese la superficie total del articulo: ");
    scanf("%f",&prop.superficieT);
    fflush(stdin);

    printf("Ingrese la superficie cubierta del articulo: ");
    scanf("%f",&prop.superficieC);
    fflush(stdin);

    printf("Ingrese el precio del articulo: ");
    scanf("%f",&prop.precio);
    fflush(stdin);

    printf("Ingrese el tipo de moneda del articulo: ");
    scanf("%s",&prop.moneda);
    fflush(stdin);

    printf("Ingrese el tipo de la propiedad del articulo: ");
    scanf("%s",&prop.tipo);
    fflush(stdin);

    printf("Ingrese el tipo de Operacion del articulo: ");
    scanf("%s",&prop.operacion);
    fflush(stdin);

    prop.activo=1;

    if (prop.id == 1){
    fseek(pA,0,SEEK_SET);
    fwrite(&prop,sizeof(struct unidades),1,pA);}
    else {
    fseek(pA,(prop.id-1)*sizeof(struct unidades),SEEK_SET);
    fwrite(&prop,sizeof(struct unidades),1,pA);
        }

 fclose(pA);
}

//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

// 3-Muestra la lista de las propiedades del archivo pArchivo
void Lista(FILE *pA){
struct unidades prop;
int i=0, cantprod;
pA=fopen("propiedades.dat","rb");
    fseek(pA,0,SEEK_END);
    cantprod=ftell(pA)/sizeof(struct unidades);// calculo la cantidad de productos registrados para el ciclo
    //printf("Fecha de\t\t\t\t\t\t\t\tSuperficie\tSuperficie\t\t\t\t\t\t\t\t\t\tFecha de");
    printf("|ID  |ingreso     |Zona      |Ciudad    |Dormitorios |Baños |total    |cubierta |Precio      |Moneda  |Tipo  |Operacion |salida |Activo\n");
    fseek(pA,0,SEEK_SET);
    while( i < cantprod ){
        fseek(pA,i*sizeof(struct unidades),SEEK_SET);
        fread(&prop,sizeof(struct unidades),1,pA);
        printf("|%-4d|%d/%d/%-7d|%-10s|%-10s|%-12d|%-6d|%-9.2f|%-9.2f|%-12.2f|%-8s|%-6s|%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        i++;
        printf("\n");
   }
printf("\n\n");
fclose(pA);
}

//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

int main() {
    int MenuInicio =1;      // Establece el primer numero del menu
    int MenuFin =5;	        // Establece último numero del menu
    int LineaDeInicio = 2;  // Establece la linea donde empieza el menu
    FILE * pArchivo;        //creamos la variable archivo


    do{
    system("cls"); //limpiamos pantalla
	int Menu; //Variable que sirve para saber en que numero de menu estamos

	printf("Seleccione una opcion moviendose con las flechas direccionales del teclado y presione enter para continuar");
	// ir a la linea de inicio, DEBE ir antes del menu seleccionable
	goy(LineaDeInicio);
	printf("\t1. Crear el archivo propiedades.dat\n");
	printf("\t2. Ingresar un nuevo inmueble\n");
	printf("\t3. Cargar/Mostrar Lista de propiedades\n");
	printf("\t4. Descripcion de la opcion 4\n");
	printf("\t5. Salir\n");

	Menu = 1;
	goy(LineaDeInicio);
	printf("---->");

	while(1) {
		// Retrasar el ciclo un poco
		Sleep(100);
		// Saber si la flecha de arriba fue pulsada
		if (GetAsyncKeyState(VK_UP)) {
			// Si Menu == 1, Menu = MenuFin, sino, Menu = Menu -1
			Menu = Menu == MenuInicio ? MenuFin : --Menu;
			// Eliminar la flecha actual
			printf("\r     ");
			// Ir a la linea del próximo menu
			goy(LineaDeInicio + Menu-1);
			// Poner la nueva flecha
			printf("---->");
		} else if (GetAsyncKeyState(VK_DOWN)) {
			Menu = Menu == MenuFin ? MenuInicio: ++Menu;
			printf("\r     ");
			goy(LineaDeInicio + Menu-1);
			printf("---->");
		} else if (GetAsyncKeyState(VK_RETURN)) {
			break;
		}
	}
	//Si elijo (5):salir, finalizo el programa.
    if (Menu == 5){
            goy(10);
            printf("Programa terminado\n\n");
            system("pause");
            return 0;
    }
	// Me muevo hacia un espacio donde pueda imprimir los demas datos de la opcion seleccionada
	goy(10);
	printf("Has seleccionado la opcion %d\n\n", Menu);

	switch (Menu) {
        case 1:crearStock(pArchivo);
               break;
        case 2:productoNuevo(pArchivo);
               break;
        case 3:Lista(pArchivo);
               break;
        case 4:printf("Cuatro");
               break;
        case 5:printf("Cinco");
               break;
        default:
            printf("El valor esta fuera de rango");
        }
    printf("\n");
	system("pause");
	}while(1);

//Fin de main

}
