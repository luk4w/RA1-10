// Lucas Franco de Mello - Luk4w
// Grupo: RA1 10

#include <iostream>
#include <string>
#include <vector>

#include "cli_controller.hpp"
#include "fsm_scanner.hpp"

using namespace std;

void testarParseExpressao();

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
    vector<string> buffer_linhas;

    // Extrair os dados do arquivo e armazenar no buffer
    int status = lerArquivo(arq, buffer_linhas);
    if (status != 0)
    {
        cerr << "Falha ao ler o arquivo " << arq << "\n";
        return status;
    }

    // Extrair os tokens de cada linha individualmente
    vector<string> tokens_linha;
    for (size_t i = 0; i < buffer_linhas.size(); ++i) {
        int status = parseExpressao(buffer_linhas[i], tokens_linha);
        if (status != 0) {
            cerr << "Erro lexico encontrado na linha " << i + 1 << endl;
        }
    }


    return 0;
}


void testarParseExpressao() {
    struct CasoTeste {
        string entrada;
        int statusEsperado;
        size_t tokensEsperados;
        string descricao;
    };

    vector<CasoTeste> testes = {
        // Entradas validas
        {"(3.14 2.0 +)", 0, 5, "Soma simples com reais"},
        {"(5 RES)", 0, 3, "Comando especial RES"},
        {"(10.5 CONTADOR MEM)", 0, 5, "Comando MEM com identificador"},
        {"((1 2 +) 3 *)", 0, 9, "Expressao aninhada"},
        {"(10 3 //)", 0, 5, "Divisao inteira"},

        // Entradas invalidas
        {"(3.14 2.0 &)", 1, 0, "Caractere invalido '&'"},
        {"3.14.5", 1, 0, "Numero malformado (dois pontos)"},
        {"3,45", 1, 0, "Numero malformado (virgula)"}
    };

    cout << "\n--- Validacao ---\n";
    for (const auto& t : testes) {
        vector<string> tokens;
        int status = parseExpressao(t.entrada, tokens);

        if (status == t.statusEsperado) {
            cout << "[OK] " << t.descricao << endl;
        } else {
            cout << "[NOK] " << t.descricao 
                      << " Esperado: " << t.statusEsperado 
                      << ", Obtido: " << status << "\n";
        }
    }
}