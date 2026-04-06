# ##############################################################################
# Sample Makefile for AVR applications in C and C++
# Leandro Schwarz
# v2.0
# ##############################################################################

# ==============================================================================
# Environment variables
# ==============================================================================

# ------------------------------------------------------------------------------
# Received through application -------------------------------------------------

BUILD_DIR								?= build
BUILD_NAME								?= application
COMPILE_C_AS_CPP						?= 0
COMPILER_DEBUG							?= 0
COMPILER_OPT							?= -Og
COMPILER_PATH							?=
COMPILER_STD_C							?= c11
COMPILER_STD_CPP						?= c++14
EXCLUDE_DIRS							?= _hide/ doc/ Release/ temp/
LIBRARY_PATH							?=
MCU_DEVICE_NAME							?= atmega328p
PROGRAMMER_CONFIG_FILE					?= avrdude.conf
PROGRAMMER_TYPE							?= arduino
USER_DEFINES_ASM						?=
USER_DEFINES_C							?=
USER_DEFINES_CPP						?=
USER_FLAGS_ASM							?=
USER_FLAGS_C							?= -Wno-switch
USER_FLAGS_CPP							?= -Wno-switch
USER_LIBS								?=
include port.mk

# ==============================================================================
# Function definitions
# ==============================================================================

rwildcard								= $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2) $(filter $(subst *,%,$2),$d))
filter-dirs								= $(foreach v,$(1),$(if $(filter $(foreach d,$(EXCLUDE_DIRS),$(d)%),$(v)),,$(v)))
filter-out-any							= $(foreach v,$(2),$(if $(findstring $(1),$(v)),,$(v)))

# ==============================================================================
# Detects device
# ==============================================================================

MCU_DEVICE_CODE							:= 0
FLASH_SIZE								:= 0
SRAM_SIZE								:= 0
include Makefile-AVR.mk
ifeq ($(MCU_DEVICE_CODE),0)
    $(error No supported device found. Verify the MCU_DEVICE_NAME environment variable!)
endif

# ==============================================================================
# Compiler executables
# ==============================================================================

COMPILER_PREFIX							= avr-
ifneq ($(COMPILER_PATH),)
    COMPILER_PATH						:= $(COMPILER_PATH)/
endif

AR										:= $(COMPILER_PATH)$(COMPILER_PREFIX)ar
AS										:= $(COMPILER_PATH)$(COMPILER_PREFIX)gcc -x assemble-with-cpp
BIN										:= $(COMPILER_PATH)$(COMPILER_PREFIX)objcopy -O binary -S
CC										:= $(COMPILER_PATH)$(COMPILER_PREFIX)gcc
CCPP									:= $(COMPILER_PATH)$(COMPILER_PREFIX)g++
CP										:= $(COMPILER_PATH)$(COMPILER_PREFIX)objcopy
HEX										:= $(COMPILER_PATH)$(COMPILER_PREFIX)objcopy -O ihex
SZ										:= $(COMPILER_PATH)$(COMPILER_PREFIX)size --format=berkley

# ==============================================================================
# Search for files
# ==============================================================================

# Main code - All header files (Mantemos 'dir' para incluir as pastas)
HEADERS_ASM   := $(call filter-dirs,$(sort $(dir $(call rwildcard, , *.S))))
HEADERS_H     := $(call filter-dirs,$(sort $(dir $(call rwildcard, , *.h))))
HEADERS_HPP   := $(call filter-dirs,$(sort $(dir $(call rwildcard, , *.hpp))))
HEADERS_HXX   := $(sort $(HEADERS_H) $(HEADERS_HPP))
HEADERS_ALL   := $(sort $(HEADERS_HXX) $(HEADERS_ASM))

# Main code - Assembly source files (REMOVE 'dir')
SOURCES_S     := $(call filter-dirs,$(call rwildcard, , *.s))
SOURCES_ASM   := $(call filter-dirs,$(call rwildcard, , *.asm))
SOURCES_AXX   := $(sort $(SOURCES_ASM) $(SOURCES_S))

# Main code - C source files (REMOVE 'dir')
SOURCES_C     := $(call filter-dirs,$(call rwildcard, , *.c))

# Main code - CPP source files (REMOVE 'dir')
SOURCES_CPP   := $(call filter-dirs,$(call rwildcard, , *.cpp))

# Main code - CXX source files
SOURCES_CXX   := $(sort $(SOURCES_C) $(SOURCES_CPP))

