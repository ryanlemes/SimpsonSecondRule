#include <stdio.h>
#include <stdlib.h>

#include "tinyexpr.h"

/// Integration method: Simpson Second Rule or Simpson's 3/8 rule
/// Developed by:
///     Ryan Lemes
/// For Numeral calculus discipline

const MAX_STRING_EXPRESSION = 265;

/**
 *  Calculate the Simpson's second rule or Simpson 3/8 rule
 *  params: 
 *  *yi - 
 *  *ci - 
 *  n   - The number of intervals to calculate 
 *  h   - The midpoint of all the intervals between the first and the second interval
 *  returns: 
 */
float Simpson_Second_Rule(double *yi, double *ci, int n, float h)
{
    float sum = 0, division;
    int i;

    division = (3 * h)/8;

    for (i = 0; i <= n; i++)
    {
        sum += (yi[i] * ci[i]);
    }
    return (division * sum);
}

/*
 * Initialize the variables 
 */
void initialize(double *ci, double *yi, double *xi, int n, double x, float midpointIntervals, te_expr *funcao) {
    // Intervals
    float a, b;
    int i;
    
    /// Take the values of a, b and n
    printf("First integral interval (a): \n");
    scanf("%f", &a);

    printf("Second integral interval (b): \n");
    scanf("%f", &b);

    printf("n value (number of subintervals): \n");
    scanf("%d", &n);

    ci = (double*)calloc(n, sizeof(double));
    yi = (double*)calloc(n, sizeof(double));
    xi = (double*)calloc(n, sizeof(double));

    // Calculate the midpoint between A and B with the number of intervals(n)
    midpointIntervals = (b - a) / n;

    // Set the first position of x1 as a and the last as b
    xi[0] = a;
    xi[n] = b;
    
    // The first and the last value of ci must be 1 as described on the rule
    ci[0] = ci[n] = 1;

    x = a;
    // Evaluate the function setting x to the value of A and put it on answ
    double answ = te_eval(funcao);
    
    // set anw of a to the first position of yi
    yi[0] = answ;

    x = b;
    // Evaluate the function using the value of x as B and set it to the last position of yi
    yi[n] = answ = te_eval(funcao);

    // Iterate 1 until n
    for(i = 1; i < n ; i++)
    {
        xi[i] = xi[i - 1] + midpointIntervals;

        x = xi[i];
        yi[i] = answ = te_eval(funcao);

        if(i % 3 == 0)
            ci[i] = 2;
        else
            ci[i] = 3;
    }
}

int main()
{
    float midpointIntervals, result;

    double *ci;
    double *yi;
    double *xi;
    
    int n;

    /// variables to resolute the function
    double x;
    int error;
    char expres[MAX_STRING_EXPRESSION];

    printf("Expression: \n");
    scanf("%s", expres);

    // Use library tiny expt to create the expression and validate.
    // Split all the variables on expres based on 'x'.
    te_variable variavel[]  = {{"x", &x}};

    // Create a function to calculate
    te_expr *funcao = te_compile(expres, variavel, 1, &error);

    // Check if the function is not wrong
    if (funcao)
    {
        initialize(ci, yi, xi, n, x, midpointIntervals, funcao);
    } 
    else 
    {
        printf("\nError on create the function with error code: " + error);
        return error;
    }

    // Calculate the integral using Simpson second rule
    result = Simpson_Second_Rule(yi, ci, n, midpointIntervals);

    printf("\nThe integration result is: %f\n\n", result);

    return 0;
}
