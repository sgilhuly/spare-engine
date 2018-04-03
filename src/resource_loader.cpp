#include "resource_loader.h"

#include <string>

bool icompare_pred(unsigned char a, unsigned char b) {
    return std::tolower(a) == std::tolower(b);
}

bool string_has_extension(const std::string& a, const std::string& b) {
    if (a.length() == b.length()) {
        return std::equal(b.begin(), b.end(), a.begin(), icompare_pred);
    } else {
        return false;
    }
}

namespace spare {
ResourceLoader::ResourceLoader() {
}
}  // namespace spare
