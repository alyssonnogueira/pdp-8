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
#include "interpretador.h"

class Step : public Gtk::Window
{
public:
	Step(std::string filename, Lexico *lexico);
	virtual ~Step();
	ifstream entrada;
	  std::string filename;
	  //Tree model columns:
	    class ModelColumns : public Gtk::TreeModel::ColumnRecord
	    {
	    public:

	      ModelColumns()
	      { add(m_col_id); add(m_col_operacao); add(m_col_operando); }

	      Gtk::TreeModelColumn<int> m_col_id;
	      Gtk::TreeModelColumn<int> m_col_operacao;
	      Gtk::TreeModelColumn<int> m_col_operando;
	    };

	    ModelColumns m_Columns;
	void RefreshScreen(int id, int operacao, int operando);
	int NewValue(string label);
	protected:
	  //Signal handlers:
	  void on_button_clicked();
	  void on_button_chooser_clicked();
	  void on_button_step_clicked();
	  void fill_buffer();
	  void ValueTrue();

	  Gtk::Window window;

	  Interpretador processador;  // Interpretador das instruções e endereços
	  Lexico *lexico; // Analisador lexico
	  vector <vector<int> > interpretador;  // Vector inteiro que armazena intruções e endereços como inteiros

	  //Grid
	  Gtk::ScrolledWindow m_ScrolledWindow;
	  Gtk::TreeView m_TreeView;
	  Glib::RefPtr<Gtk::ListStore> m_refTreeModel;

	  //Label
	  Gtk::TextView m_TextView;
	  Gtk::TextView mTextView2;
	  Gtk::Label mLabel;
	  Gtk::Label mLabel2;
	  Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;

	  Gtk::ButtonBox mButtonBox;
	  Gtk::Button mButtonChooser, mButtonExecute;
	  Gtk::Button mButtonValue;
	  Gtk::Box mBox, mBoxTop, mBoxDown, mBox1, mBox2;
	  Gtk::Separator mSeparator;
	  //Gtk::Grid m_Grid;
};

#endif /* STEP_H_ */

