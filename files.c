#include "mustel.h"

//Read map configuration file
int read_map_config(struct mapData *mData){

    FILE *fp;
    char filename[64];
    sprintf (filename, "resources/map%i/m_config.bin", mData->mapNum);

    if ((fp = fopen(filename,"r")) == NULL){
       // Program exits if the file pointer returns NULL.
       return 0; //Return 0 for file doesn't exist.
    }

    fread(&mData->fRows, sizeof(mData->fRows), 1, fp);
    fread(&mData->fCols, sizeof(mData->fCols), 1, fp);

    fclose(fp);

    return 1; //Return 1 for success
}


//Inputs: multidimensional array, rows and cols of array, map number, and 'z' level of map
int read_map_bin(struct mapData *mData, int z){

    int i, j;
    int nrows = mData->fRows;
    int ncols = mData->fCols;
    mData->mp[z].ncols = ncols;
    mData->mp[z].nrows = nrows;
    FILE *fp;
    char filename[64];
    sprintf (filename, "resources/map%i/%iz.bin", mData->mapNum, z);

    if ((fp = fopen(filename,"r")) == NULL){
        printf("Error! opening file");

        // Program exits if the file pointer returns NULL.
        return 0;
    }

    for(i = 0; i < nrows; ++i){
        for (j = 0; j < ncols; ++j){
            fread(&mData->mp[z].obPtr[i][j], sizeof(char), 1, fp);
            mData->mp[z].viewMap[i][j] = mData->mp[z].obPtr[i][j];
        }
    }


   fclose(fp);

   return 1;
}

//Write the configuration file for current map
int write_map_config(struct mapData mData){
    FILE *fp;
    char filename[64];
    sprintf (filename, "resources/map%i/m_config.bin", mData.mapNum);

    if ((fp = fopen(filename,"wb")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       return -1;
   }

    fwrite(&mData.fRows, sizeof(mData.fRows), 1, fp);
    fwrite(&mData.fCols, sizeof(mData.fCols), 1, fp);

   fclose(fp);

    return 0;
}

//Inputs: multidimensional array, rows and cols of array, map number, and 'z' level of map
int write_map_Bin(struct mapData mData, int z){

    int i, j;
    int nrows = mData.fRows;
    int ncols = mData.fCols;
    FILE *fp;
    char filename[64];
    sprintf (filename, "resources/map%i/%iz.bin", mData.mapNum, z);

   if ((fp = fopen(filename,"wb")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       return -1;
   }

    /*for(i = 0; i < nrows; ++i){
        fwrite(mData.mp[z].obPtr[i], sizeof(char), ncols, fp);
    }*/

    for(i = 0; i < nrows; ++i){
        for (j = 0; j < ncols; ++j){

            fwrite(&mData.mp[z].obPtr[i][j], sizeof(char), 1, fp);
        }
    }

   fclose(fp);

   return 0;
}
