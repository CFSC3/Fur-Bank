#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

typedef struct {
    int codigo;
    char nome[50];
    char email[50];
    char cpf[20];
    char data_nascimento[20];
    char data_cadastro[20];
} Cliente;

typedef struct {
    int numero;
    Cliente cliente;
    float saldo;
    float limite;
    float saldo_total;
} Conta;

void menu();
void infoCliente(Cliente cliente);
void infoConta(Conta conta);
void criarConta();
void efetuarSaque();
void efetuarDeposito();
void efetuarTransferencia();
void listarContas();
float atualizarSaldoTotal(Conta conta);
Conta buscarContaPorNumero(int numero);
void sacar(Conta conta, float valor);
void depositar(Conta conta, float valor);
void transferir(Conta contaOrigem, Conta contaDestino, float valor);


static Conta contas[100];
static int contadorContas = 0;
static int contadorCliente = 0;


int main(){
    SetConsoleOutputCP(CP_UTF8);
    menu();
    return 0;
};

void menu(){

    printf("===============================\n");
    printf("============\033[1;35m ATM \033[0m==============\n");
    printf("==========\033[1;35m Fur Bank \033[0m===========\n");
    printf("===============================\n\n");

    printf(" =============================\n");
    printf("|\033[1;32mSelecione uma opção no menu: \033[0m|\n");
    printf("|\033[1;32m1 - Criar conta              \033[0m|\n");
    printf("|\033[1;32m2 - Efetuar saque            \033[0m|\n");
    printf("|\033[1;32m3 - Efetuar depósito         \033[0m|\n");
    printf("|\033[1;32m4 - Efetuar transferência    \033[0m|\n");
    printf("|\033[1;32m5 - Listar contas            \033[0m|\n");
    printf("|\033[1;32m6 - Sair do sistema          \033[0m|\n");
    printf(" =============================\n\n");

    //O usuário escolhe alguma das opções.
    printf("Opção: ");
    int opcao;
    scanf("%d", &opcao);
    getchar();

    //Verificar e iniciar a escolha do usuário.
    switch (opcao){
        case 1:
        criarConta();
        break;

        case 2:
        efetuarSaque();
        break;

        case 3:
        efetuarDeposito();
        break;

        case 4:
        efetuarTransferencia();
        break;

        case 5:
        listarContas();
        break;

        case 6:
        printf("Obrigado por usar o Fur Bank!\n\n");
        Sleep(2000); //tempo de resposta do programa em 2 segundos
        exit(0);

        default:
        printf("Opção inválida.\n\n");
        Sleep(2000); //tempo de resposta do programa em 2 segundos
        menu();
        break;
    };


};

void  infoCliente(Cliente cliente){ //Mostra as informações do cliente
    printf("Código: %d\n", cliente.codigo);
    printf("Nome: %s\n", strtok(cliente.nome, "\n"));
    printf("Data de nascimento: %s\n", strtok(cliente.data_nascimento, "\n"));
    printf("Cadastro: %s\n\n", strtok(cliente.data_cadastro, "\n"));

};

void infoConta(Conta conta){ //Mostra as informações da conta
    printf("Número da conta: %d\n", conta.numero);
    printf("Cliente: %s\n", strtok(conta.cliente.nome, "\n"));
    printf("Data de nascimento: %s\n", strtok(conta.cliente.data_nascimento, "\n"));
    printf("Data Cadastro: %s\n", strtok(conta.cliente.data_cadastro, "\n"));
    printf("Saldo total: R$ %.2f\n\n", conta.saldo_total);

};