# ==============================================================================
# Create flags
# ==============================================================================

# ------------------------------------------------------------------------------
# Include flags ----------------------------------------------------------------

INCLUDES_ASM		:= $(addprefix -I, $(HEADERS_ASM))
INCLUDES_H			:= $(addprefix -I, $(HEADERS_H))
INCLUDES_HPP		:= $(addprefix -I, $(HEADERS_HPP))
INCLUDES_HXX		:= $(sort $(INCLUDES_HPP) $(INCLUDES_H))
INCLUDES_ALL		:= $(sort $(INCLUDES_ASM) $(INCLUDES_HXX))

ifneq ($(USER_DEFINES_ASM),)
    USER_DEFINES_ASM	:= $(addprefix -D,$(USER_DEFINES_ASM))
endif
DEFINES_ASM			:= $(sort $(USER_DEFINES_ASM))
ifneq ($(USER_DEFINES_C),)
    USER_DEFINES_C	:= $(addprefix -D,$(USER_DEFINES_C))
endif
DEFINES_C			:= $(sort $(USER_DEFINES_C) -D$(MCU_DEVICE_MACRO))
ifneq ($(USER_DEFINES_CPP),)
    USER_DEFINES_CPP	:= $(addprefix -D,$(USER_DEFINES_CPP))
endif
DEFINES_CPP			:= $(sort $(USER_DEFINES_CPP) -D$(MCU_DEVICE_MACRO))
DEFINES_CXX			:= $(sort $(DEFINES_C) $(DEFINES_CPP))

# ------------------------------------------------------------------------------
# MCU compiler flags -----------------------------------------------------------

FLAG_MCU			:= -mmcu=$(MCU_DEVICE_NAME)

# ------------------------------------------------------------------------------
# ASM compiler flags -----------------------------------------------------------

FLAGS_ASM			= $(FLAG_MCU)
FLAGS_ASM			+= $(COMPILER_OPT)
FLAGS_ASM			+= -Wall -fdata-sections -ffunction-sections
FLAGS_ASM			+= $(USER_FLAGS_ASM)
FLAGS_ASM			+= $(DEFINES_ASM)
FLAGS_ASM			+= $(INCLUDES_AXX)

# ------------------------------------------------------------------------------
# C compiler flags -------------------------------------------------------------

FLAGS_C				= $(FLAG_MCU)
ifneq ($(COMPILER_STD_C),)
    FLAGS_C			+= -std=$(COMPILER_STD_C)
endif
FLAGS_C				+= $(COMPILER_OPT)
FLAGS_C				+= -Wall -fdata-sections -ffunction-sections -fno-exceptions
FLAGS_C				+= $(USER_FLAGS_C)
FLAGS_C				+= $(DEFINES_C)
FLAGS_C				+= $(INCLUDES_HXX)
ifeq ($(COMPILER_DEBUG),1)
    FLAGS_C			+= -g -gdwarf-2
endif
FLAGS_C				+= -MMD -MP -MF"$(@:%.o=%.d)"

# ------------------------------------------------------------------------------
# CPP compiler flags -----------------------------------------------------------

FLAGS_CPP			= $(FLAG_MCU)
ifneq ($(COMPILER_STD_CPP),)
    FLAGS_CPP		+= -std=$(COMPILER_STD_CPP)
endif
FLAGS_CPP			+= $(COMPILER_OPT)
FLAGS_CPP			+= -Wall -fdata-sections -ffunction-sections -fno-exceptions -fno-rtti
FLAGS_CPP			+= $(USER_FLAGS_CPP)
FLAGS_CPP			+= $(DEFINES_CPP)
FLAGS_CPP			+= $(INCLUDES_HXX)
ifeq ($(COMPILER_DEBUG),1)
    FLAGS_CPP		+= -g -gdwarf-2
endif
FLAGS_CPP			+= -MMD -MP -MF"$(@:%.o=%.d)"

# ------------------------------------------------------------------------------
# CXX compiler flags -----------------------------------------------------------

FLAGS_CXX			= $(FLAG_MCU)
ifneq ($(COMPILER_STD_CPP),)
    FLAGS_CXX		+= -std=$(COMPILER_STD_CPP)
endif
FLAGS_CXX			+= $(COMPILER_OPT)
FLAGS_CXX			+= -Wall -fdata-sections -ffunction-sections -fno-exceptions -fno-rtti
FLAGS_CXX			+= $(USER_FLAGS_CPP)
FLAGS_CXX			+= $(DEFINES_CXX)
FLAGS_CXX			+= $(INCLUDES_HXX)
ifeq ($(COMPILER_DEBUG),1)
    FLAGS_CXX		+= -g -gdwarf-2
