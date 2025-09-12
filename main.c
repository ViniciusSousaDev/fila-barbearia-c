#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>  // Para a função sleep()

typedef struct Cliente {
  char *nome_cliente;
  char *tipo_corte;
  struct Cliente *proximo;
} Cliente;

typedef struct FilaEspera {
  Cliente **elementos;
  int inicio, fim, tamanho;
} FilaEspera;

FilaEspera *createFila() {
  FilaEspera *fila = (FilaEspera *)malloc(sizeof(FilaEspera));
  fila->inicio = 0;
  fila->fim = -1;
  fila->tamanho = 0;
  fila->elementos = malloc(sizeof(Cliente *) * 100);
  return fila;
}

int filaVazia(FilaEspera *fila) { return fila->tamanho == 0; }

void adicionarCliente(FilaEspera *fila, char *nome_cliente, char *tipo_corte) {
  Cliente *novoCliente = (Cliente *)malloc(sizeof(Cliente));
  novoCliente->nome_cliente = strdup(nome_cliente);
  novoCliente->tipo_corte = strdup(tipo_corte);
  novoCliente->proximo = NULL;

  fila->fim = (fila->fim + 1) % 100;
  fila->elementos[fila->fim] = novoCliente;
  fila->tamanho++;

  printf("%s é o próximo a receber o serviço: %s.\n", nome_cliente, tipo_corte);
  printf("+--------------------------------------------------------------+\n");
}

void proximoCliente(FilaEspera *fila) {
  if (filaVazia(fila)) {
    printf("Não há mais clientes na fila de espera.\n");
    printf(
        "+--------------------------------------------------------------+\n");
    return;
  }

  Cliente *clienteAtendido = fila->elementos[fila->inicio];

  printf("Próximo cliente a ser atendido: %s (Serviço: %s)\n",
         clienteAtendido->nome_cliente, clienteAtendido->tipo_corte);
  printf("+--------------------------------------------------------------+\n");

  free(clienteAtendido->nome_cliente);
  free(clienteAtendido->tipo_corte);
  free(clienteAtendido);

  fila->inicio = (fila->inicio + 1) % 100;
  fila->tamanho--;
}

void freeFilaEspera(FilaEspera *fila) {
  for (int i = 0; i < fila->tamanho; i++) {
    Cliente *temp = fila->elementos[i];
    free(temp->nome_cliente);
    free(temp->tipo_corte);
    free(temp);
  }
  free(fila->elementos);
  free(fila);
}

int quantidadeClientesFila(FilaEspera *fila) { return fila->tamanho; }

int apenasNumeros(char *str) {
  int i = 0;
  while (str[i]) {
    if (!isdigit(str[i])) {
      return 0;
    }
    i++;
  }
  return 1;
}

int selecionarTipoCorte(char *tipo_corte) {
  char input[100];
  int opcao;
  while (1) {
    printf("Escolha o tipo de corte:\n");
    printf("1. Corte de Cabelo\n");
    printf("2. Corte de Barba e Cabelo\n");
    printf("3. Barba\n");
    printf("4. Sobrancelha\n");
    printf("5. Luzes\n");
    printf("6. Pézinho\n");
    printf(
        "+--------------------------------------------------------------+\n");
    printf("Tipo de Corte: ");
    scanf("%s", input);
    printf(
        "+--------------------------------------------------------------+\n");

    if (!apenasNumeros(input)) {
      printf("Entrada inválida. Digite apenas números.\n");
      printf(
          "+--------------------------------------------------------------+\n");
      continue;
    }
    opcao = atoi(input);

    switch (opcao) {
    case 1:
      strcpy(tipo_corte, "Corte de Cabelo");
      return 1;
    case 2:
      strcpy(tipo_corte, "Corte de Barba e Cabelo");
      return 1;
    case 3:
      strcpy(tipo_corte, "Barba");
      return 1;
    case 4:
      strcpy(tipo_corte, "Sobrancelha");
      return 1;
    case 5:
      strcpy(tipo_corte, "Luzes");
      return 1;
    case 6:
      strcpy(tipo_corte, "Pézinho");
      return 1;
    default:
      printf(
          "Tipo de Corte inválido. Por favor, selecione uma opção correta.\n");
      printf(
          "+--------------------------------------------------------------+\n");
    }
  }
}

int main() {
  FilaEspera *barbearia = createFila();
  int escolha;
  char input[100];
  char nome_cliente[100];
  char tipo_corte[100];
  
  while (1) {
    printf("Eae Chefe, o que tem pra hoje?\n");
    printf("\nQuantidade de clientes na fila: %d\n",
           quantidadeClientesFila(barbearia));
    printf("\nEscolha uma ação:\n");
    printf("1. Inserir cliente na fila de espera\n");
    printf("2. Atender próximo cliente na fila de espera\n");
    printf("3. Sair\n");
    printf(
        "+--------------------------------------------------------------+\n");
    printf("Ação: ");
    scanf("%s", input);
    printf(
        "+--------------------------------------------------------------+\n");
    if (!apenasNumeros(input)) {
      printf("Entrada inválida. Digite apenas números.\n");
      printf(
          "+--------------------------------------------------------------+\n");
      continue;
    }
    escolha = atoi(input);

    switch (escolha) {
    case 1:
      printf("Digite o nome do cliente: ");
      scanf(" %[^\n]", nome_cliente);
      printf(
          "+--------------------------------------------------------------+\n");

      while (!selecionarTipoCorte(tipo_corte)) {
      }
      adicionarCliente(barbearia, nome_cliente, tipo_corte);
      break;

    case 2:
      proximoCliente(barbearia);
      break;
    case 3:
      freeFilaEspera(barbearia);
      printf("Programa encerrado.\n");
      return 0;
    default:
      printf("Opção inválida. Tente novamente.\n");
    }
  }
  return 0;
}
