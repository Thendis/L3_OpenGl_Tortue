
#include "jambe.h"

void draw_jambe(const double r, const double h){

        //TOP LEG
    Sphere rotule1(30,30,r,false);
    rotule1.drawSphere();
    //glutSolidSphere(r,20,20);
    glPushMatrix();
        glRotated(-20,1,0,0);
        draw_cylindre(30, r, r, h);
            //LEG
        glPushMatrix();
            glTranslatef(0.0, 0.0, h);
            Sphere rotule2(30,30,r,false);
            rotule2.drawSphere();
            //glutSolidSphere(r,20,20);
        glPopMatrix();
            //FOOT
            glPushMatrix();
                glTranslatef(0.0, 0.0, r*2-.1);
                glRotated(20,1,0,0);
                glTranslatef(0.0, 0.0, 0);
                draw_cylindre(30, r, r, h);

                //griffes du pied
            glPushMatrix();
                glTranslatef(0.0,0.0,(h));
                glRotatef(-90,1.0,0.0,0.0);
                glTranslatef(0.0,0.0,r);
                draw_tetraedre(r/3, r/5*2, r/3);
            glPopMatrix();

            glPushMatrix();
                glRotatef(-90,1.0,0.0,0.0);
                glRotatef((M_PI/6)*(180/M_PI),0.0,1.0,0.0);
                glTranslatef(0.0,-h,r);
                draw_tetraedre(r/3, r/5*2, r/3);
            glPopMatrix();

            glPushMatrix();
                glRotatef(-90,1.0,0.0,0.0);
                glRotatef(-(M_PI/6)*(180/M_PI),0.0,1.0,0.0);
                glTranslatef(0.0,-h,r);
                draw_tetraedre(r/3, r/5*2, r/3);
            glPopMatrix();

            //griffe à l'arrière de la patte
            glPushMatrix();
                glRotatef(90,1.0,0.0,0.0);
                glRotatef(180,0.0,0.0,1.0);
                glTranslatef(0.0,-h,0.0);
                glTranslatef(0.0,0.0,r);
                draw_tetraedre(r/3, r/4, r);
            glPopMatrix();
            glPopMatrix();
    glPopMatrix();

}
