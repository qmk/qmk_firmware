#include "gfx.h"
#include <string.h>

/* Function to log messages to a file. */
void LogInfo(const char* msg) {
	GFILE* logFile;
	
	logFile = gfileOpen("info.txt", "a");		// Open the file for append
	if (logfile) {
		gfileWrite(logFile, msg, strlen(msg));
		gfileClose(logFile);					// Close the file again
	}
}

int main(void) {
	GFILE* file;							// GFILE variable to store file info.
	const char msg[] = "Hello file!";		// String to write to a file.
	
	/* Call the µGFX init routine. */
	gfxInit();
	
	/* Mount the file system. */
	if (gfileMount('F', "/"))
		gfxHalt("Can't mount the FAT file system");

	/* Check if a file exists. */
	if (gfileExists("file.txt"))
		LogInfo("[Info]: File exists already!");
	else
		LogInfo("[Info]: The file does not exist yet!");	
	
	/* Write a string to the file. */
	file = gfileOpen("file.txt", "wx");
	if(!file) {
		LogInfo("[Error]: Something went wrong opening the file.");
		gfxHalt("Can't open the file file.txt");;
	}
	
	/* A normal write */		
	gfileWrite(file, msg, strlen(msg));
	
	/* Write the file size in the file using the uGFX equivalent of fprintf(). */
	fnprintg(file, 30, "The file is currently %dkB", gfileGetSize(file));
	
	/* Close the file */
	gfileClose(file);
	
	/* Rename te file. */
	gfileRename("file.txt", "renamedFile.txt");
	
	/* Unmount the file system again */
	gfileUnmount('F', "/");
	
	/* This line should not work as the file system is now unmounted */
	LogInfo("[Info]: Entering enldess while loop.");
	
	/* The program ends here. */
	while(1)
		gfxSleepMilliseconds(200);
}
