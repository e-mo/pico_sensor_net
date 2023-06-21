#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "pico/rand.h"
#include "hardware/spi.h"

#include "rfm69.h"
#include "rudp.h"
#include "error_report.h"

#define ever ;; 

// SPI Defines
// We are going to use SPI 0, and allocate it to the following GPIO pins
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define SPI_PORT spi0
#define PIN_MISO 16
#define PIN_CS   17
#define PIN_SCK  18
#define PIN_MOSI 19
#define PIN_RST  20
#define PIN_IRQ_0  21
#define PIN_IRQ_1  21

void set_bi() {
    bi_decl(bi_program_name("Test Transmitter"));
    bi_decl(bi_program_description("WISDOM sensor network basic range test tx."))
    bi_decl(bi_1pin_with_name(PIN_MISO, "MISO"));
    bi_decl(bi_1pin_with_name(PIN_CS, "CS"));
    bi_decl(bi_1pin_with_name(PIN_SCK, "SCK"));
    bi_decl(bi_1pin_with_name(PIN_MOSI, "MOSI"));
    bi_decl(bi_1pin_with_name(PIN_RST, "RST"));
    bi_decl(bi_1pin_with_name(PIN_IRQ_0, "IRQ 0"));
    bi_decl(bi_1pin_with_name(PIN_IRQ_1, "IRQ 1"));
}

int main() {
    // Set Picotool binary info
    set_bi();
    stdio_init_all(); // To be able to use printf

    spi_init(SPI_PORT, 1000*1000); // Defaults to master mode, which we want

    Rfm69 *rfm;
    uint rval = rfm69_init(
        &rfm,
        SPI_PORT,
        PIN_MISO,
        PIN_MOSI,
        PIN_CS,
        PIN_SCK,
        PIN_RST,
        PIN_IRQ_0,
        PIN_IRQ_1
    );

    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    
    //rfm69_mode_set(rfm, RFM69_OP_MODE_SLEEP);

    // Packet mode 
    rfm69_data_mode_set(rfm, RFM69_DATA_MODE_PACKET);
    // 250kb/s baud rate
    rfm69_bitrate_set(rfm, RFM69_MODEM_BITRATE_57_6);
    // ~2 beta 
    rfm69_fdev_set(rfm, 70000);
    // 915MHz 
    rfm69_frequency_set(rfm, 915);
    //rfm69_modulation_shaping_set(rfm, RFM69_FSK_GAUSSIAN_0_3);
    // RXBW >= fdev + br/2
    rfm69_rxbw_set(rfm, RFM69_RXBW_MANTISSA_20, 2);
    rfm69_dcfree_set(rfm, RFM69_DCFREE_WHITENING);
    // Transmit starts with any data in the FIFO
    rfm69_tx_start_condition_set(rfm, RFM69_TX_FIFO_NOT_EMPTY);

    // Set sync value (essentially functions as subnet)
    uint8_t sync[3] = {0x01, 0x01, 0x01};
    rfm69_sync_value_set(rfm, sync, 3);

    rfm69_node_address_set(rfm, 0x01); 
    rfm69_broadcast_address_set(rfm, 0x86); 

    // Set to filter by node and broadcast address
    rfm69_address_filter_set(rfm, RFM69_FILTER_NODE_BROADCAST);

    // Recommended rssi thresh default setting
    rfm69_rssi_threshold_set(rfm, 0xE4);

    //rfm69_write_masked(
    //        rfm,
    //        RFM69_REG_AFC_FEI,
    //        0x08,
    //        0x08
    //);
    //rfm69_write_masked(
    //        rfm,
    //        RFM69_REG_AFC_FEI,
    //        0x04,
    //        0x04
    //);


    // Check if rfm69_init was successful (== 0)
    // Set last error and halt process if not.
    if (rval != 0) {
        set_last_error(rval); // Can use return value from rfm69_init directly
        critical_error();
    }

    //uint8_t dagc = 0x30;
    //rfm69_write(
    //        rfm,
    //        RFM69_REG_TEST_DAGC,
    //        &dagc,
    //        1 
    //);
    
    //rfm69_write_masked(
    //        rfm,
    //        RFM69_REG_AFCBW,
    //        0x03,
    //        0x07
    //);

    //// LNA input impedance 200 ohms
    rfm69_write_masked(
            rfm,
            RFM69_REG_LNA,
            0x80,
            0x80
    );

    rfm69_power_level_set(rfm, 0);
    for(ever) { 

        //uint buf_size = get_rand_32() % 6000;
        uint buf_size = TX_PACKETS_MAX * PAYLOAD_MAX;
        printf("buf_size: %u\n", buf_size);
        uint8_t buf[buf_size];
        for (int i = 0; i < buf_size; i++) {
            buf[i] = get_rand_32() % 256;
        }
        
        RUDP_RETURN rval = rfm69_rudp_transmit(
                rfm,
                0x02,
                buf,
                buf_size,
                100,
                5
        );

    
        if (rval == RUDP_OK) printf("RUDP_OK\n\n");
        else printf("RUDP_TIMOUT\n\n");

        sleep_ms(1000);
    }
    
    return 0;
}


