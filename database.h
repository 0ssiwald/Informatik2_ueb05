/***************************************
* database.h contains all functions for
loading and saving data to the .xml file
****************************************/
#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#define FILENAME "teams.xml"

/***************************************
* int save()
* Saves all Data to the .xml File FILENAME
* Result: truth value if save was succesfull
***************************************/
int save();
void saveTeam(int, FILE*);
void savePlayer(sTeam*, int, FILE*);

/***************************************
* int load()
* Loads all Data to the .xml File FILENAME
* Result: truth value if load was successfull
***************************************/
int load();
void loadTeam(FILE *, char *);
void loadPlayer(FILE *, char *);

#endif // DATABASE_H_INCLUDED
