################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/controller/ano.c \
../code/controller/balance.c \
../code/controller/beep.c \
../code/controller/menu.c \
../code/controller/pid.c \
../code/controller/user_key.c 

COMPILED_SRCS += \
./code/controller/ano.src \
./code/controller/balance.src \
./code/controller/beep.src \
./code/controller/menu.src \
./code/controller/pid.src \
./code/controller/user_key.src 

C_DEPS += \
./code/controller/ano.d \
./code/controller/balance.d \
./code/controller/beep.d \
./code/controller/menu.d \
./code/controller/pid.d \
./code/controller/user_key.d 

OBJS += \
./code/controller/ano.o \
./code/controller/balance.o \
./code/controller/beep.o \
./code/controller/menu.o \
./code/controller/pid.o \
./code/controller/user_key.o 


# Each subdirectory must supply rules for building sources it contributes
code/controller/%.src: ../code/controller/%.c code/controller/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS_Project/WLBF_MT_TC264_ZF_2024/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/code\/controller\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

code/controller/%.o: ./code/controller/%.src code/controller/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code-2f-controller

clean-code-2f-controller:
	-$(RM) ./code/controller/ano.d ./code/controller/ano.o ./code/controller/ano.src ./code/controller/balance.d ./code/controller/balance.o ./code/controller/balance.src ./code/controller/beep.d ./code/controller/beep.o ./code/controller/beep.src ./code/controller/menu.d ./code/controller/menu.o ./code/controller/menu.src ./code/controller/pid.d ./code/controller/pid.o ./code/controller/pid.src ./code/controller/user_key.d ./code/controller/user_key.o ./code/controller/user_key.src

.PHONY: clean-code-2f-controller

