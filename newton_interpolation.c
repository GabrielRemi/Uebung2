#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int main(int argc, char **args);

double runge(const double x);
void printarr(double arr[], int N);


//Berechnet Polynom an Stelle x mit dem Horner-Schema
double horner(double x, double *stuetzstellen, double *pcoeff, int N)
{
    double pol = pcoeff[N-1];

    for (int n = N - 1; n > 0; n--)
    {
        pol = pol * (x - stuetzstellen[n - 1]) + pcoeff[n - 1];
    }

    return pol;
}

// Berechnet Polynom auf herkömmlicher Weise
 double polynom(double x, double *stuetzstellen, double *pcoeff, int N)
 {
    double p = pcoeff[0];
    for (int i = 1; i < N; i++)
    {
        double a = pcoeff[i];
        for (int j = 0; j < i; j++)
        {
            a *= x - stuetzstellen[j];
        }
        p += a;
    }

    return p;
 }

double *interpolation(int N, double *x, double *y)
{

    //#####################################################
    // DIVIDIERTE DIFFERENZEN
    //#####################################################

    /*
    f_0 
         \
         / f_01
    f_1         \
        \       /  f_012
        /  f_12         \
    f_2         \       /  f_0123
        \       /  f_123
        /  f_23
    f_3
    */

    double *pcoeff = malloc(N*sizeof(double));
    double *fdd = malloc(N*sizeof(double));
    double *temp = malloc(N*sizeof(double));
    memset(pcoeff, 0, N*sizeof(double));
    memset(fdd, 0, N*sizeof(double));
    memset(temp, 0, N*sizeof(double));
   

    // Jeder Loop berechnet eine neue Schrägzeile
    int loop = 0;
    fdd[0] = y[0]; //Startwert der Rekursion
    pcoeff[0] = fdd[0];
    while(loop < N - 1)
    {
        memmove(temp, fdd, (loop+1)*sizeof(double));
        fdd[0] = y[loop + 1];
    
        for (int i = 1; i <= loop + 1; i++)
        {
            fdd[i] = (fdd[i-1] - temp[i-1])/(x[loop + 1] - x[loop + 1 - i]);
        }
        pcoeff[loop + 1] = fdd[loop + 1];
        //printarr(fdd, N);
        loop++;
    }
    //printarr(temp, N);
    //printarr(pcoeff, N);

    free(fdd);
    free(temp);
   
    return pcoeff;
}

double runge(const double x)
{
    return 1.0/(1+x*x);
}


//  gibt double Arrays in der konsole aus
void printarr(double arr[], int N)
{
    for(int i = 0; i<N; i++) printf("%f\n", arr[i]);
    printf("\n");
}

//########################################################################
//                      MAIN
//########################################################################
int main(int argc, char **argv)
{
    // Kontrolliere Argument Eingabe
    // Eingabe: (1) stützstellen.txt (2) Ergebnis.txt (3) koeffizienten.txt 
    if ( argc < 2)
    {
        printf("Eingabe der Stützstellen fehlt");
        exit(1);
    }

    //########################################
    // Lese stützstellen aus Datei
    FILE *fp = fopen(argv[1], "r");

    int N;
    fscanf(fp, "%d", &N);
    printf("%d", N);

    double *stuetz = malloc((N)*sizeof(double));  //Stellen
    double *y = malloc((N)*sizeof(double)); //Punkte

    for (int i = 0; i < N; i++)
    {
        fscanf(fp, "%lf %lf", &stuetz[i], &y[i]);
    }

    fclose(fp);

    //#######################################


    double *pcoeff = malloc(N*sizeof(double));
    pcoeff = interpolation(N, stuetz, y);

    // Polynome berechnen und in Datei abspeichern
    fp = fopen("Data_interpolation.txt", "w");
    
    int num = 200;
    double x;
    double pol;
    for(int i = 0; i < num; i++)
    {
        x = stuetz[0] + (stuetz[N-1]-stuetz[0])/(num-1.0)*i;
        pol = horner(x, stuetz, pcoeff, N);

        fprintf(fp, "%.10f   %.10f\n", x, pol);
    }

    fclose(fp);

    // Stützstellen speichern
    fp = fopen("stuetzpunkte.txt", "w");
    for (int i = 0; i < N; i++)
    {
        fprintf(fp, "%.7f   %.7f\n", stuetz[i], y[i]);
    }


    free(stuetz);
    free(y);
    free(pcoeff);

    return 0;

}

