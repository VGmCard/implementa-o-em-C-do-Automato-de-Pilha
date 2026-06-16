#include "../include/AutomatoPilha.hpp"
#include <iostream>

// Construtor
AutomatoPilha::AutomatoPilha(int n_estados, int inicial, char simb_inicial_pilha, const bool* aceitacao)
    : Automato(inicial), num_estados(n_estados), simbolo_inicial_pilha(simb_inicial_pilha) {
    
    // Aloca vetor de estados de aceitação
    estados_aceitacao = new bool[num_estados];
    for (int i = 0; i < num_estados; ++i) {
        estados_aceitacao[i] = aceitacao[i];
    }

    // Inicializa a pilha com o símbolo padrão
    pilha.empilhar(simbolo_inicial_pilha);

    // Inicializa o vetor de transições dinâmico
    capacidade_transicoes = 10;
    qtd_transicoes = 0;
    transicoes = new Transicao[capacidade_transicoes];
}

// Destrutor
AutomatoPilha::~AutomatoPilha() {
    delete[] estados_aceitacao;
    delete[] transicoes;
}

// Redimensionamento dinâmico do vetor de transições
void AutomatoPilha::redimensionar_transicoes() {
    capacidade_transicoes *= 2;
    Transicao* novo = new Transicao[capacidade_transicoes];
    for (int i = 0; i < qtd_transicoes; ++i) {
        novo[i] = transicoes[i];
    }
    delete[] transicoes;
    transicoes = novo;
}

// Reseta o autômato para o estado original
void AutomatoPilha::resetar() {
    Automato::resetar();
    pilha.limpar();
    pilha.empilhar(simbolo_inicial_pilha);
}

// Define uma nova regra de transição
void AutomatoPilha::definir_transicao(int de_estado, char simbolo_fita, char topo_pilha, 
                                     int para_estado, char acao_pilha, char simbolo_empilhar) {
    if (qtd_transicoes >= capacidade_transicoes) {
        redimensionar_transicoes();
    }
    
    transicoes[qtd_transicoes] = {
        de_estado,
        simbolo_fita,
        topo_pilha,
        para_estado,
        acao_pilha,
        simbolo_empilhar
    };
    qtd_transicoes++;
}

// Execução da fita no AP
bool AutomatoPilha::processar(const char* fita) {
    resetar(); // Garante o reinício do estado e da pilha

    std::cout << "[AP] Pilha Inicial: ";
    pilha.mostrar();
    std::cout << "\n";

    int i = 0;
    while (true) {
        char topo = pilha.ler_topo();
        char c = fita[i];

        int t_idx = -1;

        // 1. Tenta transição consumindo o caractere atual da fita
        if (c != '\0') {
            for (int t = 0; t < qtd_transicoes; ++t) {
                if (transicoes[t].estado_de == estado_atual &&
                    transicoes[t].simbolo_fita == c &&
                    transicoes[t].topo_pilha == topo) {
                    t_idx = t;
                    break;
                }
            }
        }

        bool consumiu_fita = false;
        if (t_idx != -1) {
            consumiu_fita = true;
        } else {
            // 2. Se não achou, tenta transição-epsilon (representada por '\0')
            for (int t = 0; t < qtd_transicoes; ++t) {
                if (transicoes[t].estado_de == estado_atual &&
                    transicoes[t].simbolo_fita == '\0' &&
                    transicoes[t].topo_pilha == topo) {
                    t_idx = t;
                    break;
                }
            }
        }

        // Se nenhuma transição foi encontrada
        if (t_idx == -1) {
            // Se chegamos ao fim da fita, podemos encerrar o processamento
            if (c == '\0') {
                break;
            }
            // Se ainda havia caracteres na fita, o autômato travou (rejeitado)
            std::cout << "[AP] Travou: Sem transicao para fita='" << c 
                      << "', topo='" << (topo ? topo : 'e') << "' no Estado " << estado_atual << "\n";
            return false;
        }

        // Aplica a transição encontrada
        Transicao t = transicoes[t_idx];
        
        std::cout << "[AP] E" << estado_atual << " | Lendo '" << (consumiu_fita ? c : 'e') 
                  << "' | Topo '" << (topo ? topo : 'e') << "' -> ";

        estado_atual = t.estado_para;

        // Modifica a pilha conforme a ação
        if (t.acao_pilha == 'D') {
            pilha.desempilhar();
        } else if (t.acao_pilha == 'E') {
            pilha.empilhar(t.simbolo_empilhar);
        }

        std::cout << "E" << estado_atual << " | Pilha: ";
        pilha.mostrar();
        std::cout << "\n";

        if (consumiu_fita) {
            i++;
        }
    }

    // Aceitação por estado final
    bool aceito = estados_aceitacao[estado_atual];
    std::cout << "[AP] Fim do processamento. Estado final: E" << estado_atual 
              << " | Pilha: ";
    pilha.mostrar();
    std::cout << " -> " << (aceito ? "ACEITO" : "REJEITADO") << "\n\n";

    return aceito;
}
