#ifndef LIST_H
#define LIST_H

using namespace std;

template<typename T>
class List{
public:
  T* value;
  List<T>* next;
  
  static List<T>* createList();
  void add(T& newValue);
  void limpar();
  
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
void List<T>::limpar(){
  List<T>* aux = this;
  if(aux->next != nullptr){
    aux->next->limpar();
  }

  delete aux;
}


#endif