#include "stdio.h"
#include "briefer_gpio.h"
#include "briefer_lcd.h"

#include <netinet/in.h>
#include <linux/if.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
//#include <net/if.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define NO_OF_EXECUTION     10

typedef enum {
    LCD_DATA_MAIN,
    LCD_DATA_IP,
    LCD_DATA_HOST_NAME,
    LCD_DATA_LOCATION,
} LCD_DATA_COMMAND;

typedef struct lcd_list_t {
    LCD_DATA_COMMAND cmd; // defined to access for paritcular type.
    char buffer[16]; // buffering 
    struct lcd_list_t *pnext;   // next node
} LCD_LIST;

typedef struct briefer_t {
    LCD_LIST *phead;
    LCD_LIST *ptail;
    pthread_mutex_t access;
    pthread_t thread;
} BRIEFER;

void briefer_add_to_list(BRIEFER *pbriefer, LCD_DATA_COMMAND cmd, char *data)
{
    struct lcd_list_t *pnode = malloc(sizeof(BRIEFER));

    pthread_mutex_lock(&pbriefer->access);
    if (pnode) {
        pnode->cmd = cmd;
        strcpy(pnode->buffer, data);
        pnode->pnext = NULL;
    }

    if (pbriefer->phead) {
        struct lcd_list_t *ptemp = pbriefer->phead;
        while(ptemp != pbriefer->ptail) ptemp = ptemp->pnext;

        ptemp->pnext = pnode;
        pbriefer->ptail = pnode;
        pbriefer->ptail->pnext = pbriefer->phead;
    } else {
        pbriefer->ptail = pbriefer->phead = pnode->pnext = pnode ;
    }
    pthread_mutex_unlock(&pbriefer->access);
}

void* briefer_worker(void *data)
{
    BRIEFER *pbriefer = (BRIEFER *)data;
    char temp[16];
    pthread_mutex_lock(&pbriefer->access);
    struct lcd_list_t *pnode = pbriefer->phead;
    pthread_mutex_unlock(&pbriefer->access);
    for (int i = 0; i < NO_OF_EXECUTION; i++) {
        sprintf(temp, "CMD : %d", pnode->cmd);
        briefer_lcd_display(temp, 0 , 1);
        briefer_lcd_display(pnode->buffer, 1 , 0);
        pthread_mutex_lock(&pbriefer->access);
        pnode = pnode->pnext;
        pthread_mutex_unlock(&pbriefer->access);
    }
}

//IP, DATE, TIME, USER NAME, LOCATION, WEATHER, RAIN,
int main(int argc, char *argv[])
{
    BRIEFER briefer = {0};
    char host_buffer[512] = "Palanesami";
    unsigned char ip_address[15];
    int fd;
    struct ifreq ifr;
    int return_value;

    if(argv[1] == NULL) {
        printf("Please provide 1 args");
        return -1;
    }

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ifr.ifr_addr.sa_family = AF_INET;
    memcpy(ifr.ifr_name, "wlan0", strlen("wlan0"));
    ioctl(fd, SIOCGIFADDR, &ifr);
    close(fd);
    
    strcpy(ip_address, inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));

    //cuserid(host_buffer);
    briefer_lcd_init();

    briefer_add_to_list(&briefer, LCD_DATA_MAIN, (char *)argv[1]);
    briefer_add_to_list(&briefer, LCD_DATA_HOST_NAME, (char *)host_buffer);
    briefer_add_to_list(&briefer, LCD_DATA_IP, (char *)ip_address);
    briefer_add_to_list(&briefer, LCD_DATA_LOCATION, (char *)"Bangalore");

    return_value = pthread_mutex_init(&briefer.access, NULL);
    if (return_value) printf("pthread_mutex_init failed");

    return_value = pthread_create(&briefer.thread, NULL, briefer_worker, &briefer);
    if (return_value) printf("pthread_create failed");

    pthread_join(briefer.thread, NULL);
    briefer_lcd_deinit();
    return 0;
}