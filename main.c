#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#define anioactual 2023

void error(int num_err)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	char *errores[] = {
/* 0 */	"Error 0: Valor ingresado fuera de rango",
/* 1 */ "Error 1: Tipo de dato ingresado incorrecto",
/* 2 */ "Error 2: El archivo no existe",
/* 3 */ "Error 3: El archivo ya existe",
/* 4 */ "Error 4: El dato ingresado ya existe",
/* 5 */ "Error 5: El dato ingresado no existe",
/* 6 */ "Error 6: String fuera de rango"
		};
    SetConsoleTextAttribute(hConsole,12); //rojo
	printf( "%s",errores[num_err] );
    SetConsoleTextAttribute(hConsole,7);//base
    sleep(1);
}
void fechaHoy(int *dia, int *mes, int *anio) {
    time_t tiempo;
    struct tm *tiempoInfo;

    time(&tiempo);
    tiempoInfo = localtime(&tiempo);

    *dia = tiempoInfo->tm_mday;
    *mes = tiempoInfo->tm_mon + 1;
    *anio = tiempoInfo->tm_year + 1900;
}

void limpiarTeclado(){
    while (GetAsyncKeyState(VK_RETURN) & 0x8000) {
    // Descartar pulsaciones de tecla de Enter
}}

void limpiarBuffer(){
while (getchar() != '\n');
//eliminamos todo lo que haya en el buffer y escriba nada despues del enter en el menu
}

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

