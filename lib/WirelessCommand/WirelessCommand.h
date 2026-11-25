/*
* @fichier WirelessCommand.h
* @auteur Mathieu Goulet
* @résumé Déclaration des fonctions pour la commande sans-fil
*/
#ifndef WIRELESS_COMMAND_H
#define WIRELESS_COMMAND_H

#include <Arduino.h>
// Définition des commandes prises en charge par le robot pour la gestion des bières et l'ouverture de la canette.
enum cmdEsp : uint8_t {
  AUCUNE_COMMANDE = 0,
  DEMANDE_BIERE_ROUGE = 1,
  DEMANDE_BIERE_BLEUE = 2,
  DEMANDE_BIERE_JAUNE = 3,
  DEMANDE_OUVRIR = 4,
  DEMANDE_BIERE_ROUGE_OUVERTURE = 5,
  DEMANDE_BIERE_BLEUE_OUVERTURE = 6,
  DEMANDE_BIERE_JAUNE_OUVERTURE = 7,
};

// Déclaration de la fonction pour main.cpp 
class WirelessCommand {
 public:
  void update();
};

#endif
