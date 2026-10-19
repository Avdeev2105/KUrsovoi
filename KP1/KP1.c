#define _CRT_SECURE_NO_WARNINGS
#define M_PI 3.14159265358979323846
#include <stdio.h>
#include <locale.h>
#include <math.h>

double Q(double X) {
    if (X < 20) {
        return 5 * sqrt((X - 20+1) +5);
    }
    else if (X <=45 && X>=20){
        return 2 * (X-32.5) + 50;
    }
    else {
        return 4 * log(X - 45+2) + 60;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    double X;
    printf("Введите значение X: ");
    scanf("%lf", &X);
    printf("Q(%.2f) = %.4f\n", X, Q(X));
    return 0;
}