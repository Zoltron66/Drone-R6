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

#include "DebugAndVersionControl.h"

extern "C" {
#include "driver/gpio.h"
}

// LED GPIO pins
#define LED_WS2812              GPIO_NUM_3


// Colors -------------------------------------------------------------------------------------------------------
namespace Colors {
    // RGB Color -------------------------------------------------------------------------------------------------
    /**
     * @brief Represents an RGB color with adjustable brightness.
     * This class allows you to set and get RGB values, adjust brightness,
     * and compare colors.
     */
    class Color {
    // Init RGB Color ----------------------------------------------
    public:
        Color(uint8_t R = 0, uint8_t G = 0, uint8_t B = 0, uint8_t brightness = 100);
    
    // Colors ------------------------------------------------------
    private:
        uint8_t R;
        uint8_t G;
        uint8_t B;
        uint8_t brightness;

    // Setters and Getters -----------------------------------------
        uint8_t setOneColor(int color) const;

    public:
        void setR(int R);
        void setR(int R, int MIN, int MAX);
        void setG(int G);
        void setG(int G, int MIN, int MAX);
        void setB(int B);
        void setB(int B, int MIN, int MAX);
        void setBrightness(int brightness);
        void setBrightness(int brightness, int MIN, int MAX);

        uint8_t getRawR() const { return R; }
        uint8_t getRawG() const { return G; }
        uint8_t getRawB() const { return B; }
        uint8_t getBrightness() const { return brightness; }

        uint8_t getR() const { return setOneColor(float(brightness) / 100 * R); }
        uint8_t getG() const { return setOneColor(float(brightness) / 100 * G); }
        uint8_t getB() const { return setOneColor(float(brightness) / 100 * B); }

    // Compare RGB Colors ------------------------------------------
    public:
        bool operator==(const Color &color) const;
    };

    // Default Gadget RGB Colors
    static const Color Orange(110U, 20U, 0U);   // OK
    static const Color Red(250U, 8U, 0U);       // OK
    static const Color Blue(0U, 50U, 255U);     // OK

    // Reflector RGB Color
    static const Color White(255U, 255U, 255U); // Obviously OK

    // Extra Gadget RGB Colors
    static const Color Pink(250U, 2U, 20U);     // OK

    // Utility RGB Colors
    static const Color Wifi(10U, 100U, 250U);   // OK
    static const Color Error(255U, 0U, 0U);     // OK

    // OFF RGB Color
    static const Color Off(0U, 0U, 0U, 0U);     // Obviously OK
}


// LED ----------------------------------------------------------------------------------------------------------
/**
 * @brief Represents a single LED with color stages and controls.
 * This class allows you to set the current and target color stages,
 * move towards the target stage, and control the LED's color and brightness.
 */
class Led {
// Init LED ---------------------------------------------------
public:
    Led() {};

// LED stages -------------------------------------------------
public:
    Colors::Color currentColorStage;

private:
    Colors::Color targetColorStage;

public:
    /**
     * @brief Moves the LED towards the target color stage.
     * @param speed The speed of the transition.
     * @param MINB Minimum brightness value (default: 0).
     * @param MAXB Maximum brightness value (default: 100).
     * @param MINC Minimum color value (default: 0).
     * @param MAXC Maximum color value (default: 255).
     * @return true if the LED has reached the target stage, false otherwise.
     * 
     * This function adjusts the current color stage towards the target color stage
     * by incrementing or decrementing the brightness and RGB values based on the specified speed.
     * If the current color stage matches the target color stage, it returns true, indicating that the LED has reached the target stage.
     */
    bool moveTowardsToTargetStage(int speed, int MINB = 0, int MAXB = 100, int MINC = 0, int MAXC = 255);

// LED controls -----------------------------------------------
public:
    /**
     * @brief Sets the current and target color stages to the specified color.
     * @param color The color to set for both current and target stages.
     */
    void setColor(Colors::Color color) { currentColorStage = color; targetColorStage = color; }
    
    /**
     * @brief Sets the current color stage to the specified color.
     * @param color The color to set for the current stage.
     */
    void setCurrentColor(Colors::Color color) { currentColorStage = color; }

