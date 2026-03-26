// Lucas Franco de Mello - Luk4w
// Grupo: RA1 10

#include <iostream>
#include <string>
#include <vector>

#include "cli_controller.hpp"
#include "fsm_scanner.hpp"
#include "rpn_evaluator.hpp"

using namespace std;

// Prototipos de funcao
void testarParseExpressao();
void exibirResultados();

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
    for (size_t i = 0; i < buffer_linhas.size(); ++i)
    {
        int status = parseExpressao(buffer_linhas[i], tokens_linha);
        if (status != 0)
        {
            cerr << "Erro lexico encontrado na linha " << i + 1 << endl;
        }
    }

    // testarParseExpressao();
    exibirResultados();

    return 0;
}

void testarParseExpressao()
{
    struct CasoTeste
    {
        string entrada;
        int statusEsperado;
        size_t tokensEsperados;
        string descricao;
    };

    vector<CasoTeste> testes = {
        // Entradas validas
        {"(3.14 2.0 +)", 0, 5, "Soma simples com reais"},
        {"(5 RES)", 0, 3, "Comando RES"},
        {"(10.5 CONTADOR)", 0, 5, "Comando STORE com identificador valido"},
        {"((CONTADOR) 2.0 *)", 0, 5, "Comando LOAD com identificador valido"},
        {"((1 2 +) 3 *)", 0, 9, "Expressao aninhada"},
        {"(10 3 //)", 0, 5, "Divisao inteira"},

        // Entradas invalidas
        {"(3.14 2.0 &)", 1, 0, "Caractere invalido '&'"},
        {"3.14.5", 1, 0, "Numero malformado (dois pontos)"},
        {"3,45", 1, 0, "Numero malformado (virgula)"},
        {"(10.5 BRASIL1)", 1, 0, "Comando STORE com identificador invalido (com numero colado no final)"},
        {"(10.5 123ABC +)", 1, 0, "Identificador STORE com identificador invalido (numeros colados no inicio)"},
        {"(10.5 ABC# +)", 1, 0, "Identificador invalido (caractere especial)"},
        {"(10.5 ABC DEF +)", 1, 0, "Identificador invalido (mais de um token)"},
        {"(10.5 ABC+)", 1, 0, "Identificador invalido (sem espaco)"}};

    cout << "\n--- Validacao parseExpressao ---\n";
    for (const auto &t : testes)
    {
        vector<string> tokens;
        int status = parseExpressao(t.entrada, tokens);

        if (status == t.statusEsperado)
        {
            cout << "[OK] " << t.descricao << endl;
        }
        else
        {
            cout << "[NOK] " << t.descricao
                 << " Esperado: " << t.statusEsperado
                 << ", Obtido: " << status << "\n";
        }
    }
}

void exibirResultados()
{
    cout << "\n--- Validacao executarExpressao ---\n";

    std::vector<double> historico;
    std::map<std::string, double> memoria;

    // Teste 1: Conta Simples
    std::vector<std::string> tokens1;
    parseExpressao("(10.0 2.0 +)", tokens1);
    executarExpressao(tokens1, historico, memoria);
    std::cout << "Teste 1 (10 2 +): " << (historico.back() == 12.0 ? "[OK]" : "[NOK]") << " -> " << historico.back() << "\n";

    // Teste 2: Memoria (Store e Load)
    std::vector<std::string> tokens2;
    parseExpressao("(42.0 X)", tokens2);
    executarExpressao(tokens2, historico, memoria);
    std::cout << "Teste 2a (42 X): " << (memoria["X"] == 42.0 ? "[OK]" : "[NOK]") << " -> " << memoria["X"] << "\n";

    std::vector<std::string> tokens3;
    parseExpressao("((X) 2.0 /)", tokens3);
    executarExpressao(tokens3, historico, memoria);
    std::cout << "Teste 2b ((X) 2 /): " << (historico.back() == 21.0 ? "[OK]" : "[NOK]") << " -> " << historico.back() << "\n";
    
    // Teste 3: Historico (RES)
    std::vector<std::string> tokens4;
    parseExpressao("(1 RES)", tokens4);
    executarExpressao(tokens4, historico, memoria);
    std::cout << "Teste 3 (1 RES): " << (historico.back() == 12.0 ? "[OK]" : "[NOK]") << " -> " << historico.back() << "\n";

    // Teste 4: Erro Lexico - forçado token invalido
    std::vector<std::string> tokens5 = {"10.0", "X+", "+"};
    std::cout << "Teste 4 (Identificador Invalido): ";
    if (executarExpressao(tokens5, historico, memoria) != 0)
    {
        std::cout << "[OK]\n";
    }
    else
    {
        std::cout << "[NOK]\n";
    }
}