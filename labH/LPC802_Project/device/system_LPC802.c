/*
** ###################################################################
**     Processors:          LPC802M001JDH16
**                          LPC802M001JDH20
**                          LPC802M001JHI33
**                          LPC802M011JDH20
**                          LPC802UK
**
**     Compilers:           GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          Keil ARM C/C++ Compiler
**                          MCUXpresso Compiler
**
**     Reference manual:    LPC802 User manual Rev.1.0  1 Dec 2017
**     Version:             rev. 1.0, 2018-01-09
**     Build:               b190215
**
**     Abstract:
**         Provides a system configuration function and a global variable that
**         contains the system frequency. It configures the device and initializes
**         the oscillator (PLL) that is part of the microcontroller device.
**
**     Copyright 2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2019 NXP
**     All rights reserved.
**
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2018-01-09)
**         Initial version.
**
** ###################################################################
*/

/*!
 * @file LPC802
 * @version 1.0
 * @date 2018-01-09
 * @brief Device specific configuration file for LPC802 (implementation file)
 *
 * Provides a system configuration function and a global variable that contains
 * the system frequency. It configures the device and initializes the oscillator
 * (PLL) that is part of the microcontroller device.
 */

#include <stdint.h>
#include "fsl_device_registers.h"





/* ----------------------------------------------------------------------------
   -- Core clock
   ---------------------------------------------------------------------------- */

uint32_t SystemCoreClock = DEFAULT_SYSTEM_CLOCK;

/* ----------------------------------------------------------------------------
   -- SystemInit()
   ---------------------------------------------------------------------------- */

void SystemInit (void) {

#if defined(__MCUXPRESSO)
    extern void(*const g_pfnVectors[]) (void);
    SCB->VTOR = (uint32_t) &g_pfnVectors;
#else
    extern void *__Vectors;
    SCB->VTOR = (uint32_t) &__Vectors;
#endif
    SystemCoreClock = DEFAULT_SYSTEM_CLOCK;
  SystemInitHook();
}

/* ----------------------------------------------------------------------------
   -- SystemCoreClockUpdate()
   ---------------------------------------------------------------------------- */

void SystemCoreClockUpdate (void) {

  switch (SYSCON->MAINCLKSEL & 0x03) {
    case 0:                                       /* Free running oscillator (FRO) */
      SystemCoreClock = g_Fro_Osc_Freq;
      break;
    case 1:                                       /* System oscillator */
      SystemCoreClock = CLK_OSC_IN;
      break;
    case 2:                                       /* low power oscillator */
      SystemCoreClock = CLK_OSC_LP;
      break;
    case 3:                                       /* Free running oscillator (FRO) / 2 */
      SystemCoreClock = (g_Fro_Osc_Freq >> 1);
      break;
  }

  SystemCoreClock /= SYSCON->SYSAHBCLKDIV;
}

/* ----------------------------------------------------------------------------
   -- SystemInitHook()
   ---------------------------------------------------------------------------- */

__attribute__ ((weak)) void SystemInitHook (void) {
  /* Void implementation of the weak function. */
}
