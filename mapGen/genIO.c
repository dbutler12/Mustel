#include "mapGen.h"

//List of arguments when necessary.
void map_print_arguments(){
    printf("\n   ***************************************************************\n");
    printf("   ****LIST OF MAP COMMANDS***************************************\n");
    printf("   ***************************************************************\n");
    printf("   *   i                         to insert symbols to map        *\n");
    printf("   *     I col  row              insert at col/row               *\n");
    printf("   *     O char                  to change obstacle to insert    *\n");
    printf("   *     C col row num           insert as a col, num spots      *\n");
    printf("   *     R col row num           insert as a row, num spots      *\n");
    printf("   *     S col1 row1 col2 row2   insert as rectangle             *\n");
    printf("   *   n                         to make new map                 *\n");
    printf("   *   p                         to print the map                *\n");
    printf("   *   r col1 row1 col2 row 2    to change viewing range         *\n");
    printf("   *   s                         to save map to file             *\n");
    printf("   *   x                         to exit                         *\n");
    printf("   *   z                         to change map z level           *\n");
    printf("   *   ?                         to see command menu             *\n");
    printf("   ***************************************************************\n");
}

//List of arguments when necessary.
void main_print_arguments(){
    printf("\n   ****************************************\n");
    printf("   ****LIST OF MAP COMMANDS****************\n");
    printf("   ****************************************\n");
    printf("   *   m        to enter map maker        *\n");
    printf("   *   o        to change maps            *\n");
    printf("   *   e        to enter enemy maker      *\n");
    printf("   *   p        to print full map         *\n");
    printf("   *   x        to exit                   *\n");
    printf("   *   ?        to see command menu       *\n");
    printf("   ****************************************\n");
}

int mapIO(struct mapData *mData){

    char command[20];
    char com = '0', com2 = '0';
    int mapNum = mData->mapNum;
    int i = 0;
    int col, row, check;
    int num1, num2, num3, num4;
    char sym = '0';

    printf("\nSym: %c z:%i (%i,%i)(%i,%i)\nMap Maker: ", mData->sym, mData->z, mData->pColsRange[0], mData->pRowsRange[0], mData->pColsRange[1], mData->pRowsRange[1]);
    fgets(command, 19, stdin);
    while(command[i] != '\0'){
        if(isspace(command[i]) != 0){
            command[i] = '.';
        }
        ++i;
    }

    if (sscanf(command, "%c", &com) == 0){
        printf("\nInvalid Command\n");
        return mapNum;
    }else{
        switch(com){
        case 'i':
        case 'I':
            if(sscanf(command, "%c.%c", &com, &com2) != 2){
                return mapNum;
            }
            switch(com2){
            case 'c': //Insert at col row, as a col, num spots
            case 'C':
                if(sscanf(command, "%c.%c.%i.%i.%i", &com, &com2, &num1, &num2, &num3) == 5){
                    col = mData->pColsRange[0] + num1;
                    row = mData->pRowsRange[0] + num2;
                    check = rcChecker(*mData, col, row, num3, 'c');
                    if(check == -1){
                        printf("\nOut of range.\n");
                    }else{
                        for(i = row; i <= row + num3; ++i){
                            insert(mData->mp[mData->z], i, col, mData->sym);
                        }
                    }
                }else{
                    printf("\nInvalid inputs.\n");
                }
                return mapNum;
            case 'i':
            case 'I':
                if(sscanf(command, "%c.%c.%i.%i", &com, &com2, &num1, &num2) == 4){
                    col = mData->pColsRange[0] + num1;
                    row = mData->pRowsRange[0] + num2;
                    if(col > mData->pColsRange[1] || col < mData->pColsRange[0] || row < mData->pRowsRange[0] || row > mData->pRowsRange[1]){
                        printf("\nOut of range.\n");
                    }else{
                        insert(mData->mp[mData->z], row, col, mData->sym);
                    }
                    return mapNum;
                }
                return mapNum;
            case 'o':
            case 'O':
                if(sscanf(command, "%c.%c.%c", &com, &com2, &sym) == 3){
                    mData->sym = sym;
                }else{

                }
                return mapNum;
            case 'r': //Insert at col row, as a row, num spots
            case 'R':
                if(sscanf(command, "%c.%c.%i.%i.%i", &com, &com2, &num1, &num2, &num3) == 5){
                    col = mData->pColsRange[0] + num1;
                    row = mData->pRowsRange[0] + num2;
                    check = rcChecker(*mData, col, row, num3, 'r');
                    if(check == -1){
                        printf("\nOut of range.\n");
                    }else{
                        for(i = col; i <= col + num3; ++i){
                            insert(mData->mp[mData->z], row, i, mData->sym);
                        }
                    }
                }else{
                    printf("\nInvalid inputs.\n");
                }
                return mapNum;
            case 's': //Square (rectangle) insert
            case 'S':
                if(sscanf(command, "%c.%c.%i.%i.%i.%i", &com, &com2, &num1, &num2, &num3, &num4) == 6){
                    //Function for rectangle insert
                }else{
                    printf("\nInvalid inputs\n");
                }
                return mapNum;
            }
        case 'n':
        case 'N':
            if(mData->mp[8].obPtr == NULL){
                new_map(mData, 0);
            }else{
                printf("\nMap already loaded. Please save and close current map before creating a new map.\n");
            }
            return mapNum;
        case 'p':
        case 'P':
            map_print_handler(*mData);
            return mapNum;
        case 'r':
        case 'R': //Change range
            if(sscanf(command, "%c.%i.%i.%i.%i", &com, &num1, &num2, &num3, &num4) == 5){
                if(num1 < 0 || num2 < 0){
                    printf("\nLower bound out of range.\n");
                    return mapNum;
                }else if(num3 >= mData->fCols || num4 >= mData->fRows){
                    printf("\nUpper bound out of range.\n");
                    return mapNum;
                }else if(num3 <= num1 || num4 <= num2){
                    printf("\nNonsensical bounds.\n");
                    return mapNum;
                }
                mData->pColsRange[0] = num1;
                mData->pRowsRange[0] = num2;
                mData->pColsRange[1] = num3;
                mData->pRowsRange[1] = num4;
            }
            return mapNum;
        case 's':
        case 'S':
            save_handler(*mData);
            return mapNum;
        case 'x':
        case 'X':
            //free function
            return -1;
        case 'z':
        case 'Z':
            z_handler(&mData->z);
            return mapNum;
        default:
            map_print_arguments();
            return mapNum;
        }
    }

    return mapNum;
}

