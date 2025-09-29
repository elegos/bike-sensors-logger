// ------------- OBD Transceiver Termination pins -------------
const int obdEnableTermCheckPin = 6;  // Digital pin to enable the termination check, injecting a small current into the CAN_H line
const int obdTermCheckPin       = 7;  // Digital pin to activate the termination
const int obdTermPin            = 8;  // Digital pin to check the OBD II port termination

// ------------- OBD termination state variables -------------
bool obdTerminationDecided                   = false;
bool obdLastTerminationState                 = false;
static unsigned long obdLastStableTime       = 0;
unsigned long obdLastStableReading           = 0;
const unsigned long OBD_STABLE_TIME_REQUIRED = 200; // in milliseconds

void setup() {
    pinMode(obdEnableTermCheckPin, OUTPUT);
    pinMode(obdTermCheckPin, INPUT_PULLUP);
    pinMode(obdTermPin, OUTPUT);

    // Disable the measurement transistor at startup
    digitalWrite(obdEnableTermCheckPin, LOW);
    digitalWrite(obdTermPin, LOW);

    Serial.begin(9600);
}

void loop() {
    if (!obdTerminationDecided && 100 < millis() && millis() <= 1000>) {
        checkOBDStableTermination();
    }
}

void checkOBDStableTermination() {
    if (obdTerminationDecided) return;

    digitalWrite(obdEnableTermCheckPin, HIGH); // Enable the measurement transistor
    bool isTerminated = !digitalRead(obdTermCheckPin);
    digitalWrite(obdEnableTermCheckPin, LOW); // Disable the measurement transistor to avoid bus interference

    // Unstable signal
    if (isTerminated != obdLastStableReading) {
        obdLastStableReading = isTerminated;
        obdLastStableTime = 0; // Reset the stable time counter

        return;
    }
    
    if (obdLastStableTime == 0) {
        obdLastStableTime = millis();

        return;
    }
    
    if (millis() - obdLastStableTime >= OBD_STABLE_TIME_REQUIRED) {
        // Stable enough, proceed with decision
        obdTerminationDecided = true;
        if (!isTerminated) {
            digitalWrite(obdTermPin, HIGH);
        }
    }
}
