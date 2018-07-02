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
//#include <pdcurses.h>
#include <form.h>
#include <menu.h>
#include <assert.h>
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

char *nextt[] = {"SIGUIENTE"};

int n_choices = sizeof(choices) / sizeof(char *);
int n_nextt = sizeof(nextt) / sizeof(char *);

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

void boton (WINDOW *menu_win, int highlight)
{
    int x, y;
    
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(int i = 0; i < n_nextt; ++i)
    {    if(highlight == i + 1) /* High light the present choice */
    {    wattron(menu_win, A_REVERSE);
        mvwprintw(menu_win, y, x, "%s", nextt[i]);
        wattroff(menu_win, A_REVERSE);
    }
    else
        mvwprintw(menu_win, y, x, "%s", nextt[i]);
        ++y;
    }
    wrefresh(menu_win);
}

//---------- cambia a espacios el form
static char* trim_whitespaces(char *str)
{
    char *end;
    
    // trim leading space
    while(isspace(*str))
        str++;
    
    if(*str == 0) // all spaces?
        return str;
    
    // trim trailing space
    end = str + strnlen(str, 128) - 1;
    
    while(end > str && isspace(*end))
        end--;
    
    // write new null terminator
    *(end+1) = '\0';
    
    return str;
}

//----------- navegador del form
static FORM *ficha_medica_form;
static WINDOW *ficha_medica, *ficha_medica_body;
static FIELD *ficha_medica_fields[25];
static void driver(int ch)
{
    switch (ch)
    {
        case KEY_DOWN:
            form_driver(ficha_medica_form, REQ_NEXT_FIELD);
            form_driver(ficha_medica_form, REQ_END_LINE);
            break;
            
        case KEY_UP:
            form_driver(ficha_medica_form, REQ_PREV_FIELD);
            form_driver(ficha_medica_form, REQ_END_LINE);
            break;
            
        case KEY_LEFT:
            form_driver(ficha_medica_form, REQ_PREV_CHAR);
            break;
            
        case KEY_RIGHT:
            form_driver(ficha_medica_form, REQ_NEXT_CHAR);
            break;
        
            // Delete the char before cursor
        case 127:
            form_driver(ficha_medica_form, REQ_DEL_PREV);
            break;
            
            // Delete the char under the cursor
        case KEY_DC:
            form_driver(ficha_medica_form, REQ_DEL_CHAR);
            break;
            
        default:
            form_driver(ficha_medica_form, ch);
            break;
    }
    
    wrefresh(ficha_medica);
}























