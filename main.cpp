#include <QVector3D>
#include <QVector2D>
#include "mesh.h"
#include <QString>
#include <cmath>
#include <QList>
#include <iostream>
#include <ctime>
#include <stdio.h>
#include "meshbuilder.h"

#define M_PI 3.14159265358979323846

using namespace std;
int main()
{

    QVector3D a(0,0,0);
    QVector3D b(900,900,900);

    MeshBuilder mb;
    Mesh cone = mb.sphere(10,10);
    QString nom="C:/Users/etu/Desktop/objet.off";
    mb.saveMeshOFF(nom,cone);
    mb.loadMeshOFF(nom);
    QString nom2="C:/Users/etu/Desktop/objet.obj";
    mb.saveMesh(nom2,cone);

    return 0;
}
