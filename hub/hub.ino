#include <JeeLib.h>

byte node;
byte incoming;
bool changed = false;

typedef struct {
    byte node;
    char mode;
} Payload;

Payload payload;

void setupSerial() {
    Serial.begin(9600);
}

void setupRf() {
    rf12_initialize(1, RF12_868MHZ);
    node = rf12_config();
}

void setup() {
    setupRf();
    setupSerial();
}

void loop() {

    // send data only when you receive data:
    if (Serial.available() > 0) {

        // read the incoming byte:
        incoming = Serial.read();
        if((char) incoming > ' ') {
            
            payload.node = node;
            payload.mode = (char) incoming;
            changed = true;
        }
    }
    
    rf12_recvDone();

    if(rf12_canSend() && changed) {
        changed = false;
        rf12_sendStart(0, &payload, sizeof payload);
    }

}

