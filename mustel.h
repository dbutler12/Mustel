#ifndef MUSTEL_H_INCLUDED
#define MUSTEL_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

#define MAXMAPS 2
#define MAXMONS 1
#define MAXITEMS 1
#define PX 33 //Display X Player
#define PY 17 //Display Y Player
#define ML 67 //Main length
#define MH 35 //Main height
#define IL 40 //Right box length
#define NH 3  //Input height
#define CH 10 //Bottom box height

//Definitions for status variability
#define HVARLOW 25
#define HVARMED 50
#define HVARHIGH 75

struct player{
    int level;
    int exp;
    int nextExp;
    int hpMax;
    int hpCur;
    int att;
    int def;
    struct equip *equip;
    int pLoc[4]; //0 = map number, 1 = z level, 2 = x coordinate, 3 = y coordinate
};

struct equip{
    int helmID;
    int armorID;
    int leftID;
    int rightID;
    int bootID;
};

struct item{
    char *name; //Item name
    char sym;
    int ID; //4 digit. 1st digit determines type (0 = helm, 1 = armor, 2 = weapon, 3 = shield, 4 = boot)
    int att;
    int def;
};

//Base monster data, to be loaded in from a file eventually.
struct monsData{
    int iD;
    char sym;
    char *name;
    int maxHealth;
    int att;
    int def;
};


//This will be usedcreateWin for monsters spawned in without a spawner.
struct monster{
    char sym;
    int iD;
    int uID;
    char *name;
    int health;
    int maxHealth;
    int att;
    int def;
};

//Stack structures
struct monS{
    int iD;
    struct monster *data;
    struct monS *next;
};

struct effS{
    //struct effect *data;
    struct effS *next;
};

struct gitemS{
    //struct item *data;
    struct gitemS *next;
};

struct spawnS{
    //struct spawner *data;
    struct spawnS *next;
};

struct spawnInfo{
    int x;
    int y;
    int dist;
    int alive;
    int spawnID; //ID for the monster to spawn with this spawner
    int killedOnCount;
    int respawnTime;
    //Monster info for this spawn
    int uID;
    int iD;
    char *name;
    char sym;
    int att;
    int def;
    int maxHealth;
    int health;
};

struct maps{
    char **obstacle;           //Quick check for obstacles. 0 or 1 for now, can be expanded.
    char **viewMap;            //What is seen when all map elements are compiled.
    char **obPtr;              //Obstacle map (main map)
    struct spawnInfo *spawner; //Spawner info for this map
    int spawnNum; //Number of spawns in the map
    int nrows; //Max rows (nrows - 1)
    int ncols; //Max cols (ncols - 1)
};

struct mapData{
    struct maps mp[16];  //16 map elements for the 16 z levels
    int fRows;           //Max rows for each map
    int fCols;           //Max cols for each map
    int mapNum;          //Map number
};

struct package{
    long long int counter1;
    int counter2;
    int pLoc[4];
    struct maps *mp;
    int monsUIDCount;
    int itemUIDCount;
    struct monsData *monsData;
    struct item itemData[MAXITEMS];
    struct mapData mapData[MAXMAPS];
    struct player *pData;
};


//display matrix
extern char display[62][31];

//Window creation and destruction tools
WINDOW *createWin(int height, int width, int starty, int startx);
void destroyWin(WINDOW *win);
void refreshAll(WINDOW **map, WINDOW **commands, WINDOW **input, WINDOW **inventory, WINDOW **status);
void fullRefreshAll(WINDOW **map, WINDOW **commands, WINDOW **input, WINDOW **inventory, WINDOW **status);

//Update functions
int updateMap(WINDOW **map, WINDOW **commands, struct package *allData,char *command, int pLoc[4]);

//file read/write functions
int write_map_bin(struct mapData mData, int z);
int write_map_config(struct mapData mData);
int read_map_config(struct mapData *mData);
int read_map_bin(struct mapData *mData, int z);

//Map involvement
int map_loader (struct mapData *mData);
char **init_map_tiles(int nrows, int ncols);
bool isObstacle(char obj);

//Spawn involvement
bool spawnValid(struct package *allData, int x, int y);
void newSpawn(struct package *allData, int index, int x, int y);
void spawnIn(struct package *allData, int index);
void spawnCheck(struct package *allData);

//Tools
int generateVariableDist(int num, int dist);

//Package Involvement
void packageLoader(struct package *package);
struct monsData *monsDataLoader();
//void spawnLoader(struct package *package);
struct spawnInfo *spawnLoader(struct package *package);

#endif // MUSTEL_H_INCLUDED

