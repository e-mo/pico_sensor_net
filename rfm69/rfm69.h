// rfm69hcw.h
// This library contains register definitions and a set of baseline functions for communicating
// with the RFM69HCW transceiver module (though it should work with any of the RFM69 modules)
// specifically for working with the RaspberryPi Pico C/C++ SDK.
//
// Evan Morse
// e.morse8686@gmail.com
#ifndef RFM69_DRIVER_H
#define RFM69_DRIVER_H

#include <stdio.h> // for testing. remove later

#include "pico/stdlib.h"
#include "hardware/spi.h"

#define RFM69_REG_FIFO            0x00 // FIFO read/write access

#define RFM69_REG_OP_MODE         0x01 // Operating modes of the transceiver

#define RFM69_REG_DATA_MODUL      0x02 // Data operation mode and Modulation settings

#define RFM69_REG_BITRATE_MSB     0x03 // Bit Rate setting, Most Significant Bits
#define RFN69_REG_BITRATE_LSB     0x04 // Bit Rate setting, Least Significant Bits

#define RFM69_REG_FDEV_MSB        0x05 // Frequency Deviation setting, Most Significant Bits
#define RFM69_REG_FDEV_LSB        0x06 // Frequency Deviation setting, Least Significant Bits

#define RFM69_REG_FRF_MSB         0x07 // RF Carrier Frequency, Most Significant Bits
#define RFM69_REG_FRF_MID         0x08 // RF Carrier Frequency, Intermediate Bits
#define RFM69_REG_FRF_LSB         0x09 // RF Carrier Frequency, Least Significant Bits

#define RFM69_REG_OSC_1           0x0A // RC Oscillators Settings

#define RFM69_REG_AFC_CTRL        0x0B // AFC control in low modulation index situations

#define RFM69_REG_LISTEN_1        0x0D // Listen Mode settings
#define RFM69_REG_LISTEN_2        0x0E // Listen Mode Idle duration
#define RFM69_REG_LISTEN_3        0x0F // Listen Mode Rx duration

#define RFM69_REG_VERSION         0x10 // Version

#define RFM69_REG_PA_LEVEL        0x11 // PA selection and Output Power control
#define RFM69_REG_PA_RAMP         0x12 // Control of the PA ramp time in FSK mode

#define RFM69_REG_OCP             0x13 // Over Current Protection control

#define RFM69_REG_LNA             0x18 // LNA settings

#define RFM69_REG_RX_BW           0x19 // Channel Filter BW Control
#define RFM69_REG_AFC_BW          0x1A // Channel Filter BW control during the AFC routine

#define RFM69_REG_OOK_PEAK        0x1B // OOK demodulator selection and control in peak mode
#define RFM69_REG_OOK_AVG         0x1C // Average threshold control of the OOK demodulator
#define RFM69_REG_OOK_FIX         0x1D // Fixed threshold control of the OOK demodulato

#define RFM69_REG_AFC_FEI         0x1E // AFC and FEI control and status
#define RFM69_REG_AFC_MSB         0x1F // MSB of the frequency correction of the AFC
#define RFM69_REG_AFC_LSB         0x20 // LSB of the frequency correction of the AFC

#define RFM69_REG_FEI_MSB         0x21 // MSB of the calculated frequency error
#define RFM69_REG_FEI_LSB         0x22 // LSB of the calculated frequency error

#define RFM69_REG_RSSI_CONFIG     0x23 // RSSI-related settings
#define RFM69_REG_RSSI_VALUE      0x24 // RSSI value in dBm

#define RFM69_REG_DIO_MAPPING_1   0x25 // Mapping of pins DIO0 to DIO3
#define RFM69_REG_DIO_MAPPING_2   0x26 // Mapping of pins DIO4 and DIO5, ClkOut frequency

#define RFM69_REG_IRQ_FLAGS_1     0x27 // Status register: PLL Lock state, Timeout, RSSI > Threshold...
#define RFM69_REG_IRQ_FLAGS_2     0x28 // Status register: FIFO handling flags...

#define RFM69_REG_RSSI_THRESH     0x29 // RSSI Threshold control

#define RFM69_REG_RX_TIMEOUT_1    0x2A // Timeout duration between Rx request and RSSI detection
#define RFM69_REG_RX_TIMEOUT_2    0x2B // Timeout duration between RSSI detection and PayloadReady
#define RFM69_REG_PREAMBLE_MSB    0x2C // Preamble length, MSB
#define RFM69_REG_PREAMBLE_LSB    0x2D // Preamble length, LSB

