// nrf24_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing server
// with the RH_NRF24 class. RH_NRF24 class does not provide for addressing or
// reliability, so you should only use RH_NRF24  if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example nrf24_client
// Tested on Uno with Sparkfun NRF25L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

#include <SPI.h>
#include <RH_NRF24.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24;
// RH_NRF24 nrf24(8, 7); // use this to be electrically compatible with Mirf
// RH_NRF24 nrf24(8, 10);// For Leonardo, need explicit SS pin
// RH_NRF24 nrf24(8, 7); // For RFM73 on Anarduino Mini

uint8_t ola[5] = {0};
uint8_t oi = 0;
void setup() 
{
  Serial.begin(115200);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate1Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    

//  nrf24.spiBurstReadRegister(RH_NRF24_REG_0A_RX_ADDR_P0, ola, 5);
//  Serial.print("ADDR_P0 = ");
//  for(int index = 0; index < 5; index++)
//    Serial.print(ola[index], HEX);  

  
  
}

void loop()
{
                  Serial.println("---------------------------------------------------------------------------------------"); 
  print_registers();
  if (nrf24.available())
  { 
                  Serial.println("---------------------------------------------------------------------------------------"); 
    print_registers();
    
    // Should be a message for us now   
    uint8_t buf;
    uint8_t len = sizeof(buf);
    if (nrf24.recv(&buf, &len))
    {
//      NRF24::printBuffer("request: ", buf, len);
      Serial.print("------------------------------------------------------------------ --------------------------------got request: ");
      Serial.println(buf);
      
//      // Send a reply
//      uint8_t data[] = "And hello back to you";
//      nrf24.send(data, sizeof(data));
//      nrf24.waitPacketSent();
//      Serial.println("Sent a reply");
    }
    else
    {
      Serial.println("recv failed");
    }
    print_registers();

    
                  Serial.println("---------------------------------------------------------------------------------------"); 
  }

  

  
//  while('o' != Serial.read());
    
}


void print_registers()
{
    oi = nrf24.spiReadRegister(RH_NRF24_REG_00_CONFIG);
  Serial.print("CONFIG = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(1);
  Serial.print("EN_AA = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(2);
  Serial.print("EN_RXADDR = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(3);
  Serial.print("SETUP_AW = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(4);
  Serial.print("SETUP_RETR = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(5);
  Serial.print("RF_CH = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(6);
  Serial.print("RF_SETUP = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(7);
  Serial.print("STATUS = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(8);
  Serial.print("OBSERVE_TX = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(9);
  Serial.print("RPD = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(0x17);
  Serial.print("FIFO_STATUS = ");
  Serial.println(oi, HEX);
//
    nrf24.spiBurstReadRegister(RH_NRF24_REG_0A_RX_ADDR_P0, ola, 5);
  Serial.print("RX_ADDR_P0 = ");
  for(int index = 0; index < 5; index++)
    Serial.print(ola[index], HEX); 
  Serial.print('\n');
//  
nrf24.spiBurstReadRegister(RH_NRF24_REG_0B_RX_ADDR_P1, ola, 5);
  Serial.print("RX_ADDR_P1 = ");
  for(int index = 0; index < 5; index++)
    Serial.print(ola[index], HEX);
    Serial.print('\n'); 
    oi = nrf24.spiReadRegister(RH_NRF24_REG_0C_RX_ADDR_P2);
  Serial.print("RX_ADDR_P2 = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(RH_NRF24_REG_0D_RX_ADDR_P3);
  Serial.print("RX_ADDR_P3 = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(RH_NRF24_REG_0E_RX_ADDR_P4);
  Serial.print("RX_ADDR_P4 = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(RH_NRF24_REG_0F_RX_ADDR_P5);
  Serial.print("RX_ADDR_P5 = ");
  Serial.println(oi, HEX);
    
    nrf24.spiBurstReadRegister(RH_NRF24_REG_10_TX_ADDR, ola, 5);
  Serial.print("TX_ADDR = ");
  for(int index = 0; index < 5; index++)
    Serial.print(ola[index], HEX);
    Serial.print('\n'); 

    oi = nrf24.spiReadRegister(RH_NRF24_REG_11_RX_PW_P0);
  Serial.print("RX_PW_P0 = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(RH_NRF24_REG_12_RX_PW_P1);
  Serial.print("RX_PW_P1 = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(RH_NRF24_REG_13_RX_PW_P2);
  Serial.print("RX_PW_P2= ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(RH_NRF24_REG_14_RX_PW_P3);
  Serial.print("RX_PW_P3 = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(RH_NRF24_REG_15_RX_PW_P4);
  Serial.print("RX_PW_P4 = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(RH_NRF24_REG_16_RX_PW_P5);
  Serial.print("RX_PW_P5 = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(RH_NRF24_REG_1C_DYNPD);
  Serial.print("DYNPD = ");
  Serial.println(oi, HEX);
  oi = nrf24.spiReadRegister(RH_NRF24_REG_1D_FEATURE);
  Serial.print("FEATURE = ");
  Serial.println(oi, HEX);
  
}
