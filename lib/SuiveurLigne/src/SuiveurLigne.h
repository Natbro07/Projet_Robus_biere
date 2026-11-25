
#ifndef SuiveurLigne_h
#define SuiveurLigne_h

#include <LibRobus.h>

static const uint8_t PIN_GAUCHE = A4;
static const uint8_t PIN_CENTRE = A5;
static const uint8_t PIN_DROITE = A6;

static const int SEUIL_LIGNE = 200;
static const bool LIGNE_VALEUR_HAUTE = true;

// Vitesse max globale
static const float VITESSE_MAX = 0.25; 
static const float k_sync2 = 0.005;

// Réglages pour des virages plus secs
static const float VIRAGE_BASE   = 0.40; // Virage initial plus agressif (était 0.22)
static const float SCALE         = 0.04; // Montée en puissance plus rapide (était 0.02)
static const float VIRAGE_MAX    = 0.90; // Autorise une forte correction (était 0.50)

bool voitLigne(uint8_t pin); // RETOURNE SI IL Y A UNE LIGNE SOUS LA PIN

void avance(float left, float right); // FAIS AVANCER LE ROBOT SANS CORRECTION, LES INPUTS SONT LES VITESSES DES ROUES

bool suiveurLigne(float vitesse); // RETURN TRUE QUAND LA FONCTION EST APPELÉ
void suivreLigneDistance(float distance_m, float vitesse);

void suiveurAfficherCapteurs(); // AFFICHE LES VALEURS DES PINS ANALOGUE DES CAPTEURS

#endif
