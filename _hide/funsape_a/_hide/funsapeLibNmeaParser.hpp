//!
//! \file           funsapeLibNmeaParser.hpp
//! \brief          NMEA parser module for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-12-16
//! \version        24.07
//! \copyright      license
//! \details        NMEA parser module for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// Include guard (START)
// =============================================================================

#ifndef __FUNSAPE_LIB_NMEA_PARSER_HPP
#define __FUNSAPE_LIB_NMEA_PARSER_HPP                   2407

// =============================================================================
// Dependencies
// =============================================================================

//     /////////////////    GLOBAL DEFINITIONS FILE     /////////////////     //

#include "../funsapeLibGlobalDefines.hpp"
#if !defined(__FUNSAPE_LIB_GLOBAL_DEFINES_HPP)
#   error "Global definitions file is corrupted!"
#elif __FUNSAPE_LIB_GLOBAL_DEFINES_HPP != __FUNSAPE_LIB_NMEA_PARSER_HPP
#   error "Version mismatch between file header and global definitions file!"
#endif

//     //////////////////     LIBRARY DEPENDENCIES     //////////////////     //

#include "../util/funsapeLibDebug.hpp"
#if !defined(__FUNSAPE_LIB_DEBUG_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_DEBUG_HPP != __FUNSAPE_LIB_NMEA_PARSER_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
#endif

#include "../util/funsapeLibCircularBuffer.hpp"
#if !defined(__FUNSAPE_LIB_CIRCULAR_BUFFER_HPP)
#   error "Header file (funsapeLibDebug.hpp) is corrupted!"
#elif __FUNSAPE_LIB_CIRCULAR_BUFFER_HPP != __FUNSAPE_LIB_NMEA_PARSER_HPP
#   error "Version mismatch between header file and library dependency (funsapeLibDebug.hpp)!"
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
// Classes
// =============================================================================

//!
//! \brief          NmeaParser class
//! \details        NmeaParser class.
//!
class NmeaParser
{
    // -------------------------------------------------------------------------
    // New data types ----------------------------------------------------------
public:

