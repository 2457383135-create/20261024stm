/******************************************************************************
 * @file     cmsis_gcc.h
 * @brief    CMSIS compiler GCC header file (GCC 14 compatible)
 ******************************************************************************/

#ifndef __CMSIS_GCC_H
#define __CMSIS_GCC_H

/* ============================================================================
 * CMSIS compiler specific defines
 * ============================================================================ */
#ifndef   __ASM
  #define __ASM                                  __asm
#endif
#ifndef   __INLINE
  #define __INLINE                               inline
#endif
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static inline
#endif
#ifndef   __STATIC_FORCEINLINE
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif
#ifndef   __NO_RETURN
  #define __NO_RETURN                            __attribute__((__noreturn__))
#endif
#ifndef   __USED
  #define __USED                                 __attribute__((used))
#endif
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                        struct __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_UNION
  #define __PACKED_UNION                         union __attribute__((packed, aligned(1)))
#endif
#ifndef   __UNALIGNED_UINT32        /* deprecated */
  struct __attribute__((packed)) T_UINT32 { uint32_t v; };
  #define __UNALIGNED_UINT32(x)                  (((struct T_UINT32 *)(x))->v)
#endif
#ifndef   __UNALIGNED_UINT16_WRITE
  __PACKED_STRUCT T_UINT16_WRITE { uint16_t v; };
  #define __UNALIGNED_UINT16_WRITE(addr, val)    (void)((((struct T_UINT16_WRITE *)(void*)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT16_READ
  __PACKED_STRUCT T_UINT16_READ { uint16_t v; };
  #define __UNALIGNED_UINT16_READ(addr)          (((const struct T_UINT16_READ *)(const void *)(addr))->v)
#endif
#ifndef   __UNALIGNED_UINT32_WRITE
  __PACKED_STRUCT T_UINT32_WRITE { uint32_t v; };
  #define __UNALIGNED_UINT32_WRITE(addr, val)    (void)((((struct T_UINT32_WRITE *)(void*)(addr))->v) = (val))
#endif
#ifndef   __UNALIGNED_UINT32_READ
  __PACKED_STRUCT T_UINT32_READ { uint32_t v; };
  #define __UNALIGNED_UINT32_READ(addr)          (((const struct T_UINT32_READ *)(const void *)(addr))->v)
#endif
#ifndef   __ALIGNED
  #define __ALIGNED(x)                           __attribute__((aligned(x)))
#endif
#ifndef   __RESTRICT
  #define __RESTRICT                             __restrict
#endif

/* ============================================================================
 * Core Instruction Access
 * ============================================================================ */

/** No Operation */
__STATIC_FORCEINLINE void __NOP(void)
{
  __ASM volatile ("nop");
}

/** Wait For Interrupt */
__STATIC_FORCEINLINE void __WFI(void)
{
  __ASM volatile ("wfi");
}

/** Wait For Event */
__STATIC_FORCEINLINE void __WFE(void)
{
  __ASM volatile ("wfe");
}

/** Send Event */
__STATIC_FORCEINLINE void __SEV(void)
{
  __ASM volatile ("sev");
}

/** Instruction Synchronization Barrier */
__STATIC_FORCEINLINE void __ISB(void)
{
  __ASM volatile ("isb" ::: "memory");
}

/** Data Synchronization Barrier */
__STATIC_FORCEINLINE void __DSB(void)
{
  __ASM volatile ("dsb" ::: "memory");
}

/** Data Memory Barrier */
__STATIC_FORCEINLINE void __DMB(void)
{
  __ASM volatile ("dmb" ::: "memory");
}

/** Reverse byte order (32 bit) */
__STATIC_FORCEINLINE uint32_t __REV(uint32_t value)
{
  return __builtin_bswap32(value);
}

/** Reverse byte order (16 bit) */
__STATIC_FORCEINLINE uint32_t __REV16(uint32_t value)
{
  return __builtin_bswap16((uint16_t)value);
}

/** Reverse byte order in signed short value */
__STATIC_FORCEINLINE int32_t __REVSH(int32_t value)
{
  return (int32_t)__builtin_bswap16((uint16_t)value);
}

/** Rotate Right */
__STATIC_FORCEINLINE uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U) { return op1; }
  return (op1 >> op2) | (op1 << (32U - op2));
}

/** Breakpoint */
__STATIC_FORCEINLINE void __BKPT(uint32_t value)
{
  __ASM volatile ("bkpt %0" : : "i"(value));
}

/** Count Leading Zeros */
__STATIC_FORCEINLINE uint32_t __CLZ(uint32_t value)
{
  return __builtin_clz(value);
}

/** Reverse Bits */
__STATIC_FORCEINLINE uint32_t __RBIT(uint32_t value)
{
  uint32_t result;
  __ASM volatile ("rbit %0, %1" : "=r"(result) : "r"(value));
  return result;
}

