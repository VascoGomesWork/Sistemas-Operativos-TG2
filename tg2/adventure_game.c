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
#define MAX_TREASURE_NAME 50
#define MAX_NUMBER_OBJECT 50

typedef struct player{ 
  char name[MAX_PLAYER_NAME];
  int energy;
  int cell; //Player Location in the Map
  int object;
  int treasure;
}Player;

typedef struct monster{
    int energy;
    int cell; //Monster Location in the Map
}Monster;

typedef struct object{
    char name[MAX_OBJECT_NAME];
    int figh_efficiency_level;
}Object;

typedef struct cell{
    int north;
    int south;
    int east;
    int west;
    int up;
    int down;
    char description[MAX_CELL_DESCRIPTION];
    char object[MAX_OBJECT_NAME];
    char treasure[MAX_TREASURE_NAME];
}Cell;


/*struct Monster_Thread_Struct{
    struct Monster monster;
    int cell;
};*/

void init_player(Player *player){
    //Uses pointer to modify the variable through it's memory address
    //Asks the Player what is name is
    printf("Olá Jogador!\nQual é o seu Nome?\n");

    //Reads the Player name from the keyboard
    scanf("%s", player->name);

    //Sets the Player energy, cell, object and treasure
    player->energy = INITIAL_PLAYER_ENERGY;
    player->cell = INITIAL_PLAYER_CELL;
    player->object = NO_OBJECT;
    player->treasure = NO_TREASURE;
}

void print_player(Player player){
    printf("Nome do Jogador = %s\n", player.name);
    printf("Energia do Jogador = %d\n", player.energy);
    printf("Cell do Jogador = %d\n", player.cell);
    printf("Objecto do Jogador = %d\n", player.object);
    printf("Tesouro do Jogador = %d\n", player.treasure);
}

void init_map(Cell *map){
    map[0].north = -1;
    map[0].south = -1;
    map[0].west = -1;
    map[0].east = 1;
    map[0].up = -1;
    map[0].down = -1;
    strcpy(map[0].object, "Não existem objetos nesta sala\n");
    strcpy(map[0].treasure, "Não existem tesouros nesta sala\n");
    strcpy(map[0].description, "Você está na entrada de uma masmorra.\n Existe um monstro que tem de derrotar para chegar ao tesouro\n");

    map[1].north = -1;
    map[1].south = 2;
    map[1].west = 0;
    map[1].east = 3;
    map[1].up = -1;
    map[1].down = -1;
    strcpy(map[1].object, "Não existem objetos nesta sala\n");
    strcpy(map[1].treasure, "Não existem tesouros nesta sala\n");
    strcpy(map[1].description, "Esta é a sala 1 da masmorra");

    map[2].north = 1;
    map[2].south = -1;
    map[2].west = -1;
    map[2].east = 4;
    map[2].up = -1;
    map[2].down = -1;
    strcpy(map[2].object, "Existe um objeto nesta sala\n");
    strcpy(map[2].treasure, "Não existem tesouros nesta sala\n");
    strcpy(map[2].description, "Você chegou a sala 2 da masmorra. Esta contem um objeto para combater o monstro!");

    map[3].north = -1;
    map[3].south = -1;
    map[3].west = 1;
    map[3].east = -1;
    map[3].up = -1;
    map[3].down = -1;
    strcpy(map[3].object, "Existe um objeto nesta sala\n");
    strcpy(map[3].treasure, "Não existem tesouros nesta sala\n");
    strcpy(map[3].description, "Esta é a sala 3, aqui pode encontrar um objeto");

    map[4].north = -1;
    map[4].south = -1;
    map[4].west = 2;
    map[4].east = -1;
    map[4].up = -1;
    map[4].down = -1;
    strcpy(map[4].object, "Não existe um objeto nesta sala\n");
    strcpy(map[4].treasure, "O tesouro está nesta sala\n");
    strcpy(map[4].description, "Esta é a sala 5, e para chegar ao tesouro, você tem de derrotar o monstro");
}

void print_map(Cell *map, int n_cells){
    for(int i = 0; i < n_cells; i++){
        printf("-------Cell %d -----------------\n", i);
        printf("Descrição = %s\n", map[i].description);
        printf("Norte = %d\n", map[i].north);
        printf("Sul = %d\n", map[i].south);
        printf("Oeste = %d\n", map[i].west);
        printf("Este = %d\n", map[i].east);
        printf("Andar de Cima = %d\n", map[i].up);
        printf("Andar de Baixo = %d\n", map[i].down);
        printf("Objeto = %s\n", map[i].object);
        printf("Tesouro = %s\n", map[i].treasure);
        printf("--------------------------------\n");
    }
    
}

