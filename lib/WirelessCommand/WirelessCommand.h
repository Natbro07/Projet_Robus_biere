#ifndef WIRELESS_COMMAND_H
#define WIRELESS_COMMAND_H

#include <Arduino.h>

enum cmdEsp : uint8_t {
  AUCUNE_COMMANDE = 0,
  DEMANDE_BIERE_ROUGE = 1,
  DEMANDE_BIERE_BLEUE = 2,
  DEMANDE_BIERE_JAUNE = 3
};

class WirelessCommand {
 public:
  void update();
};

#endif
