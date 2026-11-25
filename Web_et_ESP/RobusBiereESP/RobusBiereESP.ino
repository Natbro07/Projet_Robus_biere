#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#define SERVICE_UUID "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
#define RX_CHAR_UUID "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
#define TX_CHAR_UUID "6E400003-B5A3-F393-E0A9-E50E24DCCA9E"

const byte BOUTONS[] = {18, 19, 21};
bool boutonPresse[3] = {false, false, false};

bool webConnecte = false;
BLECharacteristic* txCharacteristic;

void repondre(byte commande) {
  if (!webConnecte || !txCharacteristic) return;

  txCharacteristic->setValue(&commande, 1);
  txCharacteristic->notify();
}

void envoyerCommande(byte commande) {
  if (commande < 1 || commande > 7) {
    Serial.printf("[ESP32->Arduino] Octet refuse: %u (0x%02X)\n",
                  (unsigned)commande, (unsigned)commande);
    return;
  }

  const char* nom;
  switch (commande) {
    case 1: nom = "BIERE ROUGE"; break;
    case 2: nom = "BIERE BLEUE"; break;
    case 3: nom = "BIERE JAUNE"; break;
    case 4: nom = "OUVRIR CANETTE"; break;
    case 5: nom = "BIERE ROUGE + OUVERTURE"; break;
    case 6: nom = "BIERE BLEUE + OUVERTURE"; break;
    case 7: nom = "BIERE JAUNE + OUVERTURE"; break;
    default: nom = "COMMANDE INCONNUE"; break;
  }

  Serial.printf("[ESP32->Arduino] Envoi: %u (0x%02X) - %s\n",
                (unsigned)commande, (unsigned)commande, nom);

  const size_t octetsEnvoyes = Serial2.write(commande);
  Serial.printf("[ESP32->Arduino] Octets envoyes: %u\n",
                (unsigned)octetsEnvoyes);

  repondre(commande);
}

class CallbacksServeur : public BLEServerCallbacks {
  void onConnect(BLEServer*) override {
    webConnecte = true;
  }

  void onDisconnect(BLEServer* server) override {
    webConnecte = false;
    server->getAdvertising()->start();
  }
};

class CallbacksReception : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* characteristic) override {
    String valeur = characteristic->getValue();
    if (valeur.length()) {
      const byte commande = (byte)valeur[0];
      Serial.printf("[BLE] Reception: %u octet(s), premier octet: %u (0x%02X)\n",
                    (unsigned)valeur.length(),
                    (unsigned)commande,
                    (unsigned)commande);
      envoyerCommande(commande);
    }
  }
};

void lireBoutons() {
  for (byte i = 0; i < 3; i++) {
    bool presse = digitalRead(BOUTONS[i]) == LOW;

    if (presse && !boutonPresse[i]) {
      envoyerCommande(i + 1);
    }

    boutonPresse[i] = presse;
  }
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17);

  for (byte bouton : BOUTONS) pinMode(bouton, INPUT_PULLUP);

  BLEDevice::init("17_neurone_robot");
  BLEServer* server = BLEDevice::createServer();
  server->setCallbacks(new CallbacksServeur());

  BLEService* service = server->createService(SERVICE_UUID);

  BLECharacteristic* rx = service->createCharacteristic(
    RX_CHAR_UUID,
    BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_WRITE_NR
  );
  rx->setCallbacks(new CallbacksReception());

  txCharacteristic = service->createCharacteristic(
    TX_CHAR_UUID,
    BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ
  );
  txCharacteristic->addDescriptor(new BLE2902());

  service->start();

  BLEAdvertising* advertising = BLEDevice::getAdvertising();
  advertising->addServiceUUID(SERVICE_UUID);
  advertising->setScanResponse(true);
  advertising->start();
}

void loop() {
  lireBoutons();
  delay(20);
}
