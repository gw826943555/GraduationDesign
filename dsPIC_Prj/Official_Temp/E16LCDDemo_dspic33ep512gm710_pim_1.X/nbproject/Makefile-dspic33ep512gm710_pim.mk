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
ifeq "$(wildcard nbproject/Makefile-local-dspic33ep512gm710_pim.mk)" "nbproject/Makefile-local-dspic33ep512gm710_pim.mk"
include nbproject/Makefile-local-dspic33ep512gm710_pim.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=dspic33ep512gm710_pim
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/E16LCDDemo_dspic33ep512gm710_pim_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/E16LCDDemo_dspic33ep512gm710_pim_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=system_config/exp16/dspic33ep512gm710_pim/system.c bsp/exp16/dspic33ep512gm710_pim/adc.c bsp/exp16/dspic33ep512gm710_pim/buttons.c bsp/exp16/dspic33ep512gm710_pim/lcd.c bsp/exp16/dspic33ep512gm710_pim/leds.c bsp/exp16/dspic33ep512gm710_pim/timer_1ms.c main.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o ${OBJECTDIR}/main.o
POSSIBLE_DEPFILES=${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o.d ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o.d ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o.d ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o.d ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o.d ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o.d ${OBJECTDIR}/main.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o ${OBJECTDIR}/main.o

# Source Files
SOURCEFILES=system_config/exp16/dspic33ep512gm710_pim/system.c bsp/exp16/dspic33ep512gm710_pim/adc.c bsp/exp16/dspic33ep512gm710_pim/buttons.c bsp/exp16/dspic33ep512gm710_pim/lcd.c bsp/exp16/dspic33ep512gm710_pim/leds.c bsp/exp16/dspic33ep512gm710_pim/timer_1ms.c main.c


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
	${MAKE}  -f nbproject/Makefile-dspic33ep512gm710_pim.mk dist/${CND_CONF}/${IMAGE_TYPE}/E16LCDDemo_dspic33ep512gm710_pim_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33EP512GM710
MP_LINKER_FILE_OPTION=,--script=p33EP512GM710.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o: system_config/exp16/dspic33ep512gm710_pim/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o.d 
	@${RM} ${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system_config/exp16/dspic33ep512gm710_pim/system.c  -o ${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o: bsp/exp16/dspic33ep512gm710_pim/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o.d 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/exp16/dspic33ep512gm710_pim/adc.c  -o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o: bsp/exp16/dspic33ep512gm710_pim/buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o.d 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/exp16/dspic33ep512gm710_pim/buttons.c  -o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o: bsp/exp16/dspic33ep512gm710_pim/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o.d 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/exp16/dspic33ep512gm710_pim/lcd.c  -o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o: bsp/exp16/dspic33ep512gm710_pim/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o.d 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/exp16/dspic33ep512gm710_pim/leds.c  -o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o: bsp/exp16/dspic33ep512gm710_pim/timer_1ms.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o.d 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/exp16/dspic33ep512gm710_pim/timer_1ms.c  -o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -mno-eds-warn  -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o: system_config/exp16/dspic33ep512gm710_pim/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o.d 
	@${RM} ${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system_config/exp16/dspic33ep512gm710_pim/system.c  -o ${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/system_config/exp16/dspic33ep512gm710_pim/system.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o: bsp/exp16/dspic33ep512gm710_pim/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o.d 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/exp16/dspic33ep512gm710_pim/adc.c  -o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o: bsp/exp16/dspic33ep512gm710_pim/buttons.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o.d 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/exp16/dspic33ep512gm710_pim/buttons.c  -o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/buttons.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o: bsp/exp16/dspic33ep512gm710_pim/lcd.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o.d 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/exp16/dspic33ep512gm710_pim/lcd.c  -o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/lcd.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o: bsp/exp16/dspic33ep512gm710_pim/leds.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o.d 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/exp16/dspic33ep512gm710_pim/leds.c  -o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/leds.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o: bsp/exp16/dspic33ep512gm710_pim/timer_1ms.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim" 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o.d 
	@${RM} ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  bsp/exp16/dspic33ep512gm710_pim/timer_1ms.c  -o ${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/bsp/exp16/dspic33ep512gm710_pim/timer_1ms.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/main.o.d 
	@${RM} ${OBJECTDIR}/main.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"      -mno-eds-warn  -g -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -ffunction-sections -O0 -I"bsp/exp16/dspic33ep512gm710_pim" -I"system_config/exp16/dspic33ep512gm710_pim" -I"." -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/E16LCDDemo_dspic33ep512gm710_pim_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/E16LCDDemo_dspic33ep512gm710_pim_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_REAL_ICE=1  -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x1000:0x101B -mreserve=data@0x101C:0x101D -mreserve=data@0x101E:0x101F -mreserve=data@0x1020:0x1021 -mreserve=data@0x1022:0x1023 -mreserve=data@0x1024:0x1027 -mreserve=data@0x1028:0x104F   -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_REAL_ICE=1,$(MP_LINKER_FILE_OPTION),--heap=256,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/E16LCDDemo_dspic33ep512gm710_pim_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/E16LCDDemo_dspic33ep512gm710_pim_1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_dspic33ep512gm710_pim=$(CND_CONF)  -no-legacy-libc  $(COMPARISON_BUILD)  -Wl,--local-stack,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--heap=256,--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/E16LCDDemo_dspic33ep512gm710_pim_1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/dspic33ep512gm710_pim
	${RM} -r dist/dspic33ep512gm710_pim

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
