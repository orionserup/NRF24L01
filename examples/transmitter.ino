
#include "../src/NRF24L01.h"

#define CS_PIN 14 // chip select pin number
#define CE_PIN 12 // chip enable pin number

NRF24L01 radio(CE_PIN, CS_PIN); // our radio instance

void setup() {

    const char tx_address[] = "RECVR"; // we want to write to this address
    const char address[] = "TSMTR"; // this is this devices address

    Serial.begin(9600); // begin serial

    if(!radio.begin()) // try to start the radio, if we cant print an error
        Serial.print("Radio Could Not Connect and/or Initialize")

    radio.setRecieveAddress(address); // we want to give this device an address
    radio.setTransmitAddress(tx_address); // we are going to send all packets to this address

    radio.setMode(TRANSMIT); // we want to trasnmit only

}

void loop() {

    const char message[] = "Hello"; // message to send, change this if you want

    if(!radio.write(message, sizeof(message))) // try to send the message , if we cant print an error
        Serial.println("Radio Failed to Write");
    else  {
        Serial.print("Radio Sent:") // if we sent it then print what we sent
        Serial.println(message);
    }
    delay(1000); // wait a second and send it again

}