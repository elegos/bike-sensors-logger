// ------------- OBD Transceiver Termination pins -------------
const int terminationDPin      = 6;  // Digital pin to activate the termination
const int terminationCheckDPin = 7;  // Digital pin to check the OBD II port termination
const int canHPin              = A7; // CAN_H measurement
const int canLPin              = A6; // CAN_L measurement

// ------------- OBD termination state variables -------------
bool obdTerminationDecided                   = false;
bool obdLastTerminationState                 = false;
static unsigned long obdLastStableTime       = 0;
unsigned long obdLastStableReading           = 0;
const unsigned long OBD_STABLE_TIME_REQUIRED = 200; // in milliseconds

void setup() {
    pinMode(terminationDPin, OUTPUT);
    pinMode(terminationCheckDPin, INPUT_PULLUP);

    digitalWrite(terminationCheckDPin, LOW); // Disable the measurement transistor at startup
    Serial.begin(9600);
}

void loop() {
    if (!obdTerminationDecided && 100 < millis() && millis() <= 1000>) {
        checkOBDStableTermination();
    }
}

void checkOBDStableTermination() {
    if (obdTerminationDecided) return;
    
    bool isTerminated = digitalRead(terminationCheckDPin);

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
            digitalWrite(terminationDPin, HIGH);
        }
    }
}
