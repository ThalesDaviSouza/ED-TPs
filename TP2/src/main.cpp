#include <iostream>
#include "pacote.hpp"
#include "list.hpp"
#include "pilha.hpp"

int main(){
  Pacote teste(0, 10, "Teste1", "Teste1000", None, 0, 3);
  Pacote teste1(1, 10, "Teste2", "Teste2000", None, 0, 3);
  Pacote teste2(2, 10, "Teste3", "Teste3000", None, 0, 3);
  
  List<Pacote>* pacotes = List<Pacote>::createList(); 
  Pilha<Pacote>* pilha = Pilha<Pacote>::createPilha();

  pilha = pilha->add(teste);
  pilha = pilha->add(teste1);
  pilha = pilha->add(teste2);
  
  pacotes->add(teste);
  pacotes->add(teste1);
  pacotes->add(teste2);

  List<Pacote>* aux = pacotes;
  Pilha<Pacote>* auxP = pilha;
  
  // while(aux != nullptr){
  //   cout << aux->value->id 
  //   << " " << aux->value->nomeRemetente 
  //   << " " << aux->value->nomeDestinatario << endl;
  //   aux = aux->next;
  // }

  while(auxP != nullptr){
    cout << auxP->value->id 
    << " " << auxP->value->nomeRemetente 
    << " " << auxP->value->nomeDestinatario << endl;
    auxP = auxP->remove();
  }

  pacotes->limpar();

  return 0;
}