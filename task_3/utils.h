#pragma once
#include <cassert>

#define ASSERT(call, expected) do { \
        auto saved_call = call; \
        if (saved_call != (expected)) { \
            std::cerr << "Expected (" << (expected) << "), Value (" << (saved_call) << ")\n"; \
            assert(false); \
        } \
    } while (false)
