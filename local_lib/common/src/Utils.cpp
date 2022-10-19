#include "Utils.h"
#include "Const.h"

namespace SHILY_UTILS {
std::string toResourcePath(std::string & path) {
    std::string _path(ROOT_PATH);
    _path += "\\resources\\";
    _path += path;
    return _path;
}
}
