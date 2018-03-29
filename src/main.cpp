#include "engine.h"

int main(int argc, char **argv) {
	spare::Engine engine(640, 480);
	return engine.OnExecute();
}
