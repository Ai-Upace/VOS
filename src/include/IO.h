#pragma once
#ifdef IO_H
#define IO_H

static inline void outb(unsigned short port, unsigned char val);
static inline unsigned char inb(unsigned short port);

#endif