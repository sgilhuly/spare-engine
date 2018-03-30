#include "fps.h"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::milliseconds;

using time_point = std::chrono::time_point<std::chrono::high_resolution_clock>;

namespace spare {
FpsCounter::FpsCounter() {
	fps = 0;
	frames = 0;
	last_update = high_resolution_clock::now();
}

float FpsCounter::getFps() {
	return fps;
}

bool FpsCounter::update() {
	frames++;
	time_point now = high_resolution_clock::now();
	int millis = duration_cast<milliseconds>(now - last_update).count();

	if (millis > 250) {
		fps = (frames * 1000.0f) / millis;
		frames = 0;
		last_update = now;

		return true;
	}

	return false;
}
}  // namespace spare
