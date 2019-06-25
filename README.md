# Intro
Este projeto consiste na implementação de um dicionário, um Tipo Abstratos de Dado (TAD) com base em lista sequencial (i.e. vetor), ordenada e não ordenada, em C++. A implementação do projeto explora conceitos abordados da discplina de Estrutura de Dados Básica I, ministrada pelo professor [Selan Rodrigues](https://docente.ufrn.br/2497950/perfil).

## Funções implementadas
Funções implementadas para as classes DAL e DSAL: 
- [X] insert();
- [X] remove();
- [X] search();
- [X] min();
- [X] max();
- [X] sucessor();
- [X] antecessor();

## Compilando
Para compilar, é necessário ter o CMake instalado. Caso você não tenha instalado, execute ```sudo apt-get install cmake``` no terminal.

Caso você já tenha instalado, abra um termial na pasta raiz do projeto.

Crie o diretorio "build" e entre nele: ```$ mkdir build && cd build ```

Agora gere os arquivos para a compilação com: ```$ cmake -G"Unix Makefiles" ..```

Agora compile o projeto com: ```$ make ```

## Executando
Para executar o projeto: ```$ ./dic ```.



Autor: Ranna Raabe