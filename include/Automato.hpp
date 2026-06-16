#ifndef AUTOMATO_HPP
#define AUTOMATO_HPP

class Automato {
protected:
    int estado_inicial;
    int estado_atual;

public:
    Automato(int inicial) : estado_inicial(inicial), estado_atual(inicial) {}
    virtual ~Automato() {}

    // Reseta o autômato para o estado inicial
    virtual void resetar() {
        estado_atual = estado_inicial;
    }

    // Processa uma palavra (fita) e retorna se foi aceita
    virtual bool processar(const char* fita) = 0;

    // Retorna o estado em que o autômato se encontra no momento
    int obter_estado_atual() const {
        return estado_atual;
    }
};

#endif // AUTOMATO_HPP
