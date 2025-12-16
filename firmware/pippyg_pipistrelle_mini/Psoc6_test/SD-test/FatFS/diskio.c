/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */
#include "cyhal.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	stat = 0; ///////////////////////////////////////////////////////
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/


#define custom_card_detect P13_5
/* Pins connected to the SDHC block */
#define cmd P12_4
#define clk P12_5
#define dat0 P13_0
#define dat1 P13_1
#define dat2 P13_2
#define dat3 P13_3
/* dat4 to dat7 are reserved for future use and should be NC */
#define dat4 NC
#define dat5 NC
#define dat6 NC
#define dat7 NC
#define card_detect NC
#define emmc_reset NC
#define io_volt_sel NC
#define card_if_pwren NC
#define card_mech_writeprot NC
#define led_ctl NC
cyhal_sdhc_t sdhc_obj;

/*
__USED bool Cy_SD_Host_IsCardConnected(SDHC_Type const *base __attribute__((unused)))
{
/* P13_5 reads 0 when card detected, 1 when card not detected 
return cyhal_gpio_read(custom_card_detect) ? false : true;
}
*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	cy_rslt_t rslt;

	const cyhal_sdhc_config_t sdhc_config = {false, false, false, 4};

	rslt = cyhal_gpio_init(custom_card_detect, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, true);

	rslt = cyhal_sdhc_init(&sdhc_obj, &sdhc_config, cmd, clk, dat0, dat1, dat2, dat3, dat4, dat5, dat6, dat7, card_detect, io_volt_sel, card_if_pwren, card_mech_writeprot, led_ctl, emmc_reset, NULL);

	if(rslt == CY_RSLT_SUCCESS)
		return 0;
	else
		return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{

	cy_rslt_t rslt;

	rslt = cyhal_sdhc_read(&sdhc_obj, sector, buff, &count);

	if(rslt == CY_RSLT_SUCCESS)
		return RES_OK;
	else
		return RES_ERROR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{

	cy_rslt_t rslt;

	rslt = cyhal_sdhc_write(&sdhc_obj, sector, buff, &count);

	if(rslt == CY_RSLT_SUCCESS)
		return RES_OK;
	else
		return RES_ERROR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;

	switch (pdrv) {
	case DEV_RAM :

		// Process of the command for the RAM drive

		return res;

	case DEV_MMC :

		// Process of the command for the MMC/SD card

		return res;

	case DEV_USB :

		// Process of the command the USB drive

		return res;
	}

	return RES_PARERR;
}

const unsigned long rtcYear = 2020;
const unsigned long rtcMonth = 3;
const unsigned long rtcDay = 30;
const unsigned long rtcHour = 10;
const unsigned long rtcMinutes = 32;
const unsigned long rtcSeconds = 0;

DWORD get_fattime()
{
	/* Pack date and time into a DWORD variable */
	return (((DWORD)rtcYear - 1980) << 25) | ((DWORD)rtcMonth << 21) | ((DWORD)rtcDay << 16)| (WORD)(rtcHour << 11)|
            (WORD)(rtcMinutes << 5)	| (WORD)(rtcSeconds >> 1);;
}

