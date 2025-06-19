#ifndef LIST_H
#define LIST_H

#include <memory>

using namespace std;

template<typename T>
class List{
public:
  T* value;
  List<T>* next;
  
  static List<T>* createList();
  void add(T& newValue);
  List<T>* addFirst(T& newValue);
  T removeFirst();
  T* lastValue();
  void limpar();
  bool isVazio();
  bool hasValue();
  
private:
  List(T& value, List* next)
  : value(&value), next(next) { };
  List()
  : value(nullptr), next(nullptr) { };
};

template<typename T>
List<T>* List<T>::createList(){
  return new List();
}
template<typename T>
bool List<T>::hasValue(){
  return this != nullptr && this->value != nullptr;
}

template<typename T>
void List<T>::add(T& newValue){
  List<T>* last = this;

  // Se é o primeiro item da lista
  if(this->value == nullptr){
    this->value = &newValue;
    return;
  }

  while (last->next != nullptr)
  {
    last = last->next;
  }

  last->next = new List(newValue, nullptr);
}

template<typename T>
List<T>* List<T>::addFirst(T& newValue){
  // Se é o primeiro item da lista
  if(this->isVazio()){
    this->value = &newValue;
    return this;
  }

  List<T>* novo = new List<T>(newValue, this);
  
  return novo;
}

template<typename T>
void List<T>::limpar(){
  List<T>* aux = this;
  if(aux->next != nullptr){
    aux->next->limpar();
  }
  
  delete aux;
}

template<typename T>
bool List<T>::isVazio(){
  return (this->value == nullptr && this->next == nullptr);
}

template<typename T>
T List<T>::removeFirst(){
  if(this->isVazio()){
    return T{};
  }

  T removido = *this->value;

  // Se tem um próximo valor
  // Puxa os dados para o primeiro elemento e remove o próximo
  if(this->next != nullptr){
    List<int>* noRemover = this->next; 
    this->value = noRemover->value;
    noRemover = noRemover->next;
    delete noRemover;
  }
  // Senão, esvazia a cabeça da lista
  else{
    this->value = nullptr;
    this->next = nullptr;
  }

  return removido;
}

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