    enum class TalkerId : uint8_t {
        UNKNOWN                         = 0,    // NO TALKER DETECTED
        AB                              = 1,    // AB - Independent AIS Base Station
        AD                              = 2,    // AD - Dependent AIS Base Station
        AG                              = 3,    // AG - Heading Track Controller (Autopilot) - General
        AI                              = 4,    // AI - Mobile Class A or B AIS Station
        AN                              = 5,    // AN - AIS Aids to Navigation Station
        AP                              = 6,    // AP - Heading Track Controller (Autopilot) - Magnetic
        AR                              = 7,    // AR - AIS Receiving Station
        AS                              = 8,    // AS - AIS Station (ITU_R M1371, “Limited Base Station’)
        AT                              = 9,    // AT - AIS Transmitting Station
        AX                              = 10,   // AX - AIS Simplex Repeater Station
        BI                              = 11,   // BI - Bilge Systems
        BN                              = 12,   // BN - Bridge Navigational Watch Alarm System
        CA                              = 13,   // CA - Central Alarm Management
        CD                              = 14,   // CD - Communications - Digital Selective Calling (DSC)
        CR                              = 15,   // CR - Communications - Data Receiver
        CS                              = 16,   // CS - Communications - Satellite
        CT                              = 17,   // CT - Communications - Radio-Telephone (MF/HF)
        CV                              = 18,   // CV - Communications - Radio-Telephone (VHF)
        CX                              = 19,   // CX - Communications - Scanning Receiver
        DE                              = 20,   // DE - DECCA Navigator
        DF                              = 21,   // DF - Direction Finder
        DP                              = 22,   // DP - Dynamic Position
        DU                              = 23,   // DU - Duplex Repeater Station
        EC                              = 24,   // EC - Electronic Chart System (ECS)
        EI                              = 25,   // EI - Electronic Chart Display & Information System (ECDIS)
        EP                              = 26,   // EP - Emergency Position Indicating Beacon (EPIRB)
        ER                              = 27,   // ER - Engine Room Monitoring Systems
        FD                              = 28,   // FD - Fire Door Controller/Monitoring Point
        FE                              = 29,   // FE - Fire Extinguisher System
        FR                              = 30,   // FR - Fire Detection Point
        FS                              = 31,   // FS - Fire Sprinkler System
        GA                              = 32,   // GA - Navigation Sattelite System Receivers - Galileo Positioning System
        GB                              = 33,   // GB - Navigation Sattelite System Receivers - BDS (BeiDou System)
        GI                              = 34,   // GI - Navigation Sattelite System Receivers - NavIC (IRNSS)
        GL                              = 35,   // GL - Navigation Sattelite System Receivers - GLONASS Receiver
        GN                              = 36,   // GN - Navigation Sattelite System Receivers - Global Navigation Satellite System (GNSS)
        GP                              = 37,   // GP - Navigation Sattelite System Receivers - Global Positioning System (GPS)
        GQ                              = 38,   // GQ - Navigation Sattelite System Receivers - QZSS
        HC                              = 39,   // HC - Heading Sensors - Compass, Magnetic
        HD                              = 40,   // HD - Hull Door Controller/Monitoring Panel
        HE                              = 41,   // HE - Heading Sensors - Gyro, North Seeking
        HF                              = 42,   // HF - Heading Sensors - Fluxgate
        HN                              = 43,   // HN - Heading Sensors - Gyro, Non-North Seeking
        HS                              = 44,   // HS - Hull Stress Monitoring
        II                              = 45,   // II - Integrated Instrumentation
        IN                              = 46,   // IN - Integrated Navigation
        JA                              = 47,   // JA - Automation - Alarm and Monitoring System (reserved for future use)
        JB                              = 48,   // JB - Automation - Reefer Monitoring System (reserved for future use)
        JC                              = 49,   // JC - Automation - Power Management System (reserved for future use)
        JD                              = 50,   // JD - Automation - Propulsion Control System (reserved for future use)
        JE                              = 51,   // JE - Automation - Engine Control Console (reserved for future use)
        JF                              = 52,   // JF - Automation - Propulsion Boiler (reserved for future use)
        JG                              = 53,   // JG - Automation - Auxiliary Boiler (reserved for future use)
        JH                              = 54,   // JH - Automation - Electronic Governor System (reserved for future use)
        LC                              = 55,   // LC - Loran C
        MX                              = 56,   // MX - Multiplexer
        NL                              = 57,   // NL - Navigation Light Controller
        NV                              = 58,   // NV - Night Vision
        RA                              = 59,   // RA - Radar and/or Radar Plotting
        RB                              = 60,   // RB - Record Book (reserved for future use)
        RC                              = 61,   // RC - Propulsion Machinery Including Remote Control
        RI                              = 62,   // RI - Rudder Angle Indicator (reserved for future use)
        SA                              = 63,   // SA - Physical Shore AIS Station
        SC                              = 64,   // SC - Steering Control System/Device (reserved for future use)
        SD                              = 65,   // SD - Sounder, depth
        SG                              = 66,   // SG - Steering Gear/Steering Engine
        SN                              = 67,   // SN - Electronic Positioning System, other/general
        SS                              = 68,   // SS - Sounder, scanning
        TC                              = 69,   // TC - Track Control System (reserved for future use)
        TI                              = 70,   // TI - Turn Rate Indicator
        U0                              = 71,   // U0 - User configured talker identifier 0
        U1                              = 72,   // U1 - User configured talker identifier 1
        U2                              = 73,   // U2 - User configured talker identifier 2
        U3                              = 74,   // U3 - User configured talker identifier 3
        U4                              = 75,   // U4 - User configured talker identifier 4
        U5                              = 76,   // U5 - User configured talker identifier 5
        U6                              = 77,   // U6 - User configured talker identifier 6
        U7                              = 78,   // U7 - User configured talker identifier 7
        U8                              = 79,   // U8 - User configured talker identifier 8
        U9                              = 80,   // U9 - User configured talker identifier 9
        UP                              = 81,   // UP - Microprocessor  Controller
        VA                              = 82,   // VA - VHF Data Exchange Systems - ASM
        VD                              = 83,   // VD - Velocity Sensors - Doppler, other/general
        VM                              = 84,   // VM - Velocity Sensors - Speed Log, Water, Magnetic
        VR                              = 85,   // VR - Voyage Data Recorder
        VS                              = 86,   // VS - VHF Data Exchange Systems - Satellite
        VT                              = 87,   // VT - VHF Data Exchange Systems - Terrestrial
        VW                              = 88,   // VW - Velocity Sensors - Speed Log, Water Mechanical
        WD                              = 89,   // WD - Watertight Door Controller/Monitoring Panel
        WI                              = 90,   // WI - Weather Instruments
        WL                              = 91,   // WL - Water Level Detection Systems
        YX                              = 92,   // YX - Transducer
        ZA                              = 93,   // ZA - Timekeepers, Time/Date -Atomics Clock
        ZC                              = 94,   // ZC - Timekeepers, Time/Date -Chronometer
        ZQ                              = 95,   // ZQ - Timekeepers, Time/Date -Quartz
        ZV                              = 96,   // ZV - Timekeepers, Time/Date -Radio Update
        PROPRIETARY                     = 255   // P - Proprietary Code
    };

