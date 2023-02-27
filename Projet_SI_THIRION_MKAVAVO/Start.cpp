#include <cstdio>
#include <cstdlib>
/****************************************************************/
/* works on mac using freeglut and xquartz                      */
/* you can install freeglut using homebrew                      */
/* xquartz can be downloaded at http://xquartz.macosforge.org   */
/****************************************************************/
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <jerror.h>
#include <iostream>
#include <cmath>
#include "Sphere.h"
#include "bras.h"
#include "jambe.h"

#ifdef __WIN32
#pragma comment (lib, "jpeg.lib")
#endif


char presse;
int anglex=30,angley=20,x,y,xold,yold;

/**DECLARATION FONCTIONS*/
void affichage();
void clavier(unsigned char touche,int x,int y);
void souris(int boutton, int etat,int x,int y);
void sourismouv(int x,int y);
void redim(int l,int h);
void moove();
void coordMeridian(double r, int nb, Point* p);

/**ZOOM CAMERA*/
double base_ortho_x = 1.5;
double base_ortho_y = 1.5;
const double zoomFactor = .1;
enum{MOUSE_LEFT_BUTTON=0,MOUSE_MIDDLE_BUTTON=1,MOUSE_RIGHT_BUTTON=2,MOUSE_SCROOL_UP=3,MOUSE_SCROOL_DOWN=4};
/**FIN ZOMM CAMERA*/

/**FONCTIONS CORPS*/
void drawBody();
void drawHead();
void drawHands();
void drawLegs();
void drawCarapuce();
void zoomIn();
void zoomOut();

/**TEXTURES*/
    Texture tShell(800,800,"textures/shell.jpg");
    Texture tAbs(800,800,"textures/abs.jpg");
    Texture tHead(800,800,"textures/carapuceFace.jpg");
    Texture tNull(800,800,"textures/null.jpg");
    Texture tSol(400,400,"textures/sol.jpg");
/**FIN TEXTURES**/

/**VARIABLE POUR ANIMATIONS*/
    Point coordSoleil[100]; //Tous les points que peut prendre la lumière automatique
    int posSoleil=0; //Indice de la position du soleil
    int animVal=1; //Variable qui rythme le moment de l'animation
/**FIN ANIMATIONS*/

/**LUMIERE BOOL*/
    bool boolL2 = false;
    bool boolL0 = true;
/**FIN LUMIERE*/


using namespace std;
int main(int argc,char **argv)
{

  /* Creation de la fenetre OpenGL */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(800,800);
  glutCreateWindow("Texture JPEG");

  /* Initialisation de l'etat d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-base_ortho_x,base_ortho_x,-base_ortho_y,base_ortho_y,-20,20);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  /**LUMIERES*/
  glShadeModel(GL_SMOOTH);
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  GLfloat spotPos[]={3,3,3,0};
  GLfloat spotLookAt[]={1,1,1}; //Pointe la carapace
  GLfloat spotColor[]={1,0,0,1};
  GLfloat initPos0[]={1,1,0,1};
  GLfloat bubuleBlue[]={0,1,1,1};

  glLightfv(GL_LIGHT0,GL_POSITION,initPos0);

  glLightfv(GL_LIGHT1,GL_AMBIENT,bubuleBlue);

  glLightfv(GL_LIGHT2,GL_DIFFUSE,spotColor);
  glLightfv(GL_LIGHT2,GL_POSITION,spotPos);
  glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,spotLookAt);
  glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,91.);

  glEnable(GL_LIGHT0);

  /*Initialisation des coordonnées de déplacement e la lumière ambiante*/
  coordMeridian(1.2,100,coordSoleil);
  glPointSize(4);

  /* Mise en place de la projection perspective */
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(45.0,1,1.0,5.0);
  glMatrixMode(GL_MODELVIEW);

  /* Mise en place des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutMouseFunc(souris);
  glutMotionFunc(sourismouv);
  glutReshapeFunc(redim);
  glutIdleFunc(moove); //Initialisation de l'animation auto
    zoomIn();
  /* Entrée dans la boucle principale glut */
  glutMainLoop();
  return 0;
}



