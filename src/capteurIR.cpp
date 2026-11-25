/*
* @fichier capteurIR.cpp
* @auteur Leopold & Kilian
* @résumé Implementation de la fonction detectant la distance etre le robot et le rack de canette 
* @détails Il utilise le initTimer3 pour faire une moyenne
* @détails Exemple utilisation 
        float distanceVoulue = 10;
        if(distanceRack(distanceVoulue) == 1)
        {
            Serial.println("arrêt");
        }     
*/
#include "capteurIR.h"

volatile int compteurCapteur = 0;
float sum = 0;
int nbreEchantillon = 0;

/*
* @résumé 
* @param distance a partir de laquelle on veut un arret du robot
* @details Cette fonction lis la distance entre le robot et le rack de canettes
* @details Utilise le timer3 pour fair ela moyenne de la distance lu par le capteur
* @return true si la distance est atteinte et le robot doit s'arreter, false sinon.
*/
bool distanceRack(float distanceVoulue)
{
  float distance = 0; 
  int nbreAttendue = 10;
  if(compteurCapteur >=  10)
  {
    compteurCapteur = 0;
    float volts = analogRead(sensor)*0.0048828125;
    sum = sum + volts;
    nbreEchantillon++;
  }
  if(nbreEchantillon >= nbreAttendue)
  {
    float moy = (sum / nbreAttendue);
    distance = 30*pow(moy, -1.173);
    nbreEchantillon = 0;
    sum = 0;
    //Serial.print("Distance:");
    //Serial.println(distance);

    if(distance <= distanceVoulue)
    {
      return true;  //arrêt nécessaire
    }
  }
  return false; //Avance
}
