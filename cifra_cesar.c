6/*
 * Atividade 02 - Cifra de Cesar com sequencias numericas
 

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "sequencias.h"


void escrever_log(char texto[]) {
    FILE *f = fopen("log_execucao.txt", "a");
    char hora[30];
    time_t agora = time(NULL);

    if (f == NULL) {
        return;
    }
    strftime(hora, sizeof(hora), "%d/%m/%Y %H:%M:%S", localtime(&agora));
    fprintf(f, "[%s] %s\n", hora, texto);
    fclose(f);
}


int palavra_valida(char palavra[]) {
    int i;
    int tamanho = strlen(palavra);

    if (tamanho < 1 || tamanho > 15) {
        return 0;
    }
    for (i = 0; i < tamanho; i++) {
        if (!isalpha(palavra[i])) {
            return 0;
        }
        palavra[i] = tolower(palavra[i]);
    }
    return 1;
}


void processar(char palavra[], int shift, int tipo, int direcao, char resultado[]) {
    int i, seq, desloc, pos, nova;
    int tamanho = strlen(palavra);
    char msg[100];

    for (i = 0; i < tamanho; i++) {
        seq = sequencia(tipo, i);
        desloc = shift + seq;
        pos = palavra[i] - 'a';                      
        nova = ((pos + direcao * desloc) % 26 + 26) % 26;   
        resultado[i] = 'a' + nova;

        sprintf(msg, "Letra %d: %c | deslocamento %d + %d = %d | vira %c",
                i + 1, palavra[i], shift, seq, desloc, resultado[i]);
        escrever_log(msg);
    }
    resultado[tamanho] = '\0';
}


void limpar_teclado(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}


int pedir_dados(char palavra[], int *shift, int *tipo, int pedir_tipo) {
    printf("Palavra (ate 15 letras, sem acentos): ");
    scanf("%63s", palavra);
    if (!palavra_valida(palavra)) {
        printf("Erro: a palavra deve ter de 1 a 15 letras, sem acentos, numeros ou simbolos.\n");
        return 0;
    }

    printf("SHIFT (0 a 25): ");
    if (scanf("%d", shift) != 1 || *shift < 0 || *shift > 25) {
        printf("Erro: SHIFT invalido.\n");
        limpar_teclado();
        return 0;
    }

    if (pedir_tipo == 1) {
        printf("Tipo (1-PA, 2-PG, 3-Fibonacci, 4-Primos): ");
        if (scanf("%d", tipo) != 1 || *tipo < 1 || *tipo > 4) {
            printf("Erro: tipo de sequencia invalido.\n");
            limpar_teclado();
            return 0;
        }
    }
    return 1;
}

int main() {
    int opcao, shift, tipo, i;
    char palavra[64], resultado[64], msg[150];
    FILE *arq;

    while (1) {
        printf("\n1 - Criptografar\n2 - Descriptografar\n3 - Comparar sequencias\n0 - Sair\nOpcao: ");
        if (scanf("%d", &opcao) != 1) {
            limpar_teclado();
            opcao = -1;
        }

        if (opcao == 0) {
            printf("Encerrando.\n");
            break;
        }

        if (opcao == 1) {
            if (pedir_dados(palavra, &shift, &tipo, 1) == 0) {
                continue;
            }
            sprintf(msg, "Criptografar '%s' | SHIFT %d | Tipo %d", palavra, shift, tipo);
            escrever_log(msg);

            processar(palavra, shift, tipo, 1, resultado);
            printf("Palavra criptografada: %s\n", resultado);

            arq = fopen("resultado_criptografia.txt", "w");
            if (arq == NULL) {
                printf("Erro ao gravar o arquivo.\n");
                escrever_log("ERRO ao gravar resultado_criptografia.txt");
            } else {
                fprintf(arq, "Palavra codificada: %s | SHIFT: %d | Tipo: %d | Letras: %d\n",
                        resultado, shift, tipo, (int)strlen(resultado));
                fclose(arq);
                printf("Resultado gravado em resultado_criptografia.txt\n");
                escrever_log("Resultado gravado em resultado_criptografia.txt");
            }
        }
        else if (opcao == 2) {
            if (pedir_dados(palavra, &shift, &tipo, 1) == 0) {
                continue;
            }
            sprintf(msg, "Descriptografar '%s' | SHIFT %d | Tipo %d", palavra, shift, tipo);
            escrever_log(msg);

            processar(palavra, shift, tipo, -1, resultado);
            printf("Palavra original: %s\n", resultado);
        }
        else if (opcao == 3) {
            if (pedir_dados(palavra, &shift, &tipo, 0) == 0) {
                continue;
            }
            sprintf(msg, "Comparar sequencias para '%s' | SHIFT %d", palavra, shift);
            escrever_log(msg);

            printf("\nSem sequencia (so Cesar): ");
            for (i = 0; i < (int)strlen(palavra); i++) {
                putchar('a' + (palavra[i] - 'a' + shift) % 26);
            }
            printf("\n");

            arq = fopen("resultado_criptografia.txt", "w");
            for (tipo = 1; tipo <= 4; tipo++) {
                processar(palavra, shift, tipo, 1, resultado);
                printf("Tipo %d -> %s\n", tipo, resultado);
                if (arq != NULL) {
                    fprintf(arq, "Palavra codificada: %s | SHIFT: %d | Tipo: %d | Letras: %d\n",
                            resultado, shift, tipo, (int)strlen(resultado));
                }
            }
            if (arq != NULL) {
                fclose(arq);
                printf("Resultados gravados em resultado_criptografia.txt\n");
            }
        }
        else {
            printf("Opcao invalida.\n");
        }
    }

    return 0;
}
