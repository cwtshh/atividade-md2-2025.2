#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

struct bezout
{
    long long x;
    long long y;
    long long mdc;
};

// verificar se é primo
bool ePrimo(long long n)
{
    if (n <= 1)
        return false;
    for (long long i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}
// calcular mdc por euclides
long long mdc(long long a, long long b)
{
    // a = b * q + r
    long long resto;

    cout << "Calculo do MDC usando Algoritmo de Euclides" << endl;
    cout << "===============================" << endl;
    cout << " a = b * q + r" << endl;
    cout << "===============================" << endl;
    // enquanto o resto for diferente de 0
    while (b != 0)
    {
        resto = a % b;

        // logs pra mostrar o processo
        cout << a << " = " << b << " * " << a / b << " + " << resto << endl;

        a = b;
        b = resto;
    }

    return a;
}
// Implementaçã0 do método p de Pollard
long long pDePollard(long long n)
{

    cout << "Implementação do método p de Pollard" << endl;
    cout << "===============================" << endl;

    // caso seja numero par
    if (n % 2 == 0)
    {
        cout << "\n  N é par, fator trivial encontrado: 2" << endl;
        return 2;
    }

    // se n for primo
    if (ePrimo(n))
    {
        cout << "\n  N = " << n << " é primo!" << endl;
        return n;
    }

    long long x0 = 2; // semente
    cout << "1) n = " << n << endl;
    cout << "2) Semente x0 = 2" << endl;

    vector<long long> sequencia; // vetor de x
    sequencia.push_back(x0);

    unsigned int a = 1;

    long long xk = x0; // xk = (xk^2 + 1) mod n

    // setw para formatar a saída
    cout << "   " << left << setw(10) << "k"
         << setw(15) << "xₖ"
         << setw(20) << "xₖ² + " << a
         << setw(15) << "xₖ₊₁ mod N" << endl;
    cout << "   " << string(60, '-') << endl;
    cout << "   " << left << setw(10) << 0
         << setw(15) << x0
         << setw(20) << "-"
         << setw(15) << "-" << endl;

    int max_seq = 20; // Limitar visualização
    for (int k = 0; k < max_seq; k++)
    {
        long long fxk = xk * xk + a;
        xk = fxk % n;
        sequencia.push_back(xk);

        cout << "   " << left << setw(10) << (k + 1)
             << setw(15) << xk
             << setw(20) << fxk
             << setw(15) << xk << endl;
    }

    // encontrar um fator d de n que D < N, D != 1, D|N
    cout << "Encontrar fator D de N garantindo D << N, D ≠ 1, D|N" << endl;
    cout << "   D = mdc(|xⱼ - xᵢ|, N), onde xᵢ ≡ xⱼ (mod D), xᵢ ≠ xⱼ, i < j" << endl
         << endl;

    cout << "   " << left << setw(8) << "i"
         << setw(8) << "j"
         << setw(12) << "xᵢ"
         << setw(12) << "xⱼ"
         << setw(15) << "|xⱼ - xᵢ|"
         << setw(15) << "D=mdc(...,N)" << endl;
    cout << "   " << string(70, '-') << endl;

    long long d = 1;
    int iteracoes = 0;
    const int ITERACOES_MAX = 1000; // limitar o número de iterações

    long long xi = 0, xj = 0;

    while (d == 1 && iteracoes < ITERACOES_MAX)
    {
        // avanca na sequencia
        xi = ((xi * xi) % n + a) % n;

        // avanca duas vezes na sequencia
        xj = ((xj * xj) % n + a) % n;
        xj = ((xj * xj) % n + a) % n;

        long long diff = abs(xj - xi);
        d = mdc(diff, n);
        iteracoes++;

        // mostrar o processo
        if (iteracoes <= 15 || d > 1)
        {
            cout << "   " << left << setw(8) << iteracoes
                 << setw(8) << (2 * iteracoes)
                 << setw(12) << xi
                 << setw(12) << xj
                 << setw(15) << diff
                 << setw(15) << d << endl;
        }
        else if (iteracoes == 16)
        {
            cout << "   ... (continuando iterações) ...\n";
        }

        if (d == n)
        {
            cout << "\n   ✗ Falha: D = N (divisor trivial)\n";
            cout << "   Tente outra semente ou outro polinômio\n";
            return -1;
        }
    }

    if (iteracoes >= ITERACOES_MAX)
    {
        cout << "\n   ✗ Número excessivo de iterações!\n";
        return -1;
    }

    long long p = d;
    long long q = n / d;

    cout << "════════════════════════════════════════════════════════════" << endl;
    cout << "  RESULTADO DA FATORAÇÃO\n";
    cout << "════════════════════════════════════════════════════════════" << endl
         << endl;

    cout << "n = " << n << endl;
    cout << "p = " << p << endl;

    cout << "  Verificação: " << p << " × " << q << " = " << (p * q);
    if (p * q == n)
        cout << " ✓\n";
    else
        cout << " ✗ ERRO!\n";

    cout << "\n  ∴ " << n << " = " << p << " × " << q << "\n\n";

    return d;
}
// encontrar expoente publico E
long long encontrarEPublico(long long phi_n)
{
    cout << "\n════════════════════════════════════════════════════════════\n";
    cout << "  ESCOLHA DO EXPOENTE PÚBLICO E\n";
    cout << "════════════════════════════════════════════════════════════\n\n";

    cout << "Requisitos para E:\n";
    cout << "  1) E > 1\n";
    cout << "  2) E < φ(n) = " << phi_n << "\n";
    cout << "  3) mdc(E, φ(n)) = 1 (E e φ(n) são coprimos)\n\n";

    cout << "Buscando o menor E que satisfaz as condições:\n\n";
    cout << "  " << left << setw(10) << "E"
         << setw(20) << "mdc(E, φ(n))"
         << setw(15) << "Válido?" << endl;
    cout << "  " << string(45, '-') << endl;

    // Começar de E = 2 e testar cada número
    for (long long E = 2; E < phi_n; E++)
    {
        long long d = mdc(E, phi_n);
        bool valido = (d == 1);

        // Mostrar os primeiros 20 candidatos ou até encontrar
        if (E <= 20 || valido)
        {
            cout << "  " << left << setw(10) << E
                 << setw(20) << d
                 << setw(15) << (valido ? "✓ SIM" : "✗ Não") << endl;
        }

        // Retornar o primeiro E válido (menor)
        if (valido)
        {
            cout << "\n  ✓ Menor expoente público encontrado: E = " << E << "\n";
            return E;
        }
    }

    cout << "\n  ✗ Erro: Nenhum E válido encontrado!\n";
    return -1;
}
// Algoritmo de Euclides Estendido para encontrar x, y tais que a*x + b*y = mdc(a, b)
bezout euclidesEstendido(long long a, long long b)
{
    cout << "\n════════════════════════════════════════════════════════════" << endl;
    cout << "  ALGORITMO DE EUCLIDES ESTENDIDO\n";
    cout << "════════════════════════════════════════════════════════════" << endl
         << endl;

    cout << "Buscando inteiros x e y tais que:" << endl;
    cout << "  a * x + b * y = mdc(a, b)" << endl
         << endl;

    cout << "Tabela de execução:\n\n";
    cout << "  " << left << setw(10) << "a"
         << setw(10) << "b"
         << setw(10) << "q"
         << setw(10) << "r"
         << setw(10) << "x"
         << setw(10) << "y" << endl;
    cout << "  " << string(60, '-') << endl;

    // valores iniciais
    long long x0 = 1, x1 = 0;
    long long y0 = 0, y1 = 1;
    long long a_orig = a, b_orig = b;

    while (b != 0)
    {
        long long q = a / b;
        long long r = a % b;

        // Atualizar x e y
        long long x_temp = x0 - q * x1;
        long long y_temp = y0 - q * y1;

        cout << "  " << left << setw(10) << a
             << setw(10) << b
             << setw(10) << q
             << setw(10) << r
             << setw(10) << x0
             << setw(10) << y0 << endl;

        // Avançar
        a = b;
        b = r;
        x0 = x1;
        y0 = y1;
        x1 = x_temp;
        y1 = y_temp;
    }

    // a agora contém o mdc
    bezout resultado;
    resultado.mdc = a;
    resultado.x = x0;
    resultado.y = y0;

    cout << "\n  Resultado:\n";
    cout << "    mdc(" << a_orig << ", " << b_orig << ") = " << resultado.mdc << "\n";
    cout << "    " << a_orig << " × (" << resultado.x << ") + "
         << b_orig << " × (" << resultado.y << ") = " << resultado.mdc << "\n";

    // Verificação
    long long verificacao = a_orig * resultado.x + b_orig * resultado.y;
    cout << "\n  Verificação: " << a_orig << " × " << resultado.x
         << " + " << b_orig << " × " << resultado.y
         << " = " << verificacao << " ";

    if (verificacao == resultado.mdc)
        cout << "✓\n";
    else
        cout << "✗ ERRO!\n";

    return resultado;
}
// calcular inverso modular de e mod phi_n
long long inversoModular(long long e, long long a)
{
    cout << "════════════════════════════════════════════════════════════" << endl;
    cout << "  CÁLCULO DO INVERSO MODULAR\n";
    cout << "════════════════════════════════════════════════════════════" << endl
         << endl;

    cout << "Buscando d tal que:" << endl;
    cout << "  d * e ≡ 1 (mod φ(n))" << endl
         << endl;

    bezout resultado = euclidesEstendido(e, a);

    if (resultado.mdc != 1)
    {
        cout << "  ✗ Erro: e e φ(n) não são coprimos, inverso modular não existe!\n";
        return -1;
    }

    long long d = resultado.x;

    if (d < 0)
    {
        cout << "D inicial negativo, ajustando para positivo somando φ(n):\n";
        d = (d % a + a) % a; // Ajustar d para ser positivo
        if (d < 0)
            d += a; // Garantir que d seja positivo
        cout << "  d ajustado: " << d << "\n";
    }

    cout << "\n════════════════════════════════════════════════════════════\n";
    cout << "  EXPOENTE PRIVADO ENCONTRADO\n";
    cout << "════════════════════════════════════════════════════════════\n\n";

    cout << "  D = " << d << "\n\n";

    // Verificação final
    long long verificacao = (d * e) % a;
    cout << "  Verificação: D × E mod φ(n) = " << d << " × " << e
         << " mod " << a << " = " << verificacao << " ";

    if (verificacao == 1)
        cout << "✓\n";
    else
        cout << "✗ ERRO!\n";

    return d;
}

long long exponenciacaoModular(long long m, long long e, long long n)
{
    cout << "═══════════════════════════════════════════════════════════════" << endl;
    cout << "  ALGORITMO DE EXPONENCIAÇÃO MODULAR (m^e mod n)" << endl;
    cout << "═══════════════════════════════════════════════════════════════" << endl
         << endl;

    long long resultado = 1;
    long long base = m % n;
    long long expoente = e;

    cout << "Calculando " << m << "^" << e << " mod " << n << ":\n";

    cout << left << setw(8) << "Passo"
         << setw(10) << "Exp"
         << setw(15) << "Base"
         << setw(15) << "Resultado" << endl;
    cout << string(70, '-') << endl;

    int passo = 0;

    cout << left << setw(8) << passo
         << setw(10) << expoente
         << setw(15) << base
         << setw(15) << resultado << " (inicial)" << endl;

    passo++;

    while (expoente > 0)
    {
        bool impar = (expoente % 2 == 1);

        cout << left << setw(8) << passo
             << setw(10) << expoente
             << setw(15) << base;

        if (impar)
        {
            long long resultado_antigo = resultado;
            resultado = (resultado * base) % n;
            cout << setw(15) << base
                 << setw(15) << resultado;
            cout << " ← (" << resultado_antigo << " × " << base << ") mod " << n << endl;
        }
        else
        {
            cout << setw(15) << base
                 << setw(15) << resultado << endl;
        }

        expoente = expoente / 2;

        if (expoente > 0)
        {
            long long base_antiga = base;
            base = (base * base) % n;
            cout << "         └─> base² = (" << base_antiga << "² mod " << n << ") = " << base << endl;
        }

        passo++;
    }

    cout << "\n✓ Resultado final: " << m << "^" << e << " mod " << n << " = " << resultado << endl;
    cout << "═══════════════════════════════════════════════════════════\n"
         << endl;

    return resultado;
}

vector<long long> criptografar(const vector<int> &codigos, long long e, long long n)
{
    vector<long long> blocos;

    cout << "\n═══════════════════════════════════════════════════════════" << endl;
    cout << "  CODIFICAÇÃO (CRIPTOGRAFIA RSA)" << endl;
    cout << "  Fórmula: C ≡ M^e (mod n)" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    cout << "\nChave Pública: (e, n) = (" << e << ", " << n << ")" << endl;
    cout << "Para cada bloco M: C = M^" << e << " mod " << n << "\n"
         << endl;

    cout << "───────────────────────────────────────────────────────────" << endl;
    cout << "RESUMO DOS BLOCOS" << endl;
    cout << "───────────────────────────────────────────────────────────" << endl;

    cout << "\n"
         << left << setw(10) << "Bloco"
         << setw(12) << "M"
         << setw(20) << "Operação"
         << setw(15) << "C (cifrado)" << endl;
    cout << string(57, '-') << endl;

    // Loop pelos códigos
    for (size_t i = 0; i < codigos.size(); i++)
    {
        long long M = codigos[i]; // ← CORRIGIDO: era 'codigods'
        long long C;

        cout << left << setw(10) << (i + 1)
             << setw(12) << M
             << setw(20) << (to_string(M) + "^" + to_string(e) + " mod " + to_string(n))
             << flush;

        // Calcular C = M^e mod n
        cout << endl;
        C = exponenciacaoModular(M, e, n);

        // Repetir linha do resumo após o cálculo detalhado
        cout << left << setw(10) << (i + 1)
             << setw(12) << M
             << setw(20) << (to_string(M) + "^" + to_string(e) + " mod " + to_string(n))
             << setw(15) << C << " ✓" << endl;

        blocos.push_back(C);
    }

    // ← MOVIDO PARA FORA DO LOOP!
    cout << "\n═══════════════════════════════════════════════════════════" << endl;
    cout << "MENSAGEM CIFRADA" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    cout << "\nBlocos cifrados: ";
    for (size_t i = 0; i < blocos.size(); i++)
    {
        cout << blocos[i];
        if (i < blocos.size() - 1)
            cout << " ";
    }
    cout << "\n"
         << endl;

    return blocos;
}

vector<int> descriptografar(const vector<long long> &criptografado, long long d, long long n)
{
    vector<int> descriptografado;

    cout << "\n═══════════════════════════════════════════════════════════" << endl;
    cout << "  DECODIFICAÇÃO (DESCRIPTOGRAFIA RSA)" << endl;
    cout << "  Fórmula: M ≡ C^d (mod n)" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    cout << "\nChave Privada: (d, n) = (" << d << ", " << n << ")" << endl;
    cout << "Para cada bloco cifrado C: M = C^" << d << " mod " << n << "\n"
         << endl;

    cout << "───────────────────────────────────────────────────────────" << endl;
    cout << "RESUMO DOS BLOCOS" << endl;
    cout << "───────────────────────────────────────────────────────────" << endl;

    cout << "\n"
         << left << setw(10) << "Bloco"
         << setw(15) << "C (cifrado)"
         << setw(25) << "Operação"
         << setw(20) << "M (código)" << endl;
    cout << string(70, '-') << endl;

    for (size_t i = 0; i < criptografado
                               .size();
         i++)
    {
        long long C = criptografado[i];
        long long M;

        cout << left << setw(10) << (i + 1)
             << setw(15) << C
             << setw(25) << (to_string(C) + "^" + to_string(d) + " mod " + to_string(n))
             << flush;

        // Calcular M = C^d mod n
        cout << endl;
        M = exponenciacaoModular(C, d, n);

        // Repetir linha do resumo
        cout << left << setw(10) << (i + 1)
             << setw(15) << C
             << setw(25) << (to_string(C) + "^" + to_string(d) + " mod " + to_string(n))
             << setw(20) << M << " ✓" << endl;

        descriptografado.push_back((int)M);
    }

    cout << "\n═══════════════════════════════════════════════════════════" << endl;
    cout << "BLOCOS DECODIFICADOS" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    cout << "\nCódigos recuperados: ";
    for (size_t i = 0; i < descriptografado.size(); i++)
    {
        cout << setfill('0') << setw(2) << descriptografado[i];
        if (i < descriptografado.size() - 1)
            cout << " ";
    }
    cout << setfill(' ') << "\n"
         << endl;

    return descriptografado;
}

char codigo_para_char(int codigo)
{
    if (codigo == 0)
        return ' ';
    else if (codigo >= 11 && codigo <= 36)
        return 'A' + (codigo - 11);
    else
        return '?'; // Código inválido
}

string reconverterMensagem(const vector<int> &codigos)
{
    cout << "\n═══════════════════════════════════════════════════════════" << endl;
    cout << "  RECONVERSÃO: CÓDIGOS → CARACTERES" << endl;
    cout << "  Sistema: 11=A, 12=B, ..., 36=Z, 00=Espaço" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    string mensagem = "";

    cout << "\n"
         << left << setw(15) << "Código"
         << setw(15) << "Caractere" << endl;
    cout << string(30, '-') << endl;

    for (int codigo : codigos)
    {
        char c = codigo_para_char(codigo);
        mensagem += c;

        cout << left << setw(15) << setfill('0') << setw(2) << codigo << setfill(' ')
             << setw(15) << (c == ' ' ? "[ESPAÇO]" : string(1, c)) << endl;
    }

    cout << "\n───────────────────────────────────────────────────────────" << endl;
    cout << "Mensagem recuperada: \"" << mensagem << "\"" << endl;
    cout << "───────────────────────────────────────────────────────────" << endl;

    return mensagem;
}

int main()
{
    long long n1, n2;

    cout << "═══════════════════════════════" << endl;
    cout << " Criptografia RSA" << endl;
    cout << "═══════════════════════════════" << endl;
    cout << " Matemática Discreta 2" << endl;
    cout << " Alunos: " << endl;
    cout << " - Gustavo Costa de Jesus" << endl;
    cout << " - Iderlan Junio Cardoso da Silva" << endl;
    cout << "═══════════════════════════════" << endl;

    // etapa 1
    cout << "Digite dois números compostos distintos (pelo menos 3 dígitos): " << endl;
    cout << "Os números devem ser produto de primos distintos para que o método p de Pollard seja eficiente." << endl;
    cout << "Digite no formato: n1 n2" << endl;
    cin >> n1 >> n2;
    cout << "Você digitou os números " << n1 << " e " << n2 << endl;
    cout << endl
         << endl;

    // n1 e n2 devem ser entre 100 e 9999
    if (n1 < 100 || n1 > 9999 || n2 < 100 || n2 > 9999)
    {
        cout << "Erro: Os números devem estar entre 100 e 9999." << endl;
        return 1;
    }

    long long p = pDePollard(n1);
    long long q = pDePollard(n2);

    cout << "\n═══════════════════════════════════════════════════════════\n\n";

    // etapa 2

    // calculo do modulo
    long long n = p * q;

    // totiente de euler
    long long z = (p - 1) * (q - 1);

    cout << "Cálculo do módulo n e do totiente de Euler z" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;
    cout << "  n = p × q = " << p << " × " << q << " = " << n << endl;
    cout << "  z = (p - 1) × (q - 1) = " << (p - 1) << " × " << (q - 1) << " = " << z << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    // definir expoente E publico
    long long e = encontrarEPublico(z);
    if (e == -1)
    {
        return 1;
    }

    long long d = inversoModular(e, z);
    if (d == -1)
    {
        cout << "Erro ao calcular o inverso modular." << endl;
        return 1;
    }

    cout << "═══════════════════════════════════════════════════════════" << endl;
    cout << "  CHAVES PÚBLICA E PRIVADA" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl
         << endl;

    cout << "  Chave Pública: (e, n) = (" << e << ", " << n << ")\n";
    cout << "  Chave Privada: (d, n) = (" << d << ", " << n << ")\n";
    cout << "═══════════════════════════════════════════════════════════" << endl;

    // etapa 3 - codificacao

    // pre codificacao
    cout << "═══════════════════════════════════════════════════════════" << endl;
    cout << "  Pré Codificação" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    cout << "Digite uma mensagem (apenas letras maiúsculas e espaços): ";
    string mensagem;
    cin.ignore(); // limpar o buffer do cin
    getline(cin, mensagem);

    cout << "Sistema de codificação:\n";
    cout << "A=11, B=12, ..., Z=36, espaco=00" << endl;

    vector<int> codigods; // deuses do codigo

    cout << "Mensagem original: " << mensagem << endl;

    for (size_t i = 0; i < mensagem.length(); i++)
    {
        char c = toupper(mensagem[i]); // Converter para maiúscula
        int codigo;

        // Aplicar o sistema de codificação
        if (c == ' ')
        {
            codigo = 0; // Espaço = 00
        }
        else if (c >= 'A' && c <= 'Z')
        {
            codigo = (c - 'A') + 11; // A=11, B=12, ..., Z=36
        }
        else
        {
            cout << left << setw(12) << i
                 << setw(15) << ("'" + string(1, c) + "'")
                 << setw(15) << "INVÁLIDO" << " (ignorado)" << endl;
            continue; // Ignora caracteres inválidos
        }

        codigods.push_back(codigo);
    }

    // Mostrar a sequência numérica completa
    cout
        << "\n───────────────────────────────────────────────────────────" << endl;
    cout << "Sequência numérica da mensagem: ";
    for (size_t i = 0; i < codigods.size(); i++)
    {
        cout << setfill('0') << setw(2) << codigods[i];
        if (i < codigods.size() - 1)
            cout << " ";
    }
    cout << setfill(' ') << endl;
    cout << "───────────────────────────────────────────────────────────" << endl;

    // criptografando
    vector<long long> blocos = criptografar(codigods, e, n);

    // descriptografando
    vector<int> descriptografado = descriptografar(blocos, d, n);
    // reconvertendo para letras
    string mensagemRecuperada = reconverterMensagem(descriptografado);

    // verificacao
    cout << "\n═══════════════════════════════════════════════════════════" << endl;
    cout << "  VERIFICAÇÃO FINAL" << endl;
    cout << "═══════════════════════════════════════════════════════════" << endl;

    // Converter mensagem original para maiúsculas para comparar
    string msgUpper = mensagem;
    for (char &c : msgUpper)
        c = toupper(c);

    cout << "\nMensagem original:    \"" << msgUpper << "\"" << endl;
    cout << "Mensagem recuperada:  \"" << mensagemRecuperada << "\"" << endl;

    if (msgUpper == mensagemRecuperada)
        cout << "\nStatus: ✓ SUCESSO - As mensagens são idênticas!\n";
    else
        cout << "\nStatus: ✗ FALHA - As mensagens são diferentes!\n";

    cout << "\n═══════════════════════════════════════════════════════════\n"
         << endl;

    return 0;
}