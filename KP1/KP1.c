#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#define N 40
#define N_STAT 19
#define X_MIN 5.0
#define X_MAX 80.0
#define X_DEF 19.0    
#define Q0 50.0
#define TOL 0.03
#define ALARM 0.10
#define K1 5.0
#define B1 19.0
#define C1 5.0
#define X1 20.0
#define K2 2.0
#define S2 32.5
#define C2 50.0
#define X2 45.0
#define K3 4.0
#define S3 43.0
#define C3 60.0

double read_x(int i);
double calc_q(double x);
const char *state_name(double q);
void stats(const double q[], int n, double *mean, double *sd);

int main(void) {
    double q[N], mean, sd;
    for (int i = 0; i < N; i++) {
        double x = read_x(i + 1);
        q[i] = calc_q(x);
        printf("Q = %.2f, состояние: %s\n", q[i], state_name(q[i]));
    }
    stats(q, N_STAT, &mean, &sd);
    printf("Q[1..%d]: среднее = %.2f, СКО = %.2f\n", N_STAT, mean, sd);
    return 0;
}

double read_x(int i) {
    double x;
    for (;;) {
        printf("X[%d] (%.0f..%.0f, Q определена при X >= %.0f): ",
               i, X_MIN, X_MAX, X_DEF);
        if (scanf("%lf", &x) == 1 && x >= X_DEF && x <= X_MAX) return x;
        while (getchar() != '\n');
        printf("Неверный ввод, повторите.\n");
    }
}

double calc_q(double x) {
    if (x < X1)  return K1 * sqrt(x - B1) + C1;
    if (x <= X2) return K2 * (x - S2) + C2;
    return K3 * log(x - S3) + C3;
}

const char *state_name(double q) {
    double d = fabs(q - Q0);
    if (d <= TOL * Q0)   return "НОРМА";
    if (d <= ALARM * Q0) return "ПРЕДУПРЕЖДЕНИЕ";
    return "АВАРИЯ";
}

void stats(const double q[], int n, double *mean, double *sd) {
    double s = 0, s2 = 0;
    for (int i = 0; i < n; i++) s += q[i];
    *mean = s / n;
    for (int i = 0; i < n; i++) s2 += (q[i] - *mean) * (q[i] - *mean);
    *sd = sqrt(s2 / (n - 1));
}
