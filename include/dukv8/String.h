//
// Created by Jiang Lu on 6/2/15.
//

#ifndef DUKV8_STRING_H
#define DUKV8_STRING_H

#include <dukv8/Primitive.h>

namespace v8 {

class String : public Primitive, public HeapObject {
public:
    RTTI_DECLARE();

    static inline String *Cast(v8::Value *obj);

    /**
     * Allocates a new string from either UTF-8 encoded or ASCII data.
     * The second parameter 'length' gives the buffer length.
     * If the data is UTF-8 encoded, the caller must
     * be careful to supply the length parameter.
     * If it is not given, the function calls
     * 'strlen' to determine the buffer length, it might be
     * wrong if 'data' contains a null character.
     */
    V8EXPORT static Local<String> New(const char *data, int length = -1);

    /** Allocates a new string from 16-bit character codes.*/
    V8EXPORT static Local<String> New(const uint16_t *data, int length = -1);

    /** Creates a symbol. Returns one if it exists already.*/
    V8EXPORT static Local<String> NewSymbol(const char *data, int length = -1);

    /**
     * Creates a new string by concatenating the left and the right strings
     * passed in as parameters.
     */
    V8EXPORT static Local<String> Concat(Handle<String> left,
                                         Handle<String> right);
    /**
     * Converts an object to a UTF-8-encoded character array.  Useful if
     * you want to print the object.  If conversion to a string fails
     * (e.g. due to an exception in the toString() method of the object)
     * then the length() method returns 0 and the * operator returns
     * NULL.
     */
    class V8EXPORT Utf8Value {
    public:
        explicit Utf8Value(Handle<v8::Value> obj);
        ~Utf8Value();
        char *operator*() { return str_; }
        const char *operator*() const { return str_; }
        int length() const { return length_; }
    private:
        char *str_;
        int length_;

        // Disallow copying and assigning.
        Utf8Value(const Utf8Value &);
        void operator=(const Utf8Value &);
    };

    INTERNAL virtual void Push() const;

protected:
    String(duk_context *duk_ctx, const char *data, int length);
    String(duk_context *duk_ctx, void *heap_ptr);
    virtual ~String();

private:
    V8EXPORT static void CheckCast(v8::Value *obj);

    friend class Value;
};

String *String::Cast(v8::Value *value) {
    return static_cast<String *>(value);
}


}


#endif //DUKV8_STRING_H
