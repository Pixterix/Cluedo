#include "Body.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list_t{
        link head;
};

void Body_Init(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution){
    FILE *fp = fopen("Cluedo.txt", "r");
    if(!fp){
        printf("File not opened\n");
        exit(EXIT_FAILURE);
    }

    //Inizializzo i giocatori
    for(int i=0; i<3; i++){
        fscanf(fp, "%s", player[i].Name);
        memset(player[i].murders, 0, sizeof(player[i].murders));
        memset(player[i].weapons, 0, sizeof(player[i].weapons));
        memset(player[i].rooms, 0, sizeof(player[i].rooms));
    }

    //Inizializzo gli indizi
    for(int i=0; i<6; i++){
        fscanf(fp, "%s", murder[i].Name);
        murder[i].owner=-1;
    }
    for(int i=0; i<6; i++){
        fscanf(fp, "%s", weapon[i].Name);
        weapon[i].owner=-1;
    }
    for(int i=0; i<9; i++){
        fscanf(fp, "%s", room[i].Name);
        room[i].owner=-1;
    }

    //Inizializzo la soluzione
    memset(solution->weapons, -1, sizeof(solution->weapons));
    memset(solution->murders, -1, sizeof(solution->murders));
    memset(solution->rooms, -1, sizeof(solution->rooms));

    fclose(fp);
}

int *Index_By_Name(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, char *Name){
    int *Index = malloc(2*sizeof(int));
    if(player!=NULL)
        for(int i=0; i<3; i++)
            if(strcmp(Name, player[i].Name)==0){
                Index[0]=0;
                Index[1]=i;
                return Index;
            }
    if(murder!=NULL)
        for(int i=0; i<6; i++)
            if(strcmp(Name, murder[i].Name)==0){
                Index[0]=1;
                Index[1]=i;
                return Index;
            }
    if(weapon!=NULL)
        for(int i=0; i<6; i++)
            if(strcmp(Name, weapon[i].Name)==0) {
                Index[0]=2;
                Index[1]=i;
                return Index;
            }
    if(room!=NULL)
        for(int i=0; i<9; i++)
            if(strcmp(Name, room[i].Name)==0){
                Index[0]=3;
                Index[1]=i;
                return Index;
            }
    printf("%s not exist\n", Name);
    exit(EXIT_FAILURE);
}

void PrintAllInfo(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution, list List){
    printf("---------------------------------------------------------------------------------------\n\n");
    printf("Players:\n\n");
    for(int i=0; i<3; i++){
        printf("   %s\n", player[i].Name);
        printf("\n      Murder: ");
        for(int j=0; j<6; j++)
            printf("%2d ", player[i].murders[j]);
        printf("\n      Weapon: ");
        for(int j=0; j<6; j++)
            printf("%2d ", player[i].weapons[j]);
        printf("\n      Room:   ");
        for(int j=0; j<9; j++)
            printf("%2d ", player[i].rooms[j]);
        printf("\n\n");
    }
    printf("--------------------------\n\n");
    printf("Murders:\n\n");
    for(int i=0; i<6; i++){
        printf("   %s ", murder[i].Name);
        if(murder[i].owner==-1)
            printf("(ownerless)\n");
        else
            printf("(%s)\n", player[murder[i].owner].Name);
    }
    printf("\n--------------------------\n\n");
    printf("Weapons:\n\n");
    for(int i=0; i<6; i++){
        printf("   %s ", weapon[i].Name);
        if(weapon[i].owner==-1)
            printf("(ownerless)\n");
        else
            printf("(%s)\n", player[weapon[i].owner].Name);
    }
    printf("\n--------------------------\n\n");
    printf("Rooms:\n\n");
    for(int i=0; i<9; i++){
        printf("   %s ", room[i].Name);
        if(room[i].owner==-1)
            printf("(ownerless)\n");
        else
            printf("(%s)\n", player[room[i].owner].Name);
    }
    printf("\n--------------------------\n\n");
    printf("Recap:\n\n");
    printf("   Murder: ");
    for(int j=0; j<6; j++){
        if(solution->murders[j]==-1)
            printf(" 0  ");
        else
            printf("%s ", player[solution->murders[j]].Name);
    }
    printf("\n   Weapon: ");
    for(int j=0; j<6; j++){
        if(solution->weapons[j]==-1)
            printf(" 0  ");
        else
            printf("%s ", player[solution->weapons[j]].Name);
    }
    printf("\n   Room:   ");
    for(int j=0; j<9; j++){
        if(solution->rooms[j]==-1)
            printf(" 0  ");
        else
            printf("%s ", player[solution->rooms[j]].Name);
    }
    printf("\n\n--------------------------\n\n");
    printf("Request:\n\n");
    link c = List->head;
    while(c!=NULL){
        printf("   %s\n", player[c->player].Name);
        printf("      %s", murder[c->Murder[0]].Name);
        if(c->Murder[1]==-1)
            printf(" (Not Possible)\n");
        if(c->Murder[1]==1)
            printf(" (Sure)\n");
        if(c->Murder[1]==0)
            printf(" (Possible)\n");
        printf("      %s", weapon[c->Weapon[0]].Name);
        if(c->Weapon[1]==-1)
            printf(" (Not Possible)\n");
        if(c->Weapon[1]==1)
            printf(" (Sure)\n");
        if(c->Weapon[1]==0)
            printf(" (Possible)\n");
        printf("      %s", room[c->Room[0]].Name);
        if(c->Room[1]==-1)
            printf(" (Not Possible)\n");
        if(c->Room[1]==1)
            printf(" (Sure)\n");
        if(c->Room[1]==0)
            printf(" (Possible)\n");
        printf("\n");
        c=c->Next;
    }
    printf("---------------------------------------------------------------------------------------\n\n");
}

