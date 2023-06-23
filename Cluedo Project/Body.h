#ifndef CLUEDO_PROJECT_BODY_H
#define CLUEDO_PROJECT_BODY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    char Name[4];
    int murders[6];
    int weapons[6];
    int rooms[9];
}player_t;

typedef struct{
    char Name[4];
    int owner;
}murder_t;

typedef struct{
    char Name[4];
    int owner;
}weapon_t;

typedef struct{
    char Name[4];
    int owner;
}room_t;

typedef struct{
    int murders[6];
    int weapons[6];
    int rooms[9];
}solution_t;

typedef struct list_t *list;

typedef struct Node *link;
struct Node{
    int player;
    int Murder[2];
    int Weapon[2];
    int Room[2];
    link Next;
};

void PrintAllInfo(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution, list List);
void Body_Init(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution);
int *Index_By_Name(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, char *Name);
list ListInit();
list NewNode(int Pla, int Mur, int Wea, int Roo, list List, solution_t *solution);
void ListFree(list List);
list RescueRequest(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution);
list UpdateList(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution,
                const int *Tmp, int Player, list List);
void UpdateCard(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution,
                const int *Tmp, int Player);
list Resolut(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution, list List);
list RemoveNode(link c, link p, list List);

#endif //CLUEDO_PROJECT_BODY_H