endif
FLAGS_CXX			+= -MMD -MP -MF"$(@:%.o=%.d)"

# ------------------------------------------------------------------------------
# Linker flags -----------------------------------------------------------------

ifneq ($(USER_LIBS),)
    USER_LIBS		:= $(addprefix -l,$(USER_LIBS))
endif

FLAGS_LINKER		= $(FLAG_MCU)
ifneq ($(MCU_LINKER_FILE),)
    FLAGS_LINKER	+=-T$(MCU_LINKER_FILE)
endif
FLAGS_LINKER		+=$(LIBRARY_PATH)
FLAGS_LINKER		+= $(USER_LIBS)
FLAGS_LINKER		+= -Wl,--gc-sections -Wl,--strip-all -Wl,-Map=$(BUILD_DIR)/$(BUILD_NAME).map,--cref

# ##############################################################################
# TEST
# ##############################################################################

ifeq ($(COMPILE_C_AS_CPP),1)
    CC				:= $(CCPP)
    FLAGS_C			:= $(FLAGS_CPP)
endif

APP_FLASH_MAX = $(shell expr $(FLASH_SIZE) - $(BOOT_SIZE))

# ==============================================================================
# Build recipes
# ==============================================================================

.PHONY: assemble compile program cleanCompile cleanCompileProgram clean compileProgram compileCleanProgram cleanCompileCleanProgram cleanAssemble cleanAssembleProgram assembleProgram assembleCleanProgram cleanAssembleCleanProgram doNothing

# ------------------------------------------------------------------------------
# Assemble recipe
# ------------------------------------------------------------------------------

assemble: $(BUILD_DIR)
#	avra -fI -m "$(BUILD_DIR)/application.map" -l "$(BUILD_DIR)/application.lss" -e "$(BUILD_DIR)/application.eep" -d "$(BUILD_DIR)/application.o" -o "$(BUILD_DIR)/application.hex" main.asm
#	mv -f main.eep.hex $(BUILD_DIR)/application.hex
#	mv -f main.cof $(BUILD_DIR)/application.cof
#	mv -f main.obj $(BUILD_DIR)/application.obj
#	mv -f main.hex $(BUILD_DIR)/application.hex
	avrasm2 -fI -o "$(BUILD_DIR)/application.hex" -m "$(BUILD_DIR)/application.map" -l "$(BUILD_DIR)/application.lss" -e "$(BUILD_DIR)/application.eep" -S "$(BUILD_DIR)/application.tmp" -W+ie -d "$(BUILD_DIR)/application.o" main.asm

# ------------------------------------------------------------------------------
# Compile recipe
# ------------------------------------------------------------------------------

compile: $(BUILD_DIR)/$(BUILD_NAME).elf $(BUILD_DIR)/$(BUILD_NAME).hex $(BUILD_DIR)/$(BUILD_NAME).bin

# List of C objects
OBJECTS			+= $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_C:.c=.o)))
vpath %.c $(sort $(dir $(SOURCES_C)))

# List of CPP objects
OBJECTS			+= $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_CPP:.cpp=.o)))
vpath %.cpp $(sort $(dir $(SOURCES_CPP)))

# List of Assembly objects
OBJECTS			+= $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_S:.s=.o)))
vpath %.s $(sort $(dir $(SOURCES_S)))

# List of Assembly objects
OBJECTS			+= $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_ASM:.asm=.o)))
vpath %.asm $(sort $(dir $(SOURCES_ASM)))

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) -c $(FLAGS_C) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.cpp Makefile | $(BUILD_DIR)
	$(CCPP) -c $(FLAGS_CPP) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.cpp=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR)
	$(AS) -c $(FLAGS_ASM) $< -o $@

$(BUILD_DIR)/%.o: %.asm Makefile | $(BUILD_DIR)
	$(AS) -c $(FLAGS_ASM) $< -o $@

