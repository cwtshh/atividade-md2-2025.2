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

**Justificativa**: 	euclides_estendido() retorna inverso via coeficiente x

( F ) Se mdc(G, Zn) ≠ 1, o programa ainda consegue encontrar o inverso de G em Zn.

**Justificativa**: Código rejeita com return -1 se mdc ≠ 1

( V ) Se n1 for primo, o código aplica o Pequeno Teorema de Fermat para simplificar o cálculo de
a^x mod n1.

**Justificativa**: Verifica ePrimo(n) e reduz: e % (n-1)

( F ) A função powMod implementa o cálculo de potência modular utilizando multiplicações diretas
sem otimização.

**Justificativa**: Usa exponenciação rápida O(log n), não multiplicação direta

( V ) Quando o resultado do inverso é negativo, o código ajusta o valor somando o módulo m0.

**Justificativa**: Linha: if (d < 0) d += z; ajusta negativos

( F ) O cálculo de fi(n1) (função totiente de Euler) é utilizado apenas quando n1 não é primo.

**Justificativa**: φ(n) usado sempre: chaves RSA, Euler, e casos gerais