#include "mustel.h"

void spawnCheck(struct package *allData){

    int i;
    int counter = allData->counter2;

    for(i = 0; i < allData->mp->spawnNum; ++i){
        if(allData->mp->spawner[i].alive == 0){ //Check if alive, if 0 (dead), then check if can spawn
            int timeStart = allData->mp->spawner[i].killedOnCount;
            int timeEnd = timeStart + allData->mp->spawner[i].respawnTime;
            if(counter >= timeEnd){ //Check if time lapse has been long enough for a spawn
                spawnIn(allData, i);
            }
        }
    }

    //If not spawned, and time allows, load spawn
}

void spawnIn(struct package *allData, int index){
    int count = 0;
    int xLoc;
    int yLoc;
    int x = allData->mp->spawner[index].x;
    int y = allData->mp->spawner[index].y;
    int dist = allData->mp->spawner[index].dist;

    //Find where monster spawns first and check if it's valid
    xLoc = generateVariableDist(x, dist);
    yLoc = generateVariableDist(y, dist);

    while(!spawnValid(allData, xLoc, yLoc)){
        if(count++ >= 5){ //Failed to spawn in five times, so skip this spawn
            return;
        }
        xLoc = generateVariableDist(x, dist);
        yLoc = generateVariableDist(y, dist);
    }

    //printf("index: %i x: %i y: %i dist: %i xLoc: %i yLoc: %i ", index, x, y, dist, xLoc, yLoc);
    newSpawn(allData, index, xLoc, yLoc);

}

int generateVariableDist(int num, int dist){
    int genNum = dist * rand()/RAND_MAX;
    if(rand()/RAND_MAX > .5){
        genNum = - genNum;
    }

    return (num + genNum);
}

//TODO: Populate the obstacle map on load to make all detections easier
//Will also need to create an update system for the obstacle map
bool spawnValid(struct package *allData, int x, int y){

    if(x < 0 || x >= allData->mp->ncols || y < 0 || y > allData->mp->nrows){ //Outside of range
        return false;
    }

    char mapObj = allData->mp->viewMap[y][x];

    switch(mapObj){
    case '=':
        return false;
    case '0':
        return true;
    default:
        return false;
    }
}

void newSpawn(struct package *allData, int index, int x, int y){

    //Spawn into map
    allData->mp->viewMap[y][x] = allData->mp->spawner[index].sym;

    //Set spawn data
    allData->mp->spawner[index].alive = 1;
    allData->mp->spawner[index].killedOnCount = -1;

}

