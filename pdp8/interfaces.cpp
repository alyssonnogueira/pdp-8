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
  #include <gtkmm.h>
  #include "Carregador.h"
  #include "Ligador.h"
  #include "Simulador.hpp"
  #include "Montador.h"
  #include "Processador_macros.h"
  #include "interfaces.h"

  using namespace std;

  Interfaces::Interfaces(Glib::RefPtr<Gtk::Application>& app, Glib::RefPtr<Gtk::Builder>& refBuilder){

  Gtk::Button* pButton = nullptr;
  /*
  refBuilder->get_widget("quit_button", pButton);
  if(pButton)
  {
    pButton->signal_clicked().connect( sigc::ptr_fun(on_button_clicked) );
  }*/
    refBuilder->get_widget("d i g i t a l - PDP8", win);
    refBuilder->get_widget("PDP8", win2);
    if(win)
    {
      refBuilder->get_widget("togglebutton_cl",start_cl);
      start_cl->signal_clicked().connect(sigc::mem_fun(*this,
        &Interfaces::on_cl_clicked) );

      refBuilder->get_widget("togglebutton_co",start_co);
      start_co->signal_clicked().connect(sigc::mem_fun(*this,
        &Interfaces::on_co_clicked) );
      
      refBuilder->get_widget("togglebutton_halt", halt);
      halt->signal_clicked().connect(sigc::mem_fun(*this, 
        &Interfaces::on_halt_clicked) );
/*
      refBuilder->get_widget("imagemenuitem2", open);
      open->signal_clicked().connect(sigc::mem_fun(*this, 
        &Interfaces::on_button_chooser_clicked) );      
  */  
    //    add_action("copy", sigc::mem_fun(*this, &Interfaces::on_button_chooser_clicked()));
      app->run(*win);

    }


    delete win;
  }

  Interfaces::~Interfaces()
  {}

void Interfaces::on_halt_clicked(){
  //win->signal_hide().connect(sigc::mem_fun(*this, &Interfaces::win2));
   win2->close();
   start_cl->set_active(false);
   start_co->set_active(false);
   halt->set_active(false);
}

void Interfaces::on_cl_clicked(){
  win2->show();
  std::cout << "The Button was clicked: state="
  << (start_cl->get_active() ? "true" : "false")
  << std::endl;
  if (start_cl->get_active()){

  //------------------------------------MACRO------------------------------------
    this->start_processador();

  //-----------------------------MONTADOR------------------------------------
    this->start_montador();   

  //Ligador
    this->start_ligador();

  //------------------------------------Carregador------------------------------------
    this->start_carregador();  


  //------------------------------------SIMULADOR------------------------------------
  //start_simulador();
  }
}

void Interfaces::on_co_clicked(){
  std::cout << "The Button was clicked: state="
  << (start_co->get_active() ? "true" : "false")
  << std::endl;
  if ((start_co->get_active()) && (start_cl->get_active())){
    //------------------------------------SIMULADOR------------------------------------
    start_simulador();
  }
  else {
    cout << "CL não está ativado" << endl; 
  }
  start_co->set_active(false);
}

int Interfaces::start_processador(){
  macro = new Processador_macros();
  ifstream entrada1;
  entrada1.open("entrada_teste.txt");

  if (!entrada1){
    cout << "Não foi possível abrir o arquivo!" << endl;
    //return 0;
  }

  if(!macro->lerEntrada(&entrada1)){ // Le o arquivo de entrada e adiciona ao analisador lexico os tokens separados
    cout << "Não foi possivel ler o arquivo! " << endl;
  }

  macro->passOne();
  macro->passTwo();
  macro->saidaFinal();
  macro->expansaoFinal();
  // ========================================

  entrada1.close(); // Fecha o arquivo
  return 0;
}

int Interfaces::start_montador(){
  m = new Montador();
  m->assemblerOne("Entrada7.txt");
  m->printObjectCode();
  cout << "\n";
  m->printEDSTable();
  cout << "\n";
  m->printERS();

  vector<struct oc> obj = m->getObjectCode();
  //std::copy( m.getObjectCode().begin(), m.getObjectCode().end(), std::back_inserter( obj ) );
  int i = 0;
  ofstream saida;
  string objn = "objeto.o";
  saida.open("objeto.o", ios_base::out); //, ios_base::in

  for (int i = 0; i < obj.size(); i++) {
    oc octable = obj[i];
    saida << octable.adress << " " << octable.adress << " " << octable.opcode << " " << octable.operand << endl;
    i++;
      //obj.pop_front();
  }
  lobj.push_back(objn);
  return 0;
}