void criarConta(){ //Cria uma conta, solicitando os dados do cliente e atribuindo um número para a conta, além de atribuir um saldo inicial de 0 e um limite de 1000, para evitar que haja contas com saldo negativo ou limite negativo, caso contrário, haveria contas com saldo negativo ou limite negativo, como por exemplo, a conta 1 e a conta 2, ambas com saldo -100 e limite -1000, caso haja apenas uma conta cadastrada
    Cliente cliente;

    //Data de Cadastro
    char dia[3], mes[3], ano[5];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    if(tm.tm_mday < 10){ //Verifica se o dia é menor que 10, caso seja, adiciona um 0 antes do número do dia, caso contrário, apenas adiciona o número do dia
        sprintf(dia, "0%d", tm.tm_mday);
    } else {
        sprintf(dia, "%d", tm.tm_mday);
    };

    if((tm.tm_mon + 1) < 10){ //Verifica se o mês é menor que 10, caso seja, adiciona um 0 antes do número do mês, caso contrário, apenas adiciona o número do mês
        sprintf(mes, "0%d", tm.tm_mon + 1);
    } else {
        sprintf(mes, "%d", tm.tm_mon + 1);
    };

    sprintf(ano, "%d", tm.tm_year + 1900); //Adiciona o número do ano

    strcpy(cliente.data_cadastro, "");  //Limpa a string data_cadastro para evitar que haja informações anteriores na string, caso contrário, a data de cadastro ficaria com informações anteriores, como por exemplo, a data de cadastro do cliente anterior, caso haja um cliente anterior cadastrado
    strcat(cliente.data_cadastro, dia);
    strcat(cliente.data_cadastro, "/"); 
    strcat(cliente.data_cadastro, mes);
    strcat(cliente.data_cadastro, "/");
    strcat(cliente.data_cadastro, ano);
    strcat(cliente.data_cadastro, "\0");
    strcpy(cliente.data_cadastro, cliente.data_cadastro); //Copia a string data_cadastro para a string data_cadastro do cliente, para evitar que haja informações anteriores na string data_cadastro do cliente, caso contrário, a data de cadastro do cliente ficaria com informações anteriores, como por exemplo, a data de cadastro do cliente anterior, caso haja um cliente anterior cadastrado

    //Criação do cliente
    printf("Digite os dados do cliente:\n");
    cliente.codigo = contadorCliente + 1; //Atribui o código do cliente, que é o número de clientes cadastrados + 1, para evitar que haja clientes com o mesmo código, caso contrário, haveria clientes com o mesmo código, como por exemplo, o cliente 1 e o cliente 2, ambos com o código 1, caso haja apenas um cliente cadastrado

    printf("Nome: ");
    fgets(cliente.nome, 50, stdin);
    
    printf("Email: ");
    fgets(cliente.email, 50, stdin);
    
    printf("CPF: ");
    fgets(cliente.cpf, 20, stdin);
    
    printf("Data de nascimento (dd/mm/aaaa): ");
    fgets(cliente.data_nascimento, 20, stdin);

    contadorCliente++;

    //Criação da conta
    contas[contadorContas].numero = contadorContas + 1; //Atribui o número da conta, que é o número de contas cadastradas + 1, para evitar que haja contas com o mesmo número, caso contrário, haveria contas com o mesmo número, como por exemplo, a conta 1 e a conta 2, ambas com o número 1, caso haja apenas uma conta cadastrada
    contas[contadorContas].cliente = cliente; //Atribui o cliente da conta
    contas[contadorContas].saldo = 0.0; //Atribui o saldo da conta, que é 0, para evitar que haja contas com saldo negativo, caso contrário, haveria contas com saldo negativo, como por exemplo, a conta 1 e a conta 2, ambas com saldo -100, caso haja apenas uma conta cadastrada
    contas[contadorContas].limite = 1000.0; //Atribui o limite da conta, que é 1000, para evitar que haja contas com limite negativo, caso contrário, haveria contas com limite negativo, como por exemplo, a conta 1 e a conta 2, ambas com limite -1000, caso haja apenas uma conta cadastrada
    contas[contadorContas].saldo_total = atualizarSaldoTotal(contas[contadorContas]); //Atribui o saldo total da conta, que é a soma do saldo e do limite, para evitar que haja contas com saldo total negativo, caso contrário, haveria contas com saldo total negativo, como por exemplo, a conta 1 e a conta 2, ambas com saldo total -1000, caso haja apenas uma conta cadastrada

    printf("Conta criada com sucesso!\n\n");
    printf("Dados da conta criada:\n");
    infoConta(contas[contadorContas]);
    contadorContas++;
    Sleep(2000); //tempo de resposta do programa em 2 segundos
    menu();
};

float atualizarSaldoTotal(Conta conta){ //Atualiza o saldo total da conta, somando o saldo e o limite
    return conta.saldo + conta.limite;
};

Conta buscarContaPorNumero(int numero){ //Busca a conta pelo número, caso exista, retorna a conta, caso contrário, retorna uma conta vazia
    Conta c;
    if(contadorContas > 0){
        for(int i = 0; i < contadorContas; i++){
            if(contas[i].numero == numero){
                c = contas[i];
            };
        };
    };
    return c;
};

