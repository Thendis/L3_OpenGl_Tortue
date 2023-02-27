#include "Texture.h"

Texture::Texture(unsigned int w, unsigned int h, char* f)
{
    setDimensions(w,h);
    image = new unsigned char[width*height*3];
    //Parametrage du placage de textures

    loadJpegImage(f);
    loadTex();
}

void Texture::loadJpegImage(char *fichier)
{
  struct jpeg_decompress_struct cinfo;
  struct jpeg_error_mgr jerr;
  FILE *file;
  unsigned char *ligne;

  cinfo.err = jpeg_std_error(&jerr);
  jpeg_create_decompress(&cinfo);
#ifdef __WIN32
  if (fopen_s(&file,fichier,"rb") != 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
      exit(1);
    }
#elif __GNUC__
  if ((file = fopen(fichier,"rb")) == 0)
    {
      fprintf(stderr,"Erreur : impossible d'ouvrir le fichier texture.jpg\n");
    }
#endif
  jpeg_stdio_src(&cinfo, file);
  jpeg_read_header(&cinfo, TRUE);

  if ((cinfo.image_width!=width)||(cinfo.image_height!=height)) {
    fprintf(stdout,"Erreur : l'image n'est pas de la bonne taille\n");
    exit(1);
  }
  if (cinfo.jpeg_color_space==JCS_GRAYSCALE) {
    fprintf(stdout,"Erreur : l'image doit etre de type RGB\n");
    exit(1);
  }

  jpeg_start_decompress(&cinfo);
  ligne=image;
  while (cinfo.output_scanline<cinfo.output_height)
    {
      ligne=image+3*width*cinfo.output_scanline;
      jpeg_read_scanlines(&cinfo,&ligne,1);
    }
  jpeg_finish_decompress(&cinfo);
  jpeg_destroy_decompress(&cinfo);
}

void Texture::loadTex(){
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,image);
  glEnable(GL_TEXTURE_2D);
}
float* Texture::getTexCoords(float actualFace, float nbL, float nbC)
{
    float maxFaces = nbL*nbC;
    float etage =0.f;
    float *tmp = new float[4];
    tmp[0]=0.f;tmp[1]=0.f;tmp[2]=0.f;tmp[3]=0.f;
    int l=0;
    int c=0;
    for(int i = 0;i<=nbC*nbL;i++)
    {
        c++;
        if(c>nbC)
        {
            l++;
            c=1;
        }
        if(l*nbC+c == actualFace+1)
        {
            i = nbC*nbL+1;
        };
    }
    l++;

    //Calcule minX maxX
    float baseMouvW = 1/nbC;
    float mmrW = c/nbC;
    while(mmrW>1)
    {
        mmrW=-1.f;
    }
    if(mmrW>baseMouvW)
        tmp[0]=mmrW-baseMouvW;
    tmp[1]=mmrW;
    //Calcule minY maxY
    float baseMouvH = 1/nbL;
    float mmrH = l/nbL;
    while(mmrH>1)
    {
        mmrH=-1;
    }
    if(mmrH>baseMouvH)
        tmp[2]=mmrH-baseMouvH;
    tmp[3]=mmrH;
    //cout<<"C = "<<c<<" L = "<<l<<endl;
    //cout<<tmp[0]<<','<<tmp[1]<<','<<tmp[2]<<','<<tmp[3]<<endl;
    return tmp;
}

void Texture::setDimensions(unsigned int w,unsigned int h)
{
    width = w;
    height = h;
}

unsigned int* Texture::getDimensions()
{
    unsigned int ret[2] = {width,height};
    return ret;
}
