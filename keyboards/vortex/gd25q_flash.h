#ifndef GD25Q_FLASH_H
#define GD25Q_FLASH_H

#define GD25Q40_SECTORS         128
#define GD25Q40_SECTOR_BYTES    4096

#define GD24Q40_PAGES           2048
#define GD25Q40_PAGE_BYTES      256

#define GD24Q40_BYTES   (GD25Q40_SECTORS * GD25Q40_SECTOR_BYTES)

#define GD25Q_WREN      0x06    // Write Enable
#define GD25Q_WRDI      0x04    // Write Disable
#define GD25Q_RDSR_L    0x05    // Read Status Register S7~S0
#define GD25Q_RDSR_H    0x35    // Read Status Register S15~S8
#define GD25Q_WRSR      0x01    // Write Status Register
#define GD25Q_READ      0x03    // Read Data Bytes
#define GD25Q_FAST_READ 0x0B    // Read Data Bytes At Higher Speed
#define GD25Q_PP        0x02    // Page Program
#define GD25Q_SE        0x20    // Sector Erase
#define GD25Q_BE_32K    0x52    // 32KB Block Erase
#define GD25Q_BE_64K    0xD8    // 64KB Block Erase
#define GD25Q_CE        0xC7    // Chip Erase
#define GD25Q_DP        0xB9    // Deep Power-Down
#define GD25Q_RDI       0xAB    // Release From Deep Power-Down
#define GD25Q_REMS      0x90    // Read Maufacturer/Device ID
#define GD25Q_RDID      0x9F    // Read Identification

#define GD25Q_SR_WIP    0x01    // Write In Progress
#define GD25Q_SR_WEL    0x02    // Write Enable Latch
#define GD25Q_SR_BP0    0x04    // Block Protect 0
#define GD25Q_SR_BP1    0x08    // Block Protect 1
#define GD25Q_SR_BP2    0x10    // Block Protect 2
#define GD25Q_SR_BP3    0x20    // Block Protect 3
#define GD25Q_SR_BP4    0x40    // Block Protect 4

#endif // GD25Q_FLASH_H
