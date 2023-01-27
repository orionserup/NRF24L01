/**
 * @file NRF24L01.h
 * @author Orion Serup (oserup@proton.me)
 * @brief Contains the Declarations and definitions for the NRF24L01 library
 * @version 0.1
 * @date 2023-01-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once 

#ifndef NRFL01_H
#define NRFL01_H

#include "RF24.h"

/// @brief Radio Mode, if we are a transmitter or receiver
enum RadioMode {

    RECEIVE,    // we are recieveing data
    TRANSMIT    // we are transmitting data

};

/// @brief Class Representing the NRF module
class NRF24L01 {

public:

    /**
     * @brief Construct a new NRF24L01 object
     * 
     * @param ce_pin: Chip Enable Pin Number 
     * @param cs_pin: Chip Select Pin Number 
     */
    NRF24L01(const int ce_pin, const int cs_pin);

    /**
     * @brief Starts the Radio 
     * 
     * @return true: If the Radio Started correctly 
     * @return false: If the Radio failed to start
     */
    bool begin();

    /**
     * @brief Set the Recieving Address
     * 
     * In Receive Mode this is the address of the transmitter that we want to receive from
     * In Transmit Mode this is the Address of the device we are sending from 
     * 
     * @param address: 5 character address, only 5 characters
     */
    void setReceiveAddress(const char* address);

    /**
     * @brief Set the Transmit Address
     *  
     * In Transmit Mode this corresponds to the address that we want to write to with our transmissions
     * In Receive mode this corresponds to the device's address
     * 
     * @param address: 5 character address, only 5 characters
     */
    void setTransmitAddress(const char* address);

    /**
     * @brief Sets the Mode of the Radio
     * 
     * @param mode: Either "RECEIVE" or "TRANSMIT" see @ref RadioMode
     */
    void setMode(const RadioMode mode);

    /**
     * @brief Reads how many bytes are available in the buffers for recieving
     * @note Needs to be in Receiving mode for this to work
     * @return int: Number of bytes available to read, -1 if we are transmitting
     */
    int available();

    /**
     * @brief Sends data targetting the Reciever with the addreess matching the Transmit Address
     * @note: Needs to be in Transmit mode for this to work
     * @param buffer: data buffer to send, a pointer to any type
     * @param size: How many bytes to send
     * @return bool: If the buffer was sent
     */
    bool write(const void* const buffer, const uint8_t size);

    /**
     * @brief Reads data from a Transmitter
     * @note Needs to be in Receive Mode to work
     * @param buffer: Buffer to read into
     * @param size: How many bytes to read [1 - 255]
     * @returns true if data was read, false if not
     */
    bool read(void* const buffer, const uint8_t size);


private:

    RF24 rf24; // inner manager component, does the actual heavy lifting
    RadioMode mode; // what mode we are in

};

#endif