list ListInit(){
    list List = malloc(sizeof(*List));
    List->head=NULL;
    return List;
}

list NewNode(int Pla, int Mur, int Wea, int Roo, list List, solution_t *solution){
    link Node = malloc(sizeof(*Node));
    
    Node->player=Pla;

    //se quella carta ce l'ha qualcun'altro, metto quella richiesta a impossibile
    Node->Murder[0]=Mur;
    if(solution->murders[Mur]!=-1 && solution->murders[Mur]!=Pla) //Già occupato ma non da questo giocatore
        Node->Murder[1]=-1;
    else
        Node->Murder[1]=0;
    Node->Weapon[0]=Wea;
    if(solution->weapons[Wea]!=-1 && solution->weapons[Wea]!=Pla)
        Node->Weapon[1]=-1;
    else
        Node->Weapon[1]=0;
    Node->Room[0]=Roo;
    if(solution->rooms[Roo]!=-1 && solution->rooms[Roo]!=Pla)
        Node->Room[1]=-1;
    else
        Node->Room[1]=0;

    Node->Next=List->head;
    List->head=Node;
    
    return List;
}

void ListFree(list List){
    link x = List->head;
    while (x!=NULL){
        List->head=x->Next;
        free(x);
        x = List->head;
    }
    free(List);
}

