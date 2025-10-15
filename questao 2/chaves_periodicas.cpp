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
    cin >> n;

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