/**
* @file       bsp.c
* @copyright  Copyright (C) 2021 ThuanLe. All rights reserved.
* @license    This project is released under the ThuanLe License.
* @version    01.00.00
* @date       2021-03-13
* @author     ThuanLe
* @brief      BSP (Board Support Package)
* @note       None
* @example    None
*/

/* Includes ----------------------------------------------------------------- */
#include "bsp.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

/* Private defines ---------------------------------------------------------- */
#define DEFAULT_VREF          (1100)
#define NO_OF_SAMPLES         (64)      // Multisampling

/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
static const char *TAG = "bsp";

static esp_adc_cal_characteristics_t *m_adc_chars;
static const adc_channel_t m_adc_channel = ADC_CHANNEL_3;
static const adc_atten_t m_adc_atten     = ADC_ATTEN_DB_11;
static const adc_unit_t m_adc_unit       = ADC_UNIT_1;

/* Private function prototypes ---------------------------------------------- */
static void m_bsp_nvs_init(void);
static void m_bsp_spiffs_init(void);
static void bsp_adc_init(void);

/* Function definitions ----------------------------------------------------- */
void bsp_init(void)
{
  m_bsp_nvs_init();
  m_bsp_spiffs_init();
  bsp_adc_init();
}

void bsp_adc_get_voltage(uint16_t *voltage)
{
  uint32_t adc_reading = 0;

  // Multisampling
  for (int i = 0; i < NO_OF_SAMPLES; i++)
  {
    adc_reading += adc1_get_raw((adc1_channel_t)m_adc_channel);
  }
  adc_reading /= NO_OF_SAMPLES;

  // Convert adc_reading to voltage in mV
  *voltage = (uint16_t)esp_adc_cal_raw_to_voltage(adc_reading, m_adc_chars);
}

/* Private function --------------------------------------------------------- */
static void bsp_adc_init(void)
{
  adc1_config_width(ADC_WIDTH_BIT_12);
  adc1_config_channel_atten(m_adc_channel, m_adc_atten);

  //Characterize ADC
  m_adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize(m_adc_unit, m_adc_atten, ADC_WIDTH_BIT_12, DEFAULT_VREF, m_adc_chars);
}

static void m_bsp_nvs_init(void)
{
  esp_err_t ret = ESP_OK;

  ret = nvs_flash_init();
  if ((ESP_ERR_NVS_NO_FREE_PAGES == ret) || (ESP_ERR_NVS_NEW_VERSION_FOUND == ret))
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ESP_ERROR_CHECK(nvs_flash_init());
  }
}

static void m_bsp_spiffs_init(void)
{
  esp_err_t ret = ESP_OK;
  ESP_LOGI(TAG, "Initializing SPIFFS");

  esp_vfs_spiffs_conf_t spiffs_init_cfg = 
  {
    .base_path              = "/spiffs",
    .partition_label        = NULL,
    .max_files              = 5,
    .format_if_mount_failed = true
  };
  ret = esp_vfs_spiffs_register(&spiffs_init_cfg);

  if (ESP_OK != ret)
  {
    ESP_LOGE(TAG, "SPIFFS init failed: %s", esp_err_to_name(ret));
    return;
  }

  size_t total = 0, used = 0;
  ret = esp_spiffs_info(NULL, &total, &used);

  if (ESP_OK == ret)
    ESP_LOGI(TAG, "Partition size: total: %d, used: %d", total, used);
  else
    ESP_LOGE(TAG, "SPIFFS get info failed: %s", esp_err_to_name(ret));
}

/* End of file -------------------------------------------------------- */