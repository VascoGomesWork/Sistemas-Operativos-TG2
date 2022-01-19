#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(){
    int monster_energy, player_energy = 100;
    int monster_cell = 3;
    int player_cell = 0;
    int childStatus, childPid, pid;
    int pid_array[2];
    printf("Pai PID = %d\n", getpid());
    
    for(int i = 0; i < 2; i++){
        if(fork() != 0){
            pid = fork();
            pid_array[i] = getpid();
        }
    }

    

    do
    {
        /*int pid_child_1 = fork();
        int pid_child_2 = fork();*/
         
        //Moves Monster Around
        if(pid == 0){
            printf("Filho 1\n");
            monster_cell = 0;
            printf("Monster Cell = %d\n", monster_cell);
            exit(0);
        }
        wait(NULL);   
        //while the player cell && monster cell are different from one another player and monster moves
        while(monster_cell != player_cell){
            if(pid == 0){
                printf("Filho 2\n");
                //Moves Player around
                player_cell = 1;
                printf("Player Cell = %d\n", player_cell);
                exit(0);
            }
        }
        childPid = wait(&childStatus);
        if(pid != 0){
            printf("Teste");
            
            printf("Terminou o filho com o pid %d\n", childPid);
            //while(get_player_cell(&player) == get_monster_cell(&monster) && get_monster_energy(&monster) > 0 && get_player_energy(&player) > 0){
            if(monster_cell == player_cell){
                printf("\nLUTAR\n");
                
                
                monster_energy = monster_energy - 10;
            }
        }
        //change_player_energy(&player, 100);
        
    }while (monster_energy > 0 && player_energy > 0);


  return 0;
}