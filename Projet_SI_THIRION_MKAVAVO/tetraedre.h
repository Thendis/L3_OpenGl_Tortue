#ifndef TETRAEDRE_H_INCLUDED
#define TETRAEDRE_H_INCLUDED
#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <cstdlib>
#include <iostream>
#include "point.h"
#include <math.h>
#include "Normal.h"

/**
*Dessine un tetraedre
*/
void draw_tetraedre(const double largeur, const double longueur, const double hauteur);

#endif // TETRAEDRE_H_INCLUDED
