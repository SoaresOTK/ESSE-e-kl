# RobloxExternalLab

Protótipo educacional de overlay independente com ImGui, GLFW e OpenGL.
O aplicativo cria entidades fictícias localmente para demonstrar ESP, radar,
hotkeys, configuração e diagnóstico. Não se conecta ao Roblox, não lê memória
de outros processos e não usa offsets para interagir com jogos.

## Requisitos
- Windows 10/11
- Visual Studio 2022 com workload "Desktop development with C++"
- CMake 3.24+
- Git no PATH
- Conexão à internet na primeira configuração (FetchContent baixa GLFW e ImGui)

## Compilar
No terminal, na pasta do projeto:

```powershell
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
.\build\Release\RobloxExternalLab.exe
```

Em geradores que não criam a pasta `Release`, execute `.\build\RobloxExternalLab.exe`.

## Controles
- INSERT: mostrar/ocultar menu
- F1: ESP
- F2: radar
- F3: painel de diagnóstico
- F4: nomes
- F5: distâncias
- END: fechar

A janela é independente e sempre no topo. A opção de transparência depende
do compositor do Windows e do driver gráfico.

## Estrutura
- `engine/Simulation`: entidades fictícias e movimento.
- `overlay/OverlayUI`: desenho de ESP e radar com ImGui.
- `core/Config`: persistência de preferências em `config/settings.json`.
- `diagnostics/Diagnostics`: métricas locais do aplicativo.


## Compilar automaticamente pelo GitHub
1. Crie um repositório vazio no GitHub.
2. Envie todos os arquivos e pastas deste projeto, incluindo `.github/workflows/build.yml`.
3. Abra a aba **Actions** do repositório.
4. Se solicitado, habilite GitHub Actions.
5. Abra a execução **Build Windows x64** e aguarde ficar verde.
6. Na parte inferior da execução, baixe o Artifact `RobloxExternalLab-Windows-x64`.
