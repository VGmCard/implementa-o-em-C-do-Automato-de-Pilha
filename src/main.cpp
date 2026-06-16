#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../include/AutomatoFinito.hpp"
#include "../include/AutomatoPilha.hpp"

// Função para carregar as palavras de um arquivo de texto
std::vector<std::string> carregar_fita(const std::string& nome_arquivo) {
    std::vector<std::string> palavras;
    std::ifstream arquivo(nome_arquivo);
    
    if (arquivo.is_open()) {
        std::string linha;
        while (arquivo >> linha) {
            // Ignora linhas vazias
            if (!linha.empty()) {
                palavras.push_back(linha);
            }
        }
        arquivo.close();
        std::cout << "[INFO] " << palavras.size() << " palavras carregadas de \"" << nome_arquivo << "\".\n\n";
    } else {
        std::cout << "[AVISO] Arquivo \"" << nome_arquivo << "\" nao encontrado. Usando palavras padrao.\n\n";
    }
    
    return palavras;
}

void testar_automato_finito(const std::vector<std::string>& testes) {
    std::cout << "==================================================\n";
    std::cout << "   TESTANDO: Autômato Finito Determinístico (AFD) \n";
    std::cout << "   Linguagem: Começa com 'a' e tem num par de 'b's\n";
    std::cout << "==================================================\n";

    // Estados: 
    // E0: Inicial
    // E1: Começou com 'a', par de 'b's (Aceitação)
    // E2: Começou com 'a', ímpar de 'b's
    // E3: Erro (Morte)
    bool aceitacao[4] = { false, true, false, false };

    // 4 estados, alfabeto tamanho 2 ('a' e 'b'), estado inicial 0
    AutomatoFinito afd(4, 2, 0, aceitacao);

    // Definição das transições
    afd.definir_transicao(0, 'a', 1);
    afd.definir_transicao(0, 'b', 3); // se começar com 'b', vai para o limbo (erro)

    afd.definir_transicao(1, 'a', 1); // continua com par de 'b'
    afd.definir_transicao(1, 'b', 2); // vai para ímpar de 'b'

    afd.definir_transicao(2, 'a', 2); // continua com ímpar de 'b'
    afd.definir_transicao(2, 'b', 1); // volta para par de 'b'

    for (const std::string& fita : testes) {
        std::cout << "Palavra: \"" << fita << "\"\n";
        bool result = afd.processar(fita.c_str());
        std::cout << "Resultado: " << (result ? "ACEITA" : "REJEITADA") << "\n";
        std::cout << "--------------------------------------------------\n";
    }
}

void testar_automato_pilha(const std::vector<std::string>& testes) {
    std::cout << "==================================================\n";
    std::cout << "       TESTANDO: Autômato de Pilha (AP)           \n";
    std::cout << "       Linguagem: a^n b^n (para n >= 1)           \n";
    std::cout << "==================================================\n";

    // Estados:
    // E0: Lendo 'a's e empilhando 'A's
    // E1: Lendo 'b's e desempilhando 'A's
    // E2: Estado de Aceitação (atingido via transição-epsilon)
    bool aceitacao[3] = { false, false, true };

    // 3 estados, inicial 0, símbolo inicial da pilha '$'
    AutomatoPilha ap(3, 0, '$', aceitacao);

    // Transições do AP:
    // 1. Lendo 'a's no estado 0: empilha 'A'
    ap.definir_transicao(0, 'a', '$', 0, 'E', 'A');
    ap.definir_transicao(0, 'a', 'A', 0, 'E', 'A');

    // 2. Primeiro 'b' lido no estado 0: desempilha um 'A' e vai para o estado 1
    ap.definir_transicao(0, 'b', 'A', 1, 'D');

    // 3. Continuando a ler 'b's no estado 1: desempilha 'A's
    ap.definir_transicao(1, 'b', 'A', 1, 'D');

    // 4. Se a fita acabou (epsilon/`\0`) e o topo for '$', vai para o estado de aceitação 2
    ap.definir_transicao(1, '\0', '$', 2, 'M'); 

    for (const std::string& fita : testes) {
        std::cout << "Testando palavra: \"" << fita << "\"\n";
        bool result = ap.processar(fita.c_str());
        std::cout << "Resultado final: " << (result ? "ACEITA" : "REJEITADA") << "\n";
        std::cout << "==================================================\n";
    }
}

int main() {
    // Tenta carregar as palavras a partir do arquivo fita.txt
    std::vector<std::string> testes = carregar_fita("fita.txt");
    
    // Se o arquivo estiver vazio ou não existir, usa uma lista padrão
    if (testes.empty()) {
        testes = { 
            "ab", "aabb", "aaabbb", "aaaabbbb", "aaaaabbbbb", 
            "aab", "abb", "aaabb", "b", "a", 
            "ba", "abba", "aba", "aaaaabbbb", "aaaabbbbb" 
        };
    }

    testar_automato_finito(testes);
    std::cout << "\n\n";
    testar_automato_pilha(testes);
    
    return 0;
}

