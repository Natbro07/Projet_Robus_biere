/*
Projet: Robot bière
Equipe: les 17 neurones - P17
Auteurs: Charles-Antoine Gagnon, Olivier Grant, Kilian Renard-Angebault, Mathys Pelletier, Maxime Bélanger, Natthan Poulin et Mathieu Goulet
Date: 17 novembre 2026
*/

#include <LibRobus.h>
#include "WirelessCommand.h"
#include "Mouvement.h"

WirelessCommand wirelessCommand;
float distance = 0;
void setup() 
{
  BoardInit();
  BluetoothInit(); // Initialise UART2 pour recevoir les commandes de l'ESP32.
}
void loop() 
{
  arret();
  wirelessCommand.update();
  
}