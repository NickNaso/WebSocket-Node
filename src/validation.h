/*!
 * BufferUtil originally from:
 * ws: a node.js websocket client
 * Copyright(c) 2015 Einar Otto Stangvik <einaros@gmail.com>
 * MIT Licensed
 */

#include <napi.h>

class Validation : public Napi::ObjectWrap<Validation> {
    public:
        static Napi::Object Initialize(Napi::Env env, Napi::Object exports);
        Validation(const Napi::CallbackInfo& info);

    private:
        static Napi::FunctionReference constructor;
        Napi::Value IsValidUTF8(const Napi::CallbackInfo& info);    
};