$(BUILD_DIR)/$(BUILD_NAME).elf: $(OBJECTS) Makefile
	$(CCPP) $(OBJECTS) $(FLAGS_LINKER) -o $@
	@echo
	@echo "---------------- Memory Usage ----------------"
	@$(SZ) -B $@
	@echo
	@$(SZ) -A $@ | awk ' \
		/^\.text/  {t=$$2} \
		/^\.data/  {d=$$2} \
		/^\.bss/   {b=$$2} \
		END { \
			flash_used = t + d; \
			ram_used = d + b; \
			flash_max = $(APP_FLASH_MAX); \
			\
			printf "Flash (App): %d / %d bytes (%.2f%% used)\n", flash_used, flash_max, (flash_used/flash_max)*100; \
			printf "SRAM:        %d / %d bytes (%.2f%% used)\n", ram_used, $(SRAM_SIZE), (ram_used/$(SRAM_SIZE))*100; \
			\
			if (flash_used > flash_max) { \
				print "\n!!! WARNING: APPLICATION OVERFLOWS INTO BOOTLOADER SECTION !!!\n"; \
			} \
		}'
	@echo "----------------------------------------------"

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@

$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@

$(BUILD_DIR):
	mkdir build

# ------------------------------------------------------------------------------
# Clean recipe
# ------------------------------------------------------------------------------

