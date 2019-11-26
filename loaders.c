#include "mustel.h"

struct spawnInfo *spawnLoader(struct package *package){
    //Loads a single spawner
    //TODO extend this to load more spawners
    package->mp->spawnNum = 1;
    struct spawnInfo *temp = malloc(package->mp->spawnNum * sizeof(struct spawnInfo));

    int monID = 0;

    temp[0].x = 35;
    temp[0].y = 10;
    temp[0].dist = 5;
    temp[0].spawnID = monID; //This determines which monster spawns here.
    temp[0].killedOnCount = 0;
    temp[0].respawnTime = 1;
    temp[0].alive = 0;

    //Set Monster Info For This Spawn
    temp[0].uID = package->monsUIDCount++;
    temp[0].iD = package->monsData[monID].iD;
    temp[0].name = package->monsData[monID].name;
    temp[0].sym = package->monsData[monID].sym;
    temp[0].att = package->monsData[monID].att;
    temp[0].def = package->monsData[monID].def;
    int health = package->monsData[monID].maxHealth;
    temp[0].maxHealth = generateVariableDist(health, health*HVARLOW/100);
    temp[0].health = temp[0].maxHealth;

    return temp;

};

struct monsData *monsDataLoader(){

    struct monsData *mons = malloc(MAXMONS * sizeof(struct monsData));

    mons[0].iD = 0;
    mons[0].sym = 'r';
    mons[0].name = "Rat";
    mons[0].maxHealth = 10;
    mons[0].att = 15;
    mons[0].def = 9;

    return mons;

}

//function to generate a new map
char **init_map_tiles(int nrows, int ncols){
    int i, j;

    char **mpPtr;

	mpPtr = malloc(nrows * sizeof(char *));
	if(mpPtr == NULL){
		fprintf(stderr, "first out of memory\n");
		exit(-1);
    }
	for(i = 0; i < nrows; i++){
		mpPtr[i] = malloc(ncols * sizeof(char));
		if(mpPtr[i] == NULL){
			fprintf(stderr, "second out of memory\n");
			exit(-1);
        }
    }

    for(i = 0; i < nrows; ++i){
        for(j = 0; j < ncols; ++j){
            mpPtr[i][j] = '0';
        }
    }

   return mpPtr;
};

//Init and take map from file
int map_loader (struct mapData *mData){

    int i;

    //Load map_config
    if(read_map_config(mData) == 0){
        return 0;
    }

    //Init map pointer
    for(i = 0; i < 16; ++i){
        mData->mp[i].obPtr = init_map_tiles(mData->fRows, mData->fCols);
        mData->mp[i].viewMap = init_map_tiles(mData->fRows, mData->fCols);
        mData->mp[i].obstacle = init_map_tiles(mData->fRows, mData->fCols);
    }

    //Load map from file
    for(i = 0; i < 16; ++i){
        if(read_map_bin(mData, i) == 0){
            printf("\nRead Map Issue\n");
            return 0;
        }
    }

    //TODO: Add a spawner file and loader for the spawner.

    return 1;
}

void packageLoader(struct package *package){

    int i;

    package->counter1 = 0;
    package->counter2 = 0;
    package->monsUIDCount = 0;
    package->itemUIDCount = 0;
    //These should be initialized from a save file, eventually
    package->pLoc[0] = 0;
    package->pLoc[1] = 8;
    package->pLoc[2] = 5;
    package->pLoc[3] = 5;
    package->pData = NULL;

    //Load initial maps
    //Create mData mapNum initializer (set to -1 if not loaded or later unloaded)
    for(i = 0; i < MAXMAPS; ++i){
       package->mapData[i].mapNum = i;
       if(map_loader(&package->mapData[i]) == 0){
           printf("\nFailed to load map %i\n", i);
           exit(1);
       }
    }

    package->mp = &package->mapData[package->pLoc[0]].mp[package->pLoc[1]];


    package->monsData = monsDataLoader();

    //Saved for when mons are loaded from a file.
    /*for(i = 0; i < MAXMONS; ++i){
        if(monsDataLoader(&package->monsData[i]) == 0){
            printf("\nFailed to load monster %i\n", i);
            exit(1);
        }
    }*/

    //Load a spawner.
    //Later this should be done when a map is loaded.
    //package->mapData[package->pLoc[0]].mp[package->pLoc[1]].spawner = spawnLoader(package);
    package->mp->spawner = spawnLoader(package);

}

/*
 * Will eventually need a mons config loader that loads in all the monster IDs
 * It will also have to create all the structures for the IDs
 * Then it will finally run monsLoader with all the structures to pull monster info from the files
 */
