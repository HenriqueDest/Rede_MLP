# Projeto de Rede MLP para Reconhecimento de Sinais Cardíacos

Este projeto implementa uma Rede Neural Multicamadas (MLP) para o reconhecimento de sinais cardíacos. O objetivo é classificar os sinais cardíacos em diferentes categorias usando uma rede neural treinada com dados específicos.

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

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues e pull requests com melhorias, correções de bugs ou novas funcionalidades.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).

