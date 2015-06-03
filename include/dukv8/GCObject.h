//
// Created by Jiang Lu on 6/3/15.
//

#ifndef DUKV8_GCOBJECT_H
#define DUKV8_GCOBJECT_H

#include "Base.h"
#include "GCObjectPool.h"
#include "GlobalStash.h"

namespace v8 {
namespace internal {

class GCObject {
public:
    RTTI_DECLARE_ROOT(v8::internal::GCObject);

    GCObject();
    virtual ~GCObject();

    void AddToObjectPool(GCObjectPool *pool) const;

    void AddToGlobalStash(i::GlobalStash *stash) const;

    void RemoveFromGlobalStash(i::GlobalStash *stash) const;

private:
    void *gcobject_heap_ptr_;
    int gcobject_stash_index_;
};

}
}


#endif //DUKV8_GCOBJECT_H
