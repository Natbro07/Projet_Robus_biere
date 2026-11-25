/*
* @fichier WirelessCommand.h
* @auteur Mathieu Goulet
* @résumé Déclaration des fonctions pour la commande sans-fil
*/
#ifndef WIRELESS_COMMAND_H
#define WIRELESS_COMMAND_H

#include <Arduino.h>
// Commandes de boissons et d'ouverture de canette reçues de l'ESP32.
enum cmdEsp : uint8_t {
  AUCUNE_COMMANDE = 0,
  DEMANDE_COCA_COLA = 1,
  DEMANDE_MINUTE_MAID = 2,
  DEMANDE_PEACE_TEA = 3,
  DEMANDE_OUVRIR = 4,
  DEMANDE_COCA_COLA_OUVERTURE = 5,
  DEMANDE_MINUTE_MAID_OUVERTURE = 6,
  DEMANDE_PEACE_TEA_OUVERTURE = 7,
};

// Retourne la prochaine commande reçue, ou AUCUNE_COMMANDE si aucune commande valide n'est disponible.
cmdEsp lireCommandeSansFil();

#endif
