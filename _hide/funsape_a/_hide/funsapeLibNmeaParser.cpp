//!
//! \file           funsapeLibNmeaParser.cpp
//! \brief          NMEA parser module for the FunSAPE AVR8 Library
//! \author         Leandro Schwarz (bladabuska+funsapeavr8lib@gmail.com)
//! \date           2024-12-16
//! \version        24.07
//! \copyright      license
//! \details        NMEA parser module for the FunSAPE AVR8 Library
//! \todo           Todo list
//!

// =============================================================================
// System file dependencies
// =============================================================================

#include "funsapeLibNmeaParser.hpp"
#if !defined(__FUNSAPE_LIB_NMEA_PARSER_HPP)
#    error "Header file is corrupted!"
#elif __FUNSAPE_LIB_NMEA_PARSER_HPP != 2407
#    error "Version mismatch between source and header files!"
#endif

// =============================================================================
// File exclusive - Constants
// =============================================================================

// NONE

// =============================================================================
// File exclusive - New data types
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Global variables
// =============================================================================

// NONE

// =============================================================================
// File exclusive - Macro-functions
// =============================================================================

// NONE

// =============================================================================
// Class constructors
// =============================================================================

NmeaParser::NmeaParser(void)
{
    // Mark passage for debugging purpose
    debugMark("NmeaParser::NmeaParser(void)", Debug::CodeIndex::NMEA_PARSER_MODULE);

    // Resets data members
    this->_initialized                  = false;
    this->_circularBuffer               = nullptr;
    this->_checksumEnabled              = false;
    this->_messageMaxSize               = 0;
    this->_messageIndex                 = 0;
    this->_messageLength                = 0;
    this->_messageBuffer                = nullptr;
    this->_messageState                 = MessageState::SEARCHING_FOR_START_DELIMITER;
    this->_clearToReceiveData           = false;
    this->_readyToProcessData           = false;
    this->_newDataAvailable             = false;
    this->_talkerId                     = TalkerId::UNKNOWN;
    this->_sentenceType                 = SentenceType::UNKNOWN;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::NMEA_PARSER_MODULE);
    return;
}

NmeaParser::~NmeaParser(void)
{
    // Mark passage for debugging purpose
    debugMark("NmeaParser::~NmeaParser(void)", Debug::CodeIndex::NMEA_PARSER_MODULE);

    // Returns successfully
    debugMessage(Error::NONE, Debug::CodeIndex::NMEA_PARSER_MODULE);
    return;
}

Error NmeaParser::getLastError(void)
{
    // Returns last error
    return this->_lastError;
}

bool_t NmeaParser::init(CircularBuffer<uint8_t> *circularBuffer_p, cuint8_t maxMessageSize_p, cbool_t checksumEnabled_p)
{
    // Mark passage for debugging purpose
    debugMark("NmeaParser::init(CircularBuffer<uint8_t> *, cuint8_t, cbool_t)", Debug::CodeIndex::NMEA_PARSER_MODULE);

    // Is there some memory allocated to buffer?
    if(isPointerValid(this->_messageBuffer)) {
        free(this->_messageBuffer);
    }

    // Resets data members
    this->_circularBuffer               = nullptr;
    this->_checksumEnabled              = false;
    this->_messageMaxSize               = 0;
    this->_messageIndex                 = 0;
    this->_messageLength                = 0;
    this->_messageBuffer                = nullptr;
    this->_messageState                 = MessageState::SEARCHING_FOR_START_DELIMITER;
    this->_clearToReceiveData           = false;
    this->_readyToProcessData           = false;
    this->_newDataAvailable             = false;
    this->_talkerId                     = TalkerId::UNKNOWN;
    this->_sentenceType                 = SentenceType::UNKNOWN;

    // Check function arguments for errors
    if(!isPointerValid(circularBuffer_p)) {
        // Returns error
        this->_lastError = Error::ARGUMENT_POINTER_NULL;
        debugMessage(Error::ARGUMENT_POINTER_NULL, Debug::CodeIndex::NMEA_PARSER_MODULE);
        return false;
    }
    if(maxMessageSize_p < 10) {
        // Returns error
        this->_lastError = Error::BUFFER_SIZE_TOO_SMALL;
        debugMessage(Error::BUFFER_SIZE_TOO_SMALL, Debug::CodeIndex::NMEA_PARSER_MODULE);
        return false;
    }

    // Allocates memory
    this->_messageBuffer = (uint8_t *)calloc(maxMessageSize_p, sizeof(uint8_t));
    if(!isPointerValid(this->_messageBuffer)) {
        // Returns error
        this->_lastError = Error::MEMORY_ALLOCATION;
        debugMessage(Error::MEMORY_ALLOCATION, Debug::CodeIndex::NMEA_PARSER_MODULE);
        return false;
    }

    // Update data members
    this->_circularBuffer               = circularBuffer_p;
    this->_checksumEnabled              = checksumEnabled_p;
    this->_messageMaxSize               = maxMessageSize_p;
    this->_initialized                  = true;

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::NMEA_PARSER_MODULE);
    return true;
}

