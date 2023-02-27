#ifndef NORMAL_H
#define NORMAL_H
#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif
#include "point.h"
#include <math.h>

/**
*Classe qui sert a calculer les normals des faces
*/
class Normal{
private :
    GLfloat norm[3]={0,0,0}; // Initialisé a 0 pour eviter les erreurs

public :
/**
*Constructeur qui prend 3 points pouvant former 2 vecteur non colinéaire
*@param a un point non null
*@param b un point non null
*@param c un point non null
*/
Normal(Point a, Point b, Point c);

/**
*Retourne un le vecteur normal normalisé
*/
GLfloat* getNormal();

};
#endif // NORMAL_H
