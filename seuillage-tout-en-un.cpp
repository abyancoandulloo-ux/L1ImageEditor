#include <stdexcept>
/** @file
 * Filtres de seuillage
 **/

#include <cmath>
#include <iostream>
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

/** Une image 4x4 en teintes de gris pour les tests de renormalisation **/
ImageGris imgGrisRenorm = {
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
    {0, 50, 0, 50},
};

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
    return imgI;
}



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
    flux<<img[0].size()<<" "<<img.size()<<" 255"<<endl;
     for(int i=0;i<img.size();i++){
            for(int j=0;j<img[i].size();j++){
                flux<<((int)img[i][j])<<" ";
            }
        flux<<endl;
        }
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

/**Trouve la valeur maximale d'une image gris
*@param img un image en teintes de gris
*@return la valeur maximale
**/
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
/// BEGIN renormalise

/** Renormalize une image en teinte de gris, les ramenant dans l'intervalle [0,255]
 * @param img un image en teintes de gris
 * @return une image en teintes de gris
 **/
 

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

void renormaliseTest() {
    CHECK( ImageGrisEgal(renormalise( imgGrisRenorm),
              ImageGris( {
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
                  {0, 255, 0, 255},
              }),
              0.001) );

}
/// BEGIN seuillage

/** Filtre de seuillage
 * @param img
 * @param seuil un entier dans l'intervalle [0,255]
 * @return image en noir et blanc obtenue en remplacant la teinte de
 *  chaque pixel par
 *  - du blanc si teinte < seuil
 *  - du noir  si teinte > seuil
 **/
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

/// BEGIN doubleSeuillage

/** Filtre de double seuillage
 * @param imgIntensite image d'intensite
 * @param imgContour image codant un ensemble de pixels selectionnes
 * @param seuil un entier de l'intervalle [0,255]
 * @return une copie d'imgIntensite modifiee de sorte que:
 *  -si teinte > seuil et voisin d'un pixel de imgContour, alors pixel noir
 *  -sinon pixel blanc
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, ImageGris imgContour, int seuil) {
    ImageGris imgDoubleSeuil;
    imgDoubleSeuil=ImageGris(imgContour.size());
    //Construction du tableau imgDoubleSeuil dont tous les sous tableau sont initialisé a 255
    for(int k=0;k<imgDoubleSeuil.size();k++){
         imgDoubleSeuil[k]=vector<double>(imgContour[k].size());
     }
    
    for(int i=0;i<imgDoubleSeuil.size();i++){
         for(int j=0;j<imgDoubleSeuil[i].size();j++){
            imgDoubleSeuil[i][j]=255;
        }
    }
    
    //Parcours l'image ignorant les bornes
    for(int i=1;i<imgContour.size()-1; i++){
        for(int j=1;j<imgContour[0].size()-1; j++){
            if(imgContour[i][j]==0){
                imgDoubleSeuil[i][j]=0;
                
                //Vérification des voisins
                for(int k=-1;k<2;k++){
                    for(int l=-1;l<2;l++){
                        if(imgIntensite[i+k][j+l]>seuil){
                            
                            //Voisin sélectionné si le seuil est atteint
                            imgDoubleSeuil[i+k][j+l]=0;
                        }
                    }
                }
            }
            //Exercise 3.4
            // if(imgIntensite[i][j]<seuil){
            //     imgDoubleSeuil[i][j]=255;
            //     continue;
            // }
            // bool voisinZero=false;

            // if(imgContour[i-1][j-1]==0) {voisinZero = true;}
            // if(imgContour[i-1][j]==0) {voisinZero = true;}
            // if(imgContour[i-1][j+1]==0){ voisinZero = true;}
            // if(imgContour[i][j-1]==0) {voisinZero = true;}
            // if(imgContour[i][j+1]==0){ voisinZero = true;}
            // if(imgContour[i+1][j-1]==0){ voisinZero = true;}
            // if(imgContour[i+1][j]==0) {voisinZero = true;}
            // if(imgContour[i+1][j+1]==0) {voisinZero = true;}

            // if(voisinZero){
            //     imgDoubleSeuil[i][j] = 0;
            // }
            // else{
            //     imgDoubleSeuil[i][j] = 255;
            // }
            
        }
    }

    return imgDoubleSeuil;
}  

 
/// BEGIN doubleSeuillageIteratif

/** Filtre de double seuillage iteratif
 * @param imgIntensite image d'intensité
 * @param seuilFort un entier de l'intervalle [0,255]
 * @param seuilFaible un entier de l'intervalle [0,255]
 * @param nbAmeliorations un entier non negatif: le nombre d'itérations
 * @return le double seuillage de img
 **/
