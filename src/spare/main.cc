#include "engine.h"

int main(int argc, char **argv) {
	spare::Engine engine(1024, 768);
	return engine.OnExecute();
}
