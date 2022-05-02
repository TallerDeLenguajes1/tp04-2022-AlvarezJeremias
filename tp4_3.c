
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct task {
    int IDtarea;
    char * descripcion;
    int duracion;
} tarea;

typedef struct nodo {
    tarea T;
    struct nodo * next;
} nodo;

nodo * CrearListaVacia();
nodo * CrearNodo (int cantidad, int i);
void InsertarNodo(nodo ** lista, nodo *nodo);
nodo * BorrarNodo(nodo ** lista);
tarea CrearTarea (int cantidad, int i);
void CambioTareas (nodo ** lista, nodo ** pendientes, nodo ** realizadas,int i);
void MostrarLista(nodo * lista);
int main () {
    srand(time(NULL));
    int cantidadTareas=0;
    while (cantidadTareas== 0 || cantidadTareas>10) {
        printf ("\ningrese la cantidad de tareas a realizar: ");
        scanf ("%d", &cantidadTareas);
        // fflush(stdin);
    }
    nodo * lista = CrearListaVacia();
    nodo * listaRealizadas= CrearListaVacia();
    nodo * listaPendientes=CrearListaVacia();
    nodo * busquedaClave=CrearListaVacia();
    nodo * busquedaID=CrearListaVacia();
    nodo * auxiliar;


    for (int i = 0; i < cantidadTareas; i++) {
        auxiliar=CrearNodo(cantidadTareas,i);
        InsertarNodo(&lista,auxiliar);
    }

    CambioTareas(&lista, &listaPendientes,&listaRealizadas,cantidadTareas);

    printf("\n------Tareas Pendientes------\n\n");
    MostrarLista(listaPendientes);
    printf("\n------Tareas Realizadas------\n");
    MostrarLista(listaRealizadas);
    return 0;

}

nodo * CrearListaVacia() {
    return NULL;
}
nodo * CrearNodo(int cantidad, int i) {
    nodo * nuevoNodo= (nodo * ) malloc (sizeof(nodo));
    nuevoNodo->T=CrearTarea(cantidad,i);
    nuevoNodo->next=NULL;
    return nuevoNodo;
}

void InsertarNodo(nodo ** lista, nodo * nodo) {
    nodo->next=*lista;
    *lista=nodo;
}
tarea CrearTarea (int cantidad, int i) {
    char * cadena= (char *) malloc(sizeof(char)*200);
    printf ("\n\nEscriba la descripcion de la tarea %d: ", i+1); 
    fflush(stdin);
    getchar();
    fgets(cadena,200,stdin);
    fflush (stdin);
    getchar();
    tarea nuevaTarea;
    nuevaTarea.IDtarea= i +1;
    nuevaTarea.descripcion=(char*)malloc(sizeof(char)*strlen(cadena)+1);
    strcpy(nuevaTarea.descripcion,cadena);
    nuevaTarea.duracion=rand() %91 + 10;
    return nuevaTarea;
}

nodo * BorrarNodo (nodo ** lista) {
    nodo * auxiliar= *lista;
    *lista= (*lista)->next;
    auxiliar->next=NULL;
    return auxiliar;
}

void CambioTareas(nodo ** lista,  nodo ** pendientes, nodo ** realizadas, int cantidad) {
    char progreso;  /*La verdad es que me niego a ponerme a investigar el motivo del demonio por el cual esta funcion pregunta primero por el ultimo nodo
     y luego va descendiendo como River. La verdad es que ya estoy cansado y estoy 100% de que la explicacion es una bien simple, pero ya tengo el cerebro 
     plano como una calle recien pavimentada, y me niego a seguir probando.  */
    nodo * auxiliar;
    for (int i=0 ; i<cantidad;i++) {
        printf("\n\nLa tarea es la numero %d, ¿se ha terminado? \n inserte la letra Y si la respuesta es SI, cualquier otra letra si la respuesta es NO :  ", (*lista)->T.IDtarea);/* volvimos a la era del [y/n], maravilloso viteh.*/
        scanf("%c",&progreso);   /* En este sistema operativo, los fflush funcionan el 10% de las ocasiones, y si dejo los fflush andando en mi codigo, a mi me genera problemas
        pero al siguiente que pruebe el codigo mediante otro OS (como el ventanitas) seguramente le salga mejor este desastre si activa los fflush y comenta los getchar
        Dicho esto, ¿porque todo tiene que ser tan complicado? */
        // fflush(stdin);
        getchar();
        auxiliar=BorrarNodo(lista);
        if (progreso == 'y' || progreso== 'Y') {
            InsertarNodo(realizadas,auxiliar);
        } else {
            InsertarNodo(pendientes,auxiliar);
        }
    }

}
void MostrarLista(nodo * lista) {
    while (lista !=NULL){
        printf("\n\n ---Tarea numero %d---", lista->T.IDtarea);
        printf("\nDescripcion: ");
        puts(lista->T.descripcion);
        printf("Duracion: %d\n",lista->T.duracion);
        lista=lista->next;
    }
}
