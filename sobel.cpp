#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include "sobel.hpp"
#include "pgm.hpp"
ImageGris intensiteH(ImageGris img) {
     ImageGris imgH;
    imgH=ImageGris(img.size());
     for(int k=0;k<img.size();k++){
         imgH[k]=vector<double>(img[k].size());
     }
    for(int i=0;i<imgH.size();i++){
            for(int j=0;j<imgH[i].size();j++){
                if(i==0 or j==0 or i==img.size()-1 or j==img[i].size()-1){
                    imgH[i][j]=0;
                }else{
                    imgH[i][j]=img[i-1][j-1] + 2*img[i][j-1]+img[i+1][j-1]- img[i-1][j+1] - 2*img[i][j+1] - img[i+1][j+1];
                }
                
            }
        }
    return imgH;
}

ImageGris intensiteV(ImageGris img) {
    ImageGris imgV;
    imgV=ImageGris(img.size());
     for(int k=0;k<img.size();k++){
         imgV[k]=vector<double>(img[k].size());
     }
    for(int i=0;i<img.size();i++){
            for(int j=0;j<img[i].size();j++){
                if(i==0 or j==0 or i==img.size()-1 or j==img[i].size()-1){
                    imgV[i][j]=0;
                }else{
                    imgV[i][j]=img[i-1][j-1] + 2*img[i-1][j] +img[i-1][j+1]- img[i+1][j-1] - 2*img[i+1][j] - img[i+1][j+1];
                }
            }
        }
    return imgV;
}

ImageGris intensite(ImageGris img) {
    ImageGris imgH= intensiteH(img);
    ImageGris imgV= intensiteV(img);
    ImageGris imgI;
    imgI=ImageGris(img.size());
    for(int k=0;k<img.size();k++){
         imgI[k]=vector<double>(img[k].size());
     }
    for(int i=0;i<imgI.size();i++){
            for(int j=0;j<imgI[i].size();j++){
                if(i==0 or j==0 or i==imgI.size()-1 or j==imgI[i].size()-1){
                    imgI[i][j]=0;
                }else{
                    imgI[i][j]=sqrt(imgH[i][j]*imgH[i][j]+imgV[i][j]*imgV[i][j]);
                }
                
            }
    }
    
    return imgI;
    //Affichage de image est correct avec renormalise
    
}

ImageGris renormaliseSobel(ImageGris img) {
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
ImageGris lissage(ImageGris img){
    ImageGris imgLisse;
    imgLisse=ImageGris(img.size());
    for(int k=0;k<img.size();k++){
         imgLisse[k]=vector<double>(img[k].size());
     }
    for(int i=0;i<img.size();i++){
         for(int j=0;j<img[i].size();j++){
            if(i==0 or j==0 or i==img.size()-1 or j==img.size()-1 ){
                imgLisse[i][j]=0;
            }
            else{
                imgLisse[i][j]=(img[i-1][j-1]+img[i-1][j]+img[i-1][j+1]+ img[i][j-1]+img[i][j+1]+img[i+1][j-1]+img[i+1][j]+img[i+1][j+1])/9;
            }
         }
        
   
}
     return imgLisse;
}
