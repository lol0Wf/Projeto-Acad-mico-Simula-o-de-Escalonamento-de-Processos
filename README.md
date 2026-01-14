# Simulador de Escalonamento de Processos

Este projeto é um simulador de escalonamento de CPU desenvolvido para a disciplina de Sistemas Operacionais. O objetivo é reproduzir o comportamento de diferentes algoritmos de escalonamento e analisar métricas de desempenho de um conjunto de tarefas.

## O Projeto
O simulador lê uma lista de processos (contendo data de criação, duração e prioridade) e processa a execução conforme a política escolhida, gerando um diagrama de tempo e estatísticas de execução.

### Algoritmos Implementados:
* **FCFS (First Come, First Served):** Escalonamento por ordem de chegada.
* **SJF (Shortest Job First):** Prioriza tarefas com a menor duração.
* **PRIOp (Prioridade com Preempção):** Escala tarefas baseadas na prioridade estática, permitindo interrupções.
* **RR (Round-Robin):** Alternância por tempo (Quantum = 2), com e sem sistemas de prioridade/envelhecimento.

## Métricas de Saída
Para cada algoritmo, o simulador calcula e exibe:
1. **Tempo médio de vida:** Tempo total desde a criação até a conclusão.
2. **Tempo médio de espera:** Tempo em que a tarefa ficou na fila de prontos.
3. **Trocas de contexto:** Quantidade de vezes que o processador mudou de tarefa.
4. **Diagrama de Gantt (Vertical):** Representação visual da execução segundo a segundo.

---
*Desenvolvido como atividade prática para o curso de Ciência da Computação - IFPR.*
