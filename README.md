# 🕹️ Pac-Man em C - Projeto UERJ

> **Disciplina:** Construção de Algoritmos (UERJ)  
> **Professor:** Eugênio Silva  
> **Linguagem:** C

Este projeto é uma implementação simplificada do jogo clássico Pac-Man, rodando diretamente no terminal, cumprindo os requisitos de modularização e uso de arquivos do trabalho da disciplina.

## 🎯 Funcionalidades

- [x] Leitura de mapas a partir de arquivos `.txt` (cenários aleatórios).
- [x] Movimentação do jogador (Teclas `W`, `A`, `S`, `D`).
- [x] Placar dinâmico (pontos coletados e restantes).
- [x] Sistema de colisão e fim de jogo.
- [x] **Dificuldades:**
  - 🟢 **Fácil:** Fantasmas se movem aleatoriamente.
  - 🔴 **Difícil:** Fantasmas perseguem ativamente o jogador.

## 📂 Estrutura de Diretórios

Para manter o código limpo, o projeto utiliza a seguinte arquitetura de pastas:

```text
meu_pacman/
├── data/                   # Mapas em txt (mapa1.txt, mapa2.txt)
├── include/                # Headers (.h)
│   ├── config.h
│   ├── core.h
│   └── entidades.h
└── src/                    # Código-fonte (.c)
    ├── main.c              
    ├── config/
    │   └── mapa_loader.c   
    ├── core/
    │   └── motor_jogo.c    
    └── entidades/
        ├── jogador.c       
        └── fantasmas.c     
```

## 🚀 Como Compilar e Rodar

Certifique-se de ter o compilador `gcc` instalado. No terminal, na raiz do projeto, execute os comandos abaixo:

```bash
# Compilando o projeto

gcc src\main.c src\config\mapa.c src\core\motor_jogo.c src\entidades\jogador.c  -I include -o src\output\pacman.exe 

# Rodando o jogo (Linux/Mac)
./pacman

# Rodando o jogo (Windows)
.\src\output\pacman.exe                                                      
```