list RescueRequest(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution){
    FILE *fp = fopen("Request.txt", "r");
    if(!fp){
        printf("File not open\n");
        exit(EXIT_FAILURE);
    }

    //Tolgo le mie carte
    char tmp[4];
    int *Ntmp;
    for(int i=0; i<6; i++){
        fscanf(fp, "%s", tmp);
        Ntmp = Index_By_Name(NULL, murder, weapon, room, tmp);
        UpdateCard(player, murder, weapon, room, solution, Ntmp, 0);
    }
    free(Ntmp);

    //Inizio a leggere le richieste
    int NRequest;
    list List = ListInit();
    fscanf(fp, "%d", &NRequest);
    for(int i=0; i<NRequest; i++){
        char P[4], M[4], W[4], R[4], A[4], A2[4];
        int *Ans, *clean=NULL;
        int Pla, Mur, Wea, Roo;
        fscanf(fp, "%s %s %s %s %s", P, M, W, R, A);
        clean=Index_By_Name(player, NULL, NULL, NULL, P);    //Pla è colui che fa richiesta
        Pla=clean[1];
        free(clean);

        //se il primo non può negare si passa al secondo
        if(strcmp(A, "Not")==0)
            fscanf(fp, "%s", A2);

        //se sono stato io a dare una carta fisica (ovvero ha chiesto l'ultimo), vado avanti.
        if(strcmp(A, "Not")!=0 && strcmp(A, "Yes")!=0 && Pla==2)
            continue;

        clean=Index_By_Name(NULL, murder, NULL, NULL, M);
        Mur=clean[1];
        free(clean);
        clean=Index_By_Name(NULL, NULL, weapon, NULL, W);
        Wea=clean[1];
        free(clean);
        clean=Index_By_Name(NULL, NULL, NULL, room, R);
        Roo=clean[1];
        free(clean);

        //Caso in cui so l'indizio
        if(strcmp(A, "Not")!=0 && strcmp(A, "Yes")!=0){

            //Se negano dandomi la carta o se la "intercetto" con abilità
            Ans=Index_By_Name(NULL, murder, weapon, room, A);
            UpdateCard(player, murder, weapon, room, solution, Ans, Pla+1);
            for(int j=0; j<3; j++)
                if((Pla+1)!=j)
                    List=UpdateList(player, murder, weapon, room, solution, Ans, j, List);
            free(Ans);
            continue;
        }

        //Caso in cui nega ma non so cosa
        if(strcmp(A, "Yes")==0){
            List=NewNode(Pla+1, Mur, Wea, Roo, List, solution);
            continue;
        }

        //Caso in cui l'interessato non può negare aggiorno (Tranne se sono io a rispondere)
        if(Pla!=2){
            int c[2];
            player[Pla+1].murders[Mur]=-1;
            c[0]=1; c[1]=Mur;
            List=UpdateList(player, murder, weapon, room, solution, c, Pla+1, List);
            player[Pla+1].weapons[Wea]=-1;
            c[0]=2; c[1]=Wea;
            List=UpdateList(player, murder, weapon, room, solution, c, Pla+1, List);
            player[Pla+1].rooms[Roo]=-1;
            c[0]=3; c[1]=Roo;
            List=UpdateList(player, murder, weapon, room, solution, c, Pla+1, List);
        }

        //devo rifare le stesse cose per la seconda risposta

        //Se sto rispondendo io, esco di nuovo.
        if(strcmp(A2, "Not")!=0 && strcmp(A2, "Yes")!=0 && Pla==1)
            continue;

        int mem=2; //risponde 2 se ho fatto io domanda
        if(Pla==2)
            mem=1; //risponde 1 se la domanda l'ha fatta 2   (ovviamente se la domanda l'avesse fatta 1 non saremmo qui)

        //Caso in cui so l'indizio
        if(strcmp(A2, "Not")!=0 && strcmp(A2, "Yes")!=0){

            //Se negano dandomi la carta oppure intercetto
            Ans=Index_By_Name(NULL, murder, weapon, room, A2);
            UpdateCard(player, murder, weapon, room, solution, Ans, mem);
            for(int j=0; j<3; j++)
                if(mem!=j)
                    List=UpdateList(player, murder, weapon, room, solution, Ans, j, List);
            free(Ans);
            continue;
        }

        //Caso in cui nega ma non so cosa
        if(strcmp(A2, "Yes")==0){
            List=NewNode(mem, Mur, Wea, Roo, List, solution);
            continue;
        }

        //Caso in cui l'interessato non può negare (Tranne se sono io a rispondere)
        if(Pla!=1){
            int *c = malloc(2*sizeof(int));
            player[mem].murders[Mur]=-1;
            c[0]=1; c[1]=Mur;
            List=UpdateList(player, murder, weapon, room, solution, c, mem, List);
            player[mem].weapons[Wea]=-1;
            c[0]=2; c[1]=Wea;
            List=UpdateList(player, murder, weapon, room, solution, c, mem, List);
            player[mem].rooms[Roo]=-1;
            c[0]=3; c[1]=Roo;
            List=UpdateList(player, murder, weapon, room, solution, c, mem, List);
            free (c);
        }
    }
    fclose(fp);
    return List;
}

