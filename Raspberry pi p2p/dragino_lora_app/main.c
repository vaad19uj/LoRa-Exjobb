/*******************************************************************************
 *
 * Copyright (c) 2018 Dragino
 *
 * http://www.dragino.com
 *
 *******************************************************************************/

#include <string>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/time.h>
#include <signal.h>
#include <stdlib.h>

#include <sys/ioctl.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>


// #############################################
// #############################################

#define REG_FIFO                    0x00
#define REG_OPMODE                  0x01
#define REG_FIFO_ADDR_PTR           0x0D
#define REG_FIFO_TX_BASE_AD         0x0E
#define REG_FIFO_RX_BASE_AD         0x0F
#define REG_RX_NB_BYTES             0x13
#define REG_FIFO_RX_CURRENT_ADDR    0x10
#define REG_IRQ_FLAGS               0x12
#define REG_DIO_MAPPING_1           0x40
#define REG_DIO_MAPPING_2           0x41
#define REG_MODEM_CONFIG            0x1D
#define REG_MODEM_CONFIG2           0x1E
#define REG_MODEM_CONFIG3           0x26
#define REG_SYMB_TIMEOUT_LSB  		0x1F
#define REG_PKT_SNR_VALUE			0x19
#define REG_PAYLOAD_LENGTH          0x22
#define REG_IRQ_FLAGS_MASK          0x11
#define REG_MAX_PAYLOAD_LENGTH 		0x23
#define REG_HOP_PERIOD              0x24
#define REG_SYNC_WORD				0x39
#define REG_VERSION	  				0x42
#define REG_DETECTION_OPTIMIZE		0x31
#define REG_DETECTION_THRESHOLD		0x37

#define PAYLOAD_LENGTH              0x40

// LOW NOISE AMPLIFIER
#define REG_LNA                     0x0C
#define LNA_MAX_GAIN                0x23
#define LNA_OFF_GAIN                0x00
#define LNA_LOW_GAIN		    	0x20

#define RegDioMapping1                             0x40 // common
#define RegDioMapping2                             0x41 // common

#define RegPaConfig                                0x09 // common
#define RegPaRamp                                  0x0A // common
#define RegPaDac                                   0x5A // common

#define SX72_MC2_FSK                0x00
#define SX72_MC2_SF7                0x70
#define SX72_MC2_SF8                0x80
#define SX72_MC2_SF9                0x90
#define SX72_MC2_SF10               0xA0
#define SX72_MC2_SF11               0xB0
#define SX72_MC2_SF12               0xC0

#define SX72_MC1_LOW_DATA_RATE_OPTIMIZE  0x01 // mandated for SF11 and SF12

// sx1276 RegModemConfig1
#define SX1276_MC1_BW_125                0x70
#define SX1276_MC1_BW_250                0x80
#define SX1276_MC1_BW_500                0x90
#define SX1276_MC1_CR_4_5            0x02
#define SX1276_MC1_CR_4_6            0x04
#define SX1276_MC1_CR_4_7            0x06
#define SX1276_MC1_CR_4_8            0x08

#define SX1276_MC1_IMPLICIT_HEADER_MODE_ON    0x01

// sx1276 RegModemConfig2
#define SX1276_MC2_RX_PAYLOAD_CRCON        0x04

// sx1276 RegModemConfig3
#define SX1276_MC3_LOW_DATA_RATE_OPTIMIZE  0x08
#define SX1276_MC3_AGCAUTO                 0x04

// preamble for lora networks (nibbles swapped)
#define LORA_MAC_PREAMBLE                  0x34

#define RXLORA_RXMODE_RSSI_REG_MODEM_CONFIG1 0x0A
#ifdef LMIC_SX1276
#define RXLORA_RXMODE_RSSI_REG_MODEM_CONFIG2 0x70
#elif LMIC_SX1272
#define RXLORA_RXMODE_RSSI_REG_MODEM_CONFIG2 0x74
#endif

// FRF
#define        REG_FRF_MSB              0x06
#define        REG_FRF_MID              0x07
#define        REG_FRF_LSB              0x08

#define        FRF_MSB                  0xD9 // 868.1 Mhz
#define        FRF_MID                  0x06
#define        FRF_LSB                  0x66

