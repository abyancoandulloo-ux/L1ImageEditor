#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include "image.hpp"
#include "sobel.hpp"
#include "pgm.hpp"
ImageGris renormalise(ImageGris img) {
   int maxImg=maxImageGris(img);

    ImageGris img255;
    img255=ImageGris(img.size());
    for(int k=0;k<img.size();k++){
         img255[k]=vector<double>(img[k].size());
     }
    
    for(int i=0;i<img.size();i++){
         for(int j=0;j<img[i].size();j++){
                 img255[i][j]=img[i][j]*255/maxImg;
         }
    }
    return img255;
}

ImageGris seuillage(ImageGris img, int seuil) {
    ImageGris imgSeuil;
    imgSeuil=ImageGris(img.size());
    for(int k=0;k<imgSeuil.size();k++){
         imgSeuil[k]=vector<double>(img[k].size());
     }
    
    for(int i=0;i<imgSeuil.size();i++){
         for(int j=0;j<imgSeuil[i].size();j++){
             if(img[i][j]>=seuil){
                 imgSeuil[i][j]=0;
             }else{
                 imgSeuil[i][j]=255;
             }
         }
    }
    return imgSeuil;
}

ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    ImageGris imgDoubleSeuil;
    imgDoubleSeuil=ImageGris(imgContour.size());
    for(int k=0;k<imgDoubleSeuil.size();k++){
         imgDoubleSeuil[k]=vector<double>(imgContour[k].size());
     }
    for(int i=0;i<imgDoubleSeuil.size();i++){
         for(int j=0;j<imgDoubleSeuil[i].size();j++){
            imgDoubleSeuil[i][j]=255;
        }
    }
    

    //Exercise 3.7(Amélioration)
    //Algorithme plus optimisé et plus rapide
    //Moins de vérification conditionnelles(on vérifie juste les pixels sélectionné), double boucle plus rapide
    
    for(int i=1;i<imgContour.size()-1; i++){
        for(int j=1;j<imgContour[0].size()-1; j++){
            //Si le pixel est sélectionné dans imgContour
            if(imgContour[i][j]==0){
                imgDoubleSeuil[i][j]=0;
                
                for(int k=-1;k<2;k++){
                    for(int l=-1;l<2;l++){
                        
                        //Vérification des voisins du pixel sélectionné
                        if(imgIntensite[i+k][j+l]>seuil){
                            imgDoubleSeuil[i+k][j+l]=0;
                        }
                    }
                }
            }
        }
    }
    return imgDoubleSeuil;
    //Exercise 3.4
    // for(int i=1;i<imgDoubleSeuil.size()-1; i++){
    //     for(int j=1;j<imgDoubleSeuil[i].size()-1; j++){

    //         //Vérifie le seuil et saute a la prochaine itération
    //         if(imgIntensite[i][j]<seuil){
    //             continue;
                
    //         }
    //         //Si la valeur du pixel>seuil,on vérifie ses voisins
    //         bool voisinZero=false;
            
    //         //Vérification des voisins dont la valeur est 0(sélectionné)
    //         if(imgContour[i-1][j-1]==0) {voisinZero=true;}
    //         if(imgContour[i-1][j]==0) {voisinZero=true;}
    //         if(imgContour[i-1][j+1]==0){ voisinZero=true;}
    //         if(imgContour[i][j-1]==0) {voisinZero=true;}
    //         if(imgContour[i][j+1]==0){ voisinZero=true;}
    //         if(imgContour[i+1][j-1]==0){ voisinZero=true;}
    //         if(imgContour[i+1][j]==0) {voisinZero=true;}
    //         if(imgContour[i+1][j+1]==0) {voisinZero=true;}

    //         if(voisinZero){
    //             imgDoubleSeuil[i][j]=0;
    //         }
    //         else{
    //             imgDoubleSeuil[i][j] = 255;
    //         }
    //     }
    // }
}
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
   ImageGris contour=seuillage(imgIntensite, seuilFort);
    for (int k=0; k<nbAmeliorations;k++) {
                contour=doubleSeuillage(imgIntensite, contour, seuilFaible);
             }
    return contour;
}

