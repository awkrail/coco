#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "error.h"

uint32_t shl32(uint32_t x, unsigned int bits);

// get/set registers
void WriteAddress(uint32_t address);
void WriteData(uint32_t value);
uint32_t ReadData();

// read PCI configuration settings
uint16_t ReadVendorId(uint8_t bus, uint8_t device, uint8_t function);
uint16_t ReadDeviceId(uint8_t bus, uint8_t device, uint8_t function);
uint8_t ReadHeaderType(uint8_t bus, uint8_t device, uint8_t function);
uint32_t ReadClassCode(uint8_t bus, uint8_t device, uint8_t function);
uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function);

bool IsSingleFunctionDevice(uint8_t header_type);

enum Error ScanDevice(uint8_t bus, uint8_t device);
enum Error ScanFunction(uint8_t bus, uint8_t device, 
                          uint8_t function);
enum Error AddDevice(uint8_t bus, uint8_t device,
                       uint8_t function, uint8_t header_type);
enum Error ScanBus(uint8_t bus);
enum Error ScanAllBus();

struct Device {
  uint8_t bus, device, function, header_type;
};

struct Device devices[32];
int num_device;
