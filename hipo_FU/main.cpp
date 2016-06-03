/* 
 * File:   main.cpp
 * Author: alysson
 *
 * Created on 10 de Setembro de 2015, 11:41
 */
#include <fstream>
#include <cmath>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>
#include "interface.h"

using namespace std;

//Objetos da Tela - Para não haver problema são globais, já que funcionam durante toda a execução do Programa
GtkWidget *win = NULL;
GtkWidget *hbox, *vbox;
GtkWidget *frame0, *frame1, *frame2;
GtkWidget *table0, *table1, *table2;
GtkWidget *labels, *estados_testados, *estados_solucao;
GtkWidget *execute, *open_prog;

//Por aqui o Programa começa

int main(int argc, char *argv[]) {

    // Inicializa GTK+ 
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, (GLogFunc) gtk_false, NULL);
    gtk_init(&argc, &argv);
    g_log_set_handler("Gtk", G_LOG_LEVEL_WARNING, g_log_default_handler, NULL);

    // Janela 
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(win), 20);
    gtk_window_set_title(GTK_WINDOW(win), "HIPO");
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
    gtk_widget_realize(win);
    g_signal_connect(win, "destroy", gtk_main_quit, NULL);

    //Box Vertical
    vbox = gtk_vbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(win), vbox);

    frame2 = gtk_frame_new("Menu");
    gtk_box_pack_start(GTK_BOX(vbox), frame2, TRUE, TRUE, 0);

    // Box Horizontal
    hbox = gtk_hbox_new(FALSE, 10);
    gtk_container_add(GTK_CONTAINER(vbox), hbox);

    // Frames
    frame0 = gtk_frame_new("Programa");
    gtk_box_pack_start(GTK_BOX(hbox), frame0, TRUE, TRUE, 0);

    frame1 = gtk_frame_new("Instruções do Hipo");
    gtk_box_pack_start(GTK_BOX(hbox), frame1, TRUE, TRUE, 0);

    //Tables
    table0 = gtk_table_new(0, 0, FALSE);
    gtk_container_add(GTK_CONTAINER(frame0), table0);
    table1 = gtk_table_new(3, 3, FALSE);
    gtk_container_add(GTK_CONTAINER(frame1), table1);
    table2 = gtk_table_new(4, 4, FALSE);
    gtk_container_add(GTK_CONTAINER(frame2), table2);

    //Menu
    open_prog = gtk_button_new_from_stock("Abrir Programa");
    g_signal_connect(G_OBJECT(open_prog), "clicked", G_CALLBACK(NULL), (gpointer) win);
    gtk_widget_set_size_request(open_prog, 170, 30);
    gtk_table_attach_defaults(GTK_TABLE(table2), open_prog, 0, 3, 0, 1);

    execute = gtk_button_new_from_stock("Executar Programa");
    g_signal_connect(G_OBJECT(execute), "clicked", G_CALLBACK(NULL), (gpointer) win);
    gtk_widget_set_size_request(execute, 170, 30);
    gtk_table_attach_defaults(GTK_TABLE(table2), execute, 3, 6, 0, 1);

    labels = gtk_label_new(" Posição ");
    gtk_table_attach_defaults(GTK_TABLE(table0), labels, 0, 2, 0, 1);
  
    labels = gtk_label_new(" Valor ");
    gtk_table_attach_defaults(GTK_TABLE(table0), labels, 3, 5, 0, 1);

    labels = gtk_label_new(" Comentários ");
    gtk_table_attach_defaults(GTK_TABLE(table0), labels, 6, 8, 0, 1);

    for (int i = 0; i < 10; i++) {

    }
    //estados_solucao = gtk_label_new(" 0 ");
    //gtk_table_attach_defaults(GTK_TABLE(table0), estados_solucao, 2, 3, 3, 4);
    int length;

    ifstream fp;
    char ch;
    string retorno;
    fp.open("inst_hipo.txt", ios::in);
    length = fp.tellg();
    //fp.seekg(0, ios::beq);

    if (!fp.is_open()) {
        cout << "Não foi possível abrir o arquivo!" << endl;
    } else {

        while (fp.get(ch)) {
            retorno += ch;
            //        /fp.put(ch);
        }

    }
    char instr_hipo[retorno.length()];
    //cout << retorno << retorno.length() << endl;
    for (int i = 0; i < retorno.length(); i++) {
        instr_hipo[i] = retorno[i];
    }

    labels = gtk_label_new("Instruções do Hipo\n");
    gtk_table_attach_defaults(GTK_TABLE(table1), labels, 0, 2, 3, 4);
    //sprintf(teste, "%s", teste);
    gtk_label_set_text(GTK_LABEL(labels), instr_hipo);
    // estados_solucao = gtk_label_new(" 0 ");"Instruções do Hipo\n Acc = Acumulador\n EE = Endereço de 2 digitos\n"
    // gtk_table_attach_defaults(GTK_TABLE(table0), estados_solucao, 2, 3, 3, 4);

    // Enter the main loop 
    gtk_widget_show_all(win);
    gtk_main();

    return 0;
}