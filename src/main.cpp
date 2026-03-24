// Lucas Franco de Mello - Luk4w
// Grupo: RA1 10

#include <iostream>
#include <string>
#include <vector>

#include "cli_controller.hpp"

using namespace std;

int main(int argc, char *argv[])
{
    // Validacao do numero de argumentos
    if (argc != 2)
    {
        cerr << "Numero de argumentos invalidos\n";
        cerr << "Uso: " << argv[0] << " <teste.txt>\n";
        return 1;
    }

    string arq = argv[1];

    // Validacao de extensao .txt
    if (arq.length() < 4 || arq.substr(arq.length() - 4) != ".txt")
    {
        cerr << "A extensao do arquivo de entrada deve ser .txt\n";
        return 1;
    }

    // Alocar memoria dinamica para o buffer de linhas
    std::vector<std::string> buffer_linhas;

    // Extrair os dados do arquivo e armazenar no buffer
    int status = lerArquivo(arq, buffer_linhas);
    if (status != 0)
    {
        std::cerr << "Falha ao ler o arquivo " << arq << "\n";
        return status;
    }

    return 0;
}
