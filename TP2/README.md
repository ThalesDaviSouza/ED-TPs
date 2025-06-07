# Contexto TP2
Deverá ser implementado um sistema logístico para facilitar a gestão dos Armazéns Hanoi.
- O sistema logístico recebe pedidos de envio de pacotes, que devem ser transportados e armazenados entre os armazéns
- O sistema deve rotear e acompanhar os pacotes durante esse processo
- Um pacote chega inicialmente a qualquer armazém e é destinado a algum outro armazém da rede.
- Ao chegar a um armazem o pacote recebe um número único (id) e é calculada a sua rota em termos de armazéns. Ou seja, ao chegar o pacote, salva nele a rota que ele deverá fazer até chegar ao seu destino.
- As ligações entre os armazéns podem ser vistas como um grafo não direcionado conhecido previamente (passado por parâmetro).
- A rota do pacote pode ser uma lista encadeada.
- Os armazéns são separados por seções, cada seção representa uma conexão com um armazém que ele esteja conectado no grafo.
- Cada seção tem uma lógica de pilha (LIFO) para os pacotes.
- Uma vez por dia os pacotes são transportados, com a prioridade para os que estão a mais tempo em trânsito (talvez ter uma int de prioridade no pacote para facilitar?)
- Tem um limite de quantos pacotes podem ser transportados por dia.

### Componentes necessário para SED:
Deve ser feita uma modelagem para simulação de eventos discretos baseado no modelo das 3 fases:
- Estado atual do sistema
- Relógio para controlar conseguir prosseguir para o próximo tempo de chamada de eventos
- Lista de eventos prioridados pelo momento em que ocorrem (fila de prioridade com skip list)
- Estatísticas para calculos (como tempo médio de atendimento)

### Tipos Abstratos de Dados:
- ### Pacote
  - Data hora da postagem (string?)
  - Nome Remetente
  - Nome Destinatário
  - Tipo:
    - None (Não foi postado)
    - Postado (Postagem)
    - Chegou (Chegada em armazém, mas não foi armazenado)
    - Armazenado (Armazenado em um armazém)
    - Alocado (Alocado para transporte)
    - Entregue
  - Armazém Origem
  - Armazém Destino
  - Armazém Atual (Ponteiro para o armazém atual da Rota)
  - Rota (lista encadeada)
    - Info (Armazém do nó)
    - Next (Próximo armazém)
    - Chegada (Momento em que chegou no armazém)
    - Partida (Momento em que deixou o armazém)
    - Espera (Diferença entre o tempo de chegada e o de saída)
    - TempoTransporte (Tempo que demorou para ser transportado até o próximo armazém)

- ### Armazém
  - Quantidade de Seções
  - Seções (lista de pilhas)
    - Pacotes (dentro de cada pilha) <br/>
  - *Obs.: Implementar função de *armazenar pacotes na pilha certa* e *recuperar pacote*.

- ### Transporte
  - Pactoes sendo transportados
  - *Obs.: talvez não precise virar um TAD.

- ### Escalonador
  - Fila de prioridade dos eventos (minHeap, sugestão do professor)
    - Cada Evento ter a seguinte lógica:
      - TipoEvento
        - PostagemPacote
        - ChegadaPacote
        - ArmazenamentoPacote (Inserção instantânea, custo 1)
        - AlocacaoPacote
        - EntregaPacote
  - Váriaveis de controle:
    - Data Hora referência
    - Hora próximo evento
  


# Entrada
Cada linha contém:
- Data hora da postagem (int, número de horas a partir de uma data de referêrencia)
- Nome Remetente
- Nome Destinatário
- Tipo
- Armazém Origem
- Armazém Destino

# Saída
Para cada pacote:
- Tempo esperado de estadia
- Tempo armazenado
- Tempo em trânsito