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




