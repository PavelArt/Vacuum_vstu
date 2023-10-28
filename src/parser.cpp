#include "parser.h"
#include "servos.h"
#include "responses.h"

Parser::Parser(Servos* _servo_a, Servos* _servo_b) {
    this->servo_a = _servo_a;
    this->servo_b = _servo_b;
}

void Parser::parse(byte buffer[50], size_t length) {
    byte command = buffer[0];
    long int value = buffer[1] + buffer[2] * 256 + buffer[3] * 65536;

    switch (command) {

        /* Стакан с компонентом А */

        case PARS_SERVO_A_SET_START_POS:  
            this->servo_a->setStartPos(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_A_SET_END_POS:
            this->servo_a->setEndPos(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_A_SET_SPEED:
            this->servo_a->setSpeed(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_A_SET_ACCEL:
            this->servo_a->setAccel(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_A_SET_MIN_PWM:
            this->servo_a->setMinPWM(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_A_SET_MAX_PWM:
            this->servo_a->setMaxPWM(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_A_TO_START:
            this->servo_a->toStartPos();
            Responses::answer(command, value);
            break;
        
        case PARS_SERVO_A_TO_END:
            this->servo_a->toEndPos();
            Responses::answer(command, value);
            break;

        case PARS_SERVO_A_TO_POS:
            this->servo_a->toPoint(value);
            Responses::answer(command, value);
            break;
        
        case PARS_SERVO_A_INIT:
            this->servo_a->config();
            Responses::answer(command, value);
            break;
        
        /* Стакан с компонентом В */

        case PARS_SERVO_B_SET_START_POS:  
            this->servo_b->setStartPos(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_B_SET_END_POS:
            this->servo_b->setEndPos(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_B_SET_SPEED:
            this->servo_b->setSpeed(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_B_SET_ACCEL:
            this->servo_b->setAccel(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_B_SET_MIN_PWM:
            this->servo_b->setMinPWM(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_B_SET_MAX_PWM:
            this->servo_b->setMaxPWM(value);
            Responses::answer(command, value);
            break;

        case PARS_SERVO_B_TO_START:
            this->servo_b->toStartPos();
            Responses::answer(command, value);
            break;
        
        case PARS_SERVO_B_TO_END:
            this->servo_b->toEndPos();
            Responses::answer(command, value);
            break;

        case PARS_SERVO_B_TO_POS:
            this->servo_b->toPoint(value);
            Responses::answer(command, value);
            break;
        
        case PARS_SERVO_B_INIT:
            this->servo_b->config();
            Responses::answer(command, value);
            break;

        default:
            break;
    }
}