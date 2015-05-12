################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/converter.cpp \
../src/helper.cpp \
../src/main.cpp \
../src/unittest.cpp 

OBJS += \
./src/converter.o \
./src/helper.o \
./src/main.o \
./src/unittest.o 

CPP_DEPS += \
./src/converter.d \
./src/helper.d \
./src/main.d \
./src/unittest.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


