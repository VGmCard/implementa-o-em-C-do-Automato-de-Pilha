#ifndef PILHA_HPP
#define PILHA_HPP

class Pilha {
private:
    // Estrutura de nó para lista encadeada (alocação dinâmica de elementos da pilha)
    struct No {
        char dado;
        No* proximo;
        No(char d, No* prox) : dado(d), proximo(prox) {}
    };

    No* topo;

public:
    // Construtor
    Pilha();
    
    // Destrutor para limpar memória residual
    ~Pilha();

    // Adiciona um elemento no topo da pilha (push)
    void empilhar(char c);

    // Remove e retorna o elemento do topo (pop)
    char desempilhar();

    // Apenas lê o topo da pilha sem remover (peek/top)
    char ler_topo() const;

    // Retorna se a pilha está vazia
    bool vazia() const;

    // Remove todos os elementos da pilha
    void limpar();

    // Imprime o conteúdo da pilha (útil para debug visual)
    void mostrar() const;
};

#endif // PILHA_HPP
