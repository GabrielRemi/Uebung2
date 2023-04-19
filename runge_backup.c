/***********************************************************************
 * Newtonsche Polynominterpolation für Runges Funktion
 *
 * kompilieren  mit
 *
 *   gcc -Wall -pedantic runge.c -o runge -lm
 *
 * aufrufen mit
 *   ./runge nxy
 *
 ***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

/***********************************************************************
 * Runge-Funktion
 ***********************************************************************/
static double runge ( double const x )
{
  return ( 1. / ( 1. + x*x ) );

}  /* end of runge */

/***********************************************************************
 * Horner-Schema zur Auswertung eines Interpolationspolynoms
 * in der Newton-Darstellung
 *
 * Auswertung des Polynoms "von innen nach aussen", beginnend mit der
 * höchsten Potenz
 *
 * p(z) = [ ... [ f_n * ( x - x_{n-1} )  + f_{n-1} ] * ( z - x_{n-2} ) + ... ] ( z - x_0 ) + f_0
 *
 ***********************************************************************/
static double horner ( double const z, double * const x , double * const f, unsigned int const n )
{
  double p = 0.;  /* Startwert is 0 */

  for ( unsigned int i = n; i > 0; i-- )
  {
    /* addiere zu p den i-ten Koeffizienten und multipliziere
     * die Summe mit ( z - x_{i-1} ) 
     * ...
     */

  }
  p += f[0];
  
  return ( p );

}  /* end of horner */


/***********************************************************************
 * MAIN PROGRAM
 ***********************************************************************/
