#include "mustel.h"

int main(int argc, char *argv[]){

    char command  = '0';
    int i;


    //Pointers to each window
    WINDOW *map; WINDOW *commands; WINDOW *input; WINDOW *inventory; WINDOW *status;
	int com;

    //temp player variables
    int pL = ML/2; int pH = MH/2;
    int eR = pL + 30; int eL = pL - 31;
    int eT = pH - 16; int eB = pH + 16;

    //Curses initializations
	initscr();
	cbreak();
    noecho();
	keypad(stdscr, TRUE);
	curs_set(0);
    refresh();

    //Create all windows
	map = createWin(MH, ML, 0, 0);
	inventory = createWin(MH, IL, 0, ML);
	input = createWin(NH, ML, MH, 0);
	commands = createWin(CH, ML, MH + NH, 0);
	status = createWin(NH + CH, IL, MH, ML);

	wrefresh(map);

    //curses setting, may need modified
    nodelay(stdscr, TRUE);

    struct package allData;
    allData.monsUIDCount = 0;
    allData.itemUIDCount = 0;
    packageLoader(&allData);
    updateMap(&map, &commands, &allData, &command, allData.pLoc);

    for (;;) {
        if ((com = getch()) == ERR) {

        }
        else if(com != KEY_F(1)) {
            switch(com){
                case KEY_LEFT:
                    command = 'a';
                    break;
                case KEY_RIGHT:
                    command = 'd';
                    break;
                case KEY_UP:
                    command = 'w';
                    break;
                case KEY_DOWN:
                    command = 's';
                    break;
            }

            allData.counter2++; //Movement Counter
            updateMap(&map, &commands, &allData, &command, allData.pLoc);
        }else{
            break;
        }

        allData.counter1++; //Time counter
        if(allData.counter1 > 30000){
            command = '0';
            fullRefreshAll(&map, &inventory, &input, &commands, &status);
            updateMap(&map, &commands, &allData, &command, allData.pLoc);
            allData.counter1 = 0;
        }else{
            refreshAll(&map, &inventory, &input, &commands, &status);
        }
                    //Recreate outlines if resizing happens.
    }

	endwin();

	return 0;

}

void fullRefreshAll(WINDOW **map, WINDOW **commands, WINDOW **input, WINDOW **inventory, WINDOW **status){
        destroyWin(*map);
        destroyWin(*inventory);
        destroyWin(*commands);
        destroyWin(*status);
        destroyWin(*input);
        *map = createWin(MH, ML, 0, 0);
        *inventory = createWin(MH, IL, 0, ML);
        *input = createWin(NH, ML, MH, 0);
        *commands = createWin(CH, ML, MH + NH, 0);
        *status = createWin(NH + CH, IL, MH, ML);
        box(*map, 0 , 0);
        box(*inventory, 0 , 0);
        box(*input, 0 , 0);
        box(*commands, 0, 0);
        box(*status, 0, 0);
        wrefresh(*map);
        wrefresh(*commands);
        wrefresh(*input);
        wrefresh(*inventory);
        wrefresh(*status);
}

void refreshAll(WINDOW **map, WINDOW **commands, WINDOW **input, WINDOW **inventory, WINDOW **status){
        wrefresh(*map);
        wrefresh(*commands);
        wrefresh(*input);
        wrefresh(*inventory);
        wrefresh(*status);
}

WINDOW *createWin(int height, int width, int starty, int startx){

    WINDOW *win;

	win = newwin(height, width, starty, startx);
	box(win, 0 , 0);		/* 0, 0 gives default characters
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(win);		/* Show that box 		*/

	return win;
}

void destroyWin(WINDOW *win)
{
	wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');

	wrefresh(win);
	delwin(win);
}
