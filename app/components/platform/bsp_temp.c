/**
* @file       bsp_temp.c
* @copyright  Copyright (C) 2021 ThuanLe. All rights reserved.
* @license    This project is released under the ThuanLe License.
* @version    01.00.00
* @date       2021-03-13
* @author     ThuanLe
* @brief      BSP Temperature
* @note       None
* @example    None
*/

/* Includes ----------------------------------------------------------------- */
#include <math.h>
#include "bsp_temp.h"

/* Private defines ---------------------------------------------------------- */
#define RESISTER_1_VALUE      (10000.0)   // 10 Komh
#define VOLTAGE_INPUT_VALUE   (5000.0)    // 5 Voltage

/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
static const char *TAG = "bsp_temp";

float A = 1.009249522e-03, B = 2.378405444e-04, C = 2.019202697e-07;

/* Private function prototypes ---------------------------------------------- */
/* Function definitions ----------------------------------------------------- */
void bsp_temp_get_value(float *temp)
{
  uint16_t voltage;
  float T, logRt, Tf, Tc;

  bsp_adc_get_voltage(&voltage);

  logRt = log(RESISTER_1_VALUE * ((VOLTAGE_INPUT_VALUE / voltage - 1)));
  T = (1.0 / (A + B * logRt + C * logRt * logRt * logRt)); // We get the temperature value in Kelvin from this Stein-Hart equation
  Tc = T - 273.15;                                         // Convert Kelvin to Celsius
  Tf = (Tc * 1.8) + 32.0;                                  // Convert Kelvin to Fahrenheit

  *temp = Tc;
}

/* Private function --------------------------------------------------------- */
/* End of file -------------------------------------------------------------- */