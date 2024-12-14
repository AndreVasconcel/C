#include <stdio.h>

#define MAX_TOKENS 100
#define COMPRIMENTO_MAXIMO_DO_TOKEN 50

typedef struct {
    char lexema[COMPRIMENTO_MAXIMO_DO_TOKEN];
    char tipo_token[COMPRIMENTO_MAXIMO_DO_TOKEN];
} Token;

// Função para copiar strings
void copia_string(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

// Função para determinar o comprimento de uma string
int comprimento_string(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Função para verificar se um caractere é espaço em branco
int espaco_branco(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

// Função para verificar se um caractere é letra
int letra(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Função para verificar se um caractere é dígito
int digito(char c) {
    return c >= '0' && c <= '9';
}

// Função para adicionar um token à lista de tokens
void adiciona_token(Token *tokens, int *conta_tokens, const char *lexema, const char *tipo_token) {
    copia_string(tokens[*conta_tokens].lexema, lexema);
    copia_string(tokens[*conta_tokens].tipo_token, tipo_token);
    (*conta_tokens)++;
}

// Divide a string em tokens
void tokeniza(const char *expressao, Token *tokens, int *conta_tokens) {
    int index = 0;
    char token_atual[COMPRIMENTO_MAXIMO_DO_TOKEN] = "";
    int comprimento_token_atual = 0;

    while (expressao[index] != '\0') {
        char c = expressao[index];

        // Ignora espaços em branco
        if (espaco_branco(c)) {
            index++;
            continue;
        }

        // Identificador (começa com letra e pode conter letras e números)
        if (letra(c)) {
            while (letra(expressao[index]) || digito(expressao[index]) || expressao[index] == '_') {
                token_atual[comprimento_token_atual++] = expressao[index];
                index++;
            }
            token_atual[comprimento_token_atual] = '\0';
            adiciona_token(tokens, conta_tokens, token_atual, "IDENTIFICADOR");
            comprimento_token_atual = 0;
            token_atual[0] = '\0';
            continue;
        }

        // Número inteiro
        if (digito(c)) {
            while (digito(expressao[index])) {
                token_atual[comprimento_token_atual++] = expressao[index];
                index++;
            }
            token_atual[comprimento_token_atual] = '\0';
            adiciona_token(tokens, conta_tokens, token_atual, "LITERALINTEIRO");
            comprimento_token_atual = 0;
            token_atual[0] = '\0';
            continue;
        }

        // Parênteses, operadores de soma, subtração, multiplicação e divisão
        switch (c) {
            case '(':
                adiciona_token(tokens, conta_tokens, "(", "PARENTESESESQUERDO");
                break;
            case ')':
                adiciona_token(tokens, conta_tokens, ")", "PARENTESESDIREITO");
                break;
            case '+':
                adiciona_token(tokens, conta_tokens, "+", "OPSOMA");
                break;
            case '-':
                adiciona_token(tokens, conta_tokens, "-", "OPSUBTRACAO");
                break;
            case '*':
                adiciona_token(tokens, conta_tokens, "*", "OPMULTIPLICACAO");
                break;
            case '/':
                adiciona_token(tokens, conta_tokens, "/", "OPDIVISAO");
                break;
            default:
                token_atual[0] = c;
                token_atual[1] = '\0';
                adiciona_token(tokens, conta_tokens, token_atual, "NAORECONHECIDO");
                break;
        }
        index++;
    }
}

int main() {
    char entrada[COMPRIMENTO_MAXIMO_DO_TOKEN * MAX_TOKENS];
    printf("Digite a expressão matemática: ");
    scanf("%[^\n]", entrada);

    Token tokens[MAX_TOKENS];
    int conta_tokens = 0;

    tokeniza(entrada, tokens, &conta_tokens);

    printf("Tokens:\n");
    for (int i = 0; i < conta_tokens; i++) {
        printf("Lexema %s e Token %s\n", tokens[i].lexema, tokens[i].tipo_token);
    }

    return 0;
}