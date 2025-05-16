# Critério de escolha dos algoritmos:
1. Para vetores “quase"ordenados, o algoritmo inserção é mais rápido do que o algoritmo
quicksort. Nesse caso, você pode considerar como medida de ordenação de um vetor
o "número de quebras", ou seja, o "número de vezes que um elemento é menor que o
seu antecessor imediato". Note que se um vetor de tamanho n estiver inversamente
ordenado, o número de quebras é n − 1.

- Números de quebras = número de vezes que um elemento é menor que o seu antecessor imediato
  - Número de quebras = quantas antecessores um elemento é menor
  - Para o vetor [5 4 3 2 1] (inversamente ordenado), número de quebras = n-1 

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
- Preparar o vetor com número controla de quebras: ordenar o vetor de entrada e em seguida aplicar um embaralhamento baseado na seed fornecida. 

# Exemplo de entrada:
- 10 (lim de convergêcia)
- 0.012156 (valor de a)
- -0.00637855 (valor de b)
- 0.0172897 (valor de c)
- 1000 (tamanho do array)
- ... (valores do array que serão lidos, aparentemente inteiros)

# Exemplo de saída:
### Primeiro, a calibragem do tamanho mínimo da partição
- iter 0 (número da iteração)
- mps 2 cost 118.428736100 cmp 11772 move 7904 calls 1489
- mps 201 cost 214.439538500 cmp 36789 move 36560 calls 25
- mps 400 cost 426.090159650 cmp 74149 move 74537 calls 10
- mps 599 cost 724.355621100 cmp 126188 move 126934 calls 4
- mps 798 cost 724.355621100 cmp 126188 move 126934 calls 4
- mps 997 cost 724.355621100 cmp 126188 move 126934 calls 4
- nummps 6 limParticao 2 mpsdiff 307.661438

### Posteriormente, a calibragem do número de quebras
- iter 0 (número da iteração)
- qs lq 1 cost 74.492674050 cmp 6891 move 1969 calls 190 (qs = quicksort)
- in lq 1 cost 4.183187050 cmp 1824 move 2823 calls 1 (in = insertion)
- qs lq 100 cost 87.210576300 cmp 8785 move 3544 calls 175
- in lq 100 cost 350.310216550 cmp 61734 move 62733 calls 1
- qs lq 199 cost 85.269510200 cmp 9265 move 4820 calls 196
- in lq 199 cost 612.098030950 cmp 107046 move 108045 calls 1
- qs lq 298 cost 94.594268350 cmp 10604 move 5853 calls 175
- in lq 298 cost 787.166320850 cmp 137348 move 138347 calls 1
- qs lq 397 cost 88.197632550 cmp 10509 move 6729 calls 195
- in lq 397 cost 946.415952650 cmp 164912 move 165911 calls 1
- qs lq 496 cost 89.009508850 cmp 11117 move 7755 calls 193
- in lq 496 cost 1048.855918600 cmp 182643 move 183642 calls 1
- numlq 6 limQuebras 1 lqdiff 607.914856