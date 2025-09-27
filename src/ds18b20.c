#include "ds18b20.h"
#include <string.h>
#include <stdio.h>

ds18b20_data_t* ds18b20_data = NULL;

void ds18b20_init(void) {
    ds18b20_data = (ds18b20_data_t*)malloc(sizeof(ds18b20_data_t));
    
    if (ds18b20_data == NULL) {
        printf("Error: Memory allocation failed!\n");
        return;
    }
    
    memset(ds18b20_data, 0, sizeof(ds18b20_data_t));
    
    ds18b20_data->reserved_1 = 0xFF;
    ds18b20_data->reserved_3 = 0x10;
    ds18b20_data->configuration = 0x7F;
    ds18b20_data->is_initialized = 1;
    
    printf("DS18B20 initialized at address: %p\n", (void*)ds18b20_data);
}

void ds18b20_cleanup(void) {
    if (ds18b20_data != NULL) {
        free(ds18b20_data);
        ds18b20_data = NULL;
    }
}

void ds18b20_fill_with_test_data(void) {
    if (ds18b20_data == NULL || !ds18b20_data->is_initialized) {
        printf("Error: DS18B20 not initialized!\n");
        return;
    }
    
    ds18b20_data->temperature_lsb = 0x50;
    ds18b20_data->temperature_msb = 0x05;
    ds18b20_data->user_byte_1 = 0xAA;
    ds18b20_data->user_byte_2 = 0xBB;
    ds18b20_data->configuration = 0x7F;
    ds18b20_data->reserved_1 = 0xFF;
    ds18b20_data->reserved_2 = 0x00;
    ds18b20_data->reserved_3 = 0x10;
    ds18b20_data->crc = 0x00;
    
    for (uint8_t i = 0; i < 100; i++) {
        ds18b20_data->temperature_log[i] = 20.0f + (i * 0.5f);
    }
    ds18b20_data->log_index = 0;
    ds18b20_data->log_count = 100;
}

float ds18b20_calculate_temperature(uint8_t lsb, uint8_t msb) {
    int16_t raw_temp = (msb << 8) | lsb;
    return (float)raw_temp / 16.0f;
}

void ds18b20_add_to_log(float temperature) {
    if (ds18b20_data == NULL || !ds18b20_data->is_initialized) return;
    
    if (ds18b20_data->log_count < 100) {
        ds18b20_data->log_count++;
    }
    
    ds18b20_data->temperature_log[ds18b20_data->log_index] = temperature;
    ds18b20_data->log_index = (ds18b20_data->log_index + 1) % 100;
}

float ds18b20_get_current_temperature(void) {
    if (ds18b20_data == NULL || !ds18b20_data->is_initialized) return 0.0f;
    
    return ds18b20_calculate_temperature(
        ds18b20_data->temperature_lsb,
        ds18b20_data->temperature_msb
    );
}

void ds18b20_print_structure(void) {
    if (ds18b20_data == NULL) {
        printf("Error: ds18b20_data is NULL\n");
        return;
    }
    
    printf("\n=== DS18B20 Structure Dump ===\n");
    printf("Structure address: %p\n", (void*)ds18b20_data);
    printf("Structure size: %zu bytes\n", sizeof(ds18b20_data_t));
    
    printf("\nScratchpad Data:\n");
    printf("Temperature LSB: 0x%02X\n", ds18b20_data->temperature_lsb);
    printf("Temperature MSB: 0x%02X\n", ds18b20_data->temperature_msb);
    printf("User Byte 1: 0x%02X\n", ds18b20_data->user_byte_1);
    printf("User Byte 2: 0x%02X\n", ds18b20_data->user_byte_2);
    printf("Configuration: 0x%02X\n", ds18b20_data->configuration);
    printf("Reserved 1: 0x%02X\n", ds18b20_data->reserved_1);
    printf("Reserved 2: 0x%02X\n", ds18b20_data->reserved_2);
    printf("Reserved 3: 0x%02X\n", ds18b20_data->reserved_3);
    printf("CRC: 0x%02X\n", ds18b20_data->crc);
    
    printf("\nStatus Flags:\n");
    printf("Initialized: %s\n", ds18b20_data->is_initialized ? "YES" : "NO");
    printf("Parasitic Power: %s\n", ds18b20_data->is_parasitic_power ? "YES" : "NO");
    printf("Log Count: %d\n", ds18b20_data->log_count);
    printf("Log Index: %d\n", ds18b20_data->log_index);
    
    printf("\nTemperature Log (first 5 entries):\n");
    for (int i = 0; i < 5 && i < ds18b20_data->log_count; i++) {
        printf("  Log[%d]: %.2f°C\n", i, ds18b20_data->temperature_log[i]);
    }
    
    float calculated_temp = ds18b20_calculate_temperature(
        ds18b20_data->temperature_lsb,
        ds18b20_data->temperature_msb
    );
    printf("Calculated Temperature: %.2f°C\n", calculated_temp);
    printf("================================\n\n");
}