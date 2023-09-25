#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Função para remover tags HTML de uma string
void remove_html_tags(char* input) {
    int i = 0; // Índice para percorrer a string de entrada
    int j = 0; // Índice para construir a string de saída
    int in_tag = 0; // Variável de controle para determinar se estamos dentro de uma tag HTML

    while (input[i]) {
        if (input[i] == '<') {
            in_tag = 1; // Iniciamos uma tag HTML
        } else if (input[i] == '>') {
            in_tag = 0; // Finalizamos uma tag HTML
        } else if (!in_tag) {
            // Se não estamos dentro de uma tag HTML, copiamos o caractere para a string de saída
            input[j++] = input[i];
        }
        i++;
    }
    input[j] = '\0'; // Terminamos a string de saída com null-terminator
}

int main() {
    FILE* arquivo_entrada;
    FILE* arquivo_saida;
    char nome_arquivo_entrada[] = "/Users/thiago/Documents/University/Estrutura de Dados/AtividadeHTML/index.html"; // Substitua pelo caminho do seu arquivo HTML
    char nome_arquivo_saida[] = "saida.txt"; // Nome do arquivo de saída
    char linha[1000]; // Tamanho máximo da linha

    // Abrimos o arquivo de entrada
    arquivo_entrada = fopen(nome_arquivo_entrada, "r");
    if (arquivo_entrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada '%s'\n", nome_arquivo_entrada);
        return 1;
    }

    // Criamos o arquivo de saída
    arquivo_saida = fopen(nome_arquivo_saida, "w");
    if (arquivo_saida == NULL) {
        printf("Erro ao criar o arquivo de saída '%s'\n", nome_arquivo_saida);
        fclose(arquivo_entrada);
        return 1;
    }

    // Processamos cada linha do arquivo de entrada
    while (fgets(linha, sizeof(linha), arquivo_entrada)) {
        remove_html_tags(linha); // Chama a função para remover tags HTML da linha
        fprintf(arquivo_saida, "%s", linha); // Escreve a linha sem tags no arquivo de saída
    }

    // Fechamos os arquivos
    fclose(arquivo_entrada);
    fclose(arquivo_saida);

    // Exibimos uma mensagem de sucesso
    printf("As tags HTML foram removidas com sucesso. O texto sem tags foi salvo em '%s'\n", nome_arquivo_saida);

    return 0;
}
