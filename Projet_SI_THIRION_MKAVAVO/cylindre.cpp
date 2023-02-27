
#include "cylindre.h"

Point* draw_cylindre(int n, double r1, double r2, double h){
    Point* pCylindre=new Point[2*n];
    int fCylindre[n][4];

    //rempli tableau de points
    for(int k=0;k<2;k++){
        for(int i=0;i<n;i++){
            double theta=(2*i*M_PI)/n;
            if(k==0){
                pCylindre[i]={r1*cos(theta), r1*sin(theta), 0.0, 0.0,0.0,1.0};
            }
            else{
                pCylindre[i+n]={r2*cos(theta), r2*sin(theta), h, 0.0,0.0,1.0};
            }
        }
    }

    //rempli tableau de faces
    for(int i=0;i<n;i++){

        if(i==n-1){
            fCylindre[i][0]=i;
            fCylindre[i][1]=0;
            fCylindre[i][2]=n;
            fCylindre[i][3]=2*n-1;
        }
        else{
            fCylindre[i][0]=i;
            fCylindre[i][1]=i+1;
            fCylindre[i][2]=i+n+1;
            fCylindre[i][3]=i+n;
        }
    }


    //dessine le cylindre
    for (int i=0; i<n; i++)
    {/**VECTORS*/
            //Select 3 points
        Point a = pCylindre[fCylindre[i][0]];
        Point b = pCylindre[fCylindre[i][1]];
        Point c = pCylindre[fCylindre[i][2]];
        Normal calculN(a,b,c);
        /**FIN VECTOR*/
        glBegin(GL_POLYGON);
        glNormal3fv(calculN.getNormal());
        for (int j=0; j<4; j++)
        {
            glVertex3f(pCylindre[fCylindre[i][j]].x,pCylindre[fCylindre[i][j]].y,pCylindre[fCylindre[i][j]].z);
        }
        glEnd();
    }

    //couvercles du cylindre
    for(int k=0;k<=1;k++){
        glBegin(GL_POLYGON);
        for(int i=0;i<n;i++){
            glVertex3f(pCylindre[i+k*n].x,pCylindre[i+k*n].y,pCylindre[i+k*n].z);
        }
        glEnd();
    }

    return pCylindre;
}


Point* draw_cylindre_avec_cylindre(Point* autrePoints, int n, double r2, double h){
    Point* pCylindre=new Point[2*n];
    int fCylindre[n][4];

    //rempli le tableau de points à partir des points de la figure précédente
    for(int k=0;k<2;k++){
        for(int i=0;i<n;i++){
            double theta=(2*i*M_PI)/n;
            if(k==0){
                pCylindre[i]={autrePoints[i+n].x, autrePoints[i+n].y, autrePoints[i+n].z, 0.0,0.0,1.0};
            }
            else{
                pCylindre[i+n]={r2*cos(theta), r2*sin(theta), autrePoints[i+n].z+h, 0.0,0.0,1.0};
            }
        }
    }

    //rempli tableau de faces
    for(int i=0;i<n;i++){
        if(i==n-1){
            fCylindre[i][0]=i;
            fCylindre[i][1]=0;
            fCylindre[i][2]=n;
            fCylindre[i][3]=2*n-1;
        }
        else{
            fCylindre[i][0]=i;
            fCylindre[i][1]=i+1;
            fCylindre[i][2]=i+n+1;
            fCylindre[i][3]=i+n;
        }
    }

    //dessine le cylindre
    for (int i=0; i<n; i++)
    {   /**VECTORS*/
            //Select 3 points
        Point a = pCylindre[fCylindre[i][0]];
        Point b = pCylindre[fCylindre[i][1]];
        Point c = pCylindre[fCylindre[i][2]];
        Normal calculN(a,b,c);
        /**FIN VECTOR*/
        glBegin(GL_POLYGON);
        glNormal3fv(calculN.getNormal());
        for (int j=0; j<4; j++)
        {
            glVertex3f(pCylindre[fCylindre[i][j]].x,pCylindre[fCylindre[i][j]].y,pCylindre[fCylindre[i][j]].z);
        }
        glEnd();
    }

    //couvercles du cylindre
    for(int k=0;k<=1;k++){
        /**VECTORS*/
            //Select 3 points
        Point a = pCylindre[fCylindre[k][0]];
        Point b = pCylindre[fCylindre[k][1]];
        Point c = pCylindre[fCylindre[k][2]];

        Normal calculN(a,b,c);
        /**FIN VECTOR*/
        glBegin(GL_POLYGON);
        glNormal3fv(calculN.getNormal());
        for(int i=0;i<n;i++){
            glVertex3f(pCylindre[i+k*n].x,pCylindre[i+k*n].y,pCylindre[i+k*n].z);
        }
        glEnd();
    }

    return pCylindre;
}

/*Point* draw_cylindre_avec_sphere(Point* points1, Point* points2, int n, int NP){
    Point* pCylindre=new Point[2*n];
    int fCylindre[n][4];

}*/
