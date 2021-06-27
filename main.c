#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#define nomArchivo "clientes.dat"
#define backupClientes "backupArchivo.dat"
#define nomArchiConsumos "consumos.dat"
#define ANIO 2021

        /// TP FINAL CON CONSUMOS
         //

typedef struct{
    int id;
    int nroCliente;
    char nombre[30];
    char apellido [30];
    char dni[10];
    char email[30];
    char domicilio[45];
    char movil[12];
    int estado; ///"0" cliente dado de baja, "1" cliente activo
}stClientes;

typedef struct{
    int id;
    int idCliente;
    int anio;
    int mes;
    int dia;
    int datosConsumidos;
    int estado; ///0 cliente dado de baja, 1 cliente activo
}stConsumos;

        ///PROTOTIPADOS FUNCIONES///
void altaCliente (char archivoClientes[]);
void modNumCliente (stClientes c);
void despersistencia(stClientes clientes[], int* validos);
int validaNumCliente (int numCliente);
void modificaEstado();
int cuentaRegistros(char archivo[],int tamanio);
void cambiaEstado( int pos, int estado);
void creaBackUp (char archivo [], char nuevoArchivo []);
int validaMovil (char movil[12]);
///CONSUMOS//
int cargaAnio(int anio);
int existeConsumoCliente(char archivo[],int idCliente);
int sumaConsumoFecha(stConsumos a);
int cargaMes(int fecha);
int cargaDia (int dato);

int clienteRandom();
int mesRandom ();
int diaRandom ();
void altaConsumoRandom (char archivoConsumos[], int idStCliente, int mes, int dia);
stClientes buscaPorId ( int id);


        ///BUSCA///
int cargaNombresABuscar (char n[][40], int dim);
void modificaCliente (stClientes clientes[], int validos,  int idModificar);
stClientes buscaDni ( char dni[]);
stClientes buscaApellido ( char apellido []);
stClientes buscaPorCliente ( int numCliente);
stClientes buscaIdCliente(char archivo[], int pos);
void buscaPorClienteModEstado ( int numCliente);
int buscaPos (int numClient);
        ///CONSUMOS///
void mostrarXFecha(char archivoConsumo[]);
void cambiaConsumo(char archivoConsumo []);
void muestraConsumoPorIdCliente (int idClien);

        ///MUESTRA///
void buscaClienteApellido (char archivoClientes [],char apellido[]);
void muestraUnCliente (stClientes c);
void muestraListaClientes (char archivoClientes []);
void muestraClientesId (char archivoClientes [], int clienteBuscar);
void muestrasNomOapellido ( char n[][40], int v);
void muestraActivos ();

/// VALIDACION DE DATOS ///
int validaDni (char Dni[10]);
int validaMovil (char movil[12]);


/// FUNCIONES DE CONSUMO ///

void altaConsumo (char archivoConsumos[], int idStCliente);
void muestraListaConsumos ();

///PROTOTIPADOS MENU///
char menu();
char menuInicial();
char menuAltas();
char menuBusca();
char menuMostrar();
///---------------------------------------------------------------------------------------------------------------------------////
                                                ///MAIN()////
