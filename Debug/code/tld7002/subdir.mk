################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/tld7002/user_tld7002.c \
../code/tld7002/zf_device_dot_matrix_screen.c \
../code/tld7002/zf_device_tld7002.c 

COMPILED_SRCS += \
./code/tld7002/user_tld7002.src \
./code/tld7002/zf_device_dot_matrix_screen.src \
./code/tld7002/zf_device_tld7002.src 

C_DEPS += \
./code/tld7002/user_tld7002.d \
./code/tld7002/zf_device_dot_matrix_screen.d \
./code/tld7002/zf_device_tld7002.d 

OBJS += \
./code/tld7002/user_tld7002.o \
./code/tld7002/zf_device_dot_matrix_screen.o \
./code/tld7002/zf_device_tld7002.o 


# Each subdirectory must supply rules for building sources it contributes
code/tld7002/%.src: ../code/tld7002/%.c code/tld7002/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS_Project/WLBF_MT_TC264_ZF_2024/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/code\/tld7002\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

code/tld7002/%.o: ./code/tld7002/%.src code/tld7002/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code-2f-tld7002

clean-code-2f-tld7002:
	-$(RM) ./code/tld7002/user_tld7002.d ./code/tld7002/user_tld7002.o ./code/tld7002/user_tld7002.src ./code/tld7002/zf_device_dot_matrix_screen.d ./code/tld7002/zf_device_dot_matrix_screen.o ./code/tld7002/zf_device_dot_matrix_screen.src ./code/tld7002/zf_device_tld7002.d ./code/tld7002/zf_device_tld7002.o ./code/tld7002/zf_device_tld7002.src

.PHONY: clean-code-2f-tld7002

