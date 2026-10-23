# WCD-Analysis

Repositório de trabalho (privado) da minha dissertação de mestrado em Física no CBPF: simulação em Geant4 de um Water Cherenkov Detector (WCD) com hodoscópio, compatível com as especificações do SWGO, e os notebooks Python de análise. Serve como backup de todo o progresso, incluindo versões intermediárias.

## O que é simulado

- Tanque (WCD) com revestimento de Tyvek, preenchido com água, com 3 PMTs no fundo (Hamamatsu R5912) e 1 PMT no topo (PMT4).
- Hodoscópio: matriz de cintiladores plásticos acima do tanque (32x32 pixels de 2,5 cm) e 4 painéis RPC abaixo dele (8x8 pads de 9,5 x 7,5 cm²).
- Partícula primária: múons de 5 GeV, na vertical e em ângulos zenitais de 10 a 60 graus, além de θ = 29° com quatro ângulos azimutais.

## Requisitos

Geant4 11.1.3, CMake, compilador C++ e, para os notebooks, Python 3 com Jupyter, pandas, numpy e matplotlib. Desenvolvido em Ubuntu 20.04 (WSL2).

## Compilar e rodar

```bash
source /caminho/do/geant4-install/bin/geant4.sh
mkdir build && cd build
cmake ..
make -j4
./SWGO muon.mac      # modo batch
./SWGO               # modo interativo (carrega vis.mac)
```

As saídas são CSVs (`*_Data.csv`, `*_PMTData.csv`, `*_HodoData.csv`, `*_RPCData.csv`).

## Estrutura

```
src/, include/, SWGO.cc, CMakeLists.txt   código da simulação
*.mac                                     macros de execução
v01_angular/, v05/                        macros e saídas de simulações
analise/                                  versão organizada das análises
  angular_pmt4/        resposta angular e eficiência (3 e 4 PMTs)
  angular_3pmt/        análise angular sem PMT4
  hodoscopio/          validação do hodoscópio completo
  vertical_com_otica/  múons verticais com física óptica
backup_analises/                          cópia de todas as versões (v01 a v10)
```

Os notebooks de `analise/` usam caminhos relativos e devem ser executados a partir da própria pasta. Os de `backup_analises/` estão como eram no meu computador, com os caminhos originais do Windows, e servem só de histórico.

## Sobre as PMTs

A dissertação usa o sinal somado das 3 PMTs do fundo. O notebook `analise/angular_pmt4` também calcula as grandezas com a PMT4 e gera as figuras de eficiência para as duas configurações (`eficiencia_3pmt_*` e `eficiencia_4pmt_*`).

## Autoria

Gizele, mestrado em Física, CBPF.
