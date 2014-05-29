#include <JeeLib.h>

byte node;
#define discoPin 6

typedef struct {
 byte node;
 char mode;
} Payload;

void setupPins() {
    pinMode(discoPin, OUTPUT);
}

void setupRf() {
    rf12_initialize(1, RF12_868MHZ);
    node = rf12_config();
}

void setup() {
    Serial.begin(9600);
    Serial.println("[DEVICE] is setting up...");

    Serial.println("Initialising pins...");
    setupPins();

    Serial.println("Initialising RF12...");
    setupRf();

    Serial.println("Setup complete.");
}

void disco() {
    digitalWrite(discoPin, HIGH);
    delay(20000);
    digitalWrite(discoPin, LOW);
}

void loop () {
    if (rf12_recvDone() && rf12_crc == 0 && rf12_len == sizeof (Payload)) {
        const Payload* payload = (const Payload*) rf12_data;
        int mode = (char) payload->mode;

        switch (mode) {
            case 'd':
                disco();
                break;
        }
    }
}
