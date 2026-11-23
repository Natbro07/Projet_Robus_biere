
Projet Robot serveur de bière Robus
=======
> **Branche de Mathieu Goulet**

## Que contient la branche :

- Page web avec permettant la connection en bluetooth vers l'esp32 présent sur le robot. 
- Librairie de gestion des commandes envoyé par l'esp32 provenant du web vers Arduino pour effectuer les actions requises.

## Quelques information importante 

### Où ajouter les actions selon les commandes
(Ajouter les direction a prendre pour rejoindre la ligne et ensuite suivre la ligne. Lorsque le code du suiveur de ligne sera complet) 
- Dossier :  lib -> sous-dossier : WirelessCommand -> fichier : WirelessCommand.cpp -> gererCommande() et ajouter les actions selon la librairie du suiveur de ligne.



## Page Web
Fonctionnement de base de astro:

Contenus (images, icons, autres) - > Public ou src/assets
Code -> Src
Favicon et logo -> src/assets
Sections pouvant être réutiliser entre les pages -> components
Architecture de base de la page -> src/Layout
Contenus -> src/pages

Dans notre cas, le Header/ Barre de navigation est dans src/components/Navbar.astro, 
layout défini simplement le nom de la page et met toujours la navbar en haut de l'écran.
dans pages, index.astro est la ou notre page entière se retrouve avec en haut les informations à mettre dans nos cartes, ensuite le containeur pour les cartes avec titre, description, images, bouttons pour les commandes (commande, commande et ouverture) ensuite hors des cartes un bouton ouvrir la canette active simplement ouvre canette.

Section style : 

on défini le style des cartes, leurs taille la répétion en ligne avec une taille et un ajustement pour les petits et grand écran, le style des boutons, les effets de survol des boutons. 

Section Script :
Ajoute d'écoute d'évenement sur les boutons des cartes pour envoyé la commandes lors de l'appuis si on est connecté. Si la page vois que le status de connection est non actif, on demande de se connecter. gerer la connection web avec bluetooth. 




