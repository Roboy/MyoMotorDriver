#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=/home/letrend/MPLABXProjects/motorDriver.X/src/DEEEmulation.c /home/letrend/MPLABXProjects/motorDriver.X/src/FlashOperations.s /home/letrend/MPLABXProjects/motorDriver.X/src/adc.c /home/letrend/MPLABXProjects/motorDriver.X/src/can.c /home/letrend/MPLABXProjects/motorDriver.X/src/dma.c /home/letrend/MPLABXProjects/motorDriver.X/src/initIO.c /home/letrend/MPLABXProjects/motorDriver.X/src/main.c /home/letrend/MPLABXProjects/motorDriver.X/src/motorControl.c /home/letrend/MPLABXProjects/motorDriver.X/src/pwm.c /home/letrend/MPLABXProjects/motorDriver.X/src/qei.c /home/letrend/MPLABXProjects/motorDriver.X/src/spiFunctions.c /home/letrend/MPLABXProjects/motorDriver.X/src/timers.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/989757633/DEEEmulation.o ${OBJECTDIR}/_ext/989757633/FlashOperations.o ${OBJECTDIR}/_ext/989757633/adc.o ${OBJECTDIR}/_ext/989757633/can.o ${OBJECTDIR}/_ext/989757633/dma.o ${OBJECTDIR}/_ext/989757633/initIO.o ${OBJECTDIR}/_ext/989757633/main.o ${OBJECTDIR}/_ext/989757633/motorControl.o ${OBJECTDIR}/_ext/989757633/pwm.o ${OBJECTDIR}/_ext/989757633/qei.o ${OBJECTDIR}/_ext/989757633/spiFunctions.o ${OBJECTDIR}/_ext/989757633/timers.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/989757633/DEEEmulation.o.d ${OBJECTDIR}/_ext/989757633/FlashOperations.o.d ${OBJECTDIR}/_ext/989757633/adc.o.d ${OBJECTDIR}/_ext/989757633/can.o.d ${OBJECTDIR}/_ext/989757633/dma.o.d ${OBJECTDIR}/_ext/989757633/initIO.o.d ${OBJECTDIR}/_ext/989757633/main.o.d ${OBJECTDIR}/_ext/989757633/motorControl.o.d ${OBJECTDIR}/_ext/989757633/pwm.o.d ${OBJECTDIR}/_ext/989757633/qei.o.d ${OBJECTDIR}/_ext/989757633/spiFunctions.o.d ${OBJECTDIR}/_ext/989757633/timers.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/989757633/DEEEmulation.o ${OBJECTDIR}/_ext/989757633/FlashOperations.o ${OBJECTDIR}/_ext/989757633/adc.o ${OBJECTDIR}/_ext/989757633/can.o ${OBJECTDIR}/_ext/989757633/dma.o ${OBJECTDIR}/_ext/989757633/initIO.o ${OBJECTDIR}/_ext/989757633/main.o ${OBJECTDIR}/_ext/989757633/motorControl.o ${OBJECTDIR}/_ext/989757633/pwm.o ${OBJECTDIR}/_ext/989757633/qei.o ${OBJECTDIR}/_ext/989757633/spiFunctions.o ${OBJECTDIR}/_ext/989757633/timers.o

