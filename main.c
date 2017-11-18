#include <stdio.h>
#include <stdlib.h>

#include "tinyexpr.h"

/// Integration method: Simpson Second Rule
/// Developed by:
///     Antônio Carlos
///     Diogo Alves
///     Gustavo Loschi
///     Ryan Lemes
/// For Numeral calculus discipline

void Menu()
{
    system("cls");
    printf("Trabalho desenvolvido por:\n");
    printf("Antonio Carlos\n");
    printf("Diogo Alves\n");
    printf("Gustavo Loschi\n");
    printf("Ryan Lemes\n");
    system("pause");

    system("cls");
    printf("\n\n\n");
    printf("Segunda Regra de Simpson (nao é aquele simpson)\n");
    system("pause");

}


float Simpson_Second_Rule(double *yi, double *ci, int n, float h)
{
    float somatorio = 0, divisao;
    int i;

    divisao = (3*h)/8;

    for(i = 0; i <= n; i++)
    {
        somatorio += (yi[i] * ci[i]);
    }
    return (divisao * somatorio);
}


int main()
{
    float espacamento, resultado;
    float a, b;
    double *ci;
    double *yi;
    double *xi;
    int i, n;

    Menu();

    ///Variaveis para Resolução de Função
    double x;
    int error;
    char expres[256];

    printf("Digite expressao da integral: \n");
    scanf("%s", expres);

    te_variable variavel[]  = {{"x", &x}};
    te_expr * funcao = te_compile(expres, variavel, 1, &error);
    ///--------------------------------
    if(funcao)
    {
        /// Pegar valores de a, b e n
        printf("Digite a (primeiro intervalo da integral): \n");
        scanf("%f", &a);

        printf("Digite b (segundo intervalo da integral): \n");
        scanf("%f", &b);

        printf("Digite n (numero de subintervalos): \n");
        scanf("%d", &n);

        ci = (double*)calloc(n, sizeof(double));
        yi = (double*)calloc(n, sizeof(double));
        xi = (double*)calloc(n, sizeof(double));

        espacamento = (b - a) / n;
        xi[0] = a;
        xi[n] = b;
        ci[0] = ci[n] = 1;

        x = a;
        double resp = te_eval(funcao);
        yi[0] = resp;

        x = b;
        yi[n] = resp = te_eval(funcao);

        for(i = 1; i < n ; i++)
        {
            xi[i] = xi[i - 1] + espacamento;

            x = xi[i];
            yi[i] = resp = te_eval(funcao);

            if(i % 3 == 0)
                ci[i] = 2;
            else
                ci[i] = 3;
        }
    }

    resultado = Simpson_Second_Rule(yi, ci, n, espacamento);

    printf("\nO resultado da integral eh: %f\n\n", resultado);

    return 42;
}
