#include "SuiveurLigne.h"
#include "Mouvement.h"
#include "LibRobus.h"

float virage_past = 0;
float virage = 0;
int LAST_SIDE = 1; // 0 = gauche, 1 = centre, 2 = droite

bool voitLigne(uint8_t pin)
{
  return (analogRead(pin) > SEUIL_LIGNE) == LIGNE_VALEUR_HAUTE;
}

void avance(float v_left, float v_right){
  MOTOR_SetSpeed(RIGHT, v_right);
  MOTOR_SetSpeed(LEFT,  v_left);
};

bool suiveurLigne(float vitesse)
{
    // 1. Lecture des capteurs
    bool g_check = voitLigne(PIN_GAUCHE);
    bool c_check = voitLigne(PIN_CENTRE);
    bool d_check = voitLigne(PIN_DROITE);

    if (g_check || d_check) {
        int count_d = 0;
        int count_g = 0;
        float total = 0;
        unsigned long detection_time = millis();
        while (millis() - detection_time < 10){
            g_check = voitLigne(PIN_GAUCHE);
            c_check = voitLigne(PIN_CENTRE);
            d_check = voitLigne(PIN_DROITE);
            if (g_check){
                count_g++;
            }
            else if (d_check){
                count_d++;
            }
            total++;
        }
        if (count_d >= total / 1.5 || count_g >= total / 1.5){

            // 2. Décision du virage
            if (g_check) {
                // Ligne à gauche : virage sec à gauche
                virage = -VIRAGE_BASE;
                virage_past = 0;
                LAST_SIDE = 0;
            }
            else if (d_check) {
                // Ligne à droite : virage sec à droite
                virage = VIRAGE_BASE;
                virage_past = 0;
                LAST_SIDE = 2;
            }

        }
    }
        else if (c_check){
            // Ligne au centre : réaligner tout droit
            virage = 0;
            virage_past = 0;
            LAST_SIDE = 1;
        }
        else {
            // Ligne perdue : accélération de la recherche
            if (LAST_SIDE == 0) {
                virage = -VIRAGE_BASE - virage_past;
                virage_past += SCALE;
            } 
            else if (LAST_SIDE == 2) {
                virage = VIRAGE_BASE + virage_past;
                virage_past += SCALE;
            } 
            else {
                virage = 0;
                virage_past = 0;
            }
        }

    // Autorise une plus grande amplitude de braquage
    virage = constrain(virage, -VIRAGE_MAX, VIRAGE_MAX);
    vitesse = min(vitesse, VITESSE_MAX);
    float sync = 0;
    if (virage == 0){
        sync = (0.995 * ENCODER_Read(RIGHT) - ENCODER_Read(LEFT)) * k_sync2;
        sync = constrain(sync, -0.1, 0.1);
    }
    else sync = 0;
 
    // 3. Application aux moteurs
    // La vitesse minimale est abaissée à -0.2 (marche arrière) pour permettre un pivot rapide

    avance(constrain(vitesse * (1.0 + virage), -0.2, 0.35) + sync, 
    constrain(vitesse * (1.0 - virage), -0.2, 0.35) - sync);
    
    return true;
}

void suivreLigneDistance(float distance_m, float vitesse)
{
    const float cible = distance_m * 39.37;
    ENCODER_Reset(LEFT);
    ENCODER_Reset(RIGHT);

    while (true) {
        const float dG = ENCODER_Read(LEFT) * circonference_roue / 3200.0;
        const float dD = ENCODER_Read(RIGHT) * circonference_roue / 3200.0;
        if ((dG + dD) / 2.0 >= cible) break;

        suiveurLigne(vitesse);
        delay(10);
    }

    arret();
}

void suiveurAfficherCapteurs()
{
  Serial.print("G:"); Serial.print(analogRead(PIN_GAUCHE));
  Serial.print(" | C:"); Serial.print(analogRead(PIN_CENTRE));
  Serial.print(" | D:"); Serial.println(analogRead(PIN_DROITE));
}