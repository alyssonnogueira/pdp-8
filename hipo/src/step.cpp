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
//Heads
#include "step.h"
#include "lexico.h"
#include "interfaces.h"
// Inclui o Header da classe lexico.h

using namespace std;

Step::Step(std::string filename, Lexico *lexico) :
  mBox(Gtk::ORIENTATION_VERTICAL),
  mBoxTop(Gtk::ORIENTATION_HORIZONTAL),
  mBoxDown(Gtk::ORIENTATION_HORIZONTAL, 10),
  mBox1(Gtk::ORIENTATION_VERTICAL, 10),
  mBox2(Gtk::ORIENTATION_VERTICAL, 10),
  mButtonChooser("Voltar"),
  mButtonExecute("Próximo Passo"),
  mButtonValue("Ok"),
  mButtonBox(Gtk::ORIENTATION_HORIZONTAL)
{
	// Set title and border of the window
	this->filename = filename;
	this->lexico = lexico;
	window.set_title("HIPO Step by Step");
	window.set_border_width(1);
	window.set_default_size(800, 500);

  mBox1.set_size_request(400, 400);
  mBox2.set_size_request(400, 400);
   // Add outer box to the window (because the window
  // can only contain a single widget)
  window.add(mBox);

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
  mLabel.set_text("Acumulador: ");
  mButtonBox.pack_start(mLabel);
  mButtonBox.pack_start(mTextView2);
  mButtonBox.pack_start(mButtonValue);
  mLabel2.set_text("Inserir Valor:");

  mButtonValue.signal_clicked().connect(sigc::mem_fun(*this,
		  &Step::ValueTrue));
  mButtonBox.pack_start(mButtonExecute);
    mButtonExecute.signal_clicked().connect(sigc::mem_fun(*this,
                &Step::on_button_step_clicked) );

  mButtonChooser.set_can_default();
  mButtonChooser.grab_default();

  //inicializa buffers
  this->fill_buffer();

  //Create the Tree model:
    m_refTreeModel = Gtk::ListStore::create(m_Columns);
    m_TreeView.set_model(m_refTreeModel);

    //Add the TreeView's view columns:
    m_TreeView.append_column("ID", m_Columns.m_col_id);
    m_TreeView.append_column("Operacao", m_Columns.m_col_operacao);
    m_TreeView.append_column("Operando", m_Columns.m_col_operando);

    //Make all the columns reorderable and define a min_size:
    for(guint i = 0; i < 2; i++)
    {
      Gtk::TreeView::Column* pColumn = m_TreeView.get_column(i);
      pColumn->set_reorderable();
      pColumn->set_min_width(100);
      pColumn->set_resizable(1);

    }

  // Show all children of the window
    window.show_all();
}

Step::~Step()
{
}

void Step::on_button_clicked()
{
  hide(); //to close the application.
}

void Step::on_button_step_clicked()
{
	static int i = 0;
	static Gtk::TreeModel::Row row = *(m_refTreeModel->append());
	vector < vector<int> > lista;
	if (this->filename.length() == 0){
		Gtk::MessageDialog dialog(*this, "OPA! Você não escolheu um Programa!");
		  dialog.set_secondary_text(
		          "Por favor, clique em Abrir programa antes de prosseguir.");

		  dialog.run();
	} else {
			string retorno;
			if (i == 0){
				interpretador = lexico->identificaToken(interpretador);
				cout << "SAIDA DO VECTOR COM INTRUCOES E ENDERECOS" << endl;
			}
			processador.processaCodigo(this, interpretador);
			lista = processador.getListaComandos();
			    i++;
	}
}

void Step::on_button_chooser_clicked()
{

	this->window.close();

}

void Step::fill_buffer(){

	  this->interpretador.resize(lexico->getTamList()); // Cria 100 posição no vetor
	  for (int i = 0; i < lexico->getTamList(); ++i){
		  this->interpretador[i].resize(2); // Gera uma matriz 100 x 2
	  }

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
		        }
			m_refTextBuffer->set_text(retorno);
		}
		m_TextView.set_buffer(m_refTextBuffer);

}

void Step::RefreshScreen(int id, int operacao, int operando){
	Gtk::TreeModel::Row row = *(m_refTreeModel->append());
	row[m_Columns.m_col_id] = id;
	row[m_Columns.m_col_operacao] = operacao;
	row[m_Columns.m_col_operando] = operando;//lexico->stringToInt(processador.text[1].str());
	std::ostringstream acc;
	acc << "Acumulador: " << processador.getACC(); //processador.text[1].str();
	this->mLabel.set_text(acc.str());
}

int Step::NewValue(string label){
	this->mLabel.set_text(label);
	return 0;
}

void Step::ValueTrue(){
	Glib::RefPtr<Gtk::TextBuffer> refTextBuffer = this->mTextView2.get_buffer();
	processador.mValue = lexico->stringToInt(refTextBuffer->get_text());
	cout << "Hear!: " << processador.mValue << endl;
	refTextBuffer->set_text(" ");
	this->mTextView2.set_buffer(refTextBuffer);
	processador.RefreshSimbolTable(this);
	this->on_button_step_clicked();
}