int main()
{

     ///MENU INICIAL///
    char opcionAltas;
    char opcion;
    char opcionESC=0;
    char opcionBusca;
    char opcionMostrar;
    char dniBusca[1];
    char apellidoBusca[1];
    stClientes clienteExi;
    stClientes arregloClientes [50];
    int numCliente=-1;
    int posicion=-1;
    int clienteN=-1;
    int salir=-1;
    int vClientes=0;
    int idModicar=0;
    ///Aleatorio prueba///
    int clienteRegistro;
    int mesRan;
    int diaRan;
    stClientes stClienteRan;
    int i =0;

    FILE*archivoEstado;
    do {
        opcion=menuInicial();

        switch(opcion){
            case '1':        ///===============================CASE 1 --ALTAS CLIENTES Y CONSUMOS =========================================///
                do {
                   opcionAltas=menuAltas();
                            switch(opcionAltas){
                    case '1':                                            ///ALTAS DE CLIENTES///
                            printf("\n ALTA DE CLIENTES");
                                altaCliente(nomArchivo);

                break;
                    case '2':                ///ALTA DE CONSUMO -- PRIMERO BUSCA EL ID DEL CLIENTE POR DNI||NUMERO DE CLIENTE||APELLIDO//
                        do  {
                            opcionBusca=menuBusca();
                                    switch(opcionBusca){
                            case '1':                                 ///BUSCA POR DNI PARA ALTA DE CONSUMO//
                                do {
                                    printf("\nIngrese dni a buscar\n");
                                    fflush(stdin);
                                    gets(dniBusca);
                                    clienteExi=buscaDni(dniBusca);
                                if (clienteExi.id !=-1){
                                    printf("\nEL cliente encontrado es");
                                    muestraUnCliente(clienteExi);
                                    altaConsumo("consumos.dat", clienteExi.id);
                                    break;
                                }else{
                                    printf("\nEl cliente no existe");
                                    printf("\n");
                                    break;
                                    }
                             }while(clienteExi.nroCliente!=-1);
                        break;
                            case '2':                        ///BUSCA POR NUMERO DE CLIENTE PARA ALTA DE CONSUMO///
                                do {
                                    printf("\nIngrese numero de cliente a buscar\n");
                                    scanf("%d",&numCliente);
                                    clienteExi=buscaPorCliente(numCliente);
                                if (clienteExi.id !=-1){
                                    printf("\nEL cliente encontrado");
                                    muestraUnCliente(clienteExi);
                                    altaConsumo("consumos.dat", clienteExi.id);
                                    break;
                                }else{
                                    printf("\nEl cliente no existe");
                                    printf("\n");
                                    break;
                                    }
                            }while(clienteExi.nroCliente!=-1);
                        break;
                            case '3':                           ///BUSCA POR APELLIDO PARA ALTA DE CONSUMO///
                                do {
                                    printf("\nIngrese apellido a buscar\n");
                                    fflush(stdin);
                                    gets(apellidoBusca);
                                    clienteExi=buscaApellido(apellidoBusca);
                                if (clienteExi.id !=-1) {
                                    printf("\nEL cliente encontrado");
                                    muestraUnCliente(clienteExi);
                                    altaConsumo("consumos.dat", clienteExi.id);
                                    break;
                                }else{
                                    printf("\nEl cliente no existe");
                                    printf("\n");
                                    break;

                                    }
                            }while(clienteExi.nroCliente!=-1);

                            }
                            break;
                    case '3':                           ///ALTA CONSUMOS ALEATORIO///
                                    for (int i=0;i<50;i++) {
                                    //clienteRegistro = clienteRandom();
                                    stClienteRan=buscaPorId(clienteRandom());
                                   // muestraUnCliente(stClienteRan);
                                    mesRan=mesRandom();
                                    diaRan=diaRandom();
                                    altaConsumoRandom(nomArchiConsumos,stClienteRan.id,mesRan,diaRan);
                                }
                        printf("\n Ciclo random completo\n");

                        printf("\n");
                        system("pause");
                        }while(opcionBusca!=27);
                    }printf("\n");
                    system("pause");
                    }while(opcionAltas!=27);
        break;
            case '2':       /// ===================-CASE 2-- MODIFICACIONES-PRIMERO BUSCAR CLIENTE PARA MODIFICAR =============================///
            do{
                opcionBusca=menuBusca();

                switch(opcionBusca){

                    case '1':                       ///BUSCA POR DNI PARA MODIFICAR DATOS DEL CLIENTE//
                        do{
                            printf("\nIngrese dni a buscar\n");
                            fflush(stdin);
                            gets(dniBusca);
                            clienteExi=buscaDni(dniBusca);
                            idModicar=clienteExi.id;
                        if (clienteExi.id !=-1){
                            printf("\nEL cliente encontrado es");
                            muestraUnCliente(clienteExi);
                            break;
                        }else{
                            printf("\nEl cliente no existe");
                            printf("\n");
                            break;
                            }
                        }while(clienteExi.nroCliente!=-1);
                        printf("\n");
                        system("\npause");
                        despersistencia(arregloClientes,&vClientes);
                        modificaCliente(arregloClientes,vClientes,idModicar);
                        vClientes=0;
                break;
                    case '2':                        ///BUSCA POR NUMERO DE CLIENTE PARA MODIFICAR DATOS DEL CLIENTE///
                        do{
                            printf("\nIngrese numero de cliente a buscar\n");
                            scanf("%d",&numCliente);
                            clienteExi=buscaPorCliente(numCliente);
                            idModicar=clienteExi.id;
                            if (clienteExi.id !=-1){
                                printf("\nEL cliente encontrado");
                                muestraUnCliente(clienteExi);
                                break;
                            }else{
                                printf("\nEl cliente no existe");
                                printf("\n");
                                break;
                            }
                        }while(clienteExi.nroCliente!=-1);
                            printf("\n");
                            system("\npause");
                            despersistencia(arregloClientes,&vClientes);
                            modificaCliente(arregloClientes,vClientes,idModicar);
                            vClientes=0;
                break;
                    case '3':                       ///BUSCA POR APELLIDO PARA MODIFICAR DATOS DEL CLIENTE///

                    do{
                        printf("\nIngrese apellido a buscar\n");
                        fflush(stdin);
                        gets(apellidoBusca);
                        clienteExi=buscaApellido(apellidoBusca);
                        idModicar=clienteExi.id;
                        if (clienteExi.id !=-1){
                            printf("\nEL cliente encontrado");
                            muestraUnCliente(clienteExi);
                            break;
                        }else{
                            printf("\nEl cliente no existe");
                            printf("\n");
                            break;
                            }
                    }while(clienteExi.nroCliente!=-1);
                        printf("\n");
                        system("pause");
                        despersistencia(arregloClientes,&vClientes);
                        modificaCliente(arregloClientes,vClientes,idModicar);
                        vClientes=0;
                break;
                    case 'a':                                     ///MODIFICA CAMPOS DE CONSUMO///
                            cambiaConsumo(nomArchiConsumos);
                }
                    printf("\n");
                    system("pause");
                }while(opcionBusca!=27);
        break;
            case '3':       ///=======================================CASE 3--BUSCA PARA MOSTRAR=================================///
                printf("\nBUSCA PARA MOSTRAR\n");
                 do{
                opcionMostrar=menuMostrar();
                switch(opcionMostrar){
                    case '1':                                    ///BUSCA CONSUMOS PARA MOSTRAR//
                       mostrarXFecha(nomArchiConsumos);

                break;
                    case '2':                                    ///BUSCA POR DNI PARA MOSTRAR//
                        do{
                            printf("\nIngrese dni a buscar\n");
                            fflush(stdin);
                            gets(dniBusca);
                            clienteExi=buscaDni(dniBusca);
                            clienteN=clienteExi.nroCliente;
                            if (clienteExi.id !=-1){
                                printf("\nEL cliente encontrado es");
                                muestraUnCliente(clienteExi);
                                while(opcionESC!=27){
                                        printf("\nPARA VER LOS CONSUMOS DEL CLIENTE %d",clienteN);
                                        printf("\n ESC PARA SALIR S PARA VER");
                                        opcionESC=getch();
                                        if (opcionESC!=27){
                                        system("cls");
                                        muestraConsumoPorIdCliente(clienteExi.id);
                                        }
                                        printf("\n");
                                        system("pause");
                                    }
                                opcionESC=0;
                                break;
                            }else{
                                printf("\nEl cliente no existe");
                                printf("\n");
                                break;
                            }
                        }while(clienteExi.nroCliente!=-1);
                break;
                    case '3':                                    ///BUSCA POR NUMERO DE CLIENTE PARA MOSTRAR//
                        do{
                            printf("\nIngrese numero de cliente a buscar\n");
                            scanf("%d",&numCliente);
                            clienteExi=buscaPorCliente(numCliente);
                            if (clienteExi.id !=-1){
                                printf("\nEL cliente encontrado");
                                muestraUnCliente(clienteExi);
                                    while(opcionESC!=27){
                                        printf("\nPARA VER LOS CONSUMOS DEL CLIENTE %d",numCliente);
                                        printf("\n ESC PARA SALIR S PARA VER");
                                        opcionESC=getch();
                                        if (opcionESC!=27){
                                        system("cls");
                                        muestraConsumoPorIdCliente(clienteExi.id);
                                        }
                                        printf("\n");
                                        system("pause");
                                    }
                                opcionESC=0;
                                break;
                            }else{
                            printf("\nEl cliente no existe");
                            printf("\n");
                            break;
                            }
                        }
                        while(clienteExi.nroCliente!=-1);
                break;
                    case '4':                                    ///BUSCA POR APELLIDO PARA MOSTRAR///
                            do{
                                printf("\nIngrese apellido a buscar\n");
                                fflush(stdin);
                                gets(apellidoBusca);
                                clienteExi=buscaApellido(apellidoBusca);
                                clienteN=clienteExi.nroCliente;
                            if (clienteExi.id !=-1){
                                printf("\nEL cliente encontrado");
                                muestraUnCliente(clienteExi);
                                while(opcionESC!=27){
                                        printf("\nPARA VER LOS CONSUMOS DEL CLIENTE %d",clienteN);
                                        printf("\n ESC PARA SALIR S PARA VER");
                                        opcionESC=getch();
                                        if (opcionESC!=27){
                                        system("cls");
                                        muestraConsumoPorIdCliente(clienteExi.id);
                                        }
                                        printf("\n");
                                        system("pause");
                                    }
                                opcionESC=0;
                                break;
                                }else{
                                    printf("\nEl cliente no existe");
                                    printf("\n");
                                    break;
                                    }
                            }while(clienteExi.nroCliente!=-1);
                break;
                    case '5':                                      ///BUSCA ESTADO DEL CLIENTE PARA MOSTRAR///
                        muestraActivos();
                break;
                    case '6':                                     ///MUESTRA LISTA DE CLIENTES ///
                        muestraListaClientes(nomArchivo);
                break;
                    case 'a':
                             muestraListaConsumos(nomArchiConsumos);
                             break;
                    case 'b':
                            cambiaConsumo("consumos.dat");


                    }printf("\n");
                    system("pause");
                }while(opcionMostrar!=27);
        break;
            case '4':        ///=============================CASE 4--DAR DE BAJA UN CLIENTE--PRIMERO LO BUSCA=============================///
                printf("\nDAR DE BAJA UN CLIENTE\n");
                do{
                opcionBusca=menuBusca();
                switch(opcionBusca){
                    case '1':                       ///BUSCA POR DNI PARA DAR DE BAJA//
                        do{
                           printf("\nIngrese dni a buscar\n");
                            fflush(stdin);
                            gets(dniBusca);
                            clienteExi=buscaDni(dniBusca);
                            clienteN=clienteExi.nroCliente;
                            if (clienteExi.id !=-1&&clienteN!=-1&&clienteExi.estado!=0){
                                system("cls");
                                printf("\nEL cliente %s fue encontrado",clienteExi.dni);
                                posicion= buscaPos(clienteN);
                                cambiaEstado(posicion,0);
                                printf("\nLa baja fue exitosa");
                                printf("\n");
                                break;
                            }else{
                                printf("\nEl cliente no existe o ya esta inactivo");
                                printf("\n");
                            break;
                            }
                        }while(clienteExi.nroCliente!=-1);
                break;
                    case '2':                        ///BUSCA POR NUMERO DE CLIENTE PARA DAR DE BAJA///
                    do{
                        printf("\nIngrese numero de cliente a buscar\n");
                        scanf("%d",&numCliente);
                        clienteExi=buscaPorCliente(numCliente);
                        if (clienteExi.id !=-1&&clienteExi.estado!=0){
                            system("cls");
                            printf("\nEL cliente %d fue encontrado", numCliente);
                            posicion= buscaPos(numCliente);
                            cambiaEstado(posicion,0);
                            printf("\nLa baja fue exitosa");
                            printf("\n");
                            break;
                        }else{
                            printf("\nEl cliente no existe o ya esta inactivo");
                            printf("\n");
                            break;
                            }
                    }while(clienteExi.nroCliente!=-1);
                break;
                    case '3':                           ///BUSCA POR APELLIDO PARA DAR DE BAJA///
                        do{
                            printf("\nIngrese apellido a buscar\n");
                            fflush(stdin);
                            gets(apellidoBusca);
                            clienteExi=buscaApellido(apellidoBusca);
                            clienteN=clienteExi.nroCliente;
                            if (clienteExi.id !=-1&&clienteN!=-1&&clienteExi.estado!=0){
                                system("cls");
                                printf("\nEL cliente %s fue encontrado",clienteExi.apellido);
                                posicion= buscaPos(clienteN);
                                cambiaEstado(posicion,0);
                                printf("\nLa baja fue exitosa");
                                printf("\n");
                                break;
                            }else{
                                printf("\nEl cliente no existe o ya esta inactivo");
                                printf("\n");
                            break;
                        }
                    }while(clienteExi.nroCliente!=-1);

                    }
                    printf("\n");
                    system("pause");
                    }while(opcionBusca!=27);
        break;
            case '5':
                creaBackUp(nomArchivo,backupClientes);
                printf("\nCompletado Exitosamente. Ubicacion : Carpeta Del Programa");
        break;
            case '6':                         ///CAMBIA ESTADO DEL CLIENTE////
               archivoEstado=fopen(nomArchivo,"r+b");
               stClientes aux;
                if (archivoEstado){
                    int  i=0;
                    while(fread(&aux,sizeof(stClientes),1,archivoEstado)>0){
                        i++;
                        cambiaEstado(i,1);
                        }
                    }
                    fclose(archivoEstado);
                    printf("\nAhora todos los clientes estan activos");
        break;
            case '7':                       /// BORRA DEL ARCHIVO TODOS LOS CLIENTES INACTIVOS///
                        printf("\n!!!CUIDADO!!!! SEGURO DESEA BORRAR DE LA BASE DE DATOS LOS CLIENTES INACTIVOS\n");

        }
        printf("\n");
        system("pause");
    }
    while(opcion!=27);
    return 0;
}
///----------------------------------------------------------------------------------------------------------------------------------///
                            ///FUNCIONES MENU///

    ///MUESTRA EL MENU INICIAL///
