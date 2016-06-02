#include <fstream>
#include <cmath>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>
//#include "interface.hpp"
using namespace std;

GtkWidget *win = NULL;
GtkWidget *hbox, *vbox;
GtkWidget *frame0, *comandosFrame, *TerminalFrame;
GtkEntryBuffer *buffer;
GtkWidget *terminalEntry;
GtkWidget *button_box, *button;

static void print_hello(GtkWidget *widget, gpointer data){
	g_print("Hello World\n");
}

int main(int argc, char *argv[]) {

gtk_init(&argc, &argv);

//Interface *interface = new Interface();
//interface->FirstPanel();
/*
  gtk_init(&argc, &argv);
*/
  // Janela 
    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(win), 20);
    gtk_window_set_title(GTK_WINDOW(win), "HIPO");
    gtk_window_set_default_size(GTK_WINDOW(win), 600, 600);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
    gtk_widget_realize(win);
    g_signal_connect(win, "destroy", gtk_main_quit, NULL);

    // Box Vertical
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(win), vbox);

    //Botões
    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER (vbox), button_box);

    button = gtk_button_new_with_label("Hello Word");
    g_signal_connect(button, "clicked", G_CALLBACK (print_hello), NULL);
    g_signal_connect_swapped(button, "clicked", G_CALLBACK(gtk_widget_destroy), win);
    gtk_container_add(GTK_CONTAINER(button_box), button);


	// Box Horizontal
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(vbox), hbox);

    // Frames
    TerminalFrame = gtk_frame_new("Algoritmo Lido");
    gtk_box_pack_start(GTK_BOX(hbox), TerminalFrame, TRUE, TRUE, 0);

    comandosFrame = gtk_frame_new("Instruções do HIPO");
    gtk_box_pack_start(GTK_BOX(hbox), comandosFrame, TRUE, TRUE, 0);
/*
    char *teste;
    teste = new char[100];
	terminalEntry = gtk_entry_new();   
	buffer = gtk_entry_buffer_new (teste,
                      0);//gtk_entry_get_buffer (terminalEntry);
    gtk_entry_buffer_set_max_length (buffer, 100);
    gtk_container_add(GTK_CONTAINER(TerminalFrame), terminalEntry);
  */  
   // frame2 = gtk_frame_new("Menu");
    //gtk_box_pack_start(GTK_BOX(hbox), frame2, TRUE, TRUE, 0);

  gtk_widget_show_all(win);
 
  gtk_main();

  return 0;
}
