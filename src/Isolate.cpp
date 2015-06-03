//
// Created by Jiang Lu on 6/2/15.
//

#include <cassert>
#include <dukv8/Isolate.h>

namespace v8 {

Isolate *Isolate::s_current_isolate_ = NULL;

Isolate::Isolate() :
        previous_isolate_(NULL),
        data_(NULL),
        auto_release_pool_(new i::AutoReleasePool) {
    dukctx_ = duk_create_heap_default();
}

Isolate::~Isolate() {
    duk_destroy_heap(dukctx_);
    delete auto_release_pool_;
}

/**
 * Creates a new isolate.  Does not change the currently entered
 * isolate.
 *
 * When an isolate is no longer used its resources should be freed
 * by calling Dispose().  Using the delete operator is not allowed.
 */
Isolate *Isolate::New() {
    return new Isolate();
}

/**
 * Returns the entered isolate for the current thread or NULL in
 * case there is no current isolate.
 */
Isolate *Isolate::GetCurrent() {
    return s_current_isolate_;
}

/**
 * Custom callback used by embedders to help V8 determine if it should abort
 * when it throws and no internal handler can catch the exception.
 * If FLAG_abort_on_uncaught_exception is true, then V8 will abort if either:
 * - no custom callback is set.
 * - the custom callback set returns true.
 * Otherwise it won't abort.
 */
void Isolate::SetAbortOnUncaughtException(abort_on_uncaught_exception_t callback) {
}

/**
 * Methods below this point require holding a lock (using Locker) in
 * a multi-threaded environment.
 */

/**
 * Sets this isolate as the entered one for the current thread.
 * Saves the previously entered one (if any), so that it can be
 * restored when exiting.  Re-entering an isolate is allowed.
 */
void Isolate::Enter() {
    previous_isolate_ = s_current_isolate_;
    s_current_isolate_ = this;
}

/**
 * Exits this isolate by restoring the previously entered one in the
 * current thread.  The isolate may still stay the same, if it was
 * entered more than once.
 *
 * Requires: this == Isolate::GetCurrent().
 */
void Isolate::Exit() {
    assert(this == s_current_isolate_);
    s_current_isolate_ = previous_isolate_;
    previous_isolate_ = NULL;
}

/**
 * Disposes the isolate.  The isolate must not be entered by any
 * thread to be disposable.
 */
void Isolate::Dispose() {
    delete this;
}

}