#define RFM69_REG_SYNC_CONFIG     0x2E // Sync Word Recognition control
#define RFM69_REG_SYNC_VALUE_1    0x2F // Sync Word bytes, 1 through 8
#define RFM69_REG_SYNC_VALUE_2    0x30 
#define RFM69_REG_SYNC_VALUE_3    0x31 
#define RFM69_REG_SYNC_VALUE_4    0x32 
#define RFM69_REG_SYNC_VALUE_5    0x33 
#define RFM69_REG_SYNC_VALUE_6    0x34 
#define RFM69_REG_SYNC_VALUE_7    0x35 
#define RFM69_REG_SYNC_VALUE_8    0x36 

#define RFM69_REG_PACKET_CONFIG_1 0x37 // Packet mode settings

#define RFM69_REG_PAYLOAD_LENGTH  0x38 // Payload length setting

#define RFM69_REG_NODE_ADRS       0x39 // Node address
#define RFM69_REG_BROADCAST_ADRS  0x3A // Broadcast address

#define RFM69_REG_AUTO_MODES      0x3B // Auto modes settings

#define RFM69_REG_FIFO_THRESH     0x3C // Fifo threshold, Tx start condition

#define RFM69_REG_PACKET_CONFIG_2 0x3D // Packet mode settings

#define RFM69_REG_AES_KEY_1       0x3E // 16 bytes of the cypher key
#define RFM69_REG_AES_KEY_2       0x3F
#define RFM69_REG_AES_KEY_3       0x40
#define RFM69_REG_AES_KEY_4       0x41
#define RFM69_REG_AES_KEY_5       0x42
#define RFM69_REG_AES_KEY_6       0x43
#define RFM69_REG_AES_KEY_7       0x44
#define RFM69_REG_AES_KEY_8       0x45
#define RFM69_REG_AES_KEY_9       0x46
#define RFM69_REG_AES_KEY_10      0x47
#define RFM69_REG_AES_KEY_11      0x48
#define RFM69_REG_AES_KEY_12      0x49
#define RFM69_REG_AES_KEY_13      0x4A
#define RFM69_REG_AES_KEY_14      0x4B
#define RFM69_REG_AES_KEY_15      0x4C
#define RFM69_REG_AES_KEY_16      0x4D

#define RFM69_REG_TEMP_1          0x4E // Temperature Sensor control
#define RFM69_REG_TEMP_2          0x4F // Temperature readout

#define RFM69_REG_TEST_LNA        0x58 // Sensitivity boost
#define RFM69_REG_TEST_PA_1       0x5A // High Power PA settings
#define RFM69_REG_TEST_PA_2       0x5C // High Power PA settings
#define RFM69_REG_TEST_DAGC       0x6F // Fading Margin Improvement
#define RFM69_REG_TEST_AFC        0x71 // AFC offset for low modulation index AFC

#define RFM69_FIFO_SIZE             66 // The FIFO size is fixed to 66 bytes 
#define RFM69_FSTEP                 61

// Incomplete type representing Rfm69 radio module.
typedef struct Rfm69 Rfm69;

typedef enum _ERR_CODE {
    RFM69_NO_ERROR,
    RFM69_INIT_MALLOC,
    RFM69_INIT_TEST,
} RFM69_ERR_CODE;

#define _OP_MODE_OFFSET 2
typedef enum _OP_MODE {
    RFM69_OP_MODE_SLEEP,
    RFM69_OP_MODE_STDBY = 0x01 << _OP_MODE_OFFSET,
    RFM69_OP_MODE_FS    = 0x02 << _OP_MODE_OFFSET,
    RFM69_OP_MODE_TX    = 0x03 << _OP_MODE_OFFSET,
    RFM69_OP_MODE_RX    = 0x04 << _OP_MODE_OFFSET,
    RFM69_OP_MODE_MASK  = 0x07 << _OP_MODE_OFFSET
} RFM69_OP_MODE;

#define _DATA_MODE_OFFSET 5
typedef enum _DATA_MODE {
    RFM69_DATA_MODE_PACKET,
    RFM69_DATA_MODE_CONTINUOUS_BIT_SYNC = 0x02 << _DATA_MODE_OFFSET,
    RFM69_DATA_MODE_CONTINUOUS          = 0x03 << _DATA_MODE_OFFSET,
    RFM69_DATA_MODE_MASK                = 0x60
} RFM69_DATA_MODE;

#define _MODULATION_TYPE_OFFSET 3
typedef enum _MODULATION_TYPE {
    RFM69_MODULATION_FSK,
    RFM69_MODULATION_OOK       = 0x01 << _MODULATION_TYPE_OFFSET,
    RFM69_MODULATION_TYPE_MASK = 0x18
} RFM69_MODULATION_TYPE;

