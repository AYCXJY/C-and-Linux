#include <stdio.h>
// #include <assert.h>
#include <inttypes.h>
#include <limits.h>

void show_binary(uint32_t num, int8_t width)
{
    uint32_t num_t = num;
    int8_t t = 63, space = 0, binary[64] = {0};

    while(num_t != 0)
    {
        if(num_t % 2 == 1)
            binary[t--] = 1;
        else
            binary[t--] = 0;
        num_t /= 2;
    }
    printf("num %d = ", num);
    for(int i = 64 - width; i < 64; i++)
    {
        printf("%"PRId8"", binary[i]);   
        space++;
        if(space % 4 == 0)
        {
            printf(" ");
            space %= 4;
        }
    }
    printf("\n");
}

void show_bytes(uint8_t* start, size_t len)
{
    int i;
    for(i = len - 1; i >= 0 ;i--)
        printf("%.2X ", start[i]);
    printf("\n");
}

int in_little_endian(void)
{
    int16_t num = 0x1234;
    if(*((uint8_t*)&num) == 0x34 && *((uint8_t*)&num + 1) == 0x12)
        return 1;
    else 
        return 0;
}

unsigned replase_byte_2_60(unsigned x, int i, unsigned char b)
{
    unsigned result = x;
    int len = (int)sizeof(x);
    result &= ~(0xFF << (len - i) * 8);
    result |= (b << (len - i) * 8);
    return result;
}

int check_2_61(int x)
{
    // A. return !(x + 1);
    // B. return !x; 
    // C. return !((x & 0xFF) - 0xFF);
    // D. return !(x >> (sizeof((int)-1) << 3) & 0XFF);
}

int  int_shifts_are_arithemetic(void)
{
    int x = -1;
    return !((x >> 1) ^ x);
}

unsigned srl(unsigned x, int k)
{
    unsigned xsra = (int) x >> k;
    return ~xsra + 1;
}

unsigned sra(unsigned x, int k){
    int xsrl = (unsigned) x >> k;


    return ~xsrl + 1;
}

int any_odd_one(unsigned x)
{
    return !!(x & 0xAAAAAAAA);
}

/*
 * odd-ones.c
 */
#include <stdio.h>
#include <assert.h>

int odd_ones(unsigned x) {
    show_binary(x, 32);
    x ^= x >> 16;
    show_binary(x, 16);
    x ^= x >> 8;
    show_binary(x, 8);
    x ^= x >> 4;
    show_binary(x, 4);
    x ^= x >> 2;
    show_binary(x, 2);
    x ^= x >> 1;
    x &= 1;
    show_binary(x, 1);
    return x;
}

int leftmost_one(unsigned x)
{
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
    return (x>>1) + (x && 1);    
}


int lower_one_mask(int n)
{
    return ((1 << n) - 1);
}

// 0 <= n < w
unsigned rotate_left(unsigned x, int n )
{
    return ((x << n) | (x >> ((sizeof(unsigned) * 8) - n)));
}

int fits_bits(int x, int n)
{
    return !(x & (-1 & ~(((1 << n) & ~1) - 1))); 
}

int main(int argc, char* argv[]) {
    printf("%d\n", fits_bits(0x12, 4)); 
    return 0;
}



