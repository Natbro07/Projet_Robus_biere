/*
* @fichier timer2.cpp
* @auteur Charles-Antoine Gagnon
* @résumé Déclaration des fonctions pour le timer2 
* @note déclarez vos variables dans le fichier .cpp, en extern puis déclarez les  dans votre fichier .cpp pour pouvoir les utiliser 
*/
#include "timer2.h"

int compteurTimer2 = 0;

//créer vos variables ici

/* 
* @brief Fonction d'interruption du timer2.
* @details Cette fonction est appelée toutes les 10 ms.
*/
void interruptionTimer2();
/* 
@brief Fonction du timer2.
*/
void initTimer2()
{
  const uint8_t ancienSREG = SREG;
  cli();

  TCCR2A = 0;
  TCCR2B = 0;
  TIMSK2 = 0;
  TCNT2 = 0;
  compteurTimer2 = 0;

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
* @brief Fonction d'interruption du timer2.
* @details Cette fonction est appelée toutes les 10 ms.
*/
void interruptionTimer2()
{
    //incrémenter vos compteurs ici pour les timers
}

/*
* @brief Fonction d'interruption du timer2.
* @details Cette fonction est appelée toutes les 10 ms.
*/
ISR(TIMER2_COMPB_vect){
  if (++compteurTimer2 >= 10){
    compteurTimer2 = 0;
    interruptionTimer2();
  }
}