#define _MODULATION_SHAPING_OFFSET 0
typedef enum _MODULATION_SHAPING {
    RFM69_NO_SHAPING,
    RFM69_FSK_GAUSSIAN_1_0 = 0x01, RFM69_OOK_FCUTOFF_BR   = 0x01,
    RFM69_FSK_GAUSSIAN_0_5 = 0x02, RFM69_OOK_FCUTOFF_2XBR = 0x02,
    RFM69_FSK_GAUSSIAN_0_3 = 0x03,
    RFM69_MODULATION_SHAPING_MASK = 0x03
} RFM69_MODULATION_SHAPING;

typedef enum _MODEM_BITRATE {
// Classic modem baud rates (multiples of 1.2 kbps)
    RFM69_MODEM_BITRATE_1_2   = 0x682B, // 1.2 kbps
    RFM69_MODEM_BITRATE_2_4   = 0x3415, // 2.4 kbps
    RFM69_MODEM_BITRATE_4_8   = 0x1A0B, // 4.8 kbps
    RFM69_MODEM_BITRATE_9_6   = 0x0D05, // 9.6 kbps
    RFM69_MODEM_BITRATE_19_2  = 0x0683, // 19.2 kbps
    RFM69_MODEM_BITRATE_38_4  = 0x0341, // 38.4 kbps
    RFM69_MODEM_BITRATE_76_8  = 0x01A1, // 76.8 kbps
    RFM69_MODEM_BITRATE_153_6 = 0x00D0, // 153.6 kbps

// Classic modem baud rates (multiples of 0.9 kbps)
    RFM69_MODEM_BITRATE_57_6  = 0x022C, // 57.6 kbps
    RFM69_MODEM_BITRATE_115_2 = 0x0116, // 115.2 kbps

// Round bit rates (multiples of 12.5, 25, and 50 kbps)
    RFM69_MODEM_BITRATE_12_5  = 0x0A00, // 12.5 kbps
    RFM69_MODEM_BITRATE_25    = 0x0500, // 25 kbps
    RFM69_MODEM_BITRATE_50    = 0x0280, // 50 kbps
    RFM69_MODEM_BITRATE_100   = 0x0140, // 100 kbps
    RFM69_MODEM_BITRATE_150   = 0x00D5, // 150 kbps
    RFM69_MODEM_BITRATE_200   = 0x00A0, // 200 kbps
    RFM69_MODEM_BITRATE_250   = 0x0080, // 250 kbps
    RFM69_MODEM_BITRATE_300   = 0x006B, // 300 kbps

    RFM69_MODEM_BITRATE_WATCH_XTAL = 0x03D1, // 32.768 kbps
} RFM69_MODEM_BITRATE;

typdef enum _IRQ_FLAG {
    RFM69_IRQ_FLAG_SYNC_ADDRESS_MATCH,
    RFM69_IRQ_FLAG_,
} RFM69_IRQ_FLAG;

typedef enum _IRQ1_FLAG {
    RFM69_IRQ1_FLAG_SYNC_ADDRESS_MATCH  = 0x01,
    RFM69_IRQ1_FLAG_AUTO_MODE           = 0x02,
    RFM69_IRQ1_FLAG_TIMEOUT             = 0x04,
    RFM69_IRQ1_FLAG_RSSI                = 0x08,
    RFM69_IRQ1_FLAG_PLL_LOCK            = 0x10,
    RFM69_IRQ1_FLAG_TX_READY            = 0x20,
    RFM69_IRQ1_FLAG_RX_READY            = 0x40,
    RFM69_IRQ1_FLAG_MODE_READY          = 0x80
} RFM69_IRQ1_FLAG;

typedef enum _IRQ_2_FLAG {
    RFM69_IRQ2_FLAG_CRC_OK              = 0x02,
    RFM69_IRQ2_FLAG_PAYLOAD_READY       = 0x04,
    RFM69_IRQ2_FLAG_PACKET_SENT         = 0x08,
    RFM69_IRQ2_FLAG_FIFO_OVERRUN        = 0x10,
    RFM69_IRQ2_FLAG_FIFO_LEVEL          = 0x20,
    RFM69_IRQ2_FLAG_FIFO_NOT_EMPTY      = 0x40,
    RFM69_IRQ2_FLAG_FIFO_FULL           = 0x80
} RFM69_IRQ2_FLAG;

