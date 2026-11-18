#include "WirelessCommand.h"


void gererCommandeInconnue(uint8_t command) {
  if (command == '\r' || command == '\n') return;

  Serial.print(F("Commande inconnue: decimal="));
  Serial.print(command);
  Serial.print(F(" hex=0x"));
  if (command < 16) Serial.print('0');
  Serial.println(command, HEX);
}
/// @brief Gère les commandes inconnues
/// @param command La commande inconnue
///////////////////////////////////////////
// A noté que les nom des breuvage seront changé pour le projet final.
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

    default:
      gererCommandeInconnue(command);
  }
}


void WirelessCommand::update() {
  if (!Serial.available()) return;
  gererCommande(static_cast<uint8_t>(Serial.read()));
}
