/*
 * File: ledManager.h
 * Project: drone_r6_fw
 * File Created: Monday, 17th February 2025 2:54:44 am
 * Author: MZoltan (zoltan.matus.smm@gmail.com)
 * 
 * Last Modified: Monday, 17th February 2025 2:54:44 am
 * Version: 0.1.0 (ALPHA)
 * 
 * Copyright (c) 2025 MZoltan
 * License: MIT License
 */

#pragma once

#include "VersionControl.h"

// LED GPIO pins
#define LED_WS28XX              16  // GPIO_16

// LED Colors
namespace LedColor {
    
    // LED Color ------------------------------------------------------------------------------------------------
    //struct
}





// LED Manager --------------------------------------------------------------------------------------------------
class LedManager {
private:
    LedManager();
    static LedManager* instance;

public:

    LedManager(const LedManager& ledManager) = delete;

    LedManager& operator=(const LedManager& ledManager) = delete;

    ~LedManager() { delete instance; }

    static LedManager* getInstance();

    void startLed();
};


// TODO: Future implementation: Create a led manager for the beta version (WS2812B RGB LED).