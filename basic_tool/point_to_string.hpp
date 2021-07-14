#include <string>
#include <sstream>

namespace basic {
enum {
    ADDR_SIZE = sizeof(intptr_t) * 2 + 2
};
template<typename T>
std::string ptr2str(const T* p) {
    std::string ptr(ADDR_SIZE, '\0');
    if(4 == sizeof(intptr_t)) {
        // 32 bit
        sprintf(&ptr[0], "0x%08x", (unsigned int)(intptr_t)p);
    }
    else {
        // 64 bit
        sprintf(&ptr[0], "0x%016lx", (unsigned long)(intptr_t)p);
    }
    return ptr;
}
} // namespace basic