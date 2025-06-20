#ifndef PILHA_H
#define PILHA_H

/// @brief Estrutura de pilha (LIFO) genérica, implementada com ponteiros.
/// A pilha cresce para "baixo", ou seja, o topo está sempre no nó mais à esquerda (prev).
/// Usada nas seções dos armazéns para armazenar pacotes.
template<typename T>
class Pilha{
public:
  T* value;             ///< Valor armazenado neste nó da pilha.
  Pilha<T>* prev;       ///< Ponteiro para o próximo elemento mais abaixo na pilha (novo topo).
  Pilha<T>* next;       ///< Ponteiro para o elemento imediatamente acima (antigo topo).

  /// Cria uma nova pilha vazia.
  static Pilha<T>* createPilha();

  /// Adiciona um valor ao topo da pilha.
  Pilha<T>* add(T& value);

  /// Remove o topo da pilha.
  /// @param deletar Indica se o nó removido deve ser desalocado.
  /// @return Retorna o novo topo da pilha.
  Pilha<T>* remove(bool deletar = true);

  /// Remove recursivamente todos os nós da pilha (de cima para baixo).
  void limpar();

private:
  /// Construtor interno usado para criar um nó com valor.
  Pilha(T& value, Pilha<T>* prev, Pilha<T>* next)
  : value(&value), prev(prev), next(next) { }

  /// Construtor de nó vazio (inicial).
  Pilha()
  : value(nullptr), prev(nullptr), next(nullptr) { }  
};

/// Cria e retorna uma nova pilha vazia.
template<typename T>
Pilha<T>* Pilha<T>::createPilha(){
  return new Pilha<T>();
}

/// Adiciona um valor ao topo da pilha.
/// Caso a pilha esteja vazia, apenas define o valor no nó atual.
/// Caso contrário, cria um novo nó acima, ligando os ponteiros.
template<typename T>
Pilha<T>* Pilha<T>::add(T& value){
  Pilha<T>* top = this;
  
  // Primeiro elemento da pilha
  if(top->value == nullptr){
    top->value = &value;
    return top;
  }
  
  // Encontra o topo verdadeiro (mais abaixo na pilha)
  while(top->prev != nullptr){
    top = top->prev;
  }

  // Cria novo nó como novo topo
  top->prev = new Pilha(value, nullptr, nullptr);
  top->prev->next = top;
  return top->prev; // Retorna o novo topo
}

/// Remove o topo da pilha e retorna o novo topo.
/// Caso deletar seja true, o nó atual será deletado da memória.
/// Caso seja o único elemento da pilha, esvazia o nó ao invés de deletar.
template<typename T>
Pilha<T>* Pilha<T>::remove(bool deletar){
  Pilha<T>* top = this;
  
  if(top == nullptr){
    return nullptr;
  }

  if(deletar){
    delete top;
  }

  // Atualiza ponteiros
  if(top->next != nullptr){
    top->next->prev = nullptr;
  }
  // Pilha com um único nó — apenas esvazia o valor
  else if(top->next == nullptr){
    top->value = nullptr;
    return top;
  }

  return top->next; // Novo topo
}

/// Limpa recursivamente todos os nós da pilha (de cima para baixo).
template<typename T>
void Pilha<T>::limpar(){
  Pilha<T>* top = this;
  
  if(top->next != nullptr){
    top->next->limpar();
  }
  
  delete top;
}

#endif
