#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

// Anotação 1
#define TAMANHO_NOTA 521 // Limite da escrita
#define TAMANHO_DATA 11 // "DD/MM/AAAA"
#define TAMANHO_TITULO 101

// Arvore
typedef struct NoArvore {
    char texto[TAMANHO_NOTA];
    char data[TAMANHO_DATA];
    char titulo[TAMANHO_TITULO];
    struct NoArvore* esquerdo;
    struct NoArvore* direito;
} NoArvore;

// Funções
int validarData(char* data);
int compararComDataAtual(char* data);
void inserirNo(NoArvore** centro, const char* data, const char* titulo, const char* texto);
int compararDatas(const char* data1, const char* data2);
void exibirArvore(NoArvore* centro, int nivel);
NoArvore* criarNo(const char* data, const char* titulo, const char* texto);
NoArvore* excluirNo(NoArvore* centro, const char* data, const char* titulo);
void adicionarNota(NoArvore** centro);
void lerNota(NoArvore* centro, const char* data, const char* titulo);
void excluirNota(NoArvore** centro);
void sair();

void salvarDiario(NoArvore* centro, FILE* arquivo) {
	if (centro == NULL) {
	    return;
	}
	
	fprintf(arquivo, "%s|%s|%s\n", centro->data, centro->titulo, centro->texto);
	salvarDiario(centro->esquerdo, arquivo);
	salvarDiario(centro->direito, arquivo);
}

char data[TAMANHO_DATA];
char titulo[TAMANHO_TITULO];

void carregarDiario(NoArvore** centro, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo \"%s\". Verifique se o arquivo existe.\n", nomeArquivo);
        return;
    }

    printf("Carregando o diário...\n");

    char linha[700]; 
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char data[TAMANHO_DATA];
        char titulo[TAMANHO_TITULO];
        char texto[TAMANHO_NOTA];
        
        if (sscanf(linha, "%[^|]|%[^|]|%[^\n]", data, titulo, texto) == 3) {
            inserirNo(centro, data, titulo, texto);
        } else {
            printf("Linha inválida no arquivo: %s\n", linha);
        }
    }

    fclose(arquivo);
    printf("Diário carregado com sucesso.\n");
}

int main() {
    setlocale(LC_ALL, "");
    printf("Bem-vindo ao Diário em C!\n");

    NoArvore* centro = NULL;
    
    carregarDiario(&centro, "diario.txt");
    
    int opcao;
    do {
        printf("\n===== MENU =====\n");
        printf("1. Nova Nota.\n"); // Para registrar nova anotação no diário
        printf("2. Ler diário.\n"); // Ler alguma nota de uma data especifica
        printf("3. Excluir Nota.\n"); // Remover alguma anotação de acordo com a data.
        printf("4. Sair\n");
        printf("================\n");
        printf("\nEscolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                adicionarNota(&centro);
                break;

            case 2:
                printf("\nExibindo todas as notas do diário:\n");
    			exibirArvore(centro, 0);
    			
			    printf("\nDeseja abrir uma nota específica? (S/N): ");
			    char resposta;
				scanf(" %c", &resposta);
			    getchar();
			    
			    if (resposta == 'S' || resposta == 's') {
			    	printf("Digite o título da nota que deseja ler: ");
			        fgets(titulo, TAMANHO_TITULO, stdin);
			        titulo[strcspn(titulo, "\n")] = '\0';
			        
					printf("\nDigite a data da nota que deseja ler (DD/MM/AAAA): ");
			        fgets(data, TAMANHO_DATA, stdin);
			        data[strcspn(data, "\n")] = '\0';
			
        			printf("\nBuscando nota...\n");
        			lerNota(centro, data, titulo);
        			
		        } else {
        			printf("\nRetornando ao menu principal...\n");
        		}
    			
                break;

            case 3:

				printf("\nDigite a data da nota que deseja excluir (DD/MM/AAAA) ou digite 'X' para cancelar: ");
			    fgets(data, TAMANHO_DATA, stdin);
			    data[strcspn(data, "\n")] = '\0';
			
			    if (strcmp(data, "X") == 0 || strcmp(data, "x") == 0) {
			        printf("\nExclusão cancelada.\n");
			        break;
			    }
			
			    // Limpa o buffer antes de ler o título
			    int c;
			    while ((c = getchar()) != '\n' && c != EOF);
			
			    printf("Digite o título da nota que deseja excluir ou digite 'X' para cancelar: ");
			    fgets(titulo, TAMANHO_TITULO, stdin);
			    titulo[strcspn(titulo, "\n")] = '\0';
			
			    if (strcmp(titulo, "X") == 0 || strcmp(titulo, "x") == 0) {
			        printf("\nExclusão cancelada.\n");
			        break;
			    }
			
			    // Continua com a exclusão se ambos os valores forem fornecidos
			    centro = excluirNo(centro, data, titulo); // Atualiza a raiz da árvore
			    printf("\nNota excluída com sucesso (se existia).\n");
			    break;

            case 4:
                printf("\nSalvando o diário...\n");
		        FILE* arquivoSalvar = fopen("diario.txt", "w");
		        if (arquivoSalvar == NULL) {
		            printf("Erro ao abrir o arquivo para salvar o diário.\n");
		        } else {
		            salvarDiario(centro, arquivoSalvar);
		            fclose(arquivoSalvar);
		            printf("Diário salvo com sucesso!\n");
		        }
		        printf("\nSaindo do Diário...\n");
		        break;

            default:
                printf("Ops! Tente novamente.\n");
        }
    } while (opcao != 4);

    return 0;
}


