//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_AUTORELEASEPOOL_H
#define DUKV8_AUTORELEASEPOOL_H

#include "Base.h"

namespace v8 {
namespace internal {

class AutoReleasePool {
public:
    ~AutoReleasePool() {
        Release();
    }

    void *AutoRelease(void *heap_ptr);

    void Release();
};

}
}

#endif //DUKV8_AUTORELEASEPOOL_H
