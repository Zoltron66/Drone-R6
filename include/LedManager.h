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

extern "C" {
#include "driver/gpio.h"
}

// LED GPIO pins
#define LED_WS2812              GPIO_NUM_16

// Colors
namespace Colors
{

    class Color
    {
    private:
        int R;
        int G;
        int B;

    public:
        Color(int r, int g, int b) : R(r), G(g), B(b) {};

        int getR() const { return R; }
        int getG() const { return G; }
        int getB() const { return B; }

        void setR(int r) { R = r >= 0 && r <= 255 ? r : 0; }
        void setG(int g) { G = g >= 0 && g <= 255 ? g : 0; }
        void setB(int b) { B = b >= 0 && b <= 255 ? b : 0; }
    };

    // Default Gadget RGB Colors
    const Color Orange(247, 209, 96);
    const Color Red(218, 86, 68);
    const Color Blue(75, 159, 218);

    // Reflector RGB Color
    const Color White(255, 255, 255);

    // Extra Gadget RGB Colors (Funny colors, because why not?)
    const Color Pink(0, 0, 0);

    // Utility RGB Colors
#ifdef BLUETOOTH_MODE  
    const Color Bluetooth(10, 245, 237);
#endif
    const Color Wifi(10, 143, 245);
    const Color Error(230, 9, 57);

    // OFF RGB Color
    const Color Off(0, 0, 0);
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