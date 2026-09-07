#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/

#include <iostream>
#include <fstream>
#include "image.hpp"
#include "pgm.hpp"



ImageGris lirePGM(string source) {
    ifstream PGM;
    PGM.open(source);
    ImageGris img;
    
    if (not PGM)
    throw runtime_error("Fichier non trouve: "+source);
    
    string P;
    int col,lignes,intensite,n;
    PGM>>P>>col>>lignes>>intensite;

     img=ImageGris(lignes);
     for(int k=0;k<lignes;k++){
         img[k]=vector<double>(col);
     }
    for(int i=0;i<lignes;i++){
            for(int j=0;j<col;j++){
                PGM>>n;
                img[i][j]=n;
            }
        }
    return img;
}
int maxImageGris(ImageGris img){
     int maxImg=0;
    for(int i=0;i<img.size();i++){
         for(int j=0;j<img[i].size();j++){
             if(img[i][j]>=maxImg){
                 maxImg=img[i][j];
             }
         }
    }
    return maxImg;
}

void ecrirePGM(ImageGris img, string cible) {
      ofstream flux;
    flux.open(cible);
     if (not flux)
    throw runtime_error("Fichier non trouve: "+cible);
    flux<<"P2"<<endl;
    flux<<img[0].size()<<" "<<img.size()<<" 255"<<endl;
     for(int i=0;i<img.size();i++){
            for(int j=0;j<img[i].size();j++){
                flux<<((int)img[i][j])<<" ";
            }
        flux<<endl;
        }
}

bool ImageGrisEgal(ImageGris a, ImageGris b, float precision) {
  if (a.size() != b.size())  {
        cout << "Nombre de lignes différent" << endl;
        return false;
    }
    for (int i=0; i<a[0].size(); i++)
        if (a[0].size() != b[i].size()) {
            cout << "Nombre de colonnes différent" << endl;
            return false;
        }
    for (int i=0; i<a.size(); i++)
        for (int j=0; j<a[0].size(); j++)
            if (abs(a[i][j] - b[i][j]) > precision) {
                cout << "Valeur differentes en position " << i << "," << j
             << ": " << a[i][j] << " au lieu de " << b[i][j] << endl;
                return false;
            }
    return true;
}

ImageGris inversePGM(ImageGris img) {
  ImageGris imgInverse;
     imgInverse=ImageGris(img.size());
     for(int k=0;k<img.size();k++){
         imgInverse[k]=vector<double>(img[0].size());
     }
    
   for(int i=0;i<img.size();i++){
            for(int j=0;j<img[i].size();j++){
                    //Valeur complémentaire du pixel
                    imgInverse[i][j]=255-img[i][j];
            }
        
   }
    return imgInverse;
}