char menuInicial()
{
        char opcion;


    system("cls");
    system("color 8F");
    printf("\n\t\t\t MENU INICIAL\n\n");
    printf("\n 1 - ALTAS");
    printf("\n 2 - MODIFICA DATOS DEL CLIENTE");
    printf("\n 3 - BUSCAR PARA MOSTRAR");
    printf("\n 4 - BAJA");
    printf("\n 5 - REALIZA BACKUP DE LOS CLIENTES");
    printf("\n 6 - ACTIVA ESTADO DE TODOS LOS CLIENTES");
    printf("\n 7 - BORRAR TODOS LOS CLIENTES INACTIVOS");



    printf("\n\nESC para salir");
    printf("\n\t Elija una opcion\n\n");

    opcion=getch();

    return opcion;
}

  ///MENU CASE 1 ALTA DE CONSUMOS O CLIENTES///

char menuAltas()
{
        char opcionAltas;


    system("cls");
    system("color 8F");
    printf("\n\t\t\t MENU ALTAS\n\n");
    printf("\n 1 - CLIENTES");
    printf("\n 2 - CONSUMOS");
    printf("\n 3 - ALTA CONSUMOS ALEATORIOS");
    printf("\n\nESC para salir");
    printf("\n\t Elija una opcion\n\n");

    opcionAltas=getch();

    return opcionAltas;
}

 ///MENU CASE 2-BUSCA CLIENTES PARA ALTAS O MODIFICAR DATOS///

