/*
* @fichier WirelessCommand.cpp
* @auteur Mathieu Goulet
* @résumé Lecture et conversion des commandes reçues de l'ESP32.
*/

#include "WirelessCommand.h"
// Exemmple d'utilisation 
// cmdEsp commande = lireCommandeSansFil();

// switch (commande) {
//   case DEMANDE_COCA_COLA:
//     // trajetoireBoisson(BOISSON_COCA_COLA);
//     break;

//   case DEMANDE_MINUTE_MAID:
//   case DEMANDE_PEACE_TEA:
//   case DEMANDE_OUVRIR:
//   case DEMANDE_COCA_COLA_OUVERTURE:
//   case DEMANDE_MINUTE_MAID_OUVERTURE:
//   case DEMANDE_PEACE_TEA_OUVERTURE:
//     // Ajouter les actions correspondantes plus tard.
//     break;

//   case AUCUNE_COMMANDE:
//   default:
//     // arret();
//     break;
// }
cmdEsp lireCommandeSansFil() {
  while (Serial2.available()) {
    const int received = Serial2.read();
    if (received == '\r' || received == '\n') {
      continue;
    }

    if (received >= DEMANDE_COCA_COLA &&
        received <= DEMANDE_PEACE_TEA_OUVERTURE) {
      return static_cast<cmdEsp>(received);
    }

   
  }

  return AUCUNE_COMMANDE;
}

void initWirelessCommand()
{
  // UART2 du Mega (broches 16 TX, 17 RX), même débit que l'ESP32.
  Serial2.begin(115200);
}
