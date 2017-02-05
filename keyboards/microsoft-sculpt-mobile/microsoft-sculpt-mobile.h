#ifndef MICROSOFT_SCULPT_MOBILE_H
#define MICROSOFT_SCULPT_MOBILE_H

#ifdef SUBPROJECT_astar
        #include "astar.h"
#endif
#ifdef SUBPROJECT_teensy2pp
        #include "teensy2pp.h"
#endif

#include "quantum.h"




#include "quantum.h"




#define MATRIX_TESTING_KEYMAP( \
        k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0, k0J, k0K, k0L, k0M, k0N, k0O, k0P, k0Q,\
        k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I, k1, k1J, k1K, k1L, k1M, k1N, k1O, k1P, k1Q,\
        k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I, k2, k2J, k2K, k2L, k2M, k2N, k2O, k2P, k2Q,\
        k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, k3, k3J, k3K, k3L, k3M, k3N, k3O, k3P, k3Q,\
        k4A, k4B, k4C, k4D, k4E, k4F, k4G, k4H, k4I, k4, k4J, k4K, k4L, k4M, k4N, k4O, k4P, k4Q,\
        k5A, k5B, k5C, k5D, k5E, k5F, k5G, k5H, k5I, k5, k5J, k5K, k5L, k5M, k5N, k5O, k5P, k5Q,\
        k6A, k6B, k6C, k6D, k6E, k6F, k6G, k6H, k6I, k6, k6J, k6K, k6L, k6M, k6N, k6O, k6P, k6Q,\
        k7A, k7B, k7C, k7D, k7E, k7F, k7G, k7H, k7I, k7, k7J, k7K, k7L, k7M, k7N, k7O, k7P, k7Q\
) \
{ \
       {k0A, k0B, k0C, k0D, k0E, k0F, k0G, k0H, k0I, k0, k0J, k0K, k0L, k0M, k0N, k0O, k0P, k0Q},\
        {k1A, k1B, k1C, k1D, k1E, k1F, k1G, k1H, k1I, k1, k1J, k1K, k1L, k1M, k1N, k1O, k1P, k1Q},\
        {k2A, k2B, k2C, k2D, k2E, k2F, k2G, k2H, k2I, k2, k2J, k2K, k2L, k2M, k2N, k2O, k2P, k2Q},\
        {k3A, k3B, k3C, k3D, k3E, k3F, k3G, k3H, k3I, k3, k3J, k3K, k3L, k3M, k3N, k3O, k3P, k3Q},\
        {k4A, k4B, k4C, k4D, k4E, k4F, k4G, k4H, k4I, k4, k4J, k4K, k4L, k4M, k4N, k4O, k4P, k4Q},\
        {k5A, k5B, k5C, k5D, k5E, k5F, k5G, k5H, k5I, k5, k5J, k5K, k5L, k5M, k5N, k5O, k5P, k5Q},\
        {k6A, k6B, k6C, k6D, k6E, k6F, k6G, k6H, k6I, k6, k6J, k6K, k6L, k6M, k6N, k6O, k6P, k6Q},\
        {k7A, k7B, k7C, k7D, k7E, k7F, k7G, k7H, k7I, k7, k7J, k7K, k7L, k7M, k7N, k7O, k7P, k7Q},\
}

#endif