NoArvore* criarNo(const char* data, const char* titulo, const char* texto) {
    NoArvore* novoNo = (NoArvore*)malloc(sizeof(NoArvore));
    if (novoNo == NULL) {
        fprintf(stderr, "Erro de alocação de memória!\n");
        exit(1);
    }
    strcpy(novoNo->data, data);
    strcpy(novoNo->titulo, titulo);
    strcpy(novoNo->texto, texto);
    novoNo->esquerdo = NULL;
    novoNo->direito = NULL;
    return novoNo;
}

void inserirNo(NoArvore** centro, const char* data, const char* titulo, const char* texto) {
    if (*centro == NULL) {
        *centro = criarNo(data, titulo, texto);
    } else {
        if (compararDatas(data, (*centro)->data) < 0) {
            inserirNo(&((*centro)->esquerdo), data, titulo, texto);
        } else {
            inserirNo(&((*centro)->direito), data, titulo, texto);
        }
    }
}

void lerNota(NoArvore* centro, const char* data, const char* titulo) {
    if (centro == NULL) {
        printf("Nota não encontrada.\n");
        return;
    }

    int compData = compararDatas(data, centro->data);
    if (compData < 0) {
        
        lerNota(centro->esquerdo, data, titulo);
    } else if (compData > 0) {
        
        lerNota(centro->direito, data, titulo);
    } else {
        
        if (strcmp(titulo, centro->titulo) == 0) {
            
            printf("\nNota encontrada:\n");
            printf("Data: %s\n", centro->data);
            printf("Título: %s\n", centro->titulo);
            printf("Texto: %s\n", centro->texto);
            return;
            
        } else {
            
            lerNota(centro->direito, data, titulo);
        }
    }
}

NoArvore* excluirNo(NoArvore* centro, const char* data, const char* titulo) {
    if (centro == NULL) return NULL;

    if (compararDatas(data, centro->data) < 0) {
        centro->esquerdo = excluirNo(centro->esquerdo, data, titulo);
    } else if (compararDatas(data, centro->data) > 0) {
        centro->direito = excluirNo(centro->direito, data, titulo);
    } else if (strcmp(titulo, centro->titulo) != 0) {
        // Mesmo se a data bater, o título deve ser verificado
        centro->direito = excluirNo(centro->direito, data, titulo);
    } else {

        if (centro->esquerdo == NULL) {
            NoArvore* temp = centro->direito;
            free(centro); // Libera memória
            return temp;
        } else if (centro->direito == NULL) {
            NoArvore* temp = centro->esquerdo;
            free(centro); // Libera memória
            return temp;
        } else {
            // Caso com dois filhos: encontrar o sucessor
            NoArvore* temp = centro->direito;
            while (temp->esquerdo != NULL) temp = temp->esquerdo;

            // Copia os dados do sucessor para o nó atual
            strcpy(centro->data, temp->data);
            strcpy(centro->titulo, temp->titulo);
            strcpy(centro->texto, temp->texto);

            // Remove o sucessor da subárvore direita
            centro->direito = excluirNo(centro->direito, temp->data, temp->titulo);
        }
    }
    return centro;
}

