/*
 * File: main.cpp
 * Project: drone_r6_fw
 * File Created: Monday, 24th February 2025 8:57:51 pm
 * Author: MZoltan (zoltan.matus.smm@gmail.com)
 * 
 * Last Modified: Wednesday, 26th February 2025 11:32:22 pm
 * Version: 0.1.0 (ALPHA)
 * 
 * Copyright (c) 2025 MZoltan
 * License: MIT License
 */

#include "DebugAndVersionControl.h"
#include "UnitTests.h"

#ifndef UNIT_TESTS
#include "CameraManager.h"
#include "DistanceSensorManager.h"
#include "GyroSensorManager.h"
#include "LedManager.h"
#include "ModeManager.h"
#include "MotorManager.h"
#include "ServerManager.h"
#include "StorageManager.h"
#include "WiFiModulManager.h"
#endif

#ifndef UNIT_TESTS
void initialize(); 
void process();
void cleanup();
#endif

extern "C" void app_main(void)
{
#ifdef UNIT_TESTS
    //UnitTests::CameraManagerUnitTest(false);
    //UnitTests::DistanceSensorManagerUnitTest(false);
    //UnitTests::GyroSensorManagerUnitTest(false);
    //UnitTests::LedManagerUnitTest(false);
    //UnitTests::ModeManagerUnitTest(false);
    //UnitTests::MotorManagerUnitTest(false);
    //UnitTestst::ServerManagerUnitTest(false);
    //UnitTests::StorageManagerUnitTest(false);
    UnitTests::WiFiModulManagerUnitTest(false);
#else
#ifdef RESET_MEMORY_TO_DEFAULT
    StorageManager::resetMemoryToDefault();
#else
    // TODO: Implement the main function
    initialize();
    process();
    //cleanup();

    while (true) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }


#endif
#endif
}

#ifndef UNIT_TESTS
void initialize() {
    LedManager::init();
    // WifiModulManager::init(); Future implementation: WiFi Modul Manager init function
    CameraManager::init();
    // MotorManager::init(); Future implementation: Motor Manager init function
    // ServerManager::init(); Future implementation: Server Manager init function

}

void process() {
    LedManager* ledManager = LedManager::getInstance();
    ledManager->startLedArrayControls();
    ledManager->setColor(Colors::Orange);
    
    WiFiModulManager* wifiModulManager = WiFiModulManager::getInstance();
    wifiModulManager->setSSID(WIFI_SSID);
    wifiModulManager->setPassword(WIFI_PASSWORD);
    wifiModulManager->startWiFiControls();

    
    MotorManager::getInstance()->startMotorControls();

    vTaskDelay(30000 / portTICK_PERIOD_MS); // Wait for the wifi to connect
    ServerManager::getInstance()->startServers();
}

void cleanup() {
    LedManager::deinit();
    // WifiModulManager::deinit(); Future implementation: WiFi Modul Manager deinit function
    CameraManager::deinit();
    // MotorManager::deinit(); Future implementation: Motor Manager deinit function
    // ServerManager::deinit(); Future implementation: Server Manager deinit function
}
#endif