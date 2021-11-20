################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Controller.c \
../Employee.c \
../LinkedList.c \
../Menu.c \
../ValidarPedir.c \
../main.c \
../parser.c 

OBJS += \
./Controller.o \
./Employee.o \
./LinkedList.o \
./Menu.o \
./ValidarPedir.o \
./main.o \
./parser.o 

C_DEPS += \
./Controller.d \
./Employee.d \
./LinkedList.d \
./Menu.d \
./ValidarPedir.d \
./main.d \
./parser.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