char menuBusca()
{
        char opcionBusca;


    system("cls");
    system("color 8F");
    printf("\n\t\t\t BUSCA CLIENTE \n\n");
    printf("\n 1 - BUSCA POR DNI");
    printf("\n 2 - BUSCA POR NUMERO DE CLIENTE");
    printf("\n 3 - BUSCA POR APELLIDO");
    printf("\n\nESC para salir");
    printf("\n\t Elija una opcion\n\n");

    opcionBusca=getch();

    return opcionBusca;
}


///MENU CASE 3-BUSCA CLIENTES PARA MOSTRAR DATOS Y CONSUMOS///

char menuMostrar()
{
        char opcionMostrar;


    system("cls");
    system("color 8F");
    printf("\n\t\t\t MUESTRA CLIENTES \n\n");
    printf("\n 1 - BUSCA POR FECHA");
    printf("\n 2 - BUSCA POR DNI");
    printf("\n 3 - BUSCA POR NUMERO DE CLIENTE");
    printf("\n 4 - BUSCA POR APELLIDO");
    printf("\n 5 - MUESTRA CLIENTES ACTIVOS");
    printf("\n 6 - MUESTRA TODOS LOS CLIENTES");
    printf("\n");
    printf("////////  CONSUMOS ////// \n");
    printf("\n A - MOSTRAR LISTA DE CONSUMOS DE TODOS LOS CLIENTES");
    printf("\n B - CAMBIA CONSUMO POR FECHA");


    printf("\n\nESC para salir");
    printf("\n\t Elija una opcion\n\n");

    opcionMostrar=getch();

    return opcionMostrar;
}
///------------------------------------------------------------------------------------------------------------------------------///
                                                    ///FUNCIONES ////
  ///ALTA DE CLIENTES////
