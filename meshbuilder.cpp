#include "meshbuilder.h"
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <cmath>
#ifndef fmin
#define fmin(a,b) a<b?a:b
#endif
#define M_PI 3.14159265358979323846

#define PI 3.14159265358979323846
using namespace std;
MeshBuilder::MeshBuilder()
{
}

Mesh MeshBuilder::cylindre(double hauteur, double rayon, int cercle){
    return tronconCone(hauteur,rayon, rayon, cercle);
}

Mesh MeshBuilder::sphere(double rayon, int meri, int para)
{
    QList<QVector3D> geom;
    QList<QVector3D> norm;
    QList<int> topo;

    for(int i=0;i<para;++i){
        double anglez=-M_PI/2+(i+1)/(para+1)*M_PI;
        double r2=rayon*cos(anglez);
        double z=rayon*sin(anglez);

        for(int j=0;j<meri;++j){

            double angle=2*M_PI*j/meri;
            double x=cos(angle)*r2;
            double y=sin(angle)*r2;

            geom.append(QVector3D(x,z,y));
            norm.append(QVector3D(x,z,y)/rayon);

            if(i<para-1){

            int a=i*meri+j;
            int b=i*meri+(j+1)%meri;
            int c=(i+1)*meri+j;
            int d=(i+1)*meri+(j+1%meri);

            topo.append(a);
            topo.append(0);
            topo.append(a);

            topo.append(c);
            topo.append(0);
            topo.append(c);

            topo.append(b);
            topo.append(0);
            topo.append(b);

            topo.append(c);
            topo.append(0);
            topo.append(c);

            topo.append(d);
            topo.append(0);
            topo.append(d);

            topo.append(b);
            topo.append(0);
            topo.append(b);
            }

        }
    }
    geom.append(QVector3D(0,rayon,0));
    geom.append(QVector3D(0,-rayon,0));
    norm.append(QVector3D(0,1,0));
    norm.append(QVector3D(0,-1,0));


    return Mesh(geom,topo,norm);
}

Mesh MeshBuilder::cone(double hauteur, double rayon, int cercle){
    QList<QVector3D> geom;
    QList<QVector3D> norm;
    QList<int> topo;
    for(int i=0;i<cercle;++i){
        double co=cos(2*M_PI*i/cercle);
        double si=sin(2*M_PI*i/cercle);
        geom.append(QVector3D(co*rayon,-hauteur/2,si*rayon));
        norm.append(QVector3D(co,0,si));

        //base

        topo.append(cercle);
        topo.append(0);
        topo.append(cercle);

        topo.append(i);
        topo.append(0);
        topo.append(i);

        topo.append((i+1)%cercle);
        topo.append(0);
        topo.append((i+1)%cercle);

        //tour

        topo.append((i+1)%cercle);
        topo.append(0);
        topo.append((i+1)%cercle);

        topo.append(i);
        topo.append(0);
        topo.append(i);

        topo.append(cercle+1);
        topo.append(0);
        topo.append(cercle+1);


    }


    geom.append(QVector3D(0,-hauteur/2,0));
    geom.append(QVector3D(0,hauteur/2,0));
    norm.append(QVector3D(0,-1,0));
    norm.append(QVector3D(0,1,0));


    return Mesh(geom,topo,norm);
}

