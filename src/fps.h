#pragma once

#include <chrono>

namespace spare {
class FpsCounter {
public:
	FpsCounter();
	float getFps();
	bool update();  // Update the counter, return true if counter updated
private:
	float fps;
	int frames;
	std::chrono::time_point<std::chrono::high_resolution_clock> last_update;
};
}  // namespace spare