    /**
     * @brief Sets the brightness of the current color stage.
     * @param brightness The brightness value to set (0-100).
     */
    void setCurrentColorBrightness(float brightness) { currentColorStage.setBrightness(brightness); }

    /**
     * @brief Sets the target color stage to the specified color.
     * @param color The color to set for the target stage.
     */
    void setTargetColor(Colors::Color color) { targetColorStage = color; }

    /**
     * @brief Sets the brightness of the target color stage.
     * @param brightness The brightness value to set (0-100).
     */
    void setTargetColorBrightness(float brightness) { targetColorStage.setBrightness(brightness); }

    /**
     * @brief Sets the LED to the OFF state.
     * This function sets both the current and target color stages to the OFF color.
     */
    void setOff() { currentColorStage = Colors::Off; targetColorStage = Colors::Off; }
};

// Animation Types -----------------------------------------------------------------------------------------------
enum AnimationType {
    NONE,

    // Default Gadget Animations
    IDLE,
    IDLE_DEBUG,

    // Extra Gadget Animations
    WIFI_CONNECTING,
    WIFI_CONNECTED,
    WIFI_DISCONNECTED
};


// LED Manager --------------------------------------------------------------------------------------------------
/**
 * @brief Manages the LED array and animations.
 * This class provides controls for setting colors, animations, and managing the LED array.
 */
class LedManager {
// Init LED manager ---------------------------------------------------
private:
    LedManager();

// LED manager controls ----------------------------------------------
private:
    Colors::Color debugColor, currentColor;
    
public:
    void setDebugColor(Colors::Color color) { debugColor = color; }
    void setColor(Colors::Color color) { currentColor = color; }

    bool moveAllLedTowardsToTargetColor(int MINB = 0, int MAXB = 100, int MINC = 0, int MAXC = 255);

    void setAllOff();

// Animation controls -------------------------------------------------
private:
    AnimationType currentAnimation, lastAnimation;
    uint8_t animationSpeed;

public:
    /**
     * @brief Sets the current animation type.
     * @param animation The animation type to set.
     */
    void setAnimation(AnimationType animation) { currentAnimation = animation; }

    /**
     * @brief Resets the current animation to NONE.
     * This function sets both the current and last animations to NONE.
     */
    void resetAnimation() { currentAnimation = AnimationType::NONE; lastAnimation = AnimationType::NONE; }

    /**
     * @brief Sets the animation speed.
     * @param speed The speed value to set (default: 1).
     */
    void setAnimationSpeed(uint8_t speed = 1) { animationSpeed = speed; }

    /**
     * @brief Gets the current animation type.
     * @return The current animation type.
     */
    AnimationType getCurrentAnimation() const { return currentAnimation; }

// Animation sequences -----------------------------------------------
private:
    uint8_t animationStage;

    void resetAnimationStageIfChanged(AnimationType animation, uint8_t speed = 1);

public:
    void playNone();

    void playIdleAnimation();

#ifdef VERSION_1_OR_LATER
    void playIdleDebugAnimation();
#endif

    void playWifiConnectingAnimation();

    void playWifiConnectedAnimation();

    void playWifiDisconnectedAnimation();

// LED array controls -------------------------------------------------
private:
    Led LED[6];

public:
    /**
     * @brief Transmits the current waveform to the LED array.
     * This function sends the current color stages of all LEDs to the LED array.
     * It encodes the color data and transmits it using the RMT (Remote Control) interface.
     */
    void transmitWaveformToLedArray();

    /**
     * @brief Starts the LED array controls task.
     * This function creates a FreeRTOS task that continuously updates the LED array
     * based on the current animation and color settings.
     */
    void startLedArrayControls();

// Deinit LED manager -------------------------------------------------
public:
     ~LedManager();

// Singleton ----------------------------------------------------------
private:
    static LedManager* instance;

public:
    LedManager(const LedManager& ledManager) = delete;

    LedManager& operator=(const LedManager& ledManager) = delete;

    static void init();

    static LedManager* getInstance() { return instance; }

    static void deinit();
};