# Algoritmos de Coleta Probe/Echo
Coleta de dados em uma rede

## À Saber
- Qual a ideia do algoritmo?
- O que muda entre árvore, grafo e outras topologias?
- Qual a ordem de eventos no algoritmo?

## Ideia
Obter informações sobre todo o grafo
- Difusão --> **Probe**
- Coleta (per-se) --> **Echo**

## Em Árvore
O que um nó "pensa":
- Pai é quem me enviou o Probe
- Repasso Probe aos meus filhos
    - Todos menos o pai
- Recebo Echo de cada filho
- Envio Echo ao meu pai
    - Contém informação dos filhos acumulada

## Em Grafo Geral
- Pela existência de ciclos, vizinhos de um nó podem já ter pai
- Se nó já tem pai mas recebe outro probe, devolve echo nulo.
- Número de mensagens:
    - Pai <--> Filho : 2
    - Vizinho <--> Vizinho : 4
    - Total : 2N + 4LA (links que não tem na spanning tree) = 2N + 4(E-N)
- Geração de spanning tree por relação pai/filho





# MAR - Modelo Assíncrono de Redes (Lynch)

## Conceitos 
- Processos multithread
    - Thread para sends
    - Thread para receives
    - Thread para "transições"
- Comunicação entre threads por buffers

## Estrutura
- *Signatures*
    - Declarações de métodos (transiç)
    - "Triggers"
    - Input e Output
- *States*
    - Variáveis de processo
    - Inicializações
- *Transitions*
    - Definições de métodos
    - Pré-condição e Effect 





# Instantâneos (Snapshot)
Gravar estados de um algoritmo em determinados momentos

## Utilidade
- Depuração
- Backups/versionamento
- Detecção de propriedades estáveis
- Cálculo de valores totais sobre SD

## Conceito
- **Estado Global**
    - Coleção de estados de todos os processos
    - Foto global obtida em um snapshot
    - Pode ser consistente ou inconsistente
- **Propriedade Estável**
    - Propriedade que se atingida, permanece verdadeira pra sempre
    - Terminação, bloqueio perpétuo etc
- Algoritmo (A) monitorado (B(A)) 
- Grafo G(B(A)) de processos Pi

## Funcionamento
- Consistente se coerente a transações de um sistema distribuído (exemplo banco - débito e crédito em uma conta)
- Foto simples: 
    - Baseado em difusão
    - Não consistente 
    - snap_i: ativa processo de snapshot em G
    - Nó iniciador não sabe que foto completou
- Chandy-Lamport
    - Canais de mensagem FIFO
    - Usa mensagens de marcas (markers) que dividem mensagens enviadas antes/depois de tempo t
    - Processo:
        1. Ao receber marker, salva seu estado (foto)
        2. Manda markers pra vizinhos
        3. Começa a gravas mensagens dos vizinhos
        3. Quando recebe marker de vizinho, para de gravá-lo
        4. Quando receber todos os markers, estado final é foto + gravações

## Complexidade
- Igual a geração assíncrona de Spanning Tree
- Espacional:   O(|E|)
- Temporal:     O(diam(I+D))
    - I: tempo para processar uma ação
    - D: tempo de envio de uma mensagem





# Java Threads

## À Saber
- O que são threads em java?
- Como instanciar?
- Como identificá-las?
- Tem variáveis de condição?
- Monitores
    - Synchronized (porque em métodos e não classe?)
    - Locks (implicitos e explícitos)
    - Bloqueio em fila? FIFO?
    - Quem continua a execução depois de notify()?
    - Synch vs Lock (quando pode trocar?)

## Thread vs Processo
- Vantagens de Threads
    - Mais rápidas (criação e chaveamento de ctx)
    - Mais leves (menos memória)
    - Compartilhamento de dados/objetos
- Desvantagens de Threads
    - Escopo limitado ao processo 

## Classe Thread em Java
- ``run()``
- ``setPriority()``
- ``start()``
- ``join()``

## Escalonamento
- JVM (potencialmente SO)
- Preemptivo
- Prioridades
    - recomendado não levar em conta ao programar
    - MAX_PRIORITY  (10)
    - NORM_PRIORITY (5)
    - MIN_PRIORITY  (1)

## Identificação
- Nome
    - Pode ser dado pelo usuário
    - Se não explicitado, dado pelo sistema
    - Pode ser duplicado
- Identificador
    - Atribuido pela JVM
    - ``t.getId()``
    - Único

## Criação
- Instanciar
    -``new Thread(new MyRunnable())``
        - Implement ``run()``
    - ``new MyThreadSubClass()``
        - Override ``run()``
- Rodar e Esperar
    - ``start()`` e ``join()``
    - Como Unix ``fork()`` e ``join()``





# Sincronização (Monitores)
- Monitores em java surgem implicitamente pelo uso do modificador  ``synchronized``
- Filas de bloqueio (lock) e espera (wait) não necessariamente são FIFO, depende da implementação

## Métodos Sincronizados
- Exclusão mútua sobre métodos marcados com ``synchronized``
- O lock implícito trava só os métodos synch, outros são livres
- Escopo do lock/monitor
    - Métodos de instância - cada objeto
    - Métodos estáticos - a classe toda
    - Pode haver lock da classe E locks de objetos

## Blocos Sincronizados
- Exclusão mútua sobre blocos marcados com ``synchronized(obj)``
- Lock/monitor explícito é o argumento
- *Pode ser* mais "eficiente" que por método, pela granularidade
- Escopo
    - Classe onde está o bloco, se argumento é static var dela
    - Objeto passado pro bloco, se argumento é uma instância qualquer
        - Afeta métodos e variáveis da instância passada (não estáticos)
        - Usar mesmo objeto nas diferentes threads à sincronizar    

