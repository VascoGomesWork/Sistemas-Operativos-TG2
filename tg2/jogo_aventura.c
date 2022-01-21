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

typedef struct object{
    char name[MAX_OBJECT_NAME];
    int figh_efficiency_level;
}Object;

typedef struct player{ 
  char name[MAX_PLAYER_NAME];
  int energy;
  int cell; //Player Location in the Map
  Object object;
  int treasure;
  int time_to_fight;
}Player;

typedef struct monster{
    int energy;
    int cell; //Monster Location in the Map
}Monster;

typedef struct cell{
    int north;
    int south;
    int east;
    int west;
    int up;
    int down;
    int object_boolean;
    char description[MAX_CELL_DESCRIPTION];
    Object object;
    char treasure[MAX_TREASURE_NAME];
}Cell;

/**
 * @brief Função de Iniciação do Jogador
 * 
 * @param player 
 */
void init_player(Player *player){
    Object object;
    strcpy(object.name, "Punhos há Homem");
    object.figh_efficiency_level = 10;
    //Uses pointer to modify the variable through it's memory address
    //Asks the Player what is name is
    printf("Olá Jogador!\nQual é o seu Nome?\n");

    //Reads the Player name from the keyboard
    scanf("%s", player->name);

    //Sets the Player energy, cell, object and treasure
    player->energy = INITIAL_PLAYER_ENERGY;
    player->cell = INITIAL_PLAYER_CELL;
    player->object = object;
    player->treasure = NO_TREASURE;
}

/**
 * @brief Função para mostrar os detalhes do jogador
 * 
 * @param player 
 */
void print_player(Player player){
    printf("Nome do Jogador = %s\n", player.name);
    printf("Energia do Jogador = %d\n", player.energy);
    printf("Cell do Jogador = %d\n", player.cell);
    printf("Objecto do Jogador = %d\n", player.object);
    printf("Tesouro do Jogador = %d\n", player.treasure);
}

/**
 * @brief Função de inicialização do mapa do jogo
 * 
 * @param map 
 */
void init_map(Cell *map){
    //Object 1
    Object object1;
    strcpy(object1.name, "Sem Objeto");
    object1.figh_efficiency_level = -1;

    //Object 2
    Object object2;
    strcpy(object2.name, "Espada Escalibur");
    object2.figh_efficiency_level = 75;

    //Object 3
    Object object3;
    strcpy(object3.name, "Chinelo Voador");
    object3.figh_efficiency_level = 40;
    
    Object object_array[3] = {object1, object2, object3};

    map[0].north = -1;
    map[0].south = -1;
    map[0].west = -1;
    map[0].east = 1;
    map[0].up = -1;
    map[0].down = -1;
    map[0].object_boolean = -1;
    map[0].object = object_array[0];
    strcpy(map[0].treasure, "Não existem tesouros nesta sala\n");
    strcpy(map[0].description, "Você está na entrada de um castelo.\n Existe um monstro que tem de derrotar para chegar ao tesouro\n");

    map[1].north = -1;
    map[1].south = 2;
    map[1].west = 0;
    map[1].east = 3;
    map[1].up = -1;
    map[1].down = -1;
    map[1].object_boolean = -1;
    map[1].object = object_array[0];
    strcpy(map[1].treasure, "Não existem tesouros nesta sala\n");
    strcpy(map[1].description, "Esta é o corredor do castelo, que possibilitará a entrada em diversas salas diferentes\n");

    map[2].north = 1;
    map[2].south = -1;
    map[2].west = -1;
    map[2].east = 4;
    map[2].up = -1;
    map[2].down = -1;
    map[2].object_boolean = 1;
    map[2].object = object_array[1];
    strcpy(map[2].treasure, "Não existem tesouros nesta sala\n");
    strcpy(map[2].description, "Você chegou a sala de jantar. Esta contem um objeto para combater o monstro!");

    map[3].north = -1;
    map[3].south = -1;
    map[3].west = 1;
    map[3].east = -1;
    map[3].up = -1;
    map[3].down = -1;
    map[3].object_boolean = 1;
    map[3].object = object_array[2];
    strcpy(map[3].treasure, "Não existem tesouros nesta sala\n");
    strcpy(map[3].description, "Você encontrou o quarto real, aqui pode encontrar um objeto para combater o monstro");

    map[4].north = -1;
    map[4].south = -1;
    map[4].west = 2;
    map[4].east = -1;
    map[4].up = -1;
    map[4].down = -1;
    map[4].object_boolean = -1;
    map[4].object = object_array[0];
    strcpy(map[4].treasure, "Você encontrou o tesouro\n");
    strcpy(map[4].description, "Você entrou na cozinha, e esta sala do castelo contem o tesouro");
}