    enum class SentenceType : uint8_t {
        UNKNOWN                         = 0,    // NO MESSAGE DETECTED
        AAM                             = 1,    // AAM - Waypoint Arrival Alarm
        ALM                             = 2,    // ALM - GPS Almanac Data
        APA                             = 3,    // APA - Autopilot Sentence "A"
        APB                             = 4,    // APB - Autopilot Sentence "B"
        ASD                             = 5,    // ASD - Autopilot System Data
        BEC                             = 6,    // BEC - Bearing & Distance to Waypoint, Dead Reckoning
        BOD                             = 7,    // BOD - Bearing, Origin to Destination
        BWC                             = 8,    // BWC - Bearing & Distance to Waypoint, Great Circle
        BWR                             = 9,    // BWR - Bearing & Distance to Waypoint, Rhumb Line
        BWW                             = 10,   // BWW - Bearing, Waypoint to Waypoint
        DBT                             = 11,   // DBT - Depth Below Transducer
        DCN                             = 12,   // DCN - Decca Position
        DPT                             = 13,   // DPT - Depth
        DTM                             = 14,   // DTM - Datum being used
        FSI                             = 15,   // FSI - Frequency Set Information
        GGA                             = 16,   // GGA - Global Positioning System Fix Data
        GLC                             = 17,   // GLC - Geographic Position, Loran-C
        GLL                             = 18,   // GLL - Geographic Position, Latitude/Longitude
        GRS                             = 19,   // GRS - GPS Range Residuals
        GSA                             = 20,   // GSA - GPS DOP and Active Satellites
        GST                             = 21,   // GST - GPS Pseudorange Noise Statistics
        GSV                             = 22,   // GSV - GPS Satellites in View
        GXA                             = 23,   // GXA - TRANSIT Position
        HDG                             = 24,   // HDG - Heading, Deviation & Variation
        HDT                             = 25,   // HDT - Heading, True
        HSC                             = 26,   // HSC - Heading Steering Command
        LCD                             = 27,   // LCD - Loran-C Signal Data
        MSK                             = 28,   // MSK - send control for a beacon receiver
        MSS                             = 29,   // MSS - Beacon receiver status information.
        MTA                             = 30,   // MTA - Air Temperature (to be phased out)
        MTW                             = 31,   // MTW - Water Temperature
        MWD                             = 32,   // MWD - Wind Direction
        MWV                             = 33,   // MWV - Wind Speed and Angle
        OLN                             = 34,   // OLN - Omega Lane Numbers
        OSD                             = 35,   // OSD - Own Ship Data
        R00                             = 36,   // R00 - Waypoint active route (not standard)
        RMA                             = 37,   // RMA - Recommended Minimum Specific Loran-C Data
        RMB                             = 38,   // RMB - Recommended Minimum Navigation Information
        RMC                             = 39,   // RMC - Recommended Minimum Specific GPS/TRANSIT Data
        ROT                             = 40,   // ROT - Rate of Turn
        RPM                             = 41,   // RPM - Revolutions
        RSA                             = 42,   // RSA - Rudder Sensor Angle
        RSD                             = 43,   // RSD - RADAR System Data
        RTE                             = 44,   // RTE - Routes
        SFI                             = 45,   // SFI - Scanning Frequency Information
        STN                             = 46,   // STN - Multiple Data ID
        TRF                             = 47,   // TRF - Transit Fix Data
        TTM                             = 48,   // TTM - Tracked Target Message
        TXT                             = 49,   // TXT - Text Message
        VBW                             = 50,   // VBW - Dual Ground/Water Speed
        VDR                             = 51,   // VDR - Set and Drift
        VHW                             = 52,   // VHW - Water Speed and Heading
        VLW                             = 53,   // VLW - Distance Traveled through the Water
        VPW                             = 54,   // VPW - Speed, Measured Parallel to Wind
        VTG                             = 55,   // VTG - Track Made Good and Ground Speed
        WCV                             = 56,   // WCV - Waypoint Closure Velocity
        WNC                             = 57,   // WNC - Distance, Waypoint to Waypoint
        WPL                             = 58,   // WPL - Waypoint Location
        XDR                             = 59,   // XDR - Transducer Measurements
        XTC                             = 60,   // XTC - cross track error
        XTE                             = 61,   // XTE - Cross-Track Error, Measured
        XTR                             = 62,   // XTR - Cross-Track Error, Dead Reckoning
        ZDA                             = 63,   // ZDA - Time & Date
        ZFO                             = 64,   // ZFO - UTC & Time from Origin Waypoint
        ZTG                             = 65,   // ZTG - UTC & Time to Destination Waypoint
    };

private:
    enum class MessageState : uint8_t {
        SEARCHING_FOR_START_DELIMITER   = 0,
        SEARCHING_FOR_CR                = 1,
        SEARCHING_FOR_LF                = 2,
        WAITING_TO_PROCESS              = 3,
    };


