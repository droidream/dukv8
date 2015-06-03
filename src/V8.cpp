//
// Created by Jiang Lu on 6/2/15.
//

#include <dukv8/V8.h>
#include <dukv8/Isolate.h>
#include <dukv8/Persistent.h>
#include <dukv8/GlobalStash.h>

namespace v8 {

/**
 * Schedules an exception to be thrown when returning to JavaScript.  When an
 * exception has been scheduled it is illegal to invoke any JavaScript
 * operation; the caller must return immediately and only after the exception
 * has been handled does it become legal to invoke JavaScript operations.
 */
Handle<Value> V8EXPORT ThrowException(Handle<Value> exception) {
//#if 1 // V8LIKE_DEBUG
//    if (strstr(*String::Utf8Value(exception->ToString()), "ENOENT") == NULL) {
//        printf("exception: %s\n", *String::Utf8Value(exception->ToString()));
//        if (exception->IsObject()) {
//            Handle<Value> stack = exception.As<Object>()->Get(String::NewSymbol("stack"));
//            printf("%s\n", *String::Utf8Value(stack->ToString()));
//        }
//    }
//#endif
//    sg_last_exception = exception;
//    return exception;
    return exception;
}

void V8::SetFlagsFromCommandLine(int *argc, char **argv, bool remove_flags) {
}

const char *V8::GetVersion() {
    return "3.14.5.9";
}

bool V8::Initialize() {
    Isolate *isolate = Isolate::New();
    isolate->Enter();
    atexit([]() {
        Isolate::GetCurrent()->Dispose();
    });
    return true;
}

bool V8::Dispose() {
    return true;
}

internal::Object *V8::GlobalizeReference(internal::Object *handle) {

    i::GCObject *gcobject = RTTI_DynamicCast(
            i::GCObject, reinterpret_cast<i::GCObject *>(handle));
    if (gcobject) {
        i::GlobalStash stash("__persistent");
        gcobject->AddToGlobalStash(&stash);
    }

    return handle;
}

void V8::DisposeGlobal(internal::Object *global_handle) {
    i::GCObject *gcobject = RTTI_DynamicCast(
            i::GCObject, reinterpret_cast<i::GCObject *>(global_handle));
    if (gcobject) {
        i::GlobalStash stash("__persistent");
        gcobject->RemoveFromGlobalStash(&stash);
    }
}

void V8::MakeWeak(internal::Object *global_handle,
                  void *data,
                  WeakReferenceCallback callback) {
}

}