// ----------------------------------------
// Constants for radio registers
#define OPMODE_LORA      0x80
#define OPMODE_MASK      0x07
#define OPMODE_SLEEP     0x00
#define OPMODE_STANDBY   0x01
#define OPMODE_FSTX      0x02
#define OPMODE_TX        0x03
#define OPMODE_FSRX      0x04
#define OPMODE_RX        0x05
#define OPMODE_RX_SINGLE 0x06
#define OPMODE_CAD       0x07

// ----------------------------------------
// Bits masking the corresponding IRQs from the radio
#define IRQ_LORA_RXTOUT_MASK 0x80
#define IRQ_LORA_RXDONE_MASK 0x40
#define IRQ_LORA_CRCERR_MASK 0x20
#define IRQ_LORA_HEADER_MASK 0x10
#define IRQ_LORA_TXDONE_MASK 0x08
#define IRQ_LORA_CDDONE_MASK 0x04
#define IRQ_LORA_FHSSCH_MASK 0x02
#define IRQ_LORA_CDDETD_MASK 0x01

// DIO function mappings                D0D1D2D3
#define MAP_DIO0_LORA_RXDONE   0x00  // 00------
#define MAP_DIO0_LORA_TXDONE   0x40  // 01------
#define MAP_DIO1_LORA_RXTOUT   0x00  // --00----
#define MAP_DIO1_LORA_NOP      0x30  // --11----
#define MAP_DIO2_LORA_NOP      0xC0  // ----11--

// #############################################
// #############################################
//
typedef bool boolean;
typedef unsigned char byte;

static const int CHANNEL = 0;

char message[256];

byte receivedbytes;

enum sf_t { SF6=6, SF7, SF8, SF9, SF10, SF11, SF12 };
enum dataRate_t {DR0=0, DR1, DR2};

/*******************************************************************************
 *
 * Configure these values!
 *
 *******************************************************************************/

// SX1272 - Raspberry connections
int ssPin = 6;
int dio0  = 7;
int RST   = 0;

// Set spreading factor (SF7 - SF12)
sf_t sf_init = SF7;

// Set center frequency
uint32_t  freq = 868100000; // in Mhz! (868.1)

// Required Number of messages received
int reqNbrReceived = 10;

// Number of messages received
int nbrReceived = 10;

// Set starting dataRate
int dataRate = 0;

byte hello[32] = "HELLO";

void die(const char *s)
{
    perror(s);
    exit(1);
}

void selectreceiver()
{
    digitalWrite(ssPin, LOW);
}

void unselectreceiver()
{
    digitalWrite(ssPin, HIGH);
}

byte readReg(byte addr)
{
    unsigned char spibuf[2];

    selectreceiver();
    spibuf[0] = addr & 0x7F;
    spibuf[1] = 0x00;
    wiringPiSPIDataRW(CHANNEL, spibuf, 2);
    unselectreceiver();

    return spibuf[1];
}

void writeReg(byte addr, byte value)
{
    unsigned char spibuf[2];

    spibuf[0] = addr | 0x80;
    spibuf[1] = value;
    selectreceiver();
    wiringPiSPIDataRW(CHANNEL, spibuf, 2);

    unselectreceiver();
}

static void opmode (uint8_t mode) {
    writeReg(REG_OPMODE, (readReg(REG_OPMODE) & ~OPMODE_MASK) | mode);
}

static void opmodeLora() {
    uint8_t u = OPMODE_LORA;
	u |= 0x8;   // TBD: sx1276 high freq
    writeReg(REG_OPMODE, u);
}


void SetupLoRa()
{
    
    digitalWrite(RST, HIGH);
    delay(100);
    digitalWrite(RST, LOW);
    delay(100);

    byte version = readReg(REG_VERSION);

	// sx1276?
	digitalWrite(RST, LOW);
	delay(100);
	digitalWrite(RST, HIGH);
	delay(100);
	version = readReg(REG_VERSION);
	if (version == 0x12) {
		// sx1276
		printf("SX1276 detected, starting.\n");
	} else {
		printf("Unrecognized transceiver.\n");
		//printf("Version: 0x%x\n",version);
		exit(1);
	}

    opmode(OPMODE_SLEEP);

    // set frequency
    uint64_t frf = ((uint64_t)freq << 19) / 32000000;
    writeReg(REG_FRF_MSB, (uint8_t)(frf>>16) );
    writeReg(REG_FRF_MID, (uint8_t)(frf>> 8) );
    writeReg(REG_FRF_LSB, (uint8_t)(frf>> 0) );

    writeReg(REG_SYNC_WORD, 0x34); // LoRaWAN public sync word

	if (sf_init == SF11 || sf_init == SF12) {
		writeReg(REG_MODEM_CONFIG3,0x0C);
	} else {
		writeReg(REG_MODEM_CONFIG3,0x04);
	}
	writeReg(REG_MODEM_CONFIG,0x72);
	writeReg(REG_MODEM_CONFIG2,(sf_init<<4) | 0x04);

    if (sf_init == SF10 || sf_init == SF11 || sf_init == SF12) {
        writeReg(REG_SYMB_TIMEOUT_LSB,0x05);
    } else {
        writeReg(REG_SYMB_TIMEOUT_LSB,0x08);
    }
    writeReg(REG_MAX_PAYLOAD_LENGTH,0x80);
    writeReg(REG_PAYLOAD_LENGTH,PAYLOAD_LENGTH);
    writeReg(REG_HOP_PERIOD,0xFF);
    writeReg(REG_FIFO_ADDR_PTR, readReg(REG_FIFO_RX_BASE_AD));

    writeReg(REG_LNA, LNA_MAX_GAIN);

}

