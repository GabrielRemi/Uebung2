#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void printarr(double arr[], int N)
{
    for(int i = 0; i<N; i++) printf("%f\n", arr[i]);
    printf("\n");
}

double neville(double x, double *stuetz, double *y, int N)
{
    double *temp = malloc(N*sizeof(double)); //Speicherung des letzen Rekursionsschritss
    double *p = malloc(N*sizeof(double)); // momentane Rekursion
    memset(temp, 0, N*sizeof(double));
    memset(p, 0, N*sizeof(double));
    
    //Rekursionsanfang
    p[0] = y[0]; 

    for (int grad = 1; grad < N; grad++)
    {
        memmove(temp, p, grad*sizeof(double));
        p[0] = y[grad];

        for (int j = 1; j <= grad; j++)
        {
            p[j] = (p[j-1]*(x - stuetz[grad-j]) - temp[j-1]*(x-stuetz[grad])) / (stuetz[grad] - stuetz[grad-j]);
        }
    }

    return p[N-1];
}

int main(int argc, char **argv)
{
    // Input: (1) .txt Datei der Stützstellen (2) double Anfangswert (3) double Endwert (4) int Anzahl von auszuwertenden Stellen 
    // (5) .txt name zum speichern der Werte
    if(argc < 6)
    {
        printf("Zu wenige Angaben\n");
        exit(1);
    }

    //#############################################
    // Initialisiere stützpunkte
    FILE *fp = fopen(argv[1], "r");

    int N;  // Anzahl der stellen
    fscanf(fp, "%d", &N);
    printf("%d\n", N);

    double *stuetz = malloc(N*sizeof(double));
    double *y = malloc(N*sizeof(double));

    for (int i = 0; i < N; i++) fscanf(fp, "%lf  %lf", &stuetz[i], &y[i]);

    fclose(fp);
    //#######################################################################
    //berechne auszuwertende Stellen
    int K = atoi(argv[4]);
    double a = atoi(argv[2]); double b = atoi(argv[3]);
    double *x = malloc(K*sizeof(double));  // Stellen

    for (int i = 0; i < K; i++) x[i] = a + (b-a)/(K-1) * i;
    //#####################################################################
    
    //neville-aitken und in Datei abspeichern
    fp = fopen(argv[5], "w");
    for (int i = 0; i < K; i++) fprintf(fp, "%.7f  %.7f\n", x[i], neville(x[i], stuetz, y, N));

    fclose(fp);


    free(stuetz);
    free(y);
    free(x);

    return 0;
}