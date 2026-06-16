#!/bin/bash
cd "$(dirname "$0")"
echo "=================================================="
echo "      Compilando o Automato de Pilha C++ - Linux"
echo "=================================================="
echo ""

g++ -Iinclude src/AutomatoFinito.cpp src/Pilha.cpp src/AutomatoPilha.cpp src/main.cpp -o main

if [ $? -ne 0 ]; then
    echo ""
    echo "[ERRO] Falha na compilacao."
    echo "Verifique se o compilador g++ esta instalado."
    echo ""
    exit 1
fi

echo "[SUCESSO] Compilado com exito! Gerado: ./main"
echo ""
echo "=================================================="
echo "             Executando os Testes"
echo "=================================================="
echo ""

./main

echo ""
echo "=================================================="
echo "               Fim da Execucao"
echo "=================================================="
echo ""
