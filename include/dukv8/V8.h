//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_V8_H
#define DUKV8_V8_H

#include "Base.h"
#include "Handle.h"
#include "Value.h"
#include "Message.h"
#include "StackTrace.h"

namespace v8 {

namespace internal {
class Object;
}

typedef void (*FatalErrorCallback)(const char *location, const char *message);

typedef void (*MessageCallback)(Handle<Message> message, Handle<Value> error);

// --- Leave Script Callback ---
typedef void (*CallCompletedCallback)();

// --- Failed Access Check Callback ---
//typedef void (*FailedAccessCheckCallback)(Local < Object > target,
//                                          AccessType type,
//                                            Local <Value> data);

// --- AllowCodeGenerationFromStrings callbacks ---

/**
 * Callback to check if code generation from strings is allowed. See
 * Context::AllowCodeGenerationFromStrings.
 */
//typedef bool (*AllowCodeGenerationFromStringsCallback)(Local < Context > context);

class StartupData {
public:
    enum CompressionAlgorithm {
        kUncompressed,
        kBZip2
    };

    const char *data;
    int compressed_size;
    int raw_size;
};

typedef int *(*CounterLookupCallback)(const char *name);

typedef void *(*CreateHistogramCallback)(const char *name,
                                         int min,
                                         int max,
                                         size_t buckets);

typedef void (*AddHistogramSampleCallback)(void *histogram, int sample);

// --- Garbage Collection Callbacks ---

/**
 * Applications can register callback functions which will be called
 * before and after a garbage collection.  Allocations are not
 * allowed in the callback functions, you therefore cannot manipulate
 * objects (set or delete properties for example) since it is possible
 * such operations will result in the allocation of objects.
 */
enum GCType {
    kGCTypeScavenge = 1 << 0,
    kGCTypeMarkSweepCompact = 1 << 1,
    kGCTypeAll = kGCTypeScavenge | kGCTypeMarkSweepCompact
};

enum GCCallbackFlags {
    kNoGCCallbackFlags = 0,
    kGCCallbackFlagCompacted = 1 << 0
};

typedef void (*GCPrologueCallback)(GCType type, GCCallbackFlags flags);
typedef void (*GCEpilogueCallback)(GCType type, GCCallbackFlags flags);

typedef void (*GCCallback)();


// --- Memory Allocation Callback ---
enum ObjectSpace {
    kObjectSpaceNewSpace = 1 << 0,
    kObjectSpaceOldPointerSpace = 1 << 1,
    kObjectSpaceOldDataSpace = 1 << 2,
    kObjectSpaceCodeSpace = 1 << 3,
    kObjectSpaceMapSpace = 1 << 4,
    kObjectSpaceLoSpace = 1 << 5,

    kObjectSpaceAll = kObjectSpaceNewSpace | kObjectSpaceOldPointerSpace |
                      kObjectSpaceOldDataSpace | kObjectSpaceCodeSpace | kObjectSpaceMapSpace |
                      kObjectSpaceLoSpace
};

enum AllocationAction {
    kAllocationActionAllocate = 1 << 0,
    kAllocationActionFree = 1 << 1,
    kAllocationActionAll = kAllocationActionAllocate | kAllocationActionFree
};

typedef void (*MemoryAllocationCallback)(ObjectSpace space,
                                         AllocationAction action,
                                         int size);

class V8_EXPORT RetainedObjectInfo {
};

/**
 * EntropySource is used as a callback function when v8 needs a source
 * of entropy.
 */
typedef bool (*EntropySource)(unsigned char *buffer, size_t length);

/**
 * Schedules an exception to be thrown when returning to JavaScript.  When an
 * exception has been scheduled it is illegal to invoke any JavaScript
 * operation; the caller must return immediately and only after the exception
 * has been handled does it become legal to invoke JavaScript operations.
 */
Handle<Value> V8EXPORT ThrowException(Handle<Value> exception);

/**
 * Container class for static utility functions.
 */
class V8EXPORT V8 {
public:
    /** Set the callback to invoke in case of fatal errors. */
//    static void SetFatalErrorHandler(FatalErrorCallback that);

