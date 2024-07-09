################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.c \
../libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Pos.c \
../libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.c \
../libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Timer.c 

COMPILED_SRCS += \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.src \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Pos.src \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.src \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Timer.src 

C_DEPS += \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.d \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Pos.d \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.d \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Timer.d 

OBJS += \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.o \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Pos.o \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.o \
./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Timer.o 


# Each subdirectory must supply rules for building sources it contributes
libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/%.src: ../libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/%.c libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS_Project/WLBF_MT_TC264_2024/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/libraries\/libraries\/infineon_libraries\/Service\/CpuGeneric\/StdIf\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/%.o: ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/%.src libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-libraries-2f-libraries-2f-infineon_libraries-2f-Service-2f-CpuGeneric-2f-StdIf

clean-libraries-2f-libraries-2f-infineon_libraries-2f-Service-2f-CpuGeneric-2f-StdIf:
	-$(RM) ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.d ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.o ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_DPipe.src ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Pos.d ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Pos.o ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Pos.src ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.d ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.o ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_PwmHl.src ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Timer.d ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Timer.o ./libraries/libraries/infineon_libraries/Service/CpuGeneric/StdIf/IfxStdIf_Timer.src

.PHONY: clean-libraries-2f-libraries-2f-infineon_libraries-2f-Service-2f-CpuGeneric-2f-StdIf

