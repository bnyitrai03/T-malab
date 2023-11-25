#include "Fifo.h"

void FifoInit(pFifo_t pfifo,uint8_t* pdata,uint8_t length) {

    pfifo->data = pdata; // Point to the data buffer
    pfifo->datalen = 0;  // Initially, there's no data in the buffer
    pfifo->size = length; // Set the size of the buffer
    pfifo->wptr = 0;      // Initialize write pointer to the beginning
    pfifo->rptr = 0;      // Initialize read pointer to the beginning

    if(length == 0)
        DRV_ErrorLoop();
}

uint8_t FifoPop(pFifo_t pfifo, uint8_t* pdata) {
    uint8_t next_readptr;
    uint8_t validity;

    if (pfifo->datalen == 0) {                   //if the fifo is empty we can't pop
        validity = 0;
    } else {
    	next_readptr = pfifo->rptr+1;
    	if(pfifo->size < next_readptr){   //readptr reaches the size of the buffer it goes back to the start of the buffer
    		next_readptr = 0;
    	}
        *pdata = pfifo->data[pfifo->rptr]; // Store the popped data in the memory location pdata points to
        pfifo->rptr = next_readptr;        // Move the read pointer circularly
        pfifo->datalen--;
        validity = 1;
    }
    return validity; // Return the validity status
}

uint8_t FifoPush(pFifo_t pfifo,uint8_t data) {
    uint8_t next_writeptr;
    uint8_t validity;

    if (pfifo->datalen == pfifo->size) {                   //if the fifo is full we can't push
        validity = 0;
    } else {
    	next_writeptr = pfifo->wptr+1;
    	if(pfifo->size < next_writeptr){   // writeptr reaches the size of the buffer it goes back to the start of the buffer
    		next_writeptr = 0;
    	}
    	pfifo->data[pfifo->wptr] = data;   // Push the data in the memory location pdata points to
        pfifo->wptr = next_writeptr;        // Move the write pointer circularly
        pfifo->datalen++;
        validity = 1;
    }
    return validity; // Return the validity status
}