// ir a una línea determinada en pantalla
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
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    fflush(stdin);
    pA = fopen("propiedades.dat", "r");
     if (pA == NULL) {
        // El archivo no existe, así que lo creamos
        pA = fopen("propiedades.dat", "w");
        SetConsoleTextAttribute(hConsole,2); //verde
        printf("\nArchivo creado exitosamente\n");
        SetConsoleTextAttribute(hConsole,7);//base
        } else{
        // El archivo existe, lo cerramos
        fclose(pA);
        error(3);
        fflush(stdin);
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
int leido,flag,temp;
//struct fecha fechaHoy;
    pA=fopen("propiedades.dat","r+b");
    if (pA == NULL) {
        // El archivo no existe, salimos
        error(2);
        return 0;
        }
        //Con esto sé el numero maximo del dat hasta este momento
        fseek(pA, 0, SEEK_END);
        int numRegistros = ftell(pA) / sizeof(struct unidades);
    //Limpio cualquier cosa que haya en buffer cuando presioné enter
    fflush(stdin);
    limpiarBuffer();

    do{
    flag=1; //setteamos el flag para que si no se cumple ninguna valid. vuelva a ingresar
    printf("\nIngrese el ID del articulo: ");
    leido = scanf("%d",&temp);
    fflush(stdin);
    if (leido == 1){
    }
    //Si no se ingresa un valor correcto se pide nuevamente
    else{
        while(leido != 1)
	    {
            error(1);
            printf("\nIngrese el ID del articulo: ");
            leido = scanf("%d",&temp);
            fflush(stdin);
            }
    	}
    if (temp<0 || temp >= 1000){
            flag=1;
            error(0);
    }else{
            if (temp > numRegistros){
                flag=0;
                }else{
                fseek(pA,(temp-1)*sizeof(struct unidades),SEEK_SET);
                fread(&prop,sizeof(struct unidades),1,pA);
                flag = (prop.id==0 ? 0 : (flag = (prop.activo==0 ? 0 : 1)));
		if (flag==1){error(4);};
                     }
         }
    }while(flag==1);
     prop.id=temp;
    //ingresamos mes primero para que le día no se pase de rango luego
    do{
    printf("Ingrese el mes: ");
    leido=scanf("%d",&prop.mes);
    fflush(stdin);
    if (leido == 1){
    }
    //Se valida que mes, dia y año sean valores numéricos y no esten fuera de rango
    else{
        while(leido != 1){
            error(1);
            printf("\nIngrese el mes: ");
            leido = scanf("%d",&prop.mes);
            fflush(stdin);
        }
    }

    if(prop.mes <= 0 || prop.mes > 12){
        error(0);
        printf("\n");
        ;}

    }while(prop.mes <= 0 || prop.mes > 12);

    int veodia = corroborar(prop.mes); //devuelvo a veodia el numero de mes para comparar en el siguiente

    do{
    printf("Ingrese el dia: ");
    leido = scanf("%d",&prop.dia);
    fflush(stdin);
     if (leido == 1){
    }
    else{
        while(leido != 1){
            error(1);
            printf("\nIngrese el dia: ");
            leido = scanf("%d",&prop.dia);
            fflush(stdin);
        }
    }

    if (prop.dia<0 || prop.dia>veodia) {
            error(0);
            printf("\n");
            }
    }while(prop.dia>veodia || prop.dia < 0);

    printf("El A%co que sera ingresado es: %d",164,anioactual);
    prop.anio=anioactual;

    //Se pide el ingreso de datos para una nueva propiedad

    //-----------------------------Zona------------------------------------------------//
    printf("\n----------Zonas----------\n");
    printf("1- Capital Federal \n");
    printf("2- Bs.As. G.B.A. Zona Sur \n");
    printf("3- Bs.As. G.B.A. Zona Norte \n");
    printf("4- Bs.As. G.B.A. Zona Este \n");
    printf("5- Bs.As. G.B.A. Zona Oeste \n");
    printf("--------------------------\n");
    printf("Ingrese la Zona del articulo: ");
    scanf("%d",&leido);
    fflush(stdin);
    if (leido<=0 || leido>5 ){ //Validación de Zona
        while (leido<=0 || leido>5 ){
        error(0);
        printf("\nIngrese la Zona del articulo: ");
        scanf("%d",&leido);
        fflush(stdin);
        }
    }
    switch(leido){ //Switch para elegir la zona por opciones y minimizar el error
        case 1:
        strcpy(prop.zona,"Capital Federal ");
        break;
    case 2:
        strcpy(prop.zona,"Bs.As.Zona Sur  ");
        break;
    case 3:
        strcpy(prop.zona,"Bs.As.Zona Norte");
        break;
    case 4:
        strcpy(prop.zona,"Bs.As.Zona Este ");
        break;
    case 5:
        strcpy(prop.zona,"Bs.As.Zona Oeste");
        break;
    }

//----------------------------------------Ciudad-----------------------------------------------------//
    printf("Ingrese la Ciudad del articulo: ");
    fgets(prop.ciudad, sizeof(prop.ciudad), stdin);
    fflush(stdin);
    int contador;
    int longitud = strlen(prop.ciudad);
    if (longitud > 0 && prop.ciudad[longitud - 1] == '\n') {
    prop.ciudad[longitud - 1] = '\0'; // Reemplaza el \n con el carácter nulo \0
    }
    while(prop.ciudad==NULL || longitud > 17 || longitud <= 1){ //Validación
    error(6);
    printf("\nIngrese la Ciudad del articulo: ");
    fgets(prop.ciudad, sizeof(prop.ciudad), stdin);
    fflush(stdin);
    longitud = strlen(prop.ciudad);
    if (longitud > 0 && prop.ciudad[longitud - 1] == '\n') {
    prop.ciudad[longitud - 1] = '\0'; // Reemplaza el \n con el carácter nulo \0
    }
    }
    while (isalpha(prop.ciudad[0]==0)){ //Para verificar que se haya ingresado una letra por lo menos
    error(1);
    printf("\nIngrese la Ciudad del articulo: ");
    fgets(prop.ciudad, sizeof(prop.ciudad), stdin);
    fflush(stdin);
    }
    for(contador=0; prop.ciudad[contador]!='\0' ; contador++){ //Para convertir cualquier cadena que se ingrese, en la primera mayuscula, el resto minusculas
    if(contador==0){
    prop.ciudad[contador] = toupper(prop.ciudad[contador]);
    }
    else{
    prop.ciudad[contador] = tolower(prop.ciudad[contador]);
    }
    }
//---------------------------------------Cantidad de Dormitorios------------------------------------------------------//

    printf("Ingrese la cantidad de Dormitorios del articulo: ");
    leido = scanf("%d",&prop.dormitorios);
    fflush(stdin);
     if (leido == 1){
    }
    else{
        while(leido != 1){ //Validación
            error(1);
             printf("\nIngrese la cantidad de Dormitorios del articulo: ");
            leido = scanf("%d",&prop.dormitorios);
            fflush(stdin);
        }
    }
    while(prop.dormitorios<0 || prop.dormitorios > 999){ //Validación
    error(0);
    printf("\nIngrese la cantidad de Dormitorios del articulo: ");
    scanf("%d",&prop.dormitorios);
    }
//---------------------------Cantidad de baños-------------------------//
    printf("Ingrese la cantidad de ba%cos del articulo: ",164);
    leido = scanf("%d",&prop.banios);
    fflush(stdin);
      if (leido == 1){
    }
    else{
        while(leido != 1){ //Validación
            error(1);
            printf("\nIngrese la cantidad de ba%cos del articulo: ",164);
            leido = scanf("%d",&prop.banios);
            fflush(stdin);
        }
    }
    while(prop.banios<0 || prop.banios > 999){ //Validación
    error(0);
    printf("\nIngrese la cantidad de ba%cos del articulo: ",164);
    scanf("%d",&prop.banios);
    }
//----------------------Superficie total-----------------------------------------------//
    printf("Ingrese la superficie total del articulo: ");
    leido = scanf("%f",&prop.superficieT);
    fflush(stdin);
        if (leido == 1){
    }
    else{
        while(leido != 1){ //Validación
            error(1);
            printf("\nIngrese la superficie total del articulo: ");
            leido = scanf("%d",&prop.superficieT);
            fflush(stdin);
        }
    } //Validación
    while(prop.superficieT<=0 || prop.superficieT > 999999){
    error(0);
    printf("Ingrese la superficie total del articulo: ");
    scanf("%f",&prop.superficieT);
    }
//--------------------------Superficie cubierta ---------------------------//
    printf("Ingrese la superficie cubierta del articulo: ");
    leido = scanf("%f",&prop.superficieC);
    fflush(stdin);
        if (leido == 1){
    }
    else{ //Validación
        while(leido != 1){
            error(1);
            printf("\nIngrese la superficie cubierta del articulo: ");
            leido = scanf("%d",&prop.superficieC);
            fflush(stdin);
        }
    }
    while(prop.superficieC<=0 || prop.superficieC > 999999){ //Validación
    error(1);
    printf("\nIngrese la superficie cubierta del articulo: ");
    scanf("%f",&prop.superficieC);
    }
//--------------------------Precio-------------------------------------------//
    printf("Ingrese el precio del articulo: ");
    leido = scanf("%f",&prop.precio);
    fflush(stdin);
        if (leido == 1){
    }
    else{ //Validación
        while(leido != 1){
            error(1);
            printf("\nIngrese el precios del articulo: ");
            leido = scanf("%d",&prop.precio);
            fflush(stdin);
        }
    }
    while(prop.precio<=0 || prop.precio>=1000000){ //Validación
    error(0);
    printf("\nIngrese el precio del articulo: ");
    scanf("%f",&prop.precio);
    }
//---------------------------------Tipo de moneda --------------------------//
    printf("- - - - - - - - - - \n");
    printf("--Tipos de monedas--\n");
    printf("1- USD \n");
    printf("2- PESOS \n");
    printf("--------------------\n");
    printf("Ingrese el tipo de moneda del articulo: ");
    scanf("%d",&leido);
    fflush(stdin);
    if (leido<=0 || leido>2 ){ //Validación
        while (leido<=0 || leido>2 ){
        error(0);
        printf("\nIngrese el tipo de moneda del articulo: ");
        scanf("%d",&leido);
        fflush(stdin);
        }
    }
    switch(leido){ //Opciones de moneda para minimizar el error
        case 1:
        strcpy(prop.moneda,"USD  ");
        break;
    case 2:
        strcpy(prop.moneda,"PESOS");
        break;
    }
//------------------------------------Tipo de propiedad ------------------------------------//
    printf("- - - - - - - - - - - - - \n");
    printf("--Tipos de propiedades--\n");
    printf("1- Departamento \n");//Opciones
    printf("2- PH \n");
    printf("3- Casa \n");
    printf("------------------------\n");
    printf("Ingrese el tipo de la propiedad del articulo: ");
    scanf("%d",&leido);
    fflush(stdin);
    if (leido<=0 || leido>3 ){ //Validación
        while (leido<=0 || leido>3 ) {
        error(0);
        printf("\nIngrese el tipo de la propiedad del articulo: ");
        scanf("%d",&leido);
        fflush(stdin);
        }

    }
    switch(leido){ //Switch para validar las opciones y minimizar el error
        case 1:
        strcpy(prop.tipo,"Departamento");
        break;
    case 2:
        strcpy(prop.tipo,"PH          ");
        break;
    case 3:
        strcpy(prop.tipo,"Casa        ");
        break;
    }

//-------------------------- Tipo de operacion----------------------------------//
    //Opciones
    printf("- - - - - - - - - - - - - -\n");
    printf("---Tipo de Operaciones---\n");
    printf("1- Venta \n");
    printf("2- Alquiler \n");
    printf("3- Alquiler Temporal\n");
    printf("-------------------------\n");
    printf("Ingrese el tipo de Operacion del articulo: ");
    scanf("%d",&leido);
    fflush(stdin);
    //Validación
    if (leido<=0 || leido>3 ){
        while (leido<=0 || leido>3 ) {
        error(0);
        printf("\nIngrese el tipo de Operacion del articulo: ");
        scanf("%d",&leido);
        fflush(stdin);
        }

    }
    //Switch para validar opciones y minimizar el error
    switch(leido){
        case 1:
        strcpy(prop.operacion,"Venta            ");
        break;
    case 2:
        strcpy(prop.operacion,"Alquiler         ");
        break;
    case 3:
        strcpy(prop.operacion,"Alquiler Temporal");
        break;
    }
    //Se da de alta la propiedad
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
void listaBaja(){
        FILE *pA;
    pA=fopen("baja.xyz","rb");
    if(pA == NULL){
        printf("\n\nEl archivo no existe\n");
        return;
    }
    struct unidades prop;
    fseek(pA,0,SEEK_END);
    int cantprod=ftell(pA)/sizeof(struct unidades);// calculo la cantidad de productos registrados para el ciclo
    int i;
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|ID |ingreso   |Zona            |Ciudad          |Dormitorios|Ba%cos|total |cubierta|Precio   |Moneda|Tipo        |Operacion        |salida    |Activo\n",164);
    fseek(pA,0,SEEK_SET);
    while( i < cantprod ){
        fseek(pA,i*sizeof(struct unidades),SEEK_SET);
        fread(&prop,sizeof(struct unidades),1,pA);
        if (prop.id == 0){
        printf("|0  |0         |0               |0               |0          |0    |0     |0       |0        |0     |0           |0                |0         |      ");
        }else{
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        if (prop.anio == 0){printf("0000");}else{printf("%d|",prop.anio);}
        printf("%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        }
        i++;
        printf("\n");
   }    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
fclose(pA);


}
//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

// 3.1-Muestra la lista de las propiedades del archivo pArchivo//

void Lista(FILE *pA){
struct unidades prop;
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);   //////////////////////////comando color
 int i=0, cantprod;
pA=fopen("propiedades.dat","rb");
    fseek(pA,0,SEEK_END);
    cantprod=ftell(pA)/sizeof(struct unidades);// calculo la cantidad de productos registrados para el ciclo
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|ID |ingreso   |Zona            |Ciudad          |Dormitorios|Ba%cos|total |cubierta|Precio   |Moneda|Tipo        |Operacion        |salida    |Activo\n",164);
    fseek(pA,0,SEEK_SET);
    while( i < cantprod ){
	SetConsoleTextAttribute(hConsole,7);                /////////////////////////color
        fseek(pA,i*sizeof(struct unidades),SEEK_SET);
        fread(&prop,sizeof(struct unidades),1,pA);
        if (prop.id == 0){
	SetConsoleTextAttribute(hConsole,8);
    printf("|0  |0         |0               |0               |0          |0    |0     |0       |0        |0     |0           |0                |0         |      ");
        }else{
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        if (prop.anio == 0){printf("0000");}else{printf("%d|",prop.anio);}
        printf("%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        }
        i++;
        printf("\n");
   }
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
fclose(pA);
}



//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

// 3.2-Muestra la lista de las propiedades del archivo pArchivo (Solo los Activos)//

void soloActivos(FILE *pA){
struct unidades prop;
pA=fopen("propiedades.dat","rb");
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|ID |ingreso   |Zona            |Ciudad          |Dormitorios|Ba%cos|total |cubierta|Precio   |Moneda|Tipo        |Operacion        |salida    |Activo\n",164);
    while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.activo==1){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
   }
   }
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
fclose(pA);
}

//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//
//Funciones que usamos para hacer una busqueda dependiendo de la opcion que se elija.
//Por Operativo
int Operativo(){
int numero;
printf("Operativo:\n");
printf("1- Venta \n");
printf("2- Alquiler \n");
printf("3- Alquiler Temporal\n");
scanf("%d",&numero);
if (numero<=0 || numero>3 ){
while (numero<=0 || numero>3 ){
printf("Ingreso un valor fuera del rango\n");
printf("Ingrese la Zona del articulo: \n");
scanf("%d",&numero);
fflush(stdin);
}}
return numero;
}
//Por tipo
int Tipo(){
int numero;
printf("Tipo:\n");
printf("1- Departamento \n");
printf("2- PH \n");
printf("3- Casa \n");
scanf("%d",&numero);
if (numero<=0 || numero>3 ){
while (numero<=0 || numero>3 ){
printf("Ingreso un valor fuera del rango\n");
printf("Ingrese la Zona del articulo: \n");
scanf("%d",&numero);
fflush(stdin);
}}
return numero;
}
//Por Moneda
int Moneda(){
int numero;
printf("Moneda:\n");
printf("1- USD \n");
printf("2- PESOS \n");
scanf("%d",&numero);
if (numero<=0 || numero>2 ){
while (numero<=0 || numero>2 ){
printf("Ingreso un valor fuera del rango\n");
printf("Ingrese la Zona del articulo: \n");
scanf("%d",&numero);
fflush(stdin);
}}
return numero;
}
//Por zona
int Zona(){
int numero;
printf("Zona:\n");
printf("1- Capital Federal \n");
printf("2- Bs.As. G.B.A. Zona Sur \n");
printf("3- Bs.As. G.B.A. Zona Norte \n");
printf("4- Bs.As. G.B.A. Zona Este \n");
printf("5- Bs.As. G.B.A. Zona Oeste \n");
scanf("%d",&numero);
if (numero<=0 || numero>5 ){
while (numero<=0 || numero>5 ){
printf("Ingreso un valor fuera del rango\n");
printf("Ingrese la Zona del articulo: \n");
scanf("%d",&numero);
fflush(stdin);
}}
return numero;
}

//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

//Funcion para solo ingresar los valores tipo Float//
int busquedaFloat(int i){
float variable;
switch (i) {
    case 6:
        printf("Superficie Total:");
        scanf("%f",&variable);
        break;
    case 7:
        printf("Superficie Cubierta:");
        scanf("%f",&variable);
        break;
    case 8:
        printf("Precio:");
        scanf("%f",&variable);
        break;
    }
return variable;
}

//Funcion para solo ingresar los valores tipo Int//
int busquedaInt(int i){
int numero;
switch (i) {
    case 1:
        printf("ID:");
        scanf("%d",&numero);
        break;
    case 4:
        printf("Dormitorios:");
        scanf("%d",&numero);
        break;
    case 5:
        printf("Ba%cos:",164);
        scanf("%d",&numero);
        break;
    }
return numero;
}

//Creo una funcion para solo establecer el numero del tipo de variable a pedir
//Asi sabre de ante mano que tipo de valor tendre que usar al comparar//

int ingresoProp(){
int i;
printf("1.- ID\n");
printf("2.- Zona\n");
printf("3.- Ciudad\n");
printf("4.- Dormitorios\n");
printf("5.- Ba%cos\n",164);
printf("6.- total de la Superficie\n");
printf("7.- cubierta de la Superficie\n");
printf("8.- Precio\n");
printf("9.- Moneda\n");
printf("10.- Tipo\n");
printf("11.- Operacion\n");
printf("Ingrese el tipo de propiedad a buscar: ");
scanf("%d",&i);
while(i<=0 && i>11){
printf("Esa no es no opcion, ingrese de nuevo\n");
printf("Ingrese el tipo de propiedad a buscar: \n");
scanf("%d",&i);
}
return i;
}

//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

// 3.3-Muestra la lista de las propiedades del archivo pArchivo (Filtrada por la propiedad pedida)//

void propiedadPedida(FILE *pA){
struct unidades prop;
pA=fopen("propiedades.dat","rb");

    if (pA == NULL) {
        // El archivo no existe, salimos
        printf("El archivo propiedades no existe\n");
        return 0;
        }
fflush(stdin);
limpiarBuffer();
int seleccion_char;
int seleccion=ingresoProp(); //Hago un pedido para saber cual tipo de variable compararemos
int identificadorInt; //Creo una variable especifica para los valores tipo int
float identificadorFloat; //Creo una variable especifica para los valores tipo float
char letras[50]; //Creo una variable especifica para los valores tipo char (Cadena)
 if (seleccion ==1 || seleccion ==4 || seleccion ==5){
identificadorInt=busquedaInt(seleccion); //Si quiere un Int, serian la opcion 1,4,5
} else if (seleccion ==6 || seleccion ==7 || seleccion ==8){
identificadorFloat=busquedaFloat(seleccion); //Si quiere un float, serian la opcion 6,7,8
} else {  //Si quiere un char, serian la opcion 2,3,9,10,11
 switch (seleccion){
    case 2:
        seleccion_char=Zona();
        break;
    case 3:
        fflush( stdin );
        printf("Ciudad:");
        fgets(letras,50, stdin);
        break;
    case 9:
        seleccion_char=Moneda();
        break;
    case 10:
        seleccion_char=Tipo();
        break;
    case 11:
        seleccion_char=Operativo();
        break;
    }
}
printf("\n");
printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
printf("|ID |ingreso   |Zona            |Ciudad          |Dormitorios|Ba%cos|total |cubierta|Precio   |Moneda|Tipo        |Operacion        |salida    |Activo\n",164);
switch (seleccion) {
    case 1:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.id==identificadorInt){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 2:
        switch (seleccion_char){
            case 1 : //Cuando se quiera imprimir solo los de Capital federal
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.zona,"Capital Federal ") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
            case 2 : //Cuando se quiera imprimir solo los de Bs.As.Zona Sur
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.zona,"Bs.As.Zona Sur  ") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
            case 3 : //Cuando se quiera imprimir solo los de Bs.As.Zona Norte
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.zona,"Bs.As.Zona Norte") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
            case 4 : //Cuando se quiera imprimir solo los de Bs.As.Zona Este
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.zona,"Bs.As.Zona Este ") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
            case 5 : //Cuando se quiera imprimir solo los de Bs.As.Zona Oeste
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.zona,"Bs.As.Zona Oeste") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
        }
        break;
    case 3:
        letras[strcspn(letras, "\n")] = '\0';
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.ciudad,letras) == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 4:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.dormitorios==identificadorInt){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 5:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.banios==identificadorInt){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 6:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.superficieT==identificadorFloat){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 7:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.superficieC==identificadorFloat){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 8:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.precio==identificadorFloat){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 9: //Cuando se quiera imprimir solo los USD
        switch (seleccion_char){
            case 1 :
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.moneda,"USD  ") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
            case 2 : //Cuando se quiera imprimir solo los Pesos
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.moneda,"PESOS") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
        }
        break;
    case 10:
        switch (seleccion_char){
            case 1 : //Cuando se quiera imprimir solo los Departamentos
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.tipo,"Departamento") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
            case 2 : //Cuando se quiera imprimir solo los PH
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.tipo,"PH          ") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
            case 3 : //Cuando se quiera imprimir solo las Casas
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.tipo,"Casa        ") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
        }
        break;
    case 11:
        switch (seleccion_char){
            case 1 : //Cuando se quiera imprimir solo las de Venta
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.operacion,"Venta            ") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
            case 2 : //Cuando se quiera imprimir solo las de Alquiler
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.operacion,"Alquiler         ") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
            case 3 : //Cuando se quiera imprimir solo las de Alquiler Temporal
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.operacion,"Alquiler Temporal") == 0){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
        }
   }

printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
fclose(pA);
}

//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

// 3.4-Muestra la lista de las propiedades del archivo pArchivo (Segun un rango de tiempo)//

void rangoTiempo(FILE *pA){
struct unidades prop;
pA=fopen("propiedades.dat","rb");
int dia,mes,anio;
fflush(stdin);
limpiarBuffer();
printf("ingrese el dia:");
scanf(" %d", &dia);
printf("ingrese el mes:");
scanf(" %d", &mes);
printf("ingrese el a%co:",164);
scanf(" %d", &anio);
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|ID |ingreso   |Zona            |Ciudad          |Dormitorios|Ba%cos|total |cubierta|Precio   |Moneda|Tipo        |Operacion        |salida    |Activo\n",164);
    while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.dia<=dia && prop.mes <= mes && prop.anio <= anio && prop.activo==1){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");}
        if(prop.dia>dia && prop.mes < mes && prop.anio <= anio && prop.activo==1){
        printf("|%-3d|",prop.id);
        if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
        if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");;
        }
   }
   }
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
fclose(pA);
}

//------------------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------------------//

//3- Menu de filtros para mostrar la lista de las propiedades del archivo pArchivo//

void menulistas(FILE *pA,int MenuInicio,int MenuFin,int LineaDeInicio){
    pA=fopen("propiedades.dat","rb");
    if (pA == NULL) {
        // El archivo no existe, salimos
        printf("El archivo propiedades no existe\n");
        return 0;
        }
    MenuInicio =1;
    MenuFin =5;
    LineaDeInicio =13;

	int Menu;
	goy(11);
	printf("///////////////////////////////////////////////////////////////////////////////////");
	goy(LineaDeInicio);
	printf("\t1.- Mostrar lista completa (Incluyendo Activos e Inactivos)\n");
	printf("\t2.- Mostrar solo los Activos\n");
	printf("\t3.- Mostrar por un Tipo especifico\n");
	printf("\t4.- Mostrar por un rango de tiempo\n");
	printf("\t5.- Mostrar dados de baja\n");
    fflush(stdin);
	Menu = 1;
	goy(LineaDeInicio);
	printf("---->");
    while(1) {
		Sleep(100);
		if (GetAsyncKeyState(VK_UP)) {
			Menu = Menu == MenuInicio ? MenuFin : --Menu;
			printf("\r     ");
			goy(LineaDeInicio + Menu-1);
			printf("---->");
		} else if (GetAsyncKeyState(VK_DOWN)) {
			Menu = Menu == MenuFin ? MenuInicio: ++Menu;
			printf("\r     ");
			goy(LineaDeInicio + Menu-1);
			printf("---->");
		} else if (GetAsyncKeyState(VK_RETURN)){break;}}

        goy(17);
		switch (Menu) {
        case 1:
          //  printf("Has seleccionado la opcion 1\n");
            Lista(pA);
            break;
        case 2:
          //  printf("Has seleccionado la opcion 2\n");
            soloActivos(pA);
            break;
        case 3:
           // printf("Has seleccionado la opcion 3\n");
            propiedadPedida(pA);
            break;
        case 4:
            //printf("Has seleccionado la opcion 4\n");
            rangoTiempo(pA);
            break;
        case 5:
            listaBaja();
        }
        fflush(stdin);
        limpiarTeclado();

}
//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