bool_t NmeaParser::_getSentenceFromBuffer(void)
{
    // Local variables
    uint8_t aux8 = 0;

    // Get data from circular buffer
    while(this->_clearToReceiveData) {
        // Breaks - There is no data in the circular buffer
        if(this->_circularBuffer->isEmpty()) {
            break;
        }
        // Gets character from circular buffer
        if(!this->_circularBuffer->pop(&aux8)) {
            // Returns error
            this->_lastError = this->_circularBuffer->getLastError();
            debugMessage(this->_lastError, Debug::CodeIndex::NMEA_PARSER_MODULE);
            return false;
        }
        // Process character
        switch(this->_messageState) {
        case MessageState::SEARCHING_FOR_START_DELIMITER:
            this->_readyToProcessData = false;
            this->_newDataAvailable = false;
            this->_messageIndex = 0;
            // Ignores everything that is not a start delimiter
            if(aux8 == '$') {
                this->_messageBuffer[this->_messageIndex++] = aux8;
                this->_messageState = MessageState::SEARCHING_FOR_CR;
            }
            break;
        case MessageState::SEARCHING_FOR_CR:
            // Message buffer is full
            if(this->_messageIndex >= this->_messageMaxSize) {
                // Returns error
                this->_lastError = Error::BUFFER_FULL;
                debugMessage(Error::BUFFER_FULL, Debug::CodeIndex::NMEA_PARSER_MODULE);
            }
            // Process CR character
            if(aux8 == '\r') {
                this->_messageState = MessageState::SEARCHING_FOR_LF;
            } else {    // Process other that CR character
                this->_messageBuffer[this->_messageIndex++] = aux8;
            }
            break;
        case MessageState::SEARCHING_FOR_LF:
            // Process LF character
            if(aux8 == '\n') {
                this->_clearToReceiveData = false;
                this->_readyToProcessData = true;
                this->_messageState = MessageState::WAITING_TO_PROCESS;
                this->_messageLength = this->_messageIndex + 1;
                this->_messageIndex = 0;
            } else {
                // Error - frame error
                // Returns error
                this->_lastError = Error::FRAME_ERROR;
                debugMessage(Error::FRAME_ERROR, Debug::CodeIndex::NMEA_PARSER_MODULE);
                return false;
            }
            break;
        case MessageState::WAITING_TO_PROCESS:
            this->_clearToReceiveData = false;
            break;
        }
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::NMEA_PARSER_MODULE);
    return true;
}

bool_t NmeaParser::process(void)
{
    // Mark passage for debugging purpose
    debugMark("NmeaParser::process(void)", Debug::CodeIndex::NMEA_PARSER_MODULE);

    // CHECK FOR ERROR - Not initialized
    if(!this->_initialized) {
        // Returns error
        this->_lastError = Error::NOT_INITIALIZED;
        debugMessage(Error::NOT_INITIALIZED, Debug::CodeIndex::NMEA_PARSER_MODULE);
        return false;
    }

    // Get sentence from circular buffer
    if(!this->_getSentenceFromBuffer()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::NMEA_PARSER_MODULE);
        return false;
    }

    // Process sentence
    if(!this->_processSentence()) {
        // Returns error
        debugMessage(this->_lastError, Debug::CodeIndex::NMEA_PARSER_MODULE);
        return false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::NMEA_PARSER_MODULE);
    return true;
}

