#include <stdio.h>
#include <pico/stdlib.h>

//0x0F11
//0000 1111 0001 0001
//0x0F11
//0000 1111 0001 0001
//res = 0000 1111 0001 0001 0000 1111 0001 0001
inline uint32_t pack16(uint16_t high, uint16_t low) {
    return static_cast<uint32_t>(high)<<16 | low;
}

//We packed eight bit value to obtain 32 bits value
inline uint32_t pack8(uint8_t first, uint8_t second, uint8_t third, uint8_t four) {
    return static_cast<uint32_t>(first)<<24 | static_cast<uint32_t>(second)<<16 | static_cast<uint32_t>(third)<<8 | four;
}

uint32_t simd_add_16x2(uint32_t reg1, uint32_t reg2) {
    uint32_t mask_low = 0x7FFF7FFF;//0111 1111 1111 1111 0111 1111 1111 1111 
    //We add without high bit
    uint32_t result = (reg1 & mask_low) + (reg2 &  mask_low);
    //We manage the carry bit
    return result ^ ((reg1 ^ reg2) & ~mask_low);
}

uint32_t simd_add_8x4(uint32_t reg1, uint32_t reg2) {
    uint32_t mask_low = 0x7F7F7F7F;//0111 1111 0111 1111 0111 1111 0111 1111 
    //We add without high bit
    uint32_t result = (reg1 & mask_low) + (reg2 &  mask_low);
    //We manage the carry bit
    return result ^ ((reg1 ^ reg2) & ~mask_low);
}

static void test_8x4_simd_add() {    
    // ---- Test SIMD 4x8 bits ----
    // Octets of Reg 1 : [100,  50, 200, 10]
    // Octets of Reg 2 : [ 20,  30,  40,  5]
    uint32_t reg8_1 = pack8(100, 50, 200, 10);
    uint32_t reg8_2 = pack8(20, 30, 40, 5);
    
    uint32_t result_8x4 = simd_add_8x4(reg8_1, reg8_2);
    
    // Extract of 4 results
    uint8_t res1 = (result_8x4 >> 24) & 0xFF; // Expect: 120
    uint8_t res2 = (result_8x4 >> 16) & 0xFF; // Expect: 80
    uint8_t res3 = (result_8x4 >> 8)  & 0xFF; // Expect: 240
    uint8_t res4 = result_8x4         & 0xFF; // Expect: 15
    
    while(1) {
        printf("--- SIMD 8x4 Results ---\n");
        printf("Byte 1 (100 + 20): %d\n", res1);
        printf("Byte 2 (50 + 30) : %d\n", res2);
        printf("Byte 3 (200 + 40): %d\n", res3);
        printf("Byte 4 (10 + 5)  : %d\n", res4);
        printf("\n");
        sleep_ms(2000);
    }
}

static void test_16x2_simd_add() {    
    // ---- Test SIMD 4x8 bits ----
    // Octets of Reg 1 : [100,  50]
    // Octets of Reg 2 : [ 20,  30]
    uint32_t reg16_1 = pack16(100, 50);
    uint32_t reg16_2 = pack16(20, 30);
    
    uint32_t result_16x2 = simd_add_8x4(reg16_1, reg16_2);
    
    // Extract of 4 results
    uint8_t res1 = (result_16x2 >> 16); // Expect: 120
    uint8_t res2 = result_16x2 & 0xFFFF; // Expect: 80
    
    while(1) {
        printf("--- SIMD 8x4 Results ---\n");
        printf("Double_octet 1 (100 + 20): %d\n", res1);
        printf("Double_octet 2 (50 + 30) : %d\n", res2);
        printf("\n");
        sleep_ms(2000);
    }
}

int main() {
    stdio_init_all();   
    test_8x4_simd_add();
}


