#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

void print_map(struct Cell *map, int n_cells){
    for(int i = 0; i < n_cells; i++){
        printf("-------Cell %d -----------------\n", i);
        printf("Description = %s\n", map[i].description);
        printf("North = %d\n", map[i].north);
        printf("South = %d\n", map[i].south);
        printf("West = %d\n", map[i].west);
        printf("East = %d\n", map[i].east);
        printf("Up = %d\n", map[i].up);
        printf("Down = %d\n", map[i].down);
        printf("Object = %d\n", map[i].object);
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

void change_player_cell(struct Player *player, int cell){
    player->cell = cell;
}

void change_monster_energy(struct Monster *monster, int energy){
    monster->energy = monster->energy - energy;
}

void change_player_energy(struct Player *player, int energy){
    player->energy = player->energy - energy;
}

int get_monster_energy(struct Monster *monster){
    return monster->energy;
}

int get_player_energy(struct Player *player){
    return player->energy;
}

int get_player_cell(struct Player *player){
    return player->cell;
}

int get_monster_cell(struct Monster *monster){
    return monster->cell;
}

void get_player_descrition_location(struct Player *player, struct Cell *map){
    printf("\nPlayer Cell Description: \n%s\n",map[player->cell].description);
        printf("----------------- Cell %d -----------------\n", player->cell);
        printf("0 - North = %d\n", map[player->cell].north);
        printf("1 - South = %d\n", map[player->cell].south);
        printf("2 - West = %d\n", map[player->cell].west);
        printf("3 - East = %d\n", map[player->cell].east);
        printf("4 - Up = %d\n", map[player->cell].up);
        printf("5 - Down = %d\n", map[player->cell].down);
        printf("Object = %d\n", map[player->cell].object);
}

int read_player_input(struct Player *player, struct Cell *map){
    int cell_array[6] = {map[player->cell].north, map[player->cell].south, map[player->cell].west, map[player->cell].east, map[player->cell].up, map[player->cell].down};
    int selected_option = 0;
    int cell = -1;
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

int random_get_monster_cell(struct Monster *monster, struct Cell *map){
    int cell_array[6] = {map[monster->cell].north, map[monster->cell].south, map[monster->cell].west, map[monster->cell].east, map[monster->cell].up, map[monster->cell].down};
    int cell = -1;
    int random = 0;
    //Check if the position to where the monster wants to move is possible or not
    do{
        //Do a random so, the mosnter can be moved
        random = (rand() % 5);
        cell = cell_array[random];
        printf("Rando Number = %d\n", cell);
    }while(cell == -1);
    return cell;
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
    //print_player(player);

    //Sends the memory address of the map structure to the function init_map()
    init_map(map);
     
    //print_map(map, n_cells);

    init_monster(&monster);

    //print_monster(&monster);

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
    int player_cell_input = 0;
    printf("Player Energy = %d\n", get_player_energy(&player));
    do
    {
        change_monster_cell(&monster, random_get_monster_cell(&monster, map));
        //print_monster(&monster);

        //while the player cell && monster cell are different from one another player and monster moves
        while(get_player_cell(&player) != get_monster_cell(&monster)){
            print_monster(&monster);
            get_player_descrition_location(&player, map);
            //Gets the cell that the player choosed
            player_cell_input = read_player_input(&player, map);
            change_player_cell(&player, player_cell_input);
        }
        //while(get_player_cell(&player) == get_monster_cell(&monster) && get_monster_energy(&monster) > 0 && get_player_energy(&player) > 0){
        if(get_player_cell(&player) == get_monster_cell(&monster)){
            printf("\nLUTAR\n");
            change_monster_energy(&monster, 10);
        }
        //change_player_energy(&player, 100);
        
    }while (get_monster_energy(&monster) > 0 && get_player_energy(&player) > 0);
    
    //Greats the Player for winning the game or losing
    if(get_player_energy(&player) <= 0){
        printf("-------GAME OVER---------\n");
    }
    else{
        printf("-------CONGRATS YOU WON!!---------\n");
    }

    return 0;
    
}

