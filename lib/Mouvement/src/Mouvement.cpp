
#include "Mouvement.h"

float encodeur_droit = 0;
float encodeur_gauche = 0;
float encodeur_droit_past = 0;
float encodeur_gauche_past = 0;
float erreur_total_avancer = 0.0, erreur_past_avancer = 0.0;



void arret(){
  MOTOR_SetSpeed(RIGHT, 0);
  MOTOR_SetSpeed(LEFT, 0);
};

void avance(float left, float right){
  MOTOR_SetSpeed(RIGHT, right);
  MOTOR_SetSpeed(LEFT,  left);
};

void tourne(float left, float right){
  MOTOR_SetSpeed(RIGHT, right);
  MOTOR_SetSpeed(LEFT, left);
};

void tourner_deg(float angle, float vitesse){
  ENCODER_Reset(LEFT);
  ENCODER_Reset(RIGHT);

  // target arc length per wheel, signed (positive = turn right/clockwise)
  float cible = angle / 360.0 * circonference_rotation;

  float erreur_totale = 0;
  float erreur_past = cible;
  int   stable = 0;

  while (stable < 10){   // 10 loops in a row inside tolerance = done
    float dG =  ENCODER_Read(LEFT)  * circonference_roue / 3200.0;
    float dD = -ENCODER_Read(RIGHT) * circonference_roue / 3200.0;
    float distance = (dG + dD) / 2.0;

    float erreur = cible - distance;

    erreur_totale += erreur * dt_ms / 1000.0;
    erreur_totale = constrain(erreur_totale, -5, 5);   // anti-windup
    float derivee = (erreur - erreur_past) / (dt_ms / 1000.0);
    erreur_past = erreur;

    float sortie = kp_tourner * erreur + ki_tourner * erreur_totale + kd_tourner * derivee;

    // enforce a minimum speed so it doesn't stall, but stop inside tolerance
    if (fabs(erreur) > tolerance){
      if (fabs(sortie) < vmin) sortie = (sortie > 0) ? vmin : -vmin;
      stable = 0;
    } else {
      sortie = 0;
      stable++;
    }
    sortie = constrain(sortie, -vitesse, vitesse);

    tourne(sortie, -sortie);
    delay(dt_ms);
  }
  arret();
}

void avance_m(float distance, float vitesse){
  ENCODER_Reset(LEFT);
  ENCODER_Reset(RIGHT);

  float cible = distance * 39.37;   // meters -> inches

  float erreur_totale = 0;
  float erreur_past = cible;
  int   stable = 0;

  while (stable < 10){
    float dG = ENCODER_Read(LEFT)  * circonference_roue / 3200.0;
    float dD = ENCODER_Read(RIGHT) * circonference_roue / 3200.0;
    float distance_parcourue = (dG + dD) / 2.0;

    float erreur = cible - distance_parcourue;

    erreur_totale += erreur * dt_ms / 1000.0;
    erreur_totale = constrain(erreur_totale, -5, 5);   // anti-windup
    float derivee = (erreur - erreur_past) / (dt_ms / 1000.0);
    erreur_past = erreur;

    float sortie = kp_avance * erreur + ki_avance * erreur_totale + kd_avance * derivee;

    if (fabs(erreur) > tolerance){
      if (fabs(sortie) < vmin) sortie = (sortie > 0) ? vmin : -vmin;
      stable = 0;
    } else {
      sortie = 0;
      stable++;
    }
    sortie = constrain(sortie, -vitesse, vitesse);

    // straightness: if right is ahead of left, speed up left and slow right
    float sync = (0.995 * ENCODER_Read(RIGHT) - ENCODER_Read(LEFT)) * k_sync;
    sync = constrain(sync, -0.1, 0.1);
    if (sortie == 0) sync = 0;   // don't twitch when stopped

    avance(sortie + sync, sortie - sync);
    delay(dt_ms);
  }
  arret();
}
