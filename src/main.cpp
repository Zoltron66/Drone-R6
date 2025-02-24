
#include "VersionControl.h"
#include "WiFiModulManager.h"
#include "CameraManager.h"
#include "MotorManager.h"
#include "ServerManager.h"


extern "C" {
#include "esp_wifi.h"
#include "freertos/task.h"
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

    // DEBUG_PRINT("");
    // // Some process...

    // DEBUG_PRINT("Disconnecting in 5 seconds...");
    // vTaskDelay(5000 / portTICK_PERIOD_MS);
    // wifiModulManager->disconnectFromWiFi();

    // DEBUG_PRINT("Deinitializing Wi-Fi module...");
    // wifiModulManager->~WiFiModulManager();

    // DEBUG_PRINT("End of test... [PASSED]");
}


void initialize() {
    // Initialize the long term storage
    // StorageManager* storageManager = StorageManager::getInstance();

    // Initialize the Wi-Fi module
    //WiFiModulManager* wifiModulManager = WiFiModulManager::getInstance();
    // wifiModulManager->setSSID(storageManager->getSSID());
    // wifiModulManager->setPassword(storageManager->getPassword());

    // Initialize the Motor Manager
    //MotorManager::getInstance();

}

void process() {
    
}

void cleanup() {
    
}