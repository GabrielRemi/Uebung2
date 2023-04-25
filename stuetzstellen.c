#include<stdio.h>
#include<stdlib.h>
#include<string.h>

double runge(const double x)
{
    return 1.0/(1+x*x);
}

int main(int argc, char **argv)
{
    // Eingabe: (1) Anzahl der Stützstellen (2) Anfangswert (3) Endwert (4) Name der zu speichernden Datei
    if (argc < 5) 
    {
        printf("Eingabe fehlt\n");
        return -1;
    }

    int N = atoi(argv[1]);

     // berechnne Stützstellen und Stützpunkte
    double a = atof(argv[2]); double b = atof(argv[3]);
    double *stuetz = malloc((N)*sizeof(double));  //Stellen
    double *y = malloc((N)*sizeof(double)); //Punkte

    //####################################
    //Rechnung für äquidistante Stützstellen
    for(int i = 0; i < N; i++)
    {
        stuetz[i] = a + (b-a)/(N-1.0)*i;
        y[i] = runge(stuetz[i]);
    }

    // Werte in Datei speichern    
    FILE *fp = fopen(argv[4], "w");

    fprintf(fp, "%d\n", N); //Anzahl der Stellen abspeichern
    for (int i = 0; i < N; i++) fprintf(fp, "%.10f  %.10f\n", stuetz[i], y[i]);

    fclose(fp);

    free(stuetz);
    free(y);

    return 0;
}