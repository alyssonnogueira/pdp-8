#include <fstream>
#include <cmath>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <gtkmm/messagedialog.h>
#include <vector>
#include "step.h"
#include "lexico.h"
#include "interfaces.h"
// Inclui o Header da classe lexico.h

using namespace std;

Step::Step() :
  mBox(Gtk::ORIENTATION_VERTICAL),
  mBoxTop(Gtk::ORIENTATION_HORIZONTAL),
  mBoxDown(Gtk::ORIENTATION_HORIZONTAL, 10),
  mBox1(Gtk::ORIENTATION_VERTICAL, 10),
  mBox2(Gtk::ORIENTATION_VERTICAL, 10),
  mButtonChooser("Abrir Programa"),
  mButtonExecute("Executar Programa"),
  mButtonBox(Gtk::ORIENTATION_HORIZONTAL)
{
	GtkWidget* window;
			  	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
			  	gtk_widget_show_all (window);
  // Set title and border of the window
  set_title("HIPO");
  set_border_width(1);
  set_default_size(1000, 500);
  mBox1.set_size_request(500, 400);
  mBox2.set_size_request(500, 400);
   // Add outer box to the window (because the window
  // can only contain a single widget)
  add(mBox);

  m_ScrolledWindow.add(m_TreeView);
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  mBox.pack_start(mButtonBox);
  mBox.pack_start(mBoxDown);
  mBoxDown.pack_start(mBox1);
  //mBoxDown.pack_start(mSeparator);
  mBoxDown.pack_start(mBox2);
  mBox1.pack_start(m_ScrolledWindow);
  mBox2.pack_start(m_TextView);
  // Set the inner boxes' borders
  mBox2.set_border_width(1);
  mBox1.set_border_width(1);

  mButtonBox.pack_start(mButtonChooser);
  mButtonChooser.signal_clicked().connect(sigc::mem_fun(*this,
                &Step::on_button_chooser_clicked) );

    mButtonBox.pack_start(mButtonExecute);
    mButtonExecute.signal_clicked().connect(sigc::mem_fun(*this,
                &Step::on_button_execute_clicked) );

  mButtonChooser.set_can_default();
  mButtonChooser.grab_default();

  //Carrega arquivo de Instruções
  this->fill_buffer();

  //Create the Tree model:
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);

    //Fill the TreeView's model
    /*Gtk::TreeModel::Row row = *(m_refTreeModel->append());
    row[m_Columns.m_col_id] = "1";
    row[m_Columns.m_col_name] = "Billy Bob";
    row[m_Columns.m_col_number] = "10";
    //row[m_Columns.m_col_percentage] = 15;

*/
    //Add the TreeView's view columns:
    m_TreeView.append_column("ID", m_Columns.m_col_id);
    m_TreeView.append_column("Valor", m_Columns.m_col_name);
    m_TreeView.append_column("Comentario", m_Columns.m_col_number);
    //Gtk::TreeView::Column* Coluna = m_TreeView.get_column(i);
      //  pColumn->set_reorderable();
    //Display a progress bar instead of a decimal number:
    /*Gtk::CellRendererProgress* cell = Gtk::manage(new Gtk::CellRendererProgress);
    int cols_count = m_TreeView.append_column("Some percentage", *cell);
    Gtk::TreeViewColumn* pColumn = m_TreeView.get_column(cols_count - 1);
    if(pColumn)
    {
      pColumn->add_attribute(cell->property_value(), m_Columns.m_col_percentage);
    }
    */

    //Make all the columns reorderable and define a min_size:
    for(guint i = 0; i < 2; i++)
    {
      Gtk::TreeView::Column* pColumn = m_TreeView.get_column(i);
      pColumn->set_reorderable();
      pColumn->set_min_width(100);
      pColumn->set_resizable(1);

    }

  // Show all children of the window
  show_all_children(this);
}

Step::~Step()
{
}

void Step::on_button_clicked()
{
  hide(); //to close the application.
}

