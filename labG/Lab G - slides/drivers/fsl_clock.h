/*
 * Copyright 2017-2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_CLOCK_H_
#define _FSL_CLOCK_H_

#include "fsl_common.h"

/*! @addtogroup clock */
/*! @{ */

/*! @file */

/*******************************************************************************
 * Definitions
 *****************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief CLOCK driver version 2.1.0. */
#define FSL_CLOCK_DRIVER_VERSION (MAKE_VERSION(2, 1, 0))
/*@}*/

/* Definition for delay API in clock driver, users can redefine it to the real application. */
#ifndef SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY
#define SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY (30000000UL)
#endif

/*! @brief watchdog oscilltor clock frequency.
 *
 * This variable is used to store the watchdog oscillator frequency which is
 * set by CLOCK_InitWdtOsc, and it is returned by CLOCK_GetWdtOscFreq.
 */
extern volatile uint32_t g_Wdt_Osc_Freq;

/*! @brief external clock frequency.
 *
 * This variable is used to store the external clock frequency which is include
 * external oscillator clock and external clk in clock frequency value, it is
 * set by CLOCK_InitExtClkin when CLK IN is used as external clock or by CLOCK_InitSysOsc
 * when external oscillator is used as external clock ,and it is returned by
 * CLOCK_GetExtClkFreq.
 */
extern volatile uint32_t g_Ext_Clk_Freq;

/*! @brief FRO clock setting API address in ROM. */
#define CLOCK_FRO_SETTING_API_ROM_ADDRESS (0x0F001CD3U)
/*! @brief FAIM base address*/
#define CLOCK_FAIM_BASE (0x50010000U)

/*! @brief Clock ip name array for ADC. */
#define ADC_CLOCKS  \
    {               \
        kCLOCK_Adc, \
    }
/*! @brief Clock ip name array for ACMP. */
#define ACMP_CLOCKS  \
    {                \
        kCLOCK_Acmp, \
    }
/*! @brief Clock ip name array for DAC. */
#define DAC_CLOCKS                \
    {                             \
        kCLOCK_Dac0, kCLOCK_Dac1, \
    }
/*! @brief Clock ip name array for SWM. */
#define SWM_CLOCKS  \
    {               \
        kCLOCK_Swm, \
    }
/*! @brief Clock ip name array for ROM. */
#define ROM_CLOCKS  \
    {               \
        kCLOCK_Rom, \
    }
/*! @brief Clock ip name array for SRAM. */
#define SRAM_CLOCKS    \
    {                  \
        kCLOCK_Ram0_1, \
    }
/*! @brief Clock ip name array for IOCON. */
#define IOCON_CLOCKS  \
    {                 \
        kCLOCK_Iocon, \
    }
/*! @brief Clock ip name array for GPIO. */
#define GPIO_CLOCKS   \
    {                 \
        kCLOCK_Gpio0, \
    }
/*! @brief Clock ip name array for GPIO_INT. */
#define GPIO_INT_CLOCKS \
    {                   \
        kCLOCK_GpioInt, \
    }
/*! @brief Clock ip name array for DMA. */
#define DMA_CLOCKS  \
    {               \
        kCLOCK_Dma, \
    }
/*! @brief Clock ip name array for CRC. */
#define CRC_CLOCKS  \
    {               \
        kCLOCK_Crc, \
    }
/*! @brief Clock ip name array for WWDT. */
#define WWDT_CLOCKS  \
    {                \
        kCLOCK_Wwdt, \
    }
/*! @brief Clock ip name array for SCT0. */
#define SCT_CLOCKS  \
    {               \
        kCLOCK_Sct, \
    }
/*! @brief Clock ip name array for I2C. */
#define I2C_CLOCKS   \
    {                \
        kCLOCK_I2c0, \
    }
/*! @brief Clock ip name array for I2C. */
#define USART_CLOCKS                \
    {                               \
        kCLOCK_Uart0, kCLOCK_Uart1, \
    }
/*! @brief Clock ip name array for SPI. */
#define SPI_CLOCKS   \
    {                \
        kCLOCK_Spi0, \
    }
