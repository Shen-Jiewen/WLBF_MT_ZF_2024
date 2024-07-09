################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/mahony/AHRS.c \
../code/mahony/MahonyAHRS.c \
../code/mahony/user_lib.c 

COMPILED_SRCS += \
./code/mahony/AHRS.src \
./code/mahony/MahonyAHRS.src \
./code/mahony/user_lib.src 

C_DEPS += \
./code/mahony/AHRS.d \
./code/mahony/MahonyAHRS.d \
./code/mahony/user_lib.d 

OBJS += \
./code/mahony/AHRS.o \
./code/mahony/MahonyAHRS.o \
./code/mahony/user_lib.o 


# Each subdirectory must supply rules for building sources it contributes
code/mahony/%.src: ../code/mahony/%.c code/mahony/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/ADS_Project/WLBF_MT_TC264_2024/Debug/TASKING_C_C___Compiler-Include_paths__-I_.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/code\/mahony\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

code/mahony/%.o: ./code/mahony/%.src code/mahony/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code-2f-mahony

clean-code-2f-mahony:
	-$(RM) ./code/mahony/AHRS.d ./code/mahony/AHRS.o ./code/mahony/AHRS.src ./code/mahony/MahonyAHRS.d ./code/mahony/MahonyAHRS.o ./code/mahony/MahonyAHRS.src ./code/mahony/user_lib.d ./code/mahony/user_lib.o ./code/mahony/user_lib.src

.PHONY: clean-code-2f-mahony

