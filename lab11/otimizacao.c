#include "otimizacao.h"
#include <math.h>

// Golden ratio constant
#define G 0.618033988749895

int msa(double a, double b, double (*f)(double x), double tol, double *xmin)
{
    int it = 0;
    double x1, x2, fx1, fx2;
    
    // Initial points
    x1 = a + (1.0 - G) * (b - a);
    x2 = a + G * (b - a);
    fx1 = f(x1);
    fx2 = f(x2);
    
    // Iterate until convergence or max iterations
    while (it < 50 && (b - a) / 2.0 > tol) {
        if (fx1 <= fx2) {
            // Minimum is in [a, x2]
            b = x2;
            x2 = x1;
            fx2 = fx1;
            x1 = a + (1.0 - G) * (b - a);
            fx1 = f(x1);
        } else {
            // Minimum is in [x1, b]
            a = x1;
            x1 = x2;
            fx1 = fx2;
            x2 = a + G * (b - a);
            fx2 = f(x2);
        }
        it++;
    }
    
    *xmin = (a + b) / 2.0;
    return it;
}

int mips(double r, double delta, double (*f)(double x), double tol, double *xmin)
{
    int it = 0;
    double s, t, x;
    double fr, fs, ft, fx;
    double denom;
    
    // Initial estimates
    s = r - delta;
    t = r + delta;
    fr = f(r);
    fs = f(s);
    ft = f(t);
    
    // Iterate until convergence or max iterations
    while (it < 50) {
        // Calculate parabolic interpolation
        denom = 2.0 * ((s - r) * (ft - fs) - (fs - fr) * (t - s));
        
        if (fabs(denom) < 1e-10) {
            x = (r + s + t) / 3.0;
        } else {
            x = (r + s) / 2.0 - (fs - fr) * (t - r) * (t - s) / denom;
        }
        
        fx = f(x);
        
        // Update estimates
        r = s;
        fr = fs;
        s = t;
        fs = ft;
        t = x;
        ft = fx;
        
        it++;
        
        // Check convergence after 3 iterations
        if (it >= 3 && fabs(fs - ft) <= tol) {
            break;
        }
    }
    
    if (it >= 50) {
        return 0;
    }
    
    *xmin = (s + t) / 2.0;
    return it;
}