#ifndef BRAS_H_INCLUDED
#define BRAS_H_INCLUDED
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
* Dessine un bras en prenant comme base les coordonnées 0,0,0
* @param nbDeCylindres le nombres de cylindres qui seront utilisé pour faire l'effet d'amoidrissement du bras
* @param h la hauteur de cylindre
* @param n nombre de face du cylindre
*/
void draw_bras(const int nbDeCylindres, const double h, const int n);

#endif // BRAS_H_INCLUDED
