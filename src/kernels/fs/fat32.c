/*
 * Copyright (C) 2025 ~ ? Ai-Upace
 * Powered by Visual Operating System (VOS)
 * 
 * BY GPLv3 LICENSE:
 * - This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 * 
 * But if you want to shut down? No way! Please to
 * - Mental hospital
 * - FSF (Free Software Foundation)
 * - Court
 * 
 * - cn v :
 * 版权所有 (C) 2025 ~ ? Ai-Upace
 * 基于 VOS (Visual Operating System) 开发
 * 
 * 根据 GPLv3 许可证：
 * - 本程序是自由软件：您可以根据 GNU 通用公共许可证的条款重新分发和/或修改它
 * - 由自由软件基金会发布的 GNU 通用公共许可证
 * 
 * 但如果你想闭源？没门！请去;
 * - 精神病院
 * - 自由软件基金会 (FSF)
 * - 法院
 * 
 * END
 * <jntmngmhahayo@outlook.com>
 * <jntmngmhahayo@gmail.com>
 * 
 */
// FAT32 - fat32.c
#include <stdint.h>

// FAT32引导扇区（BPB）结构体
typedef struct {
    uint8_t  jump_boot[3];
    uint8_t  oem_name[8];
    uint16_t bytes_per_sector;
    uint8_t  sectors_per_cluster;
    uint16_t reserved_sector_count;
    uint8_t  num_fats;
    uint16_t root_entry_count;
    uint16_t total_sectors_16;
    uint8_t  media;
    uint16_t fat_size_16;
    uint16_t sectors_per_track;
    uint16_t num_heads;
    uint32_t hidden_sectors;
    uint32_t total_sectors_32;
    // FAT32扩展
    uint32_t fat_size_32;
    uint16_t ext_flags;
    uint16_t fs_version;
    uint32_t root_cluster;
    uint16_t fs_info;
    uint16_t backup_boot_sector;
    uint8_t  reserved[12];
    uint8_t  drive_number;
    uint8_t  reserved1;
    uint8_t  boot_signature;
    uint32_t volume_id;
    uint8_t  volume_label[11];
    uint8_t  fs_type[8];
} __attribute__((packed)) FAT32_BPB;

// FAT32目录项结构体
typedef struct {
    uint8_t  name[11];
    uint8_t  attr;
    uint8_t  ntres;
    uint8_t  crt_time_tenth;
    uint16_t crt_time;
    uint16_t crt_date;
    uint16_t last_access_date;
    uint16_t first_cluster_high;
    uint16_t write_time;
    uint16_t write_date;
    uint16_t first_cluster_low;
    uint32_t file_size;
} __attribute__((packed)) FAT32_DirEntry;

// 读取FAT表项
uint32_t fat32_read_fat_entry(uint8_t* fat, uint32_t cluster) {
    // FAT表每项4字节
    uint32_t entry_offset = cluster * 4;
    return *(uint32_t*)(fat + entry_offset) & 0x0FFFFFFF; // 低28位有效
}

// 设置FAT表项
void fat32_write_fat_entry(uint8_t* fat, uint32_t cluster, uint32_t value) {
    uint32_t entry_offset = cluster * 4;
    uint32_t* entry = (uint32_t*)(fat + entry_offset);
    *entry = (*entry & 0xF0000000) | (value & 0x0FFFFFFF);
}