void Step::on_button_execute_clicked()
{
	if (this->filename.length() == 0){
		Gtk::MessageDialog dialog(*this, "OPA! Você não escolheu um Programa!");
		  dialog.set_secondary_text(
		          "Por favor, clique em Abrir programa antes de prosseguir.");

		  dialog.run();
	} else {
			string retorno;
		  	vector<int> interpretador;

		    lexico.identificaToken(&interpretador);

		    cout << "SAIDA DO VECTOR COM INTRUCOES E ENDERECOS" << endl;
		    for(int i = 0; i < interpretador.size(); i++){
		      if(i % 2 == 1)
		          cout << interpretador[i] << endl;
		      else
		          cout << interpretador[i] << " ";
		    }
		    cout << endl;
		  	entrada.close();
		  	//Step *step = new Step();
		  			  	/*GtkWidget* window;
		  	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
		  	gtk_widget_show_all (window);
		  	*/
	}
	}

void Step::on_button_chooser_clicked()
{
  Gtk::FileChooserDialog dialog("Por favor selecione um programa hipo",
          Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*this);

  //Add response buttons the dialog:
  dialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
  dialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

  //Add filters, so that only certain file types can be selected:

  Glib::RefPtr<Gtk::FileFilter> filter_text = Gtk::FileFilter::create();
  filter_text->set_name("Text files");
  filter_text->add_mime_type("text/plain");
  dialog.add_filter(filter_text);

  Glib::RefPtr<Gtk::FileFilter> filter_cpp = Gtk::FileFilter::create();
  filter_cpp->set_name("HiPO");
  filter_cpp->add_mime_type("text/hip");
  filter_cpp->add_mime_type("text/hip");
  filter_cpp->add_mime_type("text/hip");
  dialog.add_filter(filter_cpp);

  Glib::RefPtr<Gtk::FileFilter> filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_pattern("*");
  dialog.add_filter(filter_any);

  //Show the dialog and wait for a user response:
  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "Open clicked." << std::endl;

      //Notice that this is a std::string, not a Glib::ustring.
      this->filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;
		string retorno;
		  	vector<int> interpretador;

			// Cria ponteiro e abre o arquivo de entrada
			entrada.open(this->filename.c_str(), ios::in);
		 	if (!entrada){
		     		cout << "Não foi possível abrir o arquivo!" << endl;
		     		//return 0;
		  	}

		  	if(!lexico.lerEntrada(&entrada)){ // Le o arquivo de entrada
		  		cout << "Não foi possivel ler o arquivo! " << endl;
		  	}
		    cout << endl;
		    cout << "SAIDA DA LISTA DO LEXICO" << endl;

		    list<string> lista = lexico.getLista();
		    std::list<string>::iterator ptr = lexico.getPonteiro();
		    int i = 0;
		    Gtk::TreeModel::Row row;// = *(m_refTreeModel->append());
		    lista.pop_front();
		    lista.pop_front();
		    for ( ptr = lista.begin(); ptr != lista.end(); ptr++ ){

		    	if (i%3 == 0){
		    		row = *(m_refTreeModel->append());
		    		row[m_Columns.m_col_id] = *ptr;
		        } else {
		        	if(i%3 == 1){
		        		row[m_Columns.m_col_name] = *ptr;
		        	} else {
		        		row[m_Columns.m_col_number] = *ptr;
		        	}
		        }
		    	cout << *ptr << endl;
		        i++;
		    }
		    /*while(i < lista.size()){
		    	Gtk::TreeModel::Row row = *(m_refTreeModel->append());
		    	row[m_Columns.m_col_id] = lista[i];
		    	i+=1;
		    	row[m_Columns.m_col_name] = lista.[i];
		    	i+=1;
		    	row[m_Columns.m_col_number] = lista.[i];
		    	i+=1;
		    }*/
		    //lexico.imprimeLista();
		    cout << endl;
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}

void Step::fill_buffer(){
	m_refTextBuffer = Gtk::TextBuffer::create();
	ifstream fp;
	char ch;
	std::string retorno;
	fp.open("inst_hipo.txt", ios::in);
	if (!fp) {
		std::cout << "Não foi possível abrir arquivo de instruções HIPO!" << endl;
		m_refTextBuffer->set_text("Não foi possível abrir arquivo de instruções HIPO!");
	} else {
		while (fp.get(ch)) {
			retorno += ch;
	        //fp.put(ch);
	        }
		m_refTextBuffer->set_text(retorno);
	}
	m_TextView.set_buffer(m_refTextBuffer);

}
