#include <stdexcept>
/** @file
 * Lecture et ecriture d'images en niveau de gris au format PGM
 **/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/// BEGIN ImageGris

/** Structure de donnees pour representer une image en teintes de gris **/
typedef vector<vector<double> > ImageGris;
/// END ImageGris

/// BEGIN lirePGM

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
    flux<<img[0].size()<<" "<<img.size()<<" 255"<<endl;
     for(int i=0;i<img.size();i++){
            for(int j=0;j<img[i].size();j++){
                flux<<((int)img[i][j])<<" ";
            }
        flux<<endl;
        }
}

/** Construit une image cliché d'une image en niveau de gris
 * @param img une image en niveau de gris
 * @return l'image cliché qui inverse les niveaux de gris
 **/
ImageGris inversePGM(ImageGris img) {
     ImageGris imgInverse;
     imgInverse=ImageGris(img.size());
     for(int k=0;k<img.size();k++){
         imgInverse[k]=vector<double>(img[0].size());
     }
    
   for(int i=0;i<img.size();i++){
            for(int j=0;j<img[i].size();j++){
                    imgInverse[i][j]=255-img[i][j];
            }
        
   }
    return imgInverse;
}

void lirePGMTest(){
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    ecrirePGM(lirePGM("images/brain.pgm"),  "pgm/brain.pgm");
    ecrirePGM(lirePGM("images/illusion.pgm"),  "pgm/illusion.pgm");
}

void inversePGMTest() {
    ImageGris imageOriginale;
    cout << "Vérifier que les images obtenues dans 'pgm/' sont semblables à celles fournies dans 'pgm/correction/'" << endl;
    imageOriginale = lirePGM("images/brain.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/brain-inverse.pgm");
    imageOriginale = lirePGM("images/illusion.pgm");
    ecrirePGM(inversePGM(imageOriginale),  "pgm/illusion-inverse.pgm");
}

int main() {
    lirePGMTest();
    inversePGMTest();
    return 0;
}

