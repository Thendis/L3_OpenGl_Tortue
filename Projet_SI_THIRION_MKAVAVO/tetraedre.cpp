#include "tetraedre.h"

void draw_tetraedre(const double largeur, const double longueur, const double hauteur){
    Point pDoigts[4]=
    {
        {largeur/2, 0.0, 0.0, 0.0,0.0,1.0},
        {0.0, hauteur, 0.0, 0.0,0.0,1.0},
        {-largeur/2, 0.0, 0.0, 0.0,0.0,1.0},
        {0.0, 0.0, longueur, 0.0,0.0,1.0}
    };

    int fDoigts[4][3]=
    {
        {0, 1, 2},
        {0, 3, 2},
        {0, 1, 3},
        {3, 1, 2}
    };

    //dessine les doigts
    for(int i=0;i<4;i++){
        /**VECTORS*/
            //Select 3 points
        Point a = pDoigts[fDoigts[i][0]];
        Point b = pDoigts[fDoigts[i][1]];
        Point c = pDoigts[fDoigts[i][2]];
        Normal calculN(a,b,c);
        /**FIN VECTOR*/
        glBegin(GL_TRIANGLES);
        glNormal3fv(calculN.getNormal());
        glColor3f(0,.8,.8);
        glNormal3f(pDoigts[i].x,pDoigts[i].y,pDoigts[i].z);
        for(int j=0;j<3;j++){
            glVertex3f(pDoigts[fDoigts[i][j]].x, pDoigts[fDoigts[i][j]].y, pDoigts[fDoigts[i][j]].z);
        }
        glColor3f(1,1,1);
        glEnd();
    }
}