/*! @brief Clock ip name array for CAPT. */
#define CAPT_CLOCKS  \
    {                \
        kCLOCK_Capt, \
    }
/*! @brief Clock ip name array for CTIMER. */
#define CTIMER_CLOCKS   \
    {                   \
        kCLOCK_Ctimer0, \
    }
/*! @brief Clock ip name array for MTB. */
#define MTB_CLOCKS  \
    {               \
        kCLOCK_Mtb, \
    }
/*! @brief Clock ip name array for MRT. */
#define MRT_CLOCKS  \
    {               \
        kCLOCK_Mrt, \
    }
/*! @brief Clock ip name array for WKT. */
#define WKT_CLOCKS  \
    {               \
        kCLOCK_Wkt, \
    }

/*! @brief Internal used Clock definition only. */
#define CLK_GATE_DEFINE(reg, bit) ((((reg)&0xFFU) << 8U) | ((bit)&0xFFU))
#define CLK_GATE_GET_REG(x) (((x) >> 8U) & 0xFFU)
#define CLK_GATE_GET_BITS_SHIFT(x) ((uint32_t)(x)&0xFFU)
/* clock mux register definition */
#define CLK_MUX_DEFINE(reg, mux) (((((uint32_t)(&((SYSCON_Type *)0U)->reg)) & 0xFFU) << 8U) | ((mux)&0xFFU))
#define CLK_MUX_GET_REG(x) ((volatile uint32_t *)(((uint32_t)(SYSCON)) + (((x) >> 8U) & 0xFFU)))
#define CLK_MUX_GET_MUX(x) ((x)&0xFFU)
#define CLK_MAIN_CLK_MUX_DEFINE(preMux, mux) ((preMux) << 8U | (mux))
#define CLK_MAIN_CLK_MUX_GET_PRE_MUX(x) (((x) >> 8U) & 0xFFU)
#define CLK_MAIN_CLK_MUX_GET_MUX(x) ((x)&0xFFU)
/* clock divider register definition */
#define CLK_DIV_DEFINE(reg) (((uint32_t)(&((SYSCON_Type *)0U)->reg)) & 0xFFFU)
#define CLK_DIV_GET_REG(x) *((volatile uint32_t *)(((uint32_t)(SYSCON)) + ((x)&0xFFFU)))
/* watch dog oscillator definition */
#define CLK_WDT_OSC_DEFINE(freq, regValue) (((freq)&0xFFFFFFU) | (((regValue)&0xFFU) << 24U))
#define CLK_WDT_OSC_GET_FREQ(x) ((x)&0xFFFFFFU)
#define CLK_WDT_OSC_GET_REG(x) (((x) >> 24U) & 0xFFU)
/* Fractional clock register map */
#define CLK_FRG_DIV_REG_MAP(base) (*(base))
#define CLK_FRG_MUL_REG_MAP(base) (*((uint32_t *)((uint32_t)(base) + 4U)))
#define CLK_FRG_SEL_REG_MAP(base) (*((uint32_t *)((uint32_t)(base) + 8U)))
/* register offset */
#define SYS_AHB_CLK_CTRL0 (0U)
/*! @brief Clock gate name used for CLOCK_EnableClock/CLOCK_DisableClock. */
typedef enum _clock_ip_name
{
    kCLOCK_IpInvalid = 0U,
    kCLOCK_Rom       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 1U),
    kCLOCK_Ram0      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 2U),
    kCLOCK_Flash     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 4U),
    kCLOCK_I2c0      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 5U),
    kCLOCK_Gpio0     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 6U),
    kCLOCK_Swm       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 7U),
    kCLOCK_Wkt       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 9U),
    kCLOCK_Mrt       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 10U),
    kCLOCK_Spi0      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 11U),
    kCLOCK_Crc       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 13U),
    kCLOCK_Uart0     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 14U),
    kCLOCK_Uart1     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 15U),
    kCLOCK_Wwdt      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 17U),
    kCLOCK_Iocon     = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 18U),
    kCLOCK_Acmp      = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 19U),
    kCLOCK_Adc       = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 24U),
    kCLOCK_Ctimer0   = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 25U),
    kCLOCK_GpioInt   = CLK_GATE_DEFINE(SYS_AHB_CLK_CTRL0, 28U),

} clock_ip_name_t;

