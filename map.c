#include "mustel.h"

bool isObstacle(char obj){

    switch(obj){
        case '0':
            return false;
        default:
            return true;
    }
}

//Updates the map.
int updateMap(WINDOW **map, WINDOW **commands, struct package *allData, char *command, int pLoc[4]){

    int i, j;
    char mapItem;

    spawnCheck(allData);

    switch(*command){

    //Update player location (if possible)
    case 'a': //move left
        //check if obstacle blocks movement

        //check if at edge of map
        if(pLoc[2] - 1 < 0){

        }else{
            if(isObstacle(allData->mp->viewMap[pLoc[3]][pLoc[2] - 1] ) == false){ //Move if no obstacle.
                pLoc[2]--;
            }
        };
        break;
    case 's': //move down
        //check if obstacle blocks movement
        //
        //check if at edge of map
        if(pLoc[3] + 1 > allData->mp->nrows){

        }else{
            if(isObstacle(allData->mp->viewMap[pLoc[3] + 1][pLoc[2]] ) == false){ //Move if no obstacle.
                pLoc[3]++;
            }
        };
        break;
    case 'd': //move right
        //check if obstacle blocks movement
        //
        //check if at edge of map
        if(pLoc[2] + 1 > allData->mp->ncols){

        }else{
            if(isObstacle(allData->mp->viewMap[pLoc[3]][pLoc[2] + 1] ) == false){ //Move if no obstacle.
                pLoc[2]++;
            }
        };
        break;
    case 'w': //move up
        //check if obstacle blocks movement
        //
        //check if at edge of map
        if(pLoc[3] - 1 < 0){

        }else{
            if(isObstacle(allData->mp->viewMap[pLoc[3] - 1][pLoc[2]] ) == false){ //Move if no obstacle.
                pLoc[3]--;
            }

        };
        break;
    default:
        break;

    }

    for(i = 1; i < 67; i = i + 2){
        for(j = 1; j < 34; ++j){
            int x = (i-PX)/2+pLoc[2]; int y = j-PY + pLoc[3];
            if(!( y < 0 || x < 0 || y >= allData->mp->nrows || x >= allData->mp->ncols )){
                mapItem = allData->mp->viewMap[y][x];
            }else{
                mapItem = ' ';
            }

            if(mapItem == '0'){
                mapItem = ' ';
            }

            mvwaddch(*map, j, i, mapItem);
        }
    }

    //printf("\nmData: %c", mData->mp[pLoc[1]].obPtr[xEnd][yEnd]);

    mvwaddch(*map, PY, PX, 'P');
	wrefresh(*map);
}



