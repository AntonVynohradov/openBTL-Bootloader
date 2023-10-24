/************************************************************************************//**
* \file         Demo/TRICORE_TC2_TC275_Lite_Kit_ADS/Boot/App/app.c
* \brief        Bootloader application source file.
* \ingroup      Boot_TRICORE_TC2_TC275_Lite_Kit_ADS
* \internal
*----------------------------------------------------------------------------------------
*                          C O P Y R I G H T
*----------------------------------------------------------------------------------------
*   Copyright (c) 2023  by Feaser    http://www.feaser.com    All rights reserved
*
*----------------------------------------------------------------------------------------
*                            L I C E N S E
*----------------------------------------------------------------------------------------
* This file is part of OpenBLT. OpenBLT is free software: you can redistribute it and/or
* modify it under the terms of the GNU General Public License as published by the Free
* Software Foundation, either version 3 of the License, or (at your option) any later
* version.
*
* OpenBLT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
* without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
* PURPOSE. See the GNU General Public License for more details.
*
* You have received a copy of the GNU General Public License along with OpenBLT. It
* should be located in ".\Doc\license.html". If not, contact Feaser to obtain a copy.
*
* \endinternal
****************************************************************************************/

/****************************************************************************************
* Include files
****************************************************************************************/
#include "boot.h"                                /* bootloader generic header          */
#include "IfxPort.h"                             /* GPIO driver                        */
#include "IfxAsclin.h"                           /* ASCLIN basic driver                */
#include "IfxMultican.h"                         /* MultiCAN basic driver              */


/****************************************************************************************
* Function prototypes
****************************************************************************************/
static void Init(void);


/****************************************************************************************
* External data declarations
****************************************************************************************/
#if (BOOT_COM_RS232_ENABLE > 0)
extern IfxAsclin_Rx_In     * rs232RxPin;
extern IfxAsclin_Tx_Out    * rs232TxPin;
#endif
#if (BOOT_COM_CAN_ENABLE > 0)
extern IfxMultican_Rxd_In  * canRxPin;
extern IfxMultican_Txd_Out * canTxPin;
#endif


/************************************************************************************//**
** \brief     Initializes the bootloader application. Should be called once during
**            software program initialization.
** \return    none.
**
****************************************************************************************/
void AppInit(void)
{
  /* Initialize the microcontroller. */
  Init();
  /* Initialize the bootloader */
  BootInit();
} /*** end of AppInit ***/


/************************************************************************************//**
** \brief     Task function of the bootloader application. Should be called continuously
**            in the program loop.
** \return    none.
**
****************************************************************************************/
void AppTask(void)
{
  /* Run the bootloader task. */
  BootTask();
} /*** end of AppTask ***/


/************************************************************************************//**
** \brief     Initializes the microcontroller.
** \return    none.
**
****************************************************************************************/
static void Init(void)
{
  /* Configure the LED GPIO pin P00.5. */
  IfxPort_setPinModeOutput(&MODULE_P00, 5U, IfxPort_OutputMode_pushPull,
                                            IfxPort_OutputIdx_general);
  /* Configure the pushbutton GPIO pin P00.7. */
  IfxPort_setPinMode(&MODULE_P00, 7U, IfxPort_Mode_inputPullUp);
#if (BOOT_COM_RS232_ENABLE > 0)
  /* Configure ASCLIN0 GPIO pins P14.0 Tx and P14.1 Rx (node 0). */
  rs232RxPin = &IfxAsclin0_RXA_P14_1_IN;
  rs232TxPin = &IfxAsclin0_TX_P14_0_OUT;
#endif
#if (BOOT_COM_CAN_ENABLE > 0)
  /* Configure the STBY GPIO pin P20.6 as a digital output. */
  IfxPort_setPinModeOutput(&MODULE_P20, 6U, IfxPort_OutputMode_pushPull,
                                            IfxPort_OutputIdx_general);
  /* Switch the CAN transceiver to normal mode by setting the STBY GPIO pin logic low. */
  IfxPort_setPinLow(&MODULE_P20, 6U);
  /* Configure MultiCAN GPIO pins P20.8 Tx and P20.7 Rx (node 0). */
  canRxPin = &IfxMultican_RXD0B_P20_7_IN;
  canTxPin = &IfxMultican_TXD0_P20_8_OUT;
#endif
} /*** end of Init ***/


/*********************************** end of app.c **************************************/
