/*!
 * BufferUtil originally from:
 * ws: a node.js websocket client
 * Copyright(c) 2015 Einar Otto Stangvik <einaros@gmail.com>
 * MIT Licensed
 */

#include <napi.h>

class BufferUtil : public Napi::ObjectWrap<BufferUtil> {
    public: 
        static Napi::Object Initialize(Napi::Env env, Napi::Object exports);
        BufferUtil(const Napi::CallbackInfo& info);

    private:
        static Napi::FunctionReference constructor;
        Napi::Value Unmask(const Napi::CallbackInfo& info);
        Napi::Value Mask(const Napi::CallbackInfo& info);
        Napi::Value Merge(const Napi::CallbackInfo& info);
};