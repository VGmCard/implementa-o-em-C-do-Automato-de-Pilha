@echo off
chcp 65001 > nul
echo ==================================================
echo       Compilando o Automato de Pilha (C++)       
echo ==================================================
echo.

:: Executa o comando de compilação do g++ incluindo a pasta "include" e todos os arquivos .cpp da "src"
g++ -Iinclude src/AutomatoFinito.cpp src/Pilha.cpp src/AutomatoPilha.cpp src/main.cpp -o main.exe

if %errorlevel% neq 0 (
    echo.
    echo [ERRO] Falha na compilação.
    echo Verifique se o compilador g++ (GCC/MinGW) está instalado e adicionado ao PATH do Windows.
    echo.
    pause
    exit /b %errorlevel%
)

echo [SUCESSO] Compilado com êxito! Gerado: main.exe
echo.
echo ==================================================
echo             Executando os Testes                 
echo ==================================================
echo.

:: Executa o arquivo binário gerado
main.exe

echo.
echo ==================================================
echo               Fim da Execução                    
echo ==================================================
echo.
pause
