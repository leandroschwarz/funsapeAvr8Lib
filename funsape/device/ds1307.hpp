//!
//! \file           hd44780.hpp
//! \brief          DS1307 module interface for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2023-05-28
//! \version        23.04
//! \copyright      license
//! \details        DS1307 RTC module interface
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __DS1307_HPP
#define __DS1307_HPP                            2304

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////     GLOBAL DEFINITIONS FILE    /////////////////     //
#include "../globalDefines.hpp"
#if !defined(__GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __GLOBAL_DEFINES_HPP != __DS1307_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //
#include "../util/debug.hpp"
#if !defined(__DEBUG_HPP)
#   error "Header file (debug.hpp) is corrupted!"
#elif __DEBUG_HPP != __DS1307_HPP
#   error "Version mismatch between header file and library dependency (debug.hpp)!"
#endif

#include "../util/bus.hpp"
#if !defined(__BUS_HPP)
#   error "Header file (bus.hpp) is corrupted!"
#elif __BUS_HPP != __DS1307_HPP
#   error "Version mismatch between header file and library dependency (bus.hpp)!"
#endif

#include "../util/dateTime.hpp"
#if !defined(__DATETIME_HPP)
#   error "Header file (dateTime.hpp) is corrupted!"
#elif __DATETIME_HPP != 2304
#   error "Version mismatch between header file and library dependency (dateTime.hpp)!"
#endif

//     ///////////////////     STANDARD C LIBRARY     ///////////////////     //
// NONE

//     ////////////////////    AVR LIBRARY FILES     ////////////////////     //
// NONE

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
// Ds1307 Class
// =============================================================================

//!
//! \brief          Ds1307 class
//! \details        Ds1307 class.
//!
class Ds1307
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    //     ///////////////     SQUARE WAVE GENERATOR     ////////////////     //
    //!
    //! \brief      Square wave generator behavior
    //! \details    Square wave generator behavior.
    //!
    enum class SquareWave {
        OFF_LOW                         = 0,
        OFF_HIGH                        = 1,
        CLOCK_1_HZ                      = 2,
        CLOCK_4_KHZ                     = 3,
        CLOCK_8_KHZ                     = 4,
        CLOCK_32_KHZ                    = 5
    };

private:
    //!
    //! \brief          Brief description
    //! \details        Long description
    //!
    enum class Register {
        SECONDS                         = 0x00,
        MINUTES                         = 0x01,
        HOURS                           = 0x02,
        DAY                             = 0x03,
        DATE                            = 0x04,
        MONTH                           = 0x05,
        YEAR                            = 0x06,
        CONTROL                         = 0x07,
        RAM_START                       = 0x08,
    };

    // -------------------------------------------------------------------------
    // Constructors ------------------------------------------------------------
public:

    //!
    //! \brief      Ds1307 class constructor
    //! \details    Creates a Ds1307 object.
    //!
    Ds1307(
            void
    );

    //!
    //! \brief      Ds1307 class destructor
    //! \details    Destroys a Ds1307 object.
    //!
    ~Ds1307(
            void
    );

    // -------------------------------------------------------------------------
    // Methods - Inherited methods ---------------------------------------------

public:
    // NONE

private:
    // NONE

protected:
    // NONE

    // -------------------------------------------------------------------------
    // Methods - Class own methods ---------------------------------------------

