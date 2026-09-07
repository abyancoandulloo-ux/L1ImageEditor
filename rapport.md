---
jupytext:
  text_representation:
    extension: .md
    format_name: myst
    format_version: 0.13
kernelspec:
  display_name: Python 3 (ipykernel)
  language: python
  name: python3
---

# Rapport de projet Image

*Les paragraphes en italique comme celui-ci vous donnent des
indications sur le contenu attendu; ils sont à supprimer une fois
votre rapport rédigé*

*Ce rapport pourra servir de support pour votre présentation orale*

*Soyez objectifs et factuels! Vous ne serez pas évalué sur ce que vous
affirmez, mais sur la pertinence et la justesse de ce que vous
affirmez.*

+++

## Auteurs

- Coan-Dulloo, Muhammad Abyan, muhammad.coan-dulloo@university-paris-saclay.fr, MI2
- Demidov, Aleksandr, aleksandr.demidov@universite-paris-saclay.fr, MI2

+++

## Résumé du travail effectué

*Pour chaque partie du sujet, décrire brièvement l'avancement de votre
projet. Exemples de réponses: «non traitée», «réalisée, documentée,
testée», «réalisée, sauf 2.3», «réalisée mais non testée», «réalisée
sauf 2.4 pour lequel notre programme ne compile pas». Pour les
questions «Aller plus loin» plus ouvertes, décrire plus en détail ce
que vous avez choisi de réaliser.*

*En plus du rapport, la documentation de chaque fonction dans le code
devra préciser son auteur et votre degré de confiance dans
l'implantation et les éléments factuels motivant cette confiance:
présence de tests, bogues et limitations connus, etc.*

- Partie 1: réalisé et testé
- Partie 2: réalisé et testé
- Partie 3: réalisé et testé (incluant les exercises "Aller plus loin")
- Partie 4: réalisé et testé
- Partie 5: réalisé et testé
- Partie 6: réalisé et testé

+++

## Démonstration

*Soutenez ce que vous affirmez dans la section précédente au moyen de
quelques exemples **bien choisis**. Vous pourrez par exemple compiler et
lancer certains de vos programmes, lancer des tests, afficher des images.*

*Ci-dessous, nous vous proposons un début de démonstration pour les différentes
parties*

*Ne gardez que des exemples pertinents qui mettent en valeur votre
travail. Inutile de perdre du temps sur le premier programme si vous
avez fait les suivants plus compliqués; l'auditeur se doutera bien que
vous avez réussi à le faire.*

+++

### Partie 1

*Les cellules commençant par `%%bash` sont interprétées comme des
commandes bash, comme dans un terminal* :

```{code-cell} ipython3
%%bash --login
clang++ pbm-affiche.cpp -o pbm-affiche
```

```{code-cell} ipython3
%%bash --login
./pbm-affiche
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pbm/smiley-inverse.pbm")      # charge l'image
im.resize((256*im.width // im.height, 256))  # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
%%bash --login
clang++ pbm-tout-en-un.cpp -o pbm-tout-en-un
```

```{code-cell} ipython3
%%bash --login
./pbm-tout-en-un
```

```{code-cell} ipython3
# Vérification d'une des images obtenues
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/code.pbm")               # charge l'image
im.resize((160, 160))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
from open_ppm import open_ppm               # importe la commande open_ppm fournie
im = open_ppm("pbm/smiley.pbm")               # charge l'image
im.resize((80, 80))                         # affiche l'image avec une taille donnée
```

### Partie 2

```{code-cell} ipython3
%%bash --login
clang++ pgm-tout-en-un.cpp -o pgm-tout-en-un
```

```{code-cell} ipython3
%%bash --login
./pgm-tout-en-un
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain.pgm")               # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

### Partie 3

```{code-cell} ipython3
%%bash --login
clang++ sobel-tout-en-un.cpp -o sobel-tout-en-un
```

```{code-cell} ipython3
! ./sobel-tout-en-un
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

