#include <stdexcept>
/** @file
 * Filtres de Sobel
 **/
#include <cmath>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

/** Structure de donnee pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;



/** Infrastructure minimale de test **/
#define CHECK(test) if (!(test)) cerr << "Test failed in file " << __FILE__ << " line " << __LINE__ << ": " #test << endl


/** Une image 4x4 en teintes de gris pour faire des tests **/
ImageGris imgGrisTest = {
    {0, 255, 54.213, 236.589},
    {18.411, 182.376, 200.787, 120},
    {139.583, 172.841, 94.0878, 88.4974},
    {158.278, 172.841, 89.0236, 80.0384}
};



/** Construire une image en teintes de gris depuis un fichier PGM
 * @param source le nom d'un fichier PGM
 * @return une image en teintes de gris
 **/
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
/// BEGIN ecrirePGM

/** Ecrit une image en teintes de gris dans un fichier PGM
 * @param img une image en teintes de gris
 * @param cible le nom d'un fichier PGM
 **/
void ecrirePGM(ImageGris img, string cible) {
     ofstream flux;
    flux.open(cible);
     if (not flux)
    throw runtime_error("Fichier non trouve: "+cible);
    flux<<"P2"<<endl;
    flux<<img[0].size()<<" "<<img.size()<<" "<<maxImageGris(img)<<endl;
     for(int i=0;i<img.size();i++){
            for(int j=0;j<img[i].size();j++){
                flux<<((int)img[i][j])<<" ";
            }
        flux<<endl;
        }
}
ImageGris renormalise(ImageGris img) {
   int maxIntensite=255;
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








/** Teste si deux images en teintes de gris sont égales modulo imprécision numérique
 * En cas de différence un message est affiché
 * @param a une image en teintes de gris
 * @param b une image en teintes de gris
 * @param precision un flottant positif: la précision souhaitée; typiquement 0.001
 * @return vrai si les images sont égales et faux sinon
 **/
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

/// BEGIN intensiteH

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
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


/// BEGIN intensiteV

/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
  
 **/
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


/// BEGIN intensiteHV

/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
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
    //Renvoie un test correct
    return imgI;
    //Affichage de image est correct avec renormalise
    //return renormalise(imgI);
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
void testSobel() {
    CHECK( ImageGrisEgal(intensiteH(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -373.47, 227.507, 0},
                  {0, -22.1312, 323.866, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensiteV(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, -15.1398, 150.501, 0},
                  {0, -9.0336, 273.023, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(intensite(imgGrisTest),
              ImageGris( {
                  {0, 0, 0, 0},
                  {0, 373.777, 272.782, 0},
                  {0, 23.9039, 423.593, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );

    cout << "Vérifier que les images obtenues dans 'sobel/' sont semblables à celles fournies dans 'sobel/correction/'" << endl;
    ecrirePGM(renormalise(lissage(intensite(lirePGM("images/Willis.512.pgm" )))), "sobel/Willis.512.pgm");
    ecrirePGM(renormalise(lissage(intensite(lirePGM("images/Baboon.512.pgm" )))), "sobel/Baboon.512.pgm");
    ecrirePGM(renormalise(lissage(intensite(lirePGM("images/Billes.256.pgm" )))), "sobel/Billes.256.pgm");
    ecrirePGM(renormalise(lissage(intensite(lirePGM("images/Embryos.512.pgm")))), "sobel/Embryos.512.pgm");
    ecrirePGM(renormalise(lissage(intensite(lirePGM("images/House.256.pgm"  )))), "sobel/House.256.pgm");
}



int main(){

    testSobel();
    return 0 ;
}

