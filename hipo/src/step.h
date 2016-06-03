/*
 * step.h
 *
 *  Created on: 03/06/2016
 *      Author: alysson
 */
#ifndef STEP_H_
#define STEP_H_

#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/separator.h>
#include <gtkmm.h>
#include "lexico.h"

class Step : public Gtk::Window {
public:
	Step();
	virtual ~Step();
	ifstream entrada;
	  std::string filename;
	  Lexico lexico;
	  //Tree model columns:
	    class ModelColumns : public Gtk::TreeModel::ColumnRecord
	    {
	    public:

	      ModelColumns()
	      { add(m_col_id); add(m_col_name); add(m_col_number); }

	      Gtk::TreeModelColumn<Glib::ustring> m_col_id;
	      Gtk::TreeModelColumn<Glib::ustring> m_col_name;
	      Gtk::TreeModelColumn<Glib::ustring> m_col_number;
	     // Gtk::TreeModelColumn<int> m_col_percentage;
	    };

	    ModelColumns m_Columns;

	protected:
	  //Signal handlers:
	  void on_button_clicked();
	  void on_button_chooser_clicked();
	  void on_button_execute_clicked();
	  void fill_buffer();

	    //Child widgets:
	  //Grid
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
	  //Gtk::Grid m_Grid;
};

#endif /* STEP_H_ */

