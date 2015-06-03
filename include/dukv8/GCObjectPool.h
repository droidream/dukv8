//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_GCOBJECTPOOL_H
#define DUKV8_GCOBJECTPOOL_H

#include "Base.h"

namespace v8 {
namespace internal {

class GCObjectPool {
public:
    GCObjectPool();
    ~GCObjectPool();

    void AddObject(void *val);

protected:
    void Initialize();
    void EnsureObjectList();
    void addNewList();
    void removeList();

private:
    bool initialized_;
    int list_idx_;
    void *list_ptr_;
};

}
}

#endif //DUKV8_GCOBJECTPOOL_H
