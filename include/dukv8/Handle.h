//
// Created by Jiang Lu on 5/31/15.
//

#ifndef DUKV8_HANDLE_H
#define DUKV8_HANDLE_H

#include <stdio.h>

namespace v8 {

#define TYPE_CHECK(T, S)                                       \
    while (false) {                                            \
        *(static_cast<T* volatile*>(0)) = static_cast<S*>(0);  \
    }


/**
 * An object reference managed by the v8 garbage collector.
 *
 * All objects returned from v8 have to be tracked by the garbage
 * collector so that it knows that the objects are still alive.  Also,
 * because the garbage collector may move objects, it is unsafe to
 * point directly to an object.  Instead, all objects are stored in
 * handles which are known by the garbage collector and updated
 * whenever an object moves.  Handles should always be passed by value
 * (except in cases like out-parameters) and they should never be
 * allocated on the heap.
 *
 * There are two types of handles: local and persistent handles.
 * Local handles are light-weight and transient and typically used in
 * local operations.  They are managed by HandleScopes.  Persistent
 * handles can be used when storing objects across several independent
 * operations and have to be explicitly deallocated when they're no
 * longer used.
 *
 * It is safe to extract the object stored in the handle by
 * dereferencing the handle (for instance, to extract the Object* from
 * a Handle<Object>); the value will still be governed by a handle
 * behind the scenes and the same rules apply to these values as to
 * their handles.
 *
 * 虚拟机中 JS 对象的句柄
 */
template<class T>
class Handle {
public:
    /**
     * 创建一个空句柄
     */
    inline Handle() : val_(NULL) {
//        printf("%s\n", __PRETTY_FUNCTION__);
    }

    /**
     * 创建一个新句柄
     */
    inline explicit Handle(T *val) : val_(val) {
//        printf("%s\n", __PRETTY_FUNCTION__);
    }

    /**
     * Handle<String> -x- Handle<Number>
     * Handle<String> ->- Handle<Value>
     */
    template<class S>
    inline Handle(Handle<S> that) : val_(reinterpret_cast<T *>(*that)) {
        /**
         * This check fails when trying to convert between incompatible
         * handles. For example, converting from a Handle<String> to a
         * Handle<Number>.
         */
        TYPE_CHECK(T, S);
    }

    inline ~Handle() {
//        printf("%s\n", __PRETTY_FUNCTION__);
    }

    /**
     * Returns true if the handle is empty.
     */
    inline bool IsEmpty() const { return val_ == 0; }

    /**
     * Sets the handle to be empty. IsEmpty() will then return true.
     */
    inline void Clear() { val_ = 0; }

    inline T *operator->() const { return val_; }

    inline T *operator*() const { return val_; }

private:
    T *val_;
};

}


#endif //DUKV8_HANDLE_H
