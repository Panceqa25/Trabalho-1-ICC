#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fenv.h>
#include <float.h>
#include <stdint.h>

union {
        double f;
        uint64_t i;
}u;

double fatorial(int num, int *cont, int nAnt, double fatAnt) {

    if (num == 0 || num == 1)  //fatorial de 0 e 1 eh 1
        return 1;

    for (int i = num; i > nAnt; i--) {
        fatAnt *= i;
        (*cont)++;
    }
    return fatAnt;
}

double aproxPi(double tolerancia, int *n, double *aprox, int *contOp) {

    double somaAtual = 0, somaAnt = 0, erro = tolerancia + 1, numerador = 0, denominador = 0;
    double fat = 1, pow = 1;
    int cont = 0, ultNum = 0;

    (*n) = 0;

    while (erro > tolerancia) {

        somaAnt = somaAtual;
        numerador = pow*fat*fat;

        denominador = fatorial(2*(*n) + 1, &cont, ultNum, denominador);
        ultNum = 2*(*n) + 1;

        somaAtual += numerador/denominador; //Acumula o valor do somatorio

        erro = fabs(somaAtual - somaAnt);

        pow *= 2;

        (*n)++;
        fat *= *n;

        (*contOp) += 7;
    }

    (*contOp) += cont + (*n);

    (*aprox) = erro;

    return 2*somaAtual; 

}

void printNum(double num) {

    u.f = num;

    printf("%.15e %016lx\n", num, u.i);

}

int main() {

    int nCima = 0, nBaixo = 0, contOp = 0;
    double tolerancia = 0, /*ulp = 0,*/ aproxBaixo = 0, aproxCima = 0;

    scanf("%lf", &tolerancia);

    //Arredondamentos p/ cima
    fesetround(FE_UPWARD);
    double piAproxCima = aproxPi(tolerancia, &nCima, &aproxCima, &contOp);
    double erroExatoCima = fabs(piAproxCima - M_PI);

    contOp = 0;

    //Arredondamentos p/ baixo
    fesetround(FE_DOWNWARD);
    double piAproxBaixo = aproxPi(tolerancia, &nBaixo, &aproxBaixo, &contOp);
    double erroExatoBaixo = fabs(piAproxBaixo - M_PI);

    //ulp = fabsl(piAproxCima - piAproxBaixo) / DBL_EPSILON;

    printf("%d\n", nCima + 1);
    printNum(aproxBaixo);
    printNum(erroExatoCima);
    printNum(piAproxCima);
    printNum(piAproxBaixo);
    printf("%d\n", nBaixo + 1);
    printf("%d\n", contOp);

    return 0;
}
