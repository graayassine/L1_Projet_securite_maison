#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <Servo.h>

// ----------------------
// LoRaWAN Configuration (ABP)
// ----------------------
static const u1_t NWKSKEY[16] = { 0x37, 0xFF, 0x5F, 0xE6, 0xAC, 0xEE, 0xFD, 0x62, 0x71, 0xCC, 0x2D, 0xE0, 0xC7, 0x0F, 0x16, 0xE2 };
static const u1_t APPSKEY[16] = { 0xD7, 0x53, 0xD3, 0x8D, 0xCE, 0xD0, 0x48, 0x14, 0x44, 0xC7, 0xF0, 0xBD, 0xEA, 0xF0, 0x55, 0x8F };
static const u4_t DEVADDR = 0x260BB66E; 

void os_getArtEui(u1_t* buf) {}
void os_getDevEui(u1_t* buf) {}
void os_getDevKey(u1_t* buf) {}

const lmic_pinmap lmic_pins = {
  .nss = 10,
  .rxtx = LMIC_UNUSED_PIN,
  .rst = 8,
  .dio = {6, 6, 6}
};

// ----------------------
// Projet Capteurs
// ----------------------
const int pirPin = 2;
const int buzzerPin = 3;
const int led1 = 9;
const int led2 = 5;
const int servoPin = 7;

Servo monServo;
bool etatPrecedent = false;



void onEvent(ev_t ev) {
  // afficher les événements 
  Serial.print(F("LMIC event: "));
  Serial.println(ev);
}

void setup() {
  Serial.begin(9600);

  // Capteurs
  pinMode(pirPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  monServo.attach(servoPin);
  monServo.write(0);

  // LoRa Init
  os_init();
  LMIC_reset();

  // ABP config
  LMIC_setSession(0x1, DEVADDR, NWKSKEY, APPSKEY);

  // Canal pour TTN Europe
  // Réinitialise les canaux pour TTN Europe (EU868)
LMIC_setupChannel(0, 868100000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);
LMIC_setupChannel(1, 868300000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);
LMIC_setupChannel(2, 868500000, DR_RANGE_MAP(DR_SF12, DR_SF7), BAND_CENTI);


  LMIC_setLinkCheckMode(0);
  LMIC.dn2Dr = DR_SF9;
  LMIC_setDrTxpow(DR_SF7, 14);

  Serial.println("🔧 Setup terminé.");
}

void loop() {
  bool mouvement = digitalRead(pirPin);

  if (mouvement && !etatPrecedent) {
    Serial.println("🚨 Mouvement détecté !");
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    monServo.write(100);
    etatPrecedent = true;

    // Crée le message à envoyer
    String message = "Mouvement détecté";
    sendMessage(message);
  }

  if (etatPrecedent && mouvement) {
    for (int i = 1000; i <= 2000; i += 50) {
      tone(buzzerPin, i);
      delay(10);
    }
    for (int i = 2000; i >= 1000; i -= 50) {
      tone(buzzerPin, i);
      delay(10);
    }
  }

  if (!mouvement && etatPrecedent) {
    Serial.println("✅ Fin du mouvement.");
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    noTone(buzzerPin);
    monServo.write(0);
    etatPrecedent = false;
  }

  os_runloop_once();
}

void sendMessage(String message) {
  if (LMIC.opmode & OP_TXRXPEND) {
    Serial.println(F("⚠️ Envoi en cours, attente..."));
  } else {
    LMIC_setTxData2(1, (uint8_t*)message.c_str(), message.length(), 0);
    Serial.println("📤 Message envoyé : " + message);
  }
}

