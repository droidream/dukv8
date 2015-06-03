//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_HANDLESCOPE_H
#define DUKV8_HANDLESCOPE_H

#include "Base.h"
#include "GCObject.h"
#include "GCObjectPool.h"

namespace v8 {

/**
* A stack-allocated class that governs a number of local handles.
* After a handle scope has been created, all local handles will be
* allocated within that handle scope until either the handle scope is
* deleted or another handle scope is created.  If there is already a
* handle scope and a new one is created, all allocations will take
* place in the new handle scope until it is deleted.  After that,
* new handles will again be allocated in the original handle scope.
*
* After the handle scope of a local handle has been deleted the
* garbage collector will no longer track the object stored in the
* handle and may deallocate it.  The behavior of accessing a handle
* for which the handle scope has been deleted is undefined.
*/

/**
 * 句柄作用域
 *
 * dukv8 中, Handle 句柄使用基于引用计数的智能指针来表达
 * 在如下示例中, 句柄作用域 handle_scope 和字符串本地句柄 value 的生命周期不一致
 * 但是 value 句柄所持有的 Duktape 对象生命周期和 handle_scope 一致
 *
 * {
 *     HandleScope handle_scope;
 *     {
 *         Local<String> value = String::New("Jiang Lu");
 *     }
 * }
 *
 */
class V8EXPORT HandleScope {
public:
    HandleScope();

    ~HandleScope();

    /**
     * Creates a new handle with the given value.
     */
    static internal::Object *CreateHandle(internal::Object *value);

private:
    static HandleScope *s_current_scope_;
    HandleScope *previous_scope_;
    i::GCObjectPool *pool_;
};

}

#endif //DUKV8_HANDLESCOPE_H
