#include <SPI.h>
#include <LoRa.h>

#define LORA_PIN_SS     16 // pin 27, IO16
#define LORA_PIN_RESET  -1
#define LORA_PIN_DIO0   26 // pin 11, IO26

#define RXD1 25
#define TXD1 27

int counter = 0;

void setup() {

  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  while (!Serial);

  Serial1.begin(115200, SERIAL_8N1, RXD1, TXD1);   

  Serial.println("LoRa Sender");

  LoRa.setPins(LORA_PIN_SS, LORA_PIN_RESET, LORA_PIN_DIO0);
  if (!LoRa.begin(868.1E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}

void loop() {
  digitalWrite(LED_BUILTIN, HIGH); 
  Serial1.println("Writing something to serial port 1");
  
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();
  LoRa.print("hello ");
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  digitalWrite(LED_BUILTIN, LOW); 
  delay(10000);
  
}
