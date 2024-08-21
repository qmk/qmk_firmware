/*
Copyright 2023 RephlexZero (@RephlexZero)
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/

#ifndef CUSTOM_ANALOG_H
#define CUSTOM_ANALOG_H
#ifndef MUXES
#    define MUXES 0
#endif
/*
#if MUXES != 0
#    include "hal.h"

// Constants
#    define SAMPLE_BUFFER_SIZE 2 // Adjust as necessary
#    define MUXES 0              // Number of multiplexer lines, adjust as necessary

// Type Definitions
typedef struct {
    adcsample_t  sampleBuffer1[SAMPLE_BUFFER_SIZE];
    adcsample_t  sampleBuffer2[SAMPLE_BUFFER_SIZE];
    adcsample_t  sampleBuffer4[SAMPLE_BUFFER_SIZE];
    volatile int completedConversions;
    semaphore_t  sem;
} ADCManager;

// Extern ADCManager instance
extern ADCManager adcManager;

// Function Prototypes
void        initADCGroups(ADCManager *adcManager);
msg_t       adcStartAllConversions(ADCManager *adcManager);
void        adcErrorCallback(ADCDriver *adcp, adcerror_t err);
adcsample_t getADCSample(const ADCManager *adcManager, uint8_t muxIndex);

#else */
#    include "analog.h"
//#endif

#endif // CUSTOM_ANALOG_H
