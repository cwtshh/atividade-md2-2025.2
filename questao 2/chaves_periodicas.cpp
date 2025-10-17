// ═══════════════════════════════════════════════════════════
// Sincronização de Chaves Periódicas
// Matemática Discreta 2
// Alunos:
// - Gustavo Costa de Jesus
// - Iderlan Junio Cardoso da Silva
// ═══════════════════════════════════════════════════════════
#include <iostream>
#include <vector>

using namespace std;

long long mdc(long long a, long long b)
{
    long long resto;
    while (b != 0)
    {
        resto = a % b;
        a = b;
        b = resto;
    }

    return a;
}

long long mmc(long long a, long long b)
{
    return (a * b) / mdc(a, b);
}

// calcula o mmc do vetor de chaves
// calcula em pares, ou seja:
// mmc(c1,c2,c3,c4,... cn) = mmc(mmc(c1,c2),c3),c4)...cn)
long long calcularVariosMMC(vector<int> &ciclos)
{
    long long resultado = ciclos[0];
    for (size_t i = 1; i < ciclos.size(); i++)
    {
        resultado = mmc(resultado, ciclos[i]);
        if (resultado > 50)
        {
            return resultado;
        }
    }
    return resultado;
}

int main()
{
    int n;
    cout << "═══════════════════════════════════════════════════════════" << endl;
    cout << " Sincronização de Chaves Periódicas" << endl;
    cout << " Matemática Discreta 2" << endl;
    cout << " Alunos: " << endl;
    cout << " - Gustavo Costa de Jesus" << endl;
    cout << " - Iderlan Junio Cardoso da Silva" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    cout << "Digite o número de chaves periódicas: ( 1 ≤ n ≤ 10 ) " << endl;
    cin >> n;

    cout << "Digite os ciclos de ativação das chaves:" << endl;
    vector<int> ciclos(n);
    for (int i = 0; i < n; i++)
    {
        cin >> ciclos[i];
    }

    long long primeiroAno = calcularVariosMMC(ciclos);

    if (primeiroAno > 50)
    {
        cout << "Não é possível sincronizar todas as chaves dentro do limite de 50 anos." << endl;
    }
    else
    {
        cout << primeiroAno << endl;
    }

    return 0;
}