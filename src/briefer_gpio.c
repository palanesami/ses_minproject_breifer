#include "stdio.h"
#include "briefer_gpio.h"

#include "unistd.h"

#define printf 
#define DEFAULT_GPIO_NUMBER 512
#define GET_GPIO_NUM(X) (DEFAULT_GPIO_NUMBER + X)

unsigned int briefer_gpio_init(int pin_number)
{
    unsigned int rvalue = -1;
    char temp[64];
    char bytes;
    FILE *fp = NULL;

    bytes = sprintf(temp, "%d", GET_GPIO_NUM(pin_number));

    fp = fopen("/sys/class/gpio/export", "w");
    printf("value %d \n", fp);
    if (fp) {
        fwrite(temp, bytes, 1, fp);
        fclose(fp);
    }
    
    usleep(200 * 1000); //200ms is requried to open the direction sys file

    bytes = sprintf(temp, "/sys/class/gpio/gpio%d/direction", GET_GPIO_NUM(pin_number));

    fp = fopen(temp, "w");
    printf("direction value %d [%s] \n", fp, temp);
    if (fp) {
        bytes = sprintf(temp, "%s", "out");
        fwrite(temp, bytes, 1, fp);
        //write(fp, temp, bytes);
        fclose(fp);
    }
    return rvalue;
}
unsigned int briefer_gpio_deinit(int pin_number)
{
    unsigned int rvalue = -1;
    char temp[64];
    char bytes;
    FILE *fp = NULL;

    bytes = sprintf(temp, "%d", GET_GPIO_NUM(pin_number));

    fp = fopen("/sys/class/gpio/unexport", "w");
    if (fp) {
        fwrite(temp, bytes, 1, fp);
        fclose(fp);
    }
    return rvalue;
}
unsigned int briefer_gpio_set(int pin_number, int value)
{
    unsigned int rvalue = -1;
    char temp[64];
    char bytes;
    FILE *fp = NULL;

    bytes = sprintf(temp, "/sys/class/gpio/gpio%d/value", GET_GPIO_NUM(pin_number));

    fp = fopen(temp, "w");
    printf("set value %d [%s] \n", fp, temp);
    if (fp) {
        bytes = sprintf(temp, "%d", !!value);
        fwrite(temp, bytes, 1, fp);
        fclose(fp);
    }
    return rvalue;
}
