# Questão 4

### **Com o código completo e preenchido corretamente, qual seria a saída com os valores: H: 7, G: 3, Zn: 11, x: 10, n1: 13**

Resposta: 9

```bash
Algoritmo de Euclides: 13 mod 11 = 2
Algoritmo de Euclides: 11 mod 2 = 1
Algoritmo de Euclides: 2 mod 1 = 0

Substituindo, temos que o inverso 13 em 11 é 6.

Fazendo a multiplicação modular: 7 * 6 mod 11 = 9
 Sendo 6 o inverso de 3.
Valor final da congruencia: 9
```

## 4.2

( V ) O algoritmo de Euclides estendido é utilizado para calcular o inverso modular de um número.

( F ) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.

**Justificativa**: O código verifica if (resultado.mdc != 1) return -1; porque o inverso modular só existe quando mdc(G, Zn) = 1. Se mdc ≠ 1, não há solução.

( V ) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de
a^x mod n1.

**Justificativa**: O código verifica if (ePrimo(n)) e reduz o expoente: expoente_reduzido = e % (n - 1), aplicando o Pequeno Teorema de Fermat: a^(p-1) ≡ 1 (mod p).​

( F ) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas
sem otimização.
**Justificativa**: A função implementa exponenciação rápida com complexidade O(log n), não multiplicações diretas O(n). O loop divide o expoente por 2 e eleva a base ao quadrado a cada iteração.

( V ) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.

**Justificativa**: O código contém if (d < 0) d += z; porque o algoritmo de Euclides Estendido pode retornar valores negativos. Somar o módulo z garante que 0 ≤ d < z.

( F ) O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.

**Justificativa**: φ(n) é calculado em múltiplos casos: sempre para gerar chaves RSA (z = (p-1)×(q-1)), no Teorema de Euler quando mdc(M,n)=1, e também quando n é primo (φ(p)=p-1). Não é exclusivo para n não-primo.​