void sacar(Conta conta, float valor){ //Realiza o saque, verificando se o valor é maior que 0 e se o saldo total é suficiente para realizar o saque, caso contrário, exibe uma mensagem de erro
    if(valor > 0 && conta.saldo_total >= valor){ //Verifica se o valor é maior que 0 e se o saldo total é suficiente para realizar o saque, caso contrário, exibe uma mensagem de erro
        for(int i = 0; i < contadorContas; i++){ //Percorre o array de contas para encontrar a conta que deseja realizar o saque
            if(contas[i].numero == conta.numero){ //Verifica se o número da conta é igual ao número da conta que deseja realizar o saque
                if(contas[i].saldo >= valor){ //Verifica se o saldo é suficiente para realizar o saque, caso contrário, exibe uma mensagem de erro
                    contas[i].saldo -= valor; //Realiza o saque, subtraindo o valor do saldo
                    contas[i].saldo_total = atualizarSaldoTotal(contas[i]); //Atualiza o saldo total da conta, somando o saldo e o limite
                    printf("Saque realizado com sucesso!\n\n");
                    Sleep(2000); //tempo de resposta do programa em 2 segundos
                    menu();
            }else{
                    float valorRestante = valor - contas[i].saldo; //Calcula o valor restante para realizar o saque, subtraindo o saldo do valor do saque
                    contas[i].limite -= valorRestante; //Realiza o saque, subtraindo o valor restante do limite
                    contas[i].saldo = 0; //Zera o saldo da conta, pois o valor do saque é maior que o saldo
                    contas[i].saldo_total = atualizarSaldoTotal(contas[i]); //Atualiza o saldo total da conta, somando o saldo e o limite
                    printf("Saque realizado com sucesso!\n\n");
                    Sleep(2000); //tempo de resposta do programa em 2 segundos
                    menu();
                };
        };
    };

    } else {
        printf("Saldo insuficiente para realizar o saque.\n\n");
        Sleep(2000); //tempo de resposta do programa em 2 segundos
        menu();
    };
};

void depositar(Conta conta, float valor){ //Realiza o depósito, verificando se o valor é maior que 0, caso contrário, exibe uma mensagem de erro
    if(valor > 0){ //Verifica se o valor é maior que 0, caso contrário, exibe uma mensagem de erro
        for(int i = 0; i < contadorContas; i++){ //Percorre o array de contas para encontrar a conta que deseja realizar o depósito
            if(contas[i].numero == conta.numero){ //Verifica se o número da conta é igual ao número da conta que deseja realizar o depósito
                contas[i].saldo += valor; //Realiza o depósito, somando o valor ao saldo
                contas[i].saldo_total = atualizarSaldoTotal(contas[i]); //Atualiza o saldo total da conta, somando o saldo e o limite
                printf("Depósito realizado com sucesso!\n\n");
                Sleep(2000); //tempo de resposta do programa em 2 segundos
                menu();
            };
        };
    } else {
        printf("Valor inválido para depósito.\n\n");
        Sleep(2000); //tempo de resposta do programa em 2 segundos
        menu();
    };
};

void transferir(Conta contaOrigem, Conta contaDestino, float valor){ //Realiza a transferência, verificando se o valor é maior que 0 e se o saldo total da conta de origem é suficiente para realizar a transferência, caso contrário, exibe uma mensagem de erro
    if(valor > 0 && contaOrigem.saldo_total >= valor){ //Verifica se o valor é maior que 0 e se o saldo total da conta de origem é suficiente para realizar a transferência, caso contrário, exibe uma mensagem de erro
        for(int co = 0; co< contadorContas; co++){
            if(contas[co].numero == contaOrigem.numero){ //Verifica se o número da conta de origem é igual ao número da conta de origem que deseja realizar a transferência
                for(int cd = 0; cd < contadorContas; cd++){
                    if(contas[cd].numero == contaDestino.numero){ //Verifica se o número da conta de destino é igual ao número da conta de destino que deseja realizar a transferência
                        if(contas[co].saldo >= valor){ //Verifica se o saldo da conta de origem é suficiente para realizar a transferência, caso contrário, exibe uma mensagem de erro
                            contas[co].saldo -= valor;
                            contas[cd].saldo += valor;
                            contas[co].saldo_total = atualizarSaldoTotal(contas[co]);
                            contas[cd].saldo_total = atualizarSaldoTotal(contas[cd]);
                            printf("Transferência realizada com sucesso!\n\n");
                            Sleep(2000); //tempo de resposta do programa em 2 segundos
                            menu();
                        }else{
                            float valorRestante = valor - contas[co].saldo; //Calcula o valor restante para realizar a transferência, subtraindo o saldo da conta de origem do valor da transferência
                            contas[co].limite -= valorRestante; //Realiza a transferência, subtraindo o valor restante do limite da conta de origem
                            contas[co].saldo = 0.0; //Zera o saldo da conta de origem, pois o valor da transferência é maior que o saldo
                            contas[cd].saldo += valor; //Realiza a transferência, somando o valor ao saldo da conta de destino
                            contas[co].saldo_total = atualizarSaldoTotal(contas[co]); //Atualiza o saldo total da conta de origem, somando o saldo e o limite
                            contas[cd].saldo_total = atualizarSaldoTotal(contas[cd]); //Atualiza o saldo total da conta de destino, somando o saldo e o limite
                            printf("Transferência realizada com sucesso!\n\n");
                            Sleep(2000); //tempo de resposta do programa em 2 segundos
                            menu();
                    };
                };
            };
        };
    };

    } else {
        printf("Saldo insuficiente para realizar a transferência.\n\n");
        Sleep(2000); //tempo de resposta do programa em 2 segundos
        menu();
    };
};

