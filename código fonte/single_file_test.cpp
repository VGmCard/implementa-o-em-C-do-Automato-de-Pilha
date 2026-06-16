#include <iostream>

// ============================================================================
// 1. CLASSE BASE: Automato
// ============================================================================
class Automato {
protected:
    int estado_inicial;
    int estado_atual;

public:
    Automato(int inicial) : estado_inicial(inicial), estado_atual(inicial) {}
    virtual ~Automato() {}

    virtual void resetar() {
        estado_atual = estado_inicial;
    }

    virtual bool processar(const char* fita) = 0;

    int obter_estado_atual() const {
        return estado_atual;
    }
};

// ============================================================================
// 2. CLASSE: AutomatoFinito (AFD)
// ============================================================================
class AutomatoFinito : public Automato {
private:
    int num_estados;
    int tam_alfabeto;
    int** matriz_transicoes;
    bool* estados_aceitacao;

    int obter_indice_simbolo(char c) const {
        if (c == 'a') return 0;
        if (c == 'b') return 1;
        return -1;
    }

public:
    AutomatoFinito(int n_estados, int t_alfabeto, int inicial, const bool* aceitacao)
        : Automato(inicial), num_estados(n_estados), tam_alfabeto(t_alfabeto) {
        
        estados_aceitacao = new bool[num_estados];
        for (int i = 0; i < num_estados; ++i) {
            estados_aceitacao[i] = aceitacao[i];
        }

        matriz_transicoes = new int*[num_estados];
        for (int i = 0; i < num_estados; ++i) {
            matriz_transicoes[i] = new int[tam_alfabeto];
            for (int j = 0; j < tam_alfabeto; ++j) {
                matriz_transicoes[i][j] = -1;
            }
        }
    }
    
    ~AutomatoFinito() override {
        delete[] estados_aceitacao;
        for (int i = 0; i < num_estados; ++i) {
            delete[] matriz_transicoes[i];
        }
        delete[] matriz_transicoes;
    }

    void definir_transicao(int de_estado, char simbolo, int para_estado) {
        int idx = obter_indice_simbolo(simbolo);
        if (de_estado >= 0 && de_estado < num_estados && idx != -1) {
            matriz_transicoes[de_estado][idx] = para_estado;
        }
    }

    bool processar(const char* fita) override {
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
};

// ============================================================================
// 3. ESTRUTURA: Pilha Dinâmica Didática
// ============================================================================
class Pilha {
private:
    struct No {
        char dado;
        No* proximo;
        No(char d, No* prox) : dado(d), proximo(prox) {}
    };
    No* topo;

public:
    Pilha() : topo(nullptr) {}
    ~Pilha() { limpar(); }

    void empilhar(char c) {
        topo = new No(c, topo);
    }

    char desempilhar() {
        if (vazia()) return '\0';
        No* temp = topo;
        char valor = temp->dado;
        topo = topo->proximo;
        delete temp;
        return valor;
    }

    char ler_topo() const {
        if (vazia()) return '\0';
        return topo->dado;
    }

    bool vazia() const { return topo == nullptr; }

    void limpar() {
        while (!vazia()) desempilhar();
    }

    void mostrar() const {
        if (vazia()) {
            std::cout << "(Pilha Vazia)";
            return;
        }
        No* atual = topo;
        while (atual != nullptr) {
            std::cout << "[" << atual->dado << "]";
            if (atual->proximo != nullptr) std::cout << " -> ";
            atual = atual->proximo;
        }
    }
};

// ============================================================================
// 4. CLASSE: AutomatoPilha (AP)
// ============================================================================
class AutomatoPilha : public Automato {
private:
    struct Transicao {
        int estado_de;
        char simbolo_fita;
        char topo_pilha;
        int estado_para;
        char acao_pilha;
        char simbolo_empilhar;
    };

    int num_estados;
    bool* estados_aceitacao;
    Pilha pilha;
    char simbolo_inicial_pilha;

    Transicao* transicoes;
    int capacidade_transicoes;
    int qtd_transicoes;

    void redimensionar_transicoes() {
        capacidade_transicoes *= 2;
        Transicao* novo = new Transicao[capacidade_transicoes];
        for (int i = 0; i < qtd_transicoes; ++i) {
            novo[i] = transicoes[i];
        }
        delete[] transicoes;
        transicoes = novo;
    }

public:
    AutomatoPilha(int n_estados, int inicial, char simb_inicial_pilha, const bool* aceitacao)
        : Automato(inicial), num_estados(n_estados), simbolo_inicial_pilha(simb_inicial_pilha) {
        
        estados_aceitacao = new bool[num_estados];
        for (int i = 0; i < num_estados; ++i) {
            estados_aceitacao[i] = aceitacao[i];
        }

        pilha.empilhar(simbolo_inicial_pilha);

        capacidade_transicoes = 10;
        qtd_transicoes = 0;
        transicoes = new Transicao[capacidade_transicoes];
    }
    
