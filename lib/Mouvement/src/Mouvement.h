
#ifndef Mouvement_h
#define Mouvement_h

#include <LibRobus.h>

const float kp_tourner = 0.075, ki_tourner = 0.0005, kd_tourner = 0.005;

const float vmin = 0.1;
const float tolerance = 0.03; // pouces (environ 0.5 degré près)
const int   dt_ms = 10;

const float circonference_rotation = 7.63 * 3.14159; // pouces
const float circonference_roue = 3.0 * 3.14159; // pouces

const float kd_avance = 0.0028, ki_avance = 0, kp_avance = 0.04, k_sync = 0.005;

//-------------------------------------------------------//

void arret();

void avance(float left, float right);

void tourne(float left, float right);

void tourner_deg(float angle, float vitesse);

void avance_m(float distance, float vitesse);

#endif