*Ajoutez des cellules et complétez avec les autres programmes implantés et images réalisées*

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Embryos.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/Billes.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
 #affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_Billes.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
 #affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
 #affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_House.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
 #affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_Embryos.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

### Partie 4

```{code-cell} ipython3

```

```{code-cell} ipython3
%%bash --login
make pgm-test
```

```{code-cell} ipython3
%%bash --login
./pgm-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/brain-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/illusion-inverse.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

*Ajoutez des cellules et complétez avec les autres programmes implantés et images réalisées*

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/correction/brain.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("pgm/illusion.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
%%bash --login
make seuillage-test
```

```{code-cell} ipython3
%%bash --login
./seuillage-test
```

```{code-cell} ipython3
%%bash --login
make sobel-test
```

```{code-cell} ipython3
%%bash --login
./sobel-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
#affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Billes.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
#affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("sobel/Baboon.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
#affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_Willis.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée  seuilFort=100,seuilFaible=80
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_WillisFort.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée seuilFort=250,seuilFaible=10
```

```{code-cell} ipython3
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_WillisFaible.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée seuilFort=100,seuilFaible=10
```

```{code-cell} ipython3
 #affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_Embryos.512.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

```{code-cell} ipython3
 #affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("seuillage_double/iteratif_House.256.pgm")        # charge l'image
