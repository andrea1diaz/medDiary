#include <ncurses.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>

using namespace std;

/*#include <stdlib.h>
#include <time.h>
#define FILENAME "windump"
int main(void)
{
    char word[7];
    int x,w,r;
    
    srandom((unsigned)time(NULL));
    word[7] = '\0';
    initscr();

    // Fill most of the screen with random 6-char words
    for(x=0;x<200;x++)
        {
            for(w=0;w<6;w++)
                word[w] = (random() % 26) + 'a';
                    }
    addch('\n');
    addstr("Press Enter to write this screen to disk\n");
    refresh();
    getch();
// write the window to disk
printw("%s\t",word);
r= scr_dump(FILENAME); if( r == ERR)
addstr("Error writing window to disk\n");
else
addstr("File written; press Enter to quit\n");
refresh();
getch();
endwin();
return 0;
}
 */

#include <stdlib.h>
#define FILENAME "window.dat"
void bomb(char *message);
int main(void)
{
    /*FILE *wfile;
    WINDOW *win;
    int r;*/
    
    fstream FHandle;
    FHandle.open("window.txt", ios::out);
    if(FHandle.is_open())
        cout << "Opened !";
    else
        cout << "Not Opened !";

    /*initscr();
    start_color();
    init_pair(1,COLOR_WHITE,COLOR_BLUE);
    
    addstr("Press Enter to read the window from disk:\n");
    refresh();
    getch();

    //open the file
    wfile = fopen(FILENAME,"r");
    rif( wfile==NULL)
        bomb("Error reading file\n");
    
    // write the window’s data
    win = getwin(wfile);
    if( win == NULL )
        bomb("Unable to read/create window\n");
    fclose(wfile);
    wrefresh(win);
getch();*/
endwin();
return 0;
}
void bomb(char *message)
{
    addstr(message);
    refresh();
    getch();
    endwin();
    exit(1);
}
