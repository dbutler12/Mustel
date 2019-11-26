#include "mapGen.h"

//List of arguments when necessary.
void insert_print_arguments(char current, struct mapData *mData){
    printf("Current character: %c    Current Level: %i\n\n", current, mData->z);
    printf("\n   ********************************************\n");
    printf("   ****LIST OF MAP COMMANDS********************\n");
    printf("   ********************************************\n");
    printf("   *   c         to change symbol to insert   *\n");
    printf("   *   u         to move up a level           *\n");
    printf("   *   d         to move down a level         *\n");
    printf("   *   r         to insert as rectangle       *\n");
    printf("   *   l         to insert as line            *\n");
    printf("   *   s col row to insert single in row col  *\n");
    printf("   *   p         to print the map             *\n");
    printf("   *   x         to exit                      *\n");
    printf("   *   ?         to see command menu          *\n");
    printf("   ********************************************\n");
}

void z_handler(int *z){
    char command[25];
    char com;
    int startZ = *z;
    int scanner;

    printf("\nYou are currently at level %i\n(U)p a level, (d)own a level, or (j)ump? \n", *z);
    fgets(command, 25, stdin);

    scanner = sscanf(command, "%c", &com);

    if(scanner != 1){
        printf("Invalid argument. Returning.\n");
        return;
    }else{
        switch(com){
        case 'U':
        case 'u':
            *z = *z + 1;
            break;
        case 'd':
        case 'D':
            *z = *z - 1;
            break;
        case 'j':
        case 'J':
            printf("\nWhat level to jump to?\n");
            fgets(command, 25, stdin);

            scanner = sscanf(command, "%i", z);

            if(scanner != 1){
                printf("Invalid argument. Returning.\n");
            }else{
                printf("\nJumped to level %i\n", *z);
            }
            break;
        }
    }

    if(*z < 0 || *z > 16){
        *z = startZ;
    }

}

//State of 0 means we need to create a brand new map.
//State of 1 means we need to init our struct to accept a read for a map.
void new_map(struct mapData *mData, int state){

    int z;

    if(state == 0){
        char command[25];
        char com = 'n';
        int scanner;

        if(mData->mp[8].obPtr != NULL){
            printf("\nWould you like to make a new map for map %i?\n", mData->mapNum);
            fgets(command, 25, stdin);
            scanner = sscanf(command, "%c", &com);
            if(com == 'y' || com == 'Y'){
                //free function goes here

            }else{
                return;
            }
        }

        if(mData->fRows == 0){

            printf("\nHow many rows do you want the map to have?\n");
            fgets(command, 25, stdin);

            scanner = sscanf(command, "%i", &mData->fRows);

            if(scanner != 1){
                printf("Invalid argument. Returning. \n");
                return;
            }
            printf("\nHow many cols do you want the map to have?\n");
            fgets(command, 25, stdin);

            scanner = sscanf(command, "%i", &mData->fCols);

            if(scanner != 1){
                printf("Invalid argument. Returning. \n");
                return;
            }
        }
    }

    for(z = 0; z < 16; ++z){
        mData->mp[z].nrows = mData->fRows;
        mData->mp[z].ncols = mData->fCols;
        mData->mp[z].obPtr = init_map_tiles(mData->fRows, mData->fCols);
        mData->mp[z].viewMap = init_map_tiles(mData->fRows, mData->fCols);
        mData->mp[z].effS = NULL;
        mData->mp[z].gitemS = NULL;
        mData->mp[z].spawnS = NULL;
        mData->mp[z].monS = NULL;
    }

    mData->pRowsRange[0] = 0;
    mData->pRowsRange[1] = mData->fRows - 1;
    mData->pColsRange[0] = 0;
    mData->pColsRange[1] = mData->fCols - 1;

}

void map_print_handler(struct mapData mData){

    printf("\nPrinting non-matrix, non-display map\n");

    print_non_display(mData);

}

void save_handler(struct mapData mData){

    int i;

    write_map_config(mData);

    for(i = 0; i < 16; ++i){
        write_map_Bin(mData, i);
    }

}

/*int read_handler(struct mapData mData){
    //Check if file for mapNum exists
    FILE *fp;
    char filename[200];
    sprintf (filename, "resources\\map%i\\%iz.bin", mData.mapNum, mData.z);
    fp = fopen(filename, "r");
    if(fp != NULL){
        //file exists
        fclose(fp);
    }else{
        //file doesn't exist
        return -1;
    }
    //Read config file for fRows and fCols

    return 0;
}*/

//Checks if inserting rows or cols is out of range.
//Returns -1 if out of range.
int rcChecker(struct mapData mData, int col, int row, int num, char type){

    if(type == 'c'){
        if (mData.pColsRange[0] > col){
            return -1;
        }else if (mData.pRowsRange[0] > row ){
            return -1;
        }else if (mData.pRowsRange[1] < row + num ){
            return -1;
        }
    }

    if(type == 'r'){
        if (mData.pColsRange[0] > col){
            return -1;
        }else if (mData.pRowsRange[0] > row){
            return -1;
        }else if (mData.pColsRange[1] < col + num - 1){
            return -1;
        }
    }

    return 0;
}


int check_map_exist(struct mapData *mData){

    int i;
    int exist = read_map_config(mData); //returns 1 if config exists

    if(exist == 0){
        return 0;
    }

    new_map(mData, 1); //Create blank map to load into.

    for(i = 0; i < 16; ++i){ //Load in map if config exists
        read_map_Bin(mData, i);
    }

    return 1;

}
