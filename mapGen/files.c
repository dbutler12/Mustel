#include "mapGen.h"


int read_map_config(struct mapData *mData){

    FILE *fp;
    char filename[64];
    sprintf (filename, "../resources/map%i/m_config.bin", mData->mapNum);

    if ((fp = fopen(filename,"r")) == NULL){
       // Program exits if the file pointer returns NULL.
       return 0; //Return 0 for file doesn't exist.
    }

    fread(&mData->fRows, sizeof(mData->fRows), 1, fp);
    fread(&mData->fCols, sizeof(mData->fCols), 1, fp);

    fclose(fp);

    return 1; //Return 1 for success
}

//Write the configuration file for current map
int write_map_config(struct mapData mData){
    FILE *fp;
    char filename[64];
    sprintf (filename, "../resources/map%i/m_config.bin", mData.mapNum);

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
    sprintf (filename, "../resources/map%i/%iz.bin", mData.mapNum, z);

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

//Inputs: multidimensional array, rows and cols of array, map number, and 'z' level of map
int read_map_Bin(struct mapData *mData, int z){

    int i, j;
    int nrows = mData->fRows;
    int ncols = mData->fCols;
    FILE *fp;
    char filename[64];
    sprintf (filename, "../resources/map%i/%iz.bin", mData->mapNum, z);

   if ((fp = fopen(filename,"r")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       return -1;
   }

    for(i = 0; i < nrows; ++i){
        for (j = 0; j < ncols; ++j){

            fread(&mData->mp[z].obPtr[i][j], sizeof(char), 1, fp);
        }
    }

   fclose(fp);

   return 0;
}


/*void readBin()
{
   int n;
   struct threeNum num;
   FILE *ptr;

   if ((ptr = fopen("C:\\Users\\Saana\\GitProj\\Programs\\CSE1f\\Practice\\Files\\tester.bin","rb")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }

   // Moves the cursor to the end of the file
   fseek(ptr, -sizeof(struct threeNum), SEEK_END);

   for(n = 1; n < 5; ++n)
   {
      fread(&num, sizeof(struct threeNum), 1, ptr);
      printf("n1: %d\tn2: %d\tn3: %d\n", num.n1, num.n2, num.n3);
      fseek(ptr, -2*sizeof(struct threeNum), SEEK_CUR);
   }
   fclose(ptr);
}*/