bool_t NmeaParser::_processSentence(void)
{
    // Local variables
    bool_t auxBool = false;

    // Ready to process data
    if(this->_readyToProcessData) {
        // Get talker ID
        this->_decodeTalkerId();
        // Get message type
        this->_decodeSentenceType();
        // Process message
        switch(this->_sentenceType) {
        case SentenceType::AAM:     auxBool = this->_parseSentenceAam(); break;
        case SentenceType::ALM:     auxBool = this->_parseSentenceAlm(); break;
        case SentenceType::APA:     auxBool = this->_parseSentenceApa(); break;
        case SentenceType::APB:     auxBool = this->_parseSentenceApb(); break;
        case SentenceType::ASD:     auxBool = this->_parseSentenceAsd(); break;
        case SentenceType::BEC:     auxBool = this->_parseSentenceBec(); break;
        case SentenceType::BOD:     auxBool = this->_parseSentenceBod(); break;
        case SentenceType::BWC:     auxBool = this->_parseSentenceBwc(); break;
        case SentenceType::BWR:     auxBool = this->_parseSentenceBwr(); break;
        case SentenceType::BWW:     auxBool = this->_parseSentenceBww(); break;
        case SentenceType::DBT:     auxBool = this->_parseSentenceDbt(); break;
        case SentenceType::DCN:     auxBool = this->_parseSentenceDcn(); break;
        case SentenceType::DPT:     auxBool = this->_parseSentenceDpt(); break;
        case SentenceType::DTM:     auxBool = this->_parseSentenceDtm(); break;
        case SentenceType::FSI:     auxBool = this->_parseSentenceFsi(); break;
        case SentenceType::GGA:     auxBool = this->_parseSentenceGga(); break;
        case SentenceType::GLC:     auxBool = this->_parseSentenceGlc(); break;
        case SentenceType::GLL:     auxBool = this->_parseSentenceGll(); break;
        case SentenceType::GRS:     auxBool = this->_parseSentenceGrs(); break;
        case SentenceType::GSA:     auxBool = this->_parseSentenceGsa(); break;
        case SentenceType::GST:     auxBool = this->_parseSentenceGst(); break;
        case SentenceType::GSV:     auxBool = this->_parseSentenceGsv(); break;
        case SentenceType::GXA:     auxBool = this->_parseSentenceGxa(); break;
        case SentenceType::HDG:     auxBool = this->_parseSentenceHdg(); break;
        case SentenceType::HDT:     auxBool = this->_parseSentenceHdt(); break;
        case SentenceType::HSC:     auxBool = this->_parseSentenceHsc(); break;
        case SentenceType::LCD:     auxBool = this->_parseSentenceLcd(); break;
        case SentenceType::MSK:     auxBool = this->_parseSentenceMsk(); break;
        case SentenceType::MSS:     auxBool = this->_parseSentenceMss(); break;
        case SentenceType::MTA:     auxBool = this->_parseSentenceMta(); break;
        case SentenceType::MTW:     auxBool = this->_parseSentenceMtw(); break;
        case SentenceType::MWD:     auxBool = this->_parseSentenceMwd(); break;
        case SentenceType::MWV:     auxBool = this->_parseSentenceMwv(); break;
        case SentenceType::OLN:     auxBool = this->_parseSentenceOln(); break;
        case SentenceType::OSD:     auxBool = this->_parseSentenceOsd(); break;
        case SentenceType::R00:     auxBool = this->_parseSentenceR00(); break;
        case SentenceType::RMA:     auxBool = this->_parseSentenceRma(); break;
        case SentenceType::RMB:     auxBool = this->_parseSentenceRmb(); break;
        case SentenceType::RMC:     auxBool = this->_parseSentenceRmc(); break;
        case SentenceType::ROT:     auxBool = this->_parseSentenceRot(); break;
        case SentenceType::RPM:     auxBool = this->_parseSentenceRpm(); break;
        case SentenceType::RSA:     auxBool = this->_parseSentenceRsa(); break;
        case SentenceType::RSD:     auxBool = this->_parseSentenceRsd(); break;
        case SentenceType::RTE:     auxBool = this->_parseSentenceRte(); break;
        case SentenceType::SFI:     auxBool = this->_parseSentenceSfi(); break;
        case SentenceType::STN:     auxBool = this->_parseSentenceStn(); break;
        case SentenceType::TRF:     auxBool = this->_parseSentenceTrf(); break;
        case SentenceType::TTM:     auxBool = this->_parseSentenceTtm(); break;
        case SentenceType::TXT:     auxBool = this->_parseSentenceTxt(); break;
        case SentenceType::VBW:     auxBool = this->_parseSentenceVbw(); break;
        case SentenceType::VDR:     auxBool = this->_parseSentenceVdr(); break;
        case SentenceType::VHW:     auxBool = this->_parseSentenceVhw(); break;
        case SentenceType::VLW:     auxBool = this->_parseSentenceVlw(); break;
        case SentenceType::VPW:     auxBool = this->_parseSentenceVpw(); break;
        case SentenceType::VTG:     auxBool = this->_parseSentenceVtg(); break;
        case SentenceType::WCV:     auxBool = this->_parseSentenceWcv(); break;
        case SentenceType::WNC:     auxBool = this->_parseSentenceWnc(); break;
        case SentenceType::WPL:     auxBool = this->_parseSentenceWpl(); break;
        case SentenceType::XDR:     auxBool = this->_parseSentenceXdr(); break;
        case SentenceType::XTC:     auxBool = this->_parseSentenceXtc(); break;
        case SentenceType::XTE:     auxBool = this->_parseSentenceXte(); break;
        case SentenceType::XTR:     auxBool = this->_parseSentenceXtr(); break;
        case SentenceType::ZDA:     auxBool = this->_parseSentenceZda(); break;
        case SentenceType::ZFO:     auxBool = this->_parseSentenceZfo(); break;
        case SentenceType::ZTG:     auxBool = this->_parseSentenceZtg(); break;
        default:
            // Returns error
            this->_lastError = Error::NMEA_SENTENCE_UNKNOWN;
            return false;
        }
        if(!auxBool) {
            // Return error
            return false;
        }
        // Data processed successfully
        this->_newDataAvailable = true;
        this->_readyToProcessData = false;
        this->_clearToReceiveData = false;
    }

    // Returns successfully
    this->_lastError = Error::NONE;
    debugMessage(Error::NONE, Debug::CodeIndex::NMEA_PARSER_MODULE);
    return true;
}

