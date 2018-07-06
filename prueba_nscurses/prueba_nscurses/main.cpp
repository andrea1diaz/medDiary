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

const char *choices[] = {
        "Ficha Medica",
        "Doctores",
        "Laboratorios",
        "Exit",
};

const char *nextt[] = {"GUARDAR(F1)  "
                 "SIGUIENTE(F2)  "
                 "MENU(F3)",
};

const char *nextt_2[] = {"GUARDAR(F1)  "
                         "ANTERIOR(F2)  "
                         "MENU(F3)",
};

const char *nextt_3[] = {"GUARDAR(F1)  "
    "MENU(F2)",
};

const char *choiceslab[] = {
        "Hematologia",
        "Bioquimica Sangre",
        "Bioquimica Orina",
        "Inmunologia",
        "Drogas",
        "Heces",
        "Atrás",
};

const char *docs[] = { "Lista de Doctores", "Agregar Doctor"
};


int n_choices = sizeof(choices) / sizeof(char *);

int n_nextt = sizeof(nextt) / sizeof(char *);
int n_nextt_2 = sizeof(nextt_2) / sizeof(char *);
int n_nextt_3 = sizeof(nextt_3) / sizeof(char *);

int n_docs = sizeof(docs) / sizeof(char *);

int n_choiceslab = sizeof(choiceslab) / sizeof(char *);
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

//------- menu docs -----------
void menu_docs (WINDOW *doctores_menu, int highlight)
{
    int x, y;

    x = 6;
    y = 4;
    box(doctores_menu, 0, 0);
    for(int i = 0; i < n_docs; ++i)
    {
        if(highlight == i + 1) /* High light the present choice */
        {
            wattron(doctores_menu, A_REVERSE);
            mvwprintw(doctores_menu, y, x, "%s", docs[i]);
            wattroff(doctores_menu, A_REVERSE);
        }
        else
            mvwprintw(doctores_menu, y, x, "%s", docs[i]);
        ++y;
    }
    wrefresh(doctores_menu);
}


