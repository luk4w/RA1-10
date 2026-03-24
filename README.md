# ASMNATOR

Lucas Franco de Mello
luk4w
RA1 10

> Devido a plataforma do github não permitir a criação de repositórios com espaços, o nome do grupo foi alterado automaticamente para RA1-10, no entanto, o nome real do grupo é RA1 10.

O **ASMNATOR** é a primeira fase do projeto da disciplina de `Linguagens Formais e Compiladores` ministrada pelo professor `Frank de Alcantara` na `Pontifícia Universidade Católica do Paraná`. Essa fase visa a construção de um `Analisador Léxico e Gerador de Assembly para ARMv7 (v16.1)`, que será simulado no [Cpulator](https://cpulator.01xz.net/?sys=arm-de1soc).

De modo geral, o programa vai processar algumas instruções em notação polonesa reversa (RPN) escritas em arquivos de texto: `teste1.txt`,`teste2.txt`,`teste3.txt`; e converter elas para código assembly, a partir de uma máquinas de estado finito (FSMs).

As instruções do professor determinam que o programa deve:

> 1. Ler um arquivo de texto contendo expressões aritméticas em Escritas RPN, segundo o formato especificado neste documento, com uma expressão por linha. Este arquivo contém o código do programa que será analisado pelo analisador léxico.
> 2. Analisar as expressões usando um analisador léxico baseado em Autômatos Finitos Determinísticos, com estados implementados por funções.
> 3. Transformar as expressões em um texto contendo o código Assembly para o Cpulator-ARMv7 DEC1-SOC(v16.1). As operações descritas no texto de entrada serão realizadas no Cpulator-ARMv7 DEC1-SOC(v16.1).
> 4. Garantir que o resultado do programa, ou as interações necessárias, sejam realizadas por meio das interfaces disponíveis no Cpulator-ARMv7 DEC1-SOC(v16.1) (display, leds, botões, chaves, etc.).
> 5. Hospedar o código, arquivos de teste e documentação em um repositório público no GitHub.
>
> — <cite>Prof. Frank de Alcantara</cite>

---

### Instruções de Compilação e Execução

A infraestrutura de *build* deste projeto é orquestrada pelo **CMake**, e garante uma compilação modular e reprodutível. Como o desenvolvimento tem como alvo principal o ambiente Windows, as instruções abaixo utilizam a *toolchain* do **MSVC** (Microsoft Visual C++) integrada ao **Visual Studio Code**.

### Pré-requisitos do Ambiente
Certifique-se de ter os seguintes componentes instalados:
* **Compilador:** Ferramentas de Build do Visual Studio Community 2022 (ou superior) com suporte para desenvolvimento em C++.
* **Editor:** Visual Studio Code.
* **Extensões (Visual Studio Code):**
  * `C/C++` (Microsoft)
  * `CMake Tools` (Microsoft)

### Metodo 1: Compilação via Visual Studio Code
A extensão [CMake Tools](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cmake-tools) automatiza o os comandos de configuração e construção, simplificando o processo. Siga os passos abaixo:

1. Abra a pasta raiz do projeto no Visual Studio Code (`File > Open Folder...`).
2. A extensão identificará o arquivo `CMakeLists.txt` então, através da paleta de comandos `Ctrl+Shift+p`, ou o atalho que você configurou, selecione um **Kit** de compilação, escolha a arquitetura nativa do MSVC (ex: `Visual Studio Community 2022 Release - x86_amd64`).
3. Aguarde o processo de configuração (*Configuring*) terminar. O CMake irá gerar a árvore de diretórios e o *cache* de compilação.
4. Utilize o atalho `Ctrl+Shift+p` para abrir a paleta de comandos, e execute `CMake: Build` para iniciar a compilação do projeto.
5. Se não houver erros, o executável final (`asmnator.exe`) será alocado dentro do diretório `build/Debug/` (ou `build/Release/`), dependendo da configuração selecionada.

### Metodo 2: Compilação via Terminal
Para compilar diretamente pelo Prompt de Comando, será necessário instalar o [CMake](https://cmake.org/download/) no sistema e garantir que ele esteja disponível no PATH. 
```shell
cmake -B build
cmake --build build --config Release
```
