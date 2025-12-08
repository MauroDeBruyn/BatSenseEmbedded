/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for the Empty PSoC6 Application
*              for ModusToolbox.
*
* Related Document: See Readme.md
*
*******************************************************************************
* (c) 2019-2020, Cypress Semiconductor Corporation. All rights reserved.
*******************************************************************************
* This software, including source code, documentation and related materials
* ("Software"), is owned by Cypress Semiconductor Corporation or one of its
* subsidiaries ("Cypress") and is protected by and subject to worldwide patent
* protection (United States and foreign), United States copyright laws and
* international treaty provisions. Therefore, you may use this Software only
* as provided in the license agreement accompanying the software package from
* which you obtained this Software ("EULA").
*
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software source
* code solely for use in connection with Cypress's integrated circuit products.
* Any reproduction, modification, translation, compilation, or representation
* of this Software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer of such
* system or application assumes all risk of such use and in doing so agrees to
* indemnify Cypress against all liability.
*******************************************************************************/

#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FatFS\diskio.h"
#include "FatFS\ff.h"



int main(void)
{
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    __enable_irq();

    /* Initialize retarget-io to use the debug UART port */
	result = cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, \
								 CY_RETARGET_IO_BAUDRATE);

	/* retarget-io init failed. Stop program execution */
	if (result != CY_RSLT_SUCCESS)
	{
		CY_ASSERT(0);
	}

	printf("\r\nStarting Example...\r\n");

	char szPrintf[32];
//	char szFileDir[20][13];
//	uint8_t u8FileCountMax; // Keeps the max number of found files
//	uint8_t u8FileCount;    // Temporary file number

//	u8FileCount = 0;

	FATFS fatFs;
	DIR fatDirectory;
	FIL fil;
	FRESULT fr;     /* FatFs return code */
	FILINFO finfo;
	uint8 resultF;
	char read_line[100]; /* Line buffer */
	char* write_line = "FATFs example in MTB2.0\r\n";
	int count = 0;


	resultF = f_mount(&fatFs, "", 1);
	if (resultF == RES_OK)
	{
		resultF = f_opendir(&fatDirectory, "/");      // open 'root' directory.
	}
	else
	{
		printf("*** ERROR to read directory\r\n");
	}

	if (resultF == RES_OK)
	{
		while(1)
		{
			resultF = f_readdir(&fatDirectory, &finfo);
			if (resultF != 0)
			{
				printf("*** ERROR to read directory\r\n");
				break;
			}
			if (finfo.fname[0] == 0)             // end of directory?
			{
				printf("*** End of directory\r\n");
				break;
			}
			if (finfo.fattrib & AM_DIR)          // is it a directory?
			{
				printf("%s\r\n", finfo.fname);
				printf("\t\t\t<DIR>\r\n");
			}
			else                                    // it is a file.
			{
				printf("%s\r\n", finfo.fname);
				printf("\t\t\t\r\n");
				itoa(finfo.fsize, szPrintf, 10);
				printf("%s\r\n", szPrintf);
				printf(" Bytes \r\n");
			}
		}
	}
	else
	{
			printf("\r*** ERROR: Could not open Directory\r\n");
	}

	resultF = f_opendir(&fatDirectory, "/");
	if(resultF != RES_OK)
		printf("Failed to open root directory\r\n");

    for (;;)
    {
		/* Open file to write a line to the file */
		/* Create a file if file does not exist */
    	fr = f_open(&fil, "message.txt", FA_WRITE | FA_OPEN_ALWAYS);
    	if(fr != FR_OK)
    	{
    		printf("Failed to create file\r\n");
    	}
		printf("Writing to file\r\n");
		f_printf(&fil, "%s Loop Execution count = %d \r\n", write_line, count++);
		f_close(&fil);

		fr = f_open(&fil, "message.txt", FA_READ);
		if (fr != FR_OK)
		{
			printf("Failed to open file\r\n");
		}

		/* Read every line and display it */
		printf("Reading from file\r\n");
		while ( f_eof(&fil) == 0 ) {
			f_gets(read_line, sizeof(read_line), &fil);
			printf("%s\r\n",read_line);
		}

		/* Close the file */
		f_close(&fil);

		cyhal_system_delay_ms(10000);
    }
}

/* [] END OF FILE */
