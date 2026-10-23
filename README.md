# WCD-Analysis

Simulação em Geant4 de um Water Cherenkov Detector (WCD) com hodoscópio, compatível com as especificações do SWGO, e os notebooks Python usados para analisar os resultados. Desenvolvido para a dissertação de mestrado em Física (CBPF).

## O que é simulado

- **Tanque (WCD):** cilindro com revestimento de Tyvek, preenchido com água, com 3 PMTs no fundo (Hamamatsu R5912, em triângulo equilátero) e 1 PMT no topo (PMT4).
- **Hodoscópio:** matriz de cintiladores plásticos acima do tanque (32x32 pixels de 2,5 cm) e 4 painéis RPC abaixo dele (8x8 pads de 9,5 x 7,5 cm²).
- **Partícula primária:** múons de 5 GeV, em incidência vertical e em vários ângulos zenitais (0, 10, 15, 30, 45 e 60 graus), além de θ = 29° com quatro ângulos azimutais.

## Requisitos

- Geant4 11.1.3 (com visualização Qt opcional)
- CMake e um compilador C++
- Python 3 com Jupyter, pandas, numpy e matplotlib para os notebooks

Desenvolvido e testado em Ubuntu 20.04 (WSL2).

## Como compilar e rodar a simulação

```bash
source /caminho/do/geant4-install/bin/geant4.sh
mkdir build && cd build
cmake ..
make -j4
./SWGO muon.mac      # modo batch, com uma macro
./SWGO               # modo interativo (carrega vis.mac)
```

As macros ficam na raiz do repositório (`muon.mac`, `vis.mac`, `gui.mac`). Os arquivos de saída são CSVs (`*_Data.csv`, `*_PMTData.csv`, `*_HodoData.csv`, `*_RPCData.csv`).

## Estrutura

```
src/, include/, SWGO.cc, CMakeLists.txt   código da simulação
*.mac                                     macros de execução
v01_angular/, v05/                        macros e saídas de simulações
analise/
  angular_pmt4/       resposta angular do WCD e eficiência de detecção (3 e 4 PMTs)
  hodoscopio/         validação do hodoscópio completo (θ = 29°, 4 azimutes)
  vertical_com_otica/ análise de múons verticais com física óptica
```

Cada pasta de `analise/` traz o notebook, as figuras geradas e os dados de entrada (CSVs). Os notebooks leem os dados por caminhos relativos, então devem ser executados a partir da própria pasta.

## Sobre as PMTs

A dissertação usa o sinal somado das 3 PMTs do fundo (PMT1+2+3). O notebook `analise/angular_pmt4` também calcula as grandezas incluindo a PMT4, e gera as figuras de eficiência para as duas configurações (`eficiencia_3pmt_*` e `eficiencia_4pmt_*`).

## Licença

A definir.

## Autoria

Gizele Santos, mestrado em Física, CBPF.
