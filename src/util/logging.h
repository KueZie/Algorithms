#pragma once

#if ENABLE_TESTING
#   define DEBUG_LOG(x) std::cout << x << std::endl
#else
#   define DEBUG_LOG(x)
#endif