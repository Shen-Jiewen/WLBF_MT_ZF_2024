################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/Fusion/FusionAhrs.c \
../code/Fusion/FusionCompass.c \
../code/Fusion/FusionOffset.c 

COMPILED_SRCS += \
./code/Fusion/FusionAhrs.src \
./code/Fusion/FusionCompass.src \
./code/Fusion/FusionOffset.src 

C_DEPS += \
./code/Fusion/FusionAhrs.d \
./code/Fusion/FusionCompass.d \
./code/Fusion/FusionOffset.d 

OBJS += \
./code/Fusion/FusionAhrs.o \
./code/Fusion/FusionCompass.o \
./code/Fusion/FusionOffset.o 


# Each subdirectory must supply rules for building sources it contributes
code/Fusion/%.src: ../code/Fusion/%.c code/Fusion/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS_Project/WLBF_MT_TC264_ZF_2024/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/code\/Fusion\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

code/Fusion/%.o: ./code/Fusion/%.src code/Fusion/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code-2f-Fusion

clean-code-2f-Fusion:
	-$(RM) ./code/Fusion/FusionAhrs.d ./code/Fusion/FusionAhrs.o ./code/Fusion/FusionAhrs.src ./code/Fusion/FusionCompass.d ./code/Fusion/FusionCompass.o ./code/Fusion/FusionCompass.src ./code/Fusion/FusionOffset.d ./code/Fusion/FusionOffset.o ./code/Fusion/FusionOffset.src

.PHONY: clean-code-2f-Fusion

