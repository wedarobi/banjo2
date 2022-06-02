# config
BASENAME := banjo2


# VERSION - selects the version of the game to build
#  usa - builds the [23/09/2000 13:19] North American version
#  jpn - builds the [27/10/2000 13:36] Japanese version
#  eur - builds the [01/12/2000 15:24] European version
#  aus - builds the [25/10/2000 14:42] Australian version
VERSION ?= usa
$(eval $(call validate-option,VERSION,usa jpn eur aus))

ifeq      ($(VERSION),usa)
  DEFINES   += VERSION_USA=1
else ifeq ($(VERSION),jpn)
  DEFINES   += VERSION_JPN=1
else ifeq ($(VERSION),eur)
  DEFINES   += VERSION_EUR=1
else ifeq ($(VERSION),aus)
  DEFINES   += VERSION_AUS=1
endif


TARGET := banjo2_$(VERSION)


# NON_MATCHING - whether to build a matching, identical copy of the ROM
#   1 - enable some alternate, more portable code that does not produce a matching ROM
#   0 - build a matching ROM
NON_MATCHING ?= 0
$(eval $(call validate-option,NON_MATCHING,0 1))


# COMPARE - whether to verify the SHA-1 hash of the ROM after building
#   1 - verifies the SHA-1 hash of the selected version of the game
#   0 - does not verify the hash
COMPARE ?= 1
$(eval $(call validate-option,COMPARE,0 1))


# Whether to hide commands or not
VERBOSE ?= 0
ifeq ($(VERBOSE),0)
  V := @
endif


# Whether to colorize build messages
COLOR ?= 1


# display selected options unless 'make clean' or 'make distclean' is run
ifeq ($(filter clean distclean,$(MAKECMDGOALS)),)
  $(info ==== Build Options ====)
  $(info Version:        $(VERSION))
  $(info Target:         $(TARGET))
  ifeq ($(COMPARE),1)
    $(info Compare ROM:    yes)
  else
    $(info Compare ROM:    no)
  endif
  ifeq ($(NON_MATCHING),1)
    $(info Build Matching: no)
  else
    $(info Build Matching: yes)
  endif
  $(info =======================)
endif


#==============================================================================#
# Target Executable and Sources                                                #
#==============================================================================#

# System tools
MKDIR := mkdir
CP := cp
CD := cd
RM := rm
CAT := cat
DIFF := diff

# Build tools
CC                := tools/ido5.3_recomp/cc
CPP               := cpp
CROSS             := mips-linux-gnu-
GCC               := $(CROSS)gcc
AS                := $(CROSS)as
LD                := $(CROSS)ld
OBJDUMP           := $(CROSS)objdump
OBJCOPY           := $(CROSS)objcopy
PYTHON            := python3
GREP              := grep -rl
SPLAT             := $(PYTHON) tools/splat/split.py
PRINT             := printf
PATCH_LIB_MATH    := tools/patch_libultra_math #!
ASM_PROCESSOR_DIR := tools/asm-processor #!

RARE_TOOLS        := tools/bk_tools #!
RARE_DECOMPRESS   := $(BK_TOOLS)/bk_inflate_code #!
RARE_COMPRESS     := $(BK_TOOLS)/bk_deflate_code #!
ASM_PROCESSOR     := $(PYTHON) $(ASM_PROCESSOR_DIR)/asm_processor.py #!
SPLAT_INPUTS      := $(PYTHON) tools/splat_inputs.py


#==============================================================================#
# Files and folders                                                            #
#==============================================================================#

VER_ROOT          := ver/$(VERSION)

# Source files
SRC_ROOT          := $(VER_ROOT)/src
ASM_ROOT          := $(VER_ROOT)/asm
BIN_ROOT          := $(VER_ROOT)/bin
BUILD_ROOT        := $(VER_ROOT)/build

# Build files
BASEROM           := $(VER_ROOT)/baserom.z64




#==============================================================================#
# Functions                                                                    #
#==============================================================================#

# Colourful text printing
NO_COL  := \033[0m
RED     := \033[0;31m
GREEN   := \033[0;32m
BLUE    := \033[0;34m
YELLOW  := \033[0;33m
BLINK   := \033[33;5m

# Print message with zero arguments (i.e. message)
define print0
  @$(PRINT) "$(GREEN)$(1)$(NO_COL)\n"
endef

# Print message with one argument (i.e. message arg)
define print1
  @$(PRINT) "$(GREEN)$(1) $(BLUE)$(2)$(NO_COL)\n"
endef

# Print message with two arguments (i.e. message arg1 -> arg2)
define print2
  @$(PRINT) "$(GREEN)$(1) $(YELLOW)$(2)$(GREEN) -> $(BLUE)$(3)$(NO_COL)\n"
endef


#==============================================================================#
# Flags                                                                        #
#==============================================================================#

# Build tool flags
CFLAGS         := -c -Wab,-r4300_mul -non_shared -G 0 -Xfullwarn -Xcpluscomm  -signed $(OPT_FLAGS) $(MIPSBIT) -D_FINALROM -DF3DEX2_GBI
CFLAGS         += -woff 649,838,807
CPPFLAGS       := -D_FINALROM -DN_MICRO
INCLUDE_CFLAGS := -I . -I include -I include/2.0L -I include/2.0L/PR
OPT_FLAGS      := -O2 
MIPSBIT        := -mips2
ASFLAGS        := -EB -mtune=vr4300 -march=vr4300 -mabi=32 -I include
GCC_ASFLAGS    := -c -x assembler-with-cpp -mabi=32 -ffreestanding -mtune=vr4300 -march=vr4300 -mfix4300 -G 0 -O -mno-shared -fno-PIC -mno-abicalls
LDFLAGS_COMMON := -T $(VER_ROOT)/symbol_addrs.core1.$(VERSION).txt \
				  -T $(VER_ROOT)/symbol_addrs.core2.$(VERSION).txt \
				  -T $(VER_ROOT)/symbol_addrs.global.$(VERSION).txt \
				  -T $(VER_ROOT)/undefined_syms.$(VERSION).txt \
				  -T $(VER_ROOT)/undefined_syms.libultra.txt \
				  --no-check-sections --accept-unknown-input-arch
LDFLAGS        := -T $(LD_SCRIPT) -Map $(ELF:.elf=.map) --no-check-sections --accept-unknown-input-arch -T undefined_syms.libultra.txt
BINOFLAGS      := -I binary -O elf32-big






#==============================================================================#
# Rules                                                                        #
#==============================================================================#

clean:
	$(call print0,Cleaning build artifacts)
	@$(RM) -rf $(BUILD_ROOT)
	@$(RM) -rf $(BIN_ROOT)
	@$(RM) -rf $(ASM_ROOT)/*.s
	@$(RM) -f $(VER_ROOT)/syms/undef_auto*
	@$(RM) -f *.ld