Mesh MeshBuilder::tronconCone(double hauteur, double rayon, double rayon2, int cercle){
    QList<QVector3D> geom;
    QList<QVector3D> norm;
    QList<int> topo;
    if(rayon==0&&rayon2==0){
        Mesh retour(geom, topo, norm);
        return retour;
    }

    if(rayon ==0){
        return cone(-hauteur,rayon2,cercle);
    }

    if(rayon2==0){
        return cone(hauteur,rayon,cercle);
    }

    for(int i=0;i<cercle;++i){
        double co=cos(2*M_PI*i/cercle);
        double si=sin(2*M_PI*i/cercle);
        geom.append(QVector3D(co*rayon,-hauteur/2,si*rayon));
        geom.append(QVector3D(co*rayon2,hauteur/2,si*rayon2));
        norm.append(QVector3D(co,0,si));

        //base

        topo.append(2*cercle);
        topo.append(0);
        topo.append(cercle);

        topo.append(2*i);
        topo.append(0);
        topo.append(i);

        topo.append(2*((i+1)%cercle));
        topo.append(0);
        topo.append((i+1)%cercle);


        //apex


        topo.append(2*((i+1)%cercle)+1);
        topo.append(0);
        topo.append((i+1)%cercle);

        topo.append(2*i+1);
        topo.append(0);
        topo.append(i);

        topo.append(2*cercle+1);
        topo.append(0);
        topo.append(cercle+1);

        //tour

        topo.append(2*((i+1)%cercle));
        topo.append(0);
        topo.append((i+1)%cercle);

        topo.append(2*i);
        topo.append(0);
        topo.append(i);


        topo.append(2*((i+1)%cercle)+1);
        topo.append(0);
        topo.append((i+1)%cercle);

        //tour


        topo.append(2*((i+1)%cercle)+1);
        topo.append(0);
        topo.append((i+1)%cercle);

        topo.append(2*i);
        topo.append(0);
        topo.append(i);

        topo.append(2*i+1);
        topo.append(0);
        topo.append(i);


    }


    geom.append(QVector3D(0,-hauteur/2,0));
    geom.append(QVector3D(0,hauteur/2,0));
    norm.append(QVector3D(0,-1,0));
    norm.append(QVector3D(0,1,0));


    return Mesh(geom,topo,norm);

}

Mesh MeshBuilder::sphere(double rayon, int cercle)
{
    QList<QVector3D> geom;
        QList<QVector3D> norm;
        QList<int> topo;
        cercle += (4-cercle%4)%4;
        QVector3D top(0,0,rayon);
        QVector3D bot(0,0, - rayon);

        for(int j = 1; j < cercle/2; j++) {
            for(int i = 0; i < cercle; i++) {
                QVector3D p(sin(j*PI*2/cercle)*rayon*cos(i*PI*2/cercle), sin(j*PI*2/cercle)*rayon*sin(i*PI*2/cercle),rayon*cos(j*PI*2/cercle));
                norm.append((p).normalized());
                geom.append(p);
            }
        }
        geom.append(top);
        geom.append(bot);
        QVector3D ntop(0,0,1);
        QVector3D nbot(0,0,-1);
        norm.append(ntop);
        norm.append(nbot);

        for(int i = 0; i < cercle; i++) {

            int sommet1 = cercle*(cercle/2 - 1);
            int sommet2 = cercle*(cercle/2 - 1) + 1;

            int top1 = i;
            int top2 = (i + 1)%cercle;

            int bot1 = cercle/2*cercle -2*cercle + (i + 1)%(cercle);
            int bot2 = cercle/2*cercle - 2*cercle + i;

           // QVector3D normale1 = QVector3D::normal(geom.at(sommet1),geom.at(top1),geom.at(top2));
            //norm.append(normale1);

            topo.append(sommet1);
            topo.append(0);
            topo.append(sommet1);

            topo.append(top1);
            topo.append(0);
            topo.append(top1);

            topo.append(top2);
            topo.append(0);
            topo.append(top2);

           // QVector3D normale2 = QVector3D::normal(geom.at(sommet2),geom.at(bot1),geom.at(bot2));
            //norm.append(normale2);

            topo.append(sommet2);
            topo.append(0);
            topo.append(sommet2);

            topo.append(bot1);
            topo.append(0);
            topo.append(bot1);

            topo.append(bot2);
            topo.append(0);
            topo.append(bot2);
        }

        for(int j = 0; j < cercle/2-2; j++) {
            for(int i = 0; i < cercle; i++) {

                int top1 = cercle*j + i;
                int top2 = cercle*j + cercle + (i+1)%cercle;
                int top3 = cercle*j + (i+1)%cercle;

                int bot1 = cercle*j + i;
                int bot2 = cercle*j + cercle + i%cercle;
                int bot3 = cercle*j + cercle + (i+1)%cercle;

                //QVector3D normale1 = QVector3D::normal(geom.at(top1),geom.at(top2),geom.at(top3));
                //norm.append(normale1);

                topo.append(top1);
                topo.append(0);
                topo.append(top1);

                topo.append(top2);
                topo.append(0);
                topo.append(top2);

                topo.append(top3);
                topo.append(0);
                topo.append(top3);

                //QVector3D normale2 = QVector3D::normal(geom.at(bot1),geom.at(bot2),geom.at(bot3));
                //norm.append(normale2);

                topo.append(bot1);
                topo.append(0);
                topo.append(bot1);

                topo.append(bot2);
                topo.append(0);
                topo.append(bot2);

                topo.append(bot3);
                topo.append(0);
                topo.append(bot3);
            }
        }

        Mesh retour(geom, topo, norm);
        return retour;
}

