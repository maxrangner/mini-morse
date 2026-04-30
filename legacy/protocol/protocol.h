#pragma once
#include <Arduino.h>

namespace MorseProtocol {
  enum PacketType {
    STATUS // 0
  };

  struct Packet {
    uint8_t protocolVersion;
    uint8_t deviceId;
    PacketType packetType;
    uint8_t payload;
  };
}