void exibirArvore(NoArvore* centro, int nivel) {
    if (centro == NULL) return;

    exibirArvore(centro->esquerdo, nivel + 1);

    for (int i = 0; i < nivel; i++) printf("  ");
    printf("Data: %s, Título: %s\n", centro->data, centro->titulo);

    exibirArvore(centro->direito, nivel + 1);
}

int compararDatas(const char* data1, const char* data2) {
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    sscanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);

    int dataNum1 = ano1 * 10000 + mes1 * 100 + dia1;
    int dataNum2 = ano2 * 10000 + mes2 * 100 + dia2;

    if (dataNum1 < dataNum2) return -1;
    if (dataNum1 > dataNum2) return 1;
    return 0;
}

void adicionarNota(NoArvore** centro) {
    char nota[TAMANHO_NOTA];
    char data[TAMANHO_DATA];
    char titulo[TAMANHO_TITULO];
    int dataValida = 0;

    while (!dataValida) {
        printf("\nQual a data de Hoje? (DD/MM/AAAA): ");
        fgets(data, TAMANHO_DATA, stdin);
        data[strcspn(data, "\n")] = 0;

        if (validarData(data) && compararComDataAtual(data)) {
            dataValida = 1;
        } else {
            printf("\nOps! Não vamos escrever sobre o passado, que tal colocar a data de hoje?.\n");
            fflush(stdin); // Testando
        }
    }

    while (1) {
        fflush(stdin); // Testando
        printf("\nQual o título de hoje? (até %d caracteres): ", TAMANHO_TITULO - 1);
        fgets(titulo, TAMANHO_TITULO, stdin);
        titulo[strcspn(titulo, "\n")] = 0;

        if (strlen(titulo) == 0) {
            printf("\nQue tal dar um título ao seu dia?\n");
        } else {
            break;
        }
    }
    // Para começar o diário
    printf("\nComo foi seu dia? (até %d caracteres): ", TAMANHO_NOTA - 1);
    fgets(nota, TAMANHO_NOTA, stdin);
    nota[strcspn(nota, "\n")] = 0;

    inserirNo(centro, data, titulo, nota);
    printf("\nNota adicionada com sucesso!\n");
}

int validarData(char *data)
{

    int i;

    for (i = 0; i < 10; i++)
    {
        if (i == 2 || i == 5)
        {
            if (data[i] != '/')
                return 0;
        }
        else
        {
            if (!isdigit(data[i]))
                return 0;
        }
    }

    if (strlen(data) != 10)
        return 0;

    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');
    int ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

    if (mes < 1 || mes > 12)
        return 0;
    int diasNoMes[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0))
        diasNoMes[1] = 29;

    if (dia < 1 || dia > diasNoMes[mes - 1])
        return 0;

    return 1; // Para a Data NÃO Retroativa
}

int compararComDataAtual(char *data)
{ // Vai servir para comparar as datas
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Lê o calendário atual
    int diaAtual = tm.tm_mday;
    int mesAtual = tm.tm_mon + 1;
    int anoAtual = tm.tm_year + 1900;

    // Analisa a data que foi inserida
    int dia = (data[0] - '0') * 10 + (data[1] - '0');
    int mes = (data[3] - '0') * 10 + (data[4] - '0');
    int ano = (data[6] - '0') * 1000 + (data[7] - '0') * 100 + (data[8] - '0') * 10 + (data[9] - '0');

    if (ano < anoAtual || (ano == anoAtual && mes < mesAtual) || (ano == anoAtual && mes == mesAtual && dia < diaAtual))
    {
        return 0; // Para a Dara Retroativa
    }

    return 1;
}

void excluirNota(NoArvore** centro) {
    printf("\nFunção de exclusão ainda não implementada.\n");
}

void sair() {
    printf("\nSaindo do diário...\n");
}
