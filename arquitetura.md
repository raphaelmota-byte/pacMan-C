# 🏗️ Arquitetura do Sistema e Estruturas de Dados

Para evitar o uso de variáveis globais e manter o código modular (como exigido no trabalho), o jogo concentra seu estado em estruturas de dados passadas por referência (ponteiros).

## 1. Estruturas de Dados Principais (`include/core.h`)

```c
// Representa uma coordenada 2D no mapa
typedef struct {
    int x;
    int y;
} Posicao;

// Representa a entidade Fantasma
typedef struct {
    Posicao pos;
    char itemAnterior; // Guarda o que estava no mapa ('.' ou ' ') antes do fantasma passar
} Fantasma;

// Guarda o estado global da partida
typedef struct {
    char mapa[20][25];
    Posicao jogador;
    Fantasma fantasmas[10];
    int qtdFantasmas;
    int pontosColetados;
    int pontosRestantes;
    int dificuldade; // 1 = Fácil, 2 = Difícil
} Estado_jogo;
```

## 2. Assinaturas e Módulos (Headers)

### ⚙️ `include/config.h` (Gerenciamento de Arquivos)
- **`void carregarMapaAleatorio(EstadoJogo *jogo);`**
  - Sorteia um arquivo `.txt` da pasta `data/`.
  - Preenche a matriz `jogo->mapa`.
  - Identifica posições iniciais de `P` (Jogador) e `G` (Fantasmas).

### 🏃 `include/entidades.h` (Lógica de Movimento)
- **`void moverJogador(EstadoJogo *jogo, char direcao);`**
  - Calcula o vetor direção com base em `W, A, S, D`.
  - Checa colisão com paredes (`#`).
- **`void moverFantasmas(EstadoJogo *jogo);`**
  - Itera o vetor `jogo->fantasmas` e chama a IA correspondente.

### 🖥️ `include/core.h` (Fluxo e Renderização)
- **`void exibirMapa(EstadoJogo *jogo);`**
  - Limpa o console (`system("clear")` ou `system("cls")`).
  - Imprime a matriz e os pontos.
- **`int verificarFimDeJogo(EstadoJogo *jogo);`**
  - Retorna `0` (Rodando), `1` (Vitória) ou `-1` (Derrota).

## 3. Lógica da Inteligência Artificial (Fantasmas)

A tomada de decisão dos fantasmas depende da variável `jogo->dificuldade`:

### 🟢 Modo Fácil (Movimento Aleatório)
1. Gera uma direção via `rand() % 4` (0=Cima, 1=Baixo, 2=Esquerda, 3=Direita).
2. Valida se a próxima posição não é uma parede (`#`).
3. Se for parede, sorteia novamente (até o limite de tentativas).

### 🔴 Modo Difícil (Perseguição por Eixo Dominante)
1. Calcula a distância Absoluta (Delta) em X e Y:
   - `deltaX = |fantasma.x - jogador.x|`
   - `deltaY = |fantasma.y - jogador.y|`
2. Identifica o **Eixo Dominante**: se `deltaX > deltaY`, o fantasma tenta primeiro se mover na horizontal (para a esquerda ou direita, dependendo de onde o jogador está).
3. **Mecanismo Anti-Travamento (Fallback):** Se o movimento no eixo dominante for bloqueado por uma parede, ele tenta o eixo secundário. Se ambos estiverem bloqueados, escolhe uma direção aleatória para desviar.