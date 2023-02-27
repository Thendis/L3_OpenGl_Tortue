#ifndef SPHERE_H
#define SPHERE_H
#include <cstdio>
#include <cstdlib>
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <jerror.h>
#include <iostream>
#include <cmath>
#include "Texture.h"
#include "point.h"
#include "Normal.h"

/**
*Classe servant a construire et à gérer l'affichage d'une sphère ou d'une demi sphère
*/
class Sphere{

    private :
        int nm; //nombre meridians
        int np; //nombre parallèles
        double rayon;
        bool isDemi;
        Point pSphere[50*50]; //Initialisé a 2 500 points max
        int pFaces[50*49][4]; //Stock les indices des points qui composent une face. FOnctionne en parallèle avec pSphere
    public :
    /***
    *Initialise une sphère/demi-sphère avec ses points, faces et ses vecteurs normaux
    *@param nm nombre de méridiens
    *@param np nombre de parallèles
    *@param r rayon
    *@param isDemi true si demi-sphère, false si sphère
    */
    Sphere(int nm, int np, double r, bool isDemi);
    /**
    *Initialise les coordonnées des points de la forme selon les infos de l'objet
    */
    void initSphereCoord();
    /**
    *Initialise les faces selon les infos de l'objet
    */
    void initFaceSphere();
    /**
    *Affiche la forme sous la forme d'un nuage de points
    */
    void showPoints();
    /**
    *Dessine la forme en lui appliquant une texture t
    *@param t la texture a appliquer
    */
    void drawSphere(Texture t);
    /**
    *Dessine la forme sans texture et sans appliquer de couleur
    */
    void drawSphere();
};



#endif // SPHERE_H_INCLUDED
