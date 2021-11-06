/* Copyright 2021 by Don Kjer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gtest/gtest.h"

extern "C" {
#include "flash_stm32.h"
#include "eeprom_stm32.h"
#include "eeprom.h"
}

/* Mock Flash Parameters:
 *
 * === Large Layout ===
 * flash size: 65536
 * page size: 2048
 * density pages: 16
 * Simulated EEPROM size: 16384
 *
 * FlashBuf Layout:
 * [Unused | Compact |  Write Log  ]
 * [0......|32768......|49152......65535]
 *
 * === Tiny Layout ===
 * flash size: 1024
 * page size: 512
 * density pages: 1
 * Simulated EEPROM size: 256
 *
 * FlashBuf Layout:
 * [Unused | Compact |  Write Log  ]
 * [0......|512......|768......1023]
 *
 */

#define EEPROM_SIZE (FEE_PAGE_SIZE * FEE_PAGE_COUNT / 2)
#define LOG_SIZE EEPROM_SIZE
#define LOG_BASE (MOCK_FLASH_SIZE - LOG_SIZE)
#define EEPROM_BASE (LOG_BASE - EEPROM_SIZE)

/* Log encoding helpers */
#define BYTE_VALUE(addr, value) (((addr) << 8) | (value))
#define WORD_ZERO(addr) (0x8000 | ((addr) >> 1))
#define WORD_ONE(addr) (0xA000 | ((addr) >> 1))
#define WORD_NEXT(addr) (0xE000 | (((addr)-0x80) >> 1))

class EepromStm32Test : public testing::Test {
   public:
    EepromStm32Test() {}
    ~EepromStm32Test() {}

   protected:
    void SetUp() override { EEPROM_Erase(); }

    void TearDown() override {
#ifdef EEPROM_DEBUG
        dumpEepromDataBuf();
#endif
    }
};

TEST_F(EepromStm32Test, TestErase) {
    EEPROM_WriteDataByte(0, 0x42);
    EEPROM_Erase();
    EXPECT_EQ(EEPROM_ReadDataByte(0), 0);
    EXPECT_EQ(EEPROM_ReadDataByte(1), 0);
}

TEST_F(EepromStm32Test, TestReadGarbage) {
    uint8_t garbage = 0x3c;
    for (int i = 0; i < MOCK_FLASH_SIZE; ++i) {
        garbage ^= 0xa3;
        garbage += i;
        FlashBuf[i] = garbage;
    }
    EEPROM_Init();  // Just verify we don't crash
}

TEST_F(EepromStm32Test, TestWriteBadAddress) {
    EXPECT_EQ(EEPROM_WriteDataByte(EEPROM_SIZE, 0x42), FLASH_BAD_ADDRESS);
    EXPECT_EQ(EEPROM_WriteDataWord(EEPROM_SIZE - 1, 0xbeef), FLASH_BAD_ADDRESS);
    EXPECT_EQ(EEPROM_WriteDataWord(EEPROM_SIZE, 0xbeef), FLASH_BAD_ADDRESS);
}

TEST_F(EepromStm32Test, TestReadBadAddress) {
    EXPECT_EQ(EEPROM_ReadDataByte(EEPROM_SIZE), 0xFF);
    EXPECT_EQ(EEPROM_ReadDataWord(EEPROM_SIZE - 1), 0xFFFF);
    EXPECT_EQ(EEPROM_ReadDataWord(EEPROM_SIZE), 0xFFFF);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)(EEPROM_SIZE - 4)), 0);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)(EEPROM_SIZE - 3)), 0xFF000000);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)EEPROM_SIZE), 0xFFFFFFFF);
}