public:
    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \return true
    //! \return false
    //!
    bool_t clockStart(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \return true
    //! \return false
    //!
    bool_t clockStop(
            void
    );

    //!
    //! \brief          Brief description
    //! \details        Long description
    //! \return         Error              Return info
    //!
    Error getLastError(
            void
    );

    //!
    //! \brief      Initializes the device.
    //! \details    Performs the device initialization, checking if the device
    //!                 address is reponding. Since the DS1307 has no internal
    //!                 register to store it's device (or part) ID, there is no
    //!                 way to be sure if the device responding is actualy a
    //!                 DS1307 device.
    //! \param[in]  busHandler_p        pointer to the \ref{Bus} handler object
    //! \return true
    //! \return false
    //!
    bool_t init(
            Bus *busHandler_p
    );

    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      squareWave_p        Param description
    //! \return true
    //! \return false
    //!
    bool_t setSquareWaveGenerator(
            const SquareWave squareWave_p
    );


//     bool_t setControl(funsapeLibDs1307CountingStatus_t counting, funsapeLibDs1307SquareWaveGenerator_t squareWave, funsapeLibDs1307TimeFormat_t timeFormat);

    //     ///////////////    DATE HANDLING FUNCTIONS     ///////////////     //
    //!
    //! \brief      Reads the current date from device.
    //! \details    The function reads the current date from device.
    //! \param[out] year_p      pointer to the variable where the year will be saved
    //!                             in four digits format (2000-2099).
    //! \param[out] month_p     pointer to the variable where the month will be
    //!                             saved (1-12).
    //! \param[out] monthDay_p  pointer to the variable where the day of the month
    //!                             will be saved (1-31).
    //! \param[out] weekDay_p   pointer to the variable where the day of the week
    //!                             will be saved (1-7).
    //! \return true
    //! \return false
    //!
    bool_t getDate(
            uint16_t *year_p,
            uint8_t *month_p,
            uint8_t *monthDay_p,
            uint8_t *weekDay_p = nullptr
    );

    //!
    //! \brief      Reads the current date from device.
    //! \details    The function reads the current date from device.
    //! \param[out] dateTime_p  pointer to \ref{DateTime} variable where all the
    //!                 available data will ve saved.
    //! \return true
    //! \return false
    //!
    bool_t getDateTime(
            DateTime *dateTime_p
    );

    //!
    //! \brief      Set the date at the device.
    //! \details    The function sets the date at the device.
    //! \param[in]  year_p      variable containing the year (2000-2099).
    //! \param[in]  month_p     variable containing the month (1-12).
    //! \param[in]  monthDay_p  variable containing the day of the month (1-31).
    //! \return true
    //! \return false
    //!
    bool_t setDate(
            uint16_t year_p,
            uint8_t month_p,
            uint8_t monthDay_p
    );

    //!
    //! \brief      Set the date at the device.
    //! \details    The function sets the date at the device.
    //! \param[in]  dateTime_p  \ref{DateTime} object containing all the date and
    //!                 time information to be set an the device.
    //! \return true
    //! \return false
    //!
    bool_t setDateTime(
            DateTime dateTime_p
    );

    //     ///////////////    TIME HANDLING FUNCTIONS     ///////////////     //
    //!
    //! \brief      Reads the current time from the device.
    //! \details    Reads the current time from the device.
    //! \param[out] hours_p     pointer to the variable where the hours must be
    //!                 saved (0-23).
    //! \param[out] minutes_p   pointer to the variable where the minutes must be
    //!                 saved (0-59).
    //! \param[out] seconds_p   pointer to the variable where the seconds must be
    //!                 saved (0-59).
    //! \param[out] abbrev_p    pointer to the \ref{ds1307TimeAbbreviation_t}
    //!                 variable where the time format must be saved.
    //! \return true
    //! \return false
    //!
    bool_t getTime(
            uint8_t *hours_p,
            uint8_t *minutes_p,
            uint8_t *seconds_p,
            DateTime::TimeFormat timeFormat_p = DateTime::TimeFormat::FORMAT_24_HOURS,
            DateTime::AmPmFlag *amPmFlag_p = nullptr
    );

    //!
    //! \brief      Set the time at the device.
    //! \details    The function sets the time at the device.
    //! \param[in]  hours_p     variable containing the hours (0-23).
    //! \param[in]  minutes_p   variable containing the minutes (0-59).
    //! \param[in]  seconds_p   variable containing the seconds (0-59).
    //! \param[in]  timeFormat_p    \ref{DateTime::TimeFormat} variable
    //!                                 containing the time format.
    //! \param[in]  amPmFlag_p      \ref{DateTime::AmPmFlag} variable containing
    //!                                 containing the AM/PM Flag.
    //! \return true
    //! \return false
    //!
    bool_t setTime(
            uint8_t hours_p,
            uint8_t minutes_p,
            uint8_t seconds_p,
            DateTime::TimeFormat timeFormat_p = DateTime::TimeFormat::FORMAT_24_HOURS,
            DateTime::AmPmFlag amPmFlag_p = DateTime::AmPmFlag::AM
    );

    //     /////////////    RAM DATA HANDLING FUNCTIONS     /////////////     //
    //!
    //! \brief      Reads the device internal RAM.
    //! \details    Reads an amount of bytes from the device internal RAM.
    //! \param[in]  position_p  RAM start position address to be read (0-55).
    //! \param[out] buffer_p    pointer to the location to store the data read.
    //! \param[in]  size_p      number of bytes to read (0-55).
    //! \return true
    //! \return false
    //!
    bool_t getRamData(
            uint8_t position_p,
            uint8_t *buffer_p,
            uint8_t size_p = 1
    );

    //!
    //! \brief      Writes at the device internal RAM.
    //! \details    Writes an amount of bytes at the device internal RAM.
    //! \param[in]  position_p  RAM start position address to be read (0-55).
    //! \param[in]  buffer_p    pointer to the location containing the data do
    //!                             be written.
    //! \param[in] size_p      number of bytes to write (0-55).
    //! \return true
    //! \return false
    //!
    bool_t setRamData(
            uint8_t position_p,
            uint8_t *buffer_p,
            uint8_t size_p = 1
    );

private:
    void _clearData(
            void
    );
    bool_t _getData(
            void
    );
    bool_t _isInitialized(
            void
    );
    bool_t _sendData(
            void
    );
    bool_t _setCounting(
            bool_t counting_p
    );

public:
    //!
    //! \brief      Brief description
    //! \details    Long description
    //! \param      character_p             Param description
    //! \param      ddramChar_p             Param description
    //! \return     bool_t              Return info
    //!
    bool_t _writeCharacter(
            uint8_t character_p,
            bool_t ddramChar_p
    );

    // -------------------------------------------------------------------------
    // Properties --------------------------------------------------------------
public:
    // NONE

private:
    //     ////////////////    PERIPHERAL BUS HANDLER     ////////////////     //
    Bus             *_busHandler;

    //     /////////////////     CONTROL AND STATUS     /////////////////     //
    bool_t          _countingHalted         : 1;
    bool_t          _initialized            : 1;
    Error           _lastError;
    SquareWave      _squareWave;

    //     /////////////    DEVICE DATA (DATE AND TIME)     /////////////     //
    DateTime        _dateTime;

protected:
    // NONE

}; // class Ds1307

// =============================================================================
// Inlined class functions
// =============================================================================

// NONE

// =============================================================================
// External global variables
// =============================================================================

// NONE

// =============================================================================
// Include guard (END)
// =============================================================================

#endif  // __DS1307_HPP

// =============================================================================
// END OF FILE
// =============================================================================
