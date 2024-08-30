#ifndef BRIEFER_GPIO_H
#define BRIEFER_GPIO_H
unsigned int briefer_gpio_init(int pin_number);
unsigned int briefer_gpio_deinit(int pin_number);
unsigned int briefer_gpio_set(int pin_number, int value);
#endif