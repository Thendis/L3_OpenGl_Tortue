#include "bras.h"


void draw_bras(const int nbDeCylindres, const double h, const int n){

    glPushMatrix();
        glScalef(0.8,0.8,1);
        double current_r2=0.3, r1=0.3;
        Point* tabPoints=draw_cylindre(n, r1, current_r2+=0.005, h);
        for(int i=1;i<nbDeCylindres;i++){
            if(i>=1 && i<10){
                tabPoints=draw_cylindre_avec_cylindre(tabPoints, n, current_r2+=0.005, h);
            }
            if(i>=10 && i<30){
                tabPoints=draw_cylindre_avec_cylindre(tabPoints, n, current_r2-=0.005, h);
            }
            if(i>=30 && i<45){
                tabPoints=draw_cylindre_avec_cylindre(tabPoints, n, current_r2-=0.0065, h);
            }
            if(i>=45 && i<=50){
                tabPoints=draw_cylindre_avec_cylindre(tabPoints, n, current_r2-=0.007, h);
            }
        }

        double largeur=current_r2/2, longueur=0.15, hauteur=current_r2/2;
        glPushMatrix();
            glTranslatef(0.0, 0.0, h*nbDeCylindres);
            glRotatef(45, 0.0, 0.0, 1.0);
            glTranslatef(0.0,current_r2-hauteur,0.0);
            draw_tetraedre(largeur, longueur, hauteur);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.0, h*nbDeCylindres);
            glRotatef(90, 0.0, 0.0, 1.0);
            glTranslatef(0.0,current_r2-hauteur,0.0);
            draw_tetraedre(largeur, longueur, hauteur);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0.0, h*nbDeCylindres);
            glRotatef(-90, 0.0, 0.0, 1.0);
            glTranslatef(0.0,current_r2-hauteur,0.0);
            draw_tetraedre(largeur, longueur, hauteur);
        glPopMatrix();

        glPushMatrix();
            glRotatef(-90, 1.0, 0.0, 0.0);
            Sphere base(10,10,h*10,false);
            base.drawSphere();
        glPopMatrix();
    glPopMatrix();
    current_r2=0.35;
}
