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

class NRF24L01 : public {

public:

    /**
     * @brief Construct a new NRF24L01 object
     * 
     * @param ce_pin 
     * @param cs_pin 
     * @param irq_pin 
     */
    NRF24L01(const int ce_pin, const int cs_pin, const int irq_pin = -1);


private:

    int irq_pin;

};




#endif