    enum class DecoderState : uint16_t {
        IDLE                                 = 0x0000,
        GETTING_TALKER                       = 0x0001,
        GETTING_MESSAGE_TYPE                 = 0x0002,
        GETTING_DATA                         = 0x0003,
        GETTING_CHECKSUM                     = 0x0004,
        GETTING_TERMINATOR_CR                = 0x0005,
        GETTING_TERMINATOR_LF                = 0x0006,
        FRAME_COMPLETE                       = 0x0007,
        PROCESSING_DATA                      = 0x0008,
        DATA_READY                           = 0x0009,

        GETTING_GGA_UTC_TIME                 = 0x0800,
        GETTING_GGA_LATITUDE                 = 0x0801,
        GETTING_GGA_NS_INDICATOR             = 0x0802,
        GETTING_GGA_LONGITUDE                = 0x0803,
        GETTING_GGA_EW_INDICATOR             = 0x0804,
        GETTING_GGA_POSITION_FIX_INDICATOR   = 0x0805,
        GETTING_GGA_SATELLITES_USED          = 0x0806,
        GETTING_GGA_HORIZ_DILU_PRECISION     = 0x0807,
        GETTING_GGA_MSL_ALTITUDE             = 0x0808,
        GETTING_GGA_MSL_ALTITUDE_UNITS       = 0x0809,
        GETTING_GGA_GEOID_SEPARATION         = 0x080A,
        GETTING_GGA_GEOID_SEPARATION_UNITS   = 0x080B,
        GETTING_GGA_AGE_DIFF_CORR            = 0x080C,
        GETTING_GGA_DIFF_REF_STATION_ID      = 0x080D,

        GETTING_RMC_UTC_TIME                 = 0x1200,
        GETTING_RMC_STATUS                   = 0x1201,
        GETTING_RMC_LATITUDE                 = 0x1202,
        GETTING_RMC_NS_INDICATOR             = 0x1203,
        GETTING_RMC_LONGITUDE                = 0x1204,
        GETTING_RMC_EW_INDICATOR             = 0x1205,
        GETTING_RMC_SPEED_OVER_GROUND        = 0x1206,
        GETTING_RMC_COURSE_OVER_GROUND       = 0x1207,
        GETTING_RMC_DATE                     = 0x1208,
        GETTING_RMC_MODE                     = 0x1209,
    };

public:
    NmeaParser(
            void
    );