/*! @brief Clock name used to get clock frequency. */
typedef enum _clock_name
{
    kCLOCK_CoreSysClk, /*!< Cpu/AHB/AHB matrix/Memories,etc */
    kCLOCK_MainClk,    /*!< Main clock */

    kCLOCK_Fro,    /*!< FRO18/24/30 */
    kCLOCK_FroDiv, /*!< FRO div clock */
    kCLOCK_ExtClk, /*!< External Clock */
    kCLOCK_LPOsc,  /*!< Low power Oscillator */
    kCLOCK_Frg,    /*!< fractional rate0 */
} clock_name_t;

/*! @brief Clock Mux Switches
 *CLK_MUX_DEFINE(reg, mux)
 *reg is used to define the mux register
 *mux is used to define the mux value
 *
 */
typedef enum _clock_select
{

    kADC_Clk_From_Fro   = CLK_MUX_DEFINE(ADCCLKSEL, 0U),
    kADC_Clk_From_ClkIn = CLK_MUX_DEFINE(ADCCLKSEL, 1U),

    kUART0_Clk_From_Fro     = CLK_MUX_DEFINE(UART0CLKSEL, 0U),
    kUART0_Clk_From_MainClk = CLK_MUX_DEFINE(UART0CLKSEL, 1U),
    kUART0_Clk_From_Frg0Clk = CLK_MUX_DEFINE(UART0CLKSEL, 2U),
    kUART0_Clk_From_Fro_Div = CLK_MUX_DEFINE(UART0CLKSEL, 4U),

    kUART1_Clk_From_Fro     = CLK_MUX_DEFINE(UART1CLKSEL, 0U),
    kUART1_Clk_From_MainClk = CLK_MUX_DEFINE(UART1CLKSEL, 1U),
    kUART1_Clk_From_Frg0Clk = CLK_MUX_DEFINE(UART1CLKSEL, 2U),
    kUART1_Clk_From_Fro_Div = CLK_MUX_DEFINE(UART1CLKSEL, 4U),

    kI2C_Clk_From_Fro     = CLK_MUX_DEFINE(I2C0CLKSEL, 0U),
    kI2C_Clk_From_MainClk = CLK_MUX_DEFINE(I2C0CLKSEL, 1U),
    kI2C_Clk_From_Frg0Clk = CLK_MUX_DEFINE(I2C0CLKSEL, 2U),
    kI2C_Clk_From_Fro_Div = CLK_MUX_DEFINE(I2C0CLKSEL, 4U),

    kSPI_Clk_From_Fro     = CLK_MUX_DEFINE(SPI0CLKSEL, 0U),
    kSPI_Clk_From_MainClk = CLK_MUX_DEFINE(SPI0CLKSEL, 1U),
    kSPI_Clk_From_Frg0Clk = CLK_MUX_DEFINE(SPI0CLKSEL, 2U),
    kSPI_Clk_From_Fro_Div = CLK_MUX_DEFINE(SPI0CLKSEL, 4U),

    kFRG0_Clk_From_Fro     = CLK_MUX_DEFINE(FRG->FRGCLKSEL, 0U),
    kFRG0_Clk_From_MainClk = CLK_MUX_DEFINE(FRG->FRGCLKSEL, 1U),

    kCLKOUT_From_Fro     = CLK_MUX_DEFINE(CLKOUTSEL, 0U),
    kCLKOUT_From_MainClk = CLK_MUX_DEFINE(CLKOUTSEL, 1U),
    kCLKOUT_From_ExtClk  = CLK_MUX_DEFINE(CLKOUTSEL, 3U),
    kCLKOUT_From_WdtOsc  = CLK_MUX_DEFINE(CLKOUTSEL, 4U)
} clock_select_t;

/*! @brief Clock divider
 */
typedef enum _clock_divider
{
    kCLOCK_DivAdcClk = CLK_DIV_DEFINE(ADCCLKDIV),
    kCLOCK_DivClkOut = CLK_DIV_DEFINE(CLKOUTDIV)
} clock_divider_t;

