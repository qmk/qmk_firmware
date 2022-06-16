/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    src/gfile/gfile_options.h
 * @brief   GFILE - File IO options header file.
 *
 * @addtogroup GFILE
 * @{
 */

#ifndef _GFILE_OPTIONS_H
#define _GFILE_OPTIONS_H

/**
 * @name    GFILE Functionality to be included
 * @{
 */
	/**
	 * @brief	Should the filesystem not be mounted automatically
	 * @details	The filesystem is normally mounted automatically if the
	 *			user does not do it manually. This option turns that off
	 *			so the user must manually mount the file-system first.
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GFILE_NEED_NOAUTOMOUNT
		#define GFILE_NEED_NOAUTOMOUNT	GFXOFF
	#endif
	/**
	 * @brief	Should the filesystem be synced automatically
	 * @details	The filesystem will automatically be synced after an open() or
	 *			write() call unless this feature is disabled.
	 * @details	If this feature is disabled, the user should sync the filesystem
	 *			himself using @p gfileSync()
	 * @details	Not all filesystems implement the syncing feature. This feature will
	 *			have no effect in such a case.
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GFILE_NEED_NOAUTOSYNC
		#define GFILE_NEED_NOAUTOSYNC	GFXOFF
	#endif
	/**
	 * @brief   Include printg, fprintg etc functions
	 * @details	Defaults to GFXOFF
	 * @pre		To get the string sprintg functions you also need to define @p GFILE_NEED_STRINGS
	 */
	#ifndef GFILE_NEED_PRINTG
		#define GFILE_NEED_PRINTG		GFXOFF
	#endif
	/**
	 * @brief   Include scang, fscang etc functions
	 * @details	Defaults to GFXOFF
	 * @pre		To get the string sscang functions you also need to define @p GFILE_NEED_STRINGS
	 */
	#ifndef GFILE_NEED_SCANG
		#define GFILE_NEED_SCANG		GFXOFF
	#endif
	/**
	 * @brief   Include the string based file functions
	 * @details	Defaults to GFXOFF
	 */
	#ifndef GFILE_NEED_STRINGS
		#define GFILE_NEED_STRINGS		GFXOFF
	#endif
	/**
	 * @brief   Map many stdio functions to their GFILE equivalent
	 * @details	Defaults to GFXOFF
	 * @note	This replaces the functions in stdio.h with equivalents
	 * 			- Do not include stdio.h as it has different conflicting definitions.
	 */
	#ifndef GFILE_NEED_STDIO
		#define GFILE_NEED_STDIO		GFXOFF
	#endif
	/**
	 * @brief   Include the USER file system
	 * @details	Defaults to GFXOFF
	 * @note	The User FS vmt strcture 'FsUSERVMT' must be defined and implemented in the user's project.
	 * @note	If GFILE_ALLOW_DEVICESPECIFIC is on then you can ensure that you are
	 * 			opening a file on the USER file system by prefixing
	 * 			its name with "U|" (the letter 'U', followed by a vertical bar).
	 *			The letter 'U' as described above should be replaced by the actual
	 *			device specifier letter in the user's FsUSERVMT structure. It is suggested
	 *			that it is actually the letter 'U' that is used and it is important that the letter
	 *			used is not one used by the other file systems.
	 */
	#ifndef GFILE_NEED_USERFS
		#define GFILE_NEED_USERFS		GFXOFF
	#endif
	/**
	 * @brief   Include the ROM file system
	 * @details	Defaults to GFXOFF
	 * @note	If GFILE_ALLOW_DEVICESPECIFIC is on then you can ensure that you are
	 * 			opening a file on the ROM file system by prefixing
	 * 			its name with "S|" (the letter 'S', followed by a vertical bar).
	 * @note	This requires a file called romfs_files.h to be in the
	 * 			users project include path. This file should include all the files
	 * 			converted to .h files using the file2c utility (using flags "-dbcs").
	 */
	#ifndef GFILE_NEED_ROMFS
		#define GFILE_NEED_ROMFS		GFXOFF
	#endif
	/**
	 * @brief   Include the RAM file system
	 * @details	Defaults to GFXOFF
	 * @note	If GFILE_ALLOW_DEVICESPECIFIC is on then you can ensure that you are
	 * 			opening a file on the RAM file system by prefixing
	 * 			its name with "R|" (the letter 'R', followed by a vertical bar).
	 * @note	You must also define GFILE_RAMFS_SIZE with the size of the file system
	 * 			to be allocated in RAM.
	 */
	#ifndef GFILE_NEED_RAMFS
		#define GFILE_NEED_RAMFS		GFXOFF
	#endif
	/**
	 * @brief   Include the FAT file system driver based on the FATFS library
	 * @details	Defaults to GFXOFF
	 * @note	If GFILE_ALLOW_DEVICESPECIFIC is on then you can ensure that you are
	 * 			opening a file on the FAT file system by prefixing
	 * 			its name with "F|" (the letter 'F', followed by a vertical bar).
	 * @note	FATFS and PETITFS offer the same FAT file system support. They just use
	 * 			different constraints. PETITFS is smaller but has less features. Only
	 * 			one can be used at a time. The block interfaces are also different.
	 */
	#ifndef GFILE_NEED_FATFS
		#define GFILE_NEED_FATFS		GFXOFF
	#endif
	/**
	 * @brief   Include the FAT file system driver based on the PETITFS library
	 * @details	Defaults to GFXOFF
	 * @note	If GFILE_ALLOW_DEVICESPECIFIC is on then you can ensure that you are
	 * 			opening a file on the FAT file system by prefixing
	 * 			its name with "F|" (the letter 'F', followed by a vertical bar).
	 * @note	FATFS and PETITFS offer the same FAT file system support. They just use
	 * 			different constraints. PETITFS is smaller but has less features. Only
	 * 			one can be used at a time. The block interfaces are also different.
	 * @note	Due to the restrictions on the PETITFS library on writing, we do not implement
	 * 			writing.
	 * @note	PETITFS can only have one file open at a time.
	 */
	#ifndef GFILE_NEED_PETITFS
		#define GFILE_NEED_PETITFS		GFXOFF
	#endif
	/**
	 * @brief   Include the operating system's native file system
	 * @details	Defaults to GFXOFF
	 * @note	If GFILE_ALLOW_DEVICESPECIFIC is on then you can ensure that you are
	 * 			opening a file on the native file system by prefixing
	 * 			its name with "N|" (the letter 'N', followed by a vertical bar).
	 * @note	If defined then the gfileStdOut and gfileStdErr handles
	 * 			use the operating system equivalent stdio and stderr.
	 * 			If it is not defined the gfileStdOut and gfileStdErr io is discarded.
	 */
	#ifndef GFILE_NEED_NATIVEFS
		#define GFILE_NEED_NATIVEFS		GFXOFF
	#endif
	/**
	 * @brief   Include ChibiOS BaseFileStream support
	 * @details	Defaults to GFXOFF
	 * @pre		This is only relevant on the ChibiOS operating system.
	 * @note	Use the @p gfileOpenBaseFileStream() call to open a GFILE based on a
	 * 			BaseFileStream. The BaseFileStream must already be open.
	 * @note	A GFile of this type cannot be opened by filename. The BaseFileStream
	 * 			must be pre-opened using the operating system.
	 */
	#ifndef GFILE_NEED_CHIBIOSFS
		#define GFILE_NEED_CHIBIOSFS	GFXOFF
	#endif
	/**
	 * @brief   Include raw memory pointer support
	 * @details	Defaults to GFXOFF
	 * @note	Use the @p gfileOpenMemory() call to open a GFILE based on a
	 * 			memory pointer. The GFILE opened appears to be of unlimited size.
	 * @note	A GFile of this type cannot be opened by filename.
	 */
	#ifndef GFILE_NEED_MEMFS
		#define GFILE_NEED_MEMFS		GFXOFF
	#endif
	/**
	 * @brief   Include support for file list functions
	 * @details	Defaults to GFXOFF
	 * @note	Adds support for @p gfileOpenFileList(), @p gfileReadFileList() and @p gfileCloseFileList().
	 */
	#ifndef GFILE_NEED_FILELISTS
		#define GFILE_NEED_FILELISTS	GFXOFF
	#endif
/**
 * @}
 *
 * @name    GFILE Optional Parameters
 * @{
 */
	/**
	 * @brief  Add floating point support to printg/scang etc.
	 */
	#ifndef GFILE_ALLOW_FLOATS
		#define GFILE_ALLOW_FLOATS	GFXOFF
	#endif
	/**
	 * @brief   Can the device be specified as part of the file name.
	 * @note	If this is on then a device letter and a vertical bar can be
	 * 			prefixed on a file name to specify that it must be on a
	 * 			specific device.
	 */
	#ifndef GFILE_ALLOW_DEVICESPECIFIC
		#define GFILE_ALLOW_DEVICESPECIFIC		GFXOFF
	#endif
	/**
	 * @brief   The maximum number of open files
	 * @note	This count excludes gfileStdIn, gfileStdOut and gfileStdErr
	 * 			(if open by default).
	 */
	#ifndef GFILE_MAX_GFILES
		#define GFILE_MAX_GFILES		3
	#endif
	/**
	 * @brief   TUse an external FATFS library instead of the uGFX inbuilt one
	 * @note	This is applicable when GFILE_NEED_FATFS is specified. It allows
	 *			the programmer to use their own FATFS implementation provided the
	 *			api matches the fatfs-0.10b API.
	 * @note	The users ffconf.h file still needs to be reachable when compiling uGFX.
	 * @note	If ffconf.h contains _FS_REENTRANT as true then the user provided simpleton
	 *			routines must be compatible with uGFX threading.
	 * @note	If ffconf.h contains _USE_LFN == 3 then the user provided simpleton routines must
	 *			be compatible with uGFX memory management.
	 */
	#ifndef GFILE_FATFS_EXTERNAL_LIB
		#define GFILE_FATFS_EXTERNAL_LIB		GFXOFF
	#endif
	/**
	 * @brief   TUse an external PETITFS library instead of the uGFX inbuilt one
	 * @note	This is applicable when GFILE_NEED_PETITFS is specified. It allows
	 *			the programmer to use their own FATFS implementation provided the
	 *			api matches the petitfs-0.03 API.
	 * @note	The users pffconf.h file still needs to be reachable when compiling uGFX.
	 */
	#ifndef GFILE_PETITFS_EXTERNAL_LIB
		#define GFILE_PETITFS_EXTERNAL_LIB	GFXOFF
	#endif
	
/** @} */

#endif /* _GFILE_OPTIONS_H */
/** @} */
