/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   interfaces.hpp
 * Author: alysson
 *
 * Created on 2 de Junho de 2016, 20:04
 */

#ifndef Interfaces_H
#define Interfaces_H

#include <fstream>
#include <cmath>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <vector>

#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/separator.h>
#include <gtkmm.h>
//#include "lexico.h"
//#include "step.h"
//#include "interpretador.h"

using namespace std;

//: public Gtk::Window

class Interfaces {
public:
	Interfaces(Glib::RefPtr<Gtk::Builder>& refBuilder);

  virtual ~Interfaces();
  ifstream entrada;
  std::string filename;
  //Lexico lexico;

  //Tree model columns:
    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:

      ModelColumns()
      { add(m_col_id); add(m_col_name); add(m_col_number); }

      Gtk::TreeModelColumn<Glib::ustring> m_col_id;
      Gtk::TreeModelColumn<Glib::ustring> m_col_name;
      Gtk::TreeModelColumn<Glib::ustring> m_col_number;
    };

    ModelColumns m_Columns;

protected:

    //Signal handlers:
  void on_button_clicked();
  void on_button_chooser_clicked();
  void on_button_execute_clicked();
  void fill_buffer();

  //Step *mStep;

  //Child widgets:
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TreeView m_TreeView;
  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

  //Label
  Gtk::TextView m_TextView;
  Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

  Gtk::ButtonBox mButtonBox;
  Gtk::Button mButtonChooser, mButtonExecute;
  Gtk::Box mBox, mBoxTop, mBoxDown, mBox1, mBox2;
  Gtk::Separator mSeparator;
};

#endif //Interfaces_H