/* ============================================================================
 * Core Function Access
 * ============================================================================ */

/** Enable IRQ Interrupts */
__STATIC_FORCEINLINE void __enable_irq(void)
{
  __ASM volatile ("cpsie i" : : : "memory");
}

/** Disable IRQ Interrupts */
__STATIC_FORCEINLINE void __disable_irq(void)
{
  __ASM volatile ("cpsid i" : : : "memory");
}

/** Get Control Register */
__STATIC_FORCEINLINE uint32_t __get_CONTROL(void)
{
  uint32_t result;
  __ASM volatile ("mrs %0, control" : "=r"(result));
  return(result);
}

/** Set Control Register */
__STATIC_FORCEINLINE void __set_CONTROL(uint32_t control)
{
  __ASM volatile ("msr control, %0" : : "r"(control));
}

/** Get IPSR Register */
__STATIC_FORCEINLINE uint32_t __get_IPSR(void)
{
  uint32_t result;
  __ASM volatile ("mrs %0, ipsr" : "=r"(result));
  return(result);
}

/** Get APSR Register */
__STATIC_FORCEINLINE uint32_t __get_APSR(void)
{
  uint32_t result;
  __ASM volatile ("mrs %0, apsr" : "=r"(result));
  return(result);
}

/** Get xPSR Register */
__STATIC_FORCEINLINE uint32_t __get_xPSR(void)
{
  uint32_t result;
  __ASM volatile ("mrs %0, xpsr" : "=r"(result));
  return(result);
}

/** Get Process Stack Pointer */
__STATIC_FORCEINLINE uint32_t __get_PSP(void)
{
  uint32_t result;
  __ASM volatile ("mrs %0, psp" : "=r"(result));
  return(result);
}

/** Set Process Stack Pointer */
__STATIC_FORCEINLINE void __set_PSP(uint32_t topOfProcStack)
{
  __ASM volatile ("msr psp, %0" : : "r"(topOfProcStack));
}

/** Get Main Stack Pointer */
__STATIC_FORCEINLINE uint32_t __get_MSP(void)
{
  uint32_t result;
  __ASM volatile ("mrs %0, msp" : "=r"(result));
  return(result);
}

/** Set Main Stack Pointer */
__STATIC_FORCEINLINE void __set_MSP(uint32_t topOfMainStack)
{
  __ASM volatile ("msr msp, %0" : : "r"(topOfMainStack));
}

/** Get Priority Mask */
__STATIC_FORCEINLINE uint32_t __get_PRIMASK(void)
{
  uint32_t result;
  __ASM volatile ("mrs %0, primask" : "=r"(result));
  return(result);
}

/** Set Priority Mask */
__STATIC_FORCEINLINE void __set_PRIMASK(uint32_t priMask)
{
  __ASM volatile ("msr primask, %0" : : "r"(priMask));
}

/** Enable FIQ */
__STATIC_FORCEINLINE void __enable_fault_irq(void)
{
  __ASM volatile ("cpsie f" : : : "memory");
}

/** Disable FIQ */
__STATIC_FORCEINLINE void __disable_fault_irq(void)
{
  __ASM volatile ("cpsid f" : : : "memory");
}

/** Get FIQ Mask */
__STATIC_FORCEINLINE uint32_t __get_FAULTMASK(void)
{
  uint32_t result;
  __ASM volatile ("mrs %0, faultmask" : "=r"(result));
  return(result);
}

/** Set FIQ Mask */
__STATIC_FORCEINLINE void __set_FAULTMASK(uint32_t faultMask)
{
  __ASM volatile ("msr faultmask, %0" : : "r"(faultMask));
}

#if defined (__FPU_PRESENT) && (__FPU_PRESENT == 1U)
/** Enable FPU */
__STATIC_FORCEINLINE void __FPU_Enable(void)
{
  __ASM volatile (
    "ldr.w r0, =0xE000ED88\n"
    "ldr r1, [r0]\n"
    "orr r1, r1, #0x00F00000\n"
    "str r1, [r0]\n"
    "dsb\n"
    "isb\n"
    : : : "r0", "r1"
  );
}
#endif

/* ============================================================================
 * ARMv6-M / ARMv7-M exclusive access functions (used by HAL UART/DMA)
 * ============================================================================ */

/** Load Register Exclusive Word */
__STATIC_FORCEINLINE uint32_t __LDREXW(volatile uint32_t *ptr)
{
  uint32_t result;
  __ASM volatile ("ldrex %0, [%1]" : "=r"(result) : "r"(ptr));
  return result;
}



/** Store Register Exclusive Word */
__STATIC_FORCEINLINE uint32_t __STREXW(uint32_t value, volatile uint32_t *ptr)
{
  uint32_t result;
  __ASM volatile ("strex %0, %2, [%1]" : "=r"(result) : "r"(ptr), "r"(value));
  return result;
}



#endif /* __CMSIS_GCC_H */