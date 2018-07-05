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
#include <stdlib.h>
#include <fstream>
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
    "Laboratorios",
    "Exit",
};

char *nextt[] = {"GUARDAR(F1)  "
                 "SIGUIENTE(F2)  "
                 "MENU(F3)",
};

char *nextt_2[] = {"GUARDAR(F1)  "
    "ANTERIOR(F2)  "
    "MENU(F3)",
};

const char *choiceslab[] = {
    "Hematologia",
    "Bioquimica Sangre",
    "Bioquimica Orina",
    "Inmunologia",
    "Drogas"
    "Heces",
};

int n_choices = sizeof(choices) / sizeof(char *);
int n_nextt = sizeof(nextt) / sizeof(char *);
int n_nextt_2 = sizeof(nextt_2) / sizeof(char *);

int n_choiceslab = sizeof(choices) / sizeof(char *);
int n_nexttlab = sizeof(nextt) / sizeof(char *);
int n_nextt_2lab = sizeof(nextt_2) / sizeof(char *);

void menu (WINDOW *menu_win, int highlight)
{
    int x, y;
    
    x = 8;
    y = 3;
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


//------- menu lab
void menulab(WINDOW *menu_winlab, int highlight)
{
    int x, y;
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;
    x = 2;
    y = 2;
    box(menu_winlab, 0, 0);
    for (int i = 0; i < n_choiceslab; ++i) {
        if (highlight == i + 1) /* High light the present choice */
        {
            wattron(menu_winlab, A_REVERSE);
            mvwprintw(menu_winlab, y, x, "%s", choiceslab[i]);
            wattroff(menu_winlab, A_REVERSE);
        } else
            mvwprintw(menu_winlab, y, x, "%s", choiceslab[i]);
        ++y;
    }
    wrefresh(menu_winlab);
}


//--------- barra inferior con opciones
void botones (WINDOW *barra, int highlight)
{
    int x, y;
    
    x = 38;
    y = 1;
    box(barra, 0, 0);
    for(int i = 0; i < n_nextt; ++i)
    {
        if(highlight == i + 1) /* High light the present choice */
        {
            //wattron(barra, A_REVERSE);
            mvwprintw(barra, y, x, "%s", nextt[i]);
            //wattroff(barra, A_REVERSE);
        }
    else
        mvwprintw(barra, y, x, "%s", nextt[i]);
        ++y;
    }
    wrefresh(barra);
}

void botones_2 (WINDOW *barra, int highlight)
{
    int x, y;
    
    x = 40;
    y = 1;
    box(barra, 0, 0);
    for(int i = 0; i < n_nextt_2; ++i)
    {
        if(highlight == i + 1) /* High light the present choice */
        {
            //wattron(barra, A_REVERSE);
            mvwprintw(barra, y, x, "%s", nextt_2[i]);
            //wattroff(barra, A_REVERSE);
        }
        else
            mvwprintw(barra, y, x, "%s", nextt_2[i]);
        ++y;
    }
    wrefresh(barra);
}


//--------- intro. de variables -------
//--------- variables de la ficha medica
static FORM *ficha_medica_form;
static FORM *ficha_medica_form_2;
static WINDOW *ficha_medica, *ficha_medica_body, *ficha_medica_2, *ficha_medica_body_2, *barra, *barra_2, *doctores_win;
static FIELD *ficha_medica_fields[16], *ficha_medica_fields_2[9];

//--------- variables laboratorio ----------------
static FORM *lab_form;
static FORM *lab_form_2;
static WINDOW *lab, *lab_body, *lab_2, *lab_body_2, *barralab, *barra_2lab, *doctores_winlab;
static FIELD *lab_fields[16], *lab_fields_2[9];




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
void form1 (int h);
void form2 (int g);
int main();

static void driver(int ch)
{
    int g = 0;
    
    switch (ch)
    {
        case KEY_F(1):
        {
            fstream fm_file;
            fm_file.open("ficha_medica.txt", ios::out);
            if (fm_file.is_open())
            {
                //fm_file << trim_whitespaces(field_buffer(ficha_medica_fields[1],0)) << "\n";
                for (int i = 1; ficha_medica_fields[i]; i = i + 2)
                {
                    fm_file << trim_whitespaces(field_buffer(ficha_medica_fields[i], 0));
                    fm_file << "\n";
                }
            }
            break;
        }
            
        case KEY_F(2):
        {
            ficha_medica_form_2 = new_form(ficha_medica_fields_2);
            assert(ficha_medica_fields_2 != NULL);
            form2(g);
            break;
        }
            
        case KEY_F(3):
        {
            
            ficha_medica_form = new_form(ficha_medica_fields);
            assert(ficha_medica_fields != NULL);
            
            main();
            break;
        }
            
            
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
        
        case 127:
            form_driver(ficha_medica_form, REQ_DEL_PREV);
            break;
            
        case KEY_DC:
            form_driver(ficha_medica_form, REQ_DEL_CHAR);
            break;
            
        default:
            form_driver(ficha_medica_form, ch);
            break;
    }
    
    
    wrefresh(ficha_medica);
}

static void driver_2(int f)
{
    int ch = 0;
    switch (f)
    {
        case KEY_F(1):
        {
            fstream fm_file;
            fm_file.open("ficha_medica2.txt", ios::out);
            if (fm_file.is_open())
            {
                fm_file << trim_whitespaces(field_buffer(ficha_medica_fields_2[1],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(ficha_medica_fields_2[3],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(ficha_medica_fields_2[6],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(ficha_medica_fields_2[8],0)) << "\n";
                /*for (int i = 1; ficha_medica_fields_2[i]; i = i + 2)
                 {
                 fm_file << trim_whitespaces(field_buffer(ficha_medica_fields_2[i], 0));
                 fm_file << "\n";
                 }*/
            }
            break;
        }
            
        case KEY_F(2):
        {
            ficha_medica_form = new_form(ficha_medica_fields);
            assert(ficha_medica_fields != NULL);
            printw("hi");
            form1(ch);
            break;
        }
            
        case KEY_F(3):
        {
            ficha_medica_form = new_form(ficha_medica_fields);
            assert(ficha_medica_fields != NULL);
            
            main();
            break;
        }
            
        case KEY_DOWN:
            form_driver(ficha_medica_form_2, REQ_NEXT_FIELD);
            form_driver(ficha_medica_form_2, REQ_END_LINE);
            break;
            
        case KEY_UP:
            form_driver(ficha_medica_form_2, REQ_PREV_FIELD);
            form_driver(ficha_medica_form_2, REQ_END_LINE);
            break;
            
        case KEY_LEFT:
            form_driver(ficha_medica_form_2, REQ_PREV_CHAR);
            break;
            
        case KEY_RIGHT:
            form_driver(ficha_medica_form_2, REQ_NEXT_CHAR);
            break;
            
            // Delete the char before cursor
        case 127:
            form_driver(ficha_medica_form_2, REQ_DEL_PREV);
            break;
            
            // Delete the char under the cursor
        case KEY_DC:
            form_driver(ficha_medica_form_2, REQ_DEL_CHAR);
            break;
            
        default:
            form_driver(ficha_medica_form_2, f);
            break;
    }
    
    wrefresh(ficha_medica_2);
}



static void lab_driver_1(int f)
{
    int h = 0;
    
    switch (f)
    {
        case KEY_F(1):
        {
            fstream fm_file;
            fm_file.open("lab.txt", ios::out);
            if (fm_file.is_open())
            {
                /*fm_file << trim_whitespaces(field_buffer(lab_fields[1],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[3],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[6],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[8],0)) << "\n";*/
                for (int i = 1; lab_fields[i]; i = i + 2)
                 {
                 fm_file << trim_whitespaces(field_buffer(lab_fields[i], 0));
                 fm_file << "\n";
                 }
            fm_file.close();
            }
            break;
        }
            
        case KEY_F(3):
        {
            lab_form = new_form(lab_fields);
            assert(lab_fields != NULL);
            main();
            break;
        }
            
        case KEY_DOWN:
            form_driver(lab_form, REQ_NEXT_FIELD);
            form_driver(lab_form, REQ_END_LINE);
            break;
            
        case KEY_UP:
            form_driver(lab_form, REQ_PREV_FIELD);
            form_driver(lab_form, REQ_END_LINE);
            break;
            
        case KEY_LEFT:
            form_driver(lab_form, REQ_PREV_CHAR);
            break;
            
        case KEY_RIGHT:
            form_driver(lab_form, REQ_NEXT_CHAR);
            break;
            
        case 127:
            form_driver(lab_form, REQ_DEL_PREV);
            break;
            
            // Delete the char under the cursor
        case KEY_DC:
            form_driver(lab_form, REQ_DEL_CHAR);
            break;
            
        default:
            form_driver(lab_form, f);
            break;
    }
    
    wrefresh(lab);
}



//----------- ficha_medica_form pg. 1
void form1 (int ch)
{
    keypad(stdscr, TRUE);
    getch();
    
    int highlight = 1;
    
    clear();
    refresh();
    ficha_medica_body = newwin(24, 80, 0, 0);
    assert(ficha_medica_body != NULL);
    box(ficha_medica_body, 0, 0);
    ficha_medica = derwin(ficha_medica_body, 16, 78, 3, 1);
    assert(ficha_medica != NULL);
    //box(ficha_medica, 0, 0);
    barra = derwin(ficha_medica_body, 3, 78, 20, 1);
    assert(barra != NULL);
    box(barra, 0, 0);
    botones(barra, highlight);
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
    ficha_medica_fields[6] = new_field(1, 20, 7, 1, 0, 0);
    ficha_medica_fields[7] = new_field(1, 40, 7, 21, 0, 0);
    ficha_medica_fields[8] = new_field(1, 20, 9, 1, 0, 0);
    ficha_medica_fields[9] = new_field(1, 40, 9, 21, 0, 0);
    ficha_medica_fields[10] = new_field(1, 20, 11, 1, 0, 0);
    ficha_medica_fields[11] = new_field(1, 40, 11, 21, 0, 0);
    ficha_medica_fields[12] = new_field(1, 20, 13, 1, 0, 0);
    ficha_medica_fields[13] = new_field(1, 40, 13, 21, 0, 0);
    ficha_medica_fields[14] = new_field(1, 20, 15, 1, 0, 0);
    ficha_medica_fields[15] = new_field(1, 40, 15, 21, 0, 0);
    
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
           ficha_medica_fields[15] != NULL);
    
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
    set_field_buffer(ficha_medica_fields[14], 0, "Donacion de Organos");
    set_field_buffer(ficha_medica_fields[15], 0, "");
    
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
    
    set_field_back(ficha_medica_fields[1], A_UNDERLINE);
    set_field_back(ficha_medica_fields[3], A_UNDERLINE);
    set_field_back(ficha_medica_fields[5], A_UNDERLINE);
    set_field_back(ficha_medica_fields[7], A_UNDERLINE);
    set_field_back(ficha_medica_fields[9], A_UNDERLINE);
    set_field_back(ficha_medica_fields[11], A_UNDERLINE);
    set_field_back(ficha_medica_fields[13], A_UNDERLINE);
    set_field_back(ficha_medica_fields[15], A_UNDERLINE);
    
    ficha_medica_form = new_form(ficha_medica_fields);
    assert(ficha_medica_form != NULL);
    set_form_win(ficha_medica_form, ficha_medica);
    set_form_sub(ficha_medica_form, derwin(ficha_medica, 18, 76, 1, 1));
    post_form(ficha_medica_form);
    
    refresh();
    wrefresh(ficha_medica_body);
    wrefresh(ficha_medica);
    
    
    char new_fields[400];
    
    ifstream fm_read;
    fm_read.open("ficha_medica.txt");
    
    //fm_read >> new_fields;
    //set_field_buffer(ficha_medica_fields[1], 0, new_fields);
    
    for (int i = 1; i < 17; i = i + 2) {
        fm_read >> new_fields;
        set_field_buffer(ficha_medica_fields[i], 0, new_fields);
    }
    
    
    fm_read.close();
    
    while ((ch = getch()) != KEY_F(12))
        driver(ch);
    
    
    
    /*unpost_form(ficha_medica_form);
    free_form(ficha_medica_form);
    for (int i = 0; ficha_medica_fields[i]; i++)
    {
        free_field(ficha_medica_fields[i]);
    }
    delwin(ficha_medica);
    delwin(ficha_medica_body);*/
}





//----------- ficha_medica_form pg. 2
void form2 (int g)
{
    int highlight = 1;
    
    wrefresh(ficha_medica_2);
    clear();
    refresh();
    ficha_medica_body_2 = newwin(24, 80, 0, 0);
    assert(ficha_medica_body_2 != NULL);
    box(ficha_medica_body_2, 0, 0);
    ficha_medica_2 = derwin(ficha_medica_body_2, 16, 78, 3, 1);
    assert(ficha_medica_2 != NULL);
    box(ficha_medica_2, 0, 0);
    barra_2 = derwin(ficha_medica_body_2, 3, 78, 20, 1);
    assert(barra_2 != NULL);
    box(barra_2, 0, 0);
    botones_2(barra_2, highlight);
    mvwprintw(ficha_medica_body_2, 1, 2, "Ficha Médica");
    
    ficha_medica_fields_2[0] = new_field(1, 20, 0, 1, 0, 0);
    ficha_medica_fields_2[1] = new_field(1, 40, 0, 21, 0, 0);
    ficha_medica_fields_2[2] = new_field(1, 20, 2, 1, 0, 0);
    ficha_medica_fields_2[3] = new_field(1, 40, 2, 21, 0, 0);
    ficha_medica_fields_2[4] = new_field(1, 40, 7, 1, 0, 0);
    ficha_medica_fields_2[5] = new_field(1, 40, 9, 1, 0, 0);
    ficha_medica_fields_2[6] = new_field(1, 20, 9, 21, 0, 0);
    ficha_medica_fields_2[7] = new_field(1, 40, 11, 1, 0, 0);
    ficha_medica_fields_2[8] = new_field(1, 20, 11, 21, 0, 0);
    
    assert(ficha_medica_fields_2[0] != NULL &&
           ficha_medica_fields_2[1] != NULL &&
           ficha_medica_fields_2[2] != NULL &&
           ficha_medica_fields_2[3] != NULL &&
           ficha_medica_fields_2[4] != NULL &&
           ficha_medica_fields_2[5] != NULL &&
           ficha_medica_fields_2[6] != NULL &&
           ficha_medica_fields_2[7] != NULL &&
           ficha_medica_fields_2[8] != NULL);
    
    set_field_buffer(ficha_medica_fields_2[0], 0, "Peso");
    set_field_buffer(ficha_medica_fields_2[1], 0, "");
    set_field_buffer(ficha_medica_fields_2[2], 0, "Estatura");
    set_field_buffer(ficha_medica_fields_2[3], 0, "");
    set_field_buffer(ficha_medica_fields_2[4], 0, "Contacto de emergencia:");
    set_field_buffer(ficha_medica_fields_2[5], 0, "Nombres");
    set_field_buffer(ficha_medica_fields_2[6], 0, "");
    set_field_buffer(ficha_medica_fields_2[7], 0, "Numero");
    set_field_buffer(ficha_medica_fields_2[8], 0, "");
    
    set_field_opts(ficha_medica_fields_2[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields_2[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields_2[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields_2[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields_2[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields_2[5], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields_2[6], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(ficha_medica_fields_2[7], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(ficha_medica_fields_2[8], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    
    set_field_back(ficha_medica_fields_2[1], A_UNDERLINE);
    set_field_back(ficha_medica_fields_2[3], A_UNDERLINE);
    set_field_back(ficha_medica_fields_2[6], A_UNDERLINE);
    set_field_back(ficha_medica_fields_2[8], A_UNDERLINE);
    
    ficha_medica_form_2 = new_form(ficha_medica_fields_2);
    assert(ficha_medica_form_2 != NULL);
    set_form_win(ficha_medica_form_2, ficha_medica_2);
    set_form_sub(ficha_medica_form_2, derwin(ficha_medica_2, 18, 76, 1, 1));
    post_form(ficha_medica_form_2);
    
    refresh();
    wrefresh(ficha_medica_body_2);
    wrefresh(ficha_medica_2);
    
    char new_fields[100];
    
    ifstream fm_read;
    fm_read.open("ficha_medica2.txt");
    
    fm_read >> new_fields;
    set_field_buffer(ficha_medica_fields_2[1], 0, new_fields);
    fm_read >> new_fields;
    set_field_buffer(ficha_medica_fields_2[3], 0, new_fields);
    fm_read >> new_fields;
    set_field_buffer(ficha_medica_fields_2[6], 0, new_fields);
    fm_read >> new_fields;
    set_field_buffer(ficha_medica_fields_2[8], 0, new_fields);
    
    fm_read.close();
    
    while ((g = getch()))
        driver_2(g);
    
    unpost_form(ficha_medica_form_2);
    free_form(ficha_medica_form_2);
    for (int i = 0; ficha_medica_fields_2[i]; i++)
    {
        free_field(ficha_medica_fields_2[i]);
    }
    delwin(ficha_medica_2);
    delwin(ficha_medica_body_2);
}


//----------- lab_form pg. 1
void form1lab (int h)
{
    int ch;
    int highlight = 1;
    
    clear();
    refresh();
    lab_body = newwin(24, 80, 0, 0);
    assert(lab_body != NULL);
    box(lab_body, 0, 0);
    lab = derwin(lab_body, 16, 78, 3, 1);
    assert(lab != NULL);
    box(lab, 0, 0);
    barra = derwin(lab_body, 3, 78, 20, 1);
    assert(barra != NULL);
    box(barra, 0, 0);
    botones(barra, highlight);
    refresh();
    mvwprintw(lab_body, 1, 2, "LABORATORIO");
    
    
    //--------- pag 1
    // FIELD *new_field(int height, int width, int toprow, int leftcol, int offscreen, int nbuffers);
    lab_fields[0] = new_field(1, 20, 0, 1, 0, 0);
    lab_fields[1] = new_field(1, 40, 0, 21, 0, 0);
    lab_fields[2] = new_field(1, 20, 2, 1, 0, 0);
    lab_fields[3] = new_field(1, 40, 2, 21, 0, 0);
    lab_fields[4] = new_field(2, 20, 4, 1, 0, 0);
    lab_fields[5] = new_field(1, 40, 4, 21, 0, 0);
    lab_fields[6] = new_field(1, 20, 7, 1, 0, 0);
    lab_fields[7] = new_field(1, 40, 7, 21, 0, 0);
    lab_fields[8] = new_field(1, 20, 9, 1, 0, 0);
    lab_fields[9] = new_field(1, 40, 9, 21, 0, 0);
    lab_fields[10] = new_field(1, 20, 11, 1, 0, 0);
    lab_fields[11] = new_field(1, 40, 11, 21, 0, 0);
    lab_fields[12] = new_field(1, 20, 13, 1, 0, 0);
    lab_fields[13] = new_field(1, 40, 13, 21, 0, 0);
    lab_fields[14] = new_field(1, 20, 15, 1, 0, 0);
    lab_fields[15] = new_field(1, 40, 15, 21, 0, 0);
    
    assert(lab_fields[0] != NULL &&
           lab_fields[1] != NULL &&
           lab_fields[2] != NULL &&
           lab_fields[3] != NULL &&
           lab_fields[4] != NULL &&
           lab_fields[5] != NULL &&
           lab_fields[6] != NULL &&
           lab_fields[7] != NULL &&
           lab_fields[8] != NULL &&
           lab_fields[9] != NULL &&
           lab_fields[10] != NULL &&
           lab_fields[11] != NULL &&
           lab_fields[12] != NULL &&
           lab_fields[13] != NULL &&
           lab_fields[14] != NULL &&
           lab_fields[15] != NULL);
    
    set_field_buffer(lab_fields[0], 0, "Resultado 1");
    set_field_buffer(lab_fields[1], 0, "");
    set_field_buffer(lab_fields[2], 0, "Resultado 2");
    set_field_buffer(lab_fields[3], 0, "");
    set_field_buffer(lab_fields[4], 0, "Pesultado 3");
    set_field_buffer(lab_fields[5], 0, "");
    set_field_buffer(lab_fields[6], 0, "Resultado 4");
    set_field_buffer(lab_fields[7], 0, "");
    set_field_buffer(lab_fields[8], 0, "Resultado 5");
    set_field_buffer(lab_fields[9], 0, "");
    set_field_buffer(lab_fields[10], 0, "Resultado 6");
    set_field_buffer(lab_fields[11], 0, "");
    set_field_buffer(lab_fields[12], 0, "Resultado 7");
    set_field_buffer(lab_fields[13], 0, "");
    set_field_buffer(lab_fields[14], 0, "Resultado 8");
    set_field_buffer(lab_fields[15], 0, "");
    
    set_field_opts(lab_fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(lab_fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(lab_fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(lab_fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(lab_fields[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(lab_fields[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(lab_fields[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(lab_fields[7], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(lab_fields[8], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(lab_fields[9], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(lab_fields[10], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(lab_fields[11], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(lab_fields[12], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(lab_fields[13], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(lab_fields[14], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(lab_fields[15], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    
    set_field_back(lab_fields[1], A_UNDERLINE);
    set_field_back(lab_fields[3], A_UNDERLINE);
    set_field_back(lab_fields[5], A_UNDERLINE);
    set_field_back(lab_fields[7], A_UNDERLINE);
    set_field_back(lab_fields[9], A_UNDERLINE);
    set_field_back(lab_fields[11], A_UNDERLINE);
    set_field_back(lab_fields[13], A_UNDERLINE);
    set_field_back(lab_fields[15], A_UNDERLINE);
    
    /*
     no entiendo que quieres hacer aca, pero si quieres un menu antes de que te pida los resultados tienes que
     inicializar la variable menu_winlab arriba:
     WINDOW *menu_winlab;
     */
     
    /*menu_winlab = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_winlab, TRUE);
    keypad(ficha_medica, TRUE);
    refresh();
    menulab(menu_winlab, highlight);*/
    
    lab_form = new_form(lab_fields);
    assert(lab_form != NULL);
    set_form_win(lab_form, lab);
    set_form_sub(lab_form, derwin(lab, 18, 76, 1, 1));
    post_form(lab_form);
    
    refresh();
    wrefresh(lab_body);
    wrefresh(lab);
    
    
    char new_fields[100];
    
    ifstream fm_read;
    fm_read.open("lab.txt");
    
    //fm_read >> new_fields;
    //set_field_buffer(ficha_medica_fields[1], 0, new_fields);
    
    for (int i = 1; lab_fields[i]; i = i + 2)
    {
        fm_read >> new_fields;
        set_field_buffer(lab_fields[i], 0, new_fields);
    }
    
    
    fm_read.close();
    
    while ((ch = getch()) != KEY_F(12))
        lab_driver_1(ch);
    
    unpost_form(lab_form);
    free_form(lab_form);
    free_field(lab_fields[0]);
    free_field(lab_fields[1]);
    free_field(lab_fields[2]);
    free_field(lab_fields[3]);
    delwin(lab);
    delwin(lab_body);
}


//-----------------------------------------------------
int main()
{
    WINDOW *menu_win;
    
    char mesg[]="Med Diary";
    int row,col;
    int highlight = 1;
    int choice = 0;
    int c, ch = 0;
    int a = 0;
    
    //------ inicio del programa
    initscr();
    clear();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS,NULL);
    
    
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
    keypad(ficha_medica, TRUE);
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
                //------- Ficha medica
                if (choice == 1)
                {
                    ficha_medica_form = new_form(ficha_medica_fields);
                    assert(ficha_medica_fields != NULL);
                    form1(ch);
                    break;
                }
                
                //------- Doctores
                if (choice == 2)
                {
                    wrefresh(doctores_win);
                    clear();
                    refresh();
                    doctores_win = newwin(24, 80, 0, 0);
                    assert(doctores_win != NULL);
                    
                    refresh();
                    mvwprintw(doctores_win, 1, 2, "Doctores");
                    box(doctores_win, 0, 0);
                    
                    
                    refresh();
                    wrefresh(doctores_win);
                    continue;
                }
                
                //------- Laboratorios
                if (choice == 3)
                {
                    form1lab(a);
                }
                
            default:
                refresh();
                break;
        }
        menu(menu_win, highlight);
        if(choice != 0)    /* User did a choice come out of the infinite loop */
            break;
    }

    clrtoeol();

    //------- corriendo programa
    refresh();
    getch();

    //--------------------------
    
    
    //------- fin de programa
    delwin(menu_win);
    endwin();
    //-----------------------
    
    return 0;
}
