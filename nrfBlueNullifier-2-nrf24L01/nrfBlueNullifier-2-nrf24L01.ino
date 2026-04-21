#include <RF24.h>
#include <esp_bt.h>
#include <esp_wifi.h>

RF24 radioA(16, 15); 
RF24 radioB(22, 21); 

uint8_t channelA = 0;
uint8_t channelB = 40;

void setupRadio(RF24 &radio) {
  if (radio.begin()) {
    radio.setPALevel(RF24_PA_MAX, true);
    radio.setDataRate(RF24_2MBPS);
    radio.setCRCLength(RF24_CRC_DISABLED);
    radio.setAutoAck(false);
    radio.stopListening();
    radio.startConstCarrier(RF24_PA_MAX, 40); 
  }
}

void setup() {
  esp_wifi_stop();
  esp_bt_controller_disable();
  
  setupRadio(radioA);
  setupRadio(radioB);
}

void loop() {
  channelA++;
  channelB++;

  if (channelA > 83) channelA = 0;
  if (channelB > 83) channelB = 0;

  radioA.setChannel(channelA);
  radioB.setChannel(channelB);
}