Mesh MeshBuilder::tore(QVector3D &centre, double rayonI, double demiEpaisseur, int cercle)
{
        QList<QVector3D> v;
        QList<QVector3D> vn;
        QList<int> t;

        float ri= rayonI;
        float r=demiEpaisseur;
        int sub=cercle;

        float angle=M_PI*2/sub;
        float cx=centre.x();
        float cy=centre.y();
        float cz=centre.z();
        float co;
        float si;

        float tx;
        float tz;

        float tco;
        float x ,y, z;

        int delta;
        int a, b, d;

        for(int i=0;i<sub;i++){
            delta=i*sub;
            co=cos(i*angle);
            si=sin(i*angle);

            tx=co*(ri);
            tz=si*(ri);

            for(int j=0;j<sub;j++){
                y=sin(j*angle);
                tco=cos(j*angle);
                x=co*tco;
                z=si*tco;

                v.append(QVector3D(x*r+tx+cx,y*r+cy,z*r+cz+tz));
                vn.append(QVector3D(x,y,z));

                a=delta+j;
                b=delta+((j+1)%sub);
                d=(delta+(j+sub))%(sub*sub);
                //delta+j delta+((j+1)%sub) (delta+(j+sub))%(sub*sub)
                t.append(a);
                t.append(0);
                t.append(a);
                t.append(b);
                t.append(0);
                t.append(b);
                t.append(d);
                t.append(0);
                t.append(d);

                b=(delta+(sub+(j+sub-1)%sub))%(sub*sub);

                //delta+j (delta+(j+sub))%(sub*sub) (delta+(sub+(j+sub-1)%sub))%(sub*sub)
                t.append(a);
                t.append(0);
                t.append(a);
                t.append(d);
                t.append(0);
                t.append(d);
                t.append(b);
                t.append(0);
                t.append(b);


            }



        }
        return Mesh(v,t,vn);
}


double mod(double a, double b) {
    while(a>b) {a-=b;}
    return a;
}

void MeshBuilder::saveMesh(QString &nom, Mesh& mesh)
{
    QFile file(nom);
    cout<<"fichier créé"<<endl;
    file.open((QIODevice::WriteOnly | QIODevice::Text));
    cout<<"fichier ouvert"<<endl;
    QTextStream out(&file);
    cout<<"flux créé"<<endl;

    for(QList<QVector3D>::iterator itVect = mesh.getGeom().begin(); itVect != mesh.getGeom().end(); ++itVect) {
    out << "v " << itVect->x() << " " << itVect->y() << " " << itVect->z() << "\n";
    }
    out << "\n";

    cout<<"geom ok"<<endl;

    for(QList<QVector3D>::iterator itNorm = mesh.getNorm().begin(); itNorm != mesh.getNorm().end(); ++itNorm) {
    out << "vn " << itNorm->x() << " " << itNorm->y() << " " << itNorm->z() << "\n";
    }
    out << "\n";

    out << "vt 0.0 0.0 \n\n";

    for(QList<int>::iterator it = mesh.getTopo().begin(); it != mesh.getTopo().end();) {
    out << "f ";
    for(int i = 0; i < 3; i++) {
    int face = (*(it++)) + 1;
    int texture = (*(it++)) + 1;
    int normale = (*(it++)) + 1;
    out << face << "/" << texture << "/" << normale << " ";
    }
    out << "\n";
    }

    file.close();
    cout<<"fichier fermé"<<endl;
}

MeshBuilder::~MeshBuilder()
{

}
