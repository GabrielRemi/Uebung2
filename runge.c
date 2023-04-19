#include<stdio.h>
#include<stdlib.h>

double runge(const double x);
void interpolation(int N, int f[]);
void printarr(double arr[], int N);


void interpolation(int N, int f[])
{
    // berechnne Stützstellen und Stützpunkte
    double a = -5; double b = 5;
    double x[N+1];  //Stellen
    double y[N+1]; //Punkte
    for(int i = 0; i <= N; i++)
    {
        x[i] = a + (b-a)/N*i;
        y[i] = runge(x[i]);
    }

    printarr(x, N+1);
    printarr(y, N+1);

}

double runge(const double x)
{
    return 1.0/(1+x*x);
}

void printarr(double arr[], int N)
{
    for(int i = 0; i<N; i++) printf("%f\n", arr[i]);
}


int main()
{
    int f[1] = {0};
    interpolation(13, f);
}

