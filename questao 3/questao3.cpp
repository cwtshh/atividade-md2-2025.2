#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct FatorPrimo
{
    int primo;
    int expoente;
};

vector<FatorPrimo> fatorizacao(int n)
{
    vector<FatorPrimo> fatores;
    // Fatoração por tentativa de divisão
    if (n % 2 == 0)
    {
        int expoente = 0;
        while (n % 2 == 0)
        {
            expoente++;
            n /= 2;
        }
        fatores.push_back({2, expoente});
    }

    // Testar fatores ímpares
    for (int i = 3; i <= sqrt(n); i += 2)
    {
        if (n % i == 0)
        {
            int expoente = 0;
            while (n % i == 0)
            {
                expoente++;
                n /= i;
            }
            fatores.push_back({i, expoente});
        }
    }

    // Se n ainda for maior que 1, então é primo
    if (n > 1)
    {
        fatores.push_back({n, 1});
    }

    return fatores;
}

int calcularTau(const vector<FatorPrimo> &fatores)
{
    int tau = 1;
    cout << "\nCálculo de τ(N):" << endl;
    cout << "τ(N) = ";

    for (long unsigned int i = 0; i < fatores.size(); i++)
    {
        int termo = fatores[i].expoente + 1;
        tau *= termo;

        cout << "(" << fatores[i].expoente << "+1)";
        if (i < fatores.size() - 1)
            cout << " × ";
    }

    cout << " = " << tau << endl;
    return tau;
}

long long calcularSigma(const vector<FatorPrimo> &fatores)
{
    long long sigma = 1;
    cout << "\nCálculo de σ(N):" << endl;
    cout << "σ(N) = ";

    for (long unsigned int i = 0; i < fatores.size(); i++)
    {
        int p = fatores[i].primo;
        int a = fatores[i].expoente;

        long long numerador = pow(p, a + 1) - 1;
        long long denominador = p - 1;
        long long termo = numerador / denominador;

        sigma *= termo;

        cout << "(" << p << "^" << (a + 1) << " - 1)/(" << p << " - 1)";
        if (i < fatores.size() - 1)
            cout << " × ";
    }

    cout << " = " << sigma << endl;
    return sigma;
}

int main()
{
    int n;

    cout << "═══════════════════════════════════════════════════════════" << endl;
    cout << "A razão da eficiencia de um número" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    cout << "Digite um número inteiro positivo: ( 1 ≤ n ≤ 105 ) " << endl;
    cin >> n;

    cout << "\nCálculo da razão da eficiência de " << n << "!" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    vector<FatorPrimo> fatores = fatorizacao(n);

    cout << "\nFatoração prima de " << n << ":" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;
    cout << " = ";
    for (long unsigned int i = 0; i < fatores.size(); i++)
    {
        cout << fatores[i].primo;
        if (fatores[i].expoente > 1)
        {
            cout << "^" << fatores[i].expoente;
        }
        if (i < fatores.size() - 1)
            cout << " × ";
    }
    cout << endl;

    cout << "\nFatores primos e expoentes:" << endl;
    for (const auto &fator : fatores)
    {
        cout << "  p = " << fator.primo << ", expoente = " << fator.expoente << endl;
    }

    int tau = calcularTau(fatores);
    long long sigma = calcularSigma(fatores);

    // Cálculo da razão da eficiência
    // double para maior precisão
    double razao = (double)sigma / tau;
    cout << "═══════════════════════════════════════════════════════════" << endl;
    cout << "\nRazão da eficiência σ(N)/τ(N) = " << sigma << " / " << tau << " = " << razao << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    // Configurar cout para mostrar ponto flutuante com precisão
    cout << "\nRazão da eficiência com duas casas decimais: " << endl;
    cout << "RazaoEficiencia(N) = ";
    cout << fixed << setprecision(2) << razao << endl;

    return 0;
}