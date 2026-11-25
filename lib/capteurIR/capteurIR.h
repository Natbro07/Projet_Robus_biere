/*
* @fichier capteurIR.h
* @auteur Leoppold & Kilian
* @résumé Déclaration des fonctions pour le capteur IR 
*/
#include <stdio.h>
#include <Arduino.h>

// Define model and input pin:
#define sensor A0 

// Retourne true lorsque le rack est a la distance demandee, en centimetres.
bool distanceRack(float distanceVoulue);