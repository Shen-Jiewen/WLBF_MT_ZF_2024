################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/libraries/zf_driver/zf_driver_adc.c \
../libraries/libraries/zf_driver/zf_driver_delay.c \
../libraries/libraries/zf_driver/zf_driver_dma.c \
../libraries/libraries/zf_driver/zf_driver_encoder.c \
../libraries/libraries/zf_driver/zf_driver_exti.c \
../libraries/libraries/zf_driver/zf_driver_flash.c \
../libraries/libraries/zf_driver/zf_driver_gpio.c \
../libraries/libraries/zf_driver/zf_driver_pit.c \
../libraries/libraries/zf_driver/zf_driver_pwm.c \
../libraries/libraries/zf_driver/zf_driver_soft_iic.c \
../libraries/libraries/zf_driver/zf_driver_soft_spi.c \
../libraries/libraries/zf_driver/zf_driver_spi.c \
../libraries/libraries/zf_driver/zf_driver_timer.c \
../libraries/libraries/zf_driver/zf_driver_uart.c 

COMPILED_SRCS += \
./libraries/libraries/zf_driver/zf_driver_adc.src \
./libraries/libraries/zf_driver/zf_driver_delay.src \
./libraries/libraries/zf_driver/zf_driver_dma.src \
./libraries/libraries/zf_driver/zf_driver_encoder.src \
./libraries/libraries/zf_driver/zf_driver_exti.src \
./libraries/libraries/zf_driver/zf_driver_flash.src \
./libraries/libraries/zf_driver/zf_driver_gpio.src \
./libraries/libraries/zf_driver/zf_driver_pit.src \
./libraries/libraries/zf_driver/zf_driver_pwm.src \
./libraries/libraries/zf_driver/zf_driver_soft_iic.src \
./libraries/libraries/zf_driver/zf_driver_soft_spi.src \
./libraries/libraries/zf_driver/zf_driver_spi.src \
./libraries/libraries/zf_driver/zf_driver_timer.src \
./libraries/libraries/zf_driver/zf_driver_uart.src 

C_DEPS += \
./libraries/libraries/zf_driver/zf_driver_adc.d \
./libraries/libraries/zf_driver/zf_driver_delay.d \
./libraries/libraries/zf_driver/zf_driver_dma.d \
./libraries/libraries/zf_driver/zf_driver_encoder.d \
./libraries/libraries/zf_driver/zf_driver_exti.d \
./libraries/libraries/zf_driver/zf_driver_flash.d \
./libraries/libraries/zf_driver/zf_driver_gpio.d \
./libraries/libraries/zf_driver/zf_driver_pit.d \
./libraries/libraries/zf_driver/zf_driver_pwm.d \
./libraries/libraries/zf_driver/zf_driver_soft_iic.d \
./libraries/libraries/zf_driver/zf_driver_soft_spi.d \
./libraries/libraries/zf_driver/zf_driver_spi.d \
./libraries/libraries/zf_driver/zf_driver_timer.d \
./libraries/libraries/zf_driver/zf_driver_uart.d 

OBJS += \
./libraries/libraries/zf_driver/zf_driver_adc.o \
./libraries/libraries/zf_driver/zf_driver_delay.o \
./libraries/libraries/zf_driver/zf_driver_dma.o \
./libraries/libraries/zf_driver/zf_driver_encoder.o \
./libraries/libraries/zf_driver/zf_driver_exti.o \
./libraries/libraries/zf_driver/zf_driver_flash.o \
./libraries/libraries/zf_driver/zf_driver_gpio.o \
./libraries/libraries/zf_driver/zf_driver_pit.o \
./libraries/libraries/zf_driver/zf_driver_pwm.o \
./libraries/libraries/zf_driver/zf_driver_soft_iic.o \
./libraries/libraries/zf_driver/zf_driver_soft_spi.o \
./libraries/libraries/zf_driver/zf_driver_spi.o \
./libraries/libraries/zf_driver/zf_driver_timer.o \
./libraries/libraries/zf_driver/zf_driver_uart.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/libraries/zf_driver/%.src: ../libraries/libraries/zf_driver/%.c libraries/libraries/zf_driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS_Project/WLBF_MT_TC264_2024/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/libraries\/libraries\/zf_driver\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

libraries/libraries/zf_driver/%.o: ./libraries/libraries/zf_driver/%.src libraries/libraries/zf_driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-libraries-2f-libraries-2f-zf_driver

clean-libraries-2f-libraries-2f-zf_driver:
	-$(RM) ./libraries/libraries/zf_driver/zf_driver_adc.d ./libraries/libraries/zf_driver/zf_driver_adc.o ./libraries/libraries/zf_driver/zf_driver_adc.src ./libraries/libraries/zf_driver/zf_driver_delay.d ./libraries/libraries/zf_driver/zf_driver_delay.o ./libraries/libraries/zf_driver/zf_driver_delay.src ./libraries/libraries/zf_driver/zf_driver_dma.d ./libraries/libraries/zf_driver/zf_driver_dma.o ./libraries/libraries/zf_driver/zf_driver_dma.src ./libraries/libraries/zf_driver/zf_driver_encoder.d ./libraries/libraries/zf_driver/zf_driver_encoder.o ./libraries/libraries/zf_driver/zf_driver_encoder.src ./libraries/libraries/zf_driver/zf_driver_exti.d ./libraries/libraries/zf_driver/zf_driver_exti.o ./libraries/libraries/zf_driver/zf_driver_exti.src ./libraries/libraries/zf_driver/zf_driver_flash.d ./libraries/libraries/zf_driver/zf_driver_flash.o ./libraries/libraries/zf_driver/zf_driver_flash.src ./libraries/libraries/zf_driver/zf_driver_gpio.d ./libraries/libraries/zf_driver/zf_driver_gpio.o ./libraries/libraries/zf_driver/zf_driver_gpio.src ./libraries/libraries/zf_driver/zf_driver_pit.d ./libraries/libraries/zf_driver/zf_driver_pit.o ./libraries/libraries/zf_driver/zf_driver_pit.src ./libraries/libraries/zf_driver/zf_driver_pwm.d ./libraries/libraries/zf_driver/zf_driver_pwm.o ./libraries/libraries/zf_driver/zf_driver_pwm.src ./libraries/libraries/zf_driver/zf_driver_soft_iic.d ./libraries/libraries/zf_driver/zf_driver_soft_iic.o ./libraries/libraries/zf_driver/zf_driver_soft_iic.src ./libraries/libraries/zf_driver/zf_driver_soft_spi.d ./libraries/libraries/zf_driver/zf_driver_soft_spi.o ./libraries/libraries/zf_driver/zf_driver_soft_spi.src ./libraries/libraries/zf_driver/zf_driver_spi.d ./libraries/libraries/zf_driver/zf_driver_spi.o ./libraries/libraries/zf_driver/zf_driver_spi.src ./libraries/libraries/zf_driver/zf_driver_timer.d ./libraries/libraries/zf_driver/zf_driver_timer.o ./libraries/libraries/zf_driver/zf_driver_timer.src ./libraries/libraries/zf_driver/zf_driver_uart.d ./libraries/libraries/zf_driver/zf_driver_uart.o ./libraries/libraries/zf_driver/zf_driver_uart.src

.PHONY: clean-libraries-2f-libraries-2f-zf_driver