void init_monster(Monster *monster){
    monster->energy = INITIAL_MONSTER_ENERGY;
    monster->cell = INITIAL_MONSTER_CELL;
}

void print_monster(Monster *monster){
    printf("Energia do Monstro = %d\n", monster->energy);
    printf("Cell do Monstro = %d\n", monster->cell);
}

void * change_monster_cell(void * monster){
    Monster * monster1 = (Monster*)monster;
    monster1->cell = random_get_monster_cell(monster1);//Mudar para função random
}

void * change_player_cell(void * player){
     
    Player * player1 = (Player*)player;
    player1->cell = read_player_input(player1);
}

void change_monster_energy(Monster *monster, int energy){
    monster->energy = monster->energy - energy;
}

void change_player_energy(Player *player, int energy){
    player->energy = player->energy - energy;
}

int get_monster_energy(Monster *monster){
    return monster->energy;
}

int get_player_energy(Player *player){
    return player->energy;
}

int get_player_cell(Player *player){
    return player->cell;
}

int get_monster_cell(Monster *monster){
    return monster->cell;
}

void get_player_descrition_location(Player *player, Cell *map){
    printf("\nDescrição da Cell do Jogador: \n%s\n",map[player->cell].description);
        printf("----------------- Cell %d -----------------\n", player->cell);
        printf("0 - Norte = %d\n", map[player->cell].north);
        printf("1 - Sul = %d\n", map[player->cell].south);
        printf("2 - Oeste = %d\n", map[player->cell].west);
        printf("3 - Este = %d\n", map[player->cell].east);
        printf("4 - Andar de Cima = %d\n", map[player->cell].up);
        printf("5 - Andar de Baixo = %d\n", map[player->cell].down);
        printf("Objeto = %s\n", map[player->cell].object);
}

int read_player_input(Player *player){
    Cell map[MAX_CELL];
    init_map(map);
    get_player_descrition_location(player, map);
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

int random_get_monster_cell(Monster *monster){
    Cell map[MAX_CELL];
    init_map(map);
    int cell_array[6] = {map[monster->cell].north, map[monster->cell].south, map[monster->cell].west, map[monster->cell].east, map[monster->cell].up, map[monster->cell].down};
    int cell = -1;
    int random = 0;
    //Check if the position to where the monster wants to move is possible or not
    do{
        //Do a random so, the monster can be moved
        random = (rand() % 5);
        cell = cell_array[random];
    }while(cell == -1);
    return cell;
}

int main(){

    Player player;
    Monster monster;
    Cell map[MAX_CELL];
    int n_cells = 4;
    Object object[MAX_NUMBER_OBJECT];
    int player_cell_input = 0;
    int check = 0;
    //Sends the memory address of the player structure to the function init_player()
    init_player(&player);

    //print_player
    //print_player(player);

    //Sends the memory address of the map structure to the function init_map()
    init_map(map);
     
    //print_map(map, n_cells);

    init_monster(&monster);

    //Player Thread Instatiation Using pthread Lybrary
    pthread_t player_thread;
    //Monster Thread Instatiation Using pthread Lybrary
    pthread_t monster_thread;

    //Player Thread and Monster_Thread Creation
    pthread_create(&monster_thread, NULL, change_monster_cell, (void *) &monster);
    pthread_create(&player_thread, NULL, change_player_cell, (void *) &player);
    do
    {
        //Calls already Created Monster_Cell
        change_monster_cell(&monster);
        
        print_monster(&monster);
            
        //Calls Already Created Player_Cell
        if(check > 0){
            change_player_cell(&player);
        }
        pthread_join(player_thread, NULL);
        if(get_player_cell(&player) == get_monster_cell(&monster)){
            //pthread_join makes the main thread wait for the other threads to finish
            //pthread_join(monster_thread, NULL);
            
            printf("\nLUTAR\n");
            change_monster_energy(&monster, 10);
        } 
        check = 1;
    }while (get_monster_energy(&monster) > 0 && get_player_energy(&player) > 0);
    
    
    //Greats the Player for winning the game or losing and Makes Threads Exit
    if(get_player_energy(&player) <= 0){
        printf("-------Você Perdeu, Boa Sorte para a Próxima---------\n");
        pthread_exit(&player_thread);
        pthread_exit(&monster_thread);
    }
    else{
        printf("-------Parabens Vocẽ Ganhou!!---------\n");
        pthread_exit(&player_thread);
        pthread_exit(&monster_thread);
    }

    return 0;
}

