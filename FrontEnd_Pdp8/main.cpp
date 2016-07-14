//COMPILA TODO O PROJETO NO TERMINAL
//g++ *.cpp -o pdp8 `pkg-config gtkmm-3.0 --cflags --libs`
//Referencias https://developer.gnome.org/gtkmm-tutorial/stable/sec-basics-simple-example.html.en
//https://developer.gnome.org/gtkmm-tutorial/stable/sec-builder-accessing-widgets.html.en
#include <iostream>
#include <gtkmm.h>
//#include "interfaces.h"

using namespace std;

Gtk::Window* win = nullptr;

int main(int argc, char *argv[]) {
	cout << "!!!PDP8 is online!!!" << endl; // prints !!!Hello World!!!
	
	//Interfaces interface;// = new Interfaces();
	
	auto app =
	    Gtk::Application::create(argc, argv,
	      "pdp8");

	    Glib::RefPtr<Gtk::Builder> builder = 
	  Gtk::Builder::create_from_file("pdp8.glade");
	  
auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file("pdp8.glade");
  }
  catch(const Glib::FileError& ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Glib::MarkupError& ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  }
  catch(const Gtk::BuilderError& ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }
	 // Gtk::Window window;
	 // window.set_default_size(200, 200);
  //Get the GtkBuilder-instantiated Dialog:
  refBuilder->get_widget("applicationwindow1", win);
  if(win)
  {
    //Get the GtkBuilder-instantiated Button, and connect a signal handler:
    /*Gtk::Button* pButton = nullptr;
    refBuilder->get_widget("quit_button", pButton);
    if(pButton)
    {
      pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
    }*/

    app->run(*win);
  }

  delete win;


	  //return app->run(window);
	return 0;
}
