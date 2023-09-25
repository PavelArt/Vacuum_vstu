#include "parser.h"
#include "Arduino.h"

Parser::Parser(Vacuum* _vacuum, UpDown* _updown, Mixer* _mixer, Cup* _cup_a, Cup* _cup_b, Memory* _memory, Display* _display, Automode* _automode) {
    this->automode = _automode;
    this->cup_a = _cup_a;
    this->cup_b = _cup_b;
    this->mixer = _mixer;
    this->updown = _updown;
    this->vacuum = _vacuum;
    this->memory = _memory;
    this->display = _display;
    
}

void Parser::parse(byte buffer[50], size_t length) {
    String filename;
    byte buf[16];
    byte k = 0;
    if (length > 4) {
        for (size_t i = 1; i < length; i++) {
            filename += (char)buffer[i];
        }
    }
    bool debug = false;
    long value = (long)buffer[1] + (long)buffer[2] * 256 + (long)buffer[3] * 65536;
    switch (buffer[0]) {

        /*  Управление миксером и верх-низом  */

        case 0x01:  /* Запуск калибровки */
            if (debug) Serial.println("Calibration started");
            updown->calibration();
            break;

        case 0x02:  /* Запуск процесса перемешивания */
            if (debug) Serial.println("Runtime for all");
            updown->calculate();
            updown->runTime();
            mixer->runTime();
            break;

        case 0x03:  /* Перемещение вверх до упора */ 
            if (debug) Serial.println("updown to Up");
            updown->toUp();
            break;

        case 0x04:  /* Перемещение вниз до упора */
            if (debug) Serial.println("updown to Down");
            /* code */
            break;

        case 0x05:  /* Остановить всё */
            if (debug) Serial.println("updown and mixer break");
            mixer->setMode(0);
            updown->setMode(0);
            mixer->brake();
            updown->brake();
            break;
        
        case 0x06:  /* Установка времени перемешивания */
            if (debug) Serial.println("setting time (mixer and updown): " + String(value));
            mixer->setTime(value);
            updown->setTime(value);
            break;

        case 0x07:  /* Установка количества циклов */
            if (debug) Serial.println("setting cycles (updown): " + String(value));
            updown->setNumberCycles(value);
            break;
        
        case 0x08:  /* Установка скорости вращения миксера */
            if (debug) Serial.println("setting speed (mixer): " + String(value));
            mixer->setSpeed(value);
            break;

        case 0x09:  /* Установка процента высоты подъема при перемешивании */
            if (debug) Serial.println("setting percent (updown):" + String(value));
            updown->setPercent(value);
            this->memory->newWriteParam(KEY_UPDOWN_PERCENT, value);
            break;

        case 0x0A:  /* Ручная установка калибровочных данных */
            if (debug) Serial.println("setting full length: " + String(value));
            updown->setFullLength(value); 
            this->memory->newWriteParam(KEY_UPDOWN_FULLLENGTH, value);
            break;

        case 0x0B:  /* Текущая позиция в шагах верх-низа */
            current_updown = updown->getCurrent();
            if (debug) Serial.println("current updown: " + String(current_updown));
            break;

        case 0x0C:  /* Сделать расчет  */
            if (debug) Serial.println("updown calculate");
            updown->calculate();
            break;

        case 0x0D:  /* Запустить только миксер */
            if (debug) Serial.println("run only mixer");
            mixer->run();
            break;

        case 0x0E:  /* Остановить только миксер */
            if (debug) Serial.println("stop only mixer");
            mixer->stop();
            break;

        case 0x0F:  /* Резко остановить только миксер */
            if (debug) Serial.println("break only mixer");
            mixer->brake();
            break;

        case 0x10:  /* Запустить только миксер на n-е время */
            if (debug) Serial.println("run only mixer in time");
            mixer->runTime();
            break;

        case 0x11:  /* Задать время работы только миксеру */
            if (debug) Serial.println("set time for mixer only" + String(value));
            mixer->setTime(value);
            break;

        case 0x12:  /* Задать ускорение миксеру */
            if (debug) Serial.println("set accel for mixer only" + String(value));
            mixer->setAccel(value);
            break;

        case 0x13:  /* Запустить только верх-низ на n-е время */
            if (debug) Serial.println("start updown in time");
            updown->runTime();
            break;

        case 0x14:  /* Резерв для системы перемешивания */

            break;
        
        case 0x15:  /* Резерв для системы перемешивания */
            /* code */
            break;

        /*  Работа со стаканами  */

        case 0x16:  /* Получить текущее положение стакана A */
            current_a_cup = cup_a->getCurrent();
            if (debug) Serial.println("current cup A: " + String(current_a_cup));
            break;

        case 0x17:  /* Получить текущее положение стакана В */
            current_b_cup = cup_b->getCurrent();
            if (debug) Serial.println("current cup B: " + String(current_b_cup));
            break;
        
        case 0x18:  /* Установить стартовую позицию стакана А */
            if (debug) Serial.println("set startpos A: " + String(value));
            cup_a->setStartPos(value);
            this->memory->newWriteParam(KEY_SERVO_A_START, value);
            break;

        case 0x19:  /* Установить стартовую позицию стакана B */
            if (debug) Serial.println("set startpos B: " + String(value));
            cup_b->setStartPos(value);
            this->memory->newWriteParam(KEY_SERVO_B_START, value);
            break;

        case 0x1A:  /* Установить конечную позицию стакана A */
            if (debug) Serial.println("set endpos A: " + String(value));
            cup_a->setEndPos(value);
            this->memory->newWriteParam(KEY_SERVO_A_END, value);
            break;
        
        case 0x1B:  /* Установить конечную позицию стакана B */
            if (debug) Serial.println("set endpos B: " + String(value));
            cup_b->setEndPos(value);
            this->memory->newWriteParam(KEY_SERVO_B_END, value);
            break;
        
        case 0x1C:  /* Установить ускорение стакана А*/
            if (debug) Serial.println("set accel A: " + String(value));
            cup_a->setAccel(value);
            this->memory->newWriteParam(KEY_SERVO_A_ACCEL, value);
            break;

        case 0x1D:  /* Установить ускорение стакана В*/
            if (debug) Serial.println("set accel B: " + String(value));
            cup_b->setAccel(value);
            this->memory->newWriteParam(KEY_SERVO_B_ACCEL, value);
            break;

        case 0x1E:  /* Установить скорость стакана А */
            if (debug) Serial.println("set speed A: " + String(value));
            cup_a->setSpeed(value);
            this->memory->newWriteParam(KEY_SERVO_A_SPEED, value);
            break;

        case 0x1F:  /* Установить скорость стакана В */
            if (debug) Serial.println("set speed B: " + String(value));
            cup_b->setSpeed(value);
            this->memory->newWriteParam(KEY_SERVO_B_SPEED, value);
            break;

        case 0x20:  /* Стакан А в стартовую позицию */
            if (debug) Serial.println("A to start ");
            cup_a->toStartPos();
            break;

        case 0x21:  /* Стакан В в стартовую позицию */
            if (debug) Serial.println("B to start ");
            cup_b->toStartPos();
            break;

        case 0x22:  /* Стакан A в конечную позицию */
            if (debug) Serial.println("A to end ");
            cup_a->toEndPos();
            break;

        case 0x23:  /* Стакан В в конечную позицию */
            if (debug) Serial.println("B to end ");
            cup_b->toEndPos();
            break;

        case 0x24:  /* Стакан А в точку */
            if (debug) Serial.println("A to point: " + String(value));
            cup_a->toPoint(value);
            break;

        case 0x25:  /* Стакан В в точку */
            if (debug) Serial.println("B to point: " + String(value));
            cup_b->toPoint(value);
            break;

        case 0x26:  /* Резерв для стаканов */
            break;
        
        case 0x27:  /* Резерв для стаканов */
            break;
        
        case 0x28:  /* Резерв для стаканов */
            break;
        
        case 0x29: /* Резерв для стаканов */
            break;
        
        /*  Команды для работы с давлением   */

        case 0x2A: /* Выключение клапана */
            if (debug) Serial.println("clapan off");
            vacuum->clapanOff();
            break;

        case 0x2B: /* Включение клапана */
            if (debug) Serial.println("clapan on");
            vacuum->clapanOn();
            break;

        case 0x2C: /* Выключение компрессора */
            if (debug) Serial.println("compressor off");
            vacuum->compOff();
            break;

        case 0x2D: /* Включение компрессора */
            if (debug) Serial.println("clapan on");
            vacuum->compOn();
            break;

        case 0x2E: /* Измерить давление */
            pressure = vacuum->measure();
            if (debug) Serial.println("pressure now: " + String(pressure));
            break;

        case 0x2F: /* Изменить границы, в которых будет держаться давление */
            if (debug) Serial.println("set border: " + String(value));
            vacuum->setBorderValue(value);
            this->memory->newWriteParam(KEY_BORDER_PRESSURE, value);
            break;

        case 0x30: /* Установить необходимое значение давления */
            if (debug) Serial.println("set need pressure: " + String(value));
            vacuum->setNeedValue(value);
            break;

        case 0x31: /* Запустить поддержание давления */
            if (debug) Serial.println("start vacuum");
            vacuum->start();
            break;

        case 0x32: /* Остановить поддержание давления (сбросить давление) */
            if (debug) Serial.println("stop vacuum: " + String(value));
            vacuum->stop();
            break;

        case 0x33: /* Остановить всё с давлением */
            if (debug) Serial.println("stop all vacuum");
            vacuum->clapanOff();
            vacuum->compOff();
            vacuum->brake();
            break;

        case 0x34: /* Резерв для давления */
            break;

        case 0x35: /* Резерв для давления */
            break;

        case 0x36: /* Резерв для давления */
            //memory->printFile("config.ini");
            break;

        /* Команды для работы с памятью */

        case 0x37: /* Запрос данных по servo a */
            this->display->setServoAStart(this->cup_a->start_pos);
            this->display->setServoAStop(this->cup_a->end_pos);
            this->display->setServoASpeed(this->cup_a->speed);
            this->display->setServoAAccel(this->cup_a->accel);
            break;

        case 0x38: /* Запрос данных по servo b */
            this->display->setServoBStart(this->cup_b->start_pos);
            this->display->setServoBStop(this->cup_b->end_pos);
            this->display->setServoBSpeed(this->cup_b->speed);
            this->display->setServoBAccel(this->cup_b->accel);
            break;

        case 0x39: /* Запрос данных по узлу смешивания */
            this->display->setPercent(this->updown->percent);
            this->display->setFullLength(this->updown->full_length);
            break;

        case 0x3A: /* Открыть config-файл */
            this->memory->newOpenFile("config.hex");
            break;

        case 0x3B: /* Записать все данные и закрыть Config-файл */
            this->memory->newWriteFile();
            for (int i = 0; i < memory->fl.arr_size; i++) {
                DEBUG_MESSAGE(String(memory->fl.arr_bytes[i]));
            }
            DEBUG_MESSAGE("IM HERE");
            break;

        case 0x3C: /* Считать все данные из конфигураций */
            this->memory->listFiles();
            break;

        case 0x3D: /* Очистить FileNames */
            this->memory->clearFileNames();
            break;

        case 0x3E: /* Следующая/предыдущая страница конфигураций */
            this->display->setCfgs(value);
            break;

        case 0x3F: /* automode */
            this->automode->setTimeServoA(value);
            break;

        case 0x40: /*  */
            this->automode->setTimeServoB(value);
            break;

        case 0x41: /*  */
            this->automode->start();
            break;

        case 0x42: /* test */
            automode->mode = 5;
            break;

        case 0x43: /* Открытие файла конфигурации авторежима */
            if (!(memory->openFile(filename, buf))) {
                break;
            }
            union {
		        byte bytes[4];
		        long number;
	        } data;

            for (size_t i = 0; i < 4; i++) {
                data.bytes[k] = buf[i];
                k++;
            };
            this->mixer->setTime(data.number);
            this->updown->setTime(data.number);

            k = 0;
            for (size_t i = 4; i < 8; i++) {
                data.bytes[k] = buf[i];
                k++;
            };
            this->mixer->setSpeed(data.number);

            k = 0;
            for (size_t i = 8; i < 12; i++) {
                data.bytes[k] = buf[i];
                k++;
            };
            this->updown->setNumberCycles(data.number);

            k = 0;
            for (size_t i = 12; i < 16; i++) {
                data.bytes[k] = buf[i];
                k++;
            };
            this->vacuum->setNeedValue(data.number);
            break;

        case 0x44: /* Запрос данных по авторежиму */
            this->display->setAutoTime(this->updown->time);
            this->display->setAutoSpeed(this->mixer->speed);
            this->display->setAutoCycles(this->updown->cycles);
            this->display->setAutoPres(this->vacuum->need_value);
            break;

        case 0x45: /* Открыть или создать файл */
            this->memory->newOpenFile(filename);
            DEBUG_MESSAGE("File opened");
            DEBUG_MESSAGE("file type: " + String(memory->fl.file_type) + " arr_size: " + String(memory->fl.arr_size) + " err:" + String(memory->fl.err));
            break;

        case 0x46: /* Обновить все поля в режиме Automode */
            this->display->setAutoTime(this->updown->time);
            this->display->setAutoSpeed(this->mixer->speed);
            this->display->setAutoCycles(this->updown->cycles);
            this->display->setAutoPres(this->vacuum->need_value);
            break;

        case 0x47: /* Открыть файл авторежима и записать данные в дисплей */
            if (this->memory->newOpenFile("configs/" + filename)) {
                if (this->memory->newGetFileType() == TYPE_USER_CONFIG) {
                    this->display->setAutoTime(this->memory->newReadParam(KEY_AUTO_TIME_MIXING));
                    this->display->setAutoCycles(this->memory->newReadParam(KEY_AUTO_NUMBER_CYCLES));
                    this->display->setAutoSpeed(this->memory->newReadParam(KEY_AUTO_MIXER_SPEED));
                    this->display->setAutoPres(this->memory->newReadParam(KEY_AUTO_NEED_PRES));
                    this->memory->newCloseFile();
                }
            }
            break;
        case 0x48:
            this->memory->newWriteParam(KEY_AUTO_MIXER_SPEED, value);
            break;
        case 0x49:
            this->memory->newWriteParam(KEY_AUTO_NEED_PRES, value);
            break;
        case 0x4A:
            this->memory->newWriteParam(KEY_AUTO_NUMBER_CYCLES, value);
            break;
        case 0x4B:
            this->memory->newWriteParam(KEY_AUTO_TIME_MIXING, value);
            break;
        case 0x4C:
            break;
        case 0x4D:
            break;
        case 0x4E:
            break;

        default:
            break;
        }
    if (debug) {
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);
    }
}