ImageGris doubleSeuillage(ImageGris imgIntensite, int seuilFort, int seuilFaible, int nbAmeliorations) {
    ImageGris contour = seuillage(imgIntensite, seuilFort);
    for (int k=0; k<nbAmeliorations;k++) {
                contour = doubleSeuillage(imgIntensite, contour, seuilFaible);
             }
    return contour;
}


void seuillageTest() {
    CHECK( ImageGrisEgal(seuillage( imgGrisTest, 80),
              ImageGris( {
                  {255, 0, 255, 0},
                  {255, 0, 0, 0},
                  {0, 0, 0, 0},
                  {0, 0, 0, 0}
              }),
              0.001) );
    CHECK( ImageGrisEgal(seuillage( intensite(imgGrisTest), 80),
              ImageGris( {
                  {255, 255, 255, 255},
                  {255, 0, 0, 255},
                  {255, 255, 0, 255},
                  {255, 255, 255, 255}
              }),
              0.001) );
    CHECK( ImageGrisEgal(doubleSeuillage(intensite(imgGrisTest), 400, 80, 4 ),
                          ImageGris( {
                              {255, 255, 255, 255},
                              {255, 0, 0, 255},
                              {255, 255, 0, 255},
                              {255, 255, 255, 255}
                          }),
                          0.001) );

    
    cout << "Vérifier que les images obtenues dans 'seuillage/' sont semblables à celles fournies dans 'seuillage/correction/'" << endl;
    ecrirePGM(seuillage(intensite(lirePGM("images/Billes.256.pgm")), 80), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Willis.512.pgm"  )), 110), "seuillage/Willis.512.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;
 ecrirePGM(seuillage(intensite(lirePGM("images/House.256.pgm")), 70), "seuillage/Billes.256.pgm");
    ecrirePGM(seuillage(intensite(lirePGM("images/Embryos.512.pgm"  )), 100), "seuillage/Willis.512.pgm");

   

}

void doubleSeuillageTest(){
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(lirePGM("images/Willis.512.pgm"), seuillage(intensite(lirePGM("images/Willis.512.pgm")), 100), 80), "seuillage_double/Willis.512.pgm");
    ecrirePGM(doubleSeuillage(lirePGM("images/Billes.256.pgm"), seuillage(intensite(lirePGM("images/Billes.256.pgm")), 100), 80), "seuillage_double/Billes.256.pgm");
    cout << "\tProposer des seuils pour Embryos.512.pgm et House.256.pgm" << endl;
}

void doubleSeuillageIteratifTest() {
    cout << "Vérifier que les images obtenues dans 'seuillage_double/' sont semblables à celles fournies dans 'seuillage_double/correction/'" << endl;
    ecrirePGM(doubleSeuillage(intensite(lirePGM("images/Willis.512.pgm")), 500, 80, 100), "seuillage_double/iteratif_Willis.512.pgm");

    cout << "\tProposer des seuils pour Billes.256.pgm, Embryos.512.pgm et House.256.pgm" << endl;
    
}


int main(){
    // Ajouter les appels aux fonctions de test nécessaire

   
   seuillageTest();
   doubleSeuillageIteratifTest();
   

    


    return 0;
}

