#include "Logs.h"

int main() {
	setupLogs(DEFAULT_DEBUG_LEVEL, DEFAULT_OUTPUT_FILENAME);
	
	addEntry(ERROR, "Je suis une erreur !");
	addEntry(WARNING, "Je suis un warning !");
	addEntry(DRAWING, "Je suis un dessin !");
	addEntry(DISASSEMBLING, "Je suis une instruction !");

	closeLogs();

	return 0;
}
