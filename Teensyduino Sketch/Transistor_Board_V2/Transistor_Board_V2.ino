byte my_buffer[128] = {};
int result;
float exponentionalize;


byte b2;
byte pinMap[] = {4, 5, 6, 7, 8, 9, 10, 11};

void setup() {

  analogWriteResolution(14);
  analogWriteFrequency(1, 18384);

  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);

  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleControlChange(myControlChange);

  for (int i=0; i<8; i++) {
    pinMode(pinMap[i], OUTPUT);
  }
}

void loop() {

  usbMIDI.read();

}

void OnNoteOn(byte channel, byte note, byte vel) {
  analogWrite(pinMap[note - 1], vel * 128);
  Serial.println(note);
}

void OnNoteOff(byte channel, byte note, byte vel) {
  analogWrite(pinMap[note - 1], 0);
}

void myControlChange(byte channel, byte control, byte value) {

  if (channel == 1) {

    if (control >= 64) {
      b2 = value;
      //Serial.println(">64");
    } else {
      result = (value << 7) | b2;
      exponentionalize = pow((float)result / 16383, 3);
      analogWrite(pinMap[control - 1], exponentionalize * 16383);
      //Serial.print("result ---"); Serial.print(result ); Serial.println();
    }
  } else if (channel == 2) {
    analogWrite(pinMap[control - 1], value * 127);
  }
}
