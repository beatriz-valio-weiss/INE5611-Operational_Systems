#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

char endereco[5][30] = {"R. Conselheiro Mafra, 123", "R. João Marçal, 234", "R. Maria Eduarda, 345", "R. João Vieira, 456", "R. Tangara, 567"};
char preco[5][20] = {"RS 1250,00", "RS 1999,99", "RS 2500,00", "RS 2760,30", "RS 2040,00"};
char bairro[5][10] = {"Centro", "Trindade", "Pantanal", "Capoeiras", "Agronomica"};

typedef struct Imovel {
  char codigo[5];
  char endereco[50];
  char preco[15];
  char bairro[30];

  struct Imovel *anterior;
} Imovel;

Imovel *topoDisponiveis = NULL;
Imovel *fundoDisponiveis = NULL;

Imovel *topoEntregues = NULL;
Imovel *fundoEntregues = NULL;

pthread_mutex_t mutexInc;
pthread_mutex_t mutexPilhas;

int inc;

void popularImovel(struct Imovel *imovel) {
  pthread_mutex_lock(&mutexInc);
  sprintf(imovel->codigo, "#%d", inc++);
  pthread_mutex_unlock(&mutexInc);
  sprintf(imovel->endereco, "%s", endereco[rand() % 5]);
  sprintf(imovel->preco, "%s", preco[rand() % 5]);
  sprintf(imovel->bairro, "%s", bairro[rand() % 5]);
}

void criarImovel(int id)
{
  Imovel *novoTopoDisponivel = (struct Imovel *) malloc(sizeof(struct Imovel));
  popularImovel(novoTopoDisponivel);

  pthread_mutex_lock(&mutexPilhas);

  novoTopoDisponivel->anterior = topoDisponiveis;
  topoDisponiveis = novoTopoDisponivel;
  if(fundoDisponiveis == NULL) {
    fundoDisponiveis = topoDisponiveis;
  }

  pthread_mutex_unlock(&mutexPilhas);

  printf("CORRETOR %d adicionou Imóvel %s\n", id, novoTopoDisponivel->codigo);
  printf("----------------------------------\n");
  printf(" Codigo: %s\n"
         " Endereço: %s\n"
         " Preço: %s\n"
         " Bairro: %s\n",
         novoTopoDisponivel->codigo,
         novoTopoDisponivel->endereco,
         novoTopoDisponivel->preco,
         novoTopoDisponivel->bairro);
  printf("----------------------------------\n");
};

void removerImovel(int id) {
  pthread_mutex_lock(&mutexPilhas);
  if(topoDisponiveis != NULL) {
    printf("CORRETOR %d removeu imovel %s\n", id, topoDisponiveis->codigo);
    if(fundoDisponiveis == topoDisponiveis) {
      topoDisponiveis = NULL;
      fundoDisponiveis = NULL;   
    } else {
      Imovel *temp = topoDisponiveis;
      topoDisponiveis = topoDisponiveis->anterior;
      free(temp);
    }
  } else {
    printf("CORRETOR %d tentou remover imovel porem nao ha imoveis disponiveis\n", id);
  }
    pthread_mutex_unlock(&mutexPilhas);
}

void alugarImovel(int id, Imovel **imovel){
  if((*imovel) == NULL) {
    pthread_mutex_lock(&mutexPilhas);
    if(topoDisponiveis != NULL) {
      (*imovel) = topoDisponiveis;
      topoDisponiveis = topoDisponiveis->anterior;
      (*imovel)->anterior = NULL;
      if(topoDisponiveis == NULL) {
        fundoDisponiveis == NULL;
      }
      printf("Inquilino %d alugou imovel %s\n", id, (*imovel)->codigo);
    } else {
      printf("Inquilino %d tentou alugar imovel porem nao ha imovel disponivel\n", id);
    }
    pthread_mutex_unlock(&mutexPilhas);
  } else {
    printf("Inquilino %d tentou alugar imovel porem ja aluga um imovel\n", id);
  }
}

void entregarImovel(int id, Imovel **imovel){
  if((*imovel) != NULL) {
    char * codigo = (*imovel)->codigo;
    pthread_mutex_lock(&mutexPilhas);
    (*imovel)->anterior = topoEntregues;
    topoEntregues = (*imovel);
    if((*imovel)->anterior == NULL) {
      fundoEntregues = (*imovel);
    }
    pthread_mutex_unlock(&mutexPilhas);
    (*imovel) = NULL;
    printf("Inquilino %d entregou imovel %s\n", id, codigo);
  } else {
    printf("Inquilino %d tentou entregar imovel porem nao esta alugando imovel no momento\n", id);
  }
}

void disponibilizarImoveis(int id) {
  pthread_mutex_lock(&mutexPilhas);
  if (fundoEntregues != NULL) {
    fundoEntregues->anterior = topoDisponiveis;
    if(fundoEntregues == NULL) {
      fundoDisponiveis = fundoEntregues;
    }
    fundoEntregues = NULL;
    topoDisponiveis = topoEntregues;
    topoEntregues = NULL;
    printf("Corretor %d disponibilizou imoveis entregues\n", id);
  } else {
    printf("Corretor %d tentou disponibilizar imoveis porem nenhum foi entregue\n", id);
  }
  pthread_mutex_unlock(&mutexPilhas);
}

void *acoesInquilino(void *arg)
{
  int id = *(int *)arg;
  struct Imovel *imovelPtr;
  while (1)
  {
    alugarImovel(id, &imovelPtr);
    sleep(5 + rand() % 4);
    entregarImovel(id, &imovelPtr);
  }
}

void *acoesCorretor(void *arg)
{
  int id = *(int *)arg;
  while (1)
  {
    int i = rand() % 5;
    switch (i)
    {
    case 0:
      disponibilizarImoveis(id);
      break;
    case 1 || 2 || 3:
      criarImovel(id);
      break;
    case 4:
      removerImovel(id);
      break;
    }
    sleep(3 + rand() % 4);
  }
}

// Funcao para fins de teste
void printarDisponiveis(){
  printf("-------------- printando imoveis disponiveis --------------\n");
  Imovel *temp = topoDisponiveis;
  while(temp != NULL) {
    printf("Codigo do imóvel disponivel é: %s\n", temp->codigo);
    temp = temp->anterior;
  }
}

// Funcao para fins de teste
void printarEntregues() {
  printf("-------------- printando imoveis entregues --------------\n");
  Imovel *temp = topoEntregues;
  while(temp != NULL) {
    printf("Codigo do imóvel entregue é: %s\n", temp->codigo);
    temp = temp->anterior;
  }
}

int main(int argc, char const *argv[])
{
  int qtdC = 50; 
  int qtdI = 50;
  pthread_t corretor[qtdC], inquilino[qtdI];
  int cIds[qtdC];
  int iIds[qtdI];

  for (size_t i = 0; i < qtdC; i++)
  {
    cIds[i] = i;
    pthread_create(&corretor[i], NULL, acoesCorretor, &cIds[i]);
  }

  for (int i = 0; i < qtdI; i++)
  {
    iIds[i] = i;
    pthread_create(&inquilino[i], NULL, acoesInquilino, &iIds[i]);
  }

  pthread_exit(NULL);

  return 0;
}
