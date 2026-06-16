#include "../include/Pilha.hpp"
#include <iostream>

// Construtor
Pilha::Pilha() : topo(nullptr) {}

// Destrutor
Pilha::~Pilha() {
    limpar();
}

// Empilha (Push)
void Pilha::empilhar(char c) {
    topo = new No(c, topo);
}

// Desempilha (Pop)
char Pilha::desempilhar() {
    if (vazia()) {
        return '\0'; 
    }
    No* temp = topo;
    char valor = temp->dado;
    topo = topo->proximo;
    delete temp;
    return valor;
}

// Visualiza o Topo (Peek)
char Pilha::ler_topo() const {
    if (vazia()) {
        return '\0';
    }
    return topo->dado;
}

// Verifica se está vazia
bool Pilha::vazia() const {
    return topo == nullptr;
}

// Limpa toda a pilha
void Pilha::limpar() {
    while (!vazia()) {
        desempilhar();
    }
}

// Imprime a pilha do topo para a base
void Pilha::mostrar() const {
    if (vazia()) {
        std::cout << "(Pilha Vazia)";
        return;
    }
    No* atual = topo;
    while (atual != nullptr) {
        std::cout << "[" << atual->dado << "]";
        if (atual->proximo != nullptr) {
            std::cout << " -> ";
        }
        atual = atual->proximo;
    }
}
