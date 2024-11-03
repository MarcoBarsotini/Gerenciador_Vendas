// Feito por Marco Barsotini
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_CEP 10
#define TAM_LOGRADOURO 50
#define TAM_BAIRRO 30
#define TAM_CIDADE 30
#define TAM_UF 3
#define TAM_CNPJ 15
#define TAM_EMAIL 50
#define TAM_CONTATO 15

typedef struct Endereco {
    char cep[TAM_CEP];
    char logradouro[TAM_LOGRADOURO];
    char bairro[TAM_BAIRRO];
    char cidade[TAM_CIDADE];
    char uf[TAM_UF];
    struct Endereco *proximo;
} Endereco;

typedef struct Fornecedor {
    char cnpj[TAM_CNPJ];
    char nome[TAM_LOGRADOURO];
    char cep[TAM_CEP];
    char numeroLogradouro[10];
    char email[TAM_EMAIL];
    char contato[TAM_CONTATO];
    struct Fornecedor *proximo;
} Fornecedor;

Endereco *listaEnderecos = NULL;
Fornecedor *listaFornecedores = NULL;

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Começando a parte de Endereços
Endereco* criarNovoEndereco() {
    Endereco *novoEndereco = (Endereco *) malloc(sizeof(Endereco));

    printf("Digite o CEP: ");
    fgets(novoEndereco->cep, TAM_CEP, stdin);
    novoEndereco->cep[strcspn(novoEndereco->cep, "\n")] = '\0';

    if (verificarEnderecoExistente(novoEndereco->cep)) {
        printf("Erro: CEP %s já cadastrado!\n", novoEndereco->cep);
        free(novoEndereco);
        return NULL;
    }

    printf("Digite o logradouro: ");
    fgets(novoEndereco->logradouro, TAM_LOGRADOURO, stdin);
    novoEndereco->logradouro[strcspn(novoEndereco->logradouro, "\n")] = '\0';

    printf("Digite o bairro: ");
    fgets(novoEndereco->bairro, TAM_BAIRRO, stdin);
    novoEndereco->bairro[strcspn(novoEndereco->bairro, "\n")] = '\0';

    printf("Digite a cidade: ");
    fgets(novoEndereco->cidade, TAM_CIDADE, stdin);
    novoEndereco->cidade[strcspn(novoEndereco->cidade, "\n")] = '\0';

    printf("Digite o estado (UF): ");
    fgets(novoEndereco->uf, TAM_UF, stdin);
    novoEndereco->uf[strcspn(novoEndereco->uf, "\n")] = '\0';

    novoEndereco->proximo = NULL;
    return novoEndereco;
}

