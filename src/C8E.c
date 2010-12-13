#include "Logs.h"
#include "Memory.h"

int main() {
	setupLogs(1, LOW_LEVEL_OPERATION, DEFAULT_OUTPUT_FILENAME);

	setupMemory();
	cleanupMemory();

	closeLogs();
	return 0;
}
