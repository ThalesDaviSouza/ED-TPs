#include "list.hpp"
#include "event.hpp"
#include "package.hpp"

// Instanciações explícitas da template List para:
// - Lista de objetos Event (histórico de eventos)
// - Lista de inteiros (IDs de pacotes)
// - Lista de pares Package* + string (pacotes com informações adicionais)
template class List<Event>;
template class List<int>;
template class List<std::pair<Package*, std::string>>;