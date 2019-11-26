************************************************************************************
* MUSTELID *************************************************************************
************************************************************************************
Author: Dwayne Butler
Saanail.Vernath@gmail.com


************************************************************************************
* Description **********************************************************************
************************************************************************************
This program is a prototype for a topdown RPG made uses the nCurses library on Linux machines. The nCurses library needs to be installed prior to running this program.

Currently the program loads in a mapfile from resources and allows the player (P) to move around using the arrow keys to explore the map. It was created to showcase the use of nCurses to display characters in the form that could be used for a game. 

The structures and functions used are setup for easy expansion of the 'game', and if the project continues, the next step would be to add more interactions (like battles or npcs).



MAPGEN:

Included in this package is a basic map creation tool. This tool allows maps to be generated using a command line menu. Maps created this way are stored in the Mustelid resources folder which will be used when Mustel is run.

************************************************************************************
* Compile and Run ******************************************************************
************************************************************************************
To compile in command line(on linux):

Make sure to have nCurses installed:
sudo apt-get install libncurses5-dev libncursesw5-dev

Then just use the makefile by calling:
make


To run after compiling:
./Mustel



MAPGEN:

Navigate to the mapGen folder and call:
make

To run after compiling:
./MapGen

************************************************************************************
* Files ****************************************************************************
************************************************************************************
Each file below has more detailed comment descriptions within them if you want to know more.

files.c
main.c
map.c
resources (directory)
spawner.c
loaders.c
makefile
mustel.h


MAPGEN:

files.c
genIO.c
main.c
makefile
map.c
mapGen.h
maphandler.c
resources(directory)

