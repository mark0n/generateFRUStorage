#ifndef CHECKSUM_HPP
#define CHECKSUM_HPP

#include <vector>
#include <cstdint>
#include <stdexcept>

uint8_t calcChecksum(std::vector<uint8_t>& vec);
void updateAreaChecksum(std::vector<uint8_t>& vec);

#endif /* CHECKSUM_HPP */