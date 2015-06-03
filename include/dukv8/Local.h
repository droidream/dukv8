//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_LOCAL_H
#define DUKV8_LOCAL_H

#include "Base.h"
#include "Handle.h"
#include "HandleScope.h"

namespace v8 {

/**
 * A light-weight stack-allocated object handle.  All operations
 * that return objects from within v8 return them in local handles.  They
 * are created within HandleScopes, and all local handles allocated within a
 * handle scope are destroyed when the handle scope is destroyed.  Hence it
 * is not necessary to explicitly deallocate local handles.
 */
template<class T> class Local : public Handle<T> {
public:
    inline Local() { }
    template<class S>
    inline Local(Local<S> that)
            : Handle<T>(reinterpret_cast<T *>(*that)) {
        /**
         * This check fails when trying to convert between incompatible
         * handles. For example, converting from a Handle<String> to a
         * Handle<Number>.
         */
        TYPE_CHECK(T, S);
    }
    template<class S>
    inline Local(S *that) : Handle<T>(that) { }
    template<class S>
    static inline Local<T> Cast(Local<S> that) {
#ifdef V8_ENABLE_CHECKS
    // If we're going to perform the type check then we have to check
    // that the handle isn't empty before doing the checked cast.
    if (that.IsEmpty()) return Local<T>();
#endif
        return Local<T>(T::Cast(*that));
    }

    template<class S>
    inline Local<S> As() {
        return Local<S>::Cast(*this);
    }

    /** Create a local handle for the content of another handle.
     *  The referee is kept alive by the local handle even when
     *  the original handle is destroyed/disposed.
     */
    inline static Local<T> New(Handle<T> that);
};

template<class T>
inline Local<T> Local<T>::New(Handle<T> that) {
    if (that.IsEmpty()) return Local<T>();
    T *that_ptr = *that;
    internal::Object *p = reinterpret_cast<internal::Object *>(that_ptr);
    return Local<T>(reinterpret_cast<T *>(HandleScope::CreateHandle(p)));
}

}

#endif //DUKV8_LOCAL_H
