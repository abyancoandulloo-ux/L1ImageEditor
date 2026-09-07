/** @file
 * Filtres de Sobel
 **/

#include "image.hpp"

/** filtre de Sobel horizontal
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite horizontale de img
 **/
ImageGris intensiteH(ImageGris img);

/** filtre de Sobel vertical
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite verticale de img
 **/
ImageGris intensiteV(ImageGris img);

/** filtre de Sobel
 * @param img une image en teintes de gris
 * @return une image en teintes de gris de l'intensite de img
 **/
ImageGris intensite(ImageGris img);
/**Trouve la valeur maximale d'une image gris
*@param img un image en teintes de gris
*@return la valeur maximale
**/
ImageGris renormaliseSobel(ImageGris img);
/**Lissage
*@param img un image en teintes de gris
*@return une image en teintes de gris plus lisse,avec un pixel égale a la moyenne de ces 8 voisins
**/
ImageGris lissage(ImageGris img);
