#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/
#include "gris-couleurs.hpp"

ImageGris CouleurAuGris( Image img ) {
    ImageGris imgGris;
    imgGris=ImageGris(img.size());
    for(int k=0;k<img.size();k++){
         imgGris[k]=vector<double>(img[k].size());
     }
    for(int i=0;i<imgGris.size();i++){
            for(int j=0;j<imgGris[i].size();j++){
                imgGris[i][j]=0.2126*img[i][j].r+0.7152*img[i][j].g+0.0722*img[i][j].b;
                
            }
        }
    return imgGris;
}

Image GrisACouleur( ImageGris img ) {
    Image imgCouleur;
    imgCouleur=Image(img.size());
    for(int k=0;k<img.size();k++){
         imgCouleur[k]=vector<Couleur>(img[k].size());
     }
    for(int i=0;i<imgCouleur.size();i++){
            for(int j=0;j<imgCouleur[i].size();j++){
                
                imgCouleur[i][j].r=img[i][j];
                imgCouleur[i][j].g=img[i][j];
                imgCouleur[i][j].b=img[i][j];
                
            }
        }
    return imgCouleur;
}

