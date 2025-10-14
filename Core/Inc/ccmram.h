#ifndef CCMRAM_H
#define CCMRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* CCMRAM memory region definition */
#define CCMRAM_BASE         0x10000000UL
#define CCMRAM_SIZE         0x00008000UL  /* 32 KB */
#define CCMRAM_END          (CCMRAM_BASE + CCMRAM_SIZE - 1)

/* Macro to place variables in CCMRAM */
#if defined(__CC_ARM)
  #define CCMRAM_SECTION __attribute__((section(".ccmram")))
#elif defined(__GNUC__)
  #define CCMRAM_SECTION __attribute__((section(".ccmram")))
#elif defined(__ICCARM__)
  #define CCMRAM_SECTION _Pragma("location=\".ccmram\"")
#else
  #define CCMRAM_SECTION
#endif

/* Macro to place functions in CCMRAM */
#if defined(__CC_ARM)
  #define CCMRAM_FUNC __attribute__((section(".ccmram")))
#elif defined(__GNUC__)
  #define CCMRAM_FUNC __attribute__((section(".ccmram")))
#elif defined(__ICCARM__)
  #define CCMRAM_FUNC _Pragma("location=\".ccmram\"")
#else
  #define CCMRAM_FUNC
#endif

/* Function declarations */
void CCMRAM_Init(void);
uint32_t CCMRAM_GetFreeSize(void);
uint32_t CCMRAM_GetUsedSize(void);

/* Inline functions for CCMRAM access */
static inline uint32_t CCMRAM_GetBase(void) {
    return CCMRAM_BASE;
}

static inline uint32_t CCMRAM_GetSize(void) {
    return CCMRAM_SIZE;
}

static inline uint32_t CCMRAM_GetEnd(void) {
    return CCMRAM_END;
}

#ifdef __cplusplus
}
#endif

#endif /* CCMRAM_H */