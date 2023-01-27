#include "../src/NRF24L01.h"

#define CS_PIN 14   // chip select pin number
#define CE_PIN 12   // chip enable pin number

NRF24L01 radio(CE_PIN, CS_PIN); // our radio instance

void setup() {

    const char address[] = "RECVR"; // this devices address
    const char rx_address[] = "TSMTR"; // device we want to read from

    Serial.begin(9600); // begin serial

    if(!radio.begin()) // try to start the radio if we cant print an error
        Serial.print("Radio Could Not Connect and/or Initialize")

    radio.setReceiveAddress(rx_address); // we want to recieve from the transmitter
    radio.setTransmitAddress(address); // we want to set our address to the reciever address

    radio.setMode(RECEIVE); // we want to receive only

}

void loop() {

    char buffer[50]; // buffer for reading
    
    while(!radio.available()); // wait for there to be something to read

    uint8_t data_size = radio.available(); // get the number of available bytes
    if(!radio.read(buffer, data_size)) // try to read the bytes into your buffer
        Serial.println("Radio Could Not Read"); // if you cant read get an error

    else {
        Serial.print("Received Data From the Radio: "); // if you can print out what was read

        for(uint8_t i = 0; i < data_size; i++) // print out the message byte by byte
            Serial.print(buffer[i]);

        Serial.println(); // throw a new line
    }

}