int getSpreadingFactor() {
	return readReg(REG_MODEM_CONFIG2) >> 4;
}

long getBandwidth() {
	byte bw = readReg(REG_MODEM_CONFIG) >> 4;
	switch(bw) {
		case 7: return 125E3;
		case 8: return 250E3;
		case 9: return 500E3;
	}
	return -1;
}

int getCodingRateDenominator() {
	int cr = (readReg(REG_MODEM_CONFIG) >> 1) & 0x07;
	int denominator = cr + 4;
	return denominator;
}

void setLdoFlag(){
	
	// Section 4.1.1.5
	long symbolDuration = 1000 / (getBandwidth() / (1L << getSpreadingFactor()));
	
	// Section 4.1.1.6
	uint8_t config3 = readReg(REG_MODEM_CONFIG3);
	if(symbolDuration > 16) {
		// set LowDataRateOptimize
		config3 |= 1UL << 3;
	} else {
		//clear LowDataRateOptimize
		config3 &= ~(1UL << 3);
	}
	writeReg(REG_MODEM_CONFIG3, config3);
}	

void setSpreadingFactor(int sf) {
	if (sf < 6) {
    sf = 6;
  } else if (sf > 12) {
    sf = 12;
  }
	if(sf == 6) {
		writeReg(REG_DETECTION_OPTIMIZE, 0xc5);
		writeReg(REG_DETECTION_THRESHOLD, 0x0c);
	} else {
		writeReg(REG_DETECTION_OPTIMIZE, 0x0c);
		writeReg(REG_DETECTION_THRESHOLD, 0x0a);
	}
  
  writeReg(REG_MODEM_CONFIG2, (readReg(REG_MODEM_CONFIG2) & 0x0f) | ((sf << 4) & 0xf0));
  setLdoFlag(); 
}

void setBandwidth(long sbw){
	int bw;
	
	if(sbw <= 125E3) {
		bw = 7;
	} else if(sbw <= 250E3) {
		bw = 8;
	} else {
		bw = 9;
	}
	
	writeReg(REG_MODEM_CONFIG, (readReg(REG_MODEM_CONFIG) & 0x0f) | ((bw << 4) & 0xf0));
	setLdoFlag();
}

void setCodingRate4(int denominator) {
	if(denominator < 5) {
		denominator = 5;
	} else if(denominator > 8) {
		denominator = 8;
	}
	
	int cr = denominator - 4;
	writeReg(REG_MODEM_CONFIG, (readReg(REG_MODEM_CONFIG) & 0xf1) | ((cr << 1) & 0x0e));
}

boolean receive(char *payload) {
    // clear rxDone
    writeReg(REG_IRQ_FLAGS, 0x40);

    int irqflags = readReg(REG_IRQ_FLAGS);

    //  payload crc: 0x20
    if((irqflags & 0x20) == 0x20)
    {
        printf("CRC error\n");
        writeReg(REG_IRQ_FLAGS, 0x20);
        return false;
    } else {

        byte currentAddr = readReg(REG_FIFO_RX_CURRENT_ADDR);
        byte receivedCount = readReg(REG_RX_NB_BYTES);
        receivedbytes = receivedCount;

        writeReg(REG_FIFO_ADDR_PTR, currentAddr);

        for(int i = 0; i < receivedCount; i++)
        {
            payload[i] = (char)readReg(REG_FIFO);
        }
    }
    return true;
}

