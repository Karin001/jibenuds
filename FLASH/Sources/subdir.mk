################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/CAN.c" \
"../Sources/GeneralFun.c" \
"../Sources/MCUInit.c" \
"../Sources/SCI.c" \
"../Sources/isr.c" \
"../Sources/main.c" \
"../Sources/txdebug.c" \

C_SRCS += \
../Sources/CAN.c \
../Sources/GeneralFun.c \
../Sources/MCUInit.c \
../Sources/SCI.c \
../Sources/isr.c \
../Sources/main.c \
../Sources/txdebug.c \

OBJS += \
./Sources/CAN_c.obj \
./Sources/GeneralFun_c.obj \
./Sources/MCUInit_c.obj \
./Sources/SCI_c.obj \
./Sources/isr_c.obj \
./Sources/main_c.obj \
./Sources/txdebug_c.obj \

OBJS_QUOTED += \
"./Sources/CAN_c.obj" \
"./Sources/GeneralFun_c.obj" \
"./Sources/MCUInit_c.obj" \
"./Sources/SCI_c.obj" \
"./Sources/isr_c.obj" \
"./Sources/main_c.obj" \
"./Sources/txdebug_c.obj" \

C_DEPS += \
./Sources/CAN_c.d \
./Sources/GeneralFun_c.d \
./Sources/MCUInit_c.d \
./Sources/SCI_c.d \
./Sources/isr_c.d \
./Sources/main_c.d \
./Sources/txdebug_c.d \

C_DEPS_QUOTED += \
"./Sources/CAN_c.d" \
"./Sources/GeneralFun_c.d" \
"./Sources/MCUInit_c.d" \
"./Sources/SCI_c.d" \
"./Sources/isr_c.d" \
"./Sources/main_c.d" \
"./Sources/txdebug_c.d" \

OBJS_OS_FORMAT += \
./Sources/CAN_c.obj \
./Sources/GeneralFun_c.obj \
./Sources/MCUInit_c.obj \
./Sources/SCI_c.obj \
./Sources/isr_c.obj \
./Sources/main_c.obj \
./Sources/txdebug_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/CAN_c.obj: ../Sources/CAN.c
	@echo 'Building file: $<'
	@echo 'Executing target #1 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/CAN.args" -ObjN="Sources/CAN_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/GeneralFun_c.obj: ../Sources/GeneralFun.c
	@echo 'Building file: $<'
	@echo 'Executing target #2 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/GeneralFun.args" -ObjN="Sources/GeneralFun_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/MCUInit_c.obj: ../Sources/MCUInit.c
	@echo 'Building file: $<'
	@echo 'Executing target #3 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MCUInit.args" -ObjN="Sources/MCUInit_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SCI_c.obj: ../Sources/SCI.c
	@echo 'Building file: $<'
	@echo 'Executing target #4 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SCI.args" -ObjN="Sources/SCI_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/isr_c.obj: ../Sources/isr.c
	@echo 'Building file: $<'
	@echo 'Executing target #5 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/isr.args" -ObjN="Sources/isr_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Executing target #6 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/txdebug_c.obj: ../Sources/txdebug.c
	@echo 'Building file: $<'
	@echo 'Executing target #7 $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/txdebug.args" -ObjN="Sources/txdebug_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


