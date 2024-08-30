#ifndef BRIEFER_LCD_H
#define BRIEFER_LCD_H
unsigned int briefer_lcd_init();
unsigned int briefer_lcd_deinit();
unsigned int briefer_lcd_display(char* buffer, char row, char clear);
#endif