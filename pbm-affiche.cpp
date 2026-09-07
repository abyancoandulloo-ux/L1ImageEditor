#include <stdexcept>
/** @file
 * Affichage d'une image PBM
 **/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/// BEGIN affichePBM

/** Affiche une image binaire PBM à l'écran avec ' ' pour 0 et '@' pour 1
 * @param source le nom d'un fichier PBM
 **/
void affichePBM(string source)  {
    ifstream flux;
    flux.open(source);
    string P;
    int col,lignes,n;
    flux>>P>>col>>lignes;
       
        for(int i=0;i<lignes;i++){
            for(int j=0;j<col;j++){
                flux>>n;
                if(n==0){
                    cout<<" ";
                }
                 else if(n==1){
                    cout<<"@";
                }
            }
            cout<<endl;
        }
    }


/** Echange le noir et le blanc dans une image PBM
 * @param source le nom du fichier PBM à lire
 * @param cible le nom du nouveau fichier PMB créé
 **/
void inversePBM(string source, string cible) {
   ifstream fluxLecture;
    fluxLecture.open(source);

    ofstream fluxEcriture;
    fluxEcriture.open(cible);
    
    string P;
    int col,lignes,n;
    fluxLecture>>P>>col>>lignes;
    fluxEcriture<<P<<endl;
    fluxEcriture<<col<<" "<<lignes<<endl;
        for(int i=0;i<lignes;i++){
            for(int j=0;j<col;j++){
                fluxLecture>>n;
                if(n==0){
                    fluxEcriture<<1<<" ";
                }
                 else if(n==1){
                    fluxEcriture<<0<<" ";
                }
            }
            fluxEcriture<<endl;
        }
    
}


int main(){
    cout << "Affichage du smiley " << endl;
    affichePBM("./images/smiley.pbm");
    cout << "Fabrication du smiley inversé (vérifiez que le nouveau fichier a été créé dans le dossier pbm/smiley-inverse.pbm" << endl;
    inversePBM("images/smiley.pbm","pbm/smiley-inverse.pbm");
    cout << "Affichage du smiley inversé" << endl;
    affichePBM("./pbm/smiley-inverse.pbm");
    return 0;
}

