/**
 *******************************************************************************
 * @file            stepper.hpp
 * @author          Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
 * @brief           Stepper motor module interface for the FunSAPE++ AVR8
 *                      Library.
 * @details         Stepper motor module interface for the FunSAPE++ AVR8
 *                      Library.
 * @date            2025-08-08
 * @version         25.08
 * @copyright       MIT License
 * @note            No notes at this time.
 * @todo            No itens in todo list yet.
 * @bug             No bugs detected yet.
 *
 *******************************************************************************
 * @attention
 *
 * MIT License
 *
 * Copyright (c) 2025 Leandro Schwarz
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 *      of this software and associated documentation files (the "Software"), to
 *      deal in the Software without restriction, including without limitation
 *      the rights to use, copy, modify, merge, publish, distribute, sublicense,
 *      and/or sell copies of the Software, and to permit persons to whom the
 *      Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 *      all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *      IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *      FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 *      THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *      OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *      ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *      OTHER DEALINGS IN THE SOFTWARE.
 *
 *******************************************************************************
*/

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __STEPPER_HPP
#define __STEPPER_HPP                   2508

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //

#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error [stepper.hpp] Error 1 - Header file (globalDefines.hpp) is missing or corrupted!
#elif __GLOBAL_DEFINES_HPP != __STEPPER_HPP
#   error [stepper.hpp] Error 2 - Build mismatch between file (stepper.hpp) and global definitions file (globalDefines.hpp)!
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error [stepper.hpp] Error 1 - Header file (debug.hpp) is missing or corrupted!
#elif __DEBUG_HPP != __STEPPER_HPP
#   error [stepper.hpp] Error 5 - Build mismatch between file (stepper.hpp) and library dependency (debug.hpp)!
#endif

#include "../peripheral/gpioPin.hpp"
#ifndef __GPIO_PIN_HPP
#   error [stepper.hpp] Error 1 - Header file (gpioPin.hpp) is missing or corrupted!
#elif __GPIO_PIN_HPP != __STEPPER_HPP
#   error [stepper.hpp] Error 5 - Build mismatch between file (stepper.hpp) and library dependency (gpioPin.hpp)!
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //

// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start main group "Devices"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Devices
 * @brief           External devices.
 * @{
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: Start subgroup "Devices/Stepper"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @addtogroup      Stepper
 * @brief           Stepper motor controller module.
 * @{
*/

// =============================================================================
// Undefining previous definitions
// =============================================================================

// NONE

// =============================================================================
// Constant definitions
// =============================================================================

// NONE

// =============================================================================
// New data types
// =============================================================================

// NONE

// =============================================================================
// Interrupt callback functions
// =============================================================================

// NONE

// =============================================================================
// Public functions declarations
// =============================================================================

// NONE

// =============================================================================
// Classes
// =============================================================================

/**
 * @brief           Stepper class.
 * @details         This class can handle unipolar stepper motors in Full Step,
 *                      Half Step and Double Coil Drive.
*/
class Stepper
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------

public:
    enum class Mode : uint8_t {
        FULL_STEP_DRIVE                 = 0,
        DUAL_COIL_DRIVE                 = 1,
        HALF_STEP_DRIVE                 = 2,
    };

private:
    enum class Step : uint8_t {
        NONE        = 0,
        A_A         = 1,
        A_B         = 2,
        B_B         = 3,
        B_C         = 4,
        C_C         = 5,
        C_D         = 6,
        D_D         = 7,
        D_A         = 8
    };

    friend Stepper::Step inlined operator+(Stepper::Step a, uint8_t b);
    friend Stepper::Step inlined operator-(Stepper::Step a, uint8_t b);

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------

public:
    /**
     * @brief       Stepper class constructor.
     * @details     Creates a Stepper object. The object still
     *                  must be initialized before use.
     * @see         init(void).
     * @par Error codes:
     *
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    Stepper(
            void
    );

    /**
     * @brief       Stepper class destructor.
     * @details     Destroys a Stepper object.
    */
    ~Stepper(
            void
    );

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------

public:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - class own methods ---------------------------------------------

public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //

    /**
     * @brief       Returns the last error.
     * @details     Returns the last error.
     * @return      @ref Error          Error status of the last operation.
    */
    Error inlined getLastError(
            void
    );

    /**
     * @brief       Initializes a Stepper object.
     * @details     This function initializes the Stepper object in the given
     *                  @ref Mode @a mode_p.
     * @param[in]   mode_p              Stepper motor drive @ref Mode.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     *
     * @par Error codes:
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t init(
            const Mode mode_p
    );

    bool_t move(
            const Rotation direction_p
    );

    /**
     * @brief       Sets the stepper motor drive mode.
     * @details     This function changes the stepper motor drive mode to the
     *                  given @ref Mode @a mode_p.
     * @param[in]   mode_p              Stepper motor drive @ref Mode.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     *
     * @par Error codes:
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t setMode(
            const Mode mode_p
    );

    /**
     * @brief       Set coil control pins.
     * @details     This function sets the control pins of the stepper coils.
     * @param[out]  coilA_p        Pointer to @ref GpioPin of A coil.
     * @param[out]  coilB_p        Pointer to @ref GpioPin of B coil.
     * @param[out]  coilC_p        Pointer to @ref GpioPin of C coil.
     * @param[out]  coilD_p        Pointer to @ref GpioPin of D coil.
     * @retval      true                if success.
     * @retval      false               if an error occurred. Retrieve the error
     *                                      by calling @ref getLastError().
     *
     * @par Error codes:
     * | Error code       | Meaning                          |
     * |:-----------------|:---------------------------------|
     * | @ref Error::NONE | Success. No erros were detected. |
     *
    */
    bool_t setPorts(
            GpioPin *coilA_p,
            GpioPin *coilB_p,
            GpioPin *coilC_p,
            GpioPin *coilD_p
    );

private:
    void _doStep(
            void
    );

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------

private:
    //     ///////////////////    DEVICE BUS PORT     ///////////////////     //
    GpioPin         *_coilA;
    GpioPin         *_coilB;
    GpioPin         *_coilC;
    GpioPin         *_coilD;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    Rotation        _currentRotation    : 1;
    Step            _currentStep;
    bool_t          _isInitialized      : 1;
    bool_t          _isPortsSet         : 1;
    Error           _lastError;
    Mode            _mode;
}; // class Stepper

// =============================================================================
// Inlined class functions
// =============================================================================

/**
 * @cond
*/

//     ///////////////////     CONTROL AND STATUS     ///////////////////     //

Error inlined Stepper::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

// Stepper::Step inlined operator+(Stepper::Step a, uint8_t b)
// {
//     b += static_cast<uint8_t>(a);
//     b %= 9;
//     b = (b == 0) ? 1 : b;

//     return static_cast<Stepper::Step>(b);
// }

// Stepper::Step inlined operator-(Stepper::Step a, uint8_t b)
// {
//     uint8_t aux8 = static_cast<uint8_t>(a);

//     if()


//         if() {
//             b -= ;
//         }
//     b %= 9;
//     b = (b == 0) ? 1 : b;

//     return static_cast<Stepper::Step>(b);
// }

/**
 * @endcond
*/

// =============================================================================
// External global variables
// =============================================================================

// NONE

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End subgroup "Devices/Stepper"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
* @}
*/

// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Doxygen: End main group "Devices"
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/**
 * @}
*/

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __STEPPER_HPP

// =============================================================================
// End of file (stepper.hpp)
// =============================================================================
