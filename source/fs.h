#pragma once

#include "common.h"

typedef enum {
    T_ROOT,
    T_DIR,
    T_FILE,
    T_DOTDOT
} EntryType;

#define MAX_ENTRIES 1024

typedef struct {
    char* name; // should point to the correct portion of the path
    char path[256];
    u64 size;
    EntryType type;
    u8 marked;
} DirEntry;

typedef struct {
    u32 n_entries;
    DirEntry entry[MAX_ENTRIES];
} DirStruct;

bool InitSDCardFS();
bool InitExtFS();
void DeinitExtFS();
void DeinitSDCardFS();

/** Check if writing to this path is allowed **/
bool CheckWritePermissions(const char* path);

/** Set new write permissions */
bool SetWritePermissions(u32 level);

/** Get write permissions */
u32 GetWritePermissions();

/** Create / overwrite file and write the provided data to it **/
bool FileCreateData(const char* path, u8* data, size_t size);

/** Read data from file@offset **/
size_t FileGetData(const char* path, u8* data, size_t size, size_t foffset);

/** Get size of file **/
size_t FileGetSize(const char* path);

/** Recursively copy a file or directory **/
bool PathCopy(const char* destdir, const char* orig);

/** Recursively delete a file or directory **/
bool PathDelete(const char* path);

/** Rename file / folder in path to new name **/
bool PathRename(const char* path, const char* newname);

/** Create a new directory in cpath **/
bool DirCreate(const char* cpath, const char* dirname);

/** Create a screenshot of the current framebuffer **/
void CreateScreenshot();

/** Get directory content under a given path **/
void GetDirContents(DirStruct* contents, const char* path);

/** Gets remaining space in filesystem in bytes */
uint64_t GetFreeSpace(const char* path);

/** Gets total spacein filesystem in bytes */
uint64_t GetTotalSpace(const char* path);

/** Return the offset - in sectors - of the FAT partition on the drive **/
uint64_t GetPartitionOffsetSector(const char* path);

/** Helper function to get drive number from path */
int PathToNumFS(const char* path);

/** Check if drive is mounted */
bool IsMountedFS(const char* path);

/** Helper function for copying DirEntry structs */
void DirEntryCpy(DirEntry* dest, const DirEntry* orig);
