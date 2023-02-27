#ifndef TEXTURE_H
#define TEXTURE_H
#include <cstdio>
#include <cstdlib>
#include <GL/freeglut.h>
#include <jpeglib.h>
#include <jerror.h>
#include <iostream>
#include <cmath>

/**
*Classe de gestion des textures. Permet de les sauvegarder et de les appeler quand necessaire
*/
class Texture{
private :
    unsigned int width;
    unsigned int height;
    unsigned char* image;


public :
/**
*Lie une image et sauvegarde ses informations
*@param w largeur de l'image
*@param h hauteur de l'image
*@param f chemin d'accès vers un fichier jpg
*/
Texture(unsigned int w, unsigned int h, char* f);
/**
*Permet de charger une autre image comme texture sur une instance de Texture
*La nouvelle image doit avoir la même taille w et h
*@param fichier chemin d'accès
*/
void loadJpegImage(char *fichier);
/**
*Charge l'image sauvegardé comme texture dans la mémoire
*/
void loadTex();
/**
*Permet de découper la texture en nbL*nbC morceaux et de récupérer celui que l'ont désire
*@param actualFace l'indice du morceau de texture désiré
*@param nbL nombre de lignes de la texture decoupé
*@param nbC nombre de colonnes de la texture découpé
*/
float* getTexCoords(float actualFace, float nbL, float nbC);

void setDimensions(unsigned int w, unsigned int h);
unsigned int* getDimensions();
};
#endif
