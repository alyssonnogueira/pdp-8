#include <fstream>
#include <cmath>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>

using namespace std;

class Interface{
private:
	GtkWidget *win = NULL;
	GtkWidget *hbox, *vbox;
	GtkWidget *frame0, *comandosFrame, *TerminalFrame;
	GtkEntryBuffer *buffer;
	GtkWidget *terminalEntry;
	GtkWidget *button_box, *newButton;
public:
	Interface();
	void FirstPanel();
	virtual ~Interface();
	static void print_hello(GtkWidget *widget, gpointer data);
};