int main(int argc, char **argv) 
{

  /* Prüfe, dass ein Werte nxy eingegeben wurde, also
   * mindestens 2 Wörter in argv
   */
  if ( argc < 2 )
  {
    fprintf( stderr, "[runge] Fehler, keine Eingabe nxy \n" );
    exit (1);
  }
  /* Das ist die Anzahl der Stützstellen
   *
   * argv[1] ist eine Zeichenkette und wird von char* nach int umgewandelt
   * mit Funktion atoi aus stdlib.h, siehe Manpages man atoi, man stdlib.h
   */
  int nxy = atoi ( argv[1] );
  /* Prüfe, dass nxy >= 2 ist
   */
  if ( nxy <= 1 ) {
    fprintf ( stderr, "[runge] Fehler, nxy muss > 1 sein\n" );
    exit(4);
  }

  /* Zur Kontrolle geben wir die Eingabe nach Standardausgabe aus
   */
  fprintf ( stdout, "# [runge] Eingabe   nxy = %2d\n", nxy );


  /* maximaler Grad des Interpolationspolynoms 
   *   = Anzahl Stützstellen - 1
   */
  int const max_deg = nxy - 1;
  
  /* Parameter für die Auswertung des Interpolationspolynoms 
   * zmin <= z <= zmax mit max_nz Punkten
   */
  int const max_nz = 200;

  double const zmin = -5.;
  double const zmax =  5.;

  /* Wir reservieren Speicher auf dem Heap für
   *   ... Stützstellen 
   */
  double * x   = (double *) malloc ( nxy * sizeof(double) );

  /* ... dividierte Differenzen
   */
  double * fdd = (double *) malloc ( nxy * sizeof(double) );

  /* ... Polynomkoeffizienten
   */
  double * pcoeff = (double *) malloc ( nxy * sizeof(double) );

  /* Prüfe, ob malloc den NULL-Pointer zurückgegeben hat;
   * falls wahr, dann Abbruch
   */
  if ( x == NULL || fdd == NULL || pcoeff == NULL )
  {
    fprintf ( stderr, "[runge] Fehler von malloc %s %d\n", __FILE__, __LINE__ );
    exit(2);
  }

  /* Setze die Werte der Stützstellen 
   */
  for ( int i = 0; i < nxy; i++ )
  {
    /* ... äquidistant zwichen zmin und zmax 
     */
    x[i] = zmin + ( zmax - zmin ) / (double)max_deg * (double)i;

    /* ... auf den nxy Nullstellen des Tschebyshow-Polnymos T_nxy
     * ...
     */

  }

  /***********************************************************************
   * Konstruktion der f_... nach Newton mit dividierten
   * Differenzen
   *
   * x_0 | y_0 = f_0
   *     |              f_01
   * x_1 | y_1 = f_1           f_012
   *     |                           \
   *     |              f_12           f_0123
   *     |                   \       /      
   * x_2 | y_2 = f_2           f_123
   *     |            \      /
   *     |              f_23
   *     |            /
   * x_3 | y_3 = f_3 
   * .   |
   * .   |
   * .   |
   *
   * Die jeweils unterste, von links nach rechts steigende Schrägzeile halten wir in fdd;
   * dabei wird folgendermassen gespeichert
   *
   * fdd[0] = f_0......k
   * fdd[1] = f_1.....k
   * fdd[2] = f_2...k
   *   ...
   * fdd[k] = f_k
   *
   * in pcoeff speichern wir schrittweise die Koeffizienten des Polynoms
   * in der obersten, von links nachts fallenden Schrägzeile ab;
   * dabei speichern wir
   *
   * pcoeff[0] = f_0
   * pcoeff[1] = f_01
   * pcoeff[2] = f_012
   *   ...
   * pcoeff[k] = f_0...k
   ***********************************************************************/

  /* initialisiere fdd und pcoeff zu Null in allen Bytes
   *
   * Funktion memset braucht #include <string.h>, siehe man memset, man string.h
   */
  memset ( fdd,    0, nxy * sizeof ( double ) );
  memset ( pcoeff, 0, nxy * sizeof ( double ) );

  for ( unsigned int grad = 0; grad <= max_deg; grad++ )
  {
    /* bis hierhin ist aus der vorherigen Iteration
     *
     * fdd = { f_{0,...,grad-1}, f_{1,...,grad-1}, ..., f_{grad-1},  0, ... , 0 }
     */

    /* jetzt fügen wir am Ende das neue f_{grad} = y[grad] hinzu und bekommen
     *
     * fdd = { f_{0,...,grad-1}, f_{1,...,grad-1}, ..., f_{grad-1}, f_{grad}, 0, ..., 0 }
     */

    fdd[grad] = runge ( x[grad] );

    /* fdd[grad] = f_{grad} ist bereits das neue Element an der richtigen Stelle;
     * jetzt berechnen wir auch fdd[0], ..., fdd[grad-1] neu über die Neville-Rekursion,
     * sodass wir nach diesem Schritt in fdd die Elemente
     *
     * fdd = {  f_{0,...,grad}, f_{1,...,grad}, ..., f_{grad-1,grad}, f_{grad}, 0, ..., 0  }
     *
     * haben
     *
     * Wir gehen wieder rückwärts vor, von 
     * grad-1 nach 0, ersetzen also zuerst im Element fdd[grad-1]
     *
     * f_{grad-1} durch f_{grad-1,grad} berechnet aus f_{grad-1} und f_{grad}
     * 
     * nach Rekursionsvorschift; dann gehen wir zu fdd[grad-2] usw.
     *
     */
    for ( int k = grad -1; k >= 0; k-- )
    {
      /* Setze die Rekursion ein
       * ...
       */
    }

    /* Füge den neu berechneten Wert 
     * fdd[0] = f_{0,...,grad} zur Liste
     * der Koeffizienten hinzu
     */
    pcoeff[grad] = fdd[0];

  }  /* end of loop on grad */

  /* Auswertung des Interpolationspolynoms mit Grad max_deg 
   *
   * Die Wertetabelle schreiben wir in eine Datei,
   * deren Namen den Polynomgrad enthält
   */

  /* Erstelle einen Dateinamen
   */
  char filename[100];
  sprintf( filename, "runge.n%d.tab", max_deg );

  /* Öffne die Datei filename zum Schreiben
   */
  FILE * fp = fopen ( filename, "w" );

  /* Schreibe die Koeffizienten des Polynoms mit Grad grad 
   * in die Datei 
   */
  fprintf ( fp, "# n = %d Koeffizienten\n", max_deg+1 );
  for ( int k = 0; k <= max_deg; k++ )
  {
    fprintf ( fp, "# k %4d  %25.16e\n", k, pcoeff[k] );
  }
  /* Schreibe eine Wertetabelle des Interpolationspolynoḿs und
   * der Funktion runge in eine Datei
   */
  for ( int l = 0; l <= max_nz; l++ )
  {
    double const z = zmin + ( zmax - zmin )/(double)max_nz * (double)l;
    double const y = horner ( z, x, pcoeff, max_deg );
    fprintf( fp, "%6d %25.16e  %25.16e %25.16e\n" , l, z, y, runge ( z ) );
  }

  /* Schliesse die Datei
   */
  fclose ( fp );

  /* Speicher freigeben
   */
  free ( x      ) ;
  free ( fdd    );
  free ( pcoeff );

  return ( 0 );
}

