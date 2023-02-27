#include "Normal.h"

Normal::Normal(Point a, Point b, Point c)
{
        //Define 2 Vect for calculat normal
        Point vecAB((b.x-a.x), (b.y-a.y), (b.z-a.z));
        Point vecAC((c.x-a.x),(c.y-a.y),(c.z-a.z));
            //Calcul normal
        GLfloat vect[3]={
            (vecAB.y*vecAC.z)-(vecAB.z*vecAC.y),
            (vecAB.z*vecAC.x)-(vecAB.x*vecAC.z),
            (vecAB.x*vecAC.y)-(vecAB.y*vecAC.x)
        };
        GLfloat lengthV = sqrt((vect[0]*vect[0])+(vect[1]*vect[1])+(vect[2]*vect[2]));
            //Narmal between 0 and 1
        norm[0]=vect[0]/lengthV;
        norm[1]=vect[1]/lengthV;
        norm[2]=vect[2]/lengthV;
};

GLfloat* Normal::getNormal(){
    return norm;
};