//------- menu lab
void menulab(WINDOW *menu_winlab, int highlightlab)
{
    int x, y;
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;
    x = 6;
    y = 1;
    box(menu_winlab, 0, 0);
    for (int i = 0; i < n_choiceslab; ++i) {
        if (highlightlab == i + 1) /* High light the present choice */
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
        if(highlight == i + 1)
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

    x = 39;
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
void botones_3 (WINDOW *barra, int highlight)
{
    int x, y;
    
    x = 53;
    y = 1;
    box(barra, 0, 0);
    for(int i = 0; i < n_nextt_3; ++i)
    {
        if(highlight == i + 1) /* High light the present choice */
        {
            //wattron(barra, A_REVERSE);
            mvwprintw(barra, y, x, "%s", nextt_3[i]);
            //wattroff(barra, A_REVERSE);
        }
        else
            mvwprintw(barra, y, x, "%s", nextt_3[i]);
        ++y;
    }
    wrefresh(barra);
}


//--------- intro. de variables -------
//--------- variables de la ficha medica
static FORM *ficha_medica_form;
static FORM *ficha_medica_form_2;
static WINDOW *ficha_medica, *ficha_medica_body, *ficha_medica_2, *ficha_medica_body_2, *barra, *barra_2;
static FIELD *ficha_medica_fields[16], *ficha_medica_fields_2[9];

//--------- variables doctores -------------------
static WINDOW *doctores, *doctores_2;
static WINDOW *doctores_menu, *doctores_files_body, *doctores_files_body_2; //*doctores_files;
static FORM *doctores_form, *doctores_form_2;
static FIELD *doctores_fields[8], *doctores_fields_2[8];

//--------- variables laboratorio ----------------
static FORM *hem_form;
static FORM *hem_form_2;
static WINDOW *hem, *hem_body, *hem_2, *hem_body_2;
static FIELD *hem_fields[16], *hem_fields_2[9];

//--------- variables laboratorio2 ----------------
static FORM *sangre_form;
static FORM *sangre_form_2;
static WINDOW *sangre, *sangre_body, *sangre_2, *sangre_body_2;
static FIELD *sangre_fields[16], *sangre_fields_2[9];

//--------- variables laboratorio3 ----------------
static FORM *orina_form;
static FORM *orina_form_2;
static WINDOW *orina, *orina_body, *orina_2, *orina_body_2;
static FIELD *orina_fields[16], *orina_fields_2[9];

//--------- variables laboratorio4 ----------------
static FORM *inmu_form;
static FORM *inmu_form_2;
static WINDOW *inmu, *inmu_body, *inmu_2, *inmu_body_2;
static FIELD *inmu_fields[16], *inmu_fields_2[9];

//--------- variables laboratorio5 ----------------
static FORM *drugs_form;
static FORM *drugs_form_2;
static WINDOW *drugs, *drugs_body, *drugs_2, *drugs_body_2;
static FIELD *drugs_fields[16], *drugs_fields_2[9];

//--------- variables laboratorio6 ----------------
static FORM *heces_form;
static FORM *heces_form_2;
static WINDOW *heces, *heces_body, *heces_2, *heces_body_2;
static FIELD *heces_fields[16], *heces_fields_2[9];




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
void doctores_files_2(int g);
static void driver_docs(int ch)
{
    int g = 0;

    switch (ch)
    {
        case KEY_F(1):
        {
            ofstream fm_file;
            //fm_file.open("ficha_medica2.txt", ios::out);
            fm_file.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/doctores/doc1.txt", ios::out);
            if (fm_file.is_open())
            {
                for (int i = 1; doctores_fields[i]; i = i + 2)
                {
                    fm_file << trim_whitespaces(field_buffer(doctores_fields[i], 0));
                    fm_file << "\n";
                }
            }
            break;
        }

        case KEY_F(2):
        {
            doctores_form_2 = new_form(doctores_fields_2);
            assert(doctores_fields_2 != NULL);
            doctores_files_2(g);
            break;
        }

        case KEY_F(3):
        {
            doctores_form = new_form(doctores_fields);
            assert(doctores_fields != NULL);

            main();
            break;
        }

        case KEY_DOWN:
            form_driver(doctores_form, REQ_NEXT_FIELD);
            form_driver(doctores_form, REQ_END_LINE);
            break;

        case KEY_UP:
            form_driver(doctores_form, REQ_PREV_FIELD);
            form_driver(doctores_form, REQ_END_LINE);
            break;

        case KEY_LEFT:
            form_driver(doctores_form, REQ_PREV_CHAR);
            break;

        case KEY_RIGHT:
            form_driver(doctores_form, REQ_NEXT_CHAR);
            break;

        case 127:
            form_driver(doctores_form, REQ_DEL_PREV);
            break;

        case KEY_DC:
            form_driver(doctores_form, REQ_DEL_CHAR);
            break;

        default:
            form_driver(doctores_form, ch);
            break;
    }


    wrefresh(doctores);
}

static void driver_2(int f)
{
    int ch = 0;
    switch (f)
    {
        case KEY_F(1):
        {
            ofstream fm_file;
            //fm_file.open("ficha_medica2.txt", ios::out);
            fm_file.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/files/ficha_medica2.txt", ios::out);
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

void doctores_win1(int g);
static void driver_docs2(int ch)
{
    int g = 0;

    switch (ch)
    {
        case KEY_F(1):
        {
            ofstream fm_file;
            //fm_file.open("ficha_medica2.txt", ios::out);
            fm_file.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/doctores/doc2.txt", ios::out);
            if (fm_file.is_open())
            {
                for (int i = 1; doctores_fields_2[i]; i = i + 2)
                {
                    fm_file << trim_whitespaces(field_buffer(doctores_fields_2[i], 0));
                    fm_file << "\n";
                }
            }
            break;
        }

        case KEY_F(2):
        {
            doctores_form = new_form(doctores_fields);
            assert(ficha_medica_fields_2 != NULL);
            doctores_win1(g);
            break;
        }

        case KEY_F(3):
        {
            doctores_form = new_form(doctores_fields);
            assert(doctores_fields != NULL);

            main();
            break;
        }

        case KEY_DOWN:
            form_driver(doctores_form_2, REQ_NEXT_FIELD);
            form_driver(doctores_form_2, REQ_END_LINE);
            break;

        case KEY_UP:
            form_driver(doctores_form_2, REQ_PREV_FIELD);
            form_driver(doctores_form_2, REQ_END_LINE);
            break;

        case KEY_LEFT:
            form_driver(doctores_form_2, REQ_PREV_CHAR);
            break;

        case KEY_RIGHT:
            form_driver(doctores_form_2, REQ_NEXT_CHAR);
            break;

        case 127:
            form_driver(doctores_form_2, REQ_DEL_PREV);
            break;

        case KEY_DC:
            form_driver(doctores_form_2, REQ_DEL_CHAR);
            break;

        default:
            form_driver(doctores_form_2, ch);
            break;
    }


    wrefresh(doctores_2);
}

static void hem_driver_1(int f)
{
    switch (f)
    {
        case KEY_F(1):
        {
            fstream fm_file;
            fm_file.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Hematologia.txt", ios::out);
            if (fm_file.is_open())
            {
                /*fm_file << trim_whitespaces(field_buffer(lab_fields[1],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[3],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[6],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[8],0)) << "\n";*/
                for (int i = 1; hem_fields[i]; i = i + 2)
                {
                    fm_file << trim_whitespaces(field_buffer(hem_fields[i], 0));
                    fm_file << "\n";
                }
                fm_file.close();
            }
            break;
        }

        case KEY_F(2):
        {
            hem_form = new_form(hem_fields);
            assert(hem_fields != NULL);
            main();
            break;
        }

        case KEY_DOWN:
            form_driver(hem_form, REQ_NEXT_FIELD);
            form_driver(hem_form, REQ_END_LINE);
            break;

        case KEY_UP:
            form_driver(hem_form, REQ_PREV_FIELD);
            form_driver(hem_form, REQ_END_LINE);
            break;

        case KEY_LEFT:
            form_driver(hem_form, REQ_PREV_CHAR);
            break;

        case KEY_RIGHT:
            form_driver(hem_form, REQ_NEXT_CHAR);
            break;

        case 127:
            form_driver(hem_form, REQ_DEL_PREV);
            break;

            // Delete the char under the cursor
        case KEY_DC:
            form_driver(hem_form, REQ_DEL_CHAR);
            break;

        default:
            form_driver(hem_form, f);
            break;
    }

    wrefresh(hem);
}

static void sangre_driver_1(int f)
{
    switch (f)
    {
        case KEY_F(1):
        {
            fstream fm_file;
            fm_file.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Sangre.txt", ios::out);
            if (fm_file.is_open())
            {
                /*fm_file << trim_whitespaces(field_buffer(lab_fields[1],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[3],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[6],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[8],0)) << "\n";*/
                for (int i = 1; sangre_fields[i]; i = i + 2)
                {
                    fm_file << trim_whitespaces(field_buffer(sangre_fields[i], 0));
                    fm_file << "\n";
                }
                fm_file.close();
            }
            break;
        }

        case KEY_F(2):
        {
            sangre_form = new_form(sangre_fields);
            assert(sangre_fields != NULL);
            main();
            break;
        }

        case KEY_DOWN:
            form_driver(sangre_form, REQ_NEXT_FIELD);
            form_driver(sangre_form, REQ_END_LINE);
            break;

        case KEY_UP:
            form_driver(sangre_form, REQ_PREV_FIELD);
            form_driver(sangre_form, REQ_END_LINE);
            break;

        case KEY_LEFT:
            form_driver(sangre_form, REQ_PREV_CHAR);
            break;

        case KEY_RIGHT:
            form_driver(sangre_form, REQ_NEXT_CHAR);
            break;

        case 127:
            form_driver(sangre_form, REQ_DEL_PREV);
            break;

        case KEY_DC:
            form_driver(sangre_form, REQ_DEL_CHAR);
            break;

        default:
            form_driver(sangre_form, f);
            break;
    }

    wrefresh(sangre);
}

static void orina_driver_1(int f)
{
    switch (f)
    {
        case KEY_F(1):
        {
            fstream fm_file;
            fm_file.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Orina.txt", ios::out);
            if (fm_file.is_open())
            {
                /*fm_file << trim_whitespaces(field_buffer(lab_fields[1],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[3],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[6],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[8],0)) << "\n";*/
                for (int i = 1; orina_fields[i]; i = i + 2)
                {
                    fm_file << trim_whitespaces(field_buffer(orina_fields[i], 0));
                    fm_file << "\n";
                }
                fm_file.close();
            }
            break;
        }

        case KEY_F(2):
        {
            orina_form = new_form(orina_fields);
            assert(orina_fields != NULL);
            main();
            break;
        }

        case KEY_DOWN:
            form_driver(orina_form, REQ_NEXT_FIELD);
            form_driver(orina_form, REQ_END_LINE);
            break;

        case KEY_UP:
            form_driver(orina_form, REQ_PREV_FIELD);
            form_driver(orina_form, REQ_END_LINE);
            break;

        case KEY_LEFT:
            form_driver(orina_form, REQ_PREV_CHAR);
            break;

        case KEY_RIGHT:
            form_driver(orina_form, REQ_NEXT_CHAR);
            break;

        case 127:
            form_driver(orina_form, REQ_DEL_PREV);
            break;
            
        case KEY_DC:
            form_driver(orina_form, REQ_DEL_CHAR);
            break;

        default:
            form_driver(orina_form, f);
            break;
    }

    wrefresh(orina);
}

static void inmu_driver_1(int f)
{
    switch (f)
    {
        case KEY_F(1):
        {
            fstream fm_file;
            fm_file.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Inmunologia.txt", ios::out);
            if (fm_file.is_open())
            {
                /*fm_file << trim_whitespaces(field_buffer(lab_fields[1],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[3],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[6],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[8],0)) << "\n";*/
                for (int i = 1; inmu_fields[i]; i = i + 2)
                {
                    fm_file << trim_whitespaces(field_buffer(inmu_fields[i], 0));
                    fm_file << "\n";
                }
                fm_file.close();
            }
            break;
        }

        case KEY_F(2):
        {
            inmu_form = new_form(inmu_fields);
            assert(inmu_fields != NULL);
            main();
            break;
        }

        case KEY_DOWN:
            form_driver(inmu_form, REQ_NEXT_FIELD);
            form_driver(inmu_form, REQ_END_LINE);
            break;

        case KEY_UP:
            form_driver(inmu_form, REQ_PREV_FIELD);
            form_driver(inmu_form, REQ_END_LINE);
            break;

        case KEY_LEFT:
            form_driver(inmu_form, REQ_PREV_CHAR);
            break;

        case KEY_RIGHT:
            form_driver(inmu_form, REQ_NEXT_CHAR);
            break;

        case 127:
            form_driver(inmu_form, REQ_DEL_PREV);
            break;

        case KEY_DC:
            form_driver(inmu_form, REQ_DEL_CHAR);
            break;

        default:
            form_driver(inmu_form, f);
            break;
    }

    wrefresh(inmu);
}

static void drugs_driver_1(int f)
{
    switch (f)
    {
        case KEY_F(1):
        {
            fstream fm_file;
            fm_file.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Drogas.txt", ios::out);
            if (fm_file.is_open())
            {
                /*fm_file << trim_whitespaces(field_buffer(lab_fields[1],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[3],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[6],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[8],0)) << "\n";*/
                for (int i = 1; drugs_fields[i]; i = i + 2)
                {
                    fm_file << trim_whitespaces(field_buffer(drugs_fields[i], 0));
                    fm_file << "\n";
                }
                fm_file.close();
            }
            break;
        }

        case KEY_F(2):
        {
            drugs_form = new_form(drugs_fields);
            assert(drugs_fields != NULL);
            main();
            break;
        }

        case KEY_DOWN:
            form_driver(drugs_form, REQ_NEXT_FIELD);
            form_driver(drugs_form, REQ_END_LINE);
            break;

        case KEY_UP:
            form_driver(drugs_form, REQ_PREV_FIELD);
            form_driver(drugs_form, REQ_END_LINE);
            break;

        case KEY_LEFT:
            form_driver(drugs_form, REQ_PREV_CHAR);
            break;

        case KEY_RIGHT:
            form_driver(drugs_form, REQ_NEXT_CHAR);
            break;

        case 127:
            form_driver(drugs_form, REQ_DEL_PREV);
            break;

        case KEY_DC:
            form_driver(drugs_form, REQ_DEL_CHAR);
            break;

        default:
            form_driver(drugs_form, f);
            break;
    }

    wrefresh(drugs);
}

static void heces_driver_1(int f)
{
    switch (f)
    {
        case KEY_F(1):
        {
            fstream fm_file;
            fm_file.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Heces.txt", ios::out);
            if (fm_file.is_open())
            {
                /*fm_file << trim_whitespaces(field_buffer(lab_fields[1],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[3],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[6],0)) << "\n";
                fm_file << trim_whitespaces(field_buffer(lab_fields[8],0)) << "\n";*/
                for (int i = 1; heces_fields[i]; i = i + 2)
                {
                    fm_file << trim_whitespaces(field_buffer(heces_fields[i], 0));
                    fm_file << "\n";
                }
                fm_file.close();
            }
            break;
        }

        case KEY_F(2):
        {
            heces_form = new_form(heces_fields);
            assert(heces_fields != NULL);
            main();
            break;
        }

        case KEY_DOWN:
            form_driver(heces_form, REQ_NEXT_FIELD);
            form_driver(heces_form, REQ_END_LINE);
            break;

        case KEY_UP:
            form_driver(heces_form, REQ_PREV_FIELD);
            form_driver(heces_form, REQ_END_LINE);
            break;

        case KEY_LEFT:
            form_driver(heces_form, REQ_PREV_CHAR);
            break;

        case KEY_RIGHT:
            form_driver(heces_form, REQ_NEXT_CHAR);
            break;

        case 127:
            form_driver(heces_form, REQ_DEL_PREV);
            break;

        case KEY_DC:
            form_driver(heces_form, REQ_DEL_CHAR);
            break;

        default:
            form_driver(heces_form, f);
            break;
    }

    wrefresh(heces);
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
    /**
    int choicelab;
    highlight = 0;

    for(int i = 0; i < n_docs; ++i) {
        if (highlight == i + 1)  High light the present choice
        {
            wattron(menulab, A_REVERSE);
            mvwprintw(doctores_menu, y, x, "%s", docs[i]);
            wattroff(doctores_menu, A_REVERSE);
        } else
            mvwprintw(doctores_menu, y, x, "%s", docs[i]);
        ++y;

        wrefresh(doctores_menu);
     **/
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
    fm_read.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/files/en.lproj/ficha_medica2.txt");

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

//----------- doctores pg. 1
void docs_files(int g);

void doctores_win1 (int g)
{
    //int c;
    int highlight = 1;
    int choice = 0;

    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;

    wrefresh(doctores);
    clear();
    refresh();

    doctores_files_body = newwin(24, 80, 0, 0);
    assert(doctores_files_body != NULL);
    box(doctores_files_body, 0, 0);
    //doctores_menu = derwin(doctores, HEIGHT, WIDTH, starty, startx);
    doctores = derwin(doctores_files_body, 16, 76, 3, 1);

    assert(doctores != NULL);
    barra = derwin(doctores_files_body, 3, 78, 20, 1);
    assert(barra != NULL);
    box(barra, 0, 0);
    botones(barra, highlight);
    refresh();
    mvwprintw(doctores_files_body, 1, 2, "Doctor");

    doctores_fields[0] = new_field(1, 20, 0, 1, 0, 0);
    doctores_fields[1] = new_field(1, 40, 0, 21, 0, 0);
    doctores_fields[2] = new_field(1, 20, 2, 1, 0, 0);
    doctores_fields[3] = new_field(1, 40, 2, 21, 0, 0);
    doctores_fields[4] = new_field(2, 20, 4, 1, 0, 0);
    doctores_fields[5] = new_field(1, 40, 4, 21, 0, 0);
    doctores_fields[6] = new_field(1, 20, 6, 1, 0, 0);
    doctores_fields[7] = new_field(1, 40, 6, 21, 0, 0);

    assert(doctores_fields[0] != NULL &&
           doctores_fields[1] != NULL &&
           doctores_fields[2] != NULL &&
           doctores_fields[3] != NULL &&
           doctores_fields[4] != NULL &&
           doctores_fields[5] != NULL &&
           doctores_fields[6] != NULL &&
           doctores_fields[7] != NULL);

    set_field_buffer(doctores_fields[0], 0, "Nombres");
    set_field_buffer(doctores_fields[1], 0, "");
    set_field_buffer(doctores_fields[2], 0, "Especialidad");
    set_field_buffer(doctores_fields[3], 0, "");
    set_field_buffer(doctores_fields[4], 0, "Clinica");
    set_field_buffer(doctores_fields[5], 0, "");
    set_field_buffer(doctores_fields[6], 0, "Telefono");
    set_field_buffer(doctores_fields[7], 0, "");

    set_field_opts(doctores_fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(doctores_fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(doctores_fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(doctores_fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(doctores_fields[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(doctores_fields[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(doctores_fields[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(doctores_fields[7], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(doctores_fields[1], A_UNDERLINE);
    set_field_back(doctores_fields[3], A_UNDERLINE);
    set_field_back(doctores_fields[5], A_UNDERLINE);
    set_field_back(doctores_fields[7], A_UNDERLINE);

    doctores_form = new_form(doctores_fields);
    assert(doctores_form != NULL);
    set_form_win(doctores_form, doctores);
    set_form_sub(doctores_form, derwin(doctores, 18, 76, 1, 1));
    post_form(doctores_form);

    refresh();
    wrefresh(doctores_files_body);
    wrefresh(doctores);

    char new_fields[100];

    ifstream fm_read;
    fm_read.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/doctores/doc1.txt");

    for (int i = 1; i < 17; i = i + 2) {
        fm_read >> new_fields;
        set_field_buffer(doctores_fields[i], 0, new_fields);
    }

    fm_read.close();

    while ((g = getch()))
        driver_docs(g);

    unpost_form(doctores_form);
    free_form(doctores_form);
    for (int i = 0; doctores_fields[i]; i++)
    {
        free_field(doctores_fields[i]);
    }
    delwin(doctores);
    delwin(doctores_files_body);



    keypad(doctores_menu, TRUE);
    refresh();
    menu_docs(doctores_menu, highlight);


    /*while(1)
    {    c = wgetch(doctores_menu);
        switch(c)
        {
            case KEY_UP:
                if(highlight == 1)
                {
                    highlight = n_docs;
                }

                else
                    --highlight;
                break;

            case KEY_DOWN:
                if(highlight == n_docs)
                    highlight = 1;
                else
                    ++highlight;
                break;

            case 10:
            {
                choice = highlight;
                if (choice == 1)
                {
                    docs_files();
                }
            }

            default:
                refresh();
                break;
        }
        menu_docs(doctores_menu, highlight);
        if(choice != 0)
            break;
    }*/
    mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, docs[choice - 1]);


}


//----------- doctores pg. 2
void doctores_files_2(int g)
{
    //int c;
    int highlight = 1;
    int choice = 0;

    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;

    wrefresh(doctores);
    clear();
    refresh();

    doctores_files_body_2 = newwin(24, 80, 0, 0);
    assert(doctores_files_body_2 != NULL);
    box(doctores_files_body_2, 0, 0);
    doctores_2 = derwin(doctores_files_body, 16, 76, 3, 1);

    assert(doctores_2 != NULL);
    barra_2 = derwin(doctores_files_body_2, 3, 78, 20, 1);
    assert(barra_2 != NULL);
    box(barra_2, 0, 0);
    botones_2(barra_2, highlight);
    refresh();
    mvwprintw(doctores_files_body_2, 1, 2, "Doctor");

    doctores_fields_2[0] = new_field(1, 20, 0, 1, 0, 0);
    doctores_fields_2[1] = new_field(1, 40, 0, 21, 0, 0);
    doctores_fields_2[2] = new_field(1, 20, 2, 1, 0, 0);
    doctores_fields_2[3] = new_field(1, 40, 2, 21, 0, 0);
    doctores_fields_2[4] = new_field(2, 20, 4, 1, 0, 0);
    doctores_fields_2[5] = new_field(1, 40, 4, 21, 0, 0);
    doctores_fields_2[6] = new_field(1, 20, 6, 1, 0, 0);
    doctores_fields_2[7] = new_field(1, 40, 6, 21, 0, 0);

    assert(doctores_fields_2[0] != NULL &&
           doctores_fields_2[1] != NULL &&
           doctores_fields_2[2] != NULL &&
           doctores_fields_2[3] != NULL &&
           doctores_fields_2[4] != NULL &&
           doctores_fields_2[5] != NULL &&
           doctores_fields_2[6] != NULL &&
           doctores_fields_2[7] != NULL);

    set_field_buffer(doctores_fields_2[0], 0, "Nombres");
    set_field_buffer(doctores_fields_2[1], 0, "");
    set_field_buffer(doctores_fields_2[2], 0, "Especialidad");
    set_field_buffer(doctores_fields_2[3], 0, "");
    set_field_buffer(doctores_fields_2[4], 0, "Clinica");
    set_field_buffer(doctores_fields_2[5], 0, "");
    set_field_buffer(doctores_fields_2[6], 0, "Telefono");
    set_field_buffer(doctores_fields_2[7], 0, "");

    set_field_opts(doctores_fields_2[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(doctores_fields_2[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(doctores_fields_2[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(doctores_fields_2[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(doctores_fields_2[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(doctores_fields_2[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(doctores_fields_2[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(doctores_fields_2[7], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(doctores_fields_2[1], A_UNDERLINE);
    set_field_back(doctores_fields_2[3], A_UNDERLINE);
    set_field_back(doctores_fields_2[5], A_UNDERLINE);
    set_field_back(doctores_fields_2[7], A_UNDERLINE);

    doctores_form_2 = new_form(doctores_fields_2);
    assert(doctores_form_2 != NULL);
    set_form_win(doctores_form_2, doctores_2);
    set_form_sub(doctores_form_2, derwin(doctores_2, 18, 76, 1, 1));
    post_form(doctores_form_2);

    refresh();
    wrefresh(doctores_files_body_2);
    wrefresh(doctores_2);

    char new_fields[100];

    ifstream fm_read;
    fm_read.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/doctores/doc2.txt");

    for (int i = 1; i < 17; i = i + 2) {
        fm_read >> new_fields;
        set_field_buffer(doctores_fields_2[i], 0, new_fields);
    }

    fm_read.close();

    while ((g = getch()))
        driver_docs2(g);

    unpost_form(doctores_form_2);
    free_form(doctores_form_2);
    for (int i = 0; doctores_fields_2[i]; i++)
    {
        free_field(doctores_fields_2[i]);
    }
    delwin(doctores_2);
    delwin(doctores_files_body_2);
}


//----------- lab_form pg. 1
void hematologia (int h)
{
    int ch;
    int highlight = 1;

    clear();
    refresh();
    hem_body = newwin(24, 80, 0, 0);
    assert(hem_body != NULL);
    box(hem_body, 0, 0);
    hem = derwin(hem_body, 16, 78, 3, 1);
    assert(hem != NULL);
    box(hem, 0, 0);
    barra = derwin(hem_body, 3, 78, 20, 1);
    assert(barra != NULL);
    box(barra, 0, 0);
    botones_3(barra, highlight);
    refresh();
    mvwprintw(hem_body, 1, 2, "RESULTADOS: PRUEBAS HEMATOLOGIA");


    //--------- pag 1
    // FIELD *new_field(int height, int width, int toprow, int leftcol, int offscreen, int nbuffers);
    hem_fields[0] = new_field(1, 20, 0, 1, 0, 0);
    hem_fields[1] = new_field(1, 40, 0, 21, 0, 0);
    hem_fields[2] = new_field(1, 20, 2, 1, 0, 0);
    hem_fields[3] = new_field(1, 40, 2, 21, 0, 0);
    hem_fields[4] = new_field(2, 20, 4, 1, 0, 0);
    hem_fields[5] = new_field(1, 40, 4, 21, 0, 0);
    hem_fields[6] = new_field(1, 20, 7, 1, 0, 0);
    hem_fields[7] = new_field(1, 40, 7, 21, 0, 0);
    hem_fields[8] = new_field(1, 20, 9, 1, 0, 0);
    hem_fields[9] = new_field(1, 40, 9, 21, 0, 0);
    hem_fields[10] = new_field(1, 20, 11, 1, 0, 0);
    hem_fields[11] = new_field(1, 40, 11, 21, 0, 0);
    hem_fields[12] = new_field(1, 20, 13, 1, 0, 0);
    hem_fields[13] = new_field(1, 40, 13, 21, 0, 0);
    hem_fields[14] = new_field(1, 20, 15, 1, 0, 0);
    hem_fields[15] = new_field(1, 40, 15, 21, 0, 0);

    assert(hem_fields[0] != NULL &&
           hem_fields[1] != NULL &&
           hem_fields[2] != NULL &&
           hem_fields[3] != NULL &&
           hem_fields[4] != NULL &&
           hem_fields[5] != NULL &&
           hem_fields[6] != NULL &&
           hem_fields[7] != NULL &&
           hem_fields[8] != NULL &&
           hem_fields[9] != NULL &&
           hem_fields[10] != NULL &&
           hem_fields[11] != NULL &&
           hem_fields[12] != NULL &&
           hem_fields[13] != NULL &&
           hem_fields[14] != NULL &&
           hem_fields[15] != NULL);

    set_field_buffer(hem_fields[0], 0, "ANTROMBINA:");
    set_field_buffer(hem_fields[1], 0, "");
    set_field_buffer(hem_fields[2], 0, "FERRITINA:");
    set_field_buffer(hem_fields[3], 0, "");
    set_field_buffer(hem_fields[4], 0, "FIBRINOGENO:");
    set_field_buffer(hem_fields[5], 0, "");
    set_field_buffer(hem_fields[6], 0, "PROTEINA C:");
    set_field_buffer(hem_fields[7], 0, "");
    set_field_buffer(hem_fields[8], 0, "PROTEINA S:");
    set_field_buffer(hem_fields[9], 0, "");
    set_field_buffer(hem_fields[10], 0, "RETICULOCITOS:");
    set_field_buffer(hem_fields[11], 0, "");
    set_field_buffer(hem_fields[12], 0, "PROTROMBINA:");
    set_field_buffer(hem_fields[13], 0, "");
    set_field_buffer(hem_fields[14], 0, "VITAMINA_B12:");
    set_field_buffer(hem_fields[15], 0, "");

    set_field_opts(hem_fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(hem_fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(hem_fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(hem_fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(hem_fields[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(hem_fields[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(hem_fields[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(hem_fields[7], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(hem_fields[8], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(hem_fields[9], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(hem_fields[10], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(hem_fields[11], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(hem_fields[12], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(hem_fields[13], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(hem_fields[14], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(hem_fields[15], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(hem_fields[1], A_UNDERLINE);
    set_field_back(hem_fields[3], A_UNDERLINE);
    set_field_back(hem_fields[5], A_UNDERLINE);
    set_field_back(hem_fields[7], A_UNDERLINE);
    set_field_back(hem_fields[9], A_UNDERLINE);
    set_field_back(hem_fields[11], A_UNDERLINE);
    set_field_back(hem_fields[13], A_UNDERLINE);
    set_field_back(hem_fields[15], A_UNDERLINE);


    hem_form = new_form(hem_fields);
    assert(hem_form != NULL);
    set_form_win(hem_form, hem);
    set_form_sub(hem_form, derwin(hem, 18, 76, 1, 1));
    post_form(hem_form);

    refresh();
    wrefresh(hem_body);
    wrefresh(hem);


    char new_fields[100];
    ifstream fm_read;
    fm_read.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Hematologia.txt");

    //fm_read >> new_fields;
    //set_field_buffer(ficha_medica_fields[1], 0, new_fields);

    for (int i = 1; hem_fields[i]; i = i + 2)
    {
        fm_read >> new_fields;
        set_field_buffer(hem_fields[i], 0, new_fields);
    }


    fm_read.close();

    while ((ch = getch()) != KEY_F(12))
        hem_driver_1(ch);

    unpost_form(hem_form);
    free_form(hem_form);
    free_field(hem_fields[0]);
    free_field(hem_fields[1]);
    free_field(hem_fields[2]);
    free_field(hem_fields[3]);
    delwin(hem);
    delwin(hem_body);
}
void bioquimica_sangre (int h)
{
    int ch;
    int highlight = 1;

    clear();
    refresh();
    sangre_body = newwin(24, 80, 0, 0);
    assert(sangre_body != NULL);
    box(sangre_body, 0, 0);
    sangre = derwin(sangre_body, 16, 78, 3, 1);
    assert(sangre != NULL);
    box(sangre, 0, 0);
    barra = derwin(sangre_body, 3, 78, 20, 1);
    assert(barra != NULL);
    box(barra, 0, 0);
    botones_3(barra, highlight);
    refresh();
    mvwprintw(sangre_body, 1, 2, "RESULTADOS: PRUEBAS DE SANGRE");


    //--------- pag 1
    // FIELD *new_field(int height, int width, int toprow, int leftcol, int offscreen, int nbuffers);
    sangre_fields[0] = new_field(1, 20, 0, 1, 0, 0);
    sangre_fields[1] = new_field(1, 40, 0, 21, 0, 0);
    sangre_fields[2] = new_field(1, 20, 2, 1, 0, 0);
    sangre_fields[3] = new_field(1, 40, 2, 21, 0, 0);
    sangre_fields[4] = new_field(2, 20, 4, 1, 0, 0);
    sangre_fields[5] = new_field(1, 40, 4, 21, 0, 0);
    sangre_fields[6] = new_field(1, 20, 7, 1, 0, 0);
    sangre_fields[7] = new_field(1, 40, 7, 21, 0, 0);
    sangre_fields[8] = new_field(1, 20, 9, 1, 0, 0);
    sangre_fields[9] = new_field(1, 40, 9, 21, 0, 0);
    sangre_fields[10] = new_field(1, 20, 11, 1, 0, 0);
    sangre_fields[11] = new_field(1, 40, 11, 21, 0, 0);
    sangre_fields[12] = new_field(1, 20, 13, 1, 0, 0);
    sangre_fields[13] = new_field(1, 40, 13, 21, 0, 0);
    sangre_fields[14] = new_field(1, 20, 15, 1, 0, 0);
    sangre_fields[15] = new_field(1, 40, 15, 21, 0, 0);

    assert(sangre_fields[0] != NULL &&
           sangre_fields[1] != NULL &&
           sangre_fields[2] != NULL &&
           sangre_fields[3] != NULL &&
           sangre_fields[4] != NULL &&
           sangre_fields[5] != NULL &&
           sangre_fields[6] != NULL &&
           sangre_fields[7] != NULL &&
           sangre_fields[8] != NULL &&
           sangre_fields[9] != NULL &&
           sangre_fields[10] != NULL &&
           sangre_fields[11] != NULL &&
           sangre_fields[12] != NULL &&
           sangre_fields[13] != NULL &&
           sangre_fields[14] != NULL &&
           sangre_fields[15] != NULL);

    set_field_buffer(sangre_fields[0], 0, "COLESTEROL TOTAL:");
    set_field_buffer(sangre_fields[1], 0, "");
    set_field_buffer(sangre_fields[2], 0, "COLESTEROL HDL:");
    set_field_buffer(sangre_fields[3], 0, "");
    set_field_buffer(sangre_fields[4], 0, "COLESTEROL LDL:");
    set_field_buffer(sangre_fields[5], 0, "");
    set_field_buffer(sangre_fields[6], 0, "TRIGLICERIDOS:");
    set_field_buffer(sangre_fields[7], 0, "");
    set_field_buffer(sangre_fields[8], 0, "GLUCOSA");
    set_field_buffer(sangre_fields[9], 0, "");
    set_field_buffer(sangre_fields[10], 0, "UREA:");
    set_field_buffer(sangre_fields[11], 0, "");
    set_field_buffer(sangre_fields[12], 0, "AMILASA:");
    set_field_buffer(sangre_fields[13], 0, "");
    set_field_buffer(sangre_fields[14], 0, "CKMB:");
    set_field_buffer(sangre_fields[15], 0, "");

    set_field_opts(sangre_fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(sangre_fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(sangre_fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(sangre_fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(sangre_fields[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(sangre_fields[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(sangre_fields[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(sangre_fields[7], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(sangre_fields[8], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(sangre_fields[9], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(sangre_fields[10], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(sangre_fields[11], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(sangre_fields[12], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(sangre_fields[13], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(sangre_fields[14], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(sangre_fields[15], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(sangre_fields[1], A_UNDERLINE);
    set_field_back(sangre_fields[3], A_UNDERLINE);
    set_field_back(sangre_fields[5], A_UNDERLINE);
    set_field_back(sangre_fields[7], A_UNDERLINE);
    set_field_back(sangre_fields[9], A_UNDERLINE);
    set_field_back(sangre_fields[11], A_UNDERLINE);
    set_field_back(sangre_fields[13], A_UNDERLINE);
    set_field_back(sangre_fields[15], A_UNDERLINE);


    sangre_form = new_form(sangre_fields);
    assert(sangre_form != NULL);
    set_form_win(sangre_form, sangre);
    set_form_sub(sangre_form, derwin(sangre, 18, 76, 1, 1));
    post_form(sangre_form);

    refresh();
    wrefresh(sangre_body);
    wrefresh(sangre);


    char new_fields[100];

    ifstream fm_read;
    fm_read.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Sangre.txt");

    //fm_read >> new_fields;
    //set_field_buffer(ficha_medica_fields[1], 0, new_fields);

    for (int i = 1; sangre_fields[i]; i = i + 2)
    {
        fm_read >> new_fields;
        set_field_buffer(sangre_fields[i], 0, new_fields);
    }


    fm_read.close();

    while ((ch = getch()) != KEY_F(12))
        sangre_driver_1(ch);

    unpost_form(sangre_form);
    free_form(sangre_form);
    free_field(sangre_fields[0]);
    free_field(sangre_fields[1]);
    free_field(sangre_fields[2]);
    free_field(sangre_fields[3]);
    delwin(sangre);
    delwin(sangre_body);
}
void bioquimica_orina (int h)
{
    int ch;
    int highlight = 1;

    clear();
    refresh();
    orina_body = newwin(24, 80, 0, 0);
    assert(orina_body != NULL);
    box(orina_body, 0, 0);
    orina = derwin(orina_body, 16, 78, 3, 1);
    assert(orina != NULL);
    box(orina, 0, 0);
    barra = derwin(orina_body, 3, 78, 20, 1);
    assert(barra != NULL);
    box(barra, 0, 0);
    botones_3(barra, highlight);
    refresh();
    mvwprintw(orina_body, 1, 2, "RESULTADOS: PRUEBAS DE ORINA");


    //--------- pag 1
    // FIELD *new_field(int height, int width, int toprow, int leftcol, int offscreen, int nbuffers);
    orina_fields[0] = new_field(1, 20, 0, 1, 0, 0);
    orina_fields[1] = new_field(1, 40, 0, 21, 0, 0);
    orina_fields[2] = new_field(1, 20, 2, 1, 0, 0);
    orina_fields[3] = new_field(1, 40, 2, 21, 0, 0);
    orina_fields[4] = new_field(2, 20, 4, 1, 0, 0);
    orina_fields[5] = new_field(1, 40, 4, 21, 0, 0);
    orina_fields[6] = new_field(1, 20, 7, 1, 0, 0);
    orina_fields[7] = new_field(1, 40, 7, 21, 0, 0);
    orina_fields[8] = new_field(1, 20, 9, 1, 0, 0);
    orina_fields[9] = new_field(1, 40, 9, 21, 0, 0);
    orina_fields[10] = new_field(1, 20, 11, 1, 0, 0);
    orina_fields[11] = new_field(1, 40, 11, 21, 0, 0);
    orina_fields[12] = new_field(1, 20, 13, 1, 0, 0);
    orina_fields[13] = new_field(1, 40, 13, 21, 0, 0);
    orina_fields[14] = new_field(1, 20, 15, 1, 0, 0);
    orina_fields[15] = new_field(1, 40, 15, 21, 0, 0);

    assert(orina_fields[0] != NULL &&
           orina_fields[1] != NULL &&
           orina_fields[2] != NULL &&
           orina_fields[3] != NULL &&
           orina_fields[4] != NULL &&
           orina_fields[5] != NULL &&
           orina_fields[6] != NULL &&
           orina_fields[7] != NULL &&
           orina_fields[8] != NULL &&
           orina_fields[9] != NULL &&
           orina_fields[10] != NULL &&
           orina_fields[11] != NULL &&
           orina_fields[12] != NULL &&
           orina_fields[13] != NULL &&
           orina_fields[14] != NULL &&
           orina_fields[15] != NULL);

    set_field_buffer(orina_fields[0], 0, "UREA:");
    set_field_buffer(orina_fields[1], 0, "");
    set_field_buffer(orina_fields[2], 0, "CREATININA:");
    set_field_buffer(orina_fields[3], 0, "");
    set_field_buffer(orina_fields[4], 0, "AMILASA:");
    set_field_buffer(orina_fields[5], 0, "");
    set_field_buffer(orina_fields[6], 0, "SODIO:");
    set_field_buffer(orina_fields[7], 0, "");
    set_field_buffer(orina_fields[8], 0, "CALCIO:");
    set_field_buffer(orina_fields[9], 0, "");
    set_field_buffer(orina_fields[10], 0, "CLORO:");
    set_field_buffer(orina_fields[11], 0, "");
    set_field_buffer(orina_fields[12], 0, "GLUCOSA_ORINA:");
    set_field_buffer(orina_fields[13], 0, "");
    set_field_buffer(orina_fields[14], 0, "ELECTROLITOS:");
    set_field_buffer(orina_fields[15], 0, "");

    set_field_opts(orina_fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(orina_fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(orina_fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(orina_fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(orina_fields[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(orina_fields[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(orina_fields[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(orina_fields[7], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(orina_fields[8], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(orina_fields[9], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(orina_fields[10], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(orina_fields[11], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(orina_fields[12], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(orina_fields[13], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(orina_fields[14], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(orina_fields[15], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(orina_fields[1], A_UNDERLINE);
    set_field_back(orina_fields[3], A_UNDERLINE);
    set_field_back(orina_fields[5], A_UNDERLINE);
    set_field_back(orina_fields[7], A_UNDERLINE);
    set_field_back(orina_fields[9], A_UNDERLINE);
    set_field_back(orina_fields[11], A_UNDERLINE);
    set_field_back(orina_fields[13], A_UNDERLINE);
    set_field_back(orina_fields[15], A_UNDERLINE);


    orina_form = new_form(orina_fields);
    assert(orina_form != NULL);
    set_form_win(orina_form, orina);
    set_form_sub(orina_form, derwin(orina, 18, 76, 1, 1));
    post_form(orina_form);

    refresh();
    wrefresh(orina_body);
    wrefresh(orina);


    char new_fields[100];

    ifstream fm_read;
    fm_read.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Orina.txt");

    //fm_read >> new_fields;
    //set_field_buffer(ficha_medica_fields[1], 0, new_fields);

    for (int i = 1; orina_fields[i]; i = i + 2)
    {
        fm_read >> new_fields;
        set_field_buffer(orina_fields[i], 0, new_fields);
    }


    fm_read.close();

    while ((ch = getch()) != KEY_F(12))
        orina_driver_1(ch);

    unpost_form(orina_form);
    free_form(orina_form);
    free_field(orina_fields[0]);
    free_field(orina_fields[1]);
    free_field(orina_fields[2]);
    free_field(orina_fields[3]);
    delwin(orina);
    delwin(orina_body);
}
void inmunologia(int h)
{
    int ch;
    int highlight = 1;

    clear();
    refresh();
    inmu_body = newwin(24, 80, 0, 0);
    assert(inmu_body != NULL);
    box(inmu_body, 0, 0);
    inmu = derwin(inmu_body, 16, 78, 3, 1);
    assert(inmu != NULL);
    box(inmu, 0, 0);
    barra = derwin(inmu_body, 3, 78, 20, 1);
    assert(barra != NULL);
    box(barra, 0, 0);
    botones_3(barra, highlight);
    refresh();
    mvwprintw(inmu_body, 1, 2, "RESULTADOS: PRUEBAS DE INMUNOLOGIA");


    //--------- pag 1
    // FIELD *new_field(int height, int width, int toprow, int leftcol, int offscreen, int nbuffers);
    inmu_fields[0] = new_field(1, 20, 0, 1, 0, 0);
    inmu_fields[1] = new_field(1, 40, 0, 21, 0, 0);
    inmu_fields[2] = new_field(1, 20, 2, 1, 0, 0);
    inmu_fields[3] = new_field(1, 40, 2, 21, 0, 0);
    inmu_fields[4] = new_field(2, 20, 4, 1, 0, 0);
    inmu_fields[5] = new_field(1, 40, 4, 21, 0, 0);
    inmu_fields[6] = new_field(1, 20, 7, 1, 0, 0);
    inmu_fields[7] = new_field(1, 40, 7, 21, 0, 0);
    inmu_fields[8] = new_field(1, 20, 9, 1, 0, 0);
    inmu_fields[9] = new_field(1, 40, 9, 21, 0, 0);
    inmu_fields[10] = new_field(1, 20, 11, 1, 0, 0);
    inmu_fields[11] = new_field(1, 40, 11, 21, 0, 0);
    inmu_fields[12] = new_field(1, 20, 13, 1, 0, 0);
    inmu_fields[13] = new_field(1, 40, 13, 21, 0, 0);
    inmu_fields[14] = new_field(1, 20, 15, 1, 0, 0);
    inmu_fields[15] = new_field(1, 40, 15, 21, 0, 0);

    assert(inmu_fields[0] != NULL &&
           inmu_fields[1] != NULL &&
           inmu_fields[2] != NULL &&
           inmu_fields[3] != NULL &&
           inmu_fields[4] != NULL &&
           inmu_fields[5] != NULL &&
           inmu_fields[6] != NULL &&
           inmu_fields[7] != NULL &&
           inmu_fields[8] != NULL &&
           inmu_fields[9] != NULL &&
           inmu_fields[10] != NULL &&
           inmu_fields[11] != NULL &&
           inmu_fields[12] != NULL &&
           inmu_fields[13] != NULL &&
           inmu_fields[14] != NULL &&
           inmu_fields[15] != NULL);

    set_field_buffer(inmu_fields[0], 0, "HERPES:");
    set_field_buffer(inmu_fields[1], 0, "");
    set_field_buffer(inmu_fields[2], 0, "RUBEOLA:");
    set_field_buffer(inmu_fields[3], 0, "");
    set_field_buffer(inmu_fields[4], 0, "SARAMPION:");
    set_field_buffer(inmu_fields[5], 0, "");
    set_field_buffer(inmu_fields[6], 0, "VARICELA:");
    set_field_buffer(inmu_fields[7], 0, "");
    set_field_buffer(inmu_fields[8], 0, "TOXOPLASMA:");
    set_field_buffer(inmu_fields[9], 0, "");
    set_field_buffer(inmu_fields[10], 0, "EPSTEIN:");
    set_field_buffer(inmu_fields[11], 0, "");
    set_field_buffer(inmu_fields[12], 0, "HELICOBACTER:");
    set_field_buffer(inmu_fields[13], 0, "");
    set_field_buffer(inmu_fields[14], 0, "VIH:");
    set_field_buffer(inmu_fields[15], 0, "");

    set_field_opts(inmu_fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(inmu_fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(inmu_fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(inmu_fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(inmu_fields[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(inmu_fields[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(inmu_fields[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(inmu_fields[7], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(inmu_fields[8], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(inmu_fields[9], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(inmu_fields[10], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(inmu_fields[11], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(inmu_fields[12], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(inmu_fields[13], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(inmu_fields[14], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(inmu_fields[15], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(inmu_fields[1], A_UNDERLINE);
    set_field_back(inmu_fields[3], A_UNDERLINE);
    set_field_back(inmu_fields[5], A_UNDERLINE);
    set_field_back(inmu_fields[7], A_UNDERLINE);
    set_field_back(inmu_fields[9], A_UNDERLINE);
    set_field_back(inmu_fields[11], A_UNDERLINE);
    set_field_back(inmu_fields[13], A_UNDERLINE);
    set_field_back(inmu_fields[15], A_UNDERLINE);



    inmu_form = new_form(inmu_fields);
    assert(inmu_form != NULL);
    set_form_win(inmu_form, inmu);
    set_form_sub(inmu_form, derwin(inmu, 18, 76, 1, 1));
    post_form(inmu_form);

    refresh();
    wrefresh(inmu_body);
    wrefresh(inmu);


    char new_fields[100];

    ifstream fm_read;
    fm_read.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Inmunologia.txt");

    //fm_read >> new_fields;
    //set_field_buffer(ficha_medica_fields[1], 0, new_fields);

    for (int i = 1; inmu_fields[i]; i = i + 2)
    {
        fm_read >> new_fields;
        set_field_buffer(inmu_fields[i], 0, new_fields);
    }


    fm_read.close();

    while ((ch = getch()) != KEY_F(12))
        inmu_driver_1(ch);

    unpost_form(inmu_form);
    free_form(inmu_form);
    free_field(inmu_fields[0]);
    free_field(inmu_fields[1]);
    free_field(inmu_fields[2]);
    free_field(inmu_fields[3]);
    delwin(inmu);
    delwin(inmu_body);
}
void drogas (int h)
{
    int ch;
    int highlight = 1;

    clear();
    refresh();
    drugs_body = newwin(24, 80, 0, 0);
    assert(drugs_body != NULL);
    box(drugs_body, 0, 0);
    drugs = derwin(drugs_body, 16, 78, 3, 1);
    assert(drugs != NULL);
    box(drugs, 0, 0);
    barra = derwin(drugs_body, 3, 78, 20, 1);
    assert(barra != NULL);
    box(barra, 0, 0);
    botones_3(barra, highlight);
    refresh();
    mvwprintw(drugs_body, 1, 2, "RESULTADOS: PRUEBAS DE DROGAS");


    //--------- pag 1
    // FIELD *new_field(int height, int width, int toprow, int leftcol, int offscreen, int nbuffers);
    drugs_fields[0] = new_field(1, 20, 0, 1, 0, 0);
    drugs_fields[1] = new_field(1, 40, 0, 21, 0, 0);
    drugs_fields[2] = new_field(1, 20, 2, 1, 0, 0);
    drugs_fields[3] = new_field(1, 40, 2, 21, 0, 0);
    drugs_fields[4] = new_field(2, 20, 4, 1, 0, 0);
    drugs_fields[5] = new_field(1, 40, 4, 21, 0, 0);
    drugs_fields[6] = new_field(1, 20, 7, 1, 0, 0);
    drugs_fields[7] = new_field(1, 40, 7, 21, 0, 0);
    drugs_fields[8] = new_field(1, 20, 9, 1, 0, 0);
    drugs_fields[9] = new_field(1, 40, 9, 21, 0, 0);
    drugs_fields[10] = new_field(1, 20, 11, 1, 0, 0);
    drugs_fields[11] = new_field(1, 40, 11, 21, 0, 0);
    drugs_fields[12] = new_field(1, 20, 13, 1, 0, 0);
    drugs_fields[13] = new_field(1, 40, 13, 21, 0, 0);
    drugs_fields[14] = new_field(1, 20, 15, 1, 0, 0);
    drugs_fields[15] = new_field(1, 40, 15, 21, 0, 0);

    assert(drugs_fields[0] != NULL &&
           drugs_fields[1] != NULL &&
           drugs_fields[2] != NULL &&
           drugs_fields[3] != NULL &&
           drugs_fields[4] != NULL &&
           drugs_fields[5] != NULL &&
           drugs_fields[6] != NULL &&
           drugs_fields[7] != NULL &&
           drugs_fields[8] != NULL &&
           drugs_fields[9] != NULL &&
           drugs_fields[10] != NULL &&
           drugs_fields[11] != NULL &&
           drugs_fields[12] != NULL &&
           drugs_fields[13] != NULL &&
           drugs_fields[14] != NULL &&
           drugs_fields[15] != NULL);

    set_field_buffer(drugs_fields[0], 0, "ANFETAMINAS:");
    set_field_buffer(drugs_fields[1], 0, "");
    set_field_buffer(drugs_fields[2], 0, "DIAZEPAN");
    set_field_buffer(drugs_fields[3], 0, "");
    set_field_buffer(drugs_fields[4], 0, "LITIO:");
    set_field_buffer(drugs_fields[5], 0, "");
    set_field_buffer(drugs_fields[6], 0, "EPAMIN:");
    set_field_buffer(drugs_fields[7], 0, "");
    set_field_buffer(drugs_fields[8], 0, "METANFETAMINAS:");
    set_field_buffer(drugs_fields[9], 0, "");
    set_field_buffer(drugs_fields[10], 0, "COCAINA:");
    set_field_buffer(drugs_fields[11], 0, "");
    set_field_buffer(drugs_fields[12], 0, "MARIHUANA:");
    set_field_buffer(drugs_fields[13], 0, "");
    set_field_buffer(drugs_fields[14], 0, "OPIACEOS:");
    set_field_buffer(drugs_fields[15], 0, "");

    set_field_opts(drugs_fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(drugs_fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(drugs_fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(drugs_fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(drugs_fields[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(drugs_fields[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(drugs_fields[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(drugs_fields[7], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(drugs_fields[8], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(drugs_fields[9], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(drugs_fields[10], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(drugs_fields[11], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(drugs_fields[12], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(drugs_fields[13], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(drugs_fields[14], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(drugs_fields[15], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(drugs_fields[1], A_UNDERLINE);
    set_field_back(drugs_fields[3], A_UNDERLINE);
    set_field_back(drugs_fields[5], A_UNDERLINE);
    set_field_back(drugs_fields[7], A_UNDERLINE);
    set_field_back(drugs_fields[9], A_UNDERLINE);
    set_field_back(drugs_fields[11], A_UNDERLINE);
    set_field_back(drugs_fields[13], A_UNDERLINE);
    set_field_back(drugs_fields[15], A_UNDERLINE);



    drugs_form = new_form(drugs_fields);
    assert(drugs_form != NULL);
    set_form_win(drugs_form, drugs);
    set_form_sub(drugs_form, derwin(drugs, 18, 76, 1, 1));
    post_form(drugs_form);

    refresh();
    wrefresh(drugs_body);
    wrefresh(drugs);


    char new_fields[100];

    ifstream fm_read;
    fm_read.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Drogas.txt");

    //fm_read >> new_fields;
    //set_field_buffer(ficha_medica_fields[1], 0, new_fields);

    for (int i = 1; drugs_fields[i]; i = i + 2)
    {
        fm_read >> new_fields;
        set_field_buffer(drugs_fields[i], 0, new_fields);
    }


    fm_read.close();

    while ((ch = getch()) != KEY_F(12))
        drugs_driver_1(ch);

    unpost_form(drugs_form);
    free_form(drugs_form);
    free_field(drugs_fields[0]);
    free_field(drugs_fields[1]);
    free_field(drugs_fields[2]);
    free_field(drugs_fields[3]);
    delwin(drugs);
    delwin(drugs_body);
}
void prueba_heces(int h)
{
    int ch;
    int highlight = 1;

    clear();
    refresh();
    heces_body = newwin(24, 80, 0, 0);
    assert(heces_body != NULL);
    box(heces_body, 0, 0);
    heces = derwin(heces_body, 16, 78, 3, 1);
    assert(heces != NULL);
    box(heces, 0, 0);
    barra = derwin(heces_body, 3, 78, 20, 1);
    assert(barra != NULL);
    box(barra, 0, 0);
    botones_3(barra, highlight);
    refresh();
    mvwprintw(heces_body, 1, 2, "RESULTADOS: PRUEBAS DE HECES");


    //--------- pag 1
    // FIELD *new_field(int height, int width, int toprow, int leftcol, int offscreen, int nbuffers);
    heces_fields[0] = new_field(1, 20, 0, 1, 0, 0);
    heces_fields[1] = new_field(1, 40, 0, 21, 0, 0);
    heces_fields[2] = new_field(1, 20, 2, 1, 0, 0);
    heces_fields[3] = new_field(1, 40, 2, 21, 0, 0);
    heces_fields[4] = new_field(2, 20, 4, 1, 0, 0);
    heces_fields[5] = new_field(1, 40, 4, 21, 0, 0);
    heces_fields[6] = new_field(1, 20, 7, 1, 0, 0);
    heces_fields[7] = new_field(1, 40, 7, 21, 0, 0);
    heces_fields[8] = new_field(1, 20, 9, 1, 0, 0);
    heces_fields[9] = new_field(1, 40, 9, 21, 0, 0);
    heces_fields[10] = new_field(1, 20, 11, 1, 0, 0);
    heces_fields[11] = new_field(1, 40, 11, 21, 0, 0);
    heces_fields[12] = new_field(1, 20, 13, 1, 0, 0);
    heces_fields[13] = new_field(1, 40, 13, 21, 0, 0);
    heces_fields[14] = new_field(1, 20, 15, 1, 0, 0);
    heces_fields[15] = new_field(1, 40, 15, 21, 0, 0);

    assert(heces_fields[0] != NULL &&
           heces_fields[1] != NULL &&
           heces_fields[2] != NULL &&
           heces_fields[3] != NULL &&
           heces_fields[4] != NULL &&
           heces_fields[5] != NULL &&
           heces_fields[6] != NULL &&
           heces_fields[7] != NULL &&
           heces_fields[8] != NULL &&
           heces_fields[9] != NULL &&
           heces_fields[10] != NULL &&
           heces_fields[11] != NULL &&
           heces_fields[12] != NULL &&
           heces_fields[13] != NULL &&
           heces_fields[14] != NULL &&
           heces_fields[15] != NULL);

    set_field_buffer(heces_fields[0], 0, "COPROCULTIVO:");
    set_field_buffer(heces_fields[1], 0, "");
    set_field_buffer(heces_fields[2], 0, "LEUCOCITOS");
    set_field_buffer(heces_fields[3], 0, "");
    set_field_buffer(heces_fields[4], 0, "COPROPARASITARIO:");
    set_field_buffer(heces_fields[5], 0, "");
    set_field_buffer(heces_fields[6], 0, "ROTAVIRUS:");
    set_field_buffer(heces_fields[7], 0, "");
    set_field_buffer(heces_fields[8], 0, "SUSTANCIAS REDUCTORAS:");
    set_field_buffer(heces_fields[9], 0, "");
    set_field_buffer(heces_fields[10], 0, "FRAGILIDAD GLOBULAR:");
    set_field_buffer(heces_fields[11], 0, "");
    set_field_buffer(heces_fields[12], 0, "THEVENON:");
    set_field_buffer(heces_fields[13], 0, "");
    set_field_buffer(heces_fields[14], 0, "TEST DE GRAHAM:");
    set_field_buffer(heces_fields[15], 0, "");

    set_field_opts(heces_fields[0], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(heces_fields[1], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(heces_fields[2], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(heces_fields[3], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(heces_fields[4], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(heces_fields[5], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(heces_fields[6], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(heces_fields[7], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(heces_fields[8], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(heces_fields[9], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(heces_fields[10], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(heces_fields[11], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(heces_fields[12], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(heces_fields[13], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);
    set_field_opts(heces_fields[14], O_VISIBLE | O_PUBLIC | O_AUTOSKIP);
    set_field_opts(heces_fields[15], O_VISIBLE | O_PUBLIC | O_EDIT | O_ACTIVE);

    set_field_back(heces_fields[1], A_UNDERLINE);
    set_field_back(heces_fields[3], A_UNDERLINE);
    set_field_back(heces_fields[5], A_UNDERLINE);
    set_field_back(heces_fields[7], A_UNDERLINE);
    set_field_back(heces_fields[9], A_UNDERLINE);
    set_field_back(heces_fields[11], A_UNDERLINE);
    set_field_back(heces_fields[13], A_UNDERLINE);
    set_field_back(heces_fields[15], A_UNDERLINE);

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

    heces_form = new_form(heces_fields);
    assert(heces_form != NULL);
    set_form_win(heces_form, heces);
    set_form_sub(heces_form, derwin(heces, 18, 76, 1, 1));
    post_form(heces_form);

    refresh();
    wrefresh(heces_body);
    wrefresh(heces);


    char new_fields[100];

    ifstream fm_read;
    fm_read.open("/Users/andreadiaz/projects/medDiary/prueba_nscurses/prueba_nscurses/laboratorio/Heces.txt");

    //fm_read >> new_fields;
    //set_field_buffer(ficha_medica_fields[1], 0, new_fields);

    for (int i = 1; heces_fields[i]; i = i + 2)
    {
        fm_read >> new_fields;
        set_field_buffer(heces_fields[i], 0, new_fields);
    }


    fm_read.close();

    while ((ch = getch()) != KEY_F(12))
        heces_driver_1(ch);

    unpost_form(heces_form);
    free_form(heces_form);
    free_field(heces_fields[0]);
    free_field(heces_fields[1]);
    free_field(heces_fields[2]);
    free_field(heces_fields[3]);
    delwin(heces);
    delwin(heces_body);
}
void labmenu(int x)

{
    WINDOW *menu_winlab;

    char mesg[] = "LABORATORIO";
    int row, col;
    int highlight = 1;
    int choice = 0;
    int c, ch = 0;
    int a = 0;
    int g = 0;


    //------ inicio del programa
    initscr();

    clear();

    noecho();

    cbreak();

    keypad(stdscr,
           TRUE);
    mousemask(ALL_MOUSE_EVENTS,NULL);


    //------ barra de inicio
    getmaxyx(stdscr, row, col);
    for (
            int i = 0;
            i<col;
            i++) {
        printw("-");
    };
    mvchgat(0, 0, -1, A_NORMAL, 1, NULL);
    mvprintw(1,(col-
                strlen(mesg)
               )/2,"%s",mesg); //imprime en la posicion dada
    printw("\n");
    for (
            int i = 0;
            i<col;
            i++) {
        printw("-");
    };

    //------- menu
    startx = (80 - WIDTH) / 2;
    starty = (24 - HEIGHT) / 2;

    menu_winlab = newwin(HEIGHT, WIDTH, starty, startx);
    keypad(menu_winlab,
           TRUE);
    keypad(ficha_medica,
           TRUE);

    refresh();

    menulab(menu_winlab, highlight);

    while(1)
    { c = wgetch(menu_winlab);
        switch(c)
        {
            case KEY_UP:
                if(highlight == 1)
                {
                    highlight = n_choiceslab;
                }

                else
                    --
                            highlight;
                break;

            case KEY_DOWN:
                if(highlight == n_choiceslab)
                    highlight = 1;
                else
                    ++
                            highlight;
                break;

            case 10:
                choice = highlight;
                //------- Ficha medica
                if (choice == 1)
                {
                    hem_form = new_form(hem_fields);
                    assert(hem_fields != NULL);
                    hematologia(ch);
                    break;
                }

                //------- Doctores
                if (choice == 2)
                {
                    sangre_form = new_form(sangre_fields);
                    assert(sangre_fields != NULL);
                    bioquimica_sangre(g);
                    break;
                }

                //------- Laboratorios
                if (choice == 3)
                {
                    orina_form = new_form(orina_fields);
                    assert(orina_fields != NULL);
                    bioquimica_orina(ch);
                    break;
                }

                if (choice == 4)
                {
                    inmu_form = new_form(inmu_fields);
                    assert(inmu_fields != NULL);
                    inmunologia(ch);
                    break;
                }
                if (choice == 5)
                {
                    drugs_form = new_form(drugs_fields);
                    assert(drugs_fields != NULL);
                    drogas(ch);
                    break;
                }
                if (choice == 6)
                {
                    heces_form = new_form(heces_fields);
                    assert(heces_fields != NULL);
                    prueba_heces(ch);
                    break;
                }
                if (choice == 7)
                {
                    main();
                }
            default:

                refresh();

                break;
        }
        menulab(menu_winlab, highlight
        );
        if(choice != 0)
            break;
    }

    clrtoeol();

//------- corriendo programa
    refresh();

    getch();

//--------------------------


//------- fin de programa
    delwin(menu_winlab);

    endwin();
//-----------------------

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
    int g = 0;

    //------ inicio del programa
    initscr();
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
                    doctores_form = new_form(doctores_fields);
                    assert(doctores_fields != NULL);
                    doctores_win1(g);
                    break;
                }

                //------- Laboratorios
                if (choice == 3)
                {
                    labmenu(a);
                }
                
                if (choice == 4)
                {
                    break;
                }
                
                

            default:
                refresh();
                break;
        }
        menu(menu_win, highlight);
        if(choice != 0)
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
