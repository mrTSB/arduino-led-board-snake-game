const byte ANODE_PINS[8] = {6, 7, 8, 9, 10, 11, 12, 13};
const byte CATHODE_PINS[8] = {A3, A2, A1, A0, 5, 4, 3, 2};

void setup() {
  for (byte i = 0; i < 8; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
    pinMode(CATHODE_PINS[i], OUTPUT);
  }

  for (byte i = 0; i < 8; i++) {
    digitalWrite(ANODE_PINS[i], HIGH);
    digitalWrite(CATHODE_PINS[i], HIGH);
  }

  Serial.begin(115200);
  Serial.setTimeout(100);
}

void loop() {
  byte x = 0;
  byte y = 0;

  static byte ledOn[8][8];

  while (Serial.available() > 0) {
    x = Serial.parseInt();
    y = Serial.parseInt();  
    ledOn[x][y] = !ledOn[x][y];
  }

  display(ledOn);
}

void display(byte pattern[8][8]) {
  for (byte i = 0; i < 8; i++) {
    for (byte j = 0; j < 8; j++) {
      if (pattern[i][j] == 1) {
        digitalWrite(CATHODE_PINS[j], LOW);
      }
      else {
        digitalWrite(CATHODE_PINS[j], HIGH);
      }
    }
    digitalWrite(ANODE_PINS[i], LOW);
    delayMicroseconds(100);
    digitalWrite(ANODE_PINS[i], HIGH);
  }
}
