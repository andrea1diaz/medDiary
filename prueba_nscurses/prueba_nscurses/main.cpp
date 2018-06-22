//
//  main.cpp
//  prueba_nscurses
//
//  Created by Andrea Diaz ♡ on 6/14/18.
//  Copyright © 2018 Andrea Diaz ♡. All rights reserved.
//



#include <iostream>

using namespace std;


#include <ncurses.h>
#include "sources/laboratorio.cpp"
#include "sources/bioquimica_orina.cpp"

int main()
{
    char mesg[]="Med Diary";        /* message to be appeared on the screen */
    int row,col;
    
    //------ inicio del programa
    initscr();                /* start the curses mode */
    start_color();            /* Start color functionality    */
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    
    //------ barra de inicio
    getmaxyx(stdscr,row,col);        /* get the number of rows and columns */
    for (int i = 0; i < col; i++) {
        printw("-");
    };
    mvchgat(0, 0, -1, A_NORMAL, 1, NULL);
    mvprintw(1,(col-strlen(mesg))/2,"%s",mesg); //imprime en la posicion dada
    printw("\n");
    for (int i = 0; i < col; i++) {
        printw("-");
    };
    //----------------------
    
    //printw("A Big string which i didn't care to type fully ");
    
    //------- barra del final
    mvprintw(row-3, 0, "\n");
    for (int i = 0; i < col; i++) {
        printw("-");
    };
    printw("\n");
    printw("MD®");
    //-----------------------
    
    //------- corriendo programa
    refresh();
    getch();
    //--------------------------
    
    
    //------- fin de programa
    endwin();
    //-----------------------
    
    return 0;
}