    ~AutomatoPilha() override {
        delete[] estados_aceitacao;
        delete[] transicoes;
    }

    void resetar() override {
        Automato::resetar();
        pilha.limpar();
        pilha.empilhar(simbolo_inicial_pilha);
    }

    void definir_transicao(int de_estado, char simbolo_fita, char topo_pilha, 
                           int para_estado, char acao_pilha, char simbolo_empilhar = '\0') {
        if (qtd_transicoes >= capacidade_transicoes) {
            redimensionar_transicoes();
        }
        transicoes[qtd_transicoes] = {
            de_estado, simbolo_fita, topo_pilha, para_estado, acao_pilha, simbolo_empilhar
        };
        qtd_transicoes++;
    }

    bool processar(const char* fita) override {
        resetar();
        std::cout << "[AP] Pilha Inicial: ";
        pilha.mostrar();
        std::cout << "\n";

        int i = 0;
        while (true) {
            char topo = pilha.ler_topo();
            char c = fita[i];
            int t_idx = -1;

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
                for (int t = 0; t < qtd_transicoes; ++t) {
                    if (transicoes[t].estado_de == estado_atual &&
                        transicoes[t].simbolo_fita == '\0' &&
                        transicoes[t].topo_pilha == topo) {
                        t_idx = t;
                        break;
                    }
                }
            }

            if (t_idx == -1) {
                if (c == '\0') break;
                std::cout << "[AP] Travou: Sem transicao para fita='" << c 
                          << "', topo='" << (topo ? topo : 'e') << "' no Estado " << estado_atual << "\n";
                return false;
            }

            Transicao t = transicoes[t_idx];
            std::cout << "[AP] E" << estado_atual << " | Lendo '" << (consumiu_fita ? c : 'e') 
                      << "' | Topo '" << (topo ? topo : 'e') << "' -> ";

            estado_atual = t.estado_para;

            if (t.acao_pilha == 'D') {
                pilha.desempilhar();
            } else if (t.acao_pilha == 'E') {
                pilha.empilhar(t.simbolo_empilhar);
            }

            std::cout << "E" << estado_atual << " | Pilha: ";
            pilha.mostrar();
            std::cout << "\n";

            if (consumiu_fita) i++;
        }

        bool aceito = estados_aceitacao[estado_atual];
        std::cout << "[AP] Fim do processamento. Estado final: E" << estado_atual << " -> " 
                  << (aceito ? "ACEITO" : "REJEITADO") << "\n\n";
        return aceito;
    }
};

// ============================================================================
// 5. TESTES E MAIN
// ============================================================================
void testar_automato_finito() {
    std::cout << "==================================================\n";
    std::cout << "   TESTANDO: Autômato Finito Determinístico (AFD) \n";
    std::cout << "   Linguagem: Começa com 'a' e tem num par de 'b's\n";
    std::cout << "==================================================\n";

    bool aceitacao[4] = { false, true, false, false };
    AutomatoFinito afd(4, 2, 0, aceitacao);

    afd.definir_transicao(0, 'a', 1);
    afd.definir_transicao(0, 'b', 3);
    afd.definir_transicao(1, 'a', 1);
    afd.definir_transicao(1, 'b', 2);
    afd.definir_transicao(2, 'a', 2);
    afd.definir_transicao(2, 'b', 1);

    const char* testes[] = { "a", "abb", "abbbb", "ab", "abbb", "b", "aba" };
    for (const char* fita : testes) {
        std::cout << "Palavra: \"" << fita << "\"\n";
        bool result = afd.processar(fita);
        std::cout << "Resultado: " << (result ? "ACEITA" : "REJEITADA") << "\n";
        std::cout << "--------------------------------------------------\n";
    }
}

void testar_automato_pilha() {
    std::cout << "==================================================\n";
    std::cout << "       TESTANDO: Autômato de Pilha (AP)           \n";
    std::cout << "       Linguagem: a^n b^n (para n >= 1)           \n";
    std::cout << "==================================================\n";

    bool aceitacao[3] = { false, false, true };
    AutomatoPilha ap(3, 0, '$', aceitacao);

    ap.definir_transicao(0, 'a', '$', 0, 'E', 'A');
    ap.definir_transicao(0, 'a', 'A', 0, 'E', 'A');
    ap.definir_transicao(0, 'b', 'A', 1, 'D');
    ap.definir_transicao(1, 'b', 'A', 1, 'D');
    ap.definir_transicao(1, '\0', '$', 2, 'M'); 

    const char* testes[] = { "ab", "aabb", "aaabbb", "aab", "abb", "aaabb", "b", "a" };
    for (const char* fita : testes) {
        std::cout << "Testando palavra: \"" << fita << "\"\n";
        bool result = ap.processar(fita);
        std::cout << "Resultado final: " << (result ? "ACEITA" : "REJEITADA") << "\n";
        std::cout << "==================================================\n";
    }
}

int main() {
    testar_automato_finito();
    std::cout << "\n\n";
    testar_automato_pilha();
    return 0;
}
