#include <fstream>
#include <cmath>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include "interface.hpp"

Interface::Interface(){
	
	gtk_init(&argc, &argv);

	win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_container_set_border_width(GTK_CONTAINER(win), 20);
    gtk_window_set_title(GTK_WINDOW(win), "HIPO");
    gtk_window_set_default_size(GTK_WINDOW(win), 600, 600);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
    gtk_widget_realize(win);
    g_signal_connect(win, "destroy", gtk_main_quit, NULL);
}

void Interface::FirstPanel(){

	// Box Vertical
    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(win), vbox);

    //Botões
    button_box = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
    gtk_container_add(GTK_CONTAINER (vbox), button_box);

    newButton = gtk_button_new_with_label("Novo");
    g_signal_connect(newButton, "clicked", G_CALLBACK (print_hello), NULL);
    g_signal_connect_swapped(newButton, "clicked", G_CALLBACK(gtk_widget_destroy), win);
    gtk_container_add(GTK_CONTAINER(button_box), newButton);


	// Box Horizontal
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(vbox), hbox);

    // Frames
    TerminalFrame = gtk_frame_new("Algoritmo Lido");
    gtk_box_pack_start(GTK_BOX(hbox), TerminalFrame, TRUE, TRUE, 0);

    comandosFrame = gtk_frame_new("Instruções do HIPO");
    gtk_box_pack_start(GTK_BOX(hbox), comandosFrame, TRUE, TRUE, 0);

}

void Interface::print_hello(GtkWidget *widget, gpointer data){
	g_print("Hello World\n");
}
