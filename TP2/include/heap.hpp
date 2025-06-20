#ifndef HEAP_HPP
#define HEAP_HPP

/// Macros auxiliares para comparação de chaves
#define ISBIGGER(x, y) (x > y ? true : false)
#define ISSMALLER(x, y) (x < y ? true : false)

/// Definição de um tipo mais legível para chaves grandes (utilizado como chave de ordenação dos eventos)
#define ULLI unsigned long long int

/// Representa um item armazenado dentro da Heap.
/// Cada item possui uma chave (usada para ordenação) e um valor genérico (template).
template<typename T>
class HeapItem{
public:
  ULLI chave;   ///< Chave usada para ordenar o item dentro da heap.
  T* value;     ///< Ponteiro para o objeto armazenado.

  HeapItem() : chave(-1), value(nullptr) { }

  /// Construtor que inicializa um HeapItem com chave e valor.
  HeapItem(ULLI chave, T* value)
  : chave(chave), value(value) { }
};

/// Implementa uma heap mínima (min-heap), usada para priorizar eventos.
/// A ordenação dos elementos é feita com base na menor chave.
template<typename T>
class Heap {
public:
  /// Construtor: recebe o tamanho máximo da heap.
  Heap(int maxsize);
  ~Heap();

  /// Insere um novo item na heap e reorganiza para manter a propriedade de heap mínima.
  void Inserir(HeapItem<T> item);

  /// Remove e retorna o item com menor chave (raiz da heap).
  HeapItem<T> Remover();

  /// Verifica se a heap está vazia.
  bool Vazio();

  HeapItem<T>* dados; ///< Vetor de itens armazenados na heap.

private:
  int tamanho;     ///< Número atual de elementos na heap.
  int maxSize;     ///< Tamanho máximo da heap.

  /// Retorna a posição do ancestral (pai) de um nó.
  int GetAncestralPos(int posicao);

  /// Retorna o ancestral do nó na posição fornecida.
  HeapItem<T> GetAncestral(int posicao);

  /// Retorna a posição do filho à esquerda.
  int GetSucessorEsqPos(int posicao);

  /// Retorna o filho à esquerda.
  HeapItem<T> GetSucessorEsq(int posicao);

  /// Retorna a posição do filho à direita.
  int GetSucessorDirPos(int posicao);

  /// Retorna o filho à direita.
  HeapItem<T> GetSucessorDir(int posicao);

  /// Sobe o item recém-inserido até sua posição correta para manter a propriedade da heap (heapify bottom-up).
  void HeapifyPorBaixo(int posicao);

  /// Desce o item da raiz após remoção até sua posição correta (heapify top-down).
  void HeapifyPorCima(int posicao);
};

/// Construtor: inicializa heap com capacidade máxima e aloca o vetor.
template<typename T>
Heap<T>::Heap(int maxsize){
  this->tamanho = 0;
  this->maxSize = maxsize;
  this->dados = new HeapItem<T>[maxsize];
}

/// Destrutor: libera o vetor alocado.
template<typename T>
Heap<T>::~Heap(){
  delete[] dados;
}

/// Insere novo item e reorganiza a heap para manter a ordenação.
template<typename T>
void Heap<T>::Inserir(HeapItem<T> item) {
  if (tamanho >= maxSize) {
    return;
  }

  dados[tamanho] = item;
  HeapifyPorBaixo(tamanho);
  tamanho++;
}

/// Remove o item com menor chave (topo da heap) e reorganiza os elementos.
template<typename T>
HeapItem<T> Heap<T>::Remover() {
  if(Vazio()) {
    return dados[0];
  }

  HeapItem<T> retorno = dados[0];
  dados[0] = dados[tamanho - 1];
  tamanho--;

  HeapifyPorCima(0);

  return retorno;
}

/// Verifica se a heap está vazia.
template<typename T>
bool Heap<T>::Vazio() {
  return tamanho == 0;
}

/// Função recursiva para manter a ordem da heap após inserção (bottom-up).
template<typename T>
void Heap<T>::HeapifyPorBaixo(int posicao) {
  int posAncestral = GetAncestralPos(posicao);

  if (posAncestral >= 0 && dados[posAncestral].chave > dados[posicao].chave) {
    HeapItem<T> aux = dados[posicao];
    dados[posicao] = dados[posAncestral];
    dados[posAncestral] = aux;
    HeapifyPorBaixo(posAncestral);
  }
}

/// Função recursiva para manter a ordem da heap após remoção (top-down).
template<typename T>
void Heap<T>::HeapifyPorCima(int posicao) {
  int menor = posicao;

  int esquerdo = GetSucessorEsqPos(posicao);
  int direito = GetSucessorDirPos(posicao);

  if (esquerdo < tamanho && dados[esquerdo].chave < dados[menor].chave) {
    menor = esquerdo;
  }

  if (direito < tamanho && dados[direito].chave < dados[menor].chave) {
    menor = direito;
  }

  if (menor != posicao) {
    HeapItem<T> aux = dados[posicao]; 
    dados[posicao] = dados[menor];
    dados[menor] = aux;
    
    HeapifyPorCima(menor);
  }
}

/// Retorna a posição do ancestral (pai) de um nó na heap.
template<typename T>
int Heap<T>::GetAncestralPos(int posicao) {
  return (posicao - 1) / 2;
}

/// Retorna o ancestral de um nó.
template<typename T>
HeapItem<T> Heap<T>::GetAncestral(int posicao) {
  return dados[GetAncestralPos(posicao)];
}

/// Retorna a posição do filho esquerdo.
template<typename T>
int Heap<T>::GetSucessorEsqPos(int posicao) {
  return posicao * 2 + 1;
}

/// Retorna o filho esquerdo.
template<typename T>
HeapItem<T> Heap<T>::GetSucessorEsq(int posicao) {
  return dados[GetSucessorEsqPos(posicao)];
}

/// Retorna a posição do filho direito.
template<typename T>
int Heap<T>::GetSucessorDirPos(int posicao) {
  return posicao * 2 + 2;
}

/// Retorna o filho direito.
template<typename T>
HeapItem<T> Heap<T>::GetSucessorDir(int posicao) {
  return dados[GetSucessorDirPos(posicao)];
}

#endif