TEST_F(EepromStm32Test, TestReadByte) {
    /* Direct compacted-area baseline: Address < 0x80 */
    FlashBuf[EEPROM_BASE + 2] = ~0xef;
    FlashBuf[EEPROM_BASE + 3] = ~0xbe;
    /* Direct compacted-area baseline: Address >= 0x80 */
    FlashBuf[EEPROM_BASE + EEPROM_SIZE - 2] = ~0x78;
    FlashBuf[EEPROM_BASE + EEPROM_SIZE - 1] = ~0x56;
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataByte(2), 0xef);
    EXPECT_EQ(EEPROM_ReadDataByte(3), 0xbe);
    EXPECT_EQ(EEPROM_ReadDataByte(EEPROM_SIZE - 2), 0x78);
    EXPECT_EQ(EEPROM_ReadDataByte(EEPROM_SIZE - 1), 0x56);
    /* Write Log byte value */
    FlashBuf[LOG_BASE]     = 0x65;
    FlashBuf[LOG_BASE + 1] = 3;
    /* Write Log word value */
    *(uint16_t*)&FlashBuf[LOG_BASE + 2] = WORD_NEXT(EEPROM_SIZE - 2);
    *(uint16_t*)&FlashBuf[LOG_BASE + 4] = ~0x9abc;
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataByte(2), 0xef);
    EXPECT_EQ(EEPROM_ReadDataByte(3), 0x65);
    EXPECT_EQ(EEPROM_ReadDataByte(EEPROM_SIZE - 2), 0xbc);
    EXPECT_EQ(EEPROM_ReadDataByte(EEPROM_SIZE - 1), 0x9a);
}

TEST_F(EepromStm32Test, TestWriteByte) {
    /* Direct compacted-area baseline: Address < 0x80 */
    EEPROM_WriteDataByte(2, 0xef);
    EEPROM_WriteDataByte(3, 0xbe);
    /* Direct compacted-area baseline: Address >= 0x80 */
    EEPROM_WriteDataByte(EEPROM_SIZE - 2, 0x78);
    EEPROM_WriteDataByte(EEPROM_SIZE - 1, 0x56);
    /* Check values */
    /* First write in each aligned word should have been direct */
    EXPECT_EQ(FlashBuf[EEPROM_BASE + 2], (uint8_t)~0xef);
    EXPECT_EQ(FlashBuf[EEPROM_BASE + EEPROM_SIZE - 2], (uint8_t)~0x78);

    /* Second write per aligned word requires a log entry */
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE], BYTE_VALUE(3, 0xbe));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 2], WORD_NEXT(EEPROM_SIZE - 1));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 4], (uint16_t)~0x5678);
}

TEST_F(EepromStm32Test, TestByteRoundTrip) {
    /* Direct compacted-area: Address < 0x80 */
    EEPROM_WriteDataWord(0, 0xdead);
    EEPROM_WriteDataByte(2, 0xef);
    EEPROM_WriteDataByte(3, 0xbe);
    /* Direct compacted-area: Address >= 0x80 */
    EEPROM_WriteDataByte(EEPROM_SIZE - 2, 0x78);
    EEPROM_WriteDataByte(EEPROM_SIZE - 1, 0x56);
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataByte(0), 0xad);
    EXPECT_EQ(EEPROM_ReadDataByte(1), 0xde);
    EXPECT_EQ(EEPROM_ReadDataByte(2), 0xef);
    EXPECT_EQ(EEPROM_ReadDataByte(3), 0xbe);
    EXPECT_EQ(EEPROM_ReadDataByte(EEPROM_SIZE - 2), 0x78);
    EXPECT_EQ(EEPROM_ReadDataByte(EEPROM_SIZE - 1), 0x56);
    /* Write log entries */
    EEPROM_WriteDataByte(2, 0x80);
    EEPROM_WriteDataByte(EEPROM_SIZE - 2, 0x3c);
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataByte(2), 0x80);
    EXPECT_EQ(EEPROM_ReadDataByte(3), 0xbe);
    EXPECT_EQ(EEPROM_ReadDataByte(EEPROM_SIZE - 2), 0x3c);
    EXPECT_EQ(EEPROM_ReadDataByte(EEPROM_SIZE - 1), 0x56);
}

