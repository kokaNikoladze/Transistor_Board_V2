MIDI-CONTROLLED TRANSISTOR DRIVER
---------------------------------

This Arduino sketch turns MIDI messages into PWM voltage outputs to control transistors,
analog circuits, or other devices via 8 digital pins (pins 4–11).

FEATURES:
- Responds to USB MIDI Note On/Off: 
  - Note velocity controls output voltage (0–16383).
- Control Change (CC) support:
  - Channel 2: 7-bit control (0–127), scaled to 14-bit PWM.
  - Channel 1: High-resolution 14-bit NRPN-style control with exponential response.
    (MSB on CC < 64, LSB on CC >= 64)

PIN ASSIGNMENTS:
- Outputs 1–8 → Digital pins 4–11

NRPN FORMAT (FOR CHANNEL 1 HIGH-RES CONTROL):
- Input value: 0–16383
- MSB = value / 128     → Send to control #1 (or any CC < 64)
- LSB = value % 128     → Send to control #65 (or any CC >= 64)
- IMPORTANT: Send LSB first, then MSB

OTHER NOTES:
- Uses 14-bit PWM resolution
- PWM frequency set on pin 1 to 18.384kHz
- Includes exponential curve: pow(result / 16383.0, 3)
- Built for Teensy or other boards with analogWriteResolution()

DEPENDENCIES:
- usbMIDI library (Teensy compatible)

