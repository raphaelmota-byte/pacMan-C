# 🏗️ Arquitetura do Sistema e Estruturas de Dados

Para evitar o uso de variáveis globais e manter o código modular (como exigido no trabalho), o jogo concentra seu estado em estruturas de dados passadas por referência (ponteiros).

## 1. Estruturas de Dados Principais (`include/estado.h`)

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
    char mapa[100][100]; // Utilizando macros MAX_LINHAS e MAX_COLUNAS
    Posicao jogador;
    Fantasma fantasmas[10];
    int qtdFantasmas;
    int pontosColetados;
    int pontosRestantes;
    int dificuldade; // 1 = Fácil, 2 = Difícil
} Estado_jogo;
```

## 2. Assinaturas e Módulos (Headers)

### ⚙️ `include/mapa.h` (Gerenciamento de Arquivos e Renderização)
- **`void sortear_caminho_mapa(char *caminho);`**
  - Sorteia um arquivo `.txt` da pasta `data/`.
- **`void carregar_cenario(Estado_jogo *jogo, char *caminhoArquivo);`**
  - Preenche a matriz `jogo->mapa` a partir do texto.
- **`void Encontrar_Entidades(Estado_jogo *jogo);`** e **`void contar_pontos(Estado_jogo *jogo);`**
  - Identificam posições iniciais de `P` e `G`, e totalizam os pontos (`.`).
- **`void exibir_mapa(Estado_jogo *jogo);`**
  - Limpa o console e imprime a matriz atualizada junto com o placar.

### 🏃 `include/entidades.h` (Lógica do Pac-Man)
- **`int captura_tecla(void);`**
  - Captura a entrada do usuário de forma contínua.
- **`void mover_jogador(Estado_jogo *jogo, int tecla);`**
  - Calcula o vetor direção com base em `W, A, S, D`, checando colisão com paredes (`#`).

### 👻 `include/fantasmas.h` (Lógica e IA dos Inimigos)
- **`void mover_fantasmas(Estado_jogo *jogo);`**
  - Itera o vetor `jogo->fantasmas` e dita o movimento das entidades conforme o nível de dificuldade escolhido.

### 🖥️ `src/main.c` (Fluxo Principal / Maestro)
- Atua como o motor do jogo em substituição ao antigo módulo `core`.
- Concentra a inicialização (`srand`), o `loop_jogo` infinito e avalia as condições de vitória ou derrota.

## 3. Lógica da Inteligência Artificial (Fantasmas)

A tomada de decisão dos fantasmas depende da variável `jogo->dificuldade`:

### 🟢 Modo Fácil (Movimento Aleatório)
1. Gera uma direção via `rand() % 4` (0=Cima, 1=Baixo, 2=Esquerda, 3=Direita).
2. Valida se a próxima posição não é uma parede (`#`).
3. Se for parede, sorteia novamente (até o limite de tentativas).

### 🔴 Modo Difícil (Perseguição por Eixo Dominante)
1. Calcula a distância Absoluta (Delta) em X e Y:
   - `deltaX = |fantasma.pos.x - jogador.x|`
   - `deltaY = |fantasma.pos.y - jogador.y|`
2. Identifica o **Eixo Dominante**: se `deltaX > deltaY`, o fantasma tenta primeiro se mover na horizontal (para a esquerda ou direita, dependendo de onde o jogador está).
3. **Mecanismo Anti-Travamento (Fallback):** Se o movimento no eixo dominante for bloqueado por uma parede, ele tenta o eixo secundário. Se ambos estiverem bloqueados, escolhe uma direção aleatória para desviar.