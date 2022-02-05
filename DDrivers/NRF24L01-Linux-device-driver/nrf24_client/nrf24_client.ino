//#include <Timer5.h>




#include <PulseSensorPlayground.h>     // Includes the PulseSensorPlayground Library.   
#include <string.h>
#include <SPI.h>
#include <RH_NRF24.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24;

char data[64];
uint8_t count = 0;

//  Variables
const int PulseWire = 0;       // PulseSensor PURPLE WIRE connected to ANALOG PIN 0
const int LED13 = 13;          // The on-board Arduino LED, close to PIN 13.
int Threshold = 550;           // Determine which Signal to "count as a beat" and which to ignore.
                               // Use the "Gettting Started Project" to fine-tune Threshold Value beyond default setting.
                               // Otherwise leave the default "550" value. 
                               
PulseSensorPlayground pulseSensor;  // Creates an instance of the PulseSensorPlayground object called "pulseSensor"



void setup() 
{
  
  //-------------- Serial port confiuguration (testing purposes) ------------------
  Serial.begin(115200);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  
  //------------- NRF24 transceiver setup ----------------------------------------
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate1Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    

  //------------- Heart sensor setup ----------------------------------------
  pulseSensor.analogInput(PulseWire);   
  pulseSensor.setThreshold(Threshold);   
}


void loop()
{
  int myBPM = pulseSensor.getBeatsPerMinute();  // Calls function on our pulseSensor object that returns BPM as an "int".

  //Serial.println(myBPM);
  
  sprintf(data, "HeartRate %d %d\n", (uint8_t)myBPM, count);
  nrf24.send((uint8_t*)data, strlen(data));

  Serial.println(data);
  
  count++;
  delay(20);
}



/*
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
  Serial.print("RX_ADDR_P1 = ");
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
 
 
 }*/
