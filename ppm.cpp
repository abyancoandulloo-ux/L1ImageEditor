#include <stdexcept>
/** @file
 * Lecture et écriture d'images au format PPM
 **/


#include <iostream>
#include <fstream>
#include "image.hpp"
#include "ppm.hpp"

Image lirePPM(string source) {
    ifstream PPM;
    PPM.open(source);
    Image img;
    
    if (not PPM)
    throw runtime_error("Fichier non trouve: "+source);
    
    string P;
    int col,lignes,intensite;
    int r,g,b;
    Couleur n;
    PPM>>P>>col>>lignes>>intensite;

     img=Image(lignes);
     for(int k=0;k<lignes;k++){
         img[k]=vector<Couleur>(col);
     }
    for(int i=0;i<lignes;i++){
            for(int j=0;j<col;j+=1){
                PPM>>r>>g>>b;
                n.r=r;
                n.g=g;
                n.b=b;
                img[i][j]=n;
                
            }
        }
    return img;
}

void ecrirePPM(Image img, string cible) {
    ofstream flux;
    flux.open(cible);
     if (not flux)
    throw runtime_error("Fichier non trouve: "+cible);
    
    flux<<"P3"<<endl;
    flux<<img[0].size()<<" "<<img.size()<<" 255"<<endl;
     for(int i=0;i<img.size();i++){
            for(int j=0;j<img[i].size();j++){
                flux<<int(img[i][j].r)<<" "<<int(img[i][j].g)<<" "<<int(img[i][j].b)<<" ";
            }
        flux<<endl;
        }
}

