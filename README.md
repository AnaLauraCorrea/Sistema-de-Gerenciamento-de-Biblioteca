<h1 align="center"> 📚 Sistema de Gerenciamento de Biblioteca </h1>

📖 Sistema desenvolvido em **C/C++** para gerenciamento completo de bibliotecas, contemplando cadastro de livros, usuários, controle de empréstimos, devoluções, renovações e geração de relatórios administrativos. O projeto aplica conceitos clássicos de **programação estruturada**, com foco em organização, confiabilidade e persistência de dados.

---

## :bulb: Por que este projeto é relevante?

Bibliotecas lidam com grandes volumes de informação que exigem **organização eficiente**, **controle rigoroso** e **atualizações constantes**. A informatização desses processos reduz erros manuais, melhora a rastreabilidade dos dados e oferece maior controle sobre empréstimos e disponibilidade de exemplares.

Este sistema demonstra, de forma prática, como a programação estruturada pode ser aplicada para resolver problemas reais de gestão informacional.

---

## Alguns itens presentes neste README

* Título e descrição do projeto
* Índice
* Funcionalidades
* Estrutura e arquitetura
* Persistência de dados
* Tecnologias utilizadas
* Pessoas desenvolvedoras
---

## :pushpin: Índice

```Markdown
## Índice
* [Descrição do Projeto](#descrição-do-projeto)
* [Funcionalidades](#funcionalidades)
* [Arquitetura do Sistema](#arquitetura-do-sistema)
* [Persistência de Dados](#persistência-de-dados)
* [Testes e Validações](#testes-e-validações)
* [Acesso ao Projeto](#acesso-ao-projeto)
* [Tecnologias Utilizadas](#tecnologias-utilizadas)
* [Pessoas Desenvolvedoras](#pessoas-desenvolvedoras)
* [Licença](#licença)
```

---

## :pushpin: Descrição do Projeto

O Sistema de Gerenciamento de Biblioteca foi projetado para automatizar operações essenciais como cadastro de livros e usuários, controle de empréstimos, devoluções e renovações. O sistema mantém a integridade das informações por meio de validações rigorosas e persistência em arquivos, garantindo confiabilidade mesmo após o encerramento da aplicação.

---

## :pushpin: Funcionalidades

```Markdown
 #:hammer: Funcionalidades do sistema
- Cadastro de livros com controle de disponibilidade
- Cadastro de usuários
- Empréstimo e devolução de exemplares
- Renovação de empréstimos conforme regras do sistema
- Relatório de livros mais requisitados
- Relatório de empréstimos vencidos
- Validação de entradas e prevenção de inconsistências
```

---

## :pushpin: Arquitetura do Sistema

O sistema segue o paradigma da **programação estruturada**, com:

* Organização do código em **funções modulares**
* Cada função responsável por uma tarefa específica
* Uso de **structs** para representar entidades:

  * Livros
  * Usuários
  * Empréstimos

Essa abordagem reduz a complexidade do código, evita vetores paralelos e melhora a manutenção e a legibilidade.

---

## :pushpin: Persistência de Dados

A persistência das informações é realizada por meio de **manipulação de arquivos**, garantindo que os dados permaneçam íntegros entre execuções do sistema.

O salvamento é feito automaticamente após operações críticas, como cadastros, empréstimos, devoluções e renovações.

---

## :pushpin: Testes e Validações

O sistema contempla validações para evitar situações inconsistentes, como:

* Cadastros duplicados
* Empréstimos de livros indisponíveis
* Renovações fora do prazo
* Devoluções inexistentes

Testes foram realizados tanto em cenários normais quanto em situações de erro, assegurando a confiabilidade do sistema.

---

:pushpin: Stacks Utilizadas

Linguagem: C 

IDE: Dev-C++

Compilador: GCC

## :pushpin: Bibliotecas Utilizadas:

As seguintes bibliotecas nativas da linguagem foram utilizadas:

* `<stdio.h>` — Entrada e saída de dados
* `<stdlib.h>` — Alocação de memória e utilitários
* `<string.h>` — Manipulação de strings
* `<time.h>` — Controle e cálculo de datas

Nenhuma biblioteca externa foi empregada.

# Autores
<p>Ana Laura Corrêa</p>

(https://github.com/AnaLauraCorrea)



