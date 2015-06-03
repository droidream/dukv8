//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_PERSISTENT_H
#define DUKV8_PERSISTENT_H

#include <dukv8/Base.h>
#include <dukv8/Handle.h>
#include <dukv8/Value.h>
#include <dukv8/V8.h>

namespace v8 {

/**
 * An object reference that is independent of any handle scope.  Where
 * a Local handle only lives as long as the HandleScope in which it was
 * allocated, a Persistent handle remains valid until it is explicitly
 * disposed.
 *
 * A persistent handle contains a reference to a storage cell within
 * the v8 engine which holds an object value and which is updated by
 * the garbage collector whenever the object is moved.  A new storage
 * cell can be created using Persistent::New and existing handles can
 * be disposed using Persistent::Dispose.  Since persistent handles
 * are passed by value you may have many persistent handle objects
 * that point to the same storage cell.  For instance, if you pass a
 * persistent handle as an argument to a function you will not get two
 * different storage cells but rather two references to the same
 * storage cell.
 */
template<class T> class Persistent : public Handle<T> {
public:
    /**
     * Creates an empty persistent handle that doesn't point to any
     * storage cell.
     */
    inline Persistent();

    /**
     * Creates a persistent handle for the same storage cell as the
     * specified handle.  This constructor allows you to pass persistent
     * handles as arguments by value and to assign between persistent
     * handles.  However, attempting to assign between incompatible
     * persistent handles, for instance from a Persistent<String> to a
     * Persistent<Number> will cause a compile-time error.  Assigning
     * between compatible persistent handles, for instance assigning a
     * Persistent<String> to a variable declared as Persistent<Value>,
     * is allowed as String is a subclass of Value.
     */
    template<class S>
    inline Persistent(Persistent<S> that)
            : Handle<T>(reinterpret_cast<T *>(*that)) {
        /**
         * This check fails when trying to convert between incompatible
         * handles. For example, converting from a Handle<String> to a
         * Handle<Number>.
         */
        TYPE_CHECK(T, S);
    }

    template<class S>
    inline Persistent(S *that) : Handle<T>(that) { }

    /**
     * "Casts" a plain handle which is known to be a persistent handle
     * to a persistent handle.
     */
    template<class S>
    explicit inline Persistent(Handle<S> that)
            : Handle<T>(*that) { }

    template<class S>
    static inline Persistent<T> Cast(Persistent<S> that) {
#ifdef V8_ENABLE_CHECKS
    // If we're going to perform the type check then we have to check
    // that the handle isn't empty before doing the checked cast.
    if (that.IsEmpty()) return Persistent<T>();
#endif
        return Persistent<T>(T::Cast(*that));
    }

    template<class S>
    inline Persistent<S> As() {
        return Persistent<S>::Cast(*this);
    }

    /**
     * Creates a new persistent handle for an existing local or
     * persistent handle.
     */
    inline static Persistent<T> New(Handle<T> that);

    /**
     * Releases the storage cell referenced by this persistent handle.
     * Does not remove the reference to the cell from any handles.
     * This handle's reference, and any other references to the storage
     * cell remain and IsEmpty will still return false.
     */
    inline void Dispose();

    /**
     * Make the reference to this object weak.  When only weak handles
     * refer to the object, the garbage collector will perform a
     * callback to the given V8::WeakReferenceCallback function, passing
     * it the object reference and the given parameters.
     */
    inline void MakeWeak(void *parameters, WeakReferenceCallback callback);

    /** Clears the weak reference to this object. */
    inline void ClearWeak();

    /**
     * Marks the reference to this object independent. Garbage collector
     * is free to ignore any object groups containing this object.
     * Weak callback for an independent handle should not
     * assume that it will be preceded by a global GC prologue callback
     * or followed by a global GC epilogue callback.
     */
    inline void MarkIndependent();

    /** Returns true if this handle was previously marked as independent. */
    inline bool IsIndependent() const;

    /** Checks if the handle holds the only reference to an object. */
    inline bool IsNearDeath() const;

    /** Returns true if the handle's reference is weak.  */
    inline bool IsWeak() const;

    /**
     * Assigns a wrapper class ID to the handle. See RetainedObjectInfo
     * interface description in v8-profiler.h for details.
     */
    inline void SetWrapperClassId(uint16_t class_id);

    /**
     * Returns the class ID previously assigned to this handle or 0 if no class
     * ID was previously assigned.
     */
    inline uint16_t WrapperClassId() const;

private:
    friend class ImplementationUtilities;
    friend class ObjectTemplate;
};

template<class T>
Persistent<T>::Persistent() : Handle<T>() { }

/**
 * Creates a new persistent handle for an existing local or
 * persistent handle.
 */
template<class T>
inline Persistent<T> Persistent<T>::New(Handle<T> that) {
    if (that.IsEmpty()) return Persistent<T>();
    T *p = *that;
    return Persistent<T>(reinterpret_cast<T *>(V8::GlobalizeReference(
            reinterpret_cast<internal::Object *>(p))));
}

/**
 * Releases the storage cell referenced by this persistent handle.
 * Does not remove the reference to the cell from any handles.
 * This handle's reference, and any other references to the storage
 * cell remain and IsEmpty will still return false.
 */
template<class T>
inline void Persistent<T>::Dispose() {
    if (this->IsEmpty()) return;
    V8::DisposeGlobal(reinterpret_cast<internal::Object *>(**this));
}

}

#endif //DUKV8_PERSISTENT_H
