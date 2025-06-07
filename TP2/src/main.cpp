#include <iostream>
#include "pacote.hpp"
#include "list.hpp"

int main(){
  Pacote teste(0, 10, "Teste1", "Teste1000", None, 0, 3);
  Pacote teste1(1, 10, "Teste2", "Teste2000", None, 0, 3);
  Pacote teste2(2, 10, "Teste3", "Teste3000", None, 0, 3);
  
  List<Pacote>* pacotes = List<Pacote>::createList(); 
  
  pacotes->add(teste);
  pacotes->add(teste1);
  pacotes->add(teste2);

  List<Pacote>* aux = pacotes;
  
  while(aux != nullptr){
    cout << aux->value->id 
    << " " << aux->value->nomeRemetente 
    << " " << aux->value->nomeDestinatario << endl;
    aux = aux->next;
  }

  pacotes->limpar();

  return 0;
}