void NmeaParser::_decodeTalkerId(void)
{
    // Local variables
    uint8_t auxStr[3];

    // Decodes talker id
    if(this->_messageBuffer[1] == 'P') {
        // Proprietary talker id
        this->_talkerId = TalkerId::PROPRIETARY;
        return;
    }

    // Prepare string
    auxStr[0] = this->_messageBuffer[1];
    auxStr[1] = this->_messageBuffer[2];
    auxStr[2] = '\0';
    // Decodes talker id
    if(strcmp((char *)auxStr, "AB")) {
        this->_talkerId = TalkerId::AB;
    } else if(strcmp((char *)auxStr, "AD")) {
        this->_talkerId = TalkerId::AD;
    } else if(strcmp((char *)auxStr, "AG")) {
        this->_talkerId = TalkerId::AG;
    } else if(strcmp((char *)auxStr, "AI")) {
        this->_talkerId = TalkerId::AI;
    } else if(strcmp((char *)auxStr, "AN")) {
        this->_talkerId = TalkerId::AN;
    } else if(strcmp((char *)auxStr, "AP")) {
        this->_talkerId = TalkerId::AP;
    } else if(strcmp((char *)auxStr, "AR")) {
        this->_talkerId = TalkerId::AR;
    } else if(strcmp((char *)auxStr, "AS")) {
        this->_talkerId = TalkerId::AS;
    } else if(strcmp((char *)auxStr, "AT")) {
        this->_talkerId = TalkerId::AT;
    } else if(strcmp((char *)auxStr, "AX")) {
        this->_talkerId = TalkerId::AX;
    } else if(strcmp((char *)auxStr, "BI")) {
        this->_talkerId = TalkerId::BI;
    } else if(strcmp((char *)auxStr, "BN")) {
        this->_talkerId = TalkerId::BN;
    } else if(strcmp((char *)auxStr, "CA")) {
        this->_talkerId = TalkerId::CA;
    } else if(strcmp((char *)auxStr, "CD")) {
        this->_talkerId = TalkerId::CD;
    } else if(strcmp((char *)auxStr, "CR")) {
        this->_talkerId = TalkerId::CR;
    } else if(strcmp((char *)auxStr, "CS")) {
        this->_talkerId = TalkerId::CS;
    } else if(strcmp((char *)auxStr, "CT")) {
        this->_talkerId = TalkerId::CT;
    } else if(strcmp((char *)auxStr, "CV")) {
        this->_talkerId = TalkerId::CV;
    } else if(strcmp((char *)auxStr, "CX")) {
        this->_talkerId = TalkerId::CX;
    } else if(strcmp((char *)auxStr, "DE")) {
        this->_talkerId = TalkerId::DE;
    } else if(strcmp((char *)auxStr, "DF")) {
        this->_talkerId = TalkerId::DF;
    } else if(strcmp((char *)auxStr, "DP")) {
        this->_talkerId = TalkerId::DP;
    } else if(strcmp((char *)auxStr, "DU")) {
        this->_talkerId = TalkerId::DU;
    } else if(strcmp((char *)auxStr, "EC")) {
        this->_talkerId = TalkerId::EC;
    } else if(strcmp((char *)auxStr, "EI")) {
        this->_talkerId = TalkerId::EI;
    } else if(strcmp((char *)auxStr, "EP")) {
        this->_talkerId = TalkerId::EP;
    } else if(strcmp((char *)auxStr, "ER")) {
        this->_talkerId = TalkerId::ER;
    } else if(strcmp((char *)auxStr, "FD")) {
        this->_talkerId = TalkerId::FD;
    } else if(strcmp((char *)auxStr, "FE")) {
        this->_talkerId = TalkerId::FE;
    } else if(strcmp((char *)auxStr, "FR")) {
        this->_talkerId = TalkerId::FR;
    } else if(strcmp((char *)auxStr, "FS")) {
        this->_talkerId = TalkerId::FS;
    } else if(strcmp((char *)auxStr, "GA")) {
        this->_talkerId = TalkerId::GA;
    } else if(strcmp((char *)auxStr, "GB")) {
        this->_talkerId = TalkerId::GB;
    } else if(strcmp((char *)auxStr, "GI")) {
        this->_talkerId = TalkerId::GI;
    } else if(strcmp((char *)auxStr, "GL")) {
        this->_talkerId = TalkerId::GL;
    } else if(strcmp((char *)auxStr, "GN")) {
        this->_talkerId = TalkerId::GN;
    } else if(strcmp((char *)auxStr, "GP")) {
        this->_talkerId = TalkerId::GP;
    } else if(strcmp((char *)auxStr, "GQ")) {
        this->_talkerId = TalkerId::GQ;
    } else if(strcmp((char *)auxStr, "HC")) {
        this->_talkerId = TalkerId::HC;
    } else if(strcmp((char *)auxStr, "HD")) {
        this->_talkerId = TalkerId::HD;
    } else if(strcmp((char *)auxStr, "HE")) {
        this->_talkerId = TalkerId::HE;
    } else if(strcmp((char *)auxStr, "HF")) {
        this->_talkerId = TalkerId::HF;
    } else if(strcmp((char *)auxStr, "HN")) {
        this->_talkerId = TalkerId::HN;
    } else if(strcmp((char *)auxStr, "HS")) {
        this->_talkerId = TalkerId::HS;
    } else if(strcmp((char *)auxStr, "II")) {
        this->_talkerId = TalkerId::II;
    } else if(strcmp((char *)auxStr, "IN")) {
        this->_talkerId = TalkerId::IN;
    } else if(strcmp((char *)auxStr, "JA")) {
        this->_talkerId = TalkerId::JA;
    } else if(strcmp((char *)auxStr, "JB")) {
        this->_talkerId = TalkerId::JB;
    } else if(strcmp((char *)auxStr, "JC")) {
        this->_talkerId = TalkerId::JC;
    } else if(strcmp((char *)auxStr, "JD")) {
        this->_talkerId = TalkerId::JD;
    } else if(strcmp((char *)auxStr, "JE")) {
        this->_talkerId = TalkerId::JE;
    } else if(strcmp((char *)auxStr, "JF")) {
        this->_talkerId = TalkerId::JF;
    } else if(strcmp((char *)auxStr, "JG")) {
        this->_talkerId = TalkerId::JG;
    } else if(strcmp((char *)auxStr, "JH")) {
        this->_talkerId = TalkerId::JH;
    } else if(strcmp((char *)auxStr, "LC")) {
        this->_talkerId = TalkerId::LC;
    } else if(strcmp((char *)auxStr, "MX")) {
        this->_talkerId = TalkerId::MX;
    } else if(strcmp((char *)auxStr, "NL")) {
        this->_talkerId = TalkerId::NL;
    } else if(strcmp((char *)auxStr, "NV")) {
        this->_talkerId = TalkerId::NV;
    } else if(strcmp((char *)auxStr, "RA")) {
        this->_talkerId = TalkerId::RA;
    } else if(strcmp((char *)auxStr, "RB")) {
        this->_talkerId = TalkerId::RB;
    } else if(strcmp((char *)auxStr, "RC")) {
        this->_talkerId = TalkerId::RC;
    } else if(strcmp((char *)auxStr, "RI")) {
        this->_talkerId = TalkerId::RI;
    } else if(strcmp((char *)auxStr, "SA")) {
        this->_talkerId = TalkerId::SA;
    } else if(strcmp((char *)auxStr, "SC")) {
        this->_talkerId = TalkerId::SC;
    } else if(strcmp((char *)auxStr, "SD")) {
        this->_talkerId = TalkerId::SD;
    } else if(strcmp((char *)auxStr, "SG")) {
        this->_talkerId = TalkerId::SG;
    } else if(strcmp((char *)auxStr, "SN")) {
        this->_talkerId = TalkerId::SN;
    } else if(strcmp((char *)auxStr, "SS")) {
        this->_talkerId = TalkerId::SS;
    } else if(strcmp((char *)auxStr, "TC")) {
        this->_talkerId = TalkerId::TC;
    } else if(strcmp((char *)auxStr, "TI")) {
        this->_talkerId = TalkerId::TI;
    } else if(strcmp((char *)auxStr, "U0")) {
        this->_talkerId = TalkerId::U0;
    } else if(strcmp((char *)auxStr, "U1")) {
        this->_talkerId = TalkerId::U1;
    } else if(strcmp((char *)auxStr, "U2")) {
        this->_talkerId = TalkerId::U2;
    } else if(strcmp((char *)auxStr, "U3")) {
        this->_talkerId = TalkerId::U3;
    } else if(strcmp((char *)auxStr, "U4")) {
        this->_talkerId = TalkerId::U4;
    } else if(strcmp((char *)auxStr, "U5")) {
        this->_talkerId = TalkerId::U5;
    } else if(strcmp((char *)auxStr, "U6")) {
        this->_talkerId = TalkerId::U6;
    } else if(strcmp((char *)auxStr, "U7")) {
        this->_talkerId = TalkerId::U7;
    } else if(strcmp((char *)auxStr, "U8")) {
        this->_talkerId = TalkerId::U8;
    } else if(strcmp((char *)auxStr, "U9")) {
        this->_talkerId = TalkerId::U9;
    } else if(strcmp((char *)auxStr, "UP")) {
        this->_talkerId = TalkerId::UP;
    } else if(strcmp((char *)auxStr, "VA")) {
        this->_talkerId = TalkerId::VA;
    } else if(strcmp((char *)auxStr, "VD")) {
        this->_talkerId = TalkerId::VD;
    } else if(strcmp((char *)auxStr, "VM")) {
        this->_talkerId = TalkerId::VM;
    } else if(strcmp((char *)auxStr, "VR")) {
        this->_talkerId = TalkerId::VR;
    } else if(strcmp((char *)auxStr, "VS")) {
        this->_talkerId = TalkerId::VS;
    } else if(strcmp((char *)auxStr, "VT")) {
        this->_talkerId = TalkerId::VT;
    } else if(strcmp((char *)auxStr, "VW")) {
        this->_talkerId = TalkerId::VW;
    } else if(strcmp((char *)auxStr, "WD")) {
        this->_talkerId = TalkerId::WD;
    } else if(strcmp((char *)auxStr, "WI")) {
        this->_talkerId = TalkerId::WI;
    } else if(strcmp((char *)auxStr, "WL")) {
        this->_talkerId = TalkerId::WL;
    } else if(strcmp((char *)auxStr, "YX")) {
        this->_talkerId = TalkerId::YX;
    } else if(strcmp((char *)auxStr, "ZA")) {
        this->_talkerId = TalkerId::ZA;
    } else if(strcmp((char *)auxStr, "ZC")) {
        this->_talkerId = TalkerId::ZC;
    } else if(strcmp((char *)auxStr, "ZQ")) {
        this->_talkerId = TalkerId::ZQ;
    } else if(strcmp((char *)auxStr, "ZV")) {
        this->_talkerId = TalkerId::ZV;
    } else {
        this->_talkerId = TalkerId::UNKNOWN;
    }

    return;
}

