// Lucas Franco de Mello - Luk4w
// Grupo: RA1 10

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // Validacao do numero de argumentos
    if (argc != 2) {
        cerr << "Numero de argumentos invalidos\n";
        cerr << "Uso: " << argv[0] << " <teste.txt>\n";
        return 1;
    }

    string arq = argv[1];

    // Validacao de extensao .txt
    if (arq.length() < 4 || arq.substr(arq.length() - 4) != ".txt") {
        cerr << "A extensao do arquivo de entrada deve ser .txt\n";
        return 1;
    }
    
    return 0;
}
