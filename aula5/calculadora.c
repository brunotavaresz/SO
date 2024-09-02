#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Uso correto: ./calculadora <número> <operação> <número>\n");
        return 1;
    }

    double num1 = strtod(argv[1], NULL); // converte string para double
    double num2 = strtod(argv[3], NULL); // converte string para double

    if (argv[2][0] == '+') { // argv[2][0] é o primeiro caractere da string argv[2]
        printf("%.2f\n", num1 + num2);
    } else if (argv[2][0] == '-') {
        printf("%.2f\n", num1 - num2);
    } else if (argv[2][0] == '*' || argv[2][0] == 'x') { // x é um sinônimo de *
        printf("%.2f\n", num1 * num2);
    } else if (argv[2][0] == '/') {
        if (num2 == 0) {
            printf("Erro: Divisão por zero.\n");
            return 1;
        }
        printf("%.2f\n", num1 / num2); 
    } else if (argv[2][0] == 'p') {
        printf("%.2f\n", pow(num1, num2)); // num1 elevado a num2
    } else {
        printf("Operação inválida: %c\n", argv[2][0]);
        return 1;
    }

    return 0;
}