TEST_F(EepromStm32Test, TestReadWord) {
    /* Direct compacted-area baseline: Address < 0x80 */
    FlashBuf[EEPROM_BASE + 0] = ~0xad;
    FlashBuf[EEPROM_BASE + 1] = ~0xde;
    /* Direct compacted-area baseline: Address >= 0x80 */
    FlashBuf[EEPROM_BASE + 200]             = ~0xcd;
    FlashBuf[EEPROM_BASE + 201]             = ~0xab;
    FlashBuf[EEPROM_BASE + EEPROM_SIZE - 4] = ~0x34;
    FlashBuf[EEPROM_BASE + EEPROM_SIZE - 3] = ~0x12;
    FlashBuf[EEPROM_BASE + EEPROM_SIZE - 2] = ~0x78;
    FlashBuf[EEPROM_BASE + EEPROM_SIZE - 1] = ~0x56;
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataWord(0), 0xdead);
    EXPECT_EQ(EEPROM_ReadDataWord(200), 0xabcd);
    EXPECT_EQ(EEPROM_ReadDataWord(EEPROM_SIZE - 4), 0x1234);
    EXPECT_EQ(EEPROM_ReadDataWord(EEPROM_SIZE - 2), 0x5678);
    /* Write Log word zero-encoded */
    *(uint16_t*)&FlashBuf[LOG_BASE] = WORD_ZERO(200);
    /* Write Log word one-encoded */
    *(uint16_t*)&FlashBuf[LOG_BASE + 2] = WORD_ONE(EEPROM_SIZE - 4);
    /* Write Log word value */
    *(uint16_t*)&FlashBuf[LOG_BASE + 4] = WORD_NEXT(EEPROM_SIZE - 2);
    *(uint16_t*)&FlashBuf[LOG_BASE + 6] = ~0x9abc;
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataWord(200), 0);
    EXPECT_EQ(EEPROM_ReadDataWord(EEPROM_SIZE - 4), 1);
    EXPECT_EQ(EEPROM_ReadDataWord(EEPROM_SIZE - 2), 0x9abc);
}

TEST_F(EepromStm32Test, TestWriteWord) {
    /* Direct compacted-area: Address < 0x80 */
    EEPROM_WriteDataWord(0, 0xdead);  // Aligned
    EEPROM_WriteDataWord(3, 0xbeef);  // Unaligned
    /* Direct compacted-area: Address >= 0x80 */
    EEPROM_WriteDataWord(200, 0xabcd);  // Aligned
    EEPROM_WriteDataWord(203, 0x9876);  // Unaligned
    EEPROM_WriteDataWord(EEPROM_SIZE - 4, 0x1234);
    EEPROM_WriteDataWord(EEPROM_SIZE - 2, 0x5678);
    /* Write Log word zero-encoded */
    EEPROM_WriteDataWord(EEPROM_SIZE - 4, 0);
    /* Write Log word one-encoded */
    EEPROM_WriteDataWord(EEPROM_SIZE - 2, 1);
    /* Write Log word value aligned */
    EEPROM_WriteDataWord(200, 0x4321);  // Aligned
    /* Write Log word value unaligned */
    EEPROM_WriteDataByte(202, 0x3c);    // Set neighboring byte
    EEPROM_WriteDataWord(203, 0xcdef);  // Unaligned
    /* Check values */
    /* Direct compacted-area */
    EXPECT_EQ(*(uint16_t*)&FlashBuf[EEPROM_BASE], (uint16_t)~0xdead);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[EEPROM_BASE + 3], (uint16_t)~0xbeef);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[EEPROM_BASE + 200], (uint16_t)~0xabcd);
    EXPECT_EQ(FlashBuf[EEPROM_BASE + 203], (uint8_t)~0x76);
    EXPECT_EQ(FlashBuf[EEPROM_BASE + 204], (uint8_t)~0x98);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[EEPROM_BASE + EEPROM_SIZE - 4], (uint16_t)~0x1234);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[EEPROM_BASE + EEPROM_SIZE - 2], (uint16_t)~0x5678);
    /* Write Log word zero-encoded */
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE], WORD_ZERO(EEPROM_SIZE - 4));
    /* Write Log word one-encoded */
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 2], WORD_ONE(EEPROM_SIZE - 2));
    /* Write Log word value aligned */
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 4], WORD_NEXT(200));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 6], (uint16_t)~0x4321);
    /* Write Log word value unaligned */
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 8], WORD_NEXT(202));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 10], (uint16_t)~0x763c);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 12], WORD_NEXT(202));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 14], (uint16_t)~0xef3c);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 16], WORD_NEXT(204));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 18], (uint16_t)~0x00cd);
}

