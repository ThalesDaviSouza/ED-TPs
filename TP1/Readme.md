# Critério de escolha dos algoritmos:
1. Para vetores “quase"ordenados, o algoritmo inserção é mais rápido do que o algoritmo
quicksort. Nesse caso, você pode considerar como medida de ordenação de um vetor
o "número de quebras", ou seja, o "número de vezes que um elemento é menor que o
seu antecessor imediato". Note que se um vetor de tamanho n estiver inversamente
ordenado, o número de quebras é n − 1.

Números de quebras = número de vezes que um elemento é menor que o seu antecessor imediato
- Número de quebras = quantas antecessores um elemento é menor
Para o vetor [5 4 3 2 1] (inversamente ordenado), número de quebras = n-1 

2. Para vetores cujo tamanho seja menor que um limiar, o algoritmo inserção deve
ser mais eficiente que o quickSort recursivo. Utilize mediana de 3 para evitar casos
extremos de ineficiência do algoritmo.

- Vetor menor que um limiar -> Usar insertion
- Vetor maior que um limiar -> Usar quicksort com insertion e com mediana de 3

# Desafios:
- Determinar os valores para "limiarQuebras"
- "minTamParticao" ou "limiar de partição": Determinado pela estratégia de varredura apresentada na Figura 2.
  - A estratégia é a seguinte: começamos com 2 valores, 2 (minMPS ou valor mínimo partição) e tamanho do array (maxMPS ou tamanho máximo da partição). Definimos então de quanto em quanto que iremos andar pela fórmula "passoMPS = (maxMPS - minMPS)/5" (passoMPS). Então, serão encontradas 5 faixas de valores com custos diferentes. Após isso, o "limite da partição" será o menor custo que encontramos e calculamos a "nova faixa" e a "diferença do custo" (diffCusto = valor absoluto(custo[ minMPS ] - custo[ maxMPS ]), ou seja, valor do absoluto do (custo do valor mínimo (minMPS) - custo do valor máximo(maxMPS))). E então será repetido o processo até que a diffCusto seja menor que o limiar do custo passado na entrada ou até que número de passos (numMPS) seja menor que 5.
- Custo de ordenação será: f(comparacoes, moves, calls) = a∗comparacoes + b∗moves + c∗calls;

# Exemplo de entrada:
- 10 (lim de convergêcia)
- 0.012156 (valor de a)
- -0.00637855 (valor de b)
- 0.0172897 (valor de c)
- 1000 (tamanho do array)
- ... (valores do array que serão lidos, aparentemente inteiros)

# Exemplo de saída:
- iter 0 (número da iteração)
- mps 2 cost 118.428736100 cmp 11772 move 7904 calls 1489
- mps 201 cost 214.439538500 cmp 36789 move 36560 calls 25
- mps 400 cost 426.090159650 cmp 74149 move 74537 calls 10
- mps 599 cost 724.355621100 cmp 126188 move 126934 calls 4
- mps 798 cost 724.355621100 cmp 126188 move 126934 calls 4
- mps 997 cost 724.355621100 cmp 126188 move 126934 calls 4
- nummps 6 limParticao 2 mpsdiff 307.661438