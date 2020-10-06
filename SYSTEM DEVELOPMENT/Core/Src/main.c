/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "SYSFN.h"


/*
 * @Brief description  main function to provoke the INIT functions (GPIO, SPI, ADC)
 * @Function- main

 * @Design by Kailash G
 *
 * @Date & Time- 5/10/2020 at 6.00pm
 *
 */


/*main Variables -----------------------------------------------*/
int main(void)
{

  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();

  ////////////////////////////////////////////////////////////FIRMWARE/////////////////////////////////////////////////////////////////////////////////
  /*
   * Interrupt START FLAG to be high as PA0 been pressed
   * Check whether the Potentiometer is >512 (thresold) under 10bit resolution at 28 samples to initiate the system
   * PIR sensor will detect the Human Motion and send 1(true) if the motion is detected and 0(false) if not detected
   * SPITX function is called to start SPI communication with Arduino UNO
   */

  while (1)
  {
	  if(START)												//EXT_Interrupt to FLAG raise (START=1)
	  {
		  HAL_Delay(100);
		  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);			//EXT_Interrupt to FLAG raise (START=1)
		  if(POT())											//Initiate Potentiometer and check whether the resistance is > 512
		  {
			  PIRsensor();
		  }
		  HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12);			//PIRsensor for Human Detection
		  START=0;											//FLAG down
	  }
  }
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	START ^= 1;
}

void Error_Handler(void)
{

}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif /* USE_FULL_ASSERT */


