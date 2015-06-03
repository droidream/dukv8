//
// Created by Jiang Lu on 6/2/15.
//

#include <dukv8/HandleScope.h>
#include <dukv8/ObjectList.h>
#include <dukv8/Value.h>
#include <dukv8/String.h>
#include <dukv8/Object.h>
#include <dukv8/Isolate.h>
#include <dukv8/GCObject.h>

namespace v8 {

HandleScope *HandleScope::s_current_scope_ = NULL;

HandleScope::HandleScope() :
        previous_scope_(s_current_scope_),
        pool_(new i::GCObjectPool()) {
    s_current_scope_ = this;
//    printf("%s\n", __PRETTY_FUNCTION__);
}

HandleScope::~HandleScope() {

    // 合适的时机清除自动释放池
    Isolate *isolate = Isolate::GetCurrent();
    isolate->GetAutoReleasePool()->Release();

    s_current_scope_ = previous_scope_;
    delete pool_;
//    printf("%s\n", __PRETTY_FUNCTION__);
}

/**
 * Creates a new handle with the given value.
 */
internal::Object *HandleScope::CreateHandle(internal::Object *value) {

    i::GCObject *gcobject = RTTI_DynamicCast(
            i::GCObject, reinterpret_cast<i::GCObject *>(value));
    if (gcobject) {
        gcobject->AddToObjectPool(s_current_scope_->pool_);
    }

    // String *string = RTTI_DynamicCast(String, reinterpret_cast<Data *>(value));
    // if (string) {
    //     string->AddToObjectPool(s_current_scope_->pool_);
    //     // s_current_scope_->pool_->AddObject(string->GetHeapPtr());
    //     return value;
    // }
    //
    // Object *object = RTTI_DynamicCast(Object, reinterpret_cast<Object *>(value));
    // if (object) {
    //     object->AddToObjectPool(s_current_scope_->pool_);
    //     // s_current_scope_->pool_->AddObject(object->GetHeapPtr());
    //     return value;
    // }
    //
    // printf("UNKNOW Object !!\n");

    return value;
}

}