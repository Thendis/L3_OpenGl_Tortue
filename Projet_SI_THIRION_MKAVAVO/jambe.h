#ifndef JAMBE_H_INCLUDED
#define JAMBE_H_INCLUDED
#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <cstdlib>
#include <iostream>

#include "cylindre.h"
#include "point.h"
#include "tetraedre.h"
#include "Sphere.h"

#include <math.h>
/**
*Dessine une jambe de la torue totalement tendu
*@param r rayon des articulations
*@param h hauteur des mambres
*/
void draw_jambe(const double r, const double h);

#endif // JAMBE_H_INCLUDED