TEST_F(EepromStm32Test, TestWordRoundTrip) {
    /* Direct compacted-area: Address < 0x80 */
    EEPROM_WriteDataWord(0, 0xdead);  // Aligned
    EEPROM_WriteDataWord(3, 0xbeef);  // Unaligned
    /* Direct compacted-area: Address >= 0x80 */
    EEPROM_WriteDataWord(200, 0xabcd);  // Aligned
    EEPROM_WriteDataWord(203, 0x9876);  // Unaligned
    EEPROM_WriteDataWord(EEPROM_SIZE - 4, 0x1234);
    EEPROM_WriteDataWord(EEPROM_SIZE - 2, 0x5678);
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataWord(0), 0xdead);
    EXPECT_EQ(EEPROM_ReadDataWord(3), 0xbeef);
    EXPECT_EQ(EEPROM_ReadDataWord(200), 0xabcd);
    EXPECT_EQ(EEPROM_ReadDataWord(203), 0x9876);
    EXPECT_EQ(EEPROM_ReadDataWord(EEPROM_SIZE - 4), 0x1234);
    EXPECT_EQ(EEPROM_ReadDataWord(EEPROM_SIZE - 2), 0x5678);

    /* Write Log word zero-encoded */
    EEPROM_WriteDataWord(EEPROM_SIZE - 4, 0);
    /* Write Log word one-encoded */
    EEPROM_WriteDataWord(EEPROM_SIZE - 2, 1);
    /* Write Log word value aligned */
    EEPROM_WriteDataWord(200, 0x4321);  // Aligned
    /* Write Log word value unaligned */
    EEPROM_WriteDataByte(202, 0x3c);    // Set neighboring byte
    EEPROM_WriteDataWord(203, 0xcdef);  // Unaligned
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataWord(200), 0x4321);
    EXPECT_EQ(EEPROM_ReadDataByte(202), 0x3c);
    EXPECT_EQ(EEPROM_ReadDataWord(203), 0xcdef);
    EXPECT_EQ(EEPROM_ReadDataWord(EEPROM_SIZE - 4), 0);
    EXPECT_EQ(EEPROM_ReadDataWord(EEPROM_SIZE - 2), 1);
}

TEST_F(EepromStm32Test, TestByteWordBoundary) {
    /* Direct compacted-area write */
    EEPROM_WriteDataWord(0x7e, 0xdead);
    EEPROM_WriteDataWord(0x80, 0xbeef);
    /* Byte log entry */
    EEPROM_WriteDataByte(0x7f, 0x3c);
    /* Word log entry */
    EEPROM_WriteDataByte(0x80, 0x18);
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataWord(0x7e), 0x3cad);
    EXPECT_EQ(EEPROM_ReadDataWord(0x80), 0xbe18);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE], BYTE_VALUE(0x7f, 0x3c));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 2], WORD_NEXT(0x80));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 4], (uint16_t)~0xbe18);
    /* Byte log entries */
    EEPROM_WriteDataWord(0x7e, 0xcafe);
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataWord(0x7e), 0xcafe);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 6], BYTE_VALUE(0x7e, 0xfe));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 8], BYTE_VALUE(0x7f, 0xca));
    /* Byte and Word log entries */
    EEPROM_WriteDataWord(0x7f, 0xba5e);
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataWord(0x7f), 0xba5e);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 10], BYTE_VALUE(0x7f, 0x5e));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 12], WORD_NEXT(0x80));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 14], (uint16_t)~0xbeba);
    /* Word log entry */
    EEPROM_WriteDataWord(0x80, 0xf00d);
    /* Check values */
    EEPROM_Init();
    EXPECT_EQ(EEPROM_ReadDataWord(0x80), 0xf00d);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 16], WORD_NEXT(0x80));
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + 18], (uint16_t)~0xf00d);
}