clean:
	@echo
	@echo ================================================================================
	@echo Removing auxiliary files...
	@echo ================================================================================
	@echo
	@rm -r -f -v $(BUILD_DIR)/*.d
	@rm -r -f -v $(BUILD_DIR)/*.lst
	@rm -r -f -v $(BUILD_DIR)/*.o
	@rm -r -f -v $(BUILD_DIR)/*.lss
	@rm -r -f -v $(BUILD_DIR)/*.map
	@rm -r -f -v $(BUILD_DIR)/*.tmp
	@echo Auxiliary files removed!
	@echo
	@echo --------------------------------------------------------------------------------
	@echo End of clean process!
	@echo ================================================================================
	@echo

# ------------------------------------------------------------------------------
# Program recipe
# ------------------------------------------------------------------------------

program:
	@echo
	@echo ================================================================================
	@echo Loading program...
	@echo ================================================================================
	@echo
ifeq ($(PROGRAMMER_TYPE),arduino)
	@echo Using AVR - ARDUINO - USART!
	avrdude -C $(PROGRAMMER_CONFIG_FILE) -v -p $(MCU_DEVICE_NAME) -c $(PROGRAMMER_TYPE) -P $(PROGRAMMER_PORT) -b$(PROGRAMMER_BAUDRATE) -D -Uflash:w:$(BUILD_DIR)/$(BUILD_NAME).hex:i
else
	@echo Programmer not suitable for this device!
	exit 0
endif
	@echo
	@echo --------------------------------------------------------------------------------
	@echo Program loaded!
	@echo ================================================================================

# ------------------------------------------------------------------------------
# Compound recipes
# ------------------------------------------------------------------------------

cleanCompile:				clean compile

compileProgram:				compile program

cleanCompileProgram:		clean compile program

compileCleanProgram:		compile clean program

cleanCompileCleanProgram:	clean compile clean program

cleanAssemble:				clean assemble

cleanAssembleProgram:		clean assemble program

assembleProgram:			assemble program

assembleCleanProgram:		assemble clean program

cleanAssembleCleanProgram:	clean assemble clean program

# ------------------------------------------------------------------------------
# Information recipe
# ------------------------------------------------------------------------------
doNothing:
	@echo
	@echo ================================================================================
	@echo Dumping...
	@echo ================================================================================
	@echo
	@echo ------------------------------
	@echo Device information
	@echo ------------------------------
	@echo
	@echo MCU_DEVICE_CODE				= $(MCU_DEVICE_CODE)
	@echo MCU_DEVICE_NAME				= $(MCU_DEVICE_NAME)
	@echo MCU_DEVICE_MACRO				= $(MCU_DEVICE_MACRO)
	@echo FLASH_SIZE					= $(FLASH_SIZE)
	@echo SRAM_SIZE						= $(SRAM_SIZE)
	@echo
	@echo ------------------------------
	@echo System information
	@echo ------------------------------
	@echo
	@echo MY_SHELL						= $(MY_SHELL)
	@echo SHELL							= $(SHELL)
	@echo SPACE							= $(SPACE)
	@echo USED_ARC						= $(USED_ARC)
	@echo USED_OS						= $(USED_OS)
	@echo USED_SHELL					= $(USED_SHELL)
	@echo
	@echo ------------------------------
	@echo Toolchain data
	@echo ------------------------------
	@echo
	@echo COMPILER_PREFIX				= $(COMPILER_PREFIX)
	@echo COMPILER_PATH					= $(COMPILER_PATH)
	@echo AR							= $(AR)
	@echo AS							= $(AS)
	@echo BIN							= $(BIN)
	@echo CC							= $(CC)
	@echo CCPP							= $(CCPP)
	@echo CP							= $(CP)
	@echo HEX							= $(HEX)
	@echo SZ							= $(SZ)
	@echo PROGRAMMER_TYPE				= $(PROGRAMMER_TYPE)
	@echo PROGRAMMER_CONFIG_FILE		= $(PROGRAMMER_CONFIG_FILE)
	@echo PROGRAMMER_PORT				= $(PROGRAMMER_PORT)
	@echo PROGRAMMER_BAUDRATE			= $(PROGRAMMER_BAUDRATE)
	@echo
	@echo ------------------------------
	@echo Toolchain version
	@echo ------------------------------
	@echo
	@$(CC) --version
	@echo
	@echo ------------------------------
	@echo User defined parameters
	@echo ------------------------------
	@echo
	@echo BUILD_NAME					= $(BUILD_NAME)
	@echo BUILD_DIR						= $(BUILD_DIR)
	@echo COMPILE_C_AS_CPP				= $(COMPILE_C_AS_CPP)
	@echo COMPILER_DEBUG				= $(COMPILER_DEBUG)
	@echo COMPILER_OPT					= $(COMPILER_OPT)
	@echo COMPILER_STD_C				= $(COMPILER_STD_C)
	@echo COMPILER_STD_CPP				= $(COMPILER_STD_CPP)
	@echo USER_DEFINES_ASM				= $(USER_DEFINES_ASM)
	@echo USER_DEFINES_C				= $(USER_DEFINES_C)
	@echo USER_DEFINES_CPP				= $(USER_DEFINES_CPP)
	@echo USER_FLAGS_ASM				= $(USER_FLAGS_ASM)
	@echo USER_FLAGS_C					= $(USER_FLAGS_C)
	@echo USER_FLAGS_CPP				= $(USER_FLAGS_CPP)
	@echo USER_LIBS						= $(USER_LIBS)
	@echo
	@echo ------------------------------
	@echo Compilation parameters
	@echo ------------------------------
	@echo
	@echo FLAGS_ASM						= $(FLAGS_ASM)
	@echo FLAGS_C						= $(FLAGS_C)
	@echo FLAGS_CPP						= $(FLAGS_CPP)
	@echo FLAGS_CXX						= $(FLAGS_CXX)
	@echo FLAGS_LINKER					= $(FLAGS_LINKER)
	@echo
	@echo ------------------------------
	@echo Library parameters
	@echo ------------------------------
	@echo
	@echo LIBRARY_PATH					= $(LIBRARY_PATH)
	@echo
	@echo ------------------------------
	@echo File listing
	@echo ------------------------------
	@echo
	@echo HEADERS_ALL					= $(HEADERS_ALL)
	@echo HEADERS_ASM					= $(HEADERS_ASM)
	@echo HEADERS_H						= $(HEADERS_H)
	@echo HEADERS_HPP					= $(HEADERS_HPP)
	@echo HEADERS_HXX					= $(HEADERS_HXX)
	@echo SOURCES_ASM					= $(SOURCES_ASM)
	@echo SOURCES_S						= $(SOURCES_S)
	@echo SOURCES_AXX					= $(SOURCES_AXX)
	@echo SOURCES_C						= $(SOURCES_C)
	@echo SOURCES_CPP					= $(SOURCES_CPP)
	@echo SOURCES_CXX					= $(SOURCES_CXX)
	@echo
	@echo ------------------------------
	@echo Auxiliary
	@echo ------------------------------
	@echo
	@echo DEFINES_ASM					= $(DEFINES_ASM)
	@echo DEFINES_C						= $(DEFINES_C)
	@echo DEFINES_CPP					= $(DEFINES_CPP)
	@echo DEFINES_CXX					= $(DEFINES_CXX)
	@echo EXCLUDE_DIRS					= $(EXCLUDE_DIRS)
	@echo FLAG_MCU						= $(FLAG_MCU)
	@echo INCLUDES_ALL					= $(INCLUDES_ALL)
	@echo INCLUDES_ASM					= $(INCLUDES_ASM)
	@echo INCLUDES_H					= $(INCLUDES_H)
	@echo INCLUDES_HPP					= $(INCLUDES_HPP)
	@echo INCLUDES_HXX					= $(INCLUDES_HXX)
	@echo
	@echo --------------------------------------------------------------------------------
	@echo end of dump process!
	@echo ================================================================================
