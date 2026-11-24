/*
* @fichier WirelessCommand.cpp
* @auteur Mathieu Goulet
* @résumé Implementation de la fonction sans-fil de l'esp32 et le web ainsi que la gestion des commandes de bières.
* @détails nécessite l'ajuste et l'utilisateur du suiveur de ligne
* @détails Exemple utilisation
        wirelessCommand.update(); // Appel de la fonction update dans la boucle principale du projet. et la fonction update va lire les commandes sans-fil et les gérer.
* @détails Pour le setup
        BoardInit();
        BluetoothInit();
*/

#include "WirelessCommand.h"
#include "Mouvement.h"
#include "SuiveurLigne.h"
#include "capteurIR.h"

void interruptionTimer3();

/*
* @résumé Code a venir pour l'ouverture de la canette.
* @param la fonction à appeler pour l'ouverture de la canette ou le code pour l'ouverture de la canette.
* @details nécessite le code pour l'ouvre canette de Mathys. 
*/
void ouvrirCanette() {
  Serial.println(F("OUVRE-CANETTE à venir"));
}

void prendrePince()
{
  Serial.println(F("PINCE NON DISPONIBLE"));
}

void suivreLigneJusquAuStand()
{
  while (!distanceRack(10)) // Tant que la distance entre le robot et le rack de canettes est supérieur à 10 cm, le robot va suivre la ligne.
  {
    suiveurLigne(0.3); // Suivi de ligne avec une vitesse de 0.3 m/s
  }
  arret();
}

void trajetBiereRouge()
{
  avance_m(0.5, 0.3);
  tourner_deg(-90, 0.25);
  suivreLigneJusquAuStand();
  arret();
}

void trajetBiereBleue()
{
  avance_m(0.5, 0.3);
  suivreLigneJusquAuStand();
  arret();
}

void trajetBiereJaune()
{
  avance_m(0.5, 0.3);
  tourner_deg(90, 0.25);
  suivreLigneJusquAuStand();
  arret();
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
      trajetBiereRouge();
      return;

    case DEMANDE_BIERE_BLEUE:
    case '2':
    case 'b':
    case 'B':
      Serial.println(F("BIERE BLEUE"));
      trajetBiereBleue();
      return;

    case DEMANDE_BIERE_JAUNE:
    case '3':
    case 'j':
    case 'J':
      Serial.println(F("BIERE JAUNE"));
      trajetBiereJaune();
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
      trajetBiereRouge();
      ouvrirCanette();
      return;

    case DEMANDE_BIERE_BLEUE_OUVERTURE:
      Serial.println(F("BIERE BLEUE + OUVERTURE"));
      trajetBiereBleue();
      ouvrirCanette();
      return;

    case DEMANDE_BIERE_JAUNE_OUVERTURE:
      Serial.println(F("BIERE JAUNE + OUVERTURE"));
      trajetBiereJaune();
      ouvrirCanette();
      return;

    default:
      arret();
      return;
  }
}


void WirelessCommand::update() {
  while (Serial2.available())
  {
    const int received = Serial2.read();
    if (received == '\r' || received == '\n')
      continue;
    gererCommande(static_cast<uint8_t>(received));
  }
}