    /**
     * Set the callback to invoke to check if code generation from
     * strings should be allowed.
     */
//    static void SetAllowCodeGenerationFromStringsCallback(
//            AllowCodeGenerationFromStringsCallback that);

    /**
     * Ignore out-of-memory exceptions.
     *
     * V8 running out of memory is treated as a fatal error by default.
     * This means that the fatal error handler is called and that V8 is
     * terminated.
     *
     * IgnoreOutOfMemoryException can be used to not treat an
     * out-of-memory situation as a fatal error.  This way, the contexts
     * that did not cause the out of memory problem might be able to
     * continue execution.
     */
//    static void IgnoreOutOfMemoryException();

    /**
     * Check if V8 is dead and therefore unusable.  This is the case after
     * fatal errors such as out-of-memory situations.
     */
//    static bool IsDead();

    /**
     * The following 4 functions are to be used when V8 is built with
     * the 'compress_startup_data' flag enabled. In this case, the
     * embedder must decompress startup data prior to initializing V8.
     *
     * This is how interaction with V8 should look like:
     *   int compressed_data_count = v8::V8::GetCompressedStartupDataCount();
     *   v8::StartupData* compressed_data =
     *     new v8::StartupData[compressed_data_count];
     *   v8::V8::GetCompressedStartupData(compressed_data);
     *   ... decompress data (compressed_data can be updated in-place) ...
     *   v8::V8::SetDecompressedStartupData(compressed_data);
     *   ... now V8 can be initialized
     *   ... make sure the decompressed data stays valid until V8 shutdown
     *
     * A helper class StartupDataDecompressor is provided. It implements
     * the protocol of the interaction described above, and can be used in
     * most cases instead of calling these API functions directly.
     */
//    static StartupData::CompressionAlgorithm GetCompressedStartupDataAlgorithm();
//    static int GetCompressedStartupDataCount();
//    static void GetCompressedStartupData(StartupData *compressed_data);
//    static void SetDecompressedStartupData(StartupData *decompressed_data);

    /**
     * Adds a message listener.
     *
     * The same message listener can be added more than once and in that
     * case it will be called more than once for each message.
     *
     * If data is specified, it will be passed to the callback when it is called.
     * Otherwise, the exception object will be passed to the callback instead.
     */
//    static bool AddMessageListener(MessageCallback that,
//                                   Handle<Value> data = Handle<Value>());

    /**
     * Remove all message listeners from the specified callback function.
     */
//    static void RemoveMessageListeners(MessageCallback that);

    /**
     * Tells V8 to capture current stack trace when uncaught exception occurs
     * and report it to the message listeners. The option is off by default.
     */
//    static void SetCaptureStackTraceForUncaughtExceptions(
//            bool capture,
//            int frame_limit = 10,
//            StackTrace::StackTraceOptions options = StackTrace::kOverview);

    /**
     * Sets V8 flags from a string.
     */
//    static void SetFlagsFromString(const char *str, int length);

    /**
     * Sets V8 flags from the command line.
     */
    static void SetFlagsFromCommandLine(int *argc,
                                        char **argv,
                                        bool remove_flags);

    /** Get the version string. */
    static const char *GetVersion();

    /**
     * Enables the host application to provide a mechanism for recording
     * statistics counters.
     */
//    static void SetCounterFunction(CounterLookupCallback);

    /**
     * Enables the host application to provide a mechanism for recording
     * histograms. The CreateHistogram function returns a
     * histogram which will later be passed to the AddHistogramSample
     * function.
     */
//    static void SetCreateHistogramFunction(CreateHistogramCallback);
//    static void SetAddHistogramSampleFunction(AddHistogramSampleCallback);

    /**
     * Enables the computation of a sliding window of states. The sliding
     * window information is recorded in statistics counters.
     */
//    static void EnableSlidingStateWindow();

