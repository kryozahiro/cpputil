################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../cpputil/Application.cpp \
../cpputil/CreatableTest.cpp \
../cpputil/EnumUtilTest.cpp \
../cpputil/GenericIoTest.cpp \
../cpputil/MathUtilTest.cpp \
../cpputil/OpenMp.cpp \
../cpputil/ThreadPool.cpp \
../cpputil/Timer.cpp \
../cpputil/TimerTest.cpp \
../cpputil/main.cpp 

OBJS += \
./cpputil/Application.o \
./cpputil/CreatableTest.o \
./cpputil/EnumUtilTest.o \
./cpputil/GenericIoTest.o \
./cpputil/MathUtilTest.o \
./cpputil/OpenMp.o \
./cpputil/ThreadPool.o \
./cpputil/Timer.o \
./cpputil/TimerTest.o \
./cpputil/main.o 

CPP_DEPS += \
./cpputil/Application.d \
./cpputil/CreatableTest.d \
./cpputil/EnumUtilTest.d \
./cpputil/GenericIoTest.d \
./cpputil/MathUtilTest.d \
./cpputil/OpenMp.d \
./cpputil/ThreadPool.d \
./cpputil/Timer.d \
./cpputil/TimerTest.d \
./cpputil/main.d 


# Each subdirectory must supply rules for building sources it contributes
cpputil/%.o: ../cpputil/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++14 -O3 -march=native -fopenmp -pedantic -Wall -Wextra -pipe -c -fmessage-length=0 -Wno-unused-parameter -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


