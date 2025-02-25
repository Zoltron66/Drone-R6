
#include "VersionControl.h"
#include "WiFiModulManager.h"
#include "CameraManager.h"
#include "MotorManager.h"
#include "ServerManager.h"


extern "C" {
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "led_strip.h"

#include <stdio.h>
}

#define WIFI_SSID "Telekom-60C778"
//#define WIFI_SSID "MZoltan’s iPhone"
#define WIFI_PASSWORD "ngntbxknf5p4rfsm-$"
//#define WIFI_PASSWORD "HXCF-riSN-33bq-taTN"


void initialize(); 
void process();
void cleanup();

extern "C" void app_main(void)
{
    cleanup();
}


void initialize() {
    DEBUG_PRINT("Starting test...");


    
    DEBUG_PRINT("Initializing Wi-Fi module...");
    WiFiModulManager* wifiModulManager = WiFiModulManager::getInstance();
    wifiModulManager->setSSID(WIFI_SSID);
    wifiModulManager->setPassword(WIFI_PASSWORD);

    DEBUG_PRINT("Initializing Camera module...");
    CameraManager* cameraManager = CameraManager::getInstance();
    // I (1291) camera: Detected OV2640 camera
    

    DEBUG_PRINT("Initializing Motor Manager...");
    MotorManager* motorManager = MotorManager::getInstance();
    

    DEBUG_PRINT("Initializing Server Manager...");
    ServerManager* serverManager = ServerManager::getInstance();
    
    DEBUG_PRINT("Connecting to Wi-Fi network...");
    int counter = 0;
    while (wifiModulManager->getNetworkStatus() != CONNECTED) {
        wifiModulManager->connectToWiFi();
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        counter++;
        if (counter > 10) {
            DEBUG_PRINT("Failed to connect to Wi-Fi network");
        }
    }

    DEBUG_PRINT("Connected to Wi-Fi network...");


    // wifi_ap_record_t apInfo;
    // esp_wifi_sta_get_ap_info(&apInfo);
    

    DEBUG_PRINT("Powering on camera...");
    //cameraManager->powerOnCamera();
    


    DEBUG_PRINT("Starting motor controls...");
    motorManager->startMotorControls();

    DEBUG_PRINT("Starting servers...");
    serverManager->startServers();

    DEBUG_PRINT("Processing...");
    while (true) {
        vTaskDelay(10000 / portTICK_PERIOD_MS);
    }
}

void process() {
    // DEBUG_PRINT("");
    // // Some process...

    // DEBUG_PRINT("Disconnecting in 5 seconds...");
    // vTaskDelay(5000 / portTICK_PERIOD_MS);
    // wifiModulManager->disconnectFromWiFi();

    // DEBUG_PRINT("Deinitializing Wi-Fi module...");
    // wifiModulManager->~WiFiModulManager();

    // DEBUG_PRINT("End of test... [PASSED]");
    
}

#define LED_STRIP_LENGTH 6U
static struct led_color_t led_strip_buf_1[LED_STRIP_LENGTH];
static struct led_color_t led_strip_buf_2[LED_STRIP_LENGTH];

#define LED_STRIP_RMT_INTR_NUM 19

void cleanup() {
    nvs_flash_init();

    struct led_strip_t led_strip = {
        .rgb_led_type = RGB_LED_TYPE_WS2812,
        .led_strip_length = LED_STRIP_LENGTH,
        .rmt_channel = RMT_CHANNEL_1,
        .rmt_interrupt_num = LED_STRIP_RMT_INTR_NUM,
        .gpio = GPIO_NUM_16,
        .led_strip_buf_1 = led_strip_buf_1,
        .led_strip_buf_2 = led_strip_buf_2
    };
    led_strip.access_semaphore = xSemaphoreCreateBinary();

    bool led_init_ok = led_strip_init(&led_strip);
    assert(led_init_ok);

    struct led_color_t led_color = {
        .red = 5,
        .green = 0,
        .blue = 0,
    };

    while (true) {
        for (uint32_t index = 0; index < LED_STRIP_LENGTH; index++) {
            led_strip_set_pixel_color(&led_strip, index, &led_color);
        }
        led_strip_show(&led_strip);

        led_color.red += 5;
        vTaskDelay(30 / portTICK_PERIOD_MS);
    }

}