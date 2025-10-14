#include "ccmram.h"
#include <string.h>

/* External symbols defined in linker script */
extern uint32_t _sccmram;
extern uint32_t _eccmram;
extern uint32_t _siccmram;

/* CCMRAM usage tracking */
static uint32_t ccmram_used = 0;

void CCMRAM_Init(void) {
    /* Copy initialized data from FLASH to CCMRAM */
    uint32_t *src = (uint32_t*)&_siccmram;
    uint32_t *dst = (uint32_t*)&_sccmram;
    uint32_t size = (uint32_t)((uint8_t*)&_eccmram - (uint8_t*)&_sccmram);
    
    if (size > 0) {
        memcpy(dst, src, size);
        ccmram_used = size;
    } else {
        ccmram_used = 0;
    }
    
    /* Also initialize CCMRAM variables to zero if needed */
    if (ccmram_used == 0) {
        /* If no initialized data, zero the CCMRAM section */
        memset(dst, 0, (uint32_t)((uint8_t*)&_eccmram - (uint8_t*)&_sccmram));
    }
}

uint32_t CCMRAM_GetFreeSize(void) {
    return CCMRAM_SIZE - ccmram_used;
}

uint32_t CCMRAM_GetUsedSize(void) {
    return ccmram_used;
}