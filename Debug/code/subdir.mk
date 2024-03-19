################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/opHot_basic_function.c \
../code/opHot_encoder.c \
../code/opHot_image_processing.c \
../code/opHot_image_show.c \
../code/opHot_motor.c \
../code/opHot_pid.c \
../code/opHot_steer.c \
../code/opHot_tracing.c \
../code/zf_myFunction.c 

COMPILED_SRCS += \
./code/opHot_basic_function.src \
./code/opHot_encoder.src \
./code/opHot_image_processing.src \
./code/opHot_image_show.src \
./code/opHot_motor.src \
./code/opHot_pid.src \
./code/opHot_steer.src \
./code/opHot_tracing.src \
./code/zf_myFunction.src 

C_DEPS += \
./code/opHot_basic_function.d \
./code/opHot_encoder.d \
./code/opHot_image_processing.d \
./code/opHot_image_show.d \
./code/opHot_motor.d \
./code/opHot_pid.d \
./code/opHot_steer.d \
./code/opHot_tracing.d \
./code/zf_myFunction.d 

OBJS += \
./code/opHot_basic_function.o \
./code/opHot_encoder.o \
./code/opHot_image_processing.o \
./code/opHot_image_show.o \
./code/opHot_motor.o \
./code/opHot_pid.o \
./code/opHot_steer.o \
./code/opHot_tracing.o \
./code/zf_myFunction.o 


# Each subdirectory must supply rules for building sources it contributes
code/%.src: ../code/%.c code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/opHotCar_Learning/opHotCar/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/code\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

code/%.o: ./code/%.src code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code

clean-code:
	-$(RM) ./code/opHot_basic_function.d ./code/opHot_basic_function.o ./code/opHot_basic_function.src ./code/opHot_encoder.d ./code/opHot_encoder.o ./code/opHot_encoder.src ./code/opHot_image_processing.d ./code/opHot_image_processing.o ./code/opHot_image_processing.src ./code/opHot_image_show.d ./code/opHot_image_show.o ./code/opHot_image_show.src ./code/opHot_motor.d ./code/opHot_motor.o ./code/opHot_motor.src ./code/opHot_pid.d ./code/opHot_pid.o ./code/opHot_pid.src ./code/opHot_steer.d ./code/opHot_steer.o ./code/opHot_steer.src ./code/opHot_tracing.d ./code/opHot_tracing.o ./code/opHot_tracing.src ./code/zf_myFunction.d ./code/zf_myFunction.o ./code/zf_myFunction.src

.PHONY: clean-code