// Initializes passed in Rfm69 pointer and sets pins to proper
// mode for spi communication. Passed pins must match the passed in
// spi instane (e.g. spi0 pins for spi0 instance).
//
// This function assumes spi_inst_t *spi has already been inistialized. 
// This function returns heap allocated memory. Since this kind of
// module typically stays active for the lifetime of the process, I
// see no reason to provide an rfm69 specific free function.
// If freeing the memory is necessary, a simple call to standard free
// will suffice.
RFM69_ERR_CODE rfm69_init(
    Rfm69 **rfm,
    spi_inst_t *spi,
    uint pin_miso,
    uint pin_mosi,
    uint pin_cs,
    uint pin_sck,
    uint pin_rst,
    uint pin_irq_0,
    uint pin_irq_1
);



// Resets the module by setting the reset pin for 100ms
// and then waiting an additional 5ms after clearing as per the
// RFM69HCW datasheet: https://cdn.sparkfun.com/datasheets/Wireless/General/RFM69HCW-V1.1.pdf
void rfm69_reset(Rfm69 *rfm);

// Writes <len> bytes from <src> to RFM69 registers/FIFO over SPI.
// SPI instance must be initialized before calling.
// If src len > 1, address will be incremented between each byte (burst write).
//
// rfm     - initialized Rfm69 *
// address - uint8_t buffer/FIFO address.
// src     - an array of uint8_t to be written.
// len     - src array length.
// Returns number of bytes written (not including address byte).
int rfm69_write(Rfm69 *rfm, 
                uint8_t address, 
                const uint8_t *src, 
                size_t len);

int rfm69_write_masked(
        Rfm69 *rfm, 
        uint8_t address, 
        const uint8_t src,
        const uint8_t mask);

// Reads <len> bytes into <dst> from RFM69 registers/FIFO over SPI.
// SPI instance must be initialized before calling.
// If src len > 1, address will be incremented between each byte (burst write).
//
// rfm     - initialized Rfm69 *
// address - uint8_t buffer/FIFO address.
// dst     - an array of uint8_t to be read into.
// len     - dst array length.
// Returns number of bytes written (not including address byte).
int rfm69_read(Rfm69 *rfm, 
               uint8_t address, 
               uint8_t *dst, 
               size_t len);

int rfm69_read_masked(
        Rfm69 *rfm,
        uint8_t address,
        uint8_t *dst,
        const uint8_t mask);

// Reads state of IRQ flags. Each function corresponds with one
// of the flag registers.
// flag    - IRQ flag constant you want to check.
// state   - stores flag state.
//
// Returns number of bytes written. 
int rfm69_irq1_flag_state(Rfm69 *rfm, RFM69_IRQ1_FLAG flag, bool *state);
int rfm69_irq2_flag_state(Rfm69 *rfm, RFM69_IRQ2_FLAG flag, bool *state);

// Sets the opterating frequency of the module.
// frequency - desired frequency in MHz.
//
// Returns number of bytes written. 
int rfm69_frequency_set(Rfm69 *rfm,
                        uint frequency);

// Reads operating frequency from module.
// Note - might not reflect set freqency until a mode change.
// frequency - stores frequency in Hz.
//
// Returns number of bytes written. 
int rfm69_frequency_get(Rfm69 *rfm, uint32_t *frequency);

// Sets modem bitrate.
int rfm69_bitrate_set(Rfm69 *rfm,
                      RFM69_MODEM_BITRATE bit_rate);

// Reads modem bitrate.
int rfm69_bitrate_get(Rfm69 *rfm, uint16_t *bit_rate);


int rfm69_rssi_get(Rfm69 *rfm, int8_t *rssi);
int rfm69_rssi_trig(Rfm69 *rfm);

// Sets module into a new mode.
// Blocks until mode is ready.
int rfm69_mode_set(Rfm69 *rfm, RFM69_OP_MODE mode);

// Gets current mode.
int rfm69_mode_get(Rfm69 *rfm, uint8_t *mode);

// Checks if current mode is ready.
int rfm69_mode_ready(Rfm69 *rfm, bool *ready);

// Blocks until mode ready IRQ flag is set. 
int rfm69_mode_wait_until_ready(Rfm69 *rfm);

int rfm69_data_mode_set(Rfm69 *rfm, RFM69_DATA_MODE mode);
int rfm69_data_mode_get(Rfm69 *rfm, uint8_t *mode);

int rfm69_modulation_type_set(Rfm69 *rfm, RFM69_MODULATION_TYPE type);
int rfm69_modulation_type_get(Rfm69 *rfm, uint8_t *type);

int rfm69_modulation_shaping_set(Rfm69 *rfm, RFM69_MODULATION_SHAPING shaping);
int rfm69_modulation_shaping_get(Rfm69 *rfm, uint8_t *shaping);

#endif // RFM69_DRIVER_H
