#include <stdio.h>

#define MAX_PLAYER_NAME 50
#define INITIAL_PLAYER_ENERGY 100
#define INITIAL_PLAYER_CELL 0
#define NO_OBJECT -1
#define NO_TREASURE -1
#define MAX_CELL_DESCRIPTION 200
#define MAX_CELL 50

struct Player{ 
  char name[MAX_PLAYER_NAME];
  int energy;
  int cell;
  int object;
  int treasure;
};

struct Cell{
    int north;
    int south;
    int east;
    int west;
    int up;
    int down;
    char description[MAX_CELL_DESCRIPTION];
    int object;
    int treasure;
};

void init_player(struct Player *player){
    //Uses pointer to modify the variable through it's memory address
    //Asks the Player what is name is
    printf("Hi Player!\nWhat is your name?\n");

    //Reads the Player name from the keyboard
    scanf("%s", player->name);

    //Sets the Player energy, cell, object and treasure
    player->energy = INITIAL_PLAYER_ENERGY;
    player->cell = INITIAL_PLAYER_CELL;
    player->object = NO_OBJECT;
    player->treasure = NO_TREASURE;
}

void print_player(struct Player player){
    printf("Player Name = %s\n", player.name);
    printf("Player Energy = %d\n", player.energy);
    printf("Player Cell = %d\n", player.cell);
    printf("Player Object = %d\n", player.object);
    printf("Player Treasure = %d\n", player.treasure);
}

void init_map(){

}

int main(){

    struct Player player;
    struct Cell map[MAX_CELL];
    int n_cells;

    //Sends the memory address of the player structure
    init_player(&player);

    //print_player
    print_player(player);

    //init_map()
    init_map();
    map[0].north = -1;
    map[0].south = -1;
    map[0].west = -1;
    map[0].east = 1;
    map[0].up = -1;
    map[0].down = -1;
    map[0].object = -1;
    strcpy(map[0].description = "");

    return 0;
}