    /** Callback function for reporting failed access checks.*/
//    static void SetFailedAccessCheckCallbackFunction(FailedAccessCheckCallback);

    /**
     * Enables the host application to receive a notification before a
     * garbage collection.  Allocations are not allowed in the
     * callback function, you therefore cannot manipulate objects (set
     * or delete properties for example) since it is possible such
     * operations will result in the allocation of objects. It is possible
     * to specify the GCType filter for your callback. But it is not possible to
     * register the same callback function two times with different
     * GCType filters.
     */
//    static void AddGCPrologueCallback(
//            GCPrologueCallback callback, GCType gc_type_filter = kGCTypeAll);

    /**
     * This function removes callback which was installed by
     * AddGCPrologueCallback function.
     */
//    static void RemoveGCPrologueCallback(GCPrologueCallback callback);

    /**
     * The function is deprecated. Please use AddGCPrologueCallback instead.
     * Enables the host application to receive a notification before a
     * garbage collection.  Allocations are not allowed in the
     * callback function, you therefore cannot manipulate objects (set
     * or delete properties for example) since it is possible such
     * operations will result in the allocation of objects.
     */
//    static void SetGlobalGCPrologueCallback(GCCallback);

    /**
     * Enables the host application to receive a notification after a
     * garbage collection.  Allocations are not allowed in the
     * callback function, you therefore cannot manipulate objects (set
     * or delete properties for example) since it is possible such
     * operations will result in the allocation of objects. It is possible
     * to specify the GCType filter for your callback. But it is not possible to
     * register the same callback function two times with different
     * GCType filters.
     */
//    static void AddGCEpilogueCallback(
//            GCEpilogueCallback callback, GCType gc_type_filter = kGCTypeAll);

    /**
     * This function removes callback which was installed by
     * AddGCEpilogueCallback function.
     */
//    static void RemoveGCEpilogueCallback(GCEpilogueCallback callback);

    /**
     * The function is deprecated. Please use AddGCEpilogueCallback instead.
     * Enables the host application to receive a notification after a
     * major garbage collection.  Allocations are not allowed in the
     * callback function, you therefore cannot manipulate objects (set
     * or delete properties for example) since it is possible such
     * operations will result in the allocation of objects.
     */
//    static void SetGlobalGCEpilogueCallback(GCCallback);

    /**
     * Enables the host application to provide a mechanism to be notified
     * and perform custom logging when V8 Allocates Executable Memory.
     */
//    static void AddMemoryAllocationCallback(MemoryAllocationCallback callback,
//                                            ObjectSpace space,
//                                            AllocationAction action);

    /**
     * Removes callback that was installed by AddMemoryAllocationCallback.
     */
//    static void RemoveMemoryAllocationCallback(MemoryAllocationCallback callback);

    /**
     * Adds a callback to notify the host application when a script finished
     * running.  If a script re-enters the runtime during executing, the
     * CallCompletedCallback is only invoked when the outer-most script
     * execution ends.  Executing scripts inside the callback do not trigger
     * further callbacks.
     */
//    static void AddCallCompletedCallback(CallCompletedCallback callback);

    /**
     * Removes callback that was installed by AddCallCompletedCallback.
     */
//    static void RemoveCallCompletedCallback(CallCompletedCallback callback);

    /**
     * Allows the host application to group objects together. If one
     * object in the group is alive, all objects in the group are alive.
     * After each garbage collection, object groups are removed. It is
     * intended to be used in the before-garbage-collection callback
     * function, for instance to simulate DOM tree connections among JS
     * wrapper objects.
     * See v8-profiler.h for RetainedObjectInfo interface description.
     */
//    static void AddObjectGroup(Persistent<Value> *objects,
//                               size_t length,
//                               RetainedObjectInfo *info = NULL);

