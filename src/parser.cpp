#include "parser.h"

Parser::Parser(Servos* _servo_a, Servos* _servo_b, PumpComp* _pump_comp_a, PumpComp* _pump_comp_b, Pressure* _pressure, Mixer* _mixer) {
    this->servo_a = _servo_a;
    this->servo_b = _servo_b;
    this->pump_comp_a = _pump_comp_a;
    this->pump_comp_b = _pump_comp_b;
    this->pressure = _pressure;
    this->mixer = _mixer;
}

void Parser::parse(byte buffer[50], size_t length) {
    byte tick_a;
    byte tick_b;
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

        case PARS_SERVO_A_ON_THE_MOVE:
            tick_a = this->servo_a->tick();
            Responses::answer(command, tick_a);
            break;

        case PARS_SERVO_B_ON_THE_MOVE:
            tick_b = this->servo_b->tick();
            Responses::answer(command, tick_b);
            break;

        
        
        case PARS_PUMP_A_START:
            pump_comp_a->RunMlManual(value);
            Responses::answer(command, value);
            break;

        case PARS_PUMP_A_STOP:
            pump_comp_a->StopManual();
            Responses::answer(command, value);
            break;

        case PARS_PUMP_A_SET_SPEED:
            pump_comp_a->SetSpeed(value);
            Responses::answer(command, value);
            break;

        case PARS_PUMP_A_SET_STEPS:
            pump_comp_a->SetSteps(value);
            Responses::answer(command, value);
            break;


        case PARS_PUMP_B_START:
            pump_comp_b->RunMlManual(value);
            Responses::answer(command, value);
            break;

        case PARS_PUMP_B_STOP:
            pump_comp_b->StopManual();
            Responses::answer(command, value);
            break;

        case PARS_PUMP_B_SET_SPEED:
            pump_comp_b->SetSpeed(value);
            Responses::answer(command, value);
            break;

        case PARS_PUMP_B_SET_STEPS:
            pump_comp_b->SetSteps(value);
            Responses::answer(command, value);
            break;

        

        case PARS_PRESSURE_START_CLAPAN:
            pressure->StartClapan();
            Responses::answer(command, value);
            break;
        
        case PARS_PRESSURE_STOP_CLAPAN:
            pressure->StopClapan();
            Responses::answer(command, value);
            break;

        case PARS_PRESSURE_START_PUMP:
            pressure->StartPump();
            Responses::answer(command, value);
            break;

        case PARS_PRESSURE_STOP_PUMP:
            pressure->StopPump();
            Responses::answer(command, value);
            break;


        
        case PARS_MIXER_START:
            mixer->StartMixer();
            Responses::answer(command, value);
            break;

        case PARS_MIXER_STOP:
            mixer->StopMixer();
            Responses::answer(command, value);
            break;

        case PARS_MIXER_SET_TIME:
            mixer->SetTime(value);
            Responses::answer(command, value);
            break;

        case PARS_MIXER_START_TIME:
            mixer->RunTime();
            Responses::answer(command, value);
            break;

        default:
            break;
    }
}