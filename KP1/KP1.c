#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#include <math.h>
#define X_MIN        5.0    
#define X_MAX        80.0    
#define Q_B       50.0    
#define Q_TOL  0.03    
#define X_LOW  20.0
#define X_MID  45.0
int read_x(double* x)
{
    if (x == NULL)
        return 0;
    if (scanf("%lf", x) != 1)
        return 0;
    if (*x < X_MIN || *x > X_MAX)
        return 0;
    return 1;
}
double calculate_q(double x)
{
    if (x < X_LOW) {
        return 5.0 * sqrt((x - 20.0 + 1.0)) + 5.0;
    }
    else if (x <= X_MID) {
        return 2.0 * (x - 32.5) + 50.0;
    }
    else {
        return 4.0 * log(x - 45.0 + 2.0) + 60.0;
    }
}
int control_state(double q)
{
    double deviation = fabs(q - Q_B);
    if (deviation <= Q_B * Q_TOL)
        return 0;
    if (deviation <= 2.0 * Q_B * Q_TOL)
        return 1;
    return 2;
}
void stats(const double q[], int n)
{
    (void)q;
    (void)n;
}
int main(void)
{
    double x;
    double q;
    int state;
    setlocale(LC_ALL, "RUS");
    printf("******* Программа мониторинга вязкости смеси в реакторе *******\n");
    printf("******* Вычисляет показатель качества Q(X) и контролирует состояние процесса *******\n\n");
    printf("Введите значение X (от %.1f до %.1f): ", X_MIN, X_MAX);
    if (scanf("%lf", &x) != 1) {
        printf("Ошибка ввода\n");
        return 1;
    }
    if (x < X_MIN || x > X_MAX) {
        printf("Ошибка ввода: X вне диапазона %.1f..%.1f\n", X_MIN, X_MAX);
        return 1;
    }
    q = calculate_q(x);
    state = control_state(q);
    printf("Q(%.2f) = %.4f\n", x, q);
    printf("Состояние процесса: %d\n", state);
    {
        double samples[1];
        samples[0] = q;
        stats(samples, 1);
    }
    return 0;
}