void altaCliente (char archivoClientes[]){
    char opcion=0;
    int flagEmail=0;
    int flagDni=0;
    int flagMovil=0;
    int flagNombreApellido=0;
    int id = cuentaRegistros(archivoClientes,sizeof(stClientes));
    stClientes c;
    FILE *pArchiClientes = fopen(archivoClientes,"ab");
    if (pArchiClientes!= NULL){
    do{
        do{

        printf("\n Nro de Cliente............: ");
        scanf("%d", &c.nroCliente);
        ///printf("\nValida cliente %d", validaNumCliente(c.nroCliente));
        if (validaNumCliente(c.nroCliente)==1){
            printf("El numero de clientes ingresado ya existe-Ingrese otro");
            ///printf("\nvalida Num  cliente %d", validaNumCliente(c.nroCliente));
            }
        }while(validaNumCliente(c.nroCliente)==1);
        printf("\nNumero de cliente nuevo fue creado. ");
        printf("\nIngrese datos para el cliente [%d] ",c.nroCliente);

        do{
        printf("\n Nombre....................: ");
        fflush(stdin);
        scanf("%s", &c.nombre);
        flagNombreApellido=validaNombreyApelido(c.nombre);
        } while (flagNombreApellido==1);
        flagNombreApellido=0;
       do{
        printf("\nApellido....................: ");
        fflush(stdin);
        scanf("%s", &c.apellido);
        flagNombreApellido=validaNombreyApelido(c.apellido);
        } while (flagNombreApellido==1);
        validaDni(&c.dni);
        do{
        printf("\n Dni..................: ");
        fflush(stdin);
        scanf("%s", &c.dni);
        flagDni=validaDni(c.dni);
        } while(flagDni==1);

        fflush(stdin);
        scanf(validaEmail (&c.email));
        printf("\n Domicilio.................: ");
        fflush(stdin);
        gets(&c.domicilio);
        ///scanf("%s", &c.domicilio);
        do{
        printf("\n Movil.....................: ");
        fflush(stdin);
        scanf("%s", &c.movil);
        flagMovil=validaMovil(c.movil);
        }while(flagMovil==1);
        printf("\n Situacion del cliente.....: ");
        scanf("%d", &c.estado);
        id++;
        c.id = id;

        fwrite(&c, sizeof(stClientes), 1, pArchiClientes);
        printf("\n ESC para salir, otra para continuar...");
        opcion=getch();
        system("cls");
    }
    while(opcion!=27);
    fclose(pArchiClientes);
    }else{
        printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}
        ///MUESTRA UN CLIENTE ////
void muestraUnCliente (stClientes c){
    printf("\n Id........................: %d", c.id);
    printf("\n Nro de Cliente............: %d", c.nroCliente);
    printf("\n Nombre....................: %s", c.nombre);
    printf("\n Apellido..................: %s", c.apellido);
    printf("\n DNI.......................: %s", c.dni);
    printf("\n Email.....................: %s", c.email);
    printf("\n Domicilio.................: %s", c.domicilio);
    printf("\n Movil.....................: %s", c.movil);
    printf("\n Situacion del cliente.....: %d", c.estado);
    printf("\n-------------------------------------------------------");
}
        ///MUESTRA LISTA DE CLIENTES DESDE UN ARCHIVO////
void muestraListaClientes (char archivoClientes []){
    system("cls");
    stClientes c;
    FILE *pArchiClientes = fopen(archivoClientes, "rb");
    if(pArchiClientes != NULL){
        while(fread(&c, sizeof(stClientes), 1, pArchiClientes)>0){
            muestraUnCliente(c);
        }
        fclose(pArchiClientes);

    }else{
       printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}
        ///CUENTA REGISTROS DE UN ARCHIVO///
int cuentaRegistros(char archivo [],int tamanioSt){

    int cantidadRegistros = 0;
    FILE *p = fopen(archivo, "rb");       ///RB - Abre un archivo de binario para operaciones de lectura

    if(p!=NULL){
        fseek(p, 0, SEEK_END);      ///FSEEK - UBICA EL CURSOR EN LA POSICION INDICADA POR PARAMETRO.
        cantidadRegistros=ftell(p)/tamanioSt;  ///FTELL - INDICA LA POSICION DEL CURSOR
        fclose(p);
    }

    return cantidadRegistros;
}
        ///MUESTRA UN CLIENTE DESDE ID///
void muestraClientesId (char archivoClientes [], int clienteBuscar){
    stClientes c;
    int i=0;
    FILE *pArchiClientes = fopen(archivoClientes, "rb");
    if(pArchiClientes != NULL){
        while(fread(&c, sizeof(stClientes), 1, pArchiClientes)>0){
                i++;
                if (i== clienteBuscar){
                    muestraUnCliente(c);
                }
        }
        fclose(pArchiClientes);

    }else{
       printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}
        ///BUSCA UN CLIENTE POR APELLIDO///
void buscaClienteApellido (char archivoClientes [],char apellido[]){
    stClientes c;


    FILE *pArchiClientes = fopen(archivoClientes, "rb");
    if(pArchiClientes ){

        while(fread(&c, sizeof(stClientes), 1, pArchiClientes)>0){
                if (strcmp(c.apellido,apellido )==0){
                        muestraUnCliente(c);
                        }
        }
        fclose(pArchiClientes);
    }
}
        ///CARGA NOMBRE EN MATRIZ DE CHAR//
int cargaNombresABuscar (char n[][40], int dim){
    int i=0;
    char opcion = 0;

    while (i<dim && opcion !=27){
        printf ("\nIngrese un nombre\n");
        scanf("%s", n[i]);
        i++;
        printf("---ESC para salir---");
        opcion=getch();
        system("cls");
    }
    return i;
}
        ///MUESTRA CHAR CARGADOS EN MATRIZ//
void muestrasNomOapellido ( char n[][40], int v){

    for (int i = 0; i<v; i++){
        /*if(strcmp(n[i],"sergio")==0){
            strcpy (n[i],"otra cosa");
        }
        */
        printf("\n %s",n[i]);
    }
}
        ///MODIFICA UN CLIENTE DESDE ID///
void modificaCliente (stClientes clientes[], int validos,  int idModificar){
    stClientes c;
    int cont=0;
    int i=0;
    int nuevoValor;
    FILE *pArchi = fopen(nomArchivo, "r+b");
        if(pArchi){
            while(fread(&c, sizeof(stClientes), 1, pArchi)>0 && c.id!=idModificar){
                     i++;
                    }
            if (i < validos){
                        modificaElCliente(&clientes[i]);
                        fseek(pArchi,-1 * sizeof (stClientes),SEEK_CUR);
                        fwrite(&clientes[i], sizeof(stClientes), 1, pArchi);
                    }else{
                    printf("\n\t\tID no se encuentra en lista de clientes");
                    }
            }
            fclose(pArchi);
        }
    ///MODIFICA EL CLIENTE///
void modificaElCliente (stClientes* c){
    char opcion;
    int nuevoValor;
    do {
        opcion=menu();

        switch(opcion){
                case '1':
                    do{
                    printf("Ingrese nuevo numero de cliente\n");
                    scanf("\n%d",&nuevoValor);
                    (*c).nroCliente=nuevoValor;
                        if (validaNumCliente(nuevoValor)==1){
                            printf("\n\tNumero de cliente ya existe-Ingrese uno nuevo\n");
                        }
                    }
                    while(validaNumCliente(nuevoValor)==1);
                    break;
                case '2':
                    printf("\nIngrese un nuevo nombre\n");
                    fflush(stdin);
                    gets((*c).nombre);
                    break;
                case '3':
                    printf("\nIngrese un nuevo apellido\n");
                    fflush(stdin);
                    gets((*c).apellido);
                    break;
                case '4':
                    printf("\nIngrese un nuevo DNI\n");
                    fflush(stdin);
                    gets((*c).dni);
                    break;
                case '5':

                    fflush(stdin);
                    scanf(validaEmail((*c).email));
                    break;
                case '6':
                    printf("\nIngrese un nuevo domicilio\n");
                    fflush(stdin);
                    gets((*c).domicilio);
                    break;
                case '7':
                    printf("\nIngrese un nuevo movil\n");
                    fflush(stdin);
                    gets((*c).movil);
                    break;
                case '8':
                    printf("Situacion del cliente- 0 activo 1 inactivo\n");
                    int num;
                    scanf("%d",&num);
                    (*c).estado=num;


        }
        printf("\n");
        system("pause");
    }
    while(opcion!=27);

    return 0;
    }
    ///MENU CLIENTE///
char menu(){
        char opcion;


    system("cls");
    system("color 8F");
    printf("\n\t\t\t Modifica datos\n\n");
    printf("\n 1 - Nro de cliente");
    printf("\n 2 - Nombre");
    printf("\n 3 - Apellido");
    printf("\n 4 - DNI");
    printf("\n 5 - Email ");
    printf("\n 6 - Domicilio");
    printf("\n 7 - Movil");
    printf("\n 8 - Situacion del cliente");
    printf("\n\nESC para salir");
    printf("\n\n\t Elija una opcion\n\n");

    opcion=getch();

    return opcion;
}
///memcpy(void *dest, const void *src, size_t n)
        ///DESPERSISTENCIA///
void despersistencia(stClientes clientes[], int* validos){
    FILE* pArch = fopen(nomArchivo,"rb");
    stClientes p;

    if (pArch != NULL){
        while (fread(&p,sizeof(stClientes),1,pArch) > 0){
            clientes[*validos] = p;
            (*validos)++;
        }
        fclose(pArch);
    }
}
    /// VALIDACION DE '@'///
void validaEmail (char pEmail[]){
    char vEmail[1][30];
    int flagEmail=0;

    do {
        if (flagEmail==0){
        printf("\n Email.....................: ");
        fflush(stdin);
        scanf("%s", &vEmail[0]);
        if (strchr(vEmail[0], 64)){
                strcpy(pEmail, vEmail[0]);
                flagEmail=1;

        } else {
          printf("Ingrese nuevamente el mail");
        }
        }
        } while (strchr(pEmail, 64)==0);

}


        /// VALIDA SI EL NUMERO DE CLIENTE YA SE ENCUENTRA///
 int validaNumCliente (int numCliente){
    int flag = 0;
    stClientes a;
    FILE*pArchi=(fopen(nomArchivo,"rb"));
    ///rewind(pArchi);                     ///NO ME SALIO COMO LO HIZO SERGIO EN LA CLASE DE 9-6-21///
    ///fseek(pArchi,0,SEEK_SET);           ///SIEMPRE RETORNA 0// ES COMO QUE NO ABRIA EL ARCHIVO//
    if (pArchi){
        while(fread(&a,sizeof(stClientes),1,pArchi)>0&&flag==0){
            if (a.nroCliente==numCliente){
                flag=1;
                return flag;
            }
        }
        fclose(pArchi);
    }
 return flag;
 }


       ///BUSCA CLIENTE POR DNI///
stClientes buscaDni ( char dni[]){

    stClientes aux;
    stClientes dniCliente;
    dniCliente.id=-1;
    int flag=0;
    FILE *pArchi = fopen(nomArchivo,"rb");
    if (pArchi){
    while (flag==0&&fread(&aux,sizeof(stClientes),1,pArchi)>0){
        if(strcmp(aux.dni,dni)==0){

            dniCliente=aux;
            flag=1;
        }
    }
    fclose(pArchi);
    }
    return dniCliente;
}


  ///BUSCA CLIENTE POR APELLIDO///
stClientes buscaApellido ( char apellido []){

    stClientes aux;
    stClientes apellidoCliente;
    apellidoCliente.id=-1;

    int flag=0;
    FILE *pArchi = fopen(nomArchivo,"rb");
    if (pArchi){
    while (flag==0&&fread(&aux,sizeof(stClientes),1,pArchi)>0){
        if(strcmp(aux.apellido,apellido)==0){

            apellidoCliente=aux;
            flag=1;
        }
    }
    fclose(pArchi);
    }
    return apellidoCliente;
}



 ///BUSCA CLIENTE POR NUMERO DE CLIENTE///
stClientes buscaPorCliente ( int numCliente){

    stClientes aux;
    stClientes cliente;
    cliente.id=-1;


    int flag=0;
    FILE *pArchi = fopen(nomArchivo,"rb");
    if (pArchi){
    while (flag==0&&fread(&aux,sizeof(stClientes),1,pArchi)>0){
        if(aux.nroCliente==numCliente){
            cliente=aux;
            flag=1;
            }
        }
        fclose(pArchi);
        }
    return cliente;
}


    ///MUESTRA LISTA DE CLIENTES ACTIVOS////
void muestraActivos (){
    system("cls");
    stClientes aux;
    FILE *pArchi = fopen(nomArchivo, "rb");
    if(pArchi){
        while(fread(&aux, sizeof(stClientes), 1, pArchi)>0){
                if (aux.estado==1){
                    muestraUnCliente(aux);

                }
        }
        fclose(pArchi);

    }else{
       printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}



///CAMBIA EL ESTADO DEL CLIENTE SEGUN POSICION/////
void cambiaEstado( int pos, int estado){
    stClientes aux;
    FILE *pArch = fopen(nomArchivo, "r+b");

    if(pArch && pos >= 0 && pos <= cuentaRegistros(nomArchivo,sizeof(stClientes))){
        fseek(pArch, sizeof(stClientes)*(pos-1), 0);
        fread(&aux, sizeof(stClientes), 1, pArch);
        aux.estado=estado;
        fseek(pArch, -1 * sizeof(stClientes), SEEK_CUR);
        fwrite(&aux, sizeof(stClientes), 1, pArch);
        fseek(pArch, sizeof(stClientes), SEEK_CUR);
        fclose(pArch);
        }
}

 ///ENCUENTRA POS A PARTIR DE NUMCLIENTES///
int buscaPos (int numClient){
    stClientes c;
    int pos=-1;
    int flag=0;


    FILE *pArchiClientes = fopen(nomArchivo, "rb");
    if(pArchiClientes ){
            while(flag !=1 && fread(&c, sizeof(stClientes), 1, pArchiClientes)>0){
                    if (c.nroCliente==numClient){
                        pos=ftell(pArchiClientes)/sizeof(stClientes);
                        flag=1;
            }
        }
        fclose(pArchiClientes);

    }else{
       printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
    return pos;
}

               /// VALIDACIONES DE DATOS ///
int validaDni (char Dni[10]){
int i=0;
int j=0;
int flag=0;

    j=strlen(Dni);

    while (i<j && flag==0){
        if (isdigit(Dni[i])){
            i++;
        }
        else {
            flag=1;

        }
    }
    return flag;
}
int validaMovil (char movil[12]){
int i=0;
int j=0;
int flag=0;

    j=strlen(movil);

    while (i<j && flag==0){
        if (isdigit(movil[i])){
            i++;
        }
        else {
            flag=1;

        }
    }
    return flag;
}
int validaNombreyApelido (char nombre_Apellido[30]){
int i=0;
int j=0;
int flag=0;

    j=strlen(nombre_Apellido);


    while (i<j && flag==0){
        if (isalpha(nombre_Apellido[i])){
            i++;
        }
        else {
            flag=1;
        }
    }
    return flag;
}

          ///CREA BACKUP DEL ARCHIVO ORIGINAL////
void creaBackUp (char archivo [], char nuevoArchivo []) {
  FILE *file1 , *file2;
    int data1 =0;

    file1 = fopen ( archivo, "r" );
    file2 = fopen ( nuevoArchivo , "w" );

    while ( (data1 = fgetc ( file1 )) != EOF ) {
        fputc ( data1, file2 );
        }

    fclose ( file1 );
    fclose ( file2 );

    return 0;
}



///  =============================                 FUNCIONES DE CONSUMOS    =================================================///

void altaConsumo (char archivoConsumos[], int idStCliente) {
    int mes[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
     int validacion=0;
    int validacion2=0;
    int vDia=0;
    int idCliente=idStCliente;
    int vMes=0;
    int vAnio=0;
    char opcion=0;
    int suma=0;
    stConsumos con;
    int id = cuentaRegistros(archivoConsumos, sizeof(stConsumos));

    FILE *pArchi = fopen(archivoConsumos,"ab");
    if (pArchi!= NULL) {
        do {


             do {
                printf("\n A%co ",164);
                scanf("%d" , &con.anio);
                vAnio=cargaAnio(con.anio);
             }while(vAnio==0);
            do {
                printf("\nMes ");
                scanf("%d" , &con.mes);
                vMes=cargaMes(con.mes);
             }while(vMes==0);
             do {
                printf("\nDia\t");
                scanf("%d" , &con.dia);
                vDia=cargaDia(con.dia);
             }while(vDia==0);

            printf("\n MB consumidos en la fecha: ");
            scanf("%d", &con.datosConsumidos);
            con.idCliente=idCliente;
            con.estado=1;
            id++;
            con.id = id;
             if (sumaConsumoFecha(con)>0){
                suma=sumaConsumoFecha(con);
                con.datosConsumidos=suma;
                }
            fwrite(&con, sizeof(stConsumos), 1, pArchi);
            printf("\n ESC para salir.");
            opcion=getch();
            system("cls");
        } while(opcion!=27);
        fclose(pArchi);
    } else {
        printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}

void muestraUnConsumo (stConsumos consumo) {


        printf("\n Id Numero              %d", consumo.id);
        printf("\n Id de Cliente numero   %d", consumo.idCliente);
        printf("\n A%co                  [%d]",164, consumo.anio);
        printf("\n Mes                   [%d]", consumo.mes);
        printf("\n Dia                   [%d]", consumo.dia);
        printf("\n Consumos del dia      [%d]mb", consumo.datosConsumidos);
        printf("\n[1]activo[0]inactivo  -[%d]-", consumo.estado);///0 para inactivo, 1 para activo
        printf("\n-------------------------------------------------------");

}

///MUESTRA LISTA DE CLIENTES DESDE UN ARCHIVO////
void muestraListaConsumos () {
    stConsumos con;
    FILE *pArchi= fopen(nomArchiConsumos, "rb");

    if(pArchi) {
            system("cls");
        while(fread(&con, sizeof(stConsumos), 1, pArchi)>0) {
            muestraUnConsumo(con);
        }
        fclose(pArchi);

    } else {
        printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}

char menuConsumo() {
    char opcion;


    system("cls");
    system("color 3F");
    printf("\n\t\t\t Busqueda por:");
    printf("\n 1 - Fecha");
    printf("\n 2 - id");
    //system("cls");
    printf("\n\nESC para salir");
    printf("\n\n\t Elija una opcion\n\n");

    opcion=getch();
    system("cls");
    return opcion;
}

void muestraConsumoPorIdCliente (int idClien) {
    stConsumos aux;
    int flag=0;
    FILE *pArchiCons= fopen(nomArchiConsumos, "rb");
    if(pArchiCons) {
        while(flag!=1&&fread(&aux, sizeof(stConsumos), 1, pArchiCons)>0) {
            if(aux.idCliente==idClien) {
                muestraUnConsumo(aux);
                }
            }
            fclose(pArchiCons);
        } else {
            printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}

/// busca por fecha
int sumaConsumoFecha(stConsumos a){
    stConsumos fecha;
    stConsumos arrayConsumos [100];
    int i=0;
    FILE *archi=fopen ("consumos.dat", "rb");
    if (archi) {
        while (fread(&fecha, sizeof(stConsumos), 1, archi)>0){
            if (fecha.anio== a.anio && fecha.mes==a.mes && fecha.dia == a.dia){
                i=fecha.datosConsumidos+a.datosConsumidos;
                }
            }
            fclose(archi);
    }
    return i;
}


///funcion de suma
int sumaConsumo(int a) {
    int suma=0;
    suma= suma + a;
    return suma;
}
/// verifica si el cliente existe
int existeConsumoCliente(char archivo[],int idCliente) {
    int flag=0;
    stClientes aux;
    stConsumos auxC;
    FILE *pArchi= fopen(archivo, "rb");
    if (pArchi) {
        while(fread(&aux, sizeof(stClientes), 1, pArchi)>0 && flag==0) {
            if(aux.id==idCliente) {
                auxC.idCliente=idCliente;
                flag=1;
            }
        }
        fclose(pArchi);
    }
    return flag;
}

///CARGA MES VALIDANDO DATO///
int cargaMes(int fecha) {
    int flag=0;
        if (fecha>=1 && fecha<=12) {
            flag=1;
        } else {
            printf("\n Mes incorrecto\n");
            system("pause");
        }
    return flag;
}


///CARGA DIA VALIDANDO DATO///
int cargaDia (int dato) {
    int flag=0;
        if (dato > 0 && dato < 31) {
            flag=1;
            }else{
    printf("\n Dia incorrecto\n");
    system("pause");
    }
            return flag;
}


///CARGA AÑO VALIDANDO DATO///
int cargaAnio(int anio) {
 int flag = 0;
    if(anio<=ANIO && anio > (ANIO-20)) {
        flag=1;
    }else{
    printf("\n Ingrese a%co dentro los ultimos 20 a%os\n",164,164);
    system("pause");
    }
  return flag;
}

///MUESTRA POR FECHA AXACTA///
void mostrarXFecha(char archivoConsumo[]) {
    stConsumos fecha;
    stConsumos a;
    int flag=0;
    system("cls");

    printf(" Ingrese la Fecha a Buscar Consumos \n");
    printf("\n ingrese el a%co\n",164);
    scanf("\n %d", &fecha.anio);
    printf("\n ingrese el mes\n");
    scanf("\n %d", &fecha.mes);
    printf("\n ingrese un dia\n");
    scanf("\n %d", &fecha.dia);

    FILE *archi=fopen ("consumos.dat", "rb");
    if (archi) {
        while (fread(&a, sizeof(stConsumos), 1, archi)>0){
            if (fecha.anio== a.anio && fecha.mes==a.mes && fecha.dia == a.dia){
                muestraUnConsumo(a);
                flag=1;
            } else {
             flag=2;
            }
        }
        fclose(archi);
    }
     if (flag==2){
        printf("\nEn la Fecha Ingresada No Existen Consumos");
     }

}

///CAMBIA CONSUMO POR FECHA////

void cambiaConsumo(char archivoConsumo []){
    stConsumos fecha;
    stConsumos a;
    int consumo=0;
    int flag=0;

    printf("Ingrese el numero de cliente");
    scanf("%d", &fecha.idCliente);
    printf(" Ingrese la Fecha del Consumo a Cambiar \n");
    printf("\n ingrese el anio\n");
    scanf("\n %d", &fecha.anio);
    printf("\n ingrese el mes\n");
    scanf("\n %d", &fecha.mes);
    printf("\n ingrese un dia\n");
    scanf("\n %d", &fecha.dia);

    FILE *archi = fopen(archivoConsumo, "r+b");
     if (archi) {
            while (fread(&a, sizeof(stConsumos), 1, archi)){
            if (fecha.anio== a.anio && fecha.mes==a.mes && fecha.dia == a.dia && fecha.idCliente==a.idCliente && flag==0){
                fseek(archi, sizeof(stConsumos)*(-1), SEEK_CUR);
                printf("\nINGRESE EL NUEVO CONSUMO\n");
                scanf("%d", &a.datosConsumidos);
                fwrite(&a, sizeof(stConsumos), 1, archi);
                fseek(archi, sizeof(stConsumos), SEEK_SET);
                flag=1;
            }

    }
        fclose(archi);

}
}

            /// FUNCIONES PARA CARGA ALEATORIO///

 int clienteRandom (){
     srand(time(NULL));
     int cantRegi;
     int random=0;
     cantRegi=cuentaRegistros(nomArchivo,sizeof(stClientes));
    int numRegistro;
        random=rand()%cantRegi;
        if(random>0){
            numRegistro=random;
            }
    return numRegistro;
 }

  /// MES ALEATORIO///
 int mesRandom (){
     srand(time(NULL));
    int mesR=0;

    while (mesR==0){
            mesR=rand()%12;
            }
    return mesR;
 }
        /// DIA ALEATORIO///
 int diaRandom (){
     srand(time(NULL));
    int diaR=0;

    while (diaR==0){
            diaR=rand()%30;
            }
    return diaR;
 }
        ///  CARGA CONSUMO A UN CLIENTE, EN EL DIA Y UN MES ALEATORIO///
 void altaConsumoRandom (char archivoConsumos[], int idStCliente, int mesR, int dia) {
    int mes[12]= {31,28,31,30,31,30,31,31,30,31,30,31};
    int idCliente=idStCliente;
    char opcion=0;
    int suma=0;
    stConsumos con;
    int id = cuentaRegistros(archivoConsumos, sizeof(stConsumos));

    FILE *pArchi = fopen(archivoConsumos,"ab");
    if (pArchi) {
            con.anio=2021;
            con.mes=mesR;
            con.dia=dia;

            con.datosConsumidos=1000;
            con.idCliente=idCliente;
            con.estado=1;
            id++;
            con.id = id;
             if (sumaConsumoFecha(con)>0){
                suma=sumaConsumoFecha(con);
                con.datosConsumidos=suma;
                }
            fwrite(&con, sizeof(stConsumos), 1, pArchi);


        fclose(pArchi);
    } else {
        printf("/n ERROR DE APERTURA DE ARCHIVO ");
    }
}

///BUSCA UN CLIENTE DESDE LA POSICION DEL ARCHIVO///
stClientes buscaIdCliente(char archivo[], int pos){
    stClientes aux;
    FILE *pArch = fopen(archivo, "rb");

    if(pArch && pos >= 0 && pos <= cuentaRegistros(archivo, sizeof(stClientes))){
        fseek(pArch, sizeof(stClientes)*pos, 0);
        fread(&aux, sizeof(stClientes), 1, pArch);

        fclose(pArch);
    }

    return aux;
}


///BUSCA CLIENTE POR NUMERO DE ID///
stClientes buscaPorId ( int id){

    stClientes aux;
    stClientes cliente;
    cliente.id=-1;


    int flag=0;
    FILE *pArchi = fopen(nomArchivo,"rb");
    if (pArchi){
    while (flag==0&&fread(&aux,sizeof(stClientes),1,pArchi)>0){
        if(aux.id==id){
            cliente=aux;
            flag=1;
            }
        }
        fclose(pArchi);
        }
    return cliente;
}