    /**
     * Allows the host application to declare implicit references between
     * the objects: if |parent| is alive, all |children| are alive too.
     * After each garbage collection, all implicit references
     * are removed.  It is intended to be used in the before-garbage-collection
     * callback function.
     */
//    static void AddImplicitReferences(Persistent<Object> parent,
//                                      Persistent<Value> *children,
//                                      size_t length);

    /**
     * Initializes from snapshot if possible. Otherwise, attempts to
     * initialize from scratch.  This function is called implicitly if
     * you use the API without calling it first.
     */
    static bool Initialize();

    /**
     * Allows the host application to provide a callback which can be used
     * as a source of entropy for random number generators.
     */
//    static void SetEntropySource(EntropySource source);

    /**
     * Allows the host application to provide a callback that allows v8 to
     * cooperate with a profiler that rewrites return addresses on stack.
     */
//    static void SetReturnAddressLocationResolver(
//            ReturnAddressLocationResolver return_address_resolver);

    /**
     * Allows the host application to provide the address of a function that's
     * invoked on entry to every V8-generated function.
     * Note that \p entry_hook is invoked at the very start of each
     * generated function.
     *
     * \param entry_hook a function that will be invoked on entry to every
     *   V8-generated function.
     * \returns true on success on supported platforms, false on failure.
     * \note Setting a new entry hook function when one is already active will
     *   fail.
     */
//    static bool SetFunctionEntryHook(FunctionEntryHook entry_hook);

    /**
     * Allows the host application to provide the address of a function that is
     * notified each time code is added, moved or removed.
     *
     * \param options options for the JIT code event handler.
     * \param event_handler the JIT code event handler, which will be invoked
     *     each time code is added, moved or removed.
     * \note \p event_handler won't get notified of existent code.
     * \note since code removal notifications are not currently issued, the
     *     \p event_handler may get notifications of code that overlaps earlier
     *     code notifications. This happens when code areas are reused, and the
     *     earlier overlapping code areas should therefore be discarded.
     * \note the events passed to \p event_handler and the strings they point to
     *     are not guaranteed to live past each call. The \p event_handler must
     *     copy strings and other parameters it needs to keep around.
     * \note the set of events declared in JitCodeEvent::EventType is expected to
     *     grow over time, and the JitCodeEvent structure is expected to accrue
     *     new members. The \p event_handler function must ignore event codes
     *     it does not recognize to maintain future compatibility.
     */
//    static void SetJitCodeEventHandler(JitCodeEventOptions options,
//                                       JitCodeEventHandler event_handler);

    /**
     * Adjusts the amount of registered external memory.  Used to give
     * V8 an indication of the amount of externally allocated memory
     * that is kept alive by JavaScript objects.  V8 uses this to decide
     * when to perform global garbage collections.  Registering
     * externally allocated memory will trigger global garbage
     * collections more often than otherwise in an attempt to garbage
     * collect the JavaScript objects keeping the externally allocated
     * memory alive.
     *
     * \param change_in_bytes the change in externally allocated memory
     *   that is kept alive by JavaScript objects.
     * \returns the adjusted value.
     */
//    static intptr_t AdjustAmountOfExternalAllocatedMemory(
//            intptr_t change_in_bytes);

    /**
     * Suspends recording of tick samples in the profiler.
     * When the V8 profiling mode is enabled (usually via command line
     * switches) this function suspends recording of tick samples.
     * Profiling ticks are discarded until ResumeProfiler() is called.
     *
     * See also the --prof and --prof_auto command line switches to
     * enable V8 profiling.
     */
//    static void PauseProfiler();

    /**
     * Resumes recording of tick samples in the profiler.
     * See also PauseProfiler().
     */
//    static void ResumeProfiler();

    /**
     * Return whether profiler is currently paused.
     */
//    static bool IsProfilerPaused();

    /**
     * Retrieve the V8 thread id of the calling thread.
     *
     * The thread id for a thread should only be retrieved after the V8
     * lock has been acquired with a Locker object with that thread.
     */
//    static int GetCurrentThreadId();

