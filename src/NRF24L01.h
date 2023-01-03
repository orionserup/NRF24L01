/**
 * @file NRF24L01.h
 * @author your name (you@domain.com)
 * @brief 
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
#include <Arduino.h>

class NRF24L01 : public RF24 {

public:

    /**
     * @brief Construct a new NRF24L01 object
     * 
     * @param ce_pin 
     * @param cs_pin 
     * @param irq_pin 
     */
    NRF24L01(const String address, const int ce_pin, const int cs_pin, const int irq_pin = -1);

    


private:

    /**
     * @brief 
     * 
     */
    void IRQHandler();

    int irq_pin;
    uint8_t buffer[64];
    uint8_t buffer_index;

};




#endif