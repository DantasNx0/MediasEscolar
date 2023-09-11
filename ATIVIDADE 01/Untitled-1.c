#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 100
#define MAX_NOTAS 10

// Estrutura para representar um aluno
typedef struct {
    char nome[MAX_NOME];
    char telefone[MAX_NOME];
    char curso[MAX_NOME];
    double notas[MAX_NOTAS];
} Aluno;

// Função para calcular a média das notas
double calcularMedia(double notas[], int numNotas) {
    double soma = 0.0;
    for (int i = 0; i < numNotas; i++) {
        soma += notas[i];
    }
    return soma / numNotas;
}

// Função para determinar a situação do aluno
const char *determinarSituacao(double media) {
    return (media >= 7.0) ? "APROVADO" : "REPROVADO";
}

int main() {
    FILE *entrada = fopen("\\DadosEntrada.csv", "r");
    FILE *saida = fopen("\\SituacaoFinal.csv", "w");

    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return 1;
    }

    // Escreve o cabeçalho no arquivo de saída
    fprintf(saida, "Nome,Nota Média,Situação\n"); 

    // Buffer para armazenar cada linha do arquivo de entrada
    char linha[1000]; 
    Aluno aluno;

    while (fgets(linha, sizeof(linha), entrada) != NULL) {
        // Divide a linha em campos separados por vírgula
        char *token = strtok(linha, ",");
        strcpy(aluno.nome, token);

        token = strtok(NULL, ",");
        strcpy(aluno.telefone, token);

        token = strtok(NULL, ",");
        strcpy(aluno.curso, token);

        int numNotas = 0;
        double somaNotas = 0.0;

        while ((token = strtok(NULL, ",")) != NULL && numNotas < MAX_NOTAS) {
            aluno.notas[numNotas++] = atof(token);
            somaNotas += aluno.notas[numNotas - 1];
        }

        // Calcula a média das notas e determina a situação
        double media = calcularMedia(aluno.notas, numNotas);
        const char *situacao = determinarSituacao(media);

        // Escreve os resultados no arquivo de saída
        fprintf(saida, "%s,%.2lf,%s\n", aluno.nome, media, situacao);
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}
