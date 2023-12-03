#pragma once

#include "types.h"

__attribute__((weak))
bool is_digit(char c) { return c >= '0' && c <= '9'; }
