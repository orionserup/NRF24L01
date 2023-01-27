# NRF24L01

A Simple and Easy to Use Receiver/Sender Library for the NRF24 Series of chips for Arduino

## Authors

[Orion Serup](oserup@proton.me)

## Dependencies 

[RF24](https://github.com/nRF24/RF24) also available through the Arduino Library manager

## Getting Started

First thing is to create an instance of the NRF24L01

We need a couple of things before we can do that, first thing first is we need to connect the NRF24L01 SPI Pins (MOSI, MISO, SCK) to the Arduinos SPI pins (See the Data sheet for both of those for that information). There are two additional pins needed to operate this module CS (Chip Select) and CE (Chip Enable), connect these to any Arduino Pins and take a note of where these are connected, this will be important. 

Now we can initialize our instance, that would look like this 

```cpp
#define CS_PIN 12 
#define CE_PIN 14 
NRF24L01 radio(CE_PIN, CS_PIN);
```

Once the object is initialized we need to connect to it and make sure that everything worked in the initialization. To do that we run

```cpp
radio.begin();
```

This will verify that everything is started correctly and will allow your device to be used. It returns true or false, if it returns false you have an issue

Next step is to set the Receiving and Transmitting Address 


If we plan on being a receiver, then the transmitting address is what we want the device address to be, this is used later. The Recieving address is the address of another device that you would like to receive from.


If you plan on being a transmitter then the roles are reversed. The transmitting address is the device that you would like to transmit to and the receiving address represents the device id/address.


**Important Note:** The addresses are 5 character strings, they have to be 5 characters long. Please try to make your addresses unique otherwise you will get interference with other people's devices if you are near them and share one of these addresses.

To set these addreses we do the following, this example is for a receiver

```cpp
#define RECEIVE_ADDRESS "ADDR0"
#define DEVICE_ADDRESS "ADDR1"

radio.setReceiveAddress(RECEIVE_ADDRESS);
radio.setTransmitAddress(DEVICE_ADDRESS);
```

Next we need to set the mode, this can be changed at any time but it is important to set it now. There are two modes, TRANSMIT and RECEIVE. Once a device has its mode set it can only be one of the two, so setting the mode to TRANSMIT means the Device only transmits data. This is the case until the mode is changed. To set the mode we do the following, again I will be demoing for a receiver

```cpp
radio.setMode(RECEIVE);
```
### Sending Data

Once the Device is setup and the mode is set to transmit then we can start sending data to a receiver. To do this we call the write function, it returns true or false depending on if the data was sent successfully.

```cpp
const char payload[] = "Hello World";
radio.write(payload, 11); // write "Hello World", which is 11 bytes long not including the null terminator
```
### Receiving Data

Once the device is set up with the appropiate addresses and has been set to Receieve then we can start receiving data. This requires waiting for data to be ready to read (@ref NRF24L01::available), this is done by the available function, it returns how many bytes are available to read from a transmitter. Once we have the number of available bytes then we can read this data into a buffer using the read function (@ref NRF24L01::read). This is done as follows

```cpp
while(radio.available() < 1){} // do nothing while there is do data available

// once there is data available to read we will be here
int data_size = radio.available(); // get how many bytes are available

char buffer[50]; // buffer to read into
radio.read(buffer, data_size); // read the number of available bytes into your buffer
// now we have the received data in the buffer to do whatever we want

