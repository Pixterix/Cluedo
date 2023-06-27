#include <stdio.h>
#include <stdlib.h>
#include "Body.h"

int main() {
    setbuf(stdout,NULL);
    fflush(stdout);

    player_t *player = malloc(3*sizeof(player_t));
    murder_t *murder = malloc(6*sizeof(murder_t));
    weapon_t *weapon = malloc(6*sizeof(weapon_t));
    room_t *room = malloc(9*sizeof(room_t));
    solution_t *solution = malloc(sizeof(solution_t));
    
    Body_Init(player, murder, weapon, room, solution);
    list List = RescueRequest(player, murder, weapon, room, solution);

    //Resolut(player, murder, weapon, room, solution, List);

    PrintAllInfo(player, murder, weapon, room, solution, List);
    
    ListFree(List);
    free(player);
    free(murder);
    free(weapon);
    free(room);
    free(solution);
    
    exit(EXIT_SUCCESS);
}
