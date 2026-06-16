#ifndef AUTOMATO_PILHA_HPP
#define AUTOMATO_PILHA_HPP

#include "Automato.hpp"
#include "Pilha.hpp"

class AutomatoPilha : public Automato {
private:
    // Estrutura que define uma regra de transição do AP
    struct Transicao {
        int estado_de;
        char simbolo_fita;      // Símbolo lido da fita ('a', 'b', etc.). '\0' indica transição-epsilon.
        char topo_pilha;        // Símbolo que precisa estar no topo da pilha (ex: '$', 'A').
        int estado_para;        // Próximo estado.
        char acao_pilha;        // 'E' = Empilhar, 'D' = Desempilhar, 'M' = Manter.
        char simbolo_empilhar;  // Símbolo a ser empilhado (caso a ação seja 'E').
    };

    int num_estados;
    bool* estados_aceitacao;

    // Pilha interna do autômato
    Pilha pilha;
    char simbolo_inicial_pilha;

    // Vetor dinâmico para armazenar as transições sem depender de std::vector ou std::map
    Transicao* transicoes;
    int capacidade_transicoes;
    int qtd_transicoes;

    // Redimensiona o vetor de transições dinamicamente se necessário
    void redimensionar_transicoes();

public:
    // Construtor
    AutomatoPilha(int n_estados, int inicial, char simb_inicial_pilha, const bool* aceitacao);
    
    // Destrutor
    ~AutomatoPilha() override;

    // Define uma transição no autômato
    void definir_transicao(int de_estado, char simbolo_fita, char topo_pilha, 
                           int para_estado, char acao_pilha, char simbolo_empilhar = '\0');

    // Executa a fita sobre o Autômato de Pilha
    bool processar(const char* fita) override;

    // Reseta o estado atual e a pilha
    void resetar() override;
};

#endif // AUTOMATO_PILHA_HPP
