#include "list.hpp"
#include "event.hpp"
#include "package.hpp"

// Instanciações explícitas para os tipos que serão usados
template class List<Event>;
template class List<int>;
template class List<std::pair<Package*, std::string>>;