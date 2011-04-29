################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Solarterm.cpp \
../src/ToFromLunar.cpp \
../src/eightchar.cpp \
../src/eightcharacter.cpp 

OBJS += \
./src/Solarterm.o \
./src/ToFromLunar.o \
./src/eightchar.o \
./src/eightcharacter.o 

CPP_DEPS += \
./src/Solarterm.d \
./src/ToFromLunar.d \
./src/eightchar.d \
./src/eightcharacter.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


