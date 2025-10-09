#include "derivadaintegral.h"
#include <math.h>

// Numerical derivative using central difference formula
double derivada(double (*f)(double x), double x, double h) {
    return (f(x + h) - f(x - h)) / (2 * h);
}

// Simpson's Rule for numerical integration
double simpson(double (*f)(double), double a, double b, int n) {
    if (n <= 0) {
        n = 100; // use a default value if n is invalid
    }

    // Ensure n is even
    if (n % 2 != 0) {
        n++;
    }

    double h = (b - a) / n;
    double sum = f(a) + f(b);

    for (int i = 1; i < n; i++) {
        if (i % 2 == 1) {  // odd indices get coefficient 4
            sum += 4.0 * f(a + i * h);
        } else {  // even indices get coefficient 2
            sum += 2.0 * f(a + i * h);
        }
    }

    return sum * h / 3.0;
}

// Recursive helper function for adaptive Simpson's method
static double adaptive_simpson_recursive(double (*f)(double), double a, double b,
                                        double tol, double s_whole, double fa, double fb, double fm, int depth) {
    // Prevent infinite recursion by limiting depth
    if (depth > 50) {
        return s_whole;
    }

    double m = (a + b) / 2.0;
    double h = (b - a) / 2.0;

    // Pontos intermediários nos subintervalos [a,m] e [m,b]
    double lm = (a + m) / 2.0;
    double rm = (m + b) / 2.0;
    double flm = f(lm);
    double frm = f(rm);

    // Simpson nos subintervalos
    double s_left = (h / 6.0) * (fa + 4.0 * flm + fm);
    double s_right = (h / 6.0) * (fm + 4.0 * frm + fb);
    double s_sum = s_left + s_right;

    // Erro estimado usando a diferença entre as duas aproximações
    double error = fabs(s_sum - s_whole) / 15.0;

    // Critério de parada
    if (error < tol){
        return s_sum + (s_sum - s_whole) / 15.0;
    }
    // Recursão com tolerância dividida
    double left_result = adaptive_simpson_recursive(f, a, m, tol/2.0, s_left, fa, fm, flm, depth + 1);
    double right_result = adaptive_simpson_recursive(f, m, b, tol/2.0, s_right, fm, fb, frm, depth + 1);

    return left_result + right_result;
}

// Adaptive Simpson's Rule for numerical integration
double simpsonadaptativo(double (*f)(double), double a, double b, double tol) {
    double fa = f(a);
    double fb = f(b);
    double m = (a + b) / 2.0;
    double fm = f(m);

    // Simpson inteiro
    double h = b - a;
    double s_whole = (h / 6.0) * (fa + 4.0 * fm + fb);

    return adaptive_simpson_recursive(f, a, b, tol, s_whole, fa, fb, fm, 0);
}