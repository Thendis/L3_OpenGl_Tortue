#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

/**
*Classe servant a gérer les informations des points
*/
class Point{
public:
    double x, y, z;
    float r, g, b;

    Point(double x_, double y_, double z_, float r_, float g_, float b_){
        x=x_; y=y_; z=z_; r=r_; g=g_; b=b_;
    }
    Point(double x_, double y_, double z_){
        x=x_; y=y_; z=z_; r=1; g=1; b=1;
    }
    Point(){};
};

#endif // POINT_H_INCLUDED
