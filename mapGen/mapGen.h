#ifndef MAPGEN_H_INCLUDED
#define MAPGEN_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct maps{
    char **viewMap;         //What is seen when all map elements are compiled.
    char **obPtr;           //Obstacle map (main map)
    struct monS *monS;      //Monster stack (will be empty without spawners, usually)
    struct effS *effS;      //Effects stack
    struct gitemS *gitemS;  //Items on ground stack
    struct spawnS *spawnS;  //Spawner stack
    int nrows; //Max rows (nrows - 1)
    int ncols; //Max cols (ncols - 1)
};

struct mapData{
    struct maps mp[16];  //16 map elements for the 16 z levels
    int z;               //Current z level
    int fRows;           //Max rows for each map
    int fCols;           //Max cols for each map
    int mapNum;          //Map number
    int pRowsRange[2];   //Current row viewing range
    int pColsRange[2];   //Current col viewing range
    char sym;            //Symbol to be inserted
};

struct monS{
    int ID;
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

struct monster{
    int mNum;
    char *name;
    int health;
};

//IO functions
int mapIO(struct mapData *mData);
int mainIO(struct mapData *mData);
void map_print_arguments();
void main_print_arguments();

//handler functions
void z_handler(int *z);
void new_map(struct mapData *mData, int state);
void map_print_handler(struct mapData mData);
int rcChecker(struct mapData mData, int col, int row, int num, char type);
int read_handler(struct mapData mData);
void save_handler(struct mapData mData);
int check_map_exist(struct mapData *mData);

//map generator functions
char **init_map_tiles(int nrows, int ncols);
void print_non_display(struct mapData mData);
void insert(struct maps mp, int row, int col, char sym);
void symbol_change(char *current);

//file read/write functions
int write_map_Bin(struct mapData mData, int z);
int write_map_config(struct mapData mData);
int read_map_config(struct mapData *mData);
int read_map_Bin(struct mapData *mData, int z);


#endif // MAPGEN_H_INCLUDED
