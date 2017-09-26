#define NTAPS 55

// FIR Coefficient Buffer
// Lowpass Filter with fg = 4 kHz @ fs = 48 kHz
fractional coefficients[NTAPS] __attribute__ ((space(xmemory),far)) = {
       42,    212,    429,    452,    132,   -250,   -236,    149,    319,
      -43,   -398,   -110,    445,    320,   -426,   -580,    304,    870,
      -37,  -1166,   -440,   1439,   1265,  -1658,  -2953,   1801,  10250,
    14534,  10250,   1801,  -2953,  -1658,   1265,   1439,   -440,  -1166,
      -37,    870,    304,   -580,   -426,    320,    445,   -110,   -398,
      -43,    319,    149,   -236,   -250,    132,    452,    429,    212,
       42
};

// FIR Delay Buffer
fractional delayBuffer[NTAPS] __attribute__ ((space(ymemory),far)); 