/*! @brief fro output frequency source definition */
typedef enum _clock_fro_src
{
    kCLOCK_FroSrcLpwrBootValue = 0U, /*!< fro source from the fro oscillator divided by low power boot value */
    //    kCLOCK_FroSrcFroOsc        = 1U << SYSCON_FROOSCCTRL_DIRECT_SHIFT,          /*!< fre source from the fro
    //    oscillator directly  */
} clock_fro_src_t;

/*! @brief fro oscillator output frequency value definition */
typedef enum _clock_fro_osc_freq
{
    kCLOCK_FroOscOut18M = 18000U, /*!< FRO oscillator output 18M */
    kCLOCK_FroOscOut24M = 24000U, /*!< FRO oscillator output 24M */
    kCLOCK_FroOscOut30M = 30000U, /*!< FRO oscillator output 30M */
} clock_fro_osc_freq_t;

/*!< Main clock source definition */
typedef enum _clock_main_clk_src
{
    kCLOCK_MainClkSrcFro    = CLK_MAIN_CLK_MUX_DEFINE(0U, 0U), /*!< main clock source from FRO */
    kCLOCK_MainClkSrcExtClk = CLK_MAIN_CLK_MUX_DEFINE(1U, 0U), /*!< main clock source from Ext clock */
    kCLOCK_MainClkSrcLPOsc  = CLK_MAIN_CLK_MUX_DEFINE(2U, 0U), /*!< main clock source from watchdog oscillator */
    kCLOCK_MainClkSrcFroDiv = CLK_MAIN_CLK_MUX_DEFINE(3U, 0U), /*!< main clock source from FRO Div */
} clock_main_clk_src_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name Clock gate, mux, and divider.
 * @{
 */

/*
 *! @brief enable ip clock.
 *
 * @param clk clock ip definition.
 */
static inline void CLOCK_EnableClock(clock_ip_name_t clk)
{
    SYSCON->SYSAHBCLKCTRL0 |= 1 << CLK_GATE_GET_BITS_SHIFT(clk);
}

/*
 *!@brief disable ip clock.
 *
 * @param clk clock ip definition.
 */
static inline void CLOCK_DisableClock(clock_ip_name_t clk)
{
    SYSCON->SYSAHBCLKCTRL0 &= ~(1 << CLK_GATE_GET_BITS_SHIFT(clk));
}

/*
 *! @brief	Configure the clock selection muxes.
 * @param	mux	: Clock to be configured.
 * @return	Nothing
 */
static inline void CLOCK_Select(clock_select_t sel)
{
    *(CLK_MUX_GET_REG(sel)) = CLK_MUX_GET_MUX(sel);
}

/*
 *! @brief	Setup peripheral clock dividers.
 * @param	name	: Clock divider name
 * @param   value: Value to be divided
 * @return	Nothing
 */
static inline void CLOCK_SetClkDivider(clock_divider_t name, uint32_t value)
{
    CLK_DIV_GET_REG(name) = value & 0xFFU;
}

/*
 *! @brief  Get peripheral clock dividers.
 * @param   name    : Clock divider name
 * @return  clock divider value
 */
static inline uint32_t CLOCK_GetClkDivider(clock_divider_t name)
{
    return CLK_DIV_GET_REG(name) & 0xFFU;
}

/*
 *! @brief   Setup Core clock dividers.
 * Be careful about the core divider value, due to core/system frequency should be lower than 30MHZ.
 * @param   value: Value to be divided
 * @return  Nothing
 */
static inline void CLOCK_SetCoreSysClkDiv(uint32_t value)
{
    assert(value != 0U);

    SYSCON->SYSAHBCLKDIV = (SYSCON->SYSAHBCLKDIV & (~SYSCON_SYSAHBCLKDIV_DIV_MASK)) | SYSCON_SYSAHBCLKDIV_DIV(value);
}

/*! @brief  Set main clock reference source.
 * @param src, reference clock_main_clk_src_t to set the main clock source.
 */
void CLOCK_SetMainClkSrc(clock_main_clk_src_t src);

/*
 *! @brief	Set Fractional generator multiplier value.
 * @param   base: Fractional generator register address
 * @param	mul	: FRG multiplier value.
 * @return	Nothing
 */
static inline void CLOCK_SetFRGClkMul(uint32_t *base, uint32_t mul)
{
    CLK_FRG_DIV_REG_MAP(base) = SYSCON_FRG_FRGDIV_DIV_MASK;
    CLK_FRG_MUL_REG_MAP(base) = SYSCON_FRG_FRGMULT_MULT(mul);
}
/* @} */

/*!
 * @name Get frequency
 * @{
 */

/*! @brief  Return Frequency of FRG0 Clock.
 *  @return Frequency of FRG0 Clock.
 */
uint32_t CLOCK_GetFRGClkFreq(void);

/*! @brief  Return Frequency of Main Clock.
 *  @return Frequency of Main Clock.
 */
uint32_t CLOCK_GetMainClkFreq(void);

/*! @brief  Return Frequency of FRO.
 *  @return Frequency of FRO.
 */
uint32_t CLOCK_GetFroFreq(void);

/*! @brief  Return Frequency of core.
 *  @return Frequency of core.
 */
static inline uint32_t CLOCK_GetCoreSysClkFreq(void)
{
    return CLOCK_GetMainClkFreq() / (SYSCON->SYSAHBCLKDIV & 0xffU);
}

/*! @brief  Return Frequency of ClockOut
 *  @return Frequency of ClockOut
 */
uint32_t CLOCK_GetClockOutClkFreq(void);

/*! @brief  Get UART0 frequency
 * @retval UART0 frequency value.
 */
uint32_t CLOCK_GetUart0ClkFreq(void);

/*! @brief  Get UART1 frequency
 * @retval UART1 frequency value.
 */
uint32_t CLOCK_GetUart1ClkFreq(void);

/*! @brief	Return Frequency of selected clock
 *  @return	Frequency of selected clock
 */
uint32_t CLOCK_GetFreq(clock_name_t clockName);

/*! @brief  Return System PLL input clock rate
 *  @return System PLL input clock rate
 */
uint32_t CLOCK_GetSystemPLLInClockRate(void);

/*! @brief  Get watch dog OSC frequency
 * @retval watch dog OSC frequency value.
 */
static inline uint32_t CLOCK_GetLPOscFreq(void)
{
    return 1000000;
}

/*! @brief  Get external clock frequency
 * @retval external clock frequency value.
 */
static inline uint32_t CLOCK_GetExtClkFreq(void)
{
    return g_Ext_Clk_Freq;
}
/* @} */

/* @} */

/*!
 * @name Fractional clock operations
 * @{
 */

/*! @brief Set FRG0 output frequency.
 * @param freq, target output frequency,freq < input and (input / freq) < 2 should be satisfy.
 * @retval true - successfully, false - input argument is invalid.
 *
 */
bool CLOCK_SetFRGClkFreq(uint32_t freq);

/* @} */

/*!
 * @name External/internal oscillator clock operations
 * @{
 */

/*! @brief  Init external CLK IN, select the CLKIN as the external clock source.
 * @param clkInFreq external clock in frequency.
 */
void CLOCK_InitExtClkin(uint32_t clkInFreq);

/*! @brief  Deinit watch dog OSC
 * @param config oscillator configuration.
 */
static inline void CLOCK_DeinitLPOsc(void)
{
    SYSCON->PDRUNCFG |= SYSCON_PDRUNCFG_LPOSC_PD_MASK;
}

/*! @brief Set FRO oscillator output frequency.
 *  Initialize the FRO clock to given frequency (18, 24 or 30 MHz).
 * @param freq, please reference clock_fro_osc_freq_t definition, frequency must be one of 18000, 24000 or 30000 KHz.
 *
 */
void CLOCK_SetFroOscFreq(clock_fro_osc_freq_t freq);

/*!
 * @brief Delay at least for several microseconds.
 *  Please note that, this API will calculate the microsecond period with the maximum
 *  supported CPU frequency, so this API will only delay for at least the given microseconds, if precise
 *  delay count was needed, please implement a new timer count to achieve this function.
 *
 * @param delay_us  Delay time in unit of microsecond.
 */
void SDK_DelayAtLeastUs(uint32_t delay_us);

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_CLOCK_H_ */
