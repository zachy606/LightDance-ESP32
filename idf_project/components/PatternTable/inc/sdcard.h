#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "sdmmc_cmd.h"
#include "esp_vfs_fat.h"
#include "driver/sdspi_host.h"

esp_err_t mount_sdcard(sdmmc_card_t **g_card);
void unmount_sdcard(sdmmc_card_t **g_card);

#ifdef __cplusplus
}
#endif