void NmeaParser::_decodeSentenceType(void)
{
    // Local variables
    uint8_t auxStr[4];

    // Prepare string
    if(this->_talkerId == TalkerId::PROPRIETARY) {
        auxStr[0] = this->_messageBuffer[2];
        auxStr[1] = this->_messageBuffer[3];
        auxStr[2] = this->_messageBuffer[4];
        auxStr[3] = '\0';
    } else {
        auxStr[0] = this->_messageBuffer[3];
        auxStr[1] = this->_messageBuffer[4];
        auxStr[2] = this->_messageBuffer[5];
        auxStr[3] = '\0';
    }

    // Decodes message type
    if(strcmp((char *)auxStr, "AAM")) {
        this->_sentenceType = SentenceType::AAM;
    } else if(strcmp((char *)auxStr, "ALM")) {
        this->_sentenceType = SentenceType::ALM;
    } else if(strcmp((char *)auxStr, "APA")) {
        this->_sentenceType = SentenceType::APA;
    } else if(strcmp((char *)auxStr, "APB")) {
        this->_sentenceType = SentenceType::APB;
    } else if(strcmp((char *)auxStr, "ASD")) {
        this->_sentenceType = SentenceType::ASD;
    } else if(strcmp((char *)auxStr, "BEC")) {
        this->_sentenceType = SentenceType::BEC;
    } else if(strcmp((char *)auxStr, "BOD")) {
        this->_sentenceType = SentenceType::BOD;
    } else if(strcmp((char *)auxStr, "BWC")) {
        this->_sentenceType = SentenceType::BWC;
    } else if(strcmp((char *)auxStr, "BWR")) {
        this->_sentenceType = SentenceType::BWR;
    } else if(strcmp((char *)auxStr, "BWW")) {
        this->_sentenceType = SentenceType::BWW;
    } else if(strcmp((char *)auxStr, "DBT")) {
        this->_sentenceType = SentenceType::DBT;
    } else if(strcmp((char *)auxStr, "DCN")) {
        this->_sentenceType = SentenceType::DCN;
    } else if(strcmp((char *)auxStr, "DPT")) {
        this->_sentenceType = SentenceType::DPT;
    } else if(strcmp((char *)auxStr, "DTM")) {
        this->_sentenceType = SentenceType::DTM;
    } else if(strcmp((char *)auxStr, "FSI")) {
        this->_sentenceType = SentenceType::FSI;
    } else if(strcmp((char *)auxStr, "GGA")) {
        this->_sentenceType = SentenceType::GGA;
    } else if(strcmp((char *)auxStr, "GLC")) {
        this->_sentenceType = SentenceType::GLC;
    } else if(strcmp((char *)auxStr, "GLL")) {
        this->_sentenceType = SentenceType::GLL;
    } else if(strcmp((char *)auxStr, "GRS")) {
        this->_sentenceType = SentenceType::GRS;
    } else if(strcmp((char *)auxStr, "GSA")) {
        this->_sentenceType = SentenceType::GSA;
    } else if(strcmp((char *)auxStr, "GST")) {
        this->_sentenceType = SentenceType::GST;
    } else if(strcmp((char *)auxStr, "GSV")) {
        this->_sentenceType = SentenceType::GSV;
    } else if(strcmp((char *)auxStr, "GXA")) {
        this->_sentenceType = SentenceType::GXA;
    } else if(strcmp((char *)auxStr, "HDG")) {
        this->_sentenceType = SentenceType::HDG;
    } else if(strcmp((char *)auxStr, "HDT")) {
        this->_sentenceType = SentenceType::HDT;
    } else if(strcmp((char *)auxStr, "HSC")) {
        this->_sentenceType = SentenceType::HSC;
    } else if(strcmp((char *)auxStr, "LCD")) {
        this->_sentenceType = SentenceType::LCD;
    } else if(strcmp((char *)auxStr, "MSK")) {
        this->_sentenceType = SentenceType::MSK;
    } else if(strcmp((char *)auxStr, "MSS")) {
        this->_sentenceType = SentenceType::MSS;
    } else if(strcmp((char *)auxStr, "MTA")) {
        this->_sentenceType = SentenceType::MTA;
    } else if(strcmp((char *)auxStr, "MTW")) {
        this->_sentenceType = SentenceType::MTW;
    } else if(strcmp((char *)auxStr, "MWD")) {
        this->_sentenceType = SentenceType::MWD;
    } else if(strcmp((char *)auxStr, "MWV")) {
        this->_sentenceType = SentenceType::MWV;
    } else if(strcmp((char *)auxStr, "OLN")) {
        this->_sentenceType = SentenceType::OLN;
    } else if(strcmp((char *)auxStr, "OSD")) {
        this->_sentenceType = SentenceType::OSD;
    } else if(strcmp((char *)auxStr, "R00")) {
        this->_sentenceType = SentenceType::R00;
    } else if(strcmp((char *)auxStr, "RMA")) {
        this->_sentenceType = SentenceType::RMA;
    } else if(strcmp((char *)auxStr, "RMB")) {
        this->_sentenceType = SentenceType::RMB;
    } else if(strcmp((char *)auxStr, "RMC")) {
        this->_sentenceType = SentenceType::RMC;
    } else if(strcmp((char *)auxStr, "ROT")) {
        this->_sentenceType = SentenceType::ROT;
    } else if(strcmp((char *)auxStr, "RPM")) {
        this->_sentenceType = SentenceType::RPM;
    } else if(strcmp((char *)auxStr, "RSA")) {
        this->_sentenceType = SentenceType::RSA;
    } else if(strcmp((char *)auxStr, "RSD")) {
        this->_sentenceType = SentenceType::RSD;
    } else if(strcmp((char *)auxStr, "RTE")) {
        this->_sentenceType = SentenceType::RTE;
    } else if(strcmp((char *)auxStr, "SFI")) {
        this->_sentenceType = SentenceType::SFI;
    } else if(strcmp((char *)auxStr, "STN")) {
        this->_sentenceType = SentenceType::STN;
    } else if(strcmp((char *)auxStr, "TRF")) {
        this->_sentenceType = SentenceType::TRF;
    } else if(strcmp((char *)auxStr, "TTM")) {
        this->_sentenceType = SentenceType::TTM;
    } else if(strcmp((char *)auxStr, "TXT")) {
        this->_sentenceType = SentenceType::TXT;
    } else if(strcmp((char *)auxStr, "VBW")) {
        this->_sentenceType = SentenceType::VBW;
    } else if(strcmp((char *)auxStr, "VDR")) {
        this->_sentenceType = SentenceType::VDR;
    } else if(strcmp((char *)auxStr, "VHW")) {
        this->_sentenceType = SentenceType::VHW;
    } else if(strcmp((char *)auxStr, "VLW")) {
        this->_sentenceType = SentenceType::VLW;
    } else if(strcmp((char *)auxStr, "VPW")) {
        this->_sentenceType = SentenceType::VPW;
    } else if(strcmp((char *)auxStr, "VTG")) {
        this->_sentenceType = SentenceType::VTG;
    } else if(strcmp((char *)auxStr, "WCV")) {
        this->_sentenceType = SentenceType::WCV;
    } else if(strcmp((char *)auxStr, "WNC")) {
        this->_sentenceType = SentenceType::WNC;
    } else if(strcmp((char *)auxStr, "WPL")) {
        this->_sentenceType = SentenceType::WPL;
    } else if(strcmp((char *)auxStr, "XDR")) {
        this->_sentenceType = SentenceType::XDR;
    } else if(strcmp((char *)auxStr, "XTC")) {
        this->_sentenceType = SentenceType::XTC;
    } else if(strcmp((char *)auxStr, "XTE")) {
        this->_sentenceType = SentenceType::XTE;
    } else if(strcmp((char *)auxStr, "XTR")) {
        this->_sentenceType = SentenceType::XTR;
    } else if(strcmp((char *)auxStr, "ZDA")) {
        this->_sentenceType = SentenceType::ZDA;
    } else if(strcmp((char *)auxStr, "ZFO")) {
        this->_sentenceType = SentenceType::ZFO;
    } else if(strcmp((char *)auxStr, "ZTG")) {
        this->_sentenceType = SentenceType::ZTG;
    } else {
        this->_sentenceType = SentenceType::UNKNOWN;
    }

    return;
}
