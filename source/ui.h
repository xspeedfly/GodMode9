// Copyright 2013 Normmatt
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include "common.h"

#define BYTES_PER_PIXEL 3
#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH_TOP 400
#define SCREEN_WIDTH_BOT 320

#define RGB(r,g,b) (r<<24|b<<16|g<<8|r)

#define COLOR_BLACK         RGB(0x00, 0x00, 0x00)
#define COLOR_WHITE         RGB(0xFF, 0xFF, 0xFF)
#define COLOR_GREY          RGB(0x80, 0x80, 0x80)

#define COLOR_RED           RGB(0xFF, 0x00, 0x00)
#define COLOR_GREEN         RGB(0x00, 0xFF, 0x00)
#define COLOR_BLUE          RGB(0x00, 0x00, 0xFF)
#define COLOR_YELLOW        RGB(0xFF, 0xFF, 0x00)
#define COLOR_CYAN          RGB(0xFF, 0x00, 0xFF)

#define COLOR_BRIGHTRED     RGB(0xFF, 0x30, 0x30)
#define COLOR_BRIGHTYELLOW  RGB(0xFF, 0xFF, 0x30)
#define COLOR_BRIGHTGREEN   RGB(0x30, 0xFF, 0x30)

#define COLOR_TINTEDBLUE    RGB(0x60, 0x60, 0x80)
#define COLOR_TINTEDYELLOW  RGB(0xD0, 0xD0, 0x60)
#define COLOR_TINTEDGREEN   RGB(0x70, 0x80, 0x70)
#define COLOR_DARKGREY      RGB(0x50, 0x50, 0x50)
#define COLOR_DARKESTGREY   RGB(0x20, 0x20, 0x20)

#define COLOR_TRANSPARENT   RGB(0xFF, 0x00, 0xEF) // otherwise known as 'super fuchsia'

#define COLOR_STD_BG        COLOR_BLACK
#define COLOR_STD_FONT      COLOR_WHITE

#ifdef EXEC_GATEWAY
	#define TOP_SCREEN0 (u8*)(*(u32*)((uint32_t)0x080FFFC0 + 4 * (*(u32*)0x080FFFD8 & 1)))
	#define BOT_SCREEN0 (u8*)(*(u32*)((uint32_t)0x080FFFD0 + 4 * (*(u32*)0x080FFFDC & 1)))
	#define TOP_SCREEN1 TOP_SCREEN0
	#define BOT_SCREEN1 BOT_SCREEN0
#elif defined(EXEC_BOOTSTRAP)
	#define TOP_SCREEN0 (u8*)(*(u32*)0x23FFFE00)
	#define TOP_SCREEN1 (u8*)(*(u32*)0x23FFFE00)
	#define BOT_SCREEN0 (u8*)(*(u32*)0x23FFFE08)
	#define BOT_SCREEN1 (u8*)(*(u32*)0x23FFFE08)
#else
	#error "Unknown execution method"
#endif

void ClearScreen(unsigned char *screen, int width, int color);
void ClearScreenF(bool clear_top, bool clear_bottom, int color);

void DrawRectangle(u8* screen, int x, int y, int width, int height, int color);
void DrawRectangleF(bool use_top, int x, int y, int width, int height, int color);

void DrawCharacter(unsigned char *screen, int character, int x, int y, int color, int bgcolor);
void DrawString(unsigned char *screen, const char *str, int x, int y, int color, int bgcolor);
void DrawStringF(bool use_top, int x, int y, int color, int bgcolor, const char *format, ...);

u32 GetDrawStringHeight(const char* str);
u32 GetDrawStringWidth(char* str);

void ResizeString(char* dest, const char* orig, int nsize, int tpos, bool align_right);
void TruncateString(char* dest, const char* orig, int nsize, int tpos);
void FormatNumber(char* str, u64 number);
void FormatBytes(char* str, u64 bytes);

bool ShowPrompt(bool ask, const char *format, ...);
bool ShowUnlockSequence(u32 seqlvl, const char *format, ...);
bool ShowInputPrompt(char* inputstr, u32 max_size, const char *format, ...);
bool ShowProgress(u64 current, u64 total, const char* opstr);
