# Como Compilar e Rodar o Projeto

Este manual explica como instalar o compilador C++ (`g++`) e rodar o projeto de Autômatos tanto no **Windows** quanto no **Linux**.

---

## 💻 1. Configuração no Windows

Siga os passos abaixo para instalar e configurar o compilador localmente:

### Passo 1: Instalar o MSYS2
Abra o **PowerShell** como administrador e execute:
```powershell
winget install MSYS2.MSYS2
```
*(Siga as instruções padrão de instalação dele na tela).*

### Passo 2: Instalar a Toolchain (g++ e make)
Assim que a instalação terminar, abra o terminal do **MSYS2** (procure por "MSYS2" no menu Iniciar do Windows) e execute:
```bash
pacman -S --noconfirm mingw-w64-x86_64-gcc mingw-w64-x86_64-make
```

### Passo 3: Adicionar o compilador ao PATH do Windows
Para que o terminal reconheça o comando `g++` de qualquer pasta:
1. Pressione a tecla **Windows** e digite `editar as variáveis de ambiente do sistema` e aperte Enter.
2. Clique no botão **Variáveis de Ambiente...** (canto inferior direito).
3. Na seção **Variáveis de Usuário** (ou do sistema), selecione a variável **Path** e clique em **Editar...**.
4. Clique em **Novo** e cole o seguinte caminho:
   ```text
   C:\msys64\mingw64\bin
   ```
5. Clique em **OK** em todas as janelas para salvar as alterações.
6. Feche e abra o seu VS Code ou terminal para recarregar as configurações.

### Passo 4: Executar os Testes
Com o compilador configurado, abra o terminal na pasta do projeto e rode o script:
```powershell
.\compilar_e_rodar.bat
```
*(Ou dê dois cliques diretamente no arquivo `compilar_e_rodar.bat` pelo Explorador de Arquivos).*

---

## 🐧 2. Configuração no Linux

No Linux, a instalação e execução são muito mais diretas:

### Passo 1: Instalar o compilador (`g++`)
Abra o terminal do seu Linux (Debian, Ubuntu e derivados) e execute:
```bash
sudo apt update
sudo apt install -y build-essential
```
*(Para distribuições Fedora/RedHat use `sudo dnf groupinstall "Development Tools"`, e no Arch Linux use `sudo pacman -S base-devel`).*

### Passo 2: Executar os Testes
Abra o terminal na pasta do projeto e execute os seguintes comandos:
```bash
# Dar permissão de execução ao script
chmod +x compilar_e_rodar.sh

# Executar a compilação e os testes
./compilar_e_rodar.sh
```

---

## 🚀 3. Alternativa Online (Sem Instalar Nada)

Caso queira testar o código imediatamente sem instalar nada no seu computador:
1. Abra o arquivo [single_file_test.cpp](single_file_test.cpp) e copie todo o seu conteúdo.
2. Acesse um compilador online como o [OnlineGDB (C++)](https://www.onlinegdb.com/).
3. Cole o código no editor e clique no botão **Run** no topo da tela.
