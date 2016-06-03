/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   main.cpp
 * Author: alysson
 *
 * Created on 2 de Junho de 2016, 20:00
 */

#include "interfaces.h"
#include <gtkmm/application.h>
#include <cstdlib>

using namespace std;


int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "Hipo");

  Interfaces interface;

  //Shows the window and returns when it is closed.
  return app->run(interface);
}
