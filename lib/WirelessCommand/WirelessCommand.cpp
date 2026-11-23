/*
* @fichier WirelessCommand.cpp
* @auteur Mathieu Goulet
* @résumé Implementation de la fonction sans-fil de l'esp32 et le web ainsi que la gestion des commandes de bières. 
* @détails nécessite l'ajuste et l'utilisateur du suiveur de ligne 
* @détails Exemple utilisation 
        wirelessCommand.update(); // Appel de la fonction update dans la boucle principale du projet. et la fonction update va lire les commandes sans-fil et les gérer.
* @détails Pour le setup
        Serial.begin(9600);     
*/

#include "WirelessCommand.h"

/*
* @résumé Code a venir pour l'ouverture de la canette.
* @param la fonction à appeler pour l'ouverture de la canette ou le code pour l'ouverture de la canette.
* @details nécessite le code pour l'ouvre canette de Mathys. 
*/
void ouvrirCanette() {
  Serial.println(F("OUVERTURE DE LA CANETTE"));
  // Ajouter les actions pour ouvrir la canette. avec l'ouvre canette.
}
// A noté que les nom des breuvage seront changé pour le projet final.
/*
* @résumé Fonction pour gérer les commandes de bières et l'ouverture de la canette.
* @param command: la commande reçu par le web vers l'esp32 qui transmet la commande au arudino.
*/
void gererCommande(uint8_t command) {
  switch (command) { // Switch case des commandes pour gérer les différentes commandes de bières
    case DEMANDE_BIERE_ROUGE: 
    case '1':
    case 'r':
    case 'R':
      Serial.println(F("BIERE ROUGE"));
      // Ajouter ici le trajet de la biere rouge.
      return;

    case DEMANDE_BIERE_BLEUE:
    case '2':
    case 'b':
    case 'B':
      Serial.println(F("BIERE BLEUE"));
      // Ajouter ici le trajet de la biere bleue.
      return;

    case DEMANDE_BIERE_JAUNE:
    case '3':
    case 'j':
    case 'J':
      Serial.println(F("BIERE JAUNE"));
      // Ajouter ici le trajet de la biere jaune.
      return;
    case DEMANDE_OUVRIR:
    case '4':
    case 'o':
    case 'O':
      Serial.println(F("OUVERTURE DE LA CANETTE"));
      ouvrirCanette();
      return;

    case DEMANDE_BIERE_ROUGE_OUVERTURE:
      Serial.println(F("BIERE ROUGE + OUVERTURE"));
      // Ajouter ici le trajet de la biere rouge.
      ouvrirCanette();
      return;

    case DEMANDE_BIERE_BLEUE_OUVERTURE:
      Serial.println(F("BIERE BLEUE + OUVERTURE"));
      // Ajouter ici le trajet de la biere bleue.
      ouvrirCanette();
      return;

    case DEMANDE_BIERE_JAUNE_OUVERTURE:
      Serial.println(F("BIERE JAUNE + OUVERTURE"));
      // Ajouter ici le trajet de la biere jaune.
      ouvrirCanette();
      return;

    default:
      Serial.println(F("COMMANDE INVALIDE"));
      return;
  }
}


void WirelessCommand::update() {
  if (!Serial.available()) return;
  gererCommande(static_cast<uint8_t>(Serial.read()));
}
