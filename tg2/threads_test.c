#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct monster{
    int energy;
    int cell; //Monster Location in the Map
}Monster;

typedef struct map{
    int north;
}Map;

int return_cell(Monster * monster){
    Map * cell;
    return 20;
}

void * change_monster_cell(void * monster){
    //monster->cell = cell;
    //ThreadData *my_data  = (ThreadData*)thread;
    Monster * monster1 = (Monster*)monster;// = (struct Monster_Thread_Struct *)arg->monster;
    //malloc(sizeof(&monster));
    
    monster1->cell = return_cell(monster1);

    //printf("MONSTER THREAD CELL = %d\n", monster->cell);
    
    
    pthread_exit(NULL);
    //return NULL;
}

int main(){

    //struct Monster_Thread_Struct monster_thread_struct;
    Monster monster;
    monster.cell = 2;

    pthread_t monster_thread;
    
    printf("Valor antes de alterado pela thread = %d\n", monster.cell);

    pthread_create(&monster_thread, NULL, change_monster_cell, (void *) &monster);
    pthread_join(monster_thread, NULL);

    printf("Valor depois de alterado pela thread = %d\n", monster.cell);

    return 0;
}