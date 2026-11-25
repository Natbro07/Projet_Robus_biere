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
* @détails Pour le setup
        Serial.begin(9600);
        initTimer3();         
*/
#include "capteurIR.h"

int compteurCapteur = 0;
uint8_t timer3Flag = false;
uint8_t compteurTimer3 = 0;
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
    Serial.print("Distance:");
    Serial.println(distance);

    if(distance <= distanceVoulue)
    {
      return true;  //arrêt nécessaire
    }
  }
  return false; //Avance
}

/* 
@brief Fonction du timer3.
*/
void initTimer3()
{
  const uint8_t ancienSREG = SREG;
  cli();

  TCCR2A = 0;
  TCCR2B = 0;
  TIMSK2 = 0;
  TCNT2 = 0;
  compteurTimer3 = 0;

  // Timer2 est sur 8 bits : base de 1 ms, puis division par 10 dans l'ISR.
  // A 16 MHz, pres diviseur 64 : 250 ticks = 1 ms.
  OCR2A = (F_CPU / 64UL / 1000UL) - 1;
  OCR2B = OCR2A;
  TCCR2A = _BV(WGM21); // Mode CTC : remise a zero sur OCR2A.
  TIFR2 = _BV(OCF2A) | _BV(OCF2B) | _BV(TOV2);

  TIMSK2 = _BV(OCIE2B);
  TCCR2B = _BV(CS22); // Pres diviseur 64.

  SREG = ancienSREG;
}

/* 
* @brief Fonction d'interruption du timer3.
* @details Cette fonction est appelée toutes les 10 ms.
*/
void interruptionTimer3()
{
  timer3Flag = true;
  compteurCapteur++;
}

/*ISR(TIMER2_COMPB_vect){
  if (++compteurTimer3 >= 10){
    compteurTimer3 = 0;
    interruptionTimer3();
  }
}*/