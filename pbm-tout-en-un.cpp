#include <stdexcept>
/** @file
 * Lecture et ecriture d'images binaires au format PBM
 **/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

/// BEGIN ImageNB
/** Structure de données pour représenter une image binaire **/
typedef vector<vector<int> > ImageNB;
/// END ImageNB

/// BEGIN lirePBM

/** Construire une image binaire depuis un fichier PBM
 * @param source le nom d'un fichier PBM
 * @return une image binaire (0/1)
 **/
ImageNB lirePBM(string source) {
    ifstream PBM;
    PBM.open(source);
    ImageNB img;
    
    if (not PBM)
    throw runtime_error("Fichier non trouve: "+source);
    
    string P;
    int col,lignes,n;
    PBM>>P>>col>>lignes;

    img=ImageNB(lignes);
     for(int k=0;k<lignes;k++){
         img[k]=vector<int>(col);
     }
    for(int i=0;i<lignes;i++){
            for(int j=0;j<col;j++){
                PBM>>n;
                img[i][j]=n;
            }
        }
    return img;
}

/// BEGIN ecrirePBM

/** Ecrit une image binaire dans un fichier PBM
 * @param img une image binaire (0/1)
 * @param cible le nom d'un fichier PBM
 **/
void ecrirePBM(ImageNB img, string cible) {
    ofstream flux;
    flux.open(cible);
     if (not flux)
    throw runtime_error("Fichier non trouve: "+cible);
    flux<<"P1"<<endl;
    flux<<img[0].size()<<" "<<img.size()<<endl;
    for(int i=0;i<img.size();i++){
            for(int j=0;j<img[i].size();j++){
                flux<<img[i][j]<<" ";
            }
        flux<<endl;
        }
}


/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param img une image binaire (0/1)
 **/
void affichePBM(ImageNB img) {
       for(int i=0;i<img.size();i++){
            for(int j=0;j<img[i].size();j++){
                if(img[i][j]==0){
                cout<<" ";
                }
                else if(img[i][j]==1){
                cout<<"@";
                }
            }
           cout<<endl;
}
}

/// BEGIN inversePBM

/** Echange le noir et le blanc dans une image PBM
 * @param img une image binaire (0/1)
 * @return l'image où le blanc et le noir ont été inversés
 **/
ImageNB inversePBM(ImageNB img) {
    ImageNB imgInverse;
     imgInverse=ImageNB(img.size());
     for(int k=0;k<img.size();k++){
         imgInverse[k]=vector<int>(img[0].size());
     }
    
   for(int i=0;i<img.size();i++){
            for(int j=0;j<img[i].size();j++){
                if(img[i][j]==0){
                    imgInverse[i][j]=1;
                }
                else if(img[i][j]==1){
                 imgInverse[i][j]=0;
                }
            }
        
   }
    return imgInverse;
}

void testLirePBM(){
    cout << "Vérifier que les images obtenues dans 'pbm/' sont semblables à celles fournies dans 'pbm/correction/'" << endl;
    ecrirePBM(lirePBM("images/smiley.pbm"),  "pbm/smiley.pbm");
    ecrirePBM(lirePBM("images/cercle.pbm"),  "pbm/cercle.pbm");
    ecrirePBM(lirePBM("images/code.pbm"), "pbm/code.pbm");
    ecrirePBM(lirePBM("images/damier.pbm"), "pbm/damier.pbm");
}

int main(){
    testLirePBM();
    affichePBM(lirePBM("pbm/smiley.pbm"));
    affichePBM(lirePBM("pbm/cercle.pbm"));
     affichePBM(lirePBM("pbm/code.pbm"));
    affichePBM(lirePBM("pbm/damier.pbm"));
    affichePBM(lirePBM("pbm/smiley-inverse.pbm"));
    cout<<"Correction"<<endl;
     affichePBM(lirePBM("pbm/correction/smiley.pbm"));
    affichePBM(lirePBM("pbm/correction/cercle.pbm"));
     affichePBM(lirePBM("pbm/correction/code.pbm"));
    affichePBM(lirePBM("pbm/correction/damier.pbm"));
    affichePBM(lirePBM("pbm/correction/smiley-inverse.pbm"));
    affichePBM(inversePBM(lirePBM("pbm/cercle.pbm")));
    affichePBM(inversePBM(lirePBM("pbm/smiley-inverse.pbm")));
    cout<<endl;
    

    return 0;
}


