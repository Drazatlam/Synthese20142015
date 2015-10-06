#ifndef MESHBUILDER_H
#define MESHBUILDER_H
#include "mesh.h"
#include <QVector3D>
#include <QString>
#include <QVector2D>
class MeshBuilder
{
private:

public:
    MeshBuilder();
    Mesh cylindre(double hauteur, double rayon, int cercle);
    Mesh cylindre(QVector3D& centre, double hauteur , double rayon, int cercle);
    Mesh sphere(double rayon, int meri, int para);
    Mesh sphere(double rayon, int cercle);
    Mesh tore(QVector3D& centre, double rayonI, double demiEpaisseur, int cercle);
    Mesh cone(double hauteur, double rayon, int cercle);
    Mesh tronconCone(double hauteur, double rayon, double rayon2, int cercle);
    Mesh loadMesh(QString& nom);
    void saveMesh(QString& nom, Mesh &mesh);
    ~MeshBuilder();


};
#endif // MESHBUILDER_H
