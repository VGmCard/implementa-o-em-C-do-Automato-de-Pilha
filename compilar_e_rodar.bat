@echo off
cd /d "%~dp0"
echo ==================================================
echo       Compilando o Automato de Pilha C++
echo ==================================================
echo.
g++ -Iinclude src/AutomatoFinito.cpp src/Pilha.cpp src/AutomatoPilha.cpp src/main.cpp -o main.exe
if %errorlevel% neq 0 (
    echo.
    echo [ERRO] Falha na compilacao.
    echo Verifique se o compilador g++ esta no PATH.
    echo.
    pause
    exit /b %errorlevel%
)
echo [SUCESSO] Compilado com exito! Gerado: main.exe
echo.
echo ==================================================
echo             Executando os Testes
echo ==================================================
echo.
main.exe
echo.
echo ==================================================
echo               Fim da Execucao
echo ==================================================
echo.
pause