# Source Files
SOURCEFILES=/home/letrend/MPLABXProjects/motorDriver.X/src/DEEEmulation.c /home/letrend/MPLABXProjects/motorDriver.X/src/FlashOperations.s /home/letrend/MPLABXProjects/motorDriver.X/src/adc.c /home/letrend/MPLABXProjects/motorDriver.X/src/can.c /home/letrend/MPLABXProjects/motorDriver.X/src/dma.c /home/letrend/MPLABXProjects/motorDriver.X/src/initIO.c /home/letrend/MPLABXProjects/motorDriver.X/src/main.c /home/letrend/MPLABXProjects/motorDriver.X/src/motorControl.c /home/letrend/MPLABXProjects/motorDriver.X/src/pwm.c /home/letrend/MPLABXProjects/motorDriver.X/src/qei.c /home/letrend/MPLABXProjects/motorDriver.X/src/spiFunctions.c /home/letrend/MPLABXProjects/motorDriver.X/src/timers.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC802
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/989757633/DEEEmulation.o: /home/letrend/MPLABXProjects/motorDriver.X/src/DEEEmulation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/DEEEmulation.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/DEEEmulation.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/DEEEmulation.c  -o ${OBJECTDIR}/_ext/989757633/DEEEmulation.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/DEEEmulation.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/DEEEmulation.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/adc.o: /home/letrend/MPLABXProjects/motorDriver.X/src/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/adc.c  -o ${OBJECTDIR}/_ext/989757633/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/can.o: /home/letrend/MPLABXProjects/motorDriver.X/src/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/can.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/can.c  -o ${OBJECTDIR}/_ext/989757633/can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/can.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/dma.o: /home/letrend/MPLABXProjects/motorDriver.X/src/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/dma.c  -o ${OBJECTDIR}/_ext/989757633/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/dma.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/initIO.o: /home/letrend/MPLABXProjects/motorDriver.X/src/initIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/initIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/initIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/initIO.c  -o ${OBJECTDIR}/_ext/989757633/initIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/initIO.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/initIO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/main.o: /home/letrend/MPLABXProjects/motorDriver.X/src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/main.c  -o ${OBJECTDIR}/_ext/989757633/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/motorControl.o: /home/letrend/MPLABXProjects/motorDriver.X/src/motorControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/motorControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/motorControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/motorControl.c  -o ${OBJECTDIR}/_ext/989757633/motorControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/motorControl.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/motorControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/pwm.o: /home/letrend/MPLABXProjects/motorDriver.X/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/pwm.c  -o ${OBJECTDIR}/_ext/989757633/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/pwm.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/qei.o: /home/letrend/MPLABXProjects/motorDriver.X/src/qei.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/qei.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/qei.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/qei.c  -o ${OBJECTDIR}/_ext/989757633/qei.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/qei.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/qei.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/spiFunctions.o: /home/letrend/MPLABXProjects/motorDriver.X/src/spiFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/spiFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/spiFunctions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/spiFunctions.c  -o ${OBJECTDIR}/_ext/989757633/spiFunctions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/spiFunctions.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/spiFunctions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/timers.o: /home/letrend/MPLABXProjects/motorDriver.X/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/timers.c  -o ${OBJECTDIR}/_ext/989757633/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/timers.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1    -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/_ext/989757633/DEEEmulation.o: /home/letrend/MPLABXProjects/motorDriver.X/src/DEEEmulation.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/DEEEmulation.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/DEEEmulation.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/DEEEmulation.c  -o ${OBJECTDIR}/_ext/989757633/DEEEmulation.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/DEEEmulation.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/DEEEmulation.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/adc.o: /home/letrend/MPLABXProjects/motorDriver.X/src/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/adc.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/adc.c  -o ${OBJECTDIR}/_ext/989757633/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/adc.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/can.o: /home/letrend/MPLABXProjects/motorDriver.X/src/can.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/can.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/can.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/can.c  -o ${OBJECTDIR}/_ext/989757633/can.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/can.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/can.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/dma.o: /home/letrend/MPLABXProjects/motorDriver.X/src/dma.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/dma.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/dma.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/dma.c  -o ${OBJECTDIR}/_ext/989757633/dma.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/dma.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/dma.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/initIO.o: /home/letrend/MPLABXProjects/motorDriver.X/src/initIO.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/initIO.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/initIO.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/initIO.c  -o ${OBJECTDIR}/_ext/989757633/initIO.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/initIO.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/initIO.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/main.o: /home/letrend/MPLABXProjects/motorDriver.X/src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/main.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/main.c  -o ${OBJECTDIR}/_ext/989757633/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/main.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/motorControl.o: /home/letrend/MPLABXProjects/motorDriver.X/src/motorControl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/motorControl.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/motorControl.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/motorControl.c  -o ${OBJECTDIR}/_ext/989757633/motorControl.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/motorControl.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/motorControl.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/pwm.o: /home/letrend/MPLABXProjects/motorDriver.X/src/pwm.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/pwm.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/pwm.c  -o ${OBJECTDIR}/_ext/989757633/pwm.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/pwm.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/pwm.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/qei.o: /home/letrend/MPLABXProjects/motorDriver.X/src/qei.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/qei.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/qei.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/qei.c  -o ${OBJECTDIR}/_ext/989757633/qei.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/qei.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/qei.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/spiFunctions.o: /home/letrend/MPLABXProjects/motorDriver.X/src/spiFunctions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/spiFunctions.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/spiFunctions.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/spiFunctions.c  -o ${OBJECTDIR}/_ext/989757633/spiFunctions.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/spiFunctions.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/spiFunctions.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/_ext/989757633/timers.o: /home/letrend/MPLABXProjects/motorDriver.X/src/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/timers.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/timers.c  -o ${OBJECTDIR}/_ext/989757633/timers.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/_ext/989757633/timers.o.d"        -g -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/timers.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/989757633/FlashOperations.o: /home/letrend/MPLABXProjects/motorDriver.X/src/FlashOperations.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/FlashOperations.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/FlashOperations.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/FlashOperations.s  -o ${OBJECTDIR}/_ext/989757633/FlashOperations.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/_ext/989757633/FlashOperations.o.d",--defsym=__MPLAB_BUILD=1,--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_ICD3=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/FlashOperations.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/_ext/989757633/FlashOperations.o: /home/letrend/MPLABXProjects/motorDriver.X/src/FlashOperations.s  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/_ext/989757633" 
	@${RM} ${OBJECTDIR}/_ext/989757633/FlashOperations.o.d 
	@${RM} ${OBJECTDIR}/_ext/989757633/FlashOperations.o 
	${MP_CC} $(MP_EXTRA_AS_PRE)  /home/letrend/MPLABXProjects/motorDriver.X/src/FlashOperations.s  -o ${OBJECTDIR}/_ext/989757633/FlashOperations.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  -Wa,-MD,"${OBJECTDIR}/_ext/989757633/FlashOperations.o.d",--defsym=__MPLAB_BUILD=1,-g,--no-relax$(MP_EXTRA_AS_POST)
	@${FIXDEPS} "${OBJECTDIR}/_ext/989757633/FlashOperations.o.d"  $(SILENT)  -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG=__DEBUG -D__MPLAB_DEBUGGER_ICD3=1  -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D__DEBUG=__DEBUG,--defsym=__MPLAB_DEBUGGER_ICD3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/motorDriver.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