    /**
     * Forcefully terminate execution of a JavaScript thread.  This can
     * be used to terminate long-running scripts.
     *
     * TerminateExecution should only be called when then V8 lock has
     * been acquired with a Locker object.  Therefore, in order to be
     * able to terminate long-running threads, preemption must be
     * enabled to allow the user of TerminateExecution to acquire the
     * lock.
     *
     * The termination is achieved by throwing an exception that is
     * uncatchable by JavaScript exception handlers.  Termination
     * exceptions act as if they were caught by a C++ TryCatch exception
     * handler.  If forceful termination is used, any C++ TryCatch
     * exception handler that catches an exception should check if that
     * exception is a termination exception and immediately return if
     * that is the case.  Returning immediately in that case will
     * continue the propagation of the termination exception if needed.
     *
     * The thread id passed to TerminateExecution must have been
     * obtained by calling GetCurrentThreadId on the thread in question.
     *
     * \param thread_id The thread id of the thread to terminate.
     */
//    static void TerminateExecution(int thread_id);

    /**
     * Forcefully terminate the current thread of JavaScript execution
     * in the given isolate. If no isolate is provided, the default
     * isolate is used.
     *
     * This method can be used by any thread even if that thread has not
     * acquired the V8 lock with a Locker object.
     *
     * \param isolate The isolate in which to terminate the current JS execution.
     */
//    static void TerminateExecution(Isolate *isolate = NULL);

    /**
     * Is V8 terminating JavaScript execution.
     *
     * Returns true if JavaScript execution is currently terminating
     * because of a call to TerminateExecution.  In that case there are
     * still JavaScript frames on the stack and the termination
     * exception is still active.
     *
     * \param isolate The isolate in which to check.
     */
//    static bool IsExecutionTerminating(Isolate *isolate = NULL);

    /**
     * Releases any resources used by v8 and stops any utility threads
     * that may be running.  Note that disposing v8 is permanent, it
     * cannot be reinitialized.
     *
     * It should generally not be necessary to dispose v8 before exiting
     * a process, this should happen automatically.  It is only necessary
     * to use if the process needs the resources taken up by v8.
     */
    static bool Dispose();

    /**
     * Get statistics about the heap memory usage.
     */
//    static void GetHeapStatistics(HeapStatistics *heap_statistics);

    /**
     * Iterates through all external resources referenced from current isolate
     * heap. This method is not expected to be used except for debugging purposes
     * and may be quite slow.
     */
//    static void VisitExternalResources(ExternalResourceVisitor *visitor);

    /**
     * Iterates through all the persistent handles in the current isolate's heap
     * that have class_ids.
     */
//    static void VisitHandlesWithClassIds(PersistentHandleVisitor *visitor);

    /**
     * Optional notification that the embedder is idle.
     * V8 uses the notification to reduce memory footprint.
     * This call can be used repeatedly if the embedder remains idle.
     * Returns true if the embedder should stop calling IdleNotification
     * until real work has been done.  This indicates that V8 has done
     * as much cleanup as it will be able to do.
     *
     * The hint argument specifies the amount of work to be done in the function
     * on scale from 1 to 1000. There is no guarantee that the actual work will
     * match the hint.
     */
//    static bool IdleNotification(int hint = 1000);

    /**
     * Optional notification that the system is running low on memory.
     * V8 uses these notifications to attempt to free memory.
     */
//    static void LowMemoryNotification();

    /**
     * Optional notification that a context has been disposed. V8 uses
     * these notifications to guide the GC heuristic. Returns the number
     * of context disposals - including this one - since the last time
     * V8 had a chance to clean up.
     */
//    static int ContextDisposedNotification();

private:
    static internal::Object *GlobalizeReference(internal::Object *handle);

    static void DisposeGlobal(internal::Object *global_handle);

    static void MakeWeak(internal::Object *global_handle,
                         void *data,
                         WeakReferenceCallback callback);

    template<class T> friend class Persistent;
};

}

#endif //DUKV8_V8_H
