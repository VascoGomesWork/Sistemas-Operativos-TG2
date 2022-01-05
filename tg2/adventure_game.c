#include <stdio.h>
#include <string.h>

#define MAX_PLAYER_NAME 50
#define INITIAL_PLAYER_ENERGY 100
#define INITIAL_MONSTER_ENERGY 100
#define INITIAL_PLAYER_CELL 0
#define INITIAL_MONSTER_CELL 1
#define NO_OBJECT -1
#define NO_TREASURE -1
#define MAX_CELL_DESCRIPTION 200
#define MAX_CELL 50
#define MAX_OBJECT_NAME 50
#define MAX_NUMBER_OBJECT 50

struct Player{ 
  char name[MAX_PLAYER_NAME];
  int energy;
  int cell; //Player Location in the Map
  int object;
  int treasure;
};

struct Monster{
    int energy;
    int cell; //Monster Location in the Map
};

struct Object{
    char name[MAX_OBJECT_NAME];
    int figh_efficiency_level;
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

void init_map(struct Cell *map){
    map[0].north = -1;
    map[0].south = -1;
    map[0].west = -1;
    map[0].east = 1;
    map[0].up = -1;
    map[0].down = -1;
    map[0].object = -1;
    strcpy(map[0].description, "TESTE1");

    map[1].north = -1;
    map[1].south = -1;
    map[1].west = -1;
    map[1].east = 1;
    map[1].up = -1;
    map[1].down = -1;
    map[1].object = 1;
    strcpy(map[1].description, "TESTE 2");
}

void print_map(struct Cell *map, int n_cells){
    for(int i = 0; i < n_cells; i++){
        printf("-------Cell %d -----------------\n", i);
        printf("North = %d\n", map[i].north);
        printf("South = %d\n", map[i].south);
        printf("West = %d\n", map[i].west);
        printf("East = %d\n", map[i].east);
        printf("Up = %d\n", map[i].up);
        printf("Down = %d\n", map[i].down);
        printf("Object = %d\n", map[i].object);
        printf("Description = %s\n", map[i].description);
        printf("--------------------------------\n");
    }
    
}

void init_monster(struct Monster *monster){
    monster->energy = INITIAL_MONSTER_ENERGY;
    monster->cell = INITIAL_MONSTER_CELL;
}

void print_monster(struct Monster *monster){
    printf("Monster Energy = %d\n", monster->energy);
    printf("Monster Cell = %d\n", monster->cell);
}

void change_monster_cell(struct Monster *monster, int cell){
    monster->cell = cell;
}

void change_monster_energy(struct Monster *monster, int energy){
    monster->energy = energy;
}

void change_player_energy(struct Player *player, int energy){
    player->energy = energy;
}

int get_monster_energy(struct Monster *monster){
    return monster->energy;
}

int get_player_energy(struct Player *player){
    return player->energy;
}

int main(){

    struct Player player;
    struct Monster monster;
    struct Cell map[MAX_CELL];
    int n_cells = 4;
    struct Object object[MAX_NUMBER_OBJECT];

    //Sends the memory address of the player structure to the function init_player()
    init_player(&player);

    //print_player
    print_player(player);

    //Sends the memory address of the map structure to the function init_map()
    init_map(map);
     
    print_map(map, n_cells);

    init_monster(&monster);

    print_monster(&monster);

    /*
    //Need to Use Threads to make the interation between the player and the monster
    Enquanto não for fim de jogo
        {
        Movimentar monstro
        Descrever a localização do jogador
        Aceitar comando do jogador
        Movimentar jogador
        Se a localização do jogador e monstro forem iguais
        Lutar
        }
    Apresentar resultado final
    */
    change_player_energy(&player, 0);
    //change_monster_energy(&monster, 0);
    printf("Player Energy = %d\n", get_player_energy(&player));
    do
    {
        change_monster_cell(&monster, 2);
        print_monster(&monster);
        change_monster_energy(&monster, 0);
    }while (get_player_energy(&player) > 0 || get_monster_energy(&monster) > 0);
    printf("-------GAME OVER---------\n");

    return 0;
    
}