    ~NmeaParser(
            void
    );

public:
    Error getLastError(
            void
    );

    bool_t init(
            CircularBuffer<uint8_t> *circularBuffer_p,
            cuint8_t maxMessageSize_p = 82,
            cbool_t checksumEnabled_p = true
    );

    bool_t process(
            void
    );




    bool_t _pushIntoBuffer(uint8_t data);
    bool_t cancelProcess(void);
    bool_t flush(void);
    bool_t isClearToReceiveData(void);
    bool_t isGettingData(void);
    bool_t isNewDataReady(void);
    bool_t isReadyToProcessData(void);
    bool_t push(uint8_t data);
    bool_t pushBuffer(uint8_t *bufData, uint16_t bufSize);
    bool_t pushData(uint8_t data);
    bool_t setDataReadyCallback(void callbackFunction(void));
    bool_t startToDecodeData(void);
    bool_t startToReceiveData(void);
    SentenceType getSentenceType(void);
    TalkerId getTalkerId(void);
    uint16_t getState(void);



private:
    bool_t _getSentenceFromBuffer(
            void
    );
    bool_t _processSentence(
            void
    );
    void _decodeTalkerId(
            void
    );
    void _decodeSentenceType(
            void
    );



    bool_t      _checkInitialized(void);            // Check if parser is initialized
    bool_t      _checkLocked(void);                 // Check if parser buffer is locked
    void        _incrementState(void);              // Increment states machine
    bool_t      _parseSentenceAam(void);            // TODO Implement  this function
    bool_t      _parseSentenceAlm(void);            // TODO Implement  this function
    bool_t      _parseSentenceApa(void);            // TODO Implement  this function
    bool_t      _parseSentenceApb(void);            // TODO Implement  this function
    bool_t      _parseSentenceAsd(void);            // TODO Implement  this function
    bool_t      _parseSentenceBec(void);            // TODO Implement  this function
    bool_t      _parseSentenceBod(void);            // TODO Implement  this function
    bool_t      _parseSentenceBwc(void);            // TODO Implement  this function
    bool_t      _parseSentenceBwr(void);            // TODO Implement  this function
    bool_t      _parseSentenceBww(void);            // TODO Implement  this function
    bool_t      _parseSentenceDbt(void);            // TODO Implement  this function
    bool_t      _parseSentenceDcn(void);            // TODO Implement  this function
    bool_t      _parseSentenceDpt(void);            // TODO Implement  this function
    bool_t      _parseSentenceDtm(void);            // TODO Implement  this function
    bool_t      _parseSentenceFsi(void);            // TODO Implement  this function
    bool_t      _parseSentenceGga(void);            // TODO Implement  this function
    bool_t      _parseSentenceGlc(void);            // TODO Implement  this function
    bool_t      _parseSentenceGll(void);            // TODO Implement  this function
    bool_t      _parseSentenceGrs(void);            // TODO Implement  this function
    bool_t      _parseSentenceGsa(void);            // TODO Implement  this function
    bool_t      _parseSentenceGst(void);            // TODO Implement  this function
    bool_t      _parseSentenceGsv(void);            // TODO Implement  this function
    bool_t      _parseSentenceGxa(void);            // TODO Implement  this function
    bool_t      _parseSentenceHdg(void);            // TODO Implement  this function
    bool_t      _parseSentenceHdt(void);            // TODO Implement  this function
    bool_t      _parseSentenceHsc(void);            // TODO Implement  this function
    bool_t      _parseSentenceLcd(void);            // TODO Implement  this function
    bool_t      _parseSentenceMsk(void);            // TODO Implement  this function
    bool_t      _parseSentenceMss(void);            // TODO Implement  this function
    bool_t      _parseSentenceMta(void);            // TODO Implement  this function
    bool_t      _parseSentenceMtw(void);            // TODO Implement  this function
    bool_t      _parseSentenceMwd(void);            // TODO Implement  this function
    bool_t      _parseSentenceMwv(void);            // TODO Implement  this function
    bool_t      _parseSentenceOln(void);            // TODO Implement  this function
    bool_t      _parseSentenceOsd(void);            // TODO Implement  this function
    bool_t      _parseSentenceR00(void);            // TODO Implement  this function
    bool_t      _parseSentenceRma(void);            // TODO Implement  this function
    bool_t      _parseSentenceRmb(void);            // TODO Implement  this function
    bool_t      _parseSentenceRmc(void);
    bool_t      _parseSentenceRot(void);            // TODO Implement  this function
    bool_t      _parseSentenceRpm(void);            // TODO Implement  this function
    bool_t      _parseSentenceRsa(void);            // TODO Implement  this function
    bool_t      _parseSentenceRsd(void);            // TODO Implement  this function
    bool_t      _parseSentenceRte(void);            // TODO Implement  this function
    bool_t      _parseSentenceSfi(void);            // TODO Implement  this function
    bool_t      _parseSentenceStn(void);            // TODO Implement  this function
    bool_t      _parseSentenceTrf(void);            // TODO Implement  this function
    bool_t      _parseSentenceTtm(void);            // TODO Implement  this function
    bool_t      _parseSentenceTxt(void);            // TODO Implement  this function
    bool_t      _parseSentenceVbw(void);            // TODO Implement  this function
    bool_t      _parseSentenceVdr(void);            // TODO Implement  this function
    bool_t      _parseSentenceVhw(void);            // TODO Implement  this function
    bool_t      _parseSentenceVlw(void);            // TODO Implement  this function
    bool_t      _parseSentenceVpw(void);            // TODO Implement  this function
    bool_t      _parseSentenceVtg(void);            // TODO Implement  this function
    bool_t      _parseSentenceWcv(void);            // TODO Implement  this function
    bool_t      _parseSentenceWnc(void);            // TODO Implement  this function
    bool_t      _parseSentenceWpl(void);            // TODO Implement  this function
    bool_t      _parseSentenceXdr(void);            // TODO Implement  this function
    bool_t      _parseSentenceXtc(void);            // TODO Implement  this function
    bool_t      _parseSentenceXte(void);            // TODO Implement  this function
    bool_t      _parseSentenceXtr(void);            // TODO Implement  this function
    bool_t      _parseSentenceZda(void);            // TODO Implement  this function
    bool_t      _parseSentenceZfo(void);            // TODO Implement  this function
    bool_t      _parseSentenceZtg(void);            // TODO Implement  this function
    bool_t      _scanSentence(char *format);


