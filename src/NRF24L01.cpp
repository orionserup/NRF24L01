/**
 * @file NRFL01.cpp
 * @author Orion Serup (oserup@proton.me)
 * @brief Contains the Implentation for the NRF24L01 Functionality
 * @version 0.1
 * @date 2023-01-26
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "NRF24L01.h"

NRF24L01::NRF24L01(const int ce_pin, const int cs_pin) : rf24(ce_pin, cs_pin) {}

bool NRF24L01::begin() {

    bool began = rf24.begin();

    if(began) { // if we are connected and started

        rf24.setPALevel(RF24_PA_LOW); // set the power level
        rf24.enableDynamicPayloads(); // have the packet size be determined per packet

    }

    return began;

}

void NRF24L01::setReceiveAddress(const char* const address)  {

    rf24.openReadingPipe(1, (const uint8_t*)address); // set the first reading address

}


void NRF24L01::setTransmitAddress(const char* const address)  {

    rf24.openWritingPipe((const uint8_t*)address); // set the writig address
}

bool NRF24L01::write(const void* const buffer, const uint8_t size) {

    if(mode == RECEIVE) return -1; // we need to be transmiting

    return rf24.write(buffer, size);  // write the data

}

void NRF24L01::setMode(const RadioMode mode) {

    this->mode = mode;  // set the mode
    if(mode == TRANSMIT) { 
        rf24.stopListening(); // turn off receiving
        rf24.flush_rx(); // throw away any unrecieved buffered data
    }
    else {  // if we are now receiving
        rf24.flush_tx(); // throw away buffered transmision data
        rf24.startListening(); // start receiving data
    }
}

int NRF24L01::available() {

    if(this->mode == TRANSMIT) return -1; // we cant have buffered data from receiving if we are transmitting

    return rf24.available()? rf24.getPayloadSize(): 0; // get the payload size if there is one

}

bool NRF24L01::read(void* const buffer, const uint8_t size) {

    if(this->mode == TRANSMIT) return false; // we cant read if we are transmitting
    
    rf24.read(buffer, size); // read into the buffer
    return true; // we read

}