void efetuarSaque(){ //Realiza o processo para efetuar o saque, solicitando o número da conta e o valor do saque, além de verificar se há contas cadastradas para realizar o saque, caso contrário, exibe uma mensagem de erro
    if(contadorContas>0){
        int numeroConta;
        printf("Digite o número da conta para realizar o saque: ");
        scanf("%d", &numeroConta);

        Conta conta = buscarContaPorNumero(numeroConta);

        if(conta.numero == numeroConta){
            float valorSaque;
            printf("Digite o valor do saque: ");
            scanf("%f", &valorSaque);
            sacar(conta, valorSaque);
            printf("Saque realizado com sucesso!\n\n");
            Sleep(2000); //tempo de resposta do programa em 2 segundos
            menu();
        } else {
            printf("Conta não encontrada.\n\n");
            Sleep(2000); //tempo de resposta do programa em 2 segundos
            menu();
        };
        
    } else {
        printf("Não há contas cadastradas para realizar o saque.\n\n");
        Sleep(2000); //tempo de resposta do programa em 2 segundos
        menu();
    };
};

void efetuarDeposito(){ //Realiza o processo para efetuar o depósito, solicitando o número da conta e o valor do depósito, além de verificar se há contas cadastradas para realizar o depósito, caso contrário, exibe uma mensagem de erro
    if(contadorContas>0){
        int numeroConta;
        printf("Digite o número da conta para realizar o depósito: ");
        scanf("%d", &numeroConta);

        Conta conta = buscarContaPorNumero(numeroConta);

        if(conta.numero == numeroConta){
            float valorDeposito;
            printf("Digite o valor do depósito: ");
            scanf("%f", &valorDeposito);
            depositar(conta, valorDeposito);
            printf("Depósito realizado com sucesso!\n\n");
            Sleep(2000); //tempo de resposta do programa em 2 segundos
            menu();
        } else {
            printf("Conta não encontrada.\n\n");
            Sleep(2000); //tempo de resposta do programa em 2 segundos
            menu();
        };
        
    } else {
        printf("Não há contas cadastradas para realizar o depósito.\n\n");
        Sleep(2000); //tempo de resposta do programa em 2 segundos
        menu();
    };
};

void efetuarTransferencia(){ //Realiza o processo para efetuar a transferência, solicitando o número da conta de origem, o número da conta de destino e o valor da transferência, além de verificar se há contas cadastradas para realizar a transferência, caso contrário, exibe uma mensagem de erro
    if(contadorContas>0){
        int numeroContaOrigem, numeroContaDestino;
        printf("Digite o número da sua conta para realizar a transferência: ");
        scanf("%d", &numeroContaOrigem);

        Conta conta_o = buscarContaPorNumero(numeroContaOrigem);

        if(conta_o.numero == numeroContaOrigem){
            printf("Digite o número da conta de destino para realizar a transferência: ");
            scanf("%d", &numeroContaDestino);

            Conta conta_d = buscarContaPorNumero(numeroContaDestino);
            if(conta_d.numero == numeroContaDestino){
                float valorTransferencia;
                printf("Digite o valor da transferência: ");
                scanf("%f", &valorTransferencia);
                transferir(conta_o, conta_d, valorTransferencia);
                printf("Transferência realizada com sucesso!\n\n");
                Sleep(2000); //tempo de resposta do programa em 2 segundos
                menu();
            } else {
                printf("Conta de destino não encontrada.\n\n");
                Sleep(2000); //tempo de resposta do programa em 2 segundos
                menu();
            };
            
        } else {
            printf("Conta de origem não encontrada.\n\n");
            Sleep(2000); //tempo de resposta do programa em 2 segundos
            menu();
        };

        
    } else {
        printf("Não há contas cadastradas para realizar a transferência.\n\n");
        Sleep(2000); //tempo de resposta do programa em 2 segundos
        menu();
    };
};

void listarContas(){ //Lista as contas cadastradas, verificando se há contas cadastradas para listar, caso contrário, exibe uma mensagem de erro
    if(contadorContas>0){
        printf("Contas cadastradas:\n\n");
        for(int i = 0; i < contadorContas; i++){
            printf("Conta %d:\n", contas[i].numero);
            infoConta(contas[i]);
            Sleep(1000); //tempo de resposta do programa em 1 segundo para mostrar as informações de cada conta, caso contrário, as informações de todas as contas seriam mostradas de uma vez, o que poderia ser confuso para o usuário, caso haja muitas contas cadastradas
        };
    } else {
        printf("Não há contas cadastradas.\n\n");
    };

    Sleep(2000); //tempo de resposta do programa em 2 segundos
    menu();
};

