#include <stdio.h>

#define MAX_ALUNOS 100

struct Aluno {
    char nome[100];
    float nota1;
    float nota2;
};

int main() {
    FILE *arquivo;
    arquivo = fopen("DadosEntrada.csv", "r");

    if (arquivo == NULL) {
        printf("Não foi possível abrir o arquivo de entrada.\n");
        return 1;
    }

    struct Aluno alunos[MAX_ALUNOS];
    int numAlunos = 0;

    // Ignorar o cabeçalho
    char cabecalho[256];
    fgets(cabecalho, sizeof(cabecalho), arquivo);

    // Ler os dados dos alunos
    while (numAlunos < MAX_ALUNOS && fscanf(arquivo, "%99[^,],%f,%f\n",
                                           alunos[numAlunos].nome,
                                           &alunos[numAlunos].nota1,
                                           &alunos[numAlunos].nota2) != EOF) {
        numAlunos++;
    }

    fclose(arquivo);

    printf("Alunos Aprovados:\n");
    printf("Nome\tMédia\n");

    for (int i = 0; i < numAlunos; i++) {
        float media = (alunos[i].nota1 + alunos[i].nota2) / 2.0;
        if (media >= 7.0) {
            printf("%s\t%.2f\n", alunos[i].nome, media);
        }
    }

    printf("\nAlunos Reprovados:\n");
    printf("Nome\tMédia\n");

    for (int i = 0; i < numAlunos; i++) {
        float media = (alunos[i].nota1 + alunos[i].nota2) / 2.0;
        if (media < 7.0) {
            printf("%s\t%.2f\n", alunos[i].nome, media);
        }
    }

    // Abrir o arquivo de saída
    FILE *saida;
    saida = fopen("SituacaoFinal.csv", "w");

    if (saida == NULL) {
        printf("Não foi possível criar o arquivo de saída.\n");
        return 1;
    }

    // Escrever os dados no arquivo de saída
    for (int i = 0; i < numAlunos; i++) {
        float media = (alunos[i].nota1 + alunos[i].nota2) / 2.0;
        const char *situacao = (media >= 7.0) ? "APROVADO" : "REPROVADO";
        fprintf(saida, "%s, %.2f, %s\n", alunos[i].nome, media, situacao);
    }

    fclose(saida);

    printf("Arquivo 'SituacaoFinal.csv' criado com sucesso.\n");

    return 0;
}
