#include "Sphere.h"


Sphere::Sphere(int nm, int np, double r, bool isDemi)
{
    this->nm = nm;
    this->np = np;
    this->rayon = r;
    this->isDemi = isDemi;
    initSphereCoord();
    initFaceSphere();
    //showPoints();
}

/**
* Creat every point of a sphere object and place them in p
*/
void Sphere::initSphereCoord()
{
    float red=1,green=1,blue=1;
    for(int i=0;i<np;i++)
    {
        double phi = (M_PI/2) + (i*(M_PI/(np-1)));
        for(int j=0;j<nm+1;j++)
        {
            int indice = (i*nm)+j;
            double theta;
            if(isDemi)
                theta = (j*((M_PI)/(nm-1)));
            else
                theta = (j*((2*M_PI)/(nm-1)));

            pSphere[indice] = {rayon*cos(theta)*cos(phi),
                                rayon*sin(theta)*cos(phi),
                                rayon*sin(phi),
                                red,
                                green,
                                blue};
        }
    }
}
/**
* Link faces with there points(GL_POLYGONE) Used for creat en draw sphere
* @author Eddin
*/
void Sphere::initFaceSphere()
{
    for(int e = 0; e<np-1;e++)
    {
        for(int i =e*nm;i<nm*(e+1);i++)
        {
            pFaces[i][0] = i;
            pFaces[i][1] = i+nm;
            pFaces[i][2] = i+1+nm;
            pFaces[i][3] = i+1;
        }
    }
}

/**
* Draw the fig based on an array au Points and the faces linked with
* @param Texture t Tex needed for draw. Make sure to make a t.loadTex() before
* @author Eddin
*/
void Sphere::drawSphere(Texture t)
{
    t.loadTex();
    int nbFaces = nm*(np-1);
    for(int i = 0;i<nbFaces;i++)
    {
        const int* face = pFaces[i];
        /**VECTORS*/
            //Select 3 points
        Point a = pSphere[face[0]];
        Point b = pSphere[face[1]];
        Point c = pSphere[face[3]];
            Normal calculN(a,b,c);
        /**FIN VECTOR*/
        glBegin(GL_POLYGON);
        glNormal3fv(calculN.getNormal());
        float *tex;
        tex = t.getTexCoords(i,(float)np,(float)nm);

            glTexCoord2f(tex[0],tex[2]);
            glVertex3d(pSphere[face[0]].x,pSphere[face[0]].y,pSphere[face[0]].z);

            glTexCoord2f(tex[0],tex[3]);
            glVertex3d(pSphere[face[1]].x,pSphere[face[1]].y,pSphere[face[1]].z);

            glTexCoord2f(tex[1],tex[3]);
            glVertex3d(pSphere[face[2]].x,pSphere[face[2]].y,pSphere[face[2]].z);

            glTexCoord2f(tex[1],tex[2]);
            glVertex3d(pSphere[face[3]].x,pSphere[face[3]].y,pSphere[face[3]].z);

        glEnd();
    }
}


/**
* Draw the fig based on an array au Points and the faces linked with
*/
void Sphere::drawSphere()
{
    int nbFaces = nm*(np-1);
    for(int i = 0;i<nbFaces;i++)
    {
        const int* face = pFaces[i];
        /**VECTORS*/
            //Select 3 points
        Point a = pSphere[face[0]];
        Point b = pSphere[face[1]];
        Point c = pSphere[face[2]];
        Normal calculN(a,b,c);
        /**FIN VECTOR*/
        glBegin(GL_POLYGON);
            glNormal3fv(calculN.getNormal());
            glVertex3d(pSphere[face[0]].x,pSphere[face[0]].y,pSphere[face[0]].z);
            glVertex3d(pSphere[face[1]].x,pSphere[face[1]].y,pSphere[face[1]].z);
            glVertex3d(pSphere[face[2]].x,pSphere[face[2]].y,pSphere[face[2]].z);
            glVertex3d(pSphere[face[3]].x,pSphere[face[3]].y,pSphere[face[3]].z);
        glEnd();
    }
}

/**
* Draw every Points in the p array
*/
void Sphere::showPoints()
{
    glBegin(GL_POINTS);
    glColor3f(1,0,0);
    for(int i=0;i<nm*np;i++)
    {
        Point point = pSphere[i];
        glVertex3d(point.x,point.y,point.z);
    }

    glEnd();

}
