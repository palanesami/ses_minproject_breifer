#include "stdio.h"
#include "string.h"
#include "briefer_gpio.h"
#include "unistd.h"

#define LCD_RS      17
#define LCD_RW      27
#define LCD_EN      22
#define LCD_D4      5
#define LCD_D5      6
#define LCD_D6      13
#define LCD_D7      26

#define NO_OF_COL   16
#define printf 
static void briefer_lcd_data_write(char buffer)
{
    
   /* printf(" write %c %x [%d %d %d %d] [%d %d %d %d] \n", buffer, buffer,
                                                (buffer >> 4) & 0x01,
                                                (buffer >> 4) & 0x02,
                                                (buffer >> 4) & 0x04,
                                                (buffer >> 4) & 0x08,
                                                (buffer) & 0x01,
                                                (buffer) & 0x02,
                                                (buffer) & 0x04,
                                                (buffer) & 0x08);
    */
    briefer_gpio_set(LCD_RW, 0);
    briefer_gpio_set(LCD_D4, (buffer >> 4) & 0x01);
    briefer_gpio_set(LCD_D5, (buffer >> 4) & 0x02);
    briefer_gpio_set(LCD_D6, (buffer >> 4) & 0x04);
    briefer_gpio_set(LCD_D7, (buffer >> 4) & 0x08);
    
    briefer_gpio_set(LCD_EN, 1);
    usleep(1000);

    briefer_gpio_set(LCD_EN, 0);
    usleep(2000);

    briefer_gpio_set(LCD_D4, (buffer) & 0x01);
    briefer_gpio_set(LCD_D5, (buffer) & 0x02);
    briefer_gpio_set(LCD_D6, (buffer) & 0x04);
    briefer_gpio_set(LCD_D7, (buffer) & 0x08);

    briefer_gpio_set(LCD_EN, 1);
    usleep(1000);

    briefer_gpio_set(LCD_EN, 0);
    usleep(5000);
}

static unsigned int briefer_lcd_gpio_init(int pin)
{
    briefer_gpio_deinit(pin);
    
    briefer_gpio_init(pin);
}

static void briefer_lcd_cmd(char buffer)
{
    briefer_gpio_set(LCD_RS, 0);
    
    briefer_lcd_data_write(buffer);

    briefer_gpio_set(LCD_RS, 1);
}

unsigned int briefer_lcd_init()
{
    briefer_lcd_gpio_init(LCD_RS);
    briefer_lcd_gpio_init(LCD_RW);
    briefer_lcd_gpio_init(LCD_EN);
    briefer_lcd_gpio_init(LCD_D4);
    briefer_lcd_gpio_init(LCD_D5);
    briefer_lcd_gpio_init(LCD_D6);
    briefer_lcd_gpio_init(LCD_D7);

    usleep(500 * 1000);

    briefer_lcd_cmd(0x02); // 4bit
    briefer_lcd_cmd(0x28); // 16*2
    briefer_lcd_cmd(0x0c); // Disp on cursor off
    briefer_lcd_cmd(0x06); // ++ cursor
    briefer_lcd_cmd(0x01); // cls display
    briefer_lcd_cmd(0x80); // home pos
}

unsigned int briefer_lcd_deinit()
{
    briefer_lcd_cmd(0x01); // cls display
    briefer_gpio_deinit(LCD_RS);
    briefer_gpio_deinit(LCD_RW);
    briefer_gpio_deinit(LCD_EN);
    briefer_gpio_deinit(LCD_D4);
    briefer_gpio_deinit(LCD_D5);
    briefer_gpio_deinit(LCD_D6);
    briefer_gpio_deinit(LCD_D7);
}


void briefer_lcd_display(char* buffer, char row, char clear)
{
    char format[NO_OF_COL];
    
    if (clear){
        briefer_lcd_cmd(0x01); // cls display
    }

    if(row) {
        briefer_lcd_cmd(0xC0); // second row
    } else {
        briefer_lcd_cmd(0x80); // home pos
    }

    if (strlen(buffer) >= NO_OF_COL) {
        strncpy(format, buffer, NO_OF_COL);
    } else {
        int stub = (NO_OF_COL - strlen(buffer)) / 2;
        for (int i = 0; i < stub; i++) {
            format[i] = ' ';    
        }
        strcpy((char*)format + stub, buffer);
        printf("[%s] [%s] [%d]\n", format, buffer, stub);
    }

    for(int i= 0; i < strlen(format); i++) {
        briefer_gpio_set(LCD_RS, 1);
        briefer_lcd_data_write(format[i]);
        briefer_gpio_set(LCD_RS, 0);
        usleep(200 * 1000);
    }
}