## Primitivas wait/notify
- Métodos herdados da classe Object, de instância (não estáticos)
- Servem para evitar spinlock/busy-waiting em locks/monitores
- ``obj.wait()`` (só ``wait()`` usa this como monitor)
    - Chamada por thread que está com acesso ao monitor/lock
    - Libera o lock, permitindo execução de thread que está esperando
    - Thread atual espera indefinidamente* na fila do monitor até alguém usar ``obj.notify()`` ou ``obj.notifyAll()``
        - *Pode ser acordada por time-out (se foi chamada por ``obj.wait(time))``) ou ``t.interrupt()``
    - Geralmente usado para dormir enquanto uma condição não for satisfeita
- ``obj.notify()`` (só ``notify()`` usa this como monitor)
    - Acorda alguma thread dormindo no monitor (deu ``wait()``)
    - NÃO libera o lock!
    - Posteriormente, quando for liberado o lock, a thread acordada poderá obetê-lo (**não necessariamente**) 
    - ``obj.notifyAll()`` faz isso para todas as threads dormindo no monitor





# Sincronização (Barreiras, Trancas e Vars. Atômicas)
- ``java.util.concurrent.*``
- Motivação/benefícios do uso:
    - Poupam tempo de programação -> produtividade
    - Muito testadas e confiáveis
    - Ótimo desempenho (são da Oracle/do Java)

## Barreiras
- Classe CyclicBarrier
- Funcionamento
    - Bloqueia threads que dão ```bar.await()```
    - Quando chega **N**-ésima thread: 
        - Libera as N threads 
        - Se reinicia para novas N esperas
- Construtor ``CyclicBarrier(N, Runnable)``
- Método ``run()`` opcional 
    - Executa após última thread chegar, mas antes da liberação
    - Qualquer thread da barreira executa, mas pode ser escolhida
- Aplicações:
    - Cálculos paralelos sobre vetores, matrizes, grafos etc
    - Espera paralela por recursos a serem utilizados juntos (e.g. downloads)

## Trancas
- Classe CountDownLatch
- Construtor ``CountDownLatch(int countInitialValue)``
- Funcionamento
    - Similar a barreiras
    - **Contador** decrementado por ``latch.countDown()``
    - Se contador chega em zero:
        - Threads que deram ``latch.await()`` são liberadas 
        - Chamadas de ``latch.await()`` seguintes não bloqueiam
        - Não é reiniciado automaticamente
- Mais flexivel e trabalhosa (?) que CyclicBarrier

## Variáveis Atômicas
- Exclusão mútua sobre variáveis primitivas ou objetos
- Aritmética de alto desempenho e métodos compare-and-set
- Pacote ``java.util.concurrent.atomic``
- Tipos 
    - ``AtomicBoolean``
    - ``AtomicInteger``
    - ``AtomicLong``
    - ``AtomicReference``
- Métodos
    - ``get()``
    - ``set()``
    - ``boolean compareAndSet(expectedValue, updateValue)``
        - Se vale expected, altera para update e retorna true





# Algoritmos Paralelos
- Dividir problema em pedaços menores, paralelizáveis
- Aplicações
    - Modelagem de sistemas e simulações
    - Processamento de imagens
    - Inteligência artificial

## Notação
- **P**: problema computacional
- **n**: tamanho da entrada
- **T*(n)**: (melhor) complexidade sequencial
- **A**: algoritmo paralelo
- **Tp(n)**: complexidade (tempo) de A em *p* processadores

## Métricas
- **Tp(n)** : Tempo
    - Melhora com aumento de *p*, mas o ganho vai diminuindo
    - Mínimo: Tinf(n) (não necessariamente quando *p* -> inf)
- **Sp(n)** : Speedup (aceleração)
    - Sp(n) = T*(n)/Tp(n)
    - Idealmente perto de *p*
    - Afetado por comunicação, criação e sincronização de tarefas, acesso a recursos de HW escassos
    - Falta de tarefas para *p* cpus paralelas
    - Máximo: T1(n)/Tinf(n)
- **Ep(n)** : Eficiência
    - Ep(n) = T1(n)/[Tp(n) * *p*]
    - Efetiva utilização dos *p* processadores
    - Ideal é Ep(n) = 1
    - Máximo: Ep(n) <= T1(n)/[Tinf(n) * *p*]
    - Diminui depois que *p* > T1(n)/Tinf(n) (passou do speedup máximo)
- **Custo Total**
    - Tp(n) * *p*

## Modelos de Máquinas Paralelas
- Critérios
    - Implementabilidade
    - Simplicidade

### DAG (Directed Acyclic Graph)
- Entradas: nodos sem arcos de entrada (n)
- Saída: nodo sem arcos de saída
- Operação: arcos de entrada representam operandos (máx 2)
- Famílias de grafos similares
- Escalonamento
    - Qual cpu deve executar cada nó? Quando? 
    - Nós tem custo constante (e.g. 1)
    - Associar a cada nó *i*:
        - *ji* processador que executará o nó
        - *ti* tempo/momento no qual o nó será executado
    - Não pode haver nós com pares <*ji*, *ti*> iguais
    - Escalonamento é sequência de pares <*ji*, *ti*>
    - Ideia é minimizar max *ti*
- Complexidade: Tp(n) = min { max ti }
