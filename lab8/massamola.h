#ifndef MASSA_MOLA_H
#define MASSA_MOLA_H

void forca (double t, double x, double y, double* fx, double* fy);
double evolui (double t, double h, double x, double y, double xp, double yp, double* xn, double* yn);
void simula (double x0, double y0, double t, int n, double* x, double* y);

#endif