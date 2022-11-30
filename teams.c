#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strcmp
#include "datastructure.h"
#include "tools.h"
#include "menu.h"
#include "datetime.h"
#include "sort.h"
#include "teams.h"


//MAXTEAMS defined in datastructure.h
   int TeamCounter = 0;
   sTeam Teams[MAXTEAMS];

void createTeam()
{
   sTeam *NewTeam = Teams + TeamCounter;

  // muss geprüft werden ob get Text sucessfull ist?
   if(TeamCounter < MAXTEAMS) // to ensure that there is still space in the array
   {
      NewTeam->NumberOfPlayers = 0;
      getText("Geben Sie bitte den Namen der Mannschaft ein \n -> ", 100, 0, &(NewTeam->Name)); //Teams + TeamCounter Zeigerschreibweise für Teams[TeamCounter]
      getText("Geben Sie bitte den Namen des Trainers ein \n -> ", 100, 1, &(NewTeam->Trainer));
      do{
         if(NewTeam->NumberOfPlayers < MAXPLAYER) // to ensure that there is still space in the array
         {
            createPlayer(NewTeam);
         }
      } while(askYesOrNo("Moechten Sie einen weiteren Spieler eingeben (j/n) ? \n"));
      clearScreen();
      TeamCounter++;
   }
}

void createPlayer(sTeam *NewTeam)
{
   sPlayer *NewPlayer = NewTeam->Players + NewTeam->NumberOfPlayers;
   char *Date_as_text = NULL;
   int Valid_Date;

   getText("Bitte geben Sie den Namen eines Spielers ein: \n -> ", 50, 0, &(NewPlayer->Name));
   do{
      getText("Geben Sie bitte das Geburtsdatum des Spielers ein: \n -> ", 50, 1, &Date_as_text);
      if(Date_as_text) // if Date_as_text is still NULL pointer dont get Date from String
         Valid_Date = getDateFromString(Date_as_text, &(NewPlayer->Birthday));
      else
         Valid_Date = 1;
   } while(!Valid_Date); // to allow empty Date input
   getNumber("Geben Sie bitte die Trikotnr. des Spilers ein: \n -> ", &(NewPlayer->ShirtNumber), 0, 99);
   NewPlayer->GoalNumber = 0;
   (NewTeam->NumberOfPlayers)++;
}

void deleteTeam()
{
   printf("deleteTeam");
   waitForEnter();
}
void deletePlayer()
{
   printf("deletePlayer");
   waitForEnter();
}
void searchPlayer()
{
   printf("searchPlayer");
   waitForEnter();
}

int cmpNames(sPlayer *P1, sPlayer *P2)
{
   return strcmp(P1->Name, P2->Name);
}

int cmpBirthday(sPlayer *P1, sPlayer *P2)
{
   if(P1->Birthday->Year - P2->Birthday->Year != 0)
      return P1->Birthday->Year - P2->Birthday->Year;
   else if(P1->Birthday->Month - P2->Birthday->Month != 0)
      return P1->Birthday->Month - P2->Birthday->Month;
   else
      return P1->Birthday->Day - P2->Birthday->Day;
}

int cmpGoals(sPlayer *P1, sPlayer *P2)
{
   if(P1->GoalNumber - P2->GoalNumber != 0)
      return P1->GoalNumber - P2->GoalNumber;
   else
     return cmpNames(P1, P2);
}

int cmpShirtNumber(sPlayer *P1, sPlayer *P2)
{
   return P1->ShirtNumber - P2->ShirtNumber;
}

void sortTeams()
{
   int Menu_point;
   int (*cmpSelected) (sPlayer*, sPlayer*);
   char Menu_title[] = "Sortieren";
   char *Menu_points[] = {"Spieler nach Namen sortieren", "Spieler nach Geburtsdatum (Alter) sortieren", "Spieler nach Trikotnr. Sortieren", "Spieler nach Anzahl geschossener Tore sortieren", "zurueck zum Hauptmenue"};
   int Number_of_Menu_Points = sizeof(Menu_points)/sizeof(Menu_points[0]);

do{
      Menu_point = getMenu(Menu_title, Menu_points, Number_of_Menu_Points);
      switch(Menu_point)
      {
         case 1:  cmpSelected = cmpNames;
               break;
         case 2:  cmpSelected = cmpBirthday;
               break;
         case 3:  cmpSelected = cmpShirtNumber;
               break;
         case 4:  cmpSelected = cmpGoals;
               break;
         case 5: return;
      }
      int i;
      for(i = 0; i < TeamCounter; i++)
                  {
                     QSort((Teams + i)->Players, (Teams + i)->NumberOfPlayers, cmpSelected);
                     printf("Spieler der Mannschaft %s sortieren ... ok \n", (Teams + i)->Name);
                  }
      waitForEnter();
   } while(Menu_point != 5);
}

void listTeams()
{
   if(TeamCounter == 0)
      printf("\nKeine Mannschaften gefunden");
   else
   {
      printf("\nListe der Mannschaften\n");
      printf("======================\n \n");
      int i;
      for(i = 0; i < TeamCounter; i++)
      {
         listOneTeam(i);
         printLine('-', 21);
      }
   }
   waitForEnter();

}

void listOneTeam(int Team_Number)
{
   sTeam *current_team = Teams + Team_Number;
   sPlayer *current_player = current_team->Players;

   printf("Name               : %s \n", current_team->Name);
   if((Teams + Team_Number)->Trainer) //if not NULL
      printf("Trainer            : %s \n", current_team->Trainer);
   else
      printf("Trainer            : <dieser Posten ist verkant> \n");
   printf("Anzahl der Spieler : %d \n", current_team->NumberOfPlayers);
   printf("Spieler: \n");
   int i;
   for(i = 0; i < current_team->NumberOfPlayers; i++)
   {
      printf("%02d. %s (%d", (i + 1), current_player->Name, current_player->ShirtNumber);
      if(current_player->Birthday) //if not NULL
      {
         printf("; * ");
         printDate(current_player->Birthday);
      }
      printf("; %d Tor", current_player->GoalNumber);
      if(current_player->GoalNumber != 1) // for plural Tore instead of Tor
         printf("e");
      printf(") \n");
      current_player++;
   }
}

void freePlayer(sPlayer *Player)
{
   free(Player->Name);
   free(Player->Birthday);
}

void freeTeam(sTeam *Team)
{
   int i;

   free(Team->Name);
   free(Team->Trainer);
   for (i = 0; i < Team->NumberOfPlayers; i++)
      freePlayer(Team->Players + i);
}

void freeTeams()
{
   int i;
   for (i = 0; i < TeamCounter; i++)
      freeTeam(Teams + i);
}


