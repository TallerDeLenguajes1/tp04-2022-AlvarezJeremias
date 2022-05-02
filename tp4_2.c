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
void buscar(tareas ** pendientes, tareas ** realizadas, int cantidad);


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
    buscar(pendientes,realizadas,cantidadTareas);
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
void buscar(tareas **pendientes,tareas **realizadas, int cantidad){

    printf("Donde desea buscar?\n1)En Tareas Pendientes\n2)En Tareas Realizadas\n");
    int op;
    scanf("%d",&op);
    fflush(stdin);
    getchar();
    switch (op){
        case 1:
            printf("\nIngrese la palabra clave de la tarea que desea buscar: ");
            char *aux=(char*)malloc(sizeof(char)*100);
            fgets(aux,100,stdin);
            for(int i=0;i<cantidad;i++){
               if(pendientes!=NULL){
                    int tam1= strlen(pendientes[i]->descripcion),
                    tam2=strlen(aux), j=0;
                    char c;
                    if(tam2 > tam1){
                        printf("La palabra buscada es mas grande\n");
                        return NULL;
                    }else{
                        c=aux[0];
                        while (j < tam1)
                        {
                            if(pendientes[i]->descripcion[j]== c){
                                if(strncmp(&pendientes[i]->descripcion[j],aux,tam2)==0){
                                    mostrarUna(pendientes[i]);
                                }
                            }
                            j++;
                        }
                    }
               }else{
                   continue;
               }
            }
            break;
        case 2:
            printf("\nIngrese el ID de la tarea que desea buscar: ");          
            int id;
            scanf("%d",&id);
            fflush(stdin);
            for(int i=0;i<cantidad;i++){
                if((i+1)==id && realizadas[i]!=NULL){
                    mostrarUna(realizadas[i]);
                }else if(realizadas[i]==NULL && (i+1)==id){
                        printf("\t\tNo se encontró la tarea\n");
                }
                if(id>cantidad || cantidad < 0){
                    printf("\t\tNo se encontró la tarea\n");
                }
                if(realizadas[i]==NULL){
                    continue;
                }
            }
            break;
    }
}