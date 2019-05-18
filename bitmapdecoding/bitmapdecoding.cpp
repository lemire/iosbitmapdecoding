

#include <random>
#include <cassert>
#include <cinttypes>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstring>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <mach/mach_time.h>
#include "datasource.h"



// tries to estimate the frequency, returns 0 on failure
double measure_frequency() {
    mach_timebase_info_data_t info;
    mach_timebase_info(&info);
    const size_t test_duration_in_cycles =
    65536;// 1048576;
    // travis feels strongly about the measure-twice-and-subtract trick.
    auto begin1 = mach_absolute_time();
    size_t cycles = 2 * test_duration_in_cycles;

     __asm volatile(
                   ".align 4\n Lcyclemeasure1:\nsubs %[counter],%[counter],#1\nbne Lcyclemeasure1\n "
                   : /* read/write reg */ [counter] "+r"(cycles));
    auto end1 = mach_absolute_time();
    double nanoseconds1 =
    (double) (end1 - begin1) * (double)info.numer / (double)info.denom;

    auto begin2 = mach_absolute_time();
    cycles = test_duration_in_cycles;
    // I think that this will have a 2-cycle latency on ARM?
    __asm volatile(
                  ".align 4\n Lcyclemeasure2:\nsubs %[counter],%[counter],#1\nbne Lcyclemeasure2\n "
                   : /* read/write reg */ [counter] "+r"(cycles));
    auto end2 = mach_absolute_time();
    double nanoseconds2 =
    (double) (end2 - begin2) * (double)info.numer / (double)info.denom;
    double nanoseconds = (nanoseconds1 - nanoseconds2);
    if ((fabs(nanoseconds - nanoseconds1 / 2) > 0.05 * nanoseconds) or
        (fabs(nanoseconds - nanoseconds2) > 0.05 * nanoseconds)) {
        return 0;
    }
    double frequency = double(test_duration_in_cycles) / nanoseconds;
    return frequency;
}


char * print_freq(char * result, double * estimated_freq) {
            result+= sprintf(result, "Measuring frequency\n");
    size_t attempt = 1000;
    std::vector<double> freqs;
    for (int i = 0; i < attempt; i++) {
        double freq =measure_frequency();
        if(freq > 0) freqs.push_back(freq);
    }
    if(freqs.size() == 0) {
        result+= sprintf(result, "Could not collect a frequency measure\n");
        return result;
    }
    std::sort(freqs.begin(),freqs.end());
    * estimated_freq = freqs[freqs.size() / 2];
    result+= sprintf(result, "Median frequency detected: %f GHz (%zu samples out of %zu). \n", * estimated_freq, freqs.size(), attempt);
    return result;
}

extern "C" {
    
    
    
    /* result might be undefined when input_num is zero */
    static inline int trailingzeroes(uint64_t input_num) {
#ifdef __BMI2__
        return _tzcnt_u64(input_num);
#else
        return __builtin_ctzll(input_num);
#endif
    }

    
    /* result might be undefined when input_num is zero */
    static inline int hamming(uint64_t input_num) {
#ifdef __POPCOUNT__
        return _popcnt64(input_num);
#else
        return __builtin_popcountll(input_num);
#endif
    }
    
    void basic_decoder(uint32_t *base_ptr, uint32_t &base, uint32_t idx,
                       uint64_t bits) {
        while (bits != 0) {
            base_ptr[base] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base++;
        }
    }
    
    
    static inline void simdjson_decoder(uint32_t *base_ptr, uint32_t &base,
                                        uint32_t idx, uint64_t bits) {
        if (bits == 0)
            return;
        uint32_t cnt = hamming(bits);
        uint32_t next_base = base + cnt;
        base_ptr += base;
        if (true) {
            base_ptr[0] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[1] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[2] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[3] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[4] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[5] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[6] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[7] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr += 8;
        }
        if (cnt > 8) {
            base_ptr[0] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[1] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[2] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[3] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[4] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[5] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[6] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr[7] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
            bits = bits & (bits - 1);
            base_ptr += 8;
            if (cnt > 16) { // unluckly
                do {
                    base_ptr[0] = static_cast<uint32_t>(idx) + trailingzeroes(bits);
                    bits = bits & (bits - 1);
                    base_ptr++;
                } while (bits != 0);
            }
        }
        base = next_base;
    }
    
    
    int measure(size_t length, char * result) {
        size_t multiplier = 1000;
        uint32_t *bigarray = (uint32_t *)malloc(sizeof(uint32_t) * WORDCOUNT * 64);
        for(size_t z = 0; z < 10 * multiplier; z++) {
            bigarray[rand() % WORDCOUNT] ^= rand(); // to defeat optimizers
            uint32_t matches1 = 0;
            const uint64_t startTime1 = mach_absolute_time();
            for(uint32_t idx = 0; idx < WORDCOUNT; idx++) basic_decoder(bigarray, matches1, idx, testdata[idx]);
            const uint64_t endTime1 = mach_absolute_time();
            
            uint32_t matches2 = 0;
            
            const uint64_t startTime2 = mach_absolute_time();
            for(uint32_t idx = 0; idx < WORDCOUNT; idx++) simdjson_decoder(bigarray, matches2, idx, testdata[idx]);
            const uint64_t endTime2 = mach_absolute_time();
            mach_timebase_info_data_t info;
            mach_timebase_info(&info);
            const double elapsedNS1 = (double) (endTime1 - startTime1) * (double)info.numer / (double)info.denom;
            const double elapsedNS2 = (double) (endTime2 - startTime2) * (double)info.numer / (double)info.denom;
            if((z % multiplier) == 0) {
                double frequency;
                result = print_freq(result, &frequency);
              result+= sprintf(result, "%u %u \n", matches1, matches2);
                result+= sprintf(result, "basic_decoder timing: %.3f nanoseconds per set bit \n", elapsedNS1 / matches1);
                result+= sprintf(result, "simdjson_decoder timing: %.3f  nanoseconds per set bit  \n", elapsedNS2 / matches2);
                if(frequency > 0){
                    result+= sprintf(result, "basic_decoder: %.3f cycles per set bit \n", elapsedNS1 / matches1 * frequency);
                    result+= sprintf(result, "simdjson_decoder: %.3f cycles per set bit  \n", elapsedNS2 / matches2 * frequency);
                }
                

            }
        }
        free(bigarray);
        return 10000;
    }
}
