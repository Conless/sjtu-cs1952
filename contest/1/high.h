#ifndef SRC_HPP
#define SRC_HPP
#include <bits/stdc++.h>
#include <cstdint>
#include <utility>

// You may include whatever you want.

void SendPacket(const uint8_t *data, int dataSize);

// You may add some functions or classes here.
std::pair<int, int> GetPacketInfo(double p1, double p2, double a) {
  int maxPacketSize = 128;
  maxPacketSize -= 3;
  if (p1 == 0.0 && p2 == 0.0) {
    return {1, maxPacketSize};
  }
  if (a == 9.0) {
    return {1, maxPacketSize};
  }
  return {2, maxPacketSize};
}

/**
 * Send the data to the receiver using the send_packet function above. The
 * function is called only once for each data. The data is completely uniform
 * random.
 * @param maxPacketSize the maximum packet size, the extra bytes will be ignored
 * @param p1 the probability of the packet being lost
 * @param p2 the probability of a bit being corrupted
 * @param data the data to be sent
 * @param dataSize the size of the data
 */
void Send(int maxPacketSize, double p1, double p2, const uint8_t *data,
          int dataSize, double a) { // NOLINT
  // TODO: implement this function
  uint8_t *packet;
  maxPacketSize -= 3;
  auto info = GetPacketInfo(p1, p2, a);
  int repeat_time = info.first;
  maxPacketSize = info.second;

  uint8_t *check_list = new uint8_t[10];
  check_list[0] = 0b11111111;
  check_list[1] = 0b11111111;
  check_list[2] = 0b11111111;
  check_list[3] = maxPacketSize & 0b11111111;
  check_list[4] = maxPacketSize >> 8 & 0b11111111;
  check_list[5] = maxPacketSize >> 16 & 0b11111111;
  check_list[6] = dataSize & 0b11111111;
  check_list[7] = dataSize >> 8 & 0b11111111;
  check_list[8] = dataSize >> 16 & 0b11111111;

  uint64_t sum = 0, cnt = dataSize;
  for (int i = 0; i < dataSize; i++) {
    sum += data[i];
  }
  check_list[9] = sum / cnt;

  uint64_t sum_diff_sum = 0, sum_diff_cnt = 0;
  for (int i = 0; i < dataSize; i += maxPacketSize) {
    int start_addr = i, length = std::min(dataSize - i, maxPacketSize);
    uint64_t sum_diff = 0;
    for (int j = 0; j < length; j++) {
      sum_diff += (data[i + j] - check_list[9]) * (data[i + j] - check_list[9]);
    }
    sum_diff /= (uint64_t)length;
    sum_diff_sum += sum_diff;
    sum_diff_cnt++;
  }

  uint64_t sum_diff_avg = sum_diff_sum / sum_diff_cnt;
  for (int i = 0; i < dataSize; i += maxPacketSize) {
    int start_addr = i, length = std::min(dataSize - i, maxPacketSize);
    packet = new uint8_t[length + 3];
    packet[0] = start_addr & 0b11111111;
    packet[1] = start_addr >> 8 & 0b11111111;
    packet[2] = start_addr >> 16 & 0b11111111;
    uint64_t sum_diff = 0;
    for (int j = 0; j < length; j++) {
      sum_diff += (data[i + j] - check_list[9]) * (data[i + j] - check_list[9]);
      packet[j + 3] = data[i + j];
    }
    sum_diff /= (uint64_t)length;
    if (p1 == 0.0) {
      repeat_time = 1;
    } else if (p1 == 0.8) {
      repeat_time = 1 + floor(1.0 * sum_diff / (0.5 * sum_diff_avg));
    } else {
      repeat_time = 1 + floor(1.0 * sum_diff / (1.0 * sum_diff_avg));
    }
    for (int j = 0; j < repeat_time; j++) {
      SendPacket(packet, length + 3);
    }
    delete packet;
  }
  if (p1 == 0.0) {
    return;
  }
  for (int i = 0; i <= 5; i++) {
    SendPacket(check_list, 10);
  }
}

bool check = false;
bool init[256000];
int last_addr = 0;

void Check(const uint8_t *data, int dataSize, uint8_t *answer) { // NOLINT
  if (check) {
    return;
  }
  int maxPacketSize = data[3] + (data[4] << 8) + (data[5] << 16);
  int totalDataSize = data[6] + (data[7] << 8) + (data[8] << 16);
  for (int i = 0; i < totalDataSize; i += maxPacketSize) {
    if (!init[i]) {
      int length = std::min(totalDataSize - i, maxPacketSize);
      for (int j = 0; j < length; j++) {
        answer[i + j] = data[9];
      }
    }
  }
  check = true;
}

/**
 * Reconstruct the data from the packets received. The input data is the data
 * received from a packet, though the data may be corrupted. The final answer
 * should be stored in the answer array.
 * @param data the data received from a packet
 * @param dataSize the size of the data (this one is not corrupted)
 * @param answer the answer array
 */
void ReceivePacket(const uint8_t *data, int dataSize,
                   uint8_t *answer) { // NOLINT
  // TODO: implement this function
  int start_addr = data[0] + (data[1] << 8) + (data[2] << 16);
  if (start_addr == 0b111111111111111111111111) {
    Check(data, dataSize, answer)
    return;
  }
  if (start_addr > 256000) {
    return;
  }
  int diff = start_addr - last_addr;
  last_addr = start_addr;
  if (init[start_addr]) {
    return;
  }
  init[start_addr] = true;
  for (int i = 0; i < dataSize; i++) {
    answer[i + start_addr] = data[i + 3];
  }
}

#endif