/*
Projet: Robot bière
Equipe: les 17 neurones - P17
Auteurs: Charles-Antoine Gagnon, Olivier Grant, Kilian Renard-Angebault, Mathys Pelletier, Maxime Bélanger, Natthan Poulin et Mathieu Goulet
Date: 17 novembre 2026
*/

#include <LibRobus.h>
#include "WirelessCommand.h"


cmdEsp commandeEsp = AUCUNE_COMMANDE;
void setup() 
{
  initWirelessCommand();
  Serial.begin(9600);
  Serial.println("Initialisation du robot bière");
}
void loop() 
{
  cmdEsp commande = lireCommandeSansFil();

switch (commande) {
  case DEMANDE_COCA_COLA:
    Serial.println("Demande de Coca-Cola reçue");
    
    break;

  case DEMANDE_MINUTE_MAID:
    Serial.println("Demande de Minute Maid reçue");

   break;
  case DEMANDE_PEACE_TEA:
    Serial.println("Demande de Peace Tea reçue");
   break;
  case DEMANDE_OUVRIR:
    Serial.println("Demande d'ouverture reçue");
   break;
  case DEMANDE_COCA_COLA_OUVERTURE:
    Serial.println("Demande d'ouverture de Coca-Cola reçue");
   break;
  case DEMANDE_MINUTE_MAID_OUVERTURE:
    Serial.println("Demande d'ouverture de Minute Maid reçue");
   break;
  case DEMANDE_PEACE_TEA_OUVERTURE:
    Serial.println("Demande d'ouverture de Peace Tea reçue");
    // Ajouter les actions correspondantes plus tard.
    break;

  case AUCUNE_COMMANDE:

  default:
    
    break;
 }
}
