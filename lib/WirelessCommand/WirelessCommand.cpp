/*
* @fichier WirelessCommand.cpp
* @auteur Mathieu Goulet
* @résumé Lecture et conversion des commandes reçues de l'ESP32.
*/

#include "WirelessCommand.h"
#include <LibRobus.h>
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
          // on regarde si la commande reçue est valide 
          //et si elle est dans l'intervalle des commandes définies dans l'énumération cmdEsp.
          // Si la commande est valide, on la convertit en type cmdEsp et on la retourne.
      return static_cast<cmdEsp>(received);
    }
  }

  return AUCUNE_COMMANDE;
}

void initWirelessCommand() 
{
  BluetoothInit();
  
}