void UpdateCard(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution,
                const int *Tmp, int Player){

    switch(Tmp[0]){
        case 1:
            for(int i=0; i<3; i++){
                if(Player!=i)
                    player[i].murders[Tmp[1]]=-1;
                else
                    player[i].murders[Tmp[1]]=1;
            }
            murder[Tmp[1]].owner=Player;
            solution->murders[Tmp[1]]=Player;
            break;
        case 2:
            for(int i=0; i<3; i++){
                if(Player!=i)
                    player[i].weapons[Tmp[1]]=-1;
                else
                    player[i].weapons[Tmp[1]]=1;
            }
            weapon[Tmp[1]].owner=Player;
            solution->weapons[Tmp[1]]=Player;
            break;
        case 3:
            for(int i=0; i<3; i++){
                if(Player!=i)
                    player[i].rooms[Tmp[1]]=-1;
                else
                    player[i].rooms[Tmp[1]]=1;
            }
            room[Tmp[1]].owner=Player;
            solution->rooms[Tmp[1]]=Player;
            break;
        default:
            printf("Error Tmp\n");
            exit(EXIT_FAILURE);
    }
}

//La uso per cercare nella lista tutte le richieste di un dato giocatore e mettere a -1 la carta non sua.
list UpdateList(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution,
                const int *Tmp, int Player, list List){
    //Vado a mettere -1 in tutte le request in cui compare una carta che so appartenga a un'altra persona.
    link c = List->head;
    while (c!=NULL){
        if(c->player==Player) {
            switch (Tmp[0]) {
                case 1:
                    c->Murder[Tmp[1]] = -1;
                    break;
                case 2:
                    c->Weapon[Tmp[1]] = -1;
                    break;
                case 3:
                    c->Room[Tmp[1]] = -1;
                    break;
                default:
                    printf("Error in UpdateList\n");
                    exit(EXIT_FAILURE);
            }
        }
        c=c->Next;
    }
    return List;
}

list Resolut(player_t *player, murder_t *murder, weapon_t *weapon, room_t *room, solution_t *solution, list List){
    int check=1;
    while(check==1){
        link c = List->head, p = NULL;
        while (c!=NULL){
            int sum=0, *Tmp = malloc(2*sizeof(int));
            if(c->Murder[1]==-1)
                sum=sum+1;
            if(c->Weapon[1]==-1)
                sum=sum+3;
            if(c->Room[1]==-1)
                sum=sum+5;
            switch(sum){
                case 0:
                case 1:
                case 3:
                case 5:
                    break;
                case 4:      //la stanza è sua
                    //rimuovo questa stanza dagli altri, metto -1 alle stanze della lista e la assegno a lui
                    Tmp[0]=3; Tmp[1]=c->Room[0];
                    break;
                case 6:      //l'arma è sua
                    //rimuovo quest'arma dagli altri, metto -1 alle armi della lista e la assegno a lui
                    Tmp[0]=2; Tmp[1]=c->Weapon[0];
                    break;
                case 8:      //il personaggio è suo
                    //rimuovo questo personaggio dagli altri, metto -1 ai personaggi della lista e lo assegno a lui
                    Tmp[0]=1; Tmp[1]=c->Murder[0];
                    break;
                default:
                    printf("Impossible Node\n");
                    exit(EXIT_FAILURE);
            }
            if(sum==4 || sum==6 || sum==8){
                //se ho assegnato una carta, rimuovo il nodo e ricomincio da capo il while esterno, bloccando l'interno
                UpdateCard(player, murder, weapon, room, solution, Tmp, c->player);
                UpdateList(player, murder, weapon, room, solution, Tmp, c->player, List);
                check=0;
                List=RemoveNode(c, p, List);
                break;
            }
            p=c; c=c->Next;
        }
    }
    return List;
}

list RemoveNode(link c, link p, list List){
    if(p==NULL)
        List->head=c->Next;
    else
        p->Next=c->Next;
    free(c);
    return List;
}
