
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

uint64_t address[6] = {0x7878787878LL,
                       0xB3B4B5B6F1LL,
                       0xB3B4B5B6CDLL,
                       0xB3B4B5B6A3LL,
                       0xB3B4B5B60FLL,
                       0xB3B4B5B605LL
                      };

RF24 radio(10, 9);

struct joystick {
  int potLX;
  int potLY;
  int potRX;
  int potRY;
  byte buttons;
};

joystick joystickData;

bool SW1 = false;
bool SW2 = false;
bool SW3 = false;
bool SW4 = false;
bool SW5 = false;
bool SW6 = false;
bool SW7 = false;

void setup() {

  Serial.begin(115200);
  Serial.println("");
  Serial.println("Iniciando RX");
  delay(1000);


  while (!radio.begin()) {
    Serial.println(F("Radio não responde!!"));
    delay (1000); // preso em loop
    radio.begin();
  }

  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(0, address[0]);
  radio.startListening();

}

void loop() {
  if (radio.available()) {
    radio.read(&joystickData, sizeof(joystick));
  }

  SW1 = bitRead(joystickData.buttons, 1);
  SW2 = bitRead(joystickData.buttons, 2);
  SW3 = bitRead(joystickData.buttons, 3);
  SW4 = bitRead(joystickData.buttons, 4);
  SW5 = bitRead(joystickData.buttons, 5);
  SW6 = bitRead(joystickData.buttons, 6);
  SW7 = bitRead(joystickData.buttons, 7);

  Serial.print("SW1: ");
  Serial.print(SW1);
  Serial.print("; SW2: ");
  Serial.print(SW2);
  Serial.print("; SW3: ");
  Serial.print(SW3);
  Serial.print("; SW4: ");
  Serial.print(SW4);
  Serial.print("; SW5: ");
  Serial.print(SW5);
  Serial.print("; SW6: ");
  Serial.print(SW6);
  Serial.print("; SW7: ");
  Serial.print(SW7);
  Serial.print("; Pot RX: ");
  Serial.print(joystickData.potRX);
  Serial.print("; Pot RY: ");
  Serial.print(joystickData.potRY);
  Serial.print("; Pot LX: ");
  Serial.print(joystickData.potLX);
  Serial.print("; Pot LY: ");
  Serial.println(joystickData.potLY);
  delay(50);
}
