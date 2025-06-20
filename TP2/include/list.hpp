#ifndef LIST_H
#define LIST_H

#include <memory>

using namespace std;

/// Lista encadeada genérica (implementada com ponteiros e sem sentinela).
/// Usada no TP2 para representar, por exemplo, a lista de seções de um armazém e a rota dos pacotes.
template<typename T>
class List{
public:
  T* value;              ///< Ponteiro para o valor armazenado no nó.
  List<T>* next;         ///< Ponteiro para o próximo nó da lista.
  
  /// Cria uma nova lista vazia.
  static List<T>* createList();

  /// Adiciona um novo valor no final da lista.
  void add(T& newValue);

  /// Adiciona um novo valor no início da lista (retorna novo ponteiro para a cabeça).
  List<T>* addFirst(T& newValue);

  /// Remove o primeiro elemento da lista (reestrutura a cabeça da lista) e retorna o valor removido.
  T removeFirst();

  /// Retorna ponteiro para o último valor da lista.
  T* lastValue();

  /// Remove recursivamente todos os nós da lista.
  void limpar();

  /// Verifica se a lista está vazia.
  bool isVazio();

  /// Verifica se o nó atual tem um valor associado.
  bool hasValue();
  
private:
  /// Construtor de nó preenchido (valor + próximo).
  List(T& value, List* next)
  : value(&value), next(next) { };

  /// Construtor de nó vazio.
  List()
  : value(nullptr), next(nullptr) { };
};

/// Cria uma lista vazia (sem valor nem próximo).
template<typename T>
List<T>* List<T>::createList(){
  return new List();
}

/// Verifica se o nó atual da lista contém um valor.
template<typename T>
bool List<T>::hasValue(){
  return this != nullptr && this->value != nullptr;
}

/// Adiciona um novo valor ao final da lista.
/// Se for o primeiro elemento, simplesmente define o valor na cabeça.
template<typename T>
void List<T>::add(T& newValue){
  List<T>* last = this;

  // Lista vazia
  if(this->value == nullptr){
    this->value = &newValue;
    return;
  }

  // Percorre até o último elemento
  while (last->next != nullptr)
  {
    last = last->next;
  }

  // Adiciona novo nó ao final
  last->next = new List(newValue, nullptr);
}

/// Adiciona um novo valor no início da lista.
/// Se a lista estiver vazia, apenas define o valor.
/// Caso contrário, cria um novo nó e retorna ele como nova cabeça da lista.
template<typename T>
List<T>* List<T>::addFirst(T& newValue){
  if(this->isVazio()){
    this->value = &newValue;
    return this;
  }

  List<T>* novo = new List<T>(newValue, this);
  
  return novo;
}

/// Remove todos os nós da lista recursivamente.
template<typename T>
void List<T>::limpar(){
  List<T>* aux = this;
  if(aux->next != nullptr){
    aux->next->limpar();
  }
  
  delete aux;
}

/// Verifica se a lista está vazia (sem valor e sem próximo).
template<typename T>
bool List<T>::isVazio(){
  return (this->value == nullptr && this->next == nullptr);
}

/// Remove o primeiro elemento da lista (reestrutura a cabeça) e retorna seu valor.
template<typename T>
T List<T>::removeFirst(){
  if(this->isVazio()){
    return T{}; // Retorna valor padrão se estiver vazia.
  }

  T removido = *this->value;

  // Se tiver próximo, reestrutura a lista copiando o próximo nó para este
  if(this->next != nullptr){
    List<int>* noRemover = this->next; 
    this->value = noRemover->value;
    this->next = noRemover->next;

    delete noRemover;
  }
  // Se não tiver próximo, esvazia a cabeça
  else{
    this->value = nullptr;
    this->next = nullptr;
  }

  return removido;
}

/// Retorna um ponteiro para o valor do último nó da lista.
/// Útil para acessar o último elemento diretamente.
template<typename T>
T* List<T>::lastValue(){
  List<T>* aux = this;

  if(aux->isVazio()){
    return nullptr;
  }

  while(aux->next != nullptr){
    aux = aux->next;
  }

  return aux->value;
}

#endif
