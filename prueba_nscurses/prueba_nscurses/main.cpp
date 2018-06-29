//
//  main.cpp
//  prueba_nscurses
//
//  Created by Andrea Diaz ♡ on 6/14/18.
//  Copyright © 2018 Andrea Diaz ♡. All rights reserved.
//


#include <stdio.h>
#include <iostream>
#include <ncurses.h>
#include <menu.h>
#include "sources/laboratorio.cpp"
#include "sources/bioquimica_orina.cpp"


//----- menu
#define CTRLD 4
#define WIDTH 30
#define HEIGHT 10

int startx = 0;
int starty = 0;

char *choices[] = {
    "Ficha Medica",
    "Doctores",
    "Laboratios",
    "Citas Medicas",
    "Exit",
};

int n_choices = sizeof(choices) / sizeof(char *);

void menu (WINDOW *menu_win, int highlight)
{
    int x, y;
    
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(int i = 0; i < n_choices; ++i)
    {    if(highlight == i + 1) /* High light the present choice */
    {    wattron(menu_win, A_REVERSE);
        mvwprintw(menu_win, y, x, "%s", choices[i]);
        wattroff(menu_win, A_REVERSE);
    }
    else
        mvwprintw(menu_win, y, x, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}


//-----------------------------------------------------
int main()
{
    ITEM **my_items;
    WINDOW *menu_win;
    ITEM *cur_item;
    char mesg[]="Med Diary";
    int row,col;
    int highlight = 1;
    int choice = 0;
    int c;
    
    //------ inicio del programa
    initscr();                /* start the curses mode */
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    
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
    
    //------- menu
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;
    
    menu_win = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
    menu(menu_win, highlight);
    while(1)
    {    c = wgetch(menu_win);
        switch(c)
        {
            case KEY_UP:
                if(highlight == 1)
                {
                    highlight = n_choices;
                }
            
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == n_choices)
                    highlight = 1;
                else
                    ++highlight;
                break;
            case 10:
                choice = highlight;
                //mvprintw(20, 0, "Item selected is %d", choice);
                //break;
               /* if (choice == 1)
                {
                    //newwin(0,0,0,0);
                    //mvprintw(20, 0, "hola");
                    clear();
                    refresh();
                    mvaddstr(5,20,"Holy updates, Batman!");
                    clearok(stdscr,TRUE);
                    refresh();
                }
                else
                {
                    mvprintw(20, 0, "Item selected is %d", choice);
                    break;
                }*/
            default:
                mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c'", c, c);
                refresh();
                break;
        }
        menu(menu_win, highlight);
        if(choice != 0)    /* User did a choice come out of the infinite loop */
            break;
    }
 
    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
    clrtoeol();
   
    //------- menu getaways jzjzjzjz
    if (choice == 1)
    {
        clear();
        refresh();
        getmaxyx(stdscr,row,col);        /* get the number of rows and columns */
        for (int i = 0; i < col; i++) {
            printw("-");
        };
        mvchgat(0, 0, -1, A_NORMAL, 1, NULL);
        mvprintw(1,(col-strlen(mesg))/2,"%s",mesg); //imprime en la posicion dada
        printw("\n");
        for (int i = 0; i < col; i++)
        {
            printw("-");
        }
    }
    
    
    
    //------- corriendo programa
    refresh();
    getch();

    //--------------------------
    
    
    //------- fin de programa
    endwin();
    //-----------------------
    
    return 0;
}
