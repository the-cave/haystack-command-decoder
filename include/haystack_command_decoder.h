// Copyright (c) 2019 Sarun Rattanasiri
// under the 3-Clause BSD License
// https://opensource.org/licenses/BSD-3-Clause

#ifndef __HAYSTACK_COMMAND_DECODER_H
#define __HAYSTACK_COMMAND_DECODER_H

#ifndef HAYSTACK_COMMAND_DECODER__KEY_SIZE
#define HAYSTACK_COMMAND_DECODER__KEY_SIZE 16
#endif

#ifndef HAYSTACK_COMMAND_DECODER__COMMAND_CAPACITY
#define HAYSTACK_COMMAND_DECODER__COMMAND_CAPACITY 8
#endif

#define HAYSTACK_COMMAND_DECODER__BUFFER_SIZE \
  (HAYSTACK_COMMAND_DECODER__COMMAND_CAPACITY / 8)

#include <stdbool.h>
#include <stdint.h>

typedef struct _haystack_command_decoder__config {
  uint8_t key[HAYSTACK_COMMAND_DECODER__KEY_SIZE];
  void (*command_received)(uint8_t command);
} HaystackCommandDecoder_Config;

typedef struct _haystack_command_decoder__state {
  bool is_unlocked;
  bool command_pending;
  uint8_t next_match;
  uint8_t buffer[HAYSTACK_COMMAND_DECODER__BUFFER_SIZE];
} HaystackCommandDecoder_State;

#define haystack_command_decoder__init(state) \
  do {                                        \
    (state)->is_unlocked = false;             \
    (state)->command_pending = false;         \
    (state)->next_match = 0;                  \
  } while (0)

void haystack_command_decoder__push(HaystackCommandDecoder_Config* config,
                                    HaystackCommandDecoder_State* state,
                                    uint8_t data);

void haystack_command_decoder__discard(HaystackCommandDecoder_State* state);

void haystack_command_decoder__execute_pending(
    HaystackCommandDecoder_Config* config,
    HaystackCommandDecoder_State* state);

#endif