void receivepacket() {

    long int SNR;
    int rssicorr;

    if(digitalRead(dio0) == 1)
    {
        if(receive(message)) {
			nbrReceived += 1;
            byte value = readReg(REG_PKT_SNR_VALUE);
            if( value & 0x80 ) // The SNR sign bit is 1
            {
                // Invert and divide by 4
                value = ( ( ~value + 1 ) & 0xFF ) >> 2;
                SNR = -value;
            }
            else
            {
                // Divide by 4
                SNR = ( value & 0xFF ) >> 2;
            }
			rssicorr = 157;

            printf("Packet RSSI: %d, ", readReg(0x1A)-rssicorr);
            printf("RSSI: %d, ", readReg(0x1B)-rssicorr);
            printf("SNR: %li, ", SNR);
            printf("Length: %i", (int)receivedbytes);
            printf("\n");
            printf("Payload: %s\n", message);
        } // received a message

    } // dio0=1
}

static void configPower (int8_t pw) {
        // no boost used for now
        if(pw >= 17) {
            pw = 15;
        } else if(pw < 2) {
            pw = 2;
        }
        // check board type for BOOST pin
        writeReg(RegPaConfig, (uint8_t)(0x80|(pw&0xf)));
        writeReg(RegPaDac, readReg(RegPaDac)|0x4);
}


static void writeBuf(byte addr, byte *value, byte len) {                                                       
    unsigned char spibuf[256];                                                                          
    spibuf[0] = addr | 0x80;                                                                            
    for (int i = 0; i < len; i++) {                                                                         
        spibuf[i + 1] = value[i];                                                                       
    }                                                                                                   
    selectreceiver();                                                                                   
    wiringPiSPIDataRW(CHANNEL, spibuf, len + 1);                                                        
    unselectreceiver();                                                                                 
}

void txlora(byte *frame, byte datalen) {

    // set the IRQ mapping DIO0=TxDone DIO1=NOP DIO2=NOP
    writeReg(RegDioMapping1, MAP_DIO0_LORA_TXDONE|MAP_DIO1_LORA_NOP|MAP_DIO2_LORA_NOP);
    // clear all radio IRQ flags
    writeReg(REG_IRQ_FLAGS, 0xFF);
    // mask all IRQs but TxDone
    writeReg(REG_IRQ_FLAGS_MASK, ~IRQ_LORA_TXDONE_MASK);

    // initialize the payload size and address pointers
    writeReg(REG_FIFO_TX_BASE_AD, 0x00);
    writeReg(REG_FIFO_ADDR_PTR, 0x00);
    writeReg(REG_PAYLOAD_LENGTH, datalen);

    // download buffer to the radio FIFO
    writeBuf(REG_FIFO, frame, datalen);
    // now we actually start the transmission
    opmode(OPMODE_TX);

    printf("send: %s\n", frame);
}

int main (int argc, char *argv[]) {

    wiringPiSetup () ;
    pinMode(ssPin, OUTPUT);
    pinMode(dio0, INPUT);
    pinMode(RST, OUTPUT);

    wiringPiSPISetup(CHANNEL, 500000);

    SetupLoRa();

        // radio init
        opmodeLora();
        opmode(OPMODE_STANDBY);
        opmode(OPMODE_RX);
        printf("Listening at SF%i on %.6lf Mhz.\n", sf_init,(double)freq/1000000);
        printf("------------------\n");
		int testActive = 1;
		
        while(testActive == 1) {
			if(nbrReceived == reqNbrReceived) {
				printf("if case?");
				switch (dataRate) 
				{
					case DR0:
						// Config
						setSpreadingFactor(12);
						setBandwidth(125E3);
						setCodingRate4(7);
						break;
										
					case DR1:
						// Config
						setSpreadingFactor(8);
						setBandwidth(250E3);
						setCodingRate4(8);
						break;
						
					case DR2:
						// Config
						setSpreadingFactor(7);
						setBandwidth(500E3);
						setCodingRate4(5);
						break;	
										
					default:
						// Close program
						printf("Finished.");
						testActive = 0;
						break;
				}
				if(testActive == 1) {
					printf("sf = %i, bw = %ld, cr = %i.", getSpreadingFactor(), getBandwidth(), getCodingRateDenominator());
					
					dataRate  += 1;
					nbrReceived = 0;
					
					printf("Waiting 10 seconds...");
					delay(10000);
				}
			}
			receivepacket(); 
			delay(1);
		}	
    return (0);
}
