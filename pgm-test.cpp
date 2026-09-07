#include <stdexcept>
/** @file
 * Filtres de conversion couleur <-> teintes de gris
 **/

#include <iostream>
#include <stdexcept>
using namespace std;
#include "pgm.hpp"
#include "image-test.hpp"

void lireEcrirePGMTest() {
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
 // Vérification que les valeurs soient dans l'intervalle [0,255]
            // if (r<0){
            //     r=0;
            // }
            // if (r>255) {
            //     r =255;
            // }
            // if (g<0) {
            //     g=0;
            // }
            // if (g>255) {
            //     g=255;
            // }
            // if (b<0) {
            //     b=0;
            // }
            // if (b>255){
            //     b=255;
            // }
int main(){
    cerr << "Tests des fonctions lirePPM et ecrirePPM" << endl;
    lireEcrirePGMTest();
    cerr << "Tests de la fonction inverseePGM" << endl;
    inversePGMTest();
}

