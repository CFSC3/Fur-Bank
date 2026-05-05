# 🏦 Fur Bank - ATM System

Um sistema de terminal que simula as operações de um caixa eletrônico (ATM), permitindo o gerenciamento de contas bancárias e transações financeiras em tempo real.

## 📝 Sobre o Projeto
O **Fur Bank** é uma aplicação desenvolvida em C que gerencia contas bancárias através de uma interface de linha de comando. O sistema utiliza estruturas compostas (`structs`) para separar os dados do **Cliente** (nome, CPF, e-mail) dos dados da **Conta** (saldo, limite, número).

A lógica do sistema inclui um gerenciamento inteligente de saldo, onde saques e transferências consideram tanto o saldo disponível quanto o limite de crédito do usuário.

## ✨ Funcionalidades
- ✅ **Criação de Conta:** Registro de novos clientes com geração automática de data de cadastro e número de conta único.
- ✅ **Saques e Depósitos:** Movimentação financeira com validação de saldo e limite.
- ✅ **Transferências:** Envio de valores entre contas cadastradas com atualização automática dos saldos de origem e destino.
- ✅ **Listagem de Contas:** Visualização detalhada de todas as contas registradas no sistema.
- ✅ **Controle de Saldo Total:** Cálculo dinâmico que soma o saldo real ao limite de crédito disponível.

## 🛠️ Tecnologias Utilizadas
- **Linguagem:** C
- **Bibliotecas Padrão:** 
  - `stdio.h` / `stdlib.h`: Entrada, saída e gestão de memória.
  - `string.h`: Manipulação de dados de texto dos clientes.
  - `windows.h`: Utilizada para codificação de caracteres (UTF-8) e controle de tempo do sistema (`Sleep`).
  - `time.h`: Geração automática de datas baseadas no relógio do sistema.

## 📸 Demonstração
<div align="center">
  <img src="Fur Bank/img/img1.png" alt="Menu Principal do Fur Bank" width="600px">
  <img src="Fur Bank/img/img2.png" alt="Criação de Conta" width="600px">
  <img src="Fur Bank/img/img3.png" alt="Efetuar Saque" width="600px">
  <img src="Fur Bank/img/img4.png" alt="Efetuar Depósito" width="600px">
  <img src="Fur Bank/img/img5.png" alt="Efetuar Transferência" width="600px">
  <img src="Fur Bank/img/img6.png" alt="Listar Contas" width="600px">
  <img src="Fur Bank/img/img7.png" alt="Sair do Sistema" width="600px">
</div>

## 🚀 Como Executar

### Pré-requisitos
* Compilador de C (GCC recomendado).
* Sistema Operacional Windows (devido ao uso da biblioteca `windows.h`).

### Passo a passo
1. Clone o repositório:
   ```bash
   git clone [https://github.com/CFSC3/Fur-Bank.git](https://github.com/CFSC3/Fur-Bank.git)

2. Compile o código:
   ```bash
   gcc game.c -o furbank

3. Execute o programa:
   ```bash
   ./furbank