int mainIO(struct mapData *mData){

    char command[12];
    char com;
    int done = 0;
    int mCheck = 0;
    int y_n = 0;
    //int number, numSize, nBeg, nEnd, jump;


    while (mData->mapNum == -1){
        printf("\nMap Number not Set. Which map would you like to work on?\n");
        fgets(command, 5, stdin);
        if ((sscanf(command, "%i", &mData->mapNum) != 1) || mData->mapNum < 0){
            printf("\nInvalid Map\n");
        }else{
            mCheck = check_map_exist(mData); //If map exists, load it in.

            if(mCheck == 0){
                printf("\nMap num: %i doesn't exist. Make new map?\n", mData->mapNum);
                while(y_n == 0){
                    fgets(command, 10, stdin);
                    y_n = sscanf(command, "%c", &com);
                    if(y_n == 0){
                        printf("\nInvalid command. Choose yes or no.\n");
                    }
                }

                if(com == 'y' || com == 'Y'){
                    new_map(mData, 0);
                }else{
                    printf("\nNew map not created. Remember to create new map (n) in map menu (m).\n");
                }

            }else{
                printf("\nLoading in map %i. Starting at z level 8.\n", mData->mapNum);
            }
            printf("\nMap num: %i\n", mData->mapNum);
            main_print_arguments();
        }
    }

    printf("\nMain: ");
    fgets(command, 3, stdin);

    if (sscanf(command, "%c", &com) != 1){
        printf("\nInvalid Command\n");
        return 0;
    }else{
        switch (com){
        case 'z':
        case 'Z':
            return 0;
        case 's':
        case 'S':
            return 0;
        case 'p':
        case 'P':
            return 0;
        case 'm':
        case 'M':
            while(done != -1){
                done = mapIO(mData);
            }
            return 0;
        case 'o':
        case 'O':
            mData->mapNum = -1;
            return 0;
        case 'x':
        case 'X':
            return -1;
        case '?':
        default:
            main_print_arguments();
            return 0;
        }
    }

    return 0;
}