    // NONE

private:
    Error                   _lastError;
    bool_t                  _initialized                : 1;
    bool_t                  _checksumEnabled            : 1;

    CircularBuffer<uint8_t> *_circularBuffer;

    uint8_t                 *_messageBuffer;
    bool_t                  _clearToReceiveData         : 1;
    bool_t                  _readyToProcessData         : 1;
    bool_t                  _newDataAvailable           : 1;
    uint8_t                 _messageIndex;
    uint8_t                 _messageLength;
    uint8_t                 _messageMaxSize;
    MessageState            _messageState;

    TalkerId                _talkerId;
    SentenceType            _sentenceType;

    // bool_t              _callbackFunctionEnable         : 1;
    // bool_t              _locked                         : 1;
    // bool_t              _messageDecoded                 : 1;
    // bool_t              _proprietaryMessage                     : 1;
    // DecoderState  _state;
    // uint8_t             _fieldLength;
    // void (* _dataReadyCallbackFunction)(void);

}; // class NmeaParser


// inlined NmeaParser::parserAtState_m &operator++(NmeaParser::parserAtState_m &auxEnum)
// {
//  auxEnum = (auxEnum == NmeaParser::PARSER_AT_STATE_MESSAGE_DECODED) ?
//            (NmeaParser::PARSER_AT_STATE_IDLE) :
//            (NmeaParser::parserAtState_m(auxEnum + 1));
//  return auxEnum;
// }

// inlined NmeaParser::parserAtState_m operator++(NmeaParser::parserAtState_m &auxEnum, int auxInt)
// {
//  NmeaParser::parserAtState_m auxInt2(auxEnum);
//  ++auxEnum;
//  return auxInt2;
// }


#endif
