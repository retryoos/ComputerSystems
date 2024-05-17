#define BITS_PER_BYTE 8

#ifdef DOUBLE
#define FP_TYPE double
#define INT_TYPE long
#define SIGN_SIZE 1
#define BITS_FP_TYPE 64
#define EXPONENT_BIAS 1023
#define EXPONENT_SIZE 11
#define MANTISSA_SIZE 52
#define PRINT_TYPE "%lf"
#else
#define FP_TYPE float
#define INT_TYPE int
#define SIGN_SIZE 1
#define BITS_FP_TYPE 32
#define EXPONENT_BIAS 127
#define EXPONENT_SIZE 8
#define MANTISSA_SIZE 23
#define PRINT_TYPE "%f"
#endif

struct Components {
    unsigned INT_TYPE mantissa : MANTISSA_SIZE;
    unsigned INT_TYPE exponent : EXPONENT_SIZE;
    unsigned INT_TYPE sign : SIGN_SIZE;
};
typedef struct Components Components;
union Converter {
    FP_TYPE n;
    unsigned INT_TYPE u;
    Components comps;
};

void print_bits(unsigned INT_TYPE num, unsigned INT_TYPE size);
void print_components(union Converter num);
void print_normalized(union Converter num);
void print_denormalized(union Converter num);
void print_reconstitution(union Converter num);
FP_TYPE power_of_2(int num);