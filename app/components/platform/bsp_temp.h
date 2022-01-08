/**
* @file       bsp_temp.h
* @copyright  Copyright (C) 2021 ThuanLe. All rights reserved.
* @license    This project is released under the ThuanLe License.
* @version    01.00.00
* @date       2021-03-13
* @author     ThuanLe
* @brief      BSP Temperature
* @note       None
* @example    None
*/

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef BSP_TEMP_H
#define BSP_TEMP_H

/* Includes ----------------------------------------------------------- */
#include "bsp.h"

/* Public defines ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Bsp temperature get value
 * 
 * @param[in]     temp Temperature
 * 
 * @attention     None
 * 
 * @return        None
 */
void bsp_temp_get_value(float *temp);

#endif /* BSP_TEMP_H */

/* End of file -------------------------------------------------------- */