//-----------------------------------------------------
int main()
{
    WINDOW *menu_win, *doctores_body;
    //FORM *ficha_medica_form;
    //FIELD *ficha_medica_fields[25];
    
    char mesg[]="Med Diary";
    int row,col;
    int highlight = 1;
    int choice = 0;
    int c, ch;
    
    //------ inicio del programa
    initscr();                /* start the curses mode */
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    
    //------ barra de inicio
    getmaxyx(stdscr,row,col);
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
   
    //------- Ficha medica

    if (choice == 1)
    {
        clear();
        refresh();
        getmaxyx(stdscr,row,col);
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
    
    ficha_medica_body = newwin(24, 80, 0, 0);
    assert(ficha_medica_body != NULL);
    box(ficha_medica_body, 0, 0);
    ficha_medica = derwin(ficha_medica_body, 20, 78, 3, 1);
    assert(ficha_medica != NULL);
    box(ficha_medica, 0, 0);
    scrollok(ficha_medica,TRUE);
    idlok(ficha_medica, true);
    refresh();
    mvwprintw(ficha_medica_body, 1, 2, "Ficha Médica");
    //--------- pag 1
    // FIELD *new_field(int height, int width, int toprow, int leftcol, int offscreen, int nbuffers);
    ficha_medica_fields[0] = new_field(1, 20, 0, 1, 0, 0);
    ficha_medica_fields[1] = new_field(1, 40, 0, 21, 0, 0);
    ficha_medica_fields[2] = new_field(1, 20, 2, 1, 0, 0);
    ficha_medica_fields[3] = new_field(1, 40, 2, 21, 0, 0);
    ficha_medica_fields[4] = new_field(2, 20, 4, 1, 0, 0);
    ficha_medica_fields[5] = new_field(1, 40, 4, 21, 0, 0);
    ficha_medica_fields[6] = new_field(1, 20, 6, 1, 0, 0);
    ficha_medica_fields[7] = new_field(1, 40, 6, 21, 0, 0);
    ficha_medica_fields[8] = new_field(1, 20, 8, 1, 0, 0);
    ficha_medica_fields[9] = new_field(1, 40, 8, 21, 0, 0);
    ficha_medica_fields[10] = new_field(1, 20, 10, 1, 0, 0);
    ficha_medica_fields[11] = new_field(1, 40, 10, 21, 0, 0);
    ficha_medica_fields[12] = new_field(1, 20, 12, 1, 0, 0);
    ficha_medica_fields[13] = new_field(1, 40, 12, 21, 0, 0);
    ficha_medica_fields[14] = new_field(1, 20, 14, 1, 0, 0);
    ficha_medica_fields[15] = new_field(1, 40, 14, 21, 0, 0);
    ficha_medica_fields[16] = new_field(1, 20, 16, 1, 0, 0);
    ficha_medica_fields[17] = new_field(1, 40, 16, 21, 0, 0);
    /*ficha_medica_fields[18] = new_field(1, 20, 16, 1, 0, 0);
    ficha_medica_fields[19] = new_field(1, 40, 18, 21, 0, 0);
    ficha_medica_fields[20] = new_field(1, 20, 18, 1, 0, 0);
    ficha_medica_fields[21] = new_field(1, 40, 20, 21, 0, 0);
    ficha_medica_fields[22] = new_field(1, 20, 20, 1, 0, 0);
    ficha_medica_fields[23] = new_field(1, 40, 22, 21, 0, 0);
    ficha_medica_fields[24] = new_field(1, 20, 22, 1, 0, 0);*/
    assert(ficha_medica_fields[0] != NULL &&
           ficha_medica_fields[1] != NULL &&
           ficha_medica_fields[2] != NULL &&
           ficha_medica_fields[3] != NULL &&
           ficha_medica_fields[4] != NULL &&
           ficha_medica_fields[5] != NULL &&
           ficha_medica_fields[6] != NULL &&
           ficha_medica_fields[7] != NULL &&
           ficha_medica_fields[8] != NULL &&
           ficha_medica_fields[9] != NULL &&
           ficha_medica_fields[10] != NULL &&
           ficha_medica_fields[11] != NULL &&
           ficha_medica_fields[12] != NULL &&
           ficha_medica_fields[13] != NULL &&
           ficha_medica_fields[14] != NULL &&
           ficha_medica_fields[15] != NULL &&
           ficha_medica_fields[16] != NULL &&
           ficha_medica_fields[17] != NULL /*&&
           ficha_medica_fields[18] != NULL &&
           ficha_medica_fields[19] != NULL &&
           ficha_medica_fields[20] != NULL &&
           ficha_medica_fields[21] != NULL &&
           ficha_medica_fields[22] != NULL &&
           ficha_medica_fields[23] != NULL &&
           ficha_medica_fields[24] != NULL*/);
    
    set_field_buffer(ficha_medica_fields[0], 0, "Nombre completo");
    set_field_buffer(ficha_medica_fields[1], 0, "");
    set_field_buffer(ficha_medica_fields[2], 0, "Fecha de nacimiento");
    set_field_buffer(ficha_medica_fields[3], 0, "DD/MM/AAAA");
    set_field_buffer(ficha_medica_fields[4], 0, "Padecimientos\nmedicos");
    set_field_buffer(ficha_medica_fields[5], 0, "");
    set_field_buffer(ficha_medica_fields[6], 0, "Notas medicas");
    set_field_buffer(ficha_medica_fields[7], 0, "");
    set_field_buffer(ficha_medica_fields[8], 0, "Alergias");
    set_field_buffer(ficha_medica_fields[9], 0, "");
    set_field_buffer(ficha_medica_fields[10], 0, "Medicamentos");
    set_field_buffer(ficha_medica_fields[11], 0, "");
    set_field_buffer(ficha_medica_fields[12], 0, "Tipo de sangre");
    set_field_buffer(ficha_medica_fields[13], 0, "");
    set_field_buffer(ficha_medica_fields[14], 0, "Donación de Organos");
    set_field_buffer(ficha_medica_fields[15], 0, "");
    set_field_buffer(ficha_medica_fields[16], 0, "Peso");
    set_field_buffer(ficha_medica_fields[17], 0, "");
    set_field_buffer(ficha_medica_fields[18], 0, "Estatura");
    set_field_buffer(ficha_medica_fields[19], 0, "");
    set_field_buffer(ficha_medica_fields[20], 0, "Contacto de emergencia:");
    set_field_buffer(ficha_medica_fields[21], 0, "Nombres");
    set_field_buffer(ficha_medica_fields[22], 0, "");
    set_field_buffer(ficha_medica_fields[23], 0, "Número");
    set_field_buffer(ficha_medica_fields[24], 0, "");
    
    set_field_opts(ficha_medica_fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[7], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields[8], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[9], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields[10], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[11], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields[12], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[13], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields[14], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[15], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields[16], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[17], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields[18], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[19], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields[20], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[21], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[22], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields[23], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields[24], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    
    set_field_back(ficha_medica_fields[1], A_UNDERLINE);
    set_field_back(ficha_medica_fields[3], A_UNDERLINE);
    set_field_back(ficha_medica_fields[5], A_UNDERLINE);
    set_field_back(ficha_medica_fields[7], A_UNDERLINE);
    set_field_back(ficha_medica_fields[9], A_UNDERLINE);
    set_field_back(ficha_medica_fields[11], A_UNDERLINE);
    set_field_back(ficha_medica_fields[13], A_UNDERLINE);
    set_field_back(ficha_medica_fields[15], A_UNDERLINE);
    set_field_back(ficha_medica_fields[17], A_UNDERLINE);
    set_field_back(ficha_medica_fields[19], A_UNDERLINE);
    set_field_back(ficha_medica_fields[22], A_UNDERLINE);
    set_field_back(ficha_medica_fields[24], A_UNDERLINE);
    
    ficha_medica_form = new_form(ficha_medica_fields);
    assert(ficha_medica_form != NULL);
    set_form_win(ficha_medica_form, ficha_medica);
    set_form_sub(ficha_medica_form, derwin(ficha_medica, 18, 76, 1, 1));
    post_form(ficha_medica_form);
    
    refresh();
    wrefresh(ficha_medica_body);
    wrefresh(ficha_medica);
    
    while ((ch = getch()) != KEY_F(1))
        driver(ch);
    
    unpost_form(ficha_medica_form);
    free_form(ficha_medica_form);
    free_field(ficha_medica_fields[0]);
    free_field(ficha_medica_fields[1]);
    free_field(ficha_medica_fields[2]);
    free_field(ficha_medica_fields[3]);
    delwin(ficha_medica);
    delwin(ficha_medica_body);
    
    
    //------- Doctores
    if (choice == 2)
    {
        clear();
        refresh();
        getmaxyx(stdscr,row,col);
        for (int i = 0; i < col; i++) {
            printw("-");
        };
        
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
