# Atividade 02 – Cifra de César com Sequências Numéricas

**Disciplina:** Algoritmo e Pensamento Computacional

**Integrantes:**
| Nome | RGM |
|---|---|
| Nicolas Dias da Silva | 47609125 |
| Victor Hugo Gonzaga | 47300701 |

## Objetivo

Programa em C que une criptografia simples, matemática aplicada (progressões e séries) e conceitos computacionais (funções, arquivos, log), em duas camadas:

1. **Camada 1 – Cifra de César:** deslocamento fixo (SHIFT) em cada letra.
2. **Camada 2 – Deslocamento dinâmico:** soma do termo `i` de uma sequência numérica escolhida.

```
deslocamento_total[i] = SHIFT + sequencia[i]
letra_nova = 'a' + (letra - 'a' + deslocamento_total[i]) % 26
```

O `% 26` faz o alfabeto "dar a volta" (depois do `z` volta para o `a`).



## Sequências implementadas

| Opção | Sequência | Termos (i = 0, 1, 2...) | Fórmula |
|---|---|---|---|
| 1 | PA (a₁=1, r=2) | 1, 3, 5, 7, 9... | aₙ = a₁ + (n-1)·r |
| 2 | PG (a₁=1, q=2) | 1, 2, 4, 8, 16... | aₙ = a₁·qⁿ⁻¹ |
| 3 | Fibonacci | 1, 1, 2, 3, 5, 8, 13... | Fₙ = Fₙ₋₁ + Fₙ₋₂ |
| 4 | Primos | 2, 3, 5, 7, 11... | – |

Com no máximo 15 letras, o maior termo da PG é 2¹⁴ = 16384, que cabe em `int` sem estouro.

## Funcionalidades

- **Criptografar:** lê palavra, SHIFT e sequência; mostra o resultado e grava em `resultado_criptografia.txt`.
- **Descriptografar:** aplica o processo inverso com os mesmos parâmetros e recupera a palavra original.
- **Comparar sequências:** mesma palavra e mesmo SHIFT com as quatro sequências (usado na análise abaixo).
- **Log de execução:** `log_execucao.txt` registra data/hora, parâmetros e o cálculo de cada letra.
- **Validação:** palavra de 1 a 15 letras, sem acentos, números ou símbolos; SHIFT de 0 a 25; sequência de 1 a 4.

## Exemplo de execução

Entrada: `coracao`, SHIFT `3`, sequência `Fibonacci`.

| Letra | c | o | r | a | c | a | o |
|---|---|---|---|---|---|---|---|
| Fibonacci[i] | 1 | 1 | 2 | 3 | 5 | 8 | 13 |
| Deslocamento (3 + Fib) | 4 | 4 | 5 | 6 | 8 | 11 | 16 |
| Resultado | g | s | w | g | k | l | e |

Saída: `Palavra criptografada: gswgkle`

Arquivo gerado (`resultado_criptografia.txt`):

```
Palavra codificada: gswgkle | SHIFT: 3 | Tipo: 3 | Letras: 7
```

## Testes

| Palavra | SHIFT | Sequência | Resultado |
|---|---|---|---|
| coracao | 3 | Só César (sem sequência) | frudfdr |
| coracao | 3 | PA | guzkooe |
| coracao | 3 | PG | gtylvjd |
| coracao | 3 | Fibonacci | gswgkle |
| coracao | 3 | Primos | huzkqqi |
| gswgkle | 3 | Fibonacci (descriptografar) | coracao |
| abc123 | – | – | Erro: palavra inválida |
| abcdefghijklmnopq (17 letras) | – | – | Erro: palavra inválida |

## Análise (Taxonomia de Bloom)

### Analisar – comparação entre as sequências

Com a mesma palavra e o mesmo SHIFT, cada sequência produz um texto cifrado diferente. Na Cifra de César pura, letras repetidas viram sempre a mesma letra (`coracao` → `frudfdr`: os dois `a` viram `d`, os dois `o` viram `r`). Com a segunda camada, o deslocamento muda a cada posição, então a mesma letra vira letras diferentes (em `gswgkle`, os dois `a` viram `g` e `l`, os dois `o` viram `s` e `e`, e os dois `c` viram `g` e `k`).

- **PA:** crescimento linear, regular e previsível.
- **PG:** crescimento rápido; como os valores são reduzidos por `% 26`, ficam saltando pelo alfabeto de forma menos óbvia.
- **Fibonacci:** os dois primeiros termos são iguais (1, 1), então as duas primeiras letras recebem o mesmo deslocamento.
- **Primos:** deslocamentos irregulares, sem padrão simples de diferença constante ou razão constante.

### Avaliar – qual é mais forte e quão segura é a cifra

Entre as quatro, **PG e Primos** dificultam mais a análise por terem termos que não seguem diferença constante, mas a diferença de força entre as sequências é pequena. Como avaliação geral, **a cifra continua fraca para uso real**:

- Quem conhece o método (César + sequência) só precisa testar SHIFT (26 opções) e o tipo de sequência (4 opções): são apenas 104 combinações, fáceis de testar por força bruta.
- As sequências são públicas e determinísticas; a segurança dependeria só do SHIFT e da escolha do tipo, que formam uma chave minúscula.
- O objetivo do trabalho é didático: mostrar como a matemática de sequências altera a criptografia, e não substituir algoritmos modernos (AES, RSA etc.).

### Criar – ideias de extensão

- Permitir que o usuário informe os parâmetros da PA (a₁, r) e da PG (a₁, q).
- Aceitar letras maiúsculas e preservar o formato original.
- Adicionar novas sequências (quadrados perfeitos, fatorial, triangulares).
- Combinar duas sequências ao mesmo tempo.

## Estrutura do repositório

```
cifra_cesar/
├── sequencias.h                 (commit 1)
├── sequencias.c                 (commit 1)
├── cifra_cesar.c                (commit 2)
├── README.md
├── resultado_criptografia.txt   (gerado na execução)
└── log_execucao.txt             (gerado na execução)
```