void affichage()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  gluLookAt(0.0,0.0,2.5,0.0,0.0,0.0,0.0,1.0,0.0);
  glRotatef(angley,1.0,0.0,0.0);
  glRotatef(anglex,0.0,1.0,0.0);

    /**SOL*/
    Point coordSol[]={
        Point(-2,-.28,-2),
        Point(-2,-.28,2),
        Point(2,-.28,2),
        Point(2,-.28,-2)
    };
    tSol.loadTex();
    glBegin(GL_POLYGON);
        glNormal3f(0,1,0);
        glTexCoord2f(0,0);
        glVertex3f(coordSol[0].x,coordSol[0].y,coordSol[0].z);
        glTexCoord2f(0,1);
        glVertex3f(coordSol[1].x,coordSol[1].y,coordSol[1].z);
        glTexCoord2f(1,1);
        glVertex3f(coordSol[2].x,coordSol[2].y,coordSol[2].z);
        glTexCoord2f(1,0);
        glVertex3f(coordSol[3].x,coordSol[3].y,coordSol[3].z);
    glEnd();
    /**FIN SOL*/

    drawCarapuce();
    //Dessine tous les points de déplacement du soleil
    glBegin(GL_POINTS);
        for(int i=0;i<sizeof(coordSoleil)/sizeof(Point);i++){
            glVertex3f(coordSoleil[i].x,coordSoleil[i].y,coordSoleil[i].z);
        }
    glEnd();

    //Si l'animation est lancé, l'incrémente
    if(animVal>1){
        animVal++;
        if(animVal>=40) { //Si animation se termine alors reinitialise animVal
            animVal=1;
            glDisable(GL_LIGHT1);
        }
    }

  glutSwapBuffers();
}

/**Deplace le soleil sur le cercle*/
void moove()
{
    GLfloat pos[]={coordSoleil[posSoleil].x,coordSoleil[posSoleil].y,coordSoleil[posSoleil].z,1};
    glLightfv(GL_LIGHT0,GL_POSITION,pos);
    glutPostRedisplay();
    posSoleil++;
    if(posSoleil>=sizeof(coordSoleil)/sizeof(Point)) posSoleil=0;
}

/**
*Dessine le carapuce et le redresse
*Est dessiné couché
*/
void drawCarapuce()
{
    glPushMatrix();
        glRotated(30,0,0,1);
        glRotated(-90,1,0,0);
        glRotated(90,0,0,1);
        glScaled(.6,.7,.6);

        drawBody();
        drawHead();

        drawHands();
        drawLegs();

    glPopMatrix();

}

/**
*Dessine la carapce
*Dessine le ventre
*Actualise les mouvements de l'animation si besoin
*/
void drawBody ()
{
    int np = 30;
    int nm = 30;
    double r =.5;

    double rotBody;
    if(animVal<20)
        rotBody = animVal;
    else
        rotBody = (40-animVal);

    glPushMatrix();
        glRotated(rotBody,0,0,1);
        glRotated(rotBody,1,0,0);
        glTranslated(0,0,.3);
        glScaled(.85,1,1);
        glColor3f(1,1,1);
        /**CARAPACE*/
        glPushMatrix();
            glScaled(1,.8,1);
            Sphere shell(nm,np,r,true);
            shell.drawSphere(tShell);
            glPushMatrix();
                glRotated(90,1,0,0);
                tNull.loadTex();
                glutSolidTorus(.05,.5,20,20);
            glPopMatrix();
        glPopMatrix();

        /**ABS*/
        glPushMatrix();
            glRotated(180,1,0,0); //Retourne demi cercle
            glScaled(.85,.5,1); //Ventre plus plat
            Sphere abs(nm,np,r,true);
            abs.drawSphere(tAbs);
        glPopMatrix();
    glPopMatrix();
}

/**Dessine la tête et recentre le regard*/
void drawHead()
{
    double rotHead;
    if(animVal<20)
        rotHead = animVal;
    else
        rotHead = (40-animVal);

    glPushMatrix();
        glRotated(rotHead,0,0,1);
        glRotated(rotHead,1,0,0);
        glTranslated(0,0,.95);
        Sphere head(30,30,.25,false);
        glScaled(1,.85,1);
        glRotated(rotHead,1,0,0);
        glRotated(180,0,1,0);
        glRotated(90,0,0,1);
        head.drawSphere(tHead);
    glPopMatrix();

    glPushMatrix();
        glTranslated(0,0,.95);
        glScaled(1,.85,1);
        glRotated(90,0,0,1);
        glTranslated(animVal*.1,0,-0.05);
        glutSolidSphere(animVal*0.02,20,20);
    glPopMatrix();

    GLfloat pos[3]={animVal*.1,0,-0.05};
    glLightfv(GL_LIGHT1,GL_POSITION,pos);

}