/**
 * @brief Função que mostra os detalhes do mapa
 * 
 * @param map 
 * @param n_cells 
 */
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

/**
 * @brief Função que inicializa o monstro
 * 
 * @param monster 
 */
void init_monster(Monster *monster){
    monster->energy = INITIAL_MONSTER_ENERGY;
    monster->cell = INITIAL_MONSTER_CELL;
}

/**
 * @brief Função que mostra os detalhes do monstro
 * 
 * @param monster 
 */
void print_monster(Monster *monster){
    printf("Energia do Monstro = %d\n", monster->energy);
    printf("Cell do Monstro = %d\n", monster->cell);
}

/**
 * @brief Função associada a Thread do monstro que realiza a sua movimentação
 * 
 * @param monster 
 * @return void* 
 */
void * change_monster_cell(void * monster){
    Monster * monster1 = (Monster*)monster;
    monster1->cell = random_get_monster_cell(monster1);//Mudar para função random
}

/**
 * @brief Função associada a Thread do jogador que pede ao utilizador a cell para que o jogador deve ser movimentado
 * 
 * @param player 
 * @return void* 
 */
void * change_player_cell(void * player){
     
    Player * player1 = (Player*)player;

    player1->cell = read_player_input(player1);
}

/**
 * @brief Função que decrementa a energia do monstro
 * 
 * @param monster 
 * @param energy 
 */
void change_monster_energy(Monster *monster, int energy){
    monster->energy = monster->energy - energy;
}

/**
 * @brief Função que decrementa a energia do jogador
 * 
 * @param player 
 * @param energy 
 */
void change_player_energy(Player *player, int energy){
    player->energy = player->energy - energy;
}

/**
 * @brief Função que retorna a energia do monstro
 * 
 * @param monster 
 * @return int 
 */
int get_monster_energy(Monster *monster){
    return monster->energy;
}

/**
 * @brief Função que retorna a energia do jogador
 * 
 * @param player 
 * @return int 
 */
int get_player_energy(Player *player){
    return player->energy;
}

/**
 * @brief Função que retorna a cell do jogador
 * 
 * @param player 
 * @return int 
 */
int get_player_cell(Player *player){
    return player->cell;
}

/**
 * @brief Função que retorna a cell do monstro
 * 
 * @param monster 
 * @return int 
 */
int get_monster_cell(Monster *monster){
    return monster->cell;
}

/**
 * @brief Função que descreve ao utilizador a cell em que este está, atavés da linha de comandos
 * 
 * @param player 
 * @param map 
 */
void get_player_descrition_location(Player *player, Cell *map){
    printf("\nDescrição da Cell do Jogador: \n%s\n",map[player->cell].description);
        printf("----------------- Cell %d -----------------\n", player->cell);
        printf("0 - Norte = %d\n", map[player->cell].north);
        printf("1 - Sul = %d\n", map[player->cell].south);
        printf("2 - Oeste = %d\n", map[player->cell].west);
        printf("3 - Este = %d\n", map[player->cell].east);
        printf("4 - Andar de Cima = %d\n", map[player->cell].up);
        printf("5 - Andar de Baixo = %d\n", map[player->cell].down);
        printf("Objeto = %s\n", map[player->cell].object.name);
        printf("Tesouro = %s\n", map[player->cell].treasure);
}

