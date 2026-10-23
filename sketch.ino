
const int doorPin = 2;
const int buzzerPin = 8;

const unsigned long openDelay = 10000; // 10 seconds
const unsigned long debounceDelay = 50;

unsigned long openTime = 0;
unsigned long lastDebounceTime = 0;

bool stableState = HIGH;
bool lastReading = HIGH;
bool wasOpen = false;

void setup() {
  pinMode(doorPin, INPUT_PULLUP);
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  noTone(buzzerPin);
}

void loop() {
  bool reading = digitalRead(doorPin);

  if (reading != lastReading) {
    lastDebounceTime = millis();
    lastReading = reading;
  }

  if (millis() - lastDebounceTime >= debounceDelay) {
    if (reading != stableState) {
      stableState = reading;

      bool doorOpen = (stableState == HIGH);

      if (doorOpen) {
        openTime = millis();
        wasOpen = true;
        Serial.println("Door opened");
      } else {
        wasOpen = false;
        noTone(buzzerPin);
        Serial.println("Door closed");
      }
    }
  }

  if (wasOpen && millis() - openTime >= openDelay) {
    tone(buzzerPin, 1000);
  }

  delay(5);
}


