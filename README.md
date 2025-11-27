# Tesouro Espacial

## Enredo
A história acompanha um guerreiro destemido em sua busca por um tesouro lendário, espalhado por duas fases repletas de perigos. Cada moeda representa um passo rumo à glória, mas monstros ferozes guardam o caminho e farão de tudo para impedir que o herói alcance seu objetivo. Em meio a cenários variados e atmosferas intensas, o jogador é lançado em uma jornada marcada por tensão, coragem e perseverança.

## Gameplay
A aventura combina ação constante e estratégia, desafiando o jogador a coletar todas as moedas enquanto desvia de monstros implacáveis. As fases apresentam níveis crescentes de dificuldade, exigindo agilidade, precisão e raciocínio rápido. O jogador deve se movimentar pelo mapa, evitar perigos, utilizar bem o tempo disponível e superar cada ameaça para conquistar as riquezas que o aguardam.

## Instruções de Compilação (Makefile)
1. Instalar corretamente o WSL Ubuntu (caso não o tenha)  
2. No terminal do Ubuntu, instalar os pacotes do sistema:
```bash
sudo apt update
sudo apt upgrade -y
```
3. Instalar os programas necessários:
- Compilador C (GCC):
```bash
sudo apt update
sudo apt install build-essential
```
- Gerenciador de Build (Make):
```bash
sudo apt install make
```
- Biblioteca Raylib:
```bash
sudo apt install libraylib-dev
```
- Git:
```bash
sudo apt install git
```
4. Clonar o repositório:
```bash
git clone https://github.com/LuizEduardoMariz/TesouroEspacial.git
```
5. Entrar na pasta do projeto:
```bash
cd TesouroEspacial
```
6. Compilar:
```bash
make
```
7. Rodar:
```bash
make run
```

## Instruções de Compilação (Manual)
1. Instalar corretamente o WSL Ubuntu (caso não o tenha)  
2. Atualizar os pacotes do sistema:
```bash
sudo apt update
sudo apt upgrade -y
```
3. Instalar os programas necessários:
- Compilador C (GCC):
```bash
sudo apt install build-essential
```
- Biblioteca Raylib:
```bash
sudo apt install libraylib-dev
```
- Git:
```bash
sudo apt install git
```
4. Clonar o repositório:
```bash
git clone https://github.com/LuizEduardoMariz/TesouroEspacial.git
```
5. Entrar na pasta do projeto:
```bash
cd TesouroEspacial
```
6. Compilar manualmente:
```bash
gcc src/*.c -Iinclude -o tesouro-espacial -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```
7. Rodar:
```bash
./tesouro-espacial
```

## Instruções de Uso
- Use as teclas direcionais (↑ ↓ ← →) para mover o personagem.
- Objetivo: fugir dos monstros e coletar todas as moedas.
- Tempo limite:
  - Fase 1: 90 segundos
  - Fase 2: 70 segundos
- O jogador perde se:
  - For capturado por um monstro
  - O tempo acabar antes de coletar todas as moedas
- No canto superior esquerdo:
  - Moedas coletadas
  - Maior pontuação global
- Ao final da partida:
  - Pontuação exibida
  - Calculada por moedas + bônus de tempo

## Principais Funções
```c
CarregarFase(int index, Mapa*, Player*, SistemaMoedas*);
mapa_colisao(const Mapa *m, int tileY, int tileX);
InitPlayer(Player *player);
UpdatePlayer(Player *player, const Mapa *mapa);
UpdateMonstro(Monstro *m, Player *player, float dt, const Mapa *mapa);
UpdateMoedas(SistemaMoedas *s, Player *p, float dt, Mapa *mapa);
```

## Highlights
- Arquitetura modular (mapa, player, moedas, inimigos)
- Sistema automático de fases
- Colisão baseada em mapa ASCII
- Inteligência artificial simples
- Temporizador por fase
- Sistema de pontuação com bônus
- Highscore persistente
- Raylib
- Gerenciamento explícito de memória

## Dificuldades Encontradas
O grupo encontrou muitas dificuldades ao longo do processo. No começo não sabíamos por onde iniciar, mas após definir o rumo os principais problemas envolveram a mecânica da moeda, o controle do personagem, o comportamento dos monstros e a colisão.

## Vídeo
https://youtu.be/rPxZWAFzOWg