/**Dessine les mains et les repositionne sur plusieurs axes*/
void drawHands()
{
    double rotHands;
    if(animVal<20)
        rotHands = animVal;
    else
        rotHands = (40-animVal);

    //LEFT
    glPushMatrix();
        glRotated(rotHands,0,0,1);
        glRotated(rotHands,1,0,0);
        glTranslated(0,0,.3);
        glScaled(.45,.45,.45);
        glTranslated(-.20,0,0);
        glRotated(-20-(rotHands),0,0,1); //Rotation épaule
        glTranslated(0,0,.55);
        glRotated(-70,0,1,0);
        glRotated(100,0,0,1);//Rotation pour aligner doigts
        draw_bras(40,.03,20);
    glPopMatrix();
    //RIGTH
    glPushMatrix();
        glRotated(rotHands,0,0,1);
        glRotated(rotHands,1,0,0);
        glTranslated(0,0,.3);
        glScaled(.45,.45,.45);
        glTranslated(.20,0,0);
        glRotated(20+(rotHands),0,0,1); //Rotation épaule
        glTranslated(0,0,.55);
        glRotated(70,0,1,0);
        glRotated(100,0,0,1);//Rotation pour aligner doigts
        draw_bras(40,.03,20);
    glPopMatrix();
}

/**Dessine les jambes et les repositionne sur plusieurs axes*/
void drawLegs()
{

    double rotLeg;
    if(animVal<20)
        rotLeg = animVal;
    else
        rotLeg = (40-animVal);
        //LEFT
    glPushMatrix();
        glRotated(rotLeg,0,0,1);
        glTranslated(0,0,.3);
        glTranslated(-.15,0,0);
        glTranslated(0,0,-.3);
        glRotated(50,0,0,1);
        glRotated(30,1,0,0);
        glRotated(180,0,1,0);
        glScaled(.45,.45,.45);
        draw_jambe(.3,.5);
    glPopMatrix();

        //RIGTH
    glPushMatrix();

        glTranslated(0,0,.3);
        glTranslated(.15,0,0);
        glTranslated(0,0,-.3);
        glRotated(30,1,0,0);
        glRotated(180,0,1,0);
        glScaled(.45,.45,.45);
        draw_jambe(.3,.5);
    glPopMatrix();

}

/**Lie les touche clavier
* a pour Animation
*/
void clavier(unsigned char touche,int x,int y)
{
  switch(touche) {
  case 'l':
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glutPostRedisplay();
    break;
  case 'n':
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glutPostRedisplay();
  break;
  case 'f':
    anglex=anglex-1;
    glutPostRedisplay();
  break;
  case 'h':
    anglex=anglex+1;
    glutPostRedisplay();
  break;
  case 't':
    angley=angley-1;
    glutPostRedisplay();
  break;
  case 'g':
    angley=angley+1;
    glutPostRedisplay();
  break;
  case 'z':
    zoomIn();
  break;
  case 'Z':
    zoomOut();
  break;
  case '0':
    if(boolL0)
        glDisable(GL_LIGHT0);
    else
        glEnable(GL_LIGHT0);
    boolL0 = !boolL0;
  break;
  case '2':
    if(boolL2)
    {
        glDisable(GL_LIGHT2);
        boolL2 = false;
    }
    else
    {
        glEnable(GL_LIGHT2);
        boolL2 = true;
    }
  break;
  case '1': /**Touche animation*/
    if(animVal==1) {
        animVal++;
        glEnable(GL_LIGHT1);
    }
  break;
  case 27: /* touche ESC */
    exit(0);
  default:
	  break;
  }
}

void souris(int bouton, int etat,int x,int y)
{
  if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_DOWN)
  {
    presse = 1;
    xold = x;
    yold=y;
  }
  if (bouton == GLUT_LEFT_BUTTON && etat == GLUT_UP)
    presse=0;

  if(bouton == MOUSE_SCROOL_UP)
    zoomIn();
if(bouton == MOUSE_SCROOL_DOWN)
    zoomOut();
}

void sourismouv(int x,int y)
  {
    if (presse)
    {
      anglex=anglex+(x-xold);
      angley=angley+(y-yold);
      glutPostRedisplay();
    }

    xold=x;
    yold=y;
  }

void redim(int l,int h)
{
  if (l<h)
    glViewport(0,(h-l)/2,l,l);
  else
    glViewport((l-h)/2,0,h,h);
}

void zoomIn()
{
    if(base_ortho_x>.3 && base_ortho_y > .3)
    {
        base_ortho_x-=zoomFactor;
        base_ortho_y-=zoomFactor;
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(-base_ortho_x,base_ortho_x,-base_ortho_y,base_ortho_y,-20,20);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glutPostRedisplay();
    }
}

void zoomOut()
{
    base_ortho_x+=zoomFactor;
    base_ortho_y+=zoomFactor;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-base_ortho_x,base_ortho_x,-base_ortho_y,base_ortho_y,-20,20);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutPostRedisplay();
}

/**
*Calcule les coordonnées d'un cercle
*@param r rayon. y fixé à .5
*@param nb nombre de points
*@param p array de point
*/
void coordMeridian(double r, int nb, Point* p)
{
    for(int i = 0; i<nb;i++){
        double t = ((double)i/(double)nb)*2*M_PI;
        p[i].x = r*cos(t);
        p[i].y = .5;
        p[i].z = r*sin(t);
    }
}

