#include "mapGen.h"

void insert(struct maps mp, int row, int col, char sym){
    mp.obPtr[row][col] = sym;
}

void symbol_change(char *current){

    char command[8];

    printf("\nWhich symbol? ");
    fgets(command, 3, stdin);

    if (sscanf(command, "%c", current) != 1){
        printf("\nInvalid Symbol. Setting to 0\n");
        current = '\0';
    }
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

void print_non_display(struct mapData mData){

    int i = 0;
    int j = 0;
    int k = 0;

    if(mData.mp[mData.z].obPtr == NULL){
        printf("\nEmpty map!\n");
        return;
    }

    printf("    ");

    for(i = 0; i <= mData.pColsRange[1] - mData.pColsRange[0]; ++i){
        printf("%i ", (i - i%10)/10);
    }

    printf("\n    ");

    for(i = 0; i <= mData.pColsRange[1] - mData.pColsRange[0]; ++i){
        printf("%i ", i%10);
    }

    printf("\n\n");

    for (i = mData.pRowsRange[0]; i <= mData.pRowsRange[1]; ++i){
        printf("%2i ", k++);
        for (j = mData.pColsRange[0]; j <= mData.pColsRange[1]; ++j){
            printf("%2c", mData.mp[mData.z].obPtr[i][j]);
        }
        printf("\n");
    }
}
