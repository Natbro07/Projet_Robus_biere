/*
* @fichier capteurIR.h
* @auteur Leoppold & Kilian
* @résumé Déclaration des fonctions pour le capteur IR 
*/
#include <stdio.h>
#include <Arduino.h>

// Define model and input pin:
#define sensor A0 

//fonction 
bool distanceRack(float distanceVoulue);
void initTimer3();
void interruptionTimer3();