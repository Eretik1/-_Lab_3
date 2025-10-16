#ifndef DS18B20_H
#define DS18B20_H

#include <stdint.h>
#include <stdlib.h>

// Команды поиска и адресации устройств
#define DS18B20_CMD_SEARCH_ROM          0xF0    ///< Поиск ROM-кодов подключенных устройств
#define DS18B20_CMD_READ_ROM            0x33    ///< Чтение ROM-кода (только для одного устройства)
#define DS18B20_CMD_MATCH_ROM           0x55    ///< Адресация конкретного устройства
#define DS18B20_CMD_SKIP_ROM            0xCC    ///< Широковещательная команда всем устройствам
#define DS18B20_CMD_ALARM_SEARCH        0xEC    ///< Поиск устройств с установленным Alarm flag

// Команды работы с температурой
#define DS18B20_CMD_CONVERT_T           0x44    ///< Запуск преобразования температуры
#define DS18B20_CMD_READ_SCRATCHPAD     0xBE    ///< Чтение данных из Scratchpad (9 байт)
#define DS18B20_CMD_WRITE_SCRATCHPAD    0x4E    ///< Запись данных в Scratchpad (TH, TL, Configuration)
#define DS18B20_CMD_COPY_SCRATCHPAD     0x48    ///< Копирование данных из Scratchpad в EEPROM
#define DS18B20_CMD_RECALL_E2           0xB8    ///< Копирование данных из EEPROM в Scratchpad
#define DS18B20_CMD_READ_POWER_SUPPLY   0xB4    ///< Чтение способа питания датчиков

typedef struct {
    uint8_t temperature_lsb;
    int8_t temperature_msb;
    uint8_t user_byte_1;
    uint8_t user_byte_2;
    uint8_t configuration;
    uint8_t reserved_1;
    uint8_t reserved_2;
    uint8_t reserved_3;
    uint8_t crc;
    
    float temperature_log[100];
    uint8_t log_index;
    uint8_t log_count;
    uint8_t is_initialized;
    uint8_t is_parasitic_power;
} ds18b20_data_t;

extern ds18b20_data_t* ds18b20_data;

void ds18b20_init(ds18b20_data_t *ds18b20_data);
void ds18b20_fill_with_test_data(void);
void ds18b20_cleanup(void);
void ds18b20_print_structure(void);

#endif 