TEST_F(EepromStm32Test, TestDWordRoundTrip) {
    /* Direct compacted-area: Address < 0x80 */
    eeprom_write_dword((uint32_t*)0, 0xdeadbeef);  // Aligned
    eeprom_write_dword((uint32_t*)9, 0x12345678);  // Unaligned
    /* Direct compacted-area: Address >= 0x80 */
    eeprom_write_dword((uint32_t*)200, 0xfacef00d);
    eeprom_write_dword((uint32_t*)(EEPROM_SIZE - 4), 0xba5eba11);  // Aligned
    eeprom_write_dword((uint32_t*)(EEPROM_SIZE - 9), 0xcafed00d);  // Unaligned
    /* Check direct values */
    EEPROM_Init();
    EXPECT_EQ(eeprom_read_dword((uint32_t*)0), 0xdeadbeef);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)9), 0x12345678);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)200), 0xfacef00d);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)(EEPROM_SIZE - 4)), 0xba5eba11);  // Aligned
    EXPECT_EQ(eeprom_read_dword((uint32_t*)(EEPROM_SIZE - 9)), 0xcafed00d);  // Unaligned
    /* Write Log byte encoded */
    eeprom_write_dword((uint32_t*)0, 0xdecafbad);
    eeprom_write_dword((uint32_t*)9, 0x87654321);
    /* Write Log word encoded */
    eeprom_write_dword((uint32_t*)200, 1);
    /* Write Log word value aligned */
    eeprom_write_dword((uint32_t*)(EEPROM_SIZE - 4), 0xdeadc0de);  // Aligned
    eeprom_write_dword((uint32_t*)(EEPROM_SIZE - 9), 0x6789abcd);  // Unaligned
    /* Check log values */
    EEPROM_Init();
    EXPECT_EQ(eeprom_read_dword((uint32_t*)0), 0xdecafbad);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)9), 0x87654321);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)200), 1);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)(EEPROM_SIZE - 4)), 0xdeadc0de);  // Aligned
    EXPECT_EQ(eeprom_read_dword((uint32_t*)(EEPROM_SIZE - 9)), 0x6789abcd);  // Unaligned
}

TEST_F(EepromStm32Test, TestBlockRoundTrip) {
    char  src0[] = "0123456789abcdef";
    void* src1   = (void*)&src0[1];
    /* Various alignments of src & dst, Address < 0x80 */
    eeprom_write_block(src0, (void*)0, sizeof(src0));
    eeprom_write_block(src0, (void*)21, sizeof(src0));
    eeprom_write_block(src1, (void*)40, sizeof(src0) - 1);
    eeprom_write_block(src1, (void*)61, sizeof(src0) - 1);
    /* Various alignments of src & dst, Address >= 0x80 */
    eeprom_write_block(src0, (void*)140, sizeof(src0));
    eeprom_write_block(src0, (void*)161, sizeof(src0));
    eeprom_write_block(src1, (void*)180, sizeof(src0) - 1);
    eeprom_write_block(src1, (void*)201, sizeof(src0) - 1);

    /* Check values */
    EEPROM_Init();

    char  dstBuf[256] = {0};
    char* dst0a       = (char*)dstBuf;
    char* dst0b       = (char*)&dstBuf[20];
    char* dst1a       = (char*)&dstBuf[41];
    char* dst1b       = (char*)&dstBuf[61];
    char* dst0c       = (char*)&dstBuf[80];
    char* dst0d       = (char*)&dstBuf[100];
    char* dst1c       = (char*)&dstBuf[121];
    char* dst1d       = (char*)&dstBuf[141];
    eeprom_read_block((void*)dst0a, (void*)0, sizeof(src0));
    eeprom_read_block((void*)dst0b, (void*)21, sizeof(src0));
    eeprom_read_block((void*)dst1a, (void*)40, sizeof(src0) - 1);
    eeprom_read_block((void*)dst1b, (void*)61, sizeof(src0) - 1);
    eeprom_read_block((void*)dst0c, (void*)140, sizeof(src0));
    eeprom_read_block((void*)dst0d, (void*)161, sizeof(src0));
    eeprom_read_block((void*)dst1c, (void*)180, sizeof(src0) - 1);
    eeprom_read_block((void*)dst1d, (void*)201, sizeof(src0) - 1);
    EXPECT_EQ(strcmp((char*)src0, dst0a), 0);
    EXPECT_EQ(strcmp((char*)src0, dst0b), 0);
    EXPECT_EQ(strcmp((char*)src0, dst0c), 0);
    EXPECT_EQ(strcmp((char*)src0, dst0d), 0);
    EXPECT_EQ(strcmp((char*)src1, dst1a), 0);
    EXPECT_EQ(strcmp((char*)src1, dst1b), 0);
    EXPECT_EQ(strcmp((char*)src1, dst1c), 0);
    EXPECT_EQ(strcmp((char*)src1, dst1d), 0);
}

TEST_F(EepromStm32Test, TestCompaction) {
    /* Direct writes */
    eeprom_write_dword((uint32_t*)0, 0xdeadbeef);
    eeprom_write_byte((uint8_t*)4, 0x3c);
    eeprom_write_word((uint16_t*)6, 0xd00d);
    eeprom_write_dword((uint32_t*)150, 0xcafef00d);
    eeprom_write_dword((uint32_t*)200, 0x12345678);
    /* Fill write log entries */
    uint32_t i;
    uint32_t val = 0xd8453c6b;
    for (i = 0; i < (LOG_SIZE / (sizeof(uint32_t) * 2)); i++) {
        val ^= 0x593ca5b3;
        val += i;
        eeprom_write_dword((uint32_t*)200, val);
    }
    /* Check values pre-compaction */
    EEPROM_Init();
    EXPECT_EQ(eeprom_read_dword((uint32_t*)0), 0xdeadbeef);
    EXPECT_EQ(eeprom_read_byte((uint8_t*)4), 0x3c);
    EXPECT_EQ(eeprom_read_word((uint16_t*)6), 0xd00d);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)150), 0xcafef00d);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)200), val);
    EXPECT_NE(*(uint16_t*)&FlashBuf[LOG_BASE], 0xFFFF);
    EXPECT_NE(*(uint16_t*)&FlashBuf[LOG_BASE + LOG_SIZE - 2], 0xFFFF);
    /* Run compaction */
    eeprom_write_byte((uint8_t*)4, 0x1f);
    EEPROM_Init();
    EXPECT_EQ(eeprom_read_dword((uint32_t*)0), 0xdeadbeef);
    EXPECT_EQ(eeprom_read_byte((uint8_t*)4), 0x1f);
    EXPECT_EQ(eeprom_read_word((uint16_t*)6), 0xd00d);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)150), 0xcafef00d);
    EXPECT_EQ(eeprom_read_dword((uint32_t*)200), val);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE], 0xFFFF);
    EXPECT_EQ(*(uint16_t*)&FlashBuf[LOG_BASE + LOG_SIZE - 2], 0xFFFF);
}
