################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/tld7002/TLD7002_driver/TLD7002FuncLayer.c \
../code/tld7002/TLD7002_driver/TLD7002_ControlLayer.c \
../code/tld7002/TLD7002_driver/TLD7002_ServiceLayer.c 

COMPILED_SRCS += \
./code/tld7002/TLD7002_driver/TLD7002FuncLayer.src \
./code/tld7002/TLD7002_driver/TLD7002_ControlLayer.src \
./code/tld7002/TLD7002_driver/TLD7002_ServiceLayer.src 

C_DEPS += \
./code/tld7002/TLD7002_driver/TLD7002FuncLayer.d \
./code/tld7002/TLD7002_driver/TLD7002_ControlLayer.d \
./code/tld7002/TLD7002_driver/TLD7002_ServiceLayer.d 

OBJS += \
./code/tld7002/TLD7002_driver/TLD7002FuncLayer.o \
./code/tld7002/TLD7002_driver/TLD7002_ControlLayer.o \
./code/tld7002/TLD7002_driver/TLD7002_ServiceLayer.o 


# Each subdirectory must supply rules for building sources it contributes
code/tld7002/TLD7002_driver/%.src: ../code/tld7002/TLD7002_driver/%.c code/tld7002/TLD7002_driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS_Project/WLBF_MT_TC264_ZF_2024/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/code\/tld7002\/TLD7002_driver\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

code/tld7002/TLD7002_driver/%.o: ./code/tld7002/TLD7002_driver/%.src code/tld7002/TLD7002_driver/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code-2f-tld7002-2f-TLD7002_driver

clean-code-2f-tld7002-2f-TLD7002_driver:
	-$(RM) ./code/tld7002/TLD7002_driver/TLD7002FuncLayer.d ./code/tld7002/TLD7002_driver/TLD7002FuncLayer.o ./code/tld7002/TLD7002_driver/TLD7002FuncLayer.src ./code/tld7002/TLD7002_driver/TLD7002_ControlLayer.d ./code/tld7002/TLD7002_driver/TLD7002_ControlLayer.o ./code/tld7002/TLD7002_driver/TLD7002_ControlLayer.src ./code/tld7002/TLD7002_driver/TLD7002_ServiceLayer.d ./code/tld7002/TLD7002_driver/TLD7002_ServiceLayer.o ./code/tld7002/TLD7002_driver/TLD7002_ServiceLayer.src

.PHONY: clean-code-2f-tld7002-2f-TLD7002_driver

