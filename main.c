#include <stdio.h>

#include "lptimer.h"
#include "periph/i2c.h"
#include "bmx280.h"

//#include "bmx280_internals.h"
//#include "bmx280_params.h"

static bmx280_t dev_bmx280;
static bmx280_params_t bme280_params = {
    .i2c_dev = I2C_DEV(1),
    .i2c_addr = 0x76,
    .t_sb = BMX280_SB_0_5, //standby time between 0.5 and 1000 ms
    .filter = BMX280_FILTER_OFF,
    .run_mode = BMX280_MODE_FORCED, //a single meas is performed in acc to the selected measurement and filter options. 
    .temp_oversample = BMX280_OSRS_X1,
    .press_oversample = BMX280_OSRS_X1,
    .humid_oversample = BMX280_OSRS_X1,
};

int main(void) {
    puts("Hello, World!\r\n");

    if (bmx280_init(&dev_bmx280, &bme280_params) == BMX280_OK) {
        puts("BME280 succesfully initialised!\r\n");
        
        while(1){
            int t = bmx280_read_temperature(&dev_bmx280); /* degrees C * 100 */
//bme
            int h = bme280_read_humidity(&dev_bmx280); /* percents * 100 */
            int p = bmx280_read_pressure(&dev_bmx280)/100; /* Pa -> mbar */

            printf("Temperature = %i.%i C, Humidity = %i.%i %%, Pressure = %i mbar.\r\n", t/100, t%100, h/100, h%100, p);
		
            lptimer_sleep(10000);
        }
		//if (bmx280_read_temperature(&dev_bmx280)>30)
		//printf("error!\r\n");
		    
	
    }

    return 0;
}
