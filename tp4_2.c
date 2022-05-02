#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

struct Tareas {
    int tareaID; //Numerado en ciclo iterativo
    char *descripcion;
    int duracion; //entre 10-100
}typedef tareas;

tareas * cargarTarea (int id);
bool preguntarProgreso();
void mostrarTareas(tareas ** tarea, int cantidad);
void mostrarUna (tareas * tarea);
void controlarTareas(tareas ** realizadas, tareas ** pendiente, int cantidad);
void liberarMemoria (tareas ** pendiente, tareas ** realizadas, int cantidad);

int main() {
    srand(time(NULL));

    printf("\n\nIngrese la cantidad de tareas: ");
    int cantidadTareas;
    scanf("%d",&cantidadTareas);
    getchar();
    fflush(stdin);
    tareas ** pendientes, **realizadas;
    pendientes= (tareas **)malloc(sizeof(tareas*)*cantidadTareas);
    realizadas= (tareas **)malloc(sizeof(tareas*)*cantidadTareas);
    
    for (int i=0;i<cantidadTareas;i++) {
        pendientes[i]=cargarTarea((i+1));
    } 
    printf("\n\n-----------Tareas Pendientes-----------\n");
    mostrarTareas(pendientes,cantidadTareas);
    controlarTareas(realizadas,pendientes,cantidadTareas);
    printf("\n\n-----------Tareas realizadas-----------\n");
    mostrarTareas(realizadas,cantidadTareas);
    printf("\n\n-----------Tareas Pendientes-----------\n");
    mostrarTareas(pendientes,cantidadTareas);
    fflush(stdin);
    getchar();
    liberarMemoria(pendientes,realizadas,cantidadTareas);
}
tareas * cargarTarea(int id) {
    tareas * unaTarea= (tareas*) malloc(sizeof(tareas));
    unaTarea->tareaID=id;
    printf("\n\n-----------------Tarea numero %d-----------------\n", id);
    printf("\n\nIngrese la descripcion de la tarea: ");
    char * buff=(char *)malloc (sizeof(char)*100);
    fgets(buff,100,stdin);
    getchar();
    fflush(stdin);

    unaTarea->descripcion=(char*) malloc(sizeof(char)*(strlen(buff)+1));
    strcpy(unaTarea->descripcion,buff);
    free(buff);
    unaTarea->duracion=rand()%(100-10+1)+10;

    return unaTarea;

}

bool preguntarProgreso(){
    printf("\t\tRealizó la tarea?\n\t\tY para confirmar.\n\t\tCualquier letra para denegar.\n");
    char letra;
    scanf("%c",&letra);
    fflush(stdin);
    getchar();
    
    if(letra == 'y' || letra == 'Y'){
        return true;
    }else{
        return false;
    }
}
void mostrarUna (tareas * tarea){
    printf("ID tarea %d\n", tarea->tareaID);
    printf("%s",tarea->descripcion);
    /* puts(tareas->descripcion); */
    printf("\nDuración %d",tarea->duracion);
    printf("\n\n----------------------------------------------------------------------------\n");
}

void mostrarTareas(tareas ** tarea, int cantidad){
    for(int i=0;i<cantidad;i++){
        if(tarea[i] != NULL){
            mostrarUna(tarea[i]);
        }else{
            continue;
        }
    }
}

void controlarTareas(tareas **realizadas,tareas **pendientes, int cantidad){
    for(int i=0;i<cantidad;i++){
       printf("\t\tTarea %d\n", i+1);
       
       if(preguntarProgreso()){
           realizadas[i]=(tareas*)malloc(sizeof(tareas));
           realizadas[i]=pendientes[i];
           pendientes[i]=NULL;
       }else{
           realizadas[i]=NULL;
       }
    }
}

void liberarMemoria(tareas **pendientes,tareas **realizadas,int cantidad){
    for(int i=0;i<cantidad;i++){
        if(pendientes[i]!=NULL){
          free(pendientes[i]->descripcion);
          free(pendientes[i]);
        }
        if(realizadas[i]!=NULL){
          free(realizadas[i]->descripcion);
          free(realizadas[i]);
        }
    }
}