// 4- baja logica de una propiedad
void bajaLogica(FILE * pA){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
struct unidades prod;
int art;//=leerArt();
char opcion;
pA=fopen("propiedades.dat","r+b");

    if (pA == NULL) {
        // El archivo no existe, salimos
        printf("El archivo propiedades no existe\n");
        return 0;
        }
    fflush(stdin);
    limpiarBuffer();
    printf("ingrese el ID: ");
    scanf("%d", &art);
    fseek(pA,0,SEEK_SET);
    fseek(pA,(art-1)*sizeof(struct unidades ),SEEK_SET);
    fread(&prod,sizeof(struct unidades ),1,pA);
    if( prod.activo == 0){
     SetConsoleTextAttribute(hConsole,4); //rojo      
     printf("La propiedad ya estaba dada de baja \n");
     SetConsoleTextAttribute(hConsole,7); //verde
     fclose(pA);
     return;
    }
    printf("Usted dar%c de baja a:\n", 160);
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|ID |ingreso   |Zona            |Ciudad          |Dormitorios|Ba%cos|total |cubierta|Precio   |Moneda|Tipo        |Operacion        |salida    |Activo\n",164);
    printf("|%-3d|",prod.id);
    if (prod.dia < 10){printf("0%d/",prod.dia);}else{printf("%d/",prod.dia);}
    if (prod.mes < 10){printf("0%d/",prod.mes);}else{printf("%d/",prod.mes);}
    printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prod.anio,prod.zona,prod.ciudad,prod.dormitorios,prod.banios,prod.superficieT,prod.superficieC,prod.precio,prod.moneda,prod.tipo,prod.operacion,prod.activo);
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Esta seguro de que quiere darla de baja? Ingrese 'S' para si o 'N' para no ");
    opcion = getchar();
    opcion = toupper(opcion);
    while (opcion != 'S' && opcion != 'N'){
        printf("ingrese una opcion valida \n");
        opcion = getchar();
        opcion = toupper(opcion);
    }
    if(opcion == 'N'){
       return;}
    else{
    prod.activo = 0;
    fseek(pA,-sizeof(struct unidades),SEEK_CUR);
    fwrite(&prod,sizeof(struct unidades),1,pA);
SetConsoleTextAttribute(hConsole,2); //verde
printf("\n***--El producto %d se dio de baja correctamente--***\n", art);}
SetConsoleTextAttribute(hConsole,7); //base
printf("\n\n");
printf("Asi quedo la lista actualizada \n");
struct unidades prop;
int i=0, cantprod;
    fseek(pA,0,SEEK_END);
    cantprod=ftell(pA)/sizeof(struct unidades);// calculo la cantidad de productos registrados para el ciclo
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|ID |ingreso   |Zona            |Ciudad          |Dormitorios|Ba%cos|total |cubierta|Precio   |Moneda|Tipo        |Operacion        |salida    |Activo\n",164);
    fseek(pA,0,SEEK_SET);
    while( i < cantprod ){
        fseek(pA,i*sizeof(struct unidades),SEEK_SET);
        fread(&prod,sizeof(struct unidades),1,pA);
        if(prod.activo == 1 ){
        printf("|%-3d|",prod.id);
        if (prod.dia < 10){printf("0%d/",prod.dia);}else{printf("%d/",prod.dia);}
        if (prod.mes < 10){printf("0%d/",prod.mes);}else{printf("%d/",prod.mes);}
        printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prod.anio,prod.zona,prod.ciudad,prod.dormitorios,prod.banios,prod.superficieT,prod.superficieC,prod.precio,prod.moneda,prod.tipo,prod.operacion,prod.activo);
        printf("\n");
        }
        i++;
   }
printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
printf("\n\n");
fclose(pA);
}

//------------------------------------------------------------------------------------------------------------//

// 6- Modificar una propiedad
void Modificarpropiedad(FILE * pA){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
struct unidades prop;
int id,opcion,numero,validacion;
pA=fopen("propiedades.dat","r+b");
fseek(pA, 0, SEEK_END);                                 //    calculamos el total
int numRegistros = ftell(pA) / sizeof(struct unidades); //    de ID's para saber si existe en el dat, sino sale.
fflush(stdin);
limpiarBuffer();
printf("Ingrese el ID a buscar: ");
scanf("%d",&id);
fflush(stdin);
//Corroboramos que exista dicho ID
//Si está fuera de rango, salimos. Sino vamos a la linea donde se encuentra
if (id > numRegistros){
    printf("El ID no existe");
    return;
    }else{
    fseek(pA,(id-1)*sizeof(struct unidades),SEEK_SET);
    fread(&prop,sizeof(struct unidades),1,pA);
    if(prop.id==0){return;}
    }

printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
printf("|ID |ingreso   |Zona            |Ciudad          |Dormitorios|Ba%cos|total |cubierta|Precio   |Moneda|Tipo        |Operacion        |salida    |Activo\n",164);
printf("|%-3d|",prop.id);
if (prop.dia < 10){printf("0%d/",prop.dia);}else{printf("%d/",prop.dia);}
if (prop.mes < 10){printf("0%d/",prop.mes);}else{printf("%d/",prop.mes);}
printf("%d|%s|%-16s|%-11d|%-4d |%-5.1f |%-7.1f |%-8.1f |%-4s |%s|%-9s|          |%d",prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
printf("\n");
printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
printf("Que valor quiere modificar:\n");
printf("1-Ciudad\n");
printf("2-Precio\n");
scanf("%d",&opcion);
fflush(stdin);
while (opcion<1 || opcion>2){
        printf("Ingreso Invalido, eliga una de las opciones mostradas\n");
        printf("Que valor quiere modificar:\n");
        printf("1-Ciudad\n");
        printf("2-Precio\n");
        scanf(" %d", &opcion);
}
printf("Esta seguro que desea modificar los datos\n");
printf("1-Si\n");
printf("2-No\n");
scanf(" %d", &validacion);
fflush(stdin);
if(validacion==1){
  switch(opcion){
    case 1:
    printf("Introduce la nueva ciudad: ");
    fgets(prop.ciudad, sizeof(prop.ciudad), stdin);
    fflush(stdin);
    int contador;
    int longitud = strlen(prop.ciudad);
    if (longitud > 0 && prop.ciudad[longitud - 1] == '\n') {
    prop.ciudad[longitud - 1] = '\0'; // Reemplaza el \n con el carácter nulo \0
    }
    while(prop.ciudad==NULL || longitud > 17 || longitud <= 1){ //Validación
    error(0);
    printf("\nIntroduce La nueva ciudad: ");
    fgets(prop.ciudad, sizeof(prop.ciudad), stdin);
    fflush(stdin);
    longitud = strlen(prop.ciudad);
    if (longitud > 0 && prop.ciudad[longitud - 1] == '\n') {
    prop.ciudad[longitud - 1] = '\0'; // Reemplaza el \n con el carácter nulo \0
    }
    }
    while (isalpha(prop.ciudad[0]==0)){ //Para verificar que se haya ingresado una letra por lo menos
    error(1);
    printf("\nIntroduce La nueva ciudad: ");
    fgets(prop.ciudad, sizeof(prop.ciudad), stdin);
    fflush(stdin);
    }
    for(contador=0; prop.ciudad[contador]!='\0' ; contador++){ //Para convertir cualquier cadena que se ingrese, en la primera mayuscula, el resto minusculas
    if(contador==0){
    prop.ciudad[contador] = toupper(prop.ciudad[contador]);
    }
    else{
    prop.ciudad[contador] = tolower(prop.ciudad[contador]);
    }
    }
    fseek(pA,(prop.id-1)*sizeof(struct unidades),SEEK_SET);
    fwrite(&prop,sizeof(struct unidades),1,pA);
    fflush(stdin);
    break;

    case 2:
    printf("Introduce el nuevo Precio: ");
    numero = scanf("%f",&prop.precio);
    fseek(pA,ftell(pA)-sizeof(struct unidades),SEEK_SET);
    fwrite(&prop, sizeof(struct unidades), 1, pA);
    fflush(stdin);
        if (numero == 1){
    }
    else{ //Validación
        while(numero != 1){
            error(1);
            printf("\nIntroduce el nuevo Precio: ");
            numero = scanf("%d",&prop.precio);
            fflush(stdin);
        }
    }
    while(prop.precio<=0 || prop.precio>=1000000){ //Validación
    error(0);
    printf("\nIntroduce el nuevo Precio:");
    scanf("%f",&prop.precio);
    }
    fseek(pA,0,SEEK_SET);
    fseek(pA,(id-1)*sizeof(struct unidades),SEEK_SET);
    fwrite(&prop, sizeof(struct unidades), 1, pA);
    fflush(stdin);
        break;
        }
}
SetConsoleTextAttribute(hConsole,2); //verde
printf("\n***--El producto %d se modifico correctamente--***\n");
SetConsoleTextAttribute(hConsole,7); //base
printf("\n\n");
fclose(pA);
}
//------------------------------------------------------------------------------------------------------------//
void bajaFisica(FILE * pA){
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
int i=0,dia,mes,anio;
struct unidades prop;
fechaHoy(&dia,&mes,&anio);
char viejo[50];
char nuevo[50]; // Suficientemente grande para "dd_mm_aaaa.xyz"
sprintf(nuevo, "propiedades_baja_%d_%d_%d.xyz", dia, mes, anio); //Guardo la fecha en "nuevo" para el rename
FILE *temp;
FILE *xyz;
FILE *archivoFechaAnterior;

        archivoFechaAnterior = fopen("fecha.txt", "r");
    if (archivoFechaAnterior != NULL) {
        fgets(viejo, sizeof(viejo), archivoFechaAnterior);
        fclose(archivoFechaAnterior);
    } else {
        archivoFechaAnterior = fopen("fecha.txt","w");
        fprintf(archivoFechaAnterior, "%s", nuevo);
        fclose(archivoFechaAnterior);
        strcpy(viejo, nuevo);
    }
    pA=fopen("propiedades.dat","rb");
    xyz = fopen(viejo,"r+b");
    if (xyz == NULL ) {
        xyz = fopen(viejo,"w+b");
    }
    temp=fopen("stock.temp","w+b");
    fseek(pA,0,SEEK_END);
    int cantprod=ftell(pA)/sizeof(struct unidades);// calculo la cantidad de productos registrados para el ciclo

    while ( i<cantprod ){
        fseek(pA,i*sizeof(struct unidades),SEEK_SET);
        fread(&prop,sizeof(struct unidades),1,pA);
        if(prop.activo == 1){
            fseek(temp,i*sizeof(struct unidades),SEEK_SET);
            fwrite(&prop,sizeof(struct unidades),1,temp);
        }else{ if (prop.activo == 0){
            fseek(xyz,i*sizeof(struct unidades),SEEK_SET);
            fwrite(&prop,sizeof(struct unidades ),1,xyz);
        }
        }
     i++;
    }
    fclose(temp);
    fclose(pA);
    fclose(xyz);
    //Le damos un momento al sistema para que cierre bien los archivos antes de hacer un rename/remove
    printf("\n---->   Cargando informacion, aguarde un momento");
    for (int x=0; x<3; x++ ){
        sleep(2);
        printf(".");
    }
// Ahora eliminar y renombrar los archivos
if (remove("propiedades.dat") == 0) {
    SetConsoleTextAttribute(hConsole,2); //verde
    printf("\n\nArchivo propiedades.dat eliminado correctamente.");
    SetConsoleTextAttribute(hConsole,7); //base
} else {
    SetConsoleTextAttribute(hConsole,4); //rojo
    perror("\n\nError al eliminar propiedades.dat\n");
    SetConsoleTextAttribute(hConsole,7); //base
    // Manejar el error según sea necesario
}

if (rename("stock.temp", "propiedades.dat") == 0) { //veo si me lo renombro
    SetConsoleTextAttribute(hConsole,2); //verde
    printf("\n\nArchivo .dat renombrado correctamente.\n\n");
    SetConsoleTextAttribute(hConsole,7); //base
} else {
    SetConsoleTextAttribute(hConsole,4); //rojo
    perror("\n\nError al renombrar el archivo .dat");
    SetConsoleTextAttribute(hConsole,7); //base
    // Manejar el error según sea necesario
}

remove("stock.temp");
SetConsoleTextAttribute(hConsole,2); //verde
printf("***--Archivo actualizado--***\n");
SetConsoleTextAttribute(hConsole,7); //base
}

//------------------------------------------------------------------------------------------------------------//
void PRESENTACION(){
    FILE *f = fopen("banner.txt", "r");
    char c;
            if (f){
	    while((c=fgetc(f)) != EOF){putc(c, stdout);}
            fclose(f);
	    }
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
SetConsoleTextAttribute(hConsole,2);
SetConsoleTextAttribute(hConsole,4);
printf("+-----------------------------------------------------------------------------------------------------------------------------------------------+\n");
printf(" Integrantes:\n");
printf(" Franco Macri\n");
printf(" Ramos Florecia Ayelen\n");
printf(" Elias Serantes\n");
printf(" Johnny Rafael Arvelo Cabrera\n");
printf(" Agustin Bardelli\n");
printf(" Leon Caceres Christian Alexis Osvaldo\n\n");
SetConsoleTextAttribute(hConsole,2);
SetConsoleTextAttribute(hConsole,7);
system ("pause");
}

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);    //comando cambia el color
    int MenuInicio =1;      // Establece el primer numero del menu
    int MenuFin =8;	        // Establece último numero del menu
    int LineaDeInicio = 2;  // Establece la linea donde empieza el menu
    FILE * pArchivo;        //creamos la variable archivo
    PRESENTACION();

    do{
    system("cls"); //limpiamos pantalla
	int Menu; //Variable que sirve para saber en que numero de menu estamos
	printf("Seleccione una opcion moviendose con las flechas direccionales del teclado y presione enter para continuar");
	// ir a la linea de inicio, DEBE ir antes del menu seleccionable
	goy(LineaDeInicio);
	printf("\t1. Crear el archivo propiedades.dat\n");
	printf("\t2. Ingresar un nuevo inmueble\n");
	printf("\t3. Cargar/Mostrar Lista de propiedades\n");
	printf("\t4. Baja logica de una propiedad\n");
	printf("\t5. Buscar propiedad\n");
	printf("\t6. Mofificar una propiedad\n");
	printf("\t7. Baja Fisica\n");
	printf("\t8. Salir\n");
    fflush(stdin);
	Menu = 1;
	goy(LineaDeInicio);
	SetConsoleTextAttribute(hConsole,6);
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
		} else if (GetAsyncKeyState(VK_RETURN)) {break;}

	}
        SetConsoleTextAttribute(hConsole,7);                  //color
	// Me muevo hacia un espacio donde pueda imprimir los demas datos de la opcion seleccionada
	goy(10);
	switch (Menu) {
        case 1:crearStock(pArchivo);
               break;
        case 2:productoNuevo(pArchivo);
               break;
        case 3:menulistas(pArchivo,MenuInicio,MenuFin,LineaDeInicio);
               break;
        case 4:bajaLogica(pArchivo);
               break;
        case 5:propiedadPedida(pArchivo);
               break;
        case 6:Modificarpropiedad(pArchivo);
               break;
        case 7:bajaFisica(pArchivo);
               break;
        case 8:return 0;
               break;
        }
    printf("\n");
    fflush(stdin);
    limpiarTeclado();
	system("pause");
	}while(1);

//Fin de main
}
