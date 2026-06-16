#include "../include/AutomatoFinito.hpp"
#include <iostream>

// Construtor
AutomatoFinito::AutomatoFinito(int n_estados, int t_alfabeto, int inicial, const bool* aceitacao)
    : Automato(inicial), num_estados(n_estados), tam_alfabeto(t_alfabeto) {
    
    // Aloca vetor de estados de aceitação
    estados_aceitacao = new bool[num_estados];
    for (int i = 0; i < num_estados; ++i) {
        estados_aceitacao[i] = aceitacao[i];
    }

    // Aloca a matriz de transições bidimensional
    matriz_transicoes = new int*[num_estados];
    for (int i = 0; i < num_estados; ++i) {
        matriz_transicoes[i] = new int[tam_alfabeto];
        // Inicializa tudo com -1 (indicando sem transição/erro)
        for (int j = 0; j < tam_alfabeto; ++j) {
            matriz_transicoes[i][j] = -1;
        }
    }
}

// Destrutor
AutomatoFinito::~AutomatoFinito() {
    delete[] estados_aceitacao;
    for (int i = 0; i < num_estados; ++i) {
        delete[] matriz_transicoes[i];
    }
    delete[] matriz_transicoes;
}

// Mapeamento simples de caracteres para índices da matriz
int AutomatoFinito::obter_indice_simbolo(char c) const {
    if (c == 'a') return 0;
    if (c == 'b') return 1;
    return -1; // Símbolo fora do alfabeto
}

// Configura uma transição na matriz
void AutomatoFinito::definir_transicao(int de_estado, char simbolo, int para_estado) {
    int idx = obter_indice_simbolo(simbolo);
    if (de_estado >= 0 && de_estado < num_estados && idx != -1) {
        matriz_transicoes[de_estado][idx] = para_estado;
    }
}

// Processamento da cadeia
bool AutomatoFinito::processar(const char* fita) {
    resetar();
    
    int i = 0;
    while (fita[i] != '\0') {
        char c = fita[i];
        int idx_simbolo = obter_indice_simbolo(c);

        if (idx_simbolo == -1) {
            std::cout << "[AFD] Erro: Símbolo '" << c << "' inválido.\n";
            return false;
        }

        int proximo = matriz_transicoes[estado_atual][idx_simbolo];
        if (proximo == -1) {
            std::cout << "[AFD] Travou: Sem transição para '" << c << "' no Estado " << estado_atual << "\n";
            return false;
        }

        estado_atual = proximo;
        i++;
    }

    return estados_aceitacao[estado_atual];
}
