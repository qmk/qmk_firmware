target_sources(qmk PUBLIC
${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/TIMv1/hal_gpt_lld.c
${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/TIMv1/hal_icu_lld.c
${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/TIMv1/hal_pwm_lld.c
)
target_include_directories(qmk PUBLIC ${CHIBIOS}/os/hal/ports/${MCU_PORT_NAME}/LLD/TIMv1)