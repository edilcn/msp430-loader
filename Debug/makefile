################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := F:/ti/ccs1011/ccs/tools/compiler/ti-cgt-msp430_20.2.1.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./flash_memory.obj" \
"./main.obj" \
"./spi.obj" \
"./drivers/uart.obj" \
"./hal/adc12_b.obj" \
"./hal/aes256.obj" \
"./hal/comp_e.obj" \
"./hal/crc.obj" \
"./hal/crc32.obj" \
"./hal/cs.obj" \
"./hal/dma.obj" \
"./hal/esi.obj" \
"./hal/eusci_a_spi.obj" \
"./hal/eusci_a_uart.obj" \
"./hal/eusci_b_i2c.obj" \
"./hal/eusci_b_spi.obj" \
"./hal/framctl.obj" \
"./hal/framctl_a.obj" \
"./hal/gpio.obj" \
"./hal/hspll.obj" \
"./hal/lcd_c.obj" \
"./hal/mpu.obj" \
"./hal/mpy32.obj" \
"./hal/mtif.obj" \
"./hal/pmm.obj" \
"./hal/ram.obj" \
"./hal/ref_a.obj" \
"./hal/rtc_b.obj" \
"./hal/rtc_c.obj" \
"./hal/saph.obj" \
"./hal/saph_a.obj" \
"./hal/sdhs.obj" \
"./hal/sfr.obj" \
"./hal/sysctl.obj" \
"./hal/timer_a.obj" \
"./hal/timer_b.obj" \
"./hal/tlv.obj" \
"./hal/uups.obj" \
"./hal/wdt_a.obj" \
"../lnk_msp430fr6989.cmd" \
$(GEN_CMDS__FLAG) \
-llibmpu_init.a \
-llibmath.a \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include drivers/subdir_vars.mk
-include hal/subdir_vars.mk
-include subdir_rules.mk
-include drivers/subdir_rules.mk
-include hal/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
msp430-loader.out \

EXE_OUTPUTS__QUOTED += \
"msp430-loader.out" \

BIN_OUTPUTS += \
msp430-loader.hex \

BIN_OUTPUTS__QUOTED += \
"msp430-loader.hex" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "msp430-loader.out"

# Tool invocations
msp430-loader.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: MSP430 Linker'
	"F:/ti/ccs1011/ccs/tools/compiler/ti-cgt-msp430_20.2.1.LTS/bin/cl430" -vmspx --data_model=restricted --use_hw_mpy=F5 --advice:power=all --advice:hw_config=all --define=__MSP430FR6989__ --define=_MPU_ENABLE -g --printf_support=minimal --diag_warning=225 --diag_wrap=off --display_error_number --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 -z -m"msp430-loader.map" --heap_size=160 --stack_size=160 --cinit_hold_wdt=on -i"F:/ti/ccs1011/ccs/ccs_base/msp430/include" -i"F:/ti/ccs1011/ccs/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"F:/ti/ccs1011/ccs/ccs_base/msp430/lib/FR59xx" -i"F:/ti/ccs1011/ccs/tools/compiler/ti-cgt-msp430_20.2.1.LTS/lib" -i"F:/ti/ccs1011/ccs/tools/compiler/ti-cgt-msp430_20.2.1.LTS/include" --priority --reread_libs --define=_MPU_ENABLE --diag_wrap=off --display_error_number --warn_sections --xml_link_info="msp430-loader_linkInfo.xml" --use_hw_mpy=F5 --rom_model -o "msp430-loader.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

msp430-loader.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: MSP430 Hex Utility'
	"F:/ti/ccs1011/ccs/tools/compiler/ti-cgt-msp430_20.2.1.LTS/bin/hex430" --memwidth=8 --romwidth=8 -o "msp430-loader.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(BIN_OUTPUTS__QUOTED)$(EXE_OUTPUTS__QUOTED)
	-$(RM) "flash_memory.obj" "main.obj" "spi.obj" "drivers\uart.obj" "hal\adc12_b.obj" "hal\aes256.obj" "hal\comp_e.obj" "hal\crc.obj" "hal\crc32.obj" "hal\cs.obj" "hal\dma.obj" "hal\esi.obj" "hal\eusci_a_spi.obj" "hal\eusci_a_uart.obj" "hal\eusci_b_i2c.obj" "hal\eusci_b_spi.obj" "hal\framctl.obj" "hal\framctl_a.obj" "hal\gpio.obj" "hal\hspll.obj" "hal\lcd_c.obj" "hal\mpu.obj" "hal\mpy32.obj" "hal\mtif.obj" "hal\pmm.obj" "hal\ram.obj" "hal\ref_a.obj" "hal\rtc_b.obj" "hal\rtc_c.obj" "hal\saph.obj" "hal\saph_a.obj" "hal\sdhs.obj" "hal\sfr.obj" "hal\sysctl.obj" "hal\timer_a.obj" "hal\timer_b.obj" "hal\tlv.obj" "hal\uups.obj" "hal\wdt_a.obj" 
	-$(RM) "flash_memory.d" "main.d" "spi.d" "drivers\uart.d" "hal\adc12_b.d" "hal\aes256.d" "hal\comp_e.d" "hal\crc.d" "hal\crc32.d" "hal\cs.d" "hal\dma.d" "hal\esi.d" "hal\eusci_a_spi.d" "hal\eusci_a_uart.d" "hal\eusci_b_i2c.d" "hal\eusci_b_spi.d" "hal\framctl.d" "hal\framctl_a.d" "hal\gpio.d" "hal\hspll.d" "hal\lcd_c.d" "hal\mpu.d" "hal\mpy32.d" "hal\mtif.d" "hal\pmm.d" "hal\ram.d" "hal\ref_a.d" "hal\rtc_b.d" "hal\rtc_c.d" "hal\saph.d" "hal\saph_a.d" "hal\sdhs.d" "hal\sfr.d" "hal\sysctl.d" "hal\timer_a.d" "hal\timer_b.d" "hal\tlv.d" "hal\uups.d" "hal\wdt_a.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

