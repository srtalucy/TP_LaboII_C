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
    fflush(stdin);
    pA = fopen("propiedades.dat", "r");
     if (pA == NULL) {
        // El archivo no existe, así que lo creamos
        pA = fopen("propiedades.dat", "w");
        } else{
        // El archivo existe, lo cerramos
        fclose(pA);
        printf("El archivo propiedades.dat ya existe\n");
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
    while(prop.zona==NULL){
    printf("Valor invalido\n");
    printf("Ingrese la Zona del articulo: ");
    scanf("%s",&prop.zona);
    }

    printf("Ingrese la Ciudad del articulo: ");
    scanf("%s",&prop.ciudad);
    fflush(stdin);
    while(prop.ciudad==NULL){
    printf("Valor invalido\n");
    printf("Ingrese la Ciudad del articulo: ");
    scanf("%s",&prop.ciudad);
    }

    printf("Ingrese la cantidad de Dormitorios del articulo: ");
    scanf("%d",&prop.dormitorios);
    fflush(stdin);
    while(prop.dormitorios<0){
    printf("Valor invalido\n");
    printf("Ingrese la cantidad de Dormitorios del articulo: ");
    scanf("%d",&prop.dormitorios);
    }

    printf("Ingrese la cantidad de banos del articulo: ");
    scanf("%d",&prop.banios);
    fflush(stdin);
    while(prop.banios<0){
    printf("Valor invalido\n");
    printf("Ingrese la cantidad de banos del articulo: ");
    scanf("%d",&prop.banios);
    }

    printf("Ingrese la superficie total del articulo: ");
    scanf("%f",&prop.superficieT);
    fflush(stdin);
    while(prop.superficieT<=0){
    printf("Valor invalido\n");
    printf("Ingrese la superficie total del articulo: ");
    scanf("%f",&prop.superficieT);
    }

    printf("Ingrese la superficie cubierta del articulo: ");
    scanf("%f",&prop.superficieC);
    fflush(stdin);
    while(prop.superficieC<=0){
    printf("Valor invalido\n");
    printf("Ingrese la superficie cubierta del articulo: ");
    scanf("%f",&prop.superficieC);
    }

    printf("Ingrese el precio del articulo: ");
    scanf("%f",&prop.precio);
    fflush(stdin);
    while(prop.precio<=0){
    printf("Valor invalido\n");
    printf("Ingrese el precio del articulo: ");
    scanf("%f",&prop.precio);
    }

    printf("Ingrese el tipo de moneda del articulo: ");
    scanf("%s",&prop.moneda);
    fflush(stdin);
    while(prop.moneda==NULL){
    printf("Valor invalido\n");
    printf("Ingrese el tipo de moneda del articulo: ");
    scanf("%s",&prop.moneda);
    }

    printf("Ingrese el tipo de la propiedad del articulo: ");
    scanf("%s",&prop.tipo);
    fflush(stdin);
    while(prop.tipo==NULL){
    printf("Valor invalido\n");
    printf("Ingrese el tipo de la propiedad del articulo: ");
    scanf("%s",&prop.tipo);
    }

    printf("Ingrese el tipo de Operacion del articulo: ");
    scanf("%s",&prop.operacion);
    fflush(stdin);
    while(prop.operacion==NULL){
    printf("Valor invalido\n");
    printf("Ingrese el tipo de Operacion del articulo: ");
    scanf("%s",&prop.operacion);
    }

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

//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

// 3.1-Muestra la lista de las propiedades del archivo pArchivo//

void Lista(FILE *pA){
struct unidades prop;
int i=0, cantprod;
pA=fopen("propiedades.dat","rb");
    fseek(pA,0,SEEK_END);
    cantprod=ftell(pA)/sizeof(struct unidades);// calculo la cantidad de productos registrados para el ciclo
    //printf("Fecha de\t\t\t\t\t\t\t\tSuperficie\tSuperficie\t\t\t\t\t\t\t\t\t\tFecha de");
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|ID   |ingreso     |Zona       |Ciudad     |Dormitorios  |Baños  |total     |cubierta  |Precio       |Moneda   |Tipo   |Operacion |salida |Activo\n");
    fseek(pA,0,SEEK_SET);
    while( i < cantprod ){
        fseek(pA,i*sizeof(struct unidades),SEEK_SET);
        fread(&prop,sizeof(struct unidades),1,pA);
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
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
    printf("|ID   |ingreso     |Zona       |Ciudad     |Dormitorios  |Baños  |total     |cubierta  |Precio       |Moneda   |Tipo   |Operacion |salida |Activo\n");
    while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.activo==1){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
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

//Funcion para solo ingresar los valores tipo Char//
char busquedaChar(int i){
char letras;
switch (i) {
    case 2:
        printf("Zona:");
        scanf(" %s", &letras);
        break;
    case 3:
        printf("Ciudad:");
        scanf(" %s", &letras);
        break;
    case 9:
        printf("Tipo de Moneda:");
        scanf(" %s", &letras);
        break;
    case 10:
        printf("Tipo de la propiedad:");
        scanf(" %s", &letras);
        break;
    case 11:
        printf("Tipo de Operacion:");
        scanf(" %s", &letras);
        break;
    }
return letras;
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
        printf("Banios:");
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
printf("5.- Baños\n");
printf("6.- total de la Superficie\n");
printf("7.- cubierta de la Superficie\n");
printf("8.- Precio\n");
printf("9.- Moneda\n");
printf("10.- Tipo\n");
printf("11.- Operacion\n");
printf("Ingrese el tipo de propiedad a buscar: \n");
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
int seleccion=ingresoProp(); //Hago un pedido para saber cual tipo de variable compararemos
int identificadorInt; //Creo una variable especifica para los valores tipo int
float identificadorFloat; //Creo una variable especifica para los valores tipo float
char identificadorChar; //Creo una variable especifica para los valores tipo char

 if (seleccion ==1 || seleccion ==4 || seleccion ==5){
identificadorInt=busquedaInt(seleccion); //Si quiere un Int, serian la opcion 1,4,5
} else if (seleccion ==6 || seleccion ==7 || seleccion ==8){
identificadorFloat=busquedaFloat(seleccion); //Si quiere un float, serian la opcion 6,7,8
} else if (seleccion ==2 || seleccion ==3 || seleccion ==9 || seleccion ==10 || seleccion ==11){
identificadorChar=busquedaChar(seleccion); //Si quiere un char, serian la opcion 2,3,9,10,11
}

printf("\n");
printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
printf("|ID   |ingreso     |Zona       |Ciudad     |Dormitorios  |Baños  |total     |cubierta  |Precio       |Moneda   |Tipo   |Operacion |salida |Activo\n");
switch (seleccion) {
    case 1:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.id==identificadorInt){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 2:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.zona,identificadorChar) == 0){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 3:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.ciudad,identificadorChar) == 0){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 4:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.dormitorios==identificadorInt){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 5:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.banios==identificadorInt){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 6:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.superficieT==identificadorFloat){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 7:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.superficieC==identificadorFloat){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 8:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.precio==identificadorFloat){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 9:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.tipo,identificadorChar) == 0){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 10:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.moneda,identificadorChar) == 0){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
    case 11:
        while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(strcmp(prop.operacion,identificadorChar) == 0){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        printf("\n");
        }
        }
        }
        break;
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
printf("ingrese el dia:");
scanf("%d",&dia);
printf("ingrese el mes:");
scanf("%d",&mes);
printf("ingrese el anio:");
scanf("%d",&anio);
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("|ID   |ingreso     |Zona       |Ciudad     |Dormitorios  |Baños  |total     |cubierta  |Precio       |Moneda   |Tipo   |Operacion |salida |Activo\n");
    while(!feof(pA)){
        if(fread(&prop,sizeof(struct unidades),1,pA)==1){
        if(prop.dia<=dia && prop.mes <= mes && prop.anio <= anio && prop.activo==1){
        printf("|%-4d |%d/%d/%-7d |%-10s |%-10s |%-12d |%-6d |%-9.1f |%-9.1f |%-12.1f |%-8s |%-6s |%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
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

//3- Menu de filtros para mostrar la lista de las propiedades del archivo pArchivo//

void menulistas(FILE *pA){
    int i;
    pA=fopen("propiedades.dat","rb");
	printf("1.- Mostrar lista completa (Incluyendo Activos e Inactivos)\n");
	printf("2.- Mostrar solo los Activos\n");
	printf("3.- Mostrar por un Tipo especifico\n");
	printf("4.- Mostrar por un rango de tiempo\n");
	scanf("%d",&i);
		switch (i) {
        case 1:
            printf("Has seleccionado la opcion 1\n");
            Lista(pA);
            break;
        case 2:
            printf("Has seleccionado la opcion 2\n");
            soloActivos(pA);
            break;
        case 3:
            printf("Has seleccionado la opcion 3\n");
            propiedadPedida(pA);
            break;
        case 4:
            printf("Has seleccionado la opcion 4\n");
            rangoTiempo(pA);
            break;
        default:
            printf("El valor esta fuera de rango");
        }
}
//------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------//

// 4- baja logica de una propiedad
void bajaLogica(FILE * pA){
struct unidades prod;
int art;//=leerArt();
char opcion;
printf("ingrese el ID");
scanf("%d", &art );
pA=fopen("propiedades.dat","r+b");

    fseek(pA,0,SEEK_SET);
    fseek(pA,(art-1)*sizeof(struct unidades ),SEEK_SET);
    fread(&prod,sizeof(struct unidades ),1,pA);
    if( prod.activo == 0){
     printf("La propiedad ya estaba dada de baja \n");
     fclose(pA);
     return;
    }
    printf("Usted dar%c de baja a:\n", 160);
    printf("Zona: %s, Ciudad: %s, Dormitorios: %d, banios: %d, SuperficieT: %.2f,SuperficieC: %.2f, Precio: %.2f, Moneda: %s, Tipo: %s, Operacion: %s \n",prod.zona,prod.ciudad, prod.dormitorios, prod.banios, prod.superficieT, prod.superficieC, prod.precio, prod.moneda,prod.tipo,prod.operacion);
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
printf("\n***--El producto %d se dio de baja correctamente--***\n", art);}
printf("\n\n\n");
printf("Asi quedo la lista actualizada \n");
struct unidades prop;
int i=0, cantprod;
    fseek(pA,0,SEEK_END);
    cantprod=ftell(pA)/sizeof(struct unidades);// calculo la cantidad de productos registrados para el ciclo
    printf("|ID  |ingreso     |Zona      |Ciudad    |Dormitorios |Baños |total    |cubierta |Precio      |Moneda  |Tipo  |Operacion |salida |Activo\n");
    fseek(pA,0,SEEK_SET);
    while( i < cantprod ){
        fseek(pA,i*sizeof(struct unidades),SEEK_SET);
        fread(&prop,sizeof(struct unidades),1,pA);
        if(prop.activo == 1 ){
        printf("|%-4d|%d/%d/%-7d|%-10s|%-10s|%-12d|%-6d|%-9.2f|%-9.2f|%-12.2f|%-8s|%-6s|%-10s|       |%-1d",prop.id,prop.dia,prop.mes,prop.anio,prop.zona,prop.ciudad,prop.dormitorios,prop.banios,prop.superficieT,prop.superficieC,prop.precio,prop.moneda,prop.tipo,prop.operacion,prop.activo);
        }

        i++;

        printf("\n");
   }
printf("\n\n");
fclose(pA);
}
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
	printf("\t4. Baja logica de una propiedad\n");
	printf("\t5. Salir\n");
    fflush(stdin);
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
                //fflush(stdin);
               break;
        case 2:productoNuevo(pArchivo);
                //fflush(stdin);
               break;
        case 3:menulistas(pArchivo);
               // fflush(stdin);
               break;
        case 4:bajaLogica(pArchivo);
               // fflush(stdin);
               break;
        case 5:printf("Cinco");
               break;
        default:
            printf("El valor esta fuera de rango");
        }
    printf("\n");
    fflush(stdin);
	system("pause");
	}while(1);

//Fin de main

}
