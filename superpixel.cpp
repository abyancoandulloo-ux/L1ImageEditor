#include <stdexcept>
/** @file
 * Filtre Super Pixel
 **/
#include <cmath>
#include "superpixel.hpp"

double distancePoints(Point p, Point c) {
    double distance=0;
    for(int i=0;i<p.size();i++){
            distance+=pow((p[i]-c[i]),2);
        
    }
    return sqrt(distance);
}

double distanceAEnsemble(Point p, EnsemblePoints C) {
   double distanceMin=0;
    for(int i=0;i<C.size();i++){
        if(distanceMin>distancePoints(p,C[i])){
            distanceMin=distancePoints(p,C[i]);
        }
    }
    return distanceMin;
}

int plusProcheVoisin(Point p, EnsemblePoints C) {
   double distanceMin=distancePoints(p,C[0]);
    int procheIndex=0;
    for(int i=0;i<C.size();i++){
        if(distanceMin>distancePoints(p,C[i])){
            distanceMin=distancePoints(p,C[i]);
            procheIndex=i;
        }
    }
    return procheIndex;
}

EnsemblePoints sousEnsemble(EnsemblePoints P,EnsemblePoints C,int k) {
    EnsemblePoints ensemble;
    ensemble=EnsemblePoints(0);
    
    for(int i=0;i<P.size();i++){
        if(k==plusProcheVoisin(P[i],C)){
            ensemble.push_back(P[i]);
        }
    }
    return ensemble;
}

Point barycentre(EnsemblePoints Q) {
    
    //Déclaration
    Point barycentre;
    
    //Allocation
    barycentre=Point(Q[0].size());
    
    //Initialisation
    for(int k=0;k<Q[0].size();k++){
        barycentre[k]=0;
    }
    //Parcours le barycentre
     for(int i=0;i<Q[0].size();i++){
         
         //Parcours le tableau Q
        for(int j=0;j<Q.size();j++){
            
            barycentre[i]+=Q[j][i]/Q.size();
             
        }
    }
    return barycentre;
}
//{{{1,1,1},{1,1,2},{},{}}

//Chaque point p est associé au point pilote c le plus proche;
//Chaque point pilote c est déplacé au barycentre de l’ensemble des points p qui lui sont associés.

EnsemblePoints KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
   for (int iter=0; iter<nbAmeliorations; iter++) {
       
        //Tableau des points p,associé a C(index des points c)
        vector<EnsemblePoints> sous;
        sous=vector<EnsemblePoints>(C.size());
       
        // Associasion des points p aux points pilotes c
        for (int i=0; i<P.size(); i++) {
            int k=plusProcheVoisin(P[i], C);
            sous[k].push_back(P[i]);
        }

        // Point c deplacé au barycentre de l'ensemble des points de p
        for (int k=0; k<C.size(); k++) {
            //Si le point c est associé a au moins 1 point p
            if (sous[k].size()>0){
                C[k]=barycentre(sous[k]);
            }
        }
    }
    return C;
    
}

EnsemblePoints FAST_KMoyenne(EnsemblePoints P,EnsemblePoints C, int nbAmeliorations) {
    vector<int> label;
    label.resize(P.size());
    for(int n=0; n<nbAmeliorations; n++) {
        vector<int> clusterSize;
        clusterSize.resize(C.size(),0);
        for (int p=((int)P.size())-1; p>=0; p--) {
            double di = 0;
            int nn=0;
            for(int d=((int)P[0].size())-1; d>=0; d--)
                di+=(P[p][d]-C[0][d])*(P[p][d]-C[0][d]);
            for(int c=((int)C.size())-1; c>=1; c--) {
                double dt=0;
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    dt+=(P[p][d]-C[c][d])*(P[p][d]-C[c][d]);
                if(dt<di) {
                    di=dt;
                    nn=c;
                }
            }
            label[p]=nn;
            clusterSize[nn]++;
        }
        for (int p=((int)P.size())-1; p>=0; p--)
            for(int d=((int)P[0].size())-1; d>=0; d--)
                C[label[p]][d]+=P[p][d];
        for(int c=((int)C.size())-1; c>=0; c--)
            if(clusterSize[c]!=0)
                for(int d=((int)P[0].size())-1; d>=0; d--)
                    C[c][d] = C[c][d]/(clusterSize[c]+1);
    }
    return C;
}

