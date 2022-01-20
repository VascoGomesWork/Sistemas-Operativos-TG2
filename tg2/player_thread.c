#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_PLAYER_NAME 50
#define INITIAL_PLAYER_ENERGY 100
#define INITIAL_MONSTER_ENERGY 100
#define INITIAL_PLAYER_CELL 0
#define INITIAL_MONSTER_CELL 4
#define NO_OBJECT -1
#define NO_TREASURE -1
#define MAX_CELL_DESCRIPTION 200
#define MAX_CELL 50
#define MAX_OBJECT_NAME 50
#define MAX_NUMBER_OBJECT 50

typedef struct player{ 
  char name[MAX_PLAYER_NAME];
  int energy;
  int cell; //Player Location in the Map
  int object;
  int treasure;
}Player;

typedef struct cell{
    int north;
    int south;
    int east;
    int west;
    int up;
    int down;
    char description[MAX_CELL_DESCRIPTION];
    int object;
    int treasure;
}Cell;

typedef struct monster{
    int energy;
    int cell; //Monster Location in the Map
}Monster;

void init_map(Cell *map){
    map[0].north = -1;
    map[0].south = -1;
    map[0].west = -1;
    map[0].east = 1;
    map[0].up = -1;
    map[0].down = -1;
    map[0].object = -1;
    map[0].treasure = -1;
    strcpy(map[0].description, "Você está na entrada de uma masmorra.\n Existe um monstro que tem de derrotar para chegar ao tesouro\n");

    map[1].north = -1;
    map[1].south = 2;
    map[1].west = 0;
    map[1].east = 3;
    map[1].up = -1;
    map[1].down = -1;
    map[1].object = -1;
    map[1].treasure = -1;
    strcpy(map[1].description, "Esta é a sala 1 da masmorra");

    map[2].north = 1;
    map[2].south = -1;
    map[2].west = -1;
    map[2].east = 4;
    map[2].up = -1;
    map[2].down = -1;
    map[2].object = 1;
    map[2].treasure = -1;
    strcpy(map[2].description, "Você chegou a sala 2 da masmorra. Esta contem um objeto para combater o monstro!");

    map[3].north = -1;
    map[3].south = -1;
    map[3].west = 1;
    map[3].east = -1;
    map[3].up = -1;
    map[3].down = -1;
    map[3].object = 1;
    map[3].treasure = -1;
    strcpy(map[3].description, "Esta é a sala 3, aqui pode encontrar um objeto");

    map[4].north = -1;
    map[4].south = -1;
    map[4].west = 2;
    map[4].east = -1;
    map[4].up = -1;
    map[4].down = -1;
    map[4].object = -1;
    map[4].treasure = 1;
    strcpy(map[4].description, "Esta é a sala 5, e para chegar ao tesouro, você tem de derrotar o monstro");
}

void * change_monster_cell(void * monster){
    printf("Monster Moving");
}

void * change_player_cell(void * player){
     
    printf("Player Moving");
}



int read_player_input(Player *player){
    Cell map[MAX_CELL];
    init_map(map);
    int cell_array[6] = {map[player->cell].north, map[player->cell].south, map[player->cell].west, map[player->cell].east, map[player->cell].up, map[player->cell].down};
    int cell = -1;
    int selected_option = 0;
    do{
        printf("Observe os pontos do mapa e indique para que celula se quer mover\n");
        //Reads the Player Input from the keyboard
        scanf("%d", &selected_option);
        //Gets 
        cell = cell_array[selected_option];
        printf("CELL = %d\n", cell);

    }while(cell == -1);
    return cell;
}

int get_player_cell(Player *player){
    return player->cell;
}

int get_monster_cell(Monster *monster){
    return monster->cell;
}

int main(){

    Player player;
    Cell map[MAX_CELL];
    Monster monster;
    //Player Thread Creation Using pthread Lybrary
    pthread_t player_thread;
    pthread_t monster_thread;

    pthread_create(&monster_thread, NULL, change_monster_cell, (void *) &monster);
    pthread_create(&player_thread, NULL, change_player_cell, (void *) &player);
    //pthread_join(player_thread, NULL);
    int i = 0;
    do
    {
        
        printf("THREAD\n");
        //Calls already Created Monster_Cell
        change_monster_cell(&monster);
        
        //print_monster(&monster);
        //get_player_descrition_location(&player, map);
            
        //Calls Already Created Player_Cell
        change_player_cell(&player);
        
        if(get_player_cell(&player) == get_monster_cell(&monster)){
            //pthread_join makes the main thread wait for the other threads to finish
            //pthread_join(monster_thread, NULL);
            
            printf("\nLUTAR\n");
            //change_monster_energy(&monster, 10);
        } 
        i++;
    }while (i < 6);

}