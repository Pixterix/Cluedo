#include <stdio.h>
#include <stdlib.h>
#include "Body.h"

int main() {
    setbuf(stdout,NULL);
    fflush(stdout);

    player_t player[3];
    murder_t murder[6];
    weapon_t weapon[6];
    room_t room[9];
    solution_t solution[1];

    Body_Init(player, murder, weapon, room, solution);
    list List = RescueRequest(player, murder, weapon, room, solution);

    //Resolut(player, murder, weapon, room, solution, List);

    PrintAllInfo(player, murder, weapon, room, solution, List);

    ListFree(List);

    exit(EXIT_SUCCESS);
}
