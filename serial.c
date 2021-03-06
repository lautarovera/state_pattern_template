/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "header.h"

/* Read and Write pointers of a circular buffer */
uint8  *rx_read_ptr = rx_buffer;
uint8  *rx_write_ptr = rx_buffer;

/* ISR that feeds the circular buffer with new serial inputs */
CY_ISR(isr_rx)
{
    while(UART_RF_ReadRxStatus() & UART_RF_RX_STS_FIFO_NOTEMPTY)
	{
        *rx_write_ptr++ = UART_RF_ReadRxData();
        
        if(rx_write_ptr >= rx_buffer + 32) rx_write_ptr = rx_buffer;
    }
    
    INT_RX_ClearPending();
}

/* Method that verifies if is a new char in the circular buffer */
static uint8 is_buffer_ready(Serial *this)
{
    return this-> ch_rdy = !(rx_write_ptr == rx_read_ptr);
}

/* Method that reads the circular buffer until an EOM is reached */
static uint8 read_buffer(Serial *this, char eom)
{
    this->str_rdy = 0;
    this->ch = *rx_read_ptr++;
    
    if(rx_read_ptr >= rx_buffer + 32) rx_read_ptr = rx_buffer;
    if(this->ch == eom)
    {
        *(this->rx_str_ptr) = 0;
        this->rx_str_ptr = this->rx_str;
        
        if(strlen(this->rx_str) > 0) this->str_rdy = 1;  
    }
    else *(this->rx_str_ptr++) = this->ch;     
 
    return this->str_rdy;  
}

/* Private constructor of the object */
static void construct(Serial *this)
{
    this->rx_str_ptr = this->rx_str;
    this->ch = 0;
    this->ch_rdy = 0;
    this->str_rdy = 0;
    this->is_buffer_ready = &is_buffer_ready;
    this->read_buffer = &read_buffer;
}

/* Public constructor that calls the private constructor */
void serial_construct(Serial *this)
{
    this->construct = &construct;
    this->construct(this);
}

/* [] END OF FILE */
