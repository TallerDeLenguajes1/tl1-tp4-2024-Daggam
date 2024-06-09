#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int idglobal = 1000; //Autoincremental.

struct Tarea{
    int TareaID;
    char *Descripcion; //
    int Duracion;
}typedef Tarea;

typedef struct Nodo Nodo;
struct Nodo{
    Tarea T;
    Nodo *Siguiente;
};

//Funciones de Listas
void insertarNodoTarea(Nodo** ListaTareas, char* Descripcion, int Duracion);
void mostrarListaTareas(Nodo* ListaTareas);
void mostrarTarea(Nodo* Tarea);

int cargarTareasPendientes(Nodo** Tarea);
void transferirTareas(Nodo** ListaTareasPendientes, Nodo** ListaTareasRealizadas);
int consultarTarea(Nodo* LTareas, int id);

int main(){
    Nodo* TareasPendientes = NULL;
    Nodo* TareasRealizadas = NULL;
    puts("Bienvenido al sistema de tareas.");
    do
    {
        if(!cargarTareasPendientes(&TareasPendientes)){
            break;
        }
    } while (1);
    
    int opciones;
    do
    {
        puts("-- Menu Tareas --");
        puts("1. Marcar tarea realizada.");
        puts("2. Ver tareas.");
        puts("3. Consultar tarea.");
        puts("4. Salir");
        printf("Ingrese una de las opciones: ");
        scanf("%d",&opciones);
        switch (opciones)
        {
        case 1:
            transferirTareas(&TareasPendientes,&TareasRealizadas);
            break;
        case 2:
            puts("-- Lista de tareas pendientes --");
            mostrarListaTareas(TareasPendientes);
            puts("-- FIN --");
            puts("-- Lista de tareas realizadas --");
            mostrarListaTareas(TareasRealizadas);
            puts("-- FIN --");
            break;
        case 3:
            printf("Ingrese la ID de la tarea a consultar: ");
            int idTarea;
            scanf("%d",&idTarea);
            if (consultarTarea(TareasPendientes,idTarea)){
                puts("ES UNA TAREA PENDIENTE.");
            }else if(consultarTarea(TareasRealizadas,idTarea)){
                puts("ES UNA TAREA REALIZADA.");
            }else{
                puts("LA TAREA NO FUE ENCONTRADA");
            }

            break;
        case 4:
            puts("Chau!!!");
            break;
        default:
            puts("Opcion invalida.");
            break;
        }
    } while (opciones!=4);
    
    return 0;
}

void insertarNodoTarea(Nodo **ListaTareas, char *Descripcion, int Duracion)
{
    Nodo* nuevoNodo = (Nodo*) malloc(sizeof(Nodo*));
    nuevoNodo->T.TareaID = idglobal++;
    nuevoNodo->T.Descripcion = (char*) malloc(strlen(Descripcion)+1);
    strcpy(nuevoNodo->T.Descripcion,Descripcion);
    nuevoNodo->T.Duracion = Duracion;
    nuevoNodo->Siguiente = *ListaTareas;
    *ListaTareas = nuevoNodo;
}

void mostrarListaTareas(Nodo *ListaTareas)
{
    while (ListaTareas!=NULL)
    {
        mostrarTarea(ListaTareas);
        ListaTareas = ListaTareas->Siguiente;
    }
    
}

void mostrarTarea(Nodo *Tarea)
{
    puts("-----------------------------------------------------------");
    printf("ID de la tarea: %d\n", Tarea->T.TareaID);
    printf("Descripcion de la tarea: %s\n", Tarea->T.Descripcion);
    printf("Duracion de la tarea: %d\n",Tarea->T.Duracion);
    puts("-----------------------------------------------------------");
}

int cargarTareasPendientes(Nodo **Tarea)
{
    
    int continuar;
    char* descripcion = (char*) malloc(100);
    int duracion;
    fflush(stdin);
    printf("Ingrese una descripcion para la tarea: ");
    gets(descripcion);
    do
    {
        printf("Ingrese la duracion: ");
        scanf("%d",&duracion);
        if(duracion< 10 || duracion > 100) puts("La duracion debe estar entre 10 y 100");
    } while (duracion< 10 || duracion > 100);
    
    insertarNodoTarea(Tarea,descripcion,duracion);

    free(descripcion);
    puts("Desea agregar otra tarea? Ingrese 1 para confirmar: ");
    scanf("%d",&continuar);
    return continuar==1;
}

void transferirTareas(Nodo **ListaTareasPendientes, Nodo **ListaTareasRealizadas)
{
    int id;
    printf("Ingrese el id de la tarea que desea transferir: ");
    scanf("%d",&id);

    Nodo* it = *ListaTareasPendientes;
    Nodo* anterior = NULL;
    while (it!=NULL)
    {
        if(it->T.TareaID == id){
            if(anterior!=NULL) anterior->Siguiente = it->Siguiente;
            it->Siguiente = *ListaTareasRealizadas;
            *ListaTareasRealizadas = it;
            break;
        }
        anterior = it;
        it = it->Siguiente;
    }

    if(it==NULL){
        puts("No se encontro una tarea con ese ID.");
    }else{
        puts("Tarea realizada con exito");
    }
}

int consultarTarea(Nodo *LTareas, int id)
{
    while (LTareas!=NULL)
    {
        if(LTareas->T.TareaID == id){
            mostrarTarea(LTareas);
            return 1;
        }
        LTareas = LTareas->Siguiente;
    }
    return 0;
}