/**
 * @brief Função que lê a opção escolhida pelo utilizador
 * 
 * @param player 
 * @return int 
 */
int read_player_input(Player *player){
    Cell map[MAX_CELL];
    init_map(map);
    get_player_descrition_location(player, map);

    int cell_array[6] = {map[player->cell].north, map[player->cell].south, map[player->cell].west, map[player->cell].east, map[player->cell].up, map[player->cell].down};
    int cell = -1;
    int selected_option = 0;
    char answer[2];
    //Checks if there is an object in the current room
    if(map[player->cell].object_boolean == 1){
        printf("\nVocê encontrou um objeto que pode ser usado no combate com o monstro!\n");
        printf("Nome do Objeto = %s | Eficiência do Objeto = %d\n", map[player->cell].object.name, map[player->cell].object.figh_efficiency_level);
        printf("Você deseja guardar o objeto?\n Responda s caso sim, ou n caso não\n");
        scanf("%s", answer);

        if(strcmp(answer, "s") == 0){
            player->object = map[player->cell].object;
            printf("\nObjeto Apanhado = %s\n", player->object.name);
        }
    }

    do{
        printf("Observe os pontos do mapa e indique para que celula se quer mover\n");
        //Reads the Player Input from the keyboard
        scanf("%d", &selected_option);
        //Gets 
        cell = cell_array[selected_option];

    }while(cell == -1);
    return cell;
}

/**
 * @brief Função que seleciona aleatoriamente a cell para onde o monstro vai
 * 
 * @param monster 
 * @return int 
 */
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

/**
 * @brief Função que pergunta ao utilizador qual a sua decisão numa luta com o monstro
 * 
 * @param player 
 * @return int 
 */
int get_player_decision(Player *player){
    Object object;
    int option_array[2] = {player->object.figh_efficiency_level, 0};
    int option = -1;
    int choosen_option = -1;
    int efitiency = 0;
    printf("Você encontrou o Monstro. Arregaçe as mangas porque agora vai ter que lutar!!\n");
    printf("Escolha de entre as opções abaixo o que deseja fazer.\n");
    do{
        printf("0 - Lutar com -> %s | Eficiência -> %d\n", player->object.name, player->object.figh_efficiency_level);
        printf("1 - Fugir Daqui para Fora\n");
        scanf("%d", &choosen_option);
        option = option_array[choosen_option];
    }while(option == -1);

    return option;
}

/**
 * @brief Função que seleciona aleatoriamente qual a decisão de luta com o jogador
 * 
 * @param monster 
 * @return int 
 */
int get_monster_decision(Monster *monster){
    //Monster has a Heavy Atack and a Light Atack and can run away
    int option_array[3] = {50, 30, 0};
    int option = -1;
    printf("Monstro: Agora é a minha vez!!\n");
    do{
        option = option_array[rand() % 3];
    }while(option == -1);
    return option;
}

int main(){

    Player player;
    Monster monster;
    Cell map[MAX_CELL];
    int n_cells = 4;
    int player_cell_input = 0;
    int check = 0;
    //Sends the memory address of the player structure to the function init_player()
    init_player(&player);

    //Sends the memory address of the map structure to the function init_map()
    init_map(map);
     
    init_monster(&monster);

    //Player Thread Instatiation Using pthread Lybrary
    pthread_t player_thread;
    //Monster Thread Instatiation Using pthread Lybrary
    pthread_t monster_thread;

    //Player Thread and Monster_Thread Creation
    pthread_create(&monster_thread, NULL, change_monster_cell, (void *) &monster);
    pthread_create(&player_thread, NULL, change_player_cell, (void *) &player);
    player.time_to_fight = 0;
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
            pthread_join(monster_thread, NULL);
            pthread_join(player_thread, NULL);
            printf("\nLUTAR\n");

            //Changes Monster Energy based on player decision
            change_monster_energy(&monster, get_player_decision(&player));
            //Changes Player Energy based on player decision
            change_player_energy(&player, get_monster_decision(&monster));
            printf("Energia do Jogador = %d\n", player.energy);
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

