#include "nrf24l01_hw.h"
#include "hal.h"

void nrf_init(void)
{
  palSetPad(GPIOD, GPIOD_PIN11);

  /*
   * Low speed SPI configuration (140.625kHz, CPHA=0, CPOL=0, MSb first).
   */
  static const SPIConfig ls_spicfg = {
    NULL,
    GPIOD,
    10,
    SPI_CR1_BR_0 | SPI_CR1_BR_1,
    //SPI_CR2_DS_2 | SPI_CR2_DS_1 | SPI_CR2_DS_0
  };
  spiStart(&SPID2, &ls_spicfg);       /* Setup transfer parameters.       */


}

void nrf_spi_csh(void)
{
  spiUnselect(&SPID2);                  /* Slave Select assertion.          */
}

void nrf_spi_csl(void)
{
  spiSelect(&SPID2);                /* Slave Select de-assertion.       */
}

unsigned char nrf_spi_xfer_byte(unsigned char data)
{
  static uint8_t txbuf[1];
  static uint8_t rxbuf[1];
  txbuf[0]=data;
  spiExchange(&SPID2,1,txbuf, rxbuf); /* Atomic transfer operations.      */
  return rxbuf[0];
}

