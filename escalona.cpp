#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

struct Task {
    int id;                  // Identificador
    int creation_time;       // Data de criação
    int duration;            // Duração necessária no processador
    int static_priority;     // Prioridade estática
    int dynamic_priority;    // Prioridade dinâmica (para envelhecimento)
    std::string state;       // Estado atual: "nova", "pronta", "rodando", "terminada"
    int executed_time = 0;   // Tempo já executado
    int quantum_time = 0;    // Tempo executado no quantum atual
    int start_time = -1;     // Tempo de início
    int end_time = -1;       // Tempo de conclusão
};

// Função para imprimir o cabeçalho do diagrama
void printHeader(int num_tasks) {
    std::cout << "tempo";
    for (int i = 1; i <= num_tasks; ++i) {
        std::cout << " P" << i;
    }
    std::cout << std::endl;
}

// Função para imprimir uma linha do diagrama
void printTimeline(int time, const std::vector<Task>& tasks) {
    std::cout << std::setw(4) << time << "-";
    for (const auto& task : tasks) {
        if (task.state == "rodando") {
            std::cout << " ##";
        } else if (task.state == "pronta") {
            std::cout << " --";
        } else {
            std::cout << "    ";
        }
    }
    std::cout << std::endl;
}

// Simulação básica (FCFS como exemplo)
void simulateFCFS(std::vector<Task>& tasks) {
    std::queue<Task*> ready_queue; // Fila de prontos
    Task* running_task = nullptr; // Tarefa em execução
    std::vector<Task*> finished_tasks;
    int t = 0; // Tempo atual
    int tmax = 100; // Tempo máximo da simulação (ajustar conforme necessário)

    printHeader(tasks.size());

    while (t < tmax) {
        // Verifica se há uma tarefa rodando e se ela terminou
        if (running_task) {
            if (running_task->executed_time == running_task->duration) {
                running_task->state = "terminada";
                running_task->end_time = t;
                finished_tasks.push_back(running_task);
                running_task = nullptr;
            }
        }

        // Insere novas tarefas na fila de prontos
        for (auto& task : tasks) {
            if (task.creation_time == t && task.state == "nova") {
                task.state = "pronta";
                ready_queue.push(&task);
            }
        }

        // Escalonamento: seleciona uma nova tarefa da fila de prontos se o processador estiver livre
        if (!running_task && !ready_queue.empty()) {
            running_task = ready_queue.front();
            ready_queue.pop();
            running_task->state = "rodando";
            if (running_task->start_time == -1) {
                running_task->start_time = t;
            }
        }

        // Atualiza o diagrama de tempo
        printTimeline(t, tasks);

        // Incrementa tempos
        if (running_task) {
            running_task->executed_time++;
        }
        t++;
    }

    // Calcula tempos médios
    double total_life_time = 0, total_wait_time = 0;
    for (const auto& task : tasks) {
        total_life_time += task.end_time - task.creation_time;
        total_wait_time += task.start_time - task.creation_time;
    }

    std::cout << "\nTempo médio de vida: " << total_life_time / tasks.size() << std::endl;
    std::cout << "Tempo médio de espera: " << total_wait_time / tasks.size() << std::endl;
    std::cout << "Número de trocas de contexto: " << finished_tasks.size() - 1 << std::endl;
}

int main() {
    // Lê dados da entrada padrão
    std::vector<Task> tasks;
    int creation_time, duration, priority;
    int id = 1;

    while (std::cin >> creation_time >> duration >> priority) {
        tasks.push_back({id++, creation_time, duration, priority, priority, "nova"});
    }

    // Executa a simulação (FCFS como exemplo inicial)
    simulateFCFS(tasks);

    return 0;
}
