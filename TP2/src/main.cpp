#include <iostream>
#include <string>
#include "pacote.hpp"
#include "list.hpp"
#include "pilha.hpp"
#include "armazem.hpp"

int main(){
  Pacote teste(0, 10, "Teste1", "Teste1000", None, 0, 1);
  Pacote teste1(1, 10, "Teste2", "Teste2000", None, 0, 1);
  Pacote teste2(2, 10, "Teste3", "Teste3000", None, 0, 1);
  
  Pacote teste3(3, 10, "Teste3", "Teste1000", None, 0, 5);
  Pacote teste4(4, 10, "Teste4", "Teste2000", None, 0, 5);
  Pacote teste5(5, 10, "Teste5", "Teste3000", None, 0, 5);
   
  Pacote teste6(6, 10, "Teste6", "Teste1000", None, 0, 10);
  Pacote teste7(7, 10, "Teste7", "Teste2000", None, 0, 10);
  Pacote teste8(8, 10, "Teste8", "Teste3000", None, 0, 10);
  
  Pacote teste9(8, 10, "Teste9", "Teste3000", None, 0, 12);
  
  // List<Pacote>* pacotes = List<Pacote>::createList(); 
  // Pilha<Pacote>* pilha = Pilha<Pacote>::createPilha();

  // pilha = pilha->add(teste);
  // pilha = pilha->add(teste1);
  // pilha = pilha->add(teste2);
  
  // pacotes->add(teste);
  // pacotes->add(teste1);
  // pacotes->add(teste2);

  // List<Pacote>* aux = pacotes;
  // Pilha<Pacote>* auxP = pilha;
  
  // while(aux != nullptr){
  //   cout << aux->value->id 
  //   << " " << aux->value->nomeRemetente 
  //   << " " << aux->value->nomeDestinatario << endl;
  //   aux = aux->next;
  // }

  // while(auxP != nullptr){
  //   cout << auxP->value->id 
  //   << " " << auxP->value->nomeRemetente 
  //   << " " << auxP->value->nomeDestinatario << endl;
  //   auxP = auxP->remove();
  // }

  // pacotes->limpar();
  int destinos[3] = {1, 5, 10};

  Armazem armazem(3, destinos);

  armazem.ArmazenarPacote(teste);
  armazem.ArmazenarPacote(teste2);
  armazem.ArmazenarPacote(teste1);

  armazem.ArmazenarPacote(teste3);
  armazem.ArmazenarPacote(teste4);
  armazem.ArmazenarPacote(teste5);

  armazem.ArmazenarPacote(teste6);
  armazem.ArmazenarPacote(teste7);
  armazem.ArmazenarPacote(teste8);

  armazem.ArmazenarPacote(teste9);

  auto t = armazem.RecuperarPacote(4, 5);
  auto t2 = armazem.RecuperarPacote(3, 5);
  auto t3 = armazem.RecuperarPacote(5, 5);
  auto t4 = armazem.RecuperarPacote(5, 5);

  auto t5 = armazem.RecuperarPacote(0, 1);
  auto t6 = armazem.RecuperarPacote(1, 1);
  auto t7 = armazem.RecuperarPacote(2, 1);

  auto aux = armazem.secoes;

  for(int i = 0; i < 3; i++){
    cout << aux->value->idArmazemDestino << endl;

    auto temp = aux->value->pacotes;
    while (temp != nullptr && temp->value != nullptr)
    {
      cout << "\tPacote: " << temp->value->id << " " << temp->value->idArmazemDestino << endl; 
      temp = temp->next;
    }
    
    aux = aux->next;
  }

  cout << "Recuperando Pacotes: " << endl;


  cout << t->id << " " << t->idArmazemDestino << " " << t->nomeRemetente << endl;
  cout << t2->id << " " << t2->idArmazemDestino << " " << t2->nomeRemetente << endl;
  cout << t3->id << " " << t3->idArmazemDestino << " " << t3->nomeRemetente << endl;

  cout << t5->id << " " << t5->idArmazemDestino << " " << t5->nomeRemetente << endl;
  cout << t6->id << " " << t6->idArmazemDestino << " " << t6->nomeRemetente << endl;
  cout << t7->id << " " << t7->idArmazemDestino << " " << t7->nomeRemetente << endl;

  return 0;
}