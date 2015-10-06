#include "mathutils.h"
#include <cmath>

mathUtils::mathUtils()
{
}

double mathUtils::fonctionQuadratique(double min, double max, double x) {

    return x<min?0:x>=max?1:1-pow((1-pow((x-min)/(max-min),2)),2);
}

double mathUtils::fonctionQuadratiqueInv(double min, double max, double x) {

    return 1-fonctionQuadratique(max,min,x);
}

double mathUtils::interpolate(double before_p0, double p0, double p1, double after_p1, double t)
{
    //Calcul des coefficients de notre polynôme
    double a3 = -0.5*before_p0 + 1.5*p0 - 1.5*p1 + 0.5*after_p1;
    double a2 = before_p0 - 2.5*p0 + 2*p1 - 0.5*after_p1;
    double a1 = -0.5*before_p0 + 0.5*p1;
    double a0 = p0;

    //Calcul de la valeur de ce polynôme en t
    return (a3 * t*t*t) + (a2 * t*t) + (a1 * t) + a0;
}