EnsemblePoints pivotSuperPixel(Image img, double lambda, int mu) {
    EnsemblePoints C;
    C=EnsemblePoints(0);
    for (int i=0; i<img.size(); i+=mu) {
        for (int j=0; j<img[i].size(); j+=mu) {
            Point p;
            
            p=Point(5);
            p[0]=i;
            p[1]=j;
            p[2]=lambda*img[i][j].r;
            p[3]=lambda*img[i][j].g;
            p[4]=lambda*img[i][j].b;
            
            C.push_back(p);
        }
    }
    return C;
}

EnsemblePoints superPixels(Image img, double lambda, int mu, int nbAmeliorations) {
    EnsemblePoints points;
    points=EnsemblePoints(0);
    EnsemblePoints pivots=pivotSuperPixel(img, lambda, mu);
    for (int i=0; i<img.size();i++) {
        for (int j=0;j<img[i].size(); j++) {
            Point p(5);
            p[0]=i;
            p[1]=j;
            p[2]=lambda*img[i][j].r;
            p[3]=lambda*img[i][j].g;
            p[4]=lambda*img[i][j].b;

            points.push_back(p);
        }
    }
    
    pivots=FAST_KMoyenne(points, pivots, nbAmeliorations);
    return pivots;
}

Image superPixel(Image img, double lambda, int mu, int nbAmeliorations) {
    // Pivots calculés par la fonction superPixels
    EnsemblePoints pivots=superPixels(img, lambda, mu, nbAmeliorations);
    Image res=img;
    for (int i=0;i<img.size(); i++) {
        for (int j=0; j<img[0].size(); j++) {
            // Construction du point 5D
            Point p(5);
            p[0]=i;
            p[1]=j;
            p[2]=lambda*img[i][j].r;
            p[3]=lambda*img[i][j].g;
            p[4]=lambda*img[i][j].b;

            bool frontiere=false;

            // Trouver l'index du pivot le plus proche de p(espace et couleur)
            int indexPivotPlusProche=plusProcheVoisin(p,pivots);
           
            // Extraction de la couleur du pivot (ponderé par lambda)
            double r=pivots[indexPivotPlusProche][2]/lambda;
            double g=pivots[indexPivotPlusProche][3]/lambda;
            double b=pivots[indexPivotPlusProche][4]/lambda;

            // Test voisin 
            // Épaisseur d'un pixel,2 voisins suffisse pour obtenir le resultat voulu/subtilté
            //      (i.j)(i+1.j)
            //      (i.j+1)
            if (j+1<img[i].size()) {
                // Construction du point 5D du voisin
                Point p2(5);
                p2[0]=i;
                p2[1]=j+1;
                p2[2]=lambda*img[i][j+1].r;
                p2[3]=lambda*img[i][j+1].g;
                p2[4]=lambda*img[i][j+1].b;
            
                int pivot2=plusProcheVoisin(p2, pivots);
                if (pivot2!=indexPivotPlusProche){
                    frontiere=true;
                }
            }
            
            // Test voisin
            if (i+1<img.size()) {
                Point p3(5);
                p3[0]=i+1;
                p3[1]=j;
                p3[2]=lambda*img[i+1][j].r;
                p3[3]=lambda*img[i+1][j].g;
                p3[4]=lambda*img[i+1][j].b;
            
                int pivot3=plusProcheVoisin(p3, pivots);
                if (pivot3!=indexPivotPlusProche) {
                    frontiere=true;
                }
            }
            // Écriture dans l'image
            res[i][j].r=r;
            res[i][j].g=g;
            res[i][j].b=b;

            // Écriture des pixels bleu
            if (frontiere) {
                res[i][j].r=0;
                res[i][j].g=0;
                res[i][j].b=255;
            }
          
        }
    }
    return res;
}

   
   









// Ecrire votre code ici


