#include "mapGen.h"

int main (void){

    int i;
    int done = 0;

    struct mapData mData;
    mData.z = 8;
    mData.fRows = 0;
    mData.fCols = 0;
    mData.mapNum = -1;
    mData.pColsRange[0] = 0;
    mData.pColsRange[1] = 0;
    mData.pRowsRange[0] = 0;
    mData.pRowsRange[1] = 0;
    mData.sym = '0';

    for(i = 0; i < 16; ++i){
        mData.mp[i].obPtr = NULL;
    }

    while(done != -1){

        done = mainIO(&mData);

    }

    return 0;
}