int Interfaces::start_ligador(){
    //------------------------------------LIGADOR------------------------------------
    ligador = new Ligador(); 
    ligador->Linker(lobj, m->getERS(), m->getEDS());
    return 0;
}

    //CARREGADOR
int Interfaces::start_carregador(){

    carregador = new Carregador(ligador->getlinhas());
    // Cria ponteiro e abre o arquivo de entrada
    ifstream entrada0;
    entrada0.open("programa.pdp"); //, ios_base::in
    if (!entrada0) {
      cout << "Não foi possível abrir o arquivo!" << endl;
        //return 0;
    }

    if (!carregador->lerEntrada(&entrada0)) { // Le o arquivo de entrada e adiciona ao analisador lexico os tokens separados
      cout << "Não foi possivel ler o arquivo! " << endl;
    }
    lobj.clear();
    return 0;
}

//SIMULADOR
int Interfaces::start_simulador(){
  simulador = new Simulador();
  vector <vector<int> > interpretador; // Vector inteiro que armazena intruções e endereços como inteiros

  interpretador.resize(500); // Cria 100 posição no vetor
  for (int i = 0; i < 500; ++i)
      interpretador[i].resize(4); // Gera uma matriz 100 x 2

  // Cria ponteiro e abre o arquivo de entrada
    ifstream entrada;
    entrada.open("programa.pdp", ios_base::in);

    if (!entrada) {
      cout << "Não foi possível abrir o arquivo!" << endl;
     // return 0;
    }


    list<string> lista;
    char ch;
    string PC;
    int intPC;
    while (!entrada.eof()) {
      while (entrada.get(ch)) // percorre o arquivo caracter a caracter
      {
          if (ch == ';' || ch == '\n') // verifica se o caracter encontrado é um ; ou \n
          {
              lista.push_back(PC); // adiciona a string a ultima posicao da lista
              cout << endl << "STRING " << PC << endl;
              PC = "";
            } else {
              PC += ch; // Gera a string até achar um ; ou \n
            }
          }
        }

        int EXEC, OP, OPER;
        while (!(lista.empty())) {

          PC = lista.front();
          intPC = simulador->stringToInt(PC);
          lista.pop_front();

          PC = lista.front();
          if (PC == "-1")
            EXEC = -1;
          else
            EXEC = simulador->stringToInt(PC);
          lista.pop_front();

          PC = lista.front();
          OP = simulador->stringToInt(PC);
          lista.pop_front();

          PC = lista.front();
          OPER = simulador->stringToInt(PC);
          lista.pop_front();

          interpretador[intPC][0] = intPC;
          interpretador[intPC][1] = EXEC;
          interpretador[intPC][2] = OP;
          interpretador[intPC][3] = OPER;
          cout << interpretador[intPC][0] << " " << interpretador[intPC][1] << " " << interpretador[intPC][2] << " " << interpretador[intPC][3] << endl;
        }
        cout << "INICIANDO PROGRAMA, PRESSIONE ENTER" << endl;
        simulador->processaCodigo(interpretador);
  entrada.close(); // Fecha o arquivo
  return 0;
}

void Interfaces::on_button_chooser_clicked()
{
  Gtk::FileChooserDialog dialog("Por favor selecione um programa PDP8",
          Gtk::FILE_CHOOSER_ACTION_OPEN);
  dialog.set_transient_for(*win);

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
      /*
      //Notice that this is a std::string, not a Glib::ustring.
      this->filename = dialog.get_filename();
      std::cout << "File selected: " <<  filename << std::endl;
    string retorno;
        vector<int> interpretador;

      // Cria ponteiro e abre o arquivo de entrada
      entrada.open(this->filename.c_str(), ios::in);
      if (!entrada){
            cout << "Não foi possível abrir o arquivo!" << endl;
        }

        if(!lexico.lerEntrada(&entrada)){ // Le o arquivo de entrada
          cout << "Não foi possivel ler o arquivo! " << endl;
        }
        cout << endl;
        cout << "SAIDA DA LISTA DO LEXICO" << endl;

        list<string> lista = lexico.getList();
        std::list<string>::iterator ptr;
        int i = 0;
        Gtk::TreeModel::Row row;// = *(m_refTreeModel->append());
        //Pega tamanho do código
        ptr = lista.begin();
        lista.pop_front();
        int tamList = lexico.stringToInt(*ptr);
        //Pega o tamanho em bits dos operandos
        ptr = lista.begin();
        lista.pop_front();
        int tamInstrucoes = lexico.stringToInt(*ptr);
        lexico.setTamList(tamList);
        lexico.setTamInstrucoes(tamInstrucoes);

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

        cout << endl;
      break;*/
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
