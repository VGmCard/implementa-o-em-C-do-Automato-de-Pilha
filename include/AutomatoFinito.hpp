#ifndef AUTOMATO_FINITO_HPP
#define AUTOMATO_FINITO_HPP

#include "Automato.hpp"

class AutomatoFinito : public Automato {
private:
    int num_estados;
    int tam_alfabeto;
    int** matriz_transicoes;
    bool* estados_aceitacao;

    // Método auxiliar para converter caractere no índice da matriz de transição
    int obter_indice_simbolo(char c) const;

public:
    // Construtor
    AutomatoFinito(int n_estados, int t_alfabeto, int inicial, const bool* aceitacao);
    
    // Destrutor para liberação de memória
    ~AutomatoFinito() override;

    // Configura a tabela de transição
    void definir_transicao(int de_estado, char simbolo, int para_estado);

    // Sobrescreve o processamento da fita
    bool processar(const char* fita) override;
};

#endif // AUTOMATO_FINITO_HPP
