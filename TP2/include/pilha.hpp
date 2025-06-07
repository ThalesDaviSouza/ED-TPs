#ifndef PILHA_H
#define PILHA_H

template<typename T>
class Pilha{
public:
  T* value;
  Pilha<T>* prev;
  Pilha<T>* next;

  static Pilha<T>* createPilha();
  Pilha<T>* add(T& value);
  Pilha<T>* remove();
  void limpar();

private:
  Pilha(T& value, Pilha<T>* prev, Pilha<T>* next)
  : value(&value), prev(prev), next(next) { }

  Pilha()
  : value(nullptr), prev(nullptr), next(nullptr) { }  
};

template<typename T>
Pilha<T>* Pilha<T>::createPilha(){
  return new Pilha<T>();
}

template<typename T>
Pilha<T>* Pilha<T>::add(T& value){
  Pilha<T>* top = this;
  
  // Primeira inserção
  if(top->value == nullptr){
    top->value = &value;
    return top;
  }
  
  while(top->prev != nullptr){
    top = top->prev;
  }
  top->prev = new Pilha(value, nullptr, nullptr);
  top->prev->next = top;
  return top->prev;
}

/// @return Retorna o novo topo 
template<typename T>
Pilha<T>* Pilha<T>::remove(){
  Pilha<T>* top = this;
  
  if(top == nullptr){
    return nullptr;
  }

  delete top;

  return top->next;
}

template<typename T>
void Pilha<T>::limpar(){
  Pilha<T>* top = this;
  
  if(top->next != nullptr){
    top->next->limpar();
  }
  
  delete top;
}


#endif