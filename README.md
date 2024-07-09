# Projeto de Rede MLP para Reconhecimento de Sinais Cardíacos

Este projeto implementa uma Rede Neural Multicamadas (MLP) para o reconhecimento de sinais cardíacos. O objetivo é classificar os sinais cardíacos em diferentes categorias usando uma rede neural treinada com dados específicos.

## Interface de Treinamento com Válidação Cruzada com Parada Antecipada
![image](https://github.com/HenriqueDest/Rede_MLP/assets/104697173/329201d5-ccd0-4add-afb9-66ff60dd706d)

## Classificação dos Sinais
![image](https://github.com/HenriqueDest/Rede_MLP/assets/104697173/b96150c8-6f1a-4b0f-af8e-8e4391003104)

## Aquisição e Classificação em Tempo Real dos Sinais
![image](https://github.com/HenriqueDest/Rede_MLP/assets/104697173/b06285a3-2be3-4b3f-9b18-53509cabb649)

## Distribuição das Classes de Acordo com a Época de Treinamento
<p align="center">
  <img src="https://github.com/HenriqueDest/Rede_MLP/assets/104697173/186cdc8a-afa3-434b-be8c-b6fe4bd0348c" alt="2024-07-09 00-05-58 - Trim" width="1129" height="500">
</p>

## Estrutura do Projeto

O projeto é estruturado da seguinte forma:

- **URna.cpp**: Arquivo principal que contém a implementação da rede neural, leitura de dados e manipulação de portas seriais.
- **URna.h**: Arquivo de cabeçalho contendo as declarações das funções e variáveis usadas no projeto.
- **Dados de Treinamento e Validação**: Pastas contendo os dados usados para treinar e validar a rede neural.
- **Gráficos**: Visualização dos dados e resultados do treinamento.

## Funcionalidades

- Treinamento de uma rede MLP com dados de sinais cardíacos.
- Validação cruzada dos resultados do treinamento.
- Configuração automática de portas seriais para leitura de dados em tempo real.
- Salvamento dos pesos da rede neural e resultados de treinamento em arquivos.
- Visualização dos resultados em gráficos.

## Pré-requisitos

- RAD Studio 12 ou superior.
- Biblioteca VCL para gráficos e manipulação de componentes.
- Conjunto de dados de sinais cardíacos para treinamento e validação.

## Como Compilar e Executar

1. Abra o projeto no RAD Studio.
2. Configure as propriedades do projeto para a plataforma desejada (Windows 32-bit, por exemplo).
3. Compile o projeto usando a opção `Build`.
4. Execute o projeto diretamente do RAD Studio ou através do executável gerado.

## Configuração da Porta Serial

Para configurar a porta serial, selecione a porta desejada no componente `CbSerialPort1` e a taxa de baud no componente `CbBaudRate1`. O projeto detecta automaticamente as portas seriais disponíveis no sistema.

## Uso

1. Adicione os dados de treinamento na pasta `treinamento` e os dados de validação na pasta `validacao`.
2. Selecione a porta serial para leitura de dados em tempo real, se aplicável.
3. Inicie o treinamento clicando no botão `Iniciar Treinamento`.
4. Acompanhe os resultados do treinamento e validação nos gráficos exibidos na interface.
   
## Aquisição de Sinais

Para ser feito a aquisição de sinais, foi utilizado o seguinte Hardware junto ao arduino para coletar os dados em uma frequência de 500Hz

![Imagem do WhatsApp de 2024-07-05 à(s) 20 56 47_13014959](https://github.com/HenriqueDest/Rede_MLP/assets/104697173/ebf95b77-8cd7-4be5-b155-f41535dd28a1)

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests com melhorias, correções de bugs ou novas funcionalidades.



