#pragma once

/* Настройки сервоприводов */

#define BASE_A_PIN 5
#define BASE_A_START_POS 0
#define BASE_A_END_POS 70
#define BASE_A_SPEED 30
#define BASE_A_ACCEL 30
#define BASE_A_PAUSE 5000 // мс
#define BASE_A_MIN_PWM 500
#define BASE_A_MAX_PWM 2400

#define BASE_B_PIN 6
#define BASE_B_START_POS 0
#define BASE_B_END_POS 100
#define BASE_B_SPEED 30
#define BASE_B_ACCEL 30
#define BASE_B_PAUSE 5000 // мс
#define BASE_B_MIN_PWM 500
#define BASE_B_MAX_PWM 2400

#define COMP_A_STEPS 200
#define COMP_A_EN 7
#define COMP_A_DIR 8
#define COMP_A_STEP 9

#define COMP_B_STEPS 200
#define COMP_B_EN 13
#define COMP_B_DIR 12
#define COMP_B_STEP 11

#define CLAPAN_PIN A1
#define PUMP_PIN A2
#define MIXER_PIN A4

/* Настройки нагревателя */