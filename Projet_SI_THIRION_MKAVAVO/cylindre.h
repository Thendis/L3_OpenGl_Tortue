#ifndef CYLINDRE_H_INCLUDED
#define CYLINDRE_H_INCLUDED
#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include <cstdlib>
#include "point.h"
#include <math.h>
#include "Normal.h"
/**
*Dessine un cylindre
*@param r1 rayon de la première base du cylindre
*@param r2 rayon de la seconde base du cylindre
*@param h la hauteur du cylindre
*/
Point* draw_cylindre(int n, double r1, double r2, double h);
/**
*Dessine une succession de cylindre
*@param autrePoints la base de construiction du prochain cylindre
*@param n nombre de faces
*@param r2 rayon de l'autre extremite du cylindre
*@param h hauteur
*/
Point* draw_cylindre_avec_cylindre(Point* autrePoints, int n, double r2, double h);

#endif // CYLINDRE_H_INCLUDED
