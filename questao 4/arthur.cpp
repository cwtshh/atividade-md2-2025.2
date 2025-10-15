#include <iostream>

// metodo de mmc do Arthur corrigido
int mdcComPassos(int a, int b)
{
    int resto;
    while (b != 0)
    {
        resto = a % b;
        printf("Algoritmo de Euclides: %d mod %d = %d\n", a, b, resto);
        a = b;
        b = resto;
    }
    return a;
}

int inversoModular(int a, int m)
{
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    int A = a, B = m;

    mdcComPassos(a, m); // linha desnecessária, não é usada no cálculo

    while (m != 0)
    {
        q = a / m;
        t = m;
        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;

    printf("\nSubstituindo, temos que o inverso %d em %d é %d.\n\n", A, B, x1);

    return x1;
}

int powMod(int base, int exp, int mod)
{
    long long res = 1;
    long long b = base % mod;
    while (exp > 0)
    {
        if (exp & 1)
        {
            res = (res * b) % mod;
        }
        b = (b * b) % mod;
        exp >>= 1;
    }
    return (int)res;
}

int main()
{
    int H, G, Zn, x, n1;

    printf("Insira H: ");
    scanf("%d", &H);
    printf("Insira G: ");
    scanf("%d", &G);
    printf("Insira Zn: ");
    scanf("%d", &Zn);
    printf("Insira x: ");
    scanf("%d", &x);
    printf("Insira n1: ");
    scanf("%d", &n1);
    printf("\n");

    int inverso = inversoModular(n1, Zn);
    int a = (H * inverso) % Zn;

    printf("Fazendo a multiplicação modular: %d * %d mod %d = %d\n", H, inverso, Zn, a);
    printf(" Sendo %d o inverso de %d.\n", inverso, G);

    int resultado = powMod(a, x, n1);
    printf("Valor final da congruencia: %d\n", resultado);

    return 0;
}