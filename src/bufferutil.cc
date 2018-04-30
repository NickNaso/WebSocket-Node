/*!
 * BufferUtil originally from:
 * ws: a node.js websocket client
 * Copyright(c) 2015 Einar Otto Stangvik <einaros@gmail.com>
 * MIT Licensed
 */

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdio.h>
#include "bufferutil.h"

Napi::FunctionReference BufferUtil::constructor;

Napi::Object BufferUtil::Initialize(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  Napi::Function func = DefineClass(env, "BufferUtil", {
    InstanceMethod("unmask", &BufferUtil::Unmask),
    InstanceMethod("mask", &BufferUtil::Mask),
    InstanceMethod("merge", &BufferUtil::Merge)
  });
  exports.Set("BufferUtil", func);
  return exports;
}

BufferUtil::BufferUtil(const Napi::CallbackInfo& info) 
  : Napi::ObjectWrap<BufferUtil>(info) {
    // NOOP
}

Napi::Value BufferUtil::Mask(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Buffer<int> buffer_obj = info[0].As<Napi::Buffer<int>>();
  Napi::Buffer<int> mask_obj = info[1].As<Napi::Buffer<int>>();
  unsigned int *mask = (unsigned int*) mask_obj.Data();
  Napi::Buffer<int> output_obj = info[2].As<Napi::Buffer<int>>();
  unsigned int dataOffset = info[3].As<Napi::Number>().Uint32Value();
  unsigned int length = info[4].As<Napi::Number>().Uint32Value();
  unsigned int* to = (unsigned int*)(output_obj.Data() + dataOffset);
  unsigned int* from = (unsigned int*)buffer_obj.Data();
  unsigned int len32 = length / 4;
  unsigned int i;
    for (i = 0; i < len32; ++i) *(to + i) = *(from + i) ^ *mask;
    to += i;
    from += i;
    switch (length % 4) {
      case 3: *((unsigned char*)to+2) = *((unsigned char*)from+2) ^ *((unsigned char*)mask+2);
      case 2: *((unsigned char*)to+1) = *((unsigned char*)from+1) ^ *((unsigned char*)mask+1);
      case 1: *((unsigned char*)to  ) = *((unsigned char*)from  ) ^ *((unsigned char*)mask);
      case 0:;
    }
    return Napi::Boolean::New(env, true);
}

Napi::Value BufferUtil::Unmask(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Buffer<int> buffer_obj = info[0].As<Napi::Buffer<int>>();
  size_t length = buffer_obj.Length();
  Napi::Buffer<int> mask_obj = info[1].As<Napi::Buffer<int>>();
  unsigned int *mask = (unsigned int*)mask_obj.Data();
  unsigned int* from = (unsigned int*)buffer_obj.Data();
  size_t len32 = length / 4;
  unsigned int i;
  for (i = 0; i < len32; ++i) *(from + i) ^= *mask;
    from += i;
    switch (length % 4) {
      case 3: *((unsigned char*)from+2) = *((unsigned char*)from+2) ^ ((unsigned char*)mask)[2];
      case 2: *((unsigned char*)from+1) = *((unsigned char*)from+1) ^ ((unsigned char*)mask)[1];
      case 1: *((unsigned char*)from  ) = *((unsigned char*)from  ) ^ ((unsigned char*)mask)[0];
      case 0:;
  }
  return Napi::Boolean::New(env, true);
}

Napi::Value BufferUtil::Merge(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Buffer<char> bufferObj = info[0].As<Napi::Buffer<char>>();
  char* buffer = bufferObj.Data();
  Napi::Array array = info[1].As<Napi::Array>();
  unsigned int arrayLength = array.Length();
  size_t offset = 0;
  unsigned int i;
  for (i = 0; i < arrayLength; ++i) {
    Napi::Buffer<char>* src = new Napi::Buffer<char>(env, array.Get(i));
    size_t length = src->Length();
    memcpy(buffer + offset, src->Data(), length);
    offset += length;
  }
  return Napi::Boolean::New(env, true);
}

Napi::Object init(Napi::Env env, Napi::Object exports) {
  BufferUtil::Initialize(env, exports);
  return exports;
}

NODE_API_MODULE(bufferutil, init)