im.resize((256*im.width // im.height, 256))# affiche l'image avec une taille donnée
```

### Partie 5

```{code-cell} ipython3
%%bash --login
make ppm-test
```

```{code-cell} ipython3
%%bash --login
./ppm-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("ppm/House.256.ppm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("ppm/Billes.256.ppm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("ppm/Baboon.512.ppm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("gris-couleurs/House.256.pgm")       # charge l'image
im.resize((100, 68))                         # affiche l'image avec une taille donnée
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("gris-couleurs/Baboon.512.pgm")       # charge l'image
im.resize((100, 68))             
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("gris-couleurs/Billes.256.pgm")       # charge l'image
im.resize((100, 68))   
```

### Partie 6

```{code-cell} ipython3
%%bash --login
make superpixel-test
```

```{code-cell} ipython3
%%bash --login
./superpixel-test
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/Willis.512.ppm")       # charge l'image
im.resize((1024, 1024))  
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/Willislambda.512.ppm")       # charge l'image lambda=100 detaille sans contour,petite region,
im.resize((1024, 1024))                       #accorde plus d importance a couleur
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/Willismu.512.ppm")       # charge l'image mu=100 contrast distinct
im.resize((1024, 1024))  
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/Billes.256.ppm")       # charge l'image
im.resize((1024, 1024))  
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/Baboon.512.ppm")       # charge l'image
im.resize((1024, 1024))  
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/Embryos.512.ppm")       # charge l'image
im.resize((1024, 1024))  
```

```{code-cell} ipython3
# affichage de l'image crée
from open_ppm import open_ppm                # importe la commande open_ppm fournie
im = open_ppm("superpixel/House.256.ppm")       # charge l'image
im.resize((1024, 1024))  
```

## Organisation du travail

*Décrire en quelques phrases comment vous vous êtes organisés pour
travailler sur le projet: nombre d'heures consacrées au projet,
répartition du travail dans le binôme, moyens mis en œuvre pour
collaborer, etc. Si vous avez bénéficié d'aide (en dehors de celle
de vos enseigants), précisez le.*

```{code-cell} ipython3
# Le travail a débuté dès que le projet a été rendu disponible sur JupyterLab.
# À partir de ce moment-là, j’ai consacré environ une demi-journée au projet chaque week-end, 
# ainsi que du temps supplémentaire pendant les séances de TP.

# Dans notre binôme, nous avons choisi une organisation simple : chacun a travaillé individuellement sur l’ensemble du projet,
# puis nous avons combiné nos résultats et vérifié la cohérence finale de notre travail.
# Nous n’avons reçu aucune aide extérieure, en dehors de celle fournie par les enseignants durant les séances de TP.
```

## Prise de recul

*Décrire en quelques phrases les difficultés rencontrées, ce que vous
avez appris à l'occasion du projet, le cas échéant comment vous vous y
prendriez si vous aviez à le refaire.*


(1) La première difficulté que j’ai rencontrée concernait le filtre de Sobel.
Les tests fonctionnaient, mais les images ne s’affichaient pas à cause d’un overflow error.
J’ai réalisé que le problème venait de la fonction ecrirePGM, où les intensités maximales étaient fixées par défaut à 255.
J’ai donc implanté une fonction de renormalisation pour pouvoir afficher l’image correctement.

(2) La deuxième difficulté que j’ai rencontrée concernait les algorithmes de double seuillage.
Pour la première fonction doubleSeuillage(), les tests passaient, mais cette fonction provoquait des bugs lorsque 
je l’utilisais dans la deuxième fonction, car j’avais mal interprété une condition de l’énoncé : il était indiqué qu’un pixel est à 0 
si le seuil est atteint et s’il a un voisin qui atteint également ce seuil.

(3) La troisième difficulté concernait la fonction superPixel.
L’erreur venait du fait que la fonction ecrirePPM ne tronquait pas les décimales.
C’était une erreur subtile, car ecrirePPM passait ses tests sans problème.

(4) La compréhension et l’interprétation de certains énoncés me posaient quelques difficultés.
Surtout dans la partie 6, où j’ai dû prendre du temps pour décrypter certaines instructions.
Mais en traduisant en anglais, j’ai pu remédier à ce problème.

(5) Le dessin des contours bleus m’avait posé un léger problème de visualisation, car je voulais vérifier les 8 voisins à l’aide d’une boucle.
Ensuite j'ai essayé de vérifier les voisins manuellement,sans boucle et alorsj’ai réalisé (grâce à un schéma) que 2 voisins 
suffisaient pour détecter la frontière une seule fois et obtenir un bord d’un pixel bleu

Ce projet a été pour moi un véritable test de patience, mais il m’a permis de renforcer mes compétences en débogage ainsi que mes bases en C++.
J’ai également développé mon esprit d’équipe en travaillant avec mon binôme, ainsi que mes capacités d’analyse, notamment grâce à la 
 nécessité de visualiser et de comprendre plusieurs variables en parallèle.

 Ce projet m’a appris qu’il ne faut pas toujours s’acharner sur un problème : il est parfois préférable de prendre du recul et d’avancer avec patience.
 J’ai constaté que faire une pause et revenir le lendemain permettait souvent à mon cerveau de réanalyser le problème sous un autre angle et de trouver 
 plus facilement la solution.

 Enfin, j’ai appris :

 à structurer mon approche algorithmique plutôt que de coder immédiatement(notamment avec les exercises ***);

 à identifier et comprendre l’origine réelle d’une erreur, même lorsqu’elle provient d’un détail subtil ;

 à tester mes fonctions de manière plus rigoureuse ;

 et à garder une méthode de travail organisée, notamment pour les fonctions complexes et les projets longs.

 Ce projet m’a donc apporté autant sur le plan technique que sur le plan méthodologique.


 Si je devais recommencer le projet, j’aurais pris le temps de mieux me documenter sur les formats d’images PPM et PGM, 
 ainsi que sur les algorithmes associés, avant de me lancer dans l’implémentation. Cela m’aurait évité de mal interpréter certains énoncés.

 Je pourrais également :

 planifier davantage en établissant une feuille de route claire pour chaque étape du projet ;

 prendre plus de notes lors de ma lecture de l’énoncé afin d’éviter les erreurs d’interprétation ;

 poser plus de questions ou chercher des ressources complémentaires lorsque quelque chose me paraît ambigu ;

 mieux commenter mon code, pour garder une trace claire de mes intentions au moment de l’écriture ;

 et garder une organisation stricte des fichiers et fonctions, afin de faciliter le débogage et la relecture.

 En bref, si je devais recommencer, je préparerais davantage mon approche théorique et méthodologique avant de passer au code,
 ce qui me ferait gagner du temps et éviterait plusieurs erreurs.
