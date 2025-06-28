#include "pacote.hpp"

// Destrutor do pacote:
// Libera a memória alocada para a lista de rotas do pacote.
Pacote::~Pacote(){
  this->Rotas->limpar();
}