int verificarEnderecoExistente(char *cep) {
    Endereco *atual = listaEnderecos;
    while (atual != NULL) {
        if (strcmp(atual->cep, cep) == 0) {
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void adicionarEnderecoNaLista() {
    Endereco *novo = criarNovoEndereco();
    if (novo == NULL) return;

    if (listaEnderecos == NULL) {
        listaEnderecos = novo;
    } else {
        Endereco *atual = listaEnderecos;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

void exibirEnderecos() {
    if (listaEnderecos == NULL) {
        printf("Nenhum endereço cadastrado!\n");
        return;
    }

    Endereco *atual = listaEnderecos;
    while (atual != NULL) {
        printf("CEP: %s, Logradouro: %s, Bairro: %s, Cidade: %s, UF: %s\n",
               atual->cep, atual->logradouro, atual->bairro, atual->cidade, atual->uf);
        atual = atual->proximo;
    }
}

void alterarEndereco() {
    char cep[TAM_CEP];
    printf("Digite o CEP para alterar: ");
    fgets(cep, TAM_CEP, stdin);
    cep[strcspn(cep, "\n")] = '\0';

    Endereco *atual = listaEnderecos;
    while (atual != NULL) {
        if (strcmp(atual->cep, cep) == 0) {
            printf("Novo Logradouro: ");
            fgets(atual->logradouro, TAM_LOGRADOURO, stdin);
            atual->logradouro[strcspn(atual->logradouro, "\n")] = '\0';

            printf("Novo Bairro: ");
            fgets(atual->bairro, TAM_BAIRRO, stdin);
            atual->bairro[strcspn(atual->bairro, "\n")] = '\0';

            printf("Nova Cidade: ");
            fgets(atual->cidade, TAM_CIDADE, stdin);
            atual->cidade[strcspn(atual->cidade, "\n")] = '\0';

            printf("Novo UF: ");
            fgets(atual->uf, TAM_UF, stdin);
            atual->uf[strcspn(atual->uf, "\n")] = '\0';

            printf("Endereço alterado com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }
    printf("Endereço não encontrado!\n");
}

void removerEndereco() {
    char cep[TAM_CEP];
    printf("Digite o CEP para remover: ");
    fgets(cep, TAM_CEP, stdin);
    cep[strcspn(cep, "\n")] = '\0';

    Endereco *atual = listaEnderecos;
    Endereco *anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->cep, cep) == 0) {
            if (anterior == NULL) {
                listaEnderecos = atual->proximo;
            } else {
                anterior->proximo = atual->proximo;
            }
            free(atual);
            printf("Endereço removido com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Endereço não encontrado!\n");
}

//Fim da listagem de endereço, começando a parte de fornecedores

// Fornecedores Block
Fornecedor* criarNovoFornecedor() {
    Fornecedor *novoFornecedor = (Fornecedor *) malloc(sizeof(Fornecedor));

    printf("CNPJ: ");
    fgets(novoFornecedor->cnpj, TAM_CNPJ, stdin);
    novoFornecedor->cnpj[strcspn(novoFornecedor->cnpj, "\n")] = '\0';

    if (verificarFornecedorExistente(novoFornecedor->cnpj)) {
        printf("Erro: CNPJ %s já cadastrado!\n", novoFornecedor->cnpj);
        free(novoFornecedor);
        return NULL;
    }

    printf("Nome: ");
    fgets(novoFornecedor->nome, TAM_LOGRADOURO, stdin);
    novoFornecedor->nome[strcspn(novoFornecedor->nome, "\n")] = '\0';

    printf("CEP do fornecedor: ");
    fgets(novoFornecedor->cep, TAM_CEP, stdin);
    novoFornecedor->cep[strcspn(novoFornecedor->cep, "\n")] = '\0';

    if (!verificarEnderecoExistente(novoFornecedor->cep)) {
        printf("Erro: CEP %s não cadastrado!\n", novoFornecedor->cep);
        free(novoFornecedor);
        return NULL;
    }

    printf("Número do Logradouro: ");
    fgets(novoFornecedor->numeroLogradouro, sizeof(novoFornecedor->numeroLogradouro), stdin);
    novoFornecedor->numeroLogradouro[strcspn(novoFornecedor->numeroLogradouro, "\n")] = '\0';

    printf("Email: ");
    fgets(novoFornecedor->email, TAM_EMAIL, stdin);
    novoFornecedor->email[strcspn(novoFornecedor->email, "\n")] = '\0';

    printf("Contato: ");
    fgets(novoFornecedor->contato, TAM_CONTATO, stdin);
    novoFornecedor->contato[strcspn(novoFornecedor->contato, "\n")] = '\0';

    novoFornecedor->proximo = NULL;
    return novoFornecedor;
}

int verificarFornecedorExistente(char *cnpj) {
    Fornecedor *atual = listaFornecedores;
    while (atual != NULL) {
        if (strcmp(atual->cnpj, cnpj) == 0) {
            return 1;
        }
        atual = atual->proximo;
    }
    return 0;
}

void adicionarFornecedorNaLista() {
    Fornecedor *novo = criarNovoFornecedor();
    if (novo == NULL) return;

    if (listaFornecedores == NULL) {
        listaFornecedores = novo;
    } else {
        Fornecedor *atual = listaFornecedores;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

void exibirFornecedores() {
    if (listaFornecedores == NULL) {
        printf("Nenhum fornecedor cadastrado!\n");
        return;
    }

    Fornecedor *atual = listaFornecedores;
    while (atual != NULL) {
        printf("CNPJ: %s, Nome: %s, CEP: %s, Número: %s, Email: %s, Contato: %s\n",
               atual->cnpj, atual->nome, atual->cep, atual->numeroLogradouro, atual->email, atual->contato);
        atual = atual->proximo;
    }
}
//Fim do bloco Fornecedores

// Criação do menu :)
void menu() {
    int opcao;
    do {
        printf("\n--- MENU ---\n");
        printf("1. Adicionar Endereço\n");
        printf("2. Exibir Endereços\n");
        printf("3. Alterar Endereço\n");
        printf("4. Remover Endereço\n");
        printf("5. Adicionar Fornecedor\n");
        printf("6. Exibir Fornecedores\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1: adicionarEnderecoNaLista(); break;
            case 2: exibirEnderecos(); break;
            case 3: alterarEndereco(); break;
            case 4: removerEndereco(); break;
            case 5: adicionarFornecedorNaLista(); break;
            case 6: exibirFornecedores(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
// Fim do codigo


// Feito por Marco Barsotini
// usando o Replit pra automatização de Testes