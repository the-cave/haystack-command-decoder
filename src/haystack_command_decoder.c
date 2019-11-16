// Copyright (c) 2019 Sarun Rattanasiri
// under the 3-Clause BSD License
// https://opensource.org/licenses/BSD-3-Clause

#include "haystack_command_decoder.h"

void haystack_command_decoder__push(HaystackCommandDecoder_Config* config,
                                    HaystackCommandDecoder_State* state,
                                    uint8_t data) {
  if (state->is_unlocked) {
    if (data < HAYSTACK_COMMAND_DECODER__COMMAND_CAPACITY) {
      state->buffer[data >> 3] |= 1 << (data % 8);
    }
    state->command_pending = true;
    state->is_unlocked = false;
    return;
  }
  uint8_t matching_position = state->next_match;
  if (data == config->key[matching_position]) {
    matching_position++;
  } else {
    state->next_match = 0;
    return;
  }
  if (matching_position == HAYSTACK_COMMAND_DECODER__KEY_SIZE) {
    state->is_unlocked = true;
    state->next_match = 0;
    return;
  }
  state->next_match = matching_position;
}

void haystack_command_decoder__discard(HaystackCommandDecoder_State* state) {
  state->is_unlocked = false;
  state->next_match = 0;
}

void haystack_command_decoder__execute_pending(
    HaystackCommandDecoder_Config* config,
    HaystackCommandDecoder_State* state) {
  if (!state->command_pending)
    return;
  state->command_pending = false;
  for (uint8_t index_scanner = 0;
       index_scanner < HAYSTACK_COMMAND_DECODER__BUFFER_SIZE; index_scanner++) {
    uint8_t buffer_value = state->buffer[index_scanner];
    if (!buffer_value)
      continue;
    for (uint8_t bit_scanner = 1, decoded_value = 0; bit_scanner != 0;
         bit_scanner = bit_scanner << 1, decoded_value++) {
      if (!(buffer_value & bit_scanner))
        continue;
      config->command_received((index_scanner << 3) | decoded_value);
    }
    state->buffer[index_scanner] &= ~buffer_value;
  }
}
