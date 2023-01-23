#include "pci.h"
#include "asmfunc.h"
#include "error.h"

const uint16_t kConfigAddress = 0x0cf8;
const uint16_t kConfigData = 0x0cfc;

uint32_t shl32(uint32_t x, unsigned int bits)
{
  return x << bits;
}

uint32_t MakeAddress(uint8_t bus, uint8_t device,
                     uint8_t function, uint8_t reg_addr)
{
  return shl32(1, 31) 
    | shl32(bus, 16)
    | shl32(device, 11)
    | shl32(function, 8)
    | (reg_addr & 0xfcu);
}

void WriteAddress(uint32_t address)
{
  IoOut32(kConfigAddress, address);
}

void WriteData(uint32_t value)
{
  IoOut32(kConfigData, value);
}

uint32_t ReadData()
{
  return IoIn32(kConfigData);
}

uint16_t ReadVendorId(uint8_t bus, uint8_t device, uint8_t function)
{
  WriteAddress(MakeAddress(bus, device, function, 0x00));
  return ReadData() & 0xffffu;
}

uint16_t ReadDeviceId(uint8_t bus, uint8_t device, uint8_t function)
{
  WriteAddress(MakeAddress(bus, device, function, 0x00));
  return ReadData() >> 16;
}

uint8_t ReadHeaderType(uint8_t bus, uint8_t device, uint8_t function)
{
  WriteAddress(MakeAddress(bus, device, function, 0x0c));
  return (ReadData() >> 16) & 0xffu;
}

uint32_t ReadClassCode(uint8_t bus, uint8_t device, uint8_t function)
{
  WriteAddress(MakeAddress(bus, device, function, 0x08));
  return ReadData();
}

uint32_t ReadBusNumbers(uint8_t bus, uint8_t device, uint8_t function)
{
  WriteAddress(MakeAddress(bus, device, function, 0x18));
  return ReadData();
}

bool IsSingleFunctionDevice(uint8_t header_type)
{
  return (header_type & 0x80u) == 0;
}

enum Error ScanDevice(uint8_t bus, uint8_t device)
{
  enum Error err = ScanFunction(bus, device, 0);
  if(err)
    return err;

  if(IsSingleFunctionDevice(ReadHeaderType(bus, device, 0)))
    return kSuccess;

  for(uint8_t function = 1; function < 8; ++function) {
    if(ReadVendorId(bus, device, function) == 0xffffu)
      continue;

    enum Error err = ScanFunction(bus, device, function);
    if(err)
      return err;
  }
  
  return kSuccess;
}

enum Error ScanFunction(uint8_t bus, uint8_t device, 
                          uint8_t function)
{
  uint8_t header_type = ReadHeaderType(bus, device, function);
  enum Error err = AddDevice(bus, device, function, header_type);
  if(err)
    return err;

  uint32_t class_code = ReadClassCode(bus, device, function);
  uint8_t base = (class_code >> 24) & 0xffu;
  uint8_t sub = (class_code >> 16) & 0xffu;

  if(base == 0x06u && sub == 0x04u) {
    uint32_t bus_numbers = ReadBusNumbers(bus, device, function);
    uint8_t secondary_bus = (bus_numbers >> 8) & 0xffu;
    return ScanBus(secondary_bus);
  }

  return kSuccess;
}

enum Error AddDevice(uint8_t bus, uint8_t device, 
                       uint8_t function, uint8_t header_type)
{
  int max_device_size = 32; // max device size
  if(num_device == max_device_size)
    return kFull;

  struct Device dev = {bus, device, function, header_type};
  devices[num_device] = dev;
  ++num_device;

  return kSuccess;
}

enum Error ScanBus(uint8_t bus)
{
  for(uint8_t device = 0; device < 32; ++device) {
    if(ReadVendorId(bus, device, 0) == 0xffffu)
      continue;

    enum Error err = ScanDevice(bus, device);
    if(err)
      return err;
  }
  return kSuccess;
}

enum Error ScanAllBus()
{
  num_device = 0;

  uint8_t header_type = ReadHeaderType(0, 0, 0);
  if(IsSingleFunctionDevice(header_type))
    return ScanBus(0);

  for(uint8_t function = 1; function < 8; ++function) {
    if(ReadVendorId(0, 0, function) == 0xffffu)
      continue;
    
    enum Error err = ScanBus(function);
    if(err)
      return err;
  }
  return kSuccess;
}
