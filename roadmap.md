# 🗺️ Roadmap de Desenvolvimento (Passo a Passo)

Siga esta ordem para evitar frustrações. Teste cada etapa isoladamente antes de avançar para a próxima.

## Fase 1: Estrutura Base e Leitura de Arquivo
- [X] Criar a estrutura de pastas (`src/`, `include/`, `data/`).
- [X] Criar os arquivos de cabeçalho (`.h`) com as definições das `structs`.
- [X] Criar pelo menos dois cenários `.txt` na pasta `data/` seguindo o modelo do trabalho.
- [X] Implementar a função para ler o arquivo `.txt` e imprimir a matriz pura no terminal.

## Fase 2: Mapeamento e Renderização
- [X] Implementar a função que varre a matriz carregada e encontra a coordenada `x, y` do jogador (`P`) e dos fantasmas (`G`).
- [X] Contar quantos pontos (`.`) existem no mapa e salvar em `pontosRestantes`.
- [ ] Implementar a função de limpar a tela e redesenhar o mapa com o placar de pontos.

## Fase 3: Movimentação do Jogador
- [ ] Capturar a tecla do usuário (`W, A, S, D`).
- [ ] Fazer o jogador se mover (trocando o `P` de lugar na matriz com um espaço vazio ` `).
- [ ] Implementar a verificação de parede (impedir que o `P` ande por cima de um `#`).
- [ ] Fazer o jogador "comer" os pontos (`.`), somando em `pontosColetados` e diminuindo de `pontosRestantes`.

## Fase 4: O Básico dos Fantasmas (Modo Fácil)
- [ ] Criar o menu inicial perguntando a dificuldade (1 = Fácil, 2 = Difícil).
- [ ] Implementar o loop onde cada fantasma escolhe uma direção aleatória.
- [ ] Garantir que o fantasma não apague os pontos (`.`) quando passar por cima deles (usar a variável `itemAnterior` da struct).
- [ ] Implementar a checagem de Game Over (se a coordenada do jogador for igual à do fantasma).

## Fase 5: Inteligência Artificial (Modo Difícil)
- [ ] Implementar a lógica matemática de aproximação (comparar o `x` e o `y` do fantasma com o do jogador).
- [ ] Testar se o fantasma persegue corretamente sem atravessar paredes.
- [ ] Adicionar o "fallback" (se ele bater de frente com uma parede tentando seguir o jogador, ele deve tentar desviar pelos lados).

## Fase 6: Polimento Final
- [ ] Verificar se o jogo encerra e mostra a mensagem de "Vitória" quando `pontosRestantes == 0`.
- [ ] Revisar se não há nenhum `include` de arquivo `.c` solto (apenas `.h`).
- [ ] Testar no laboratório ou no sistema Windows/Linux para garantir a compatibilidade (especialmente a parte de limpar a tela).
