#ifndef HEAP_HPP
#define HEAP_HPP

#define ISBIGGER(x, y) (x > y ? true : false)
#define ISSMALLER(x, y) (x < y ? true : false)
#define ULLI unsigned long long int

template<typename T>
class HeapItem{
public:
  ULLI chave;
  T* value;

  HeapItem() : chave(-1), value(nullptr) { }
  HeapItem(ULLI chave, T* value)
  : chave(chave), value(value) { }

};

template<typename T>
class Heap {
public:
  Heap(int maxsize);
  ~Heap();

  void Inserir(HeapItem<T> item);
  HeapItem<T> Remover();
  HeapItem<T>* dados;

  bool Vazio();
  
private:
  int tamanho;
  int maxSize;

  int GetAncestralPos(int posicao);
  HeapItem<T> GetAncestral(int posicao);
  int GetSucessorEsqPos(int posicao);
  HeapItem<T> GetSucessorEsq(int posicao);
  int GetSucessorDirPos(int posicao);
  HeapItem<T> GetSucessorDir(int posicao);

  void HeapifyPorBaixo(int posicao);
  void HeapifyPorCima(int posicao);
};



template<typename T>
Heap<T>::Heap(int maxsize){
  this->tamanho = 0;
  this->maxSize = maxsize;
  this->dados = new HeapItem<T>[maxsize];
}

template<typename T>
Heap<T>::~Heap(){
  delete[] dados;
}

template<typename T>
void Heap<T>::Inserir(HeapItem<T> item) {
  if (tamanho >= maxSize) {
    return;
  }

  dados[tamanho] = item;
  HeapifyPorBaixo(tamanho);
  tamanho++;
}

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

template<typename T>
bool Heap<T>::Vazio() {
  return tamanho == 0;
}

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


template<typename T>
int Heap<T>::GetAncestralPos(int posicao) {
  return (posicao - 1) / 2;
}

template<typename T>
HeapItem<T> Heap<T>::GetAncestral(int posicao) {
  return dados[GetAncestralPos(posicao)];
}

template<typename T>
int Heap<T>::GetSucessorEsqPos(int posicao) {
  return posicao * 2 + 1;
}

template<typename T>
HeapItem<T> Heap<T>::GetSucessorEsq(int posicao) {
  return dados[GetSucessorEsqPos(posicao)];
}

template<typename T>
int Heap<T>::GetSucessorDirPos(int posicao) {
  return posicao * 2 + 2;
}

template<typename T>
HeapItem<T> Heap<T>::GetSucessorDir(int posicao) {
  return dados[GetSucessorDirPos(posicao)];
}

#endif