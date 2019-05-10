#include "SmartcardWrap.h"
#include <iostream>

Napi::FunctionReference Smartcard::constructor;

Napi::Object Smartcard::Init(Napi::Env env, Napi::Object exports) {
    Napi::HandleScope scope(env);

    Napi::Function func = DefineClass(env, "Smartcard", {
            InstanceMethod("write", &Smartcard::write),
            InstanceMethod("read", &Smartcard::read),
            InstanceMethod("reset", &Smartcard::reset)
        });
    
    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("Smartcard", func);
    return exports;
}

Smartcard::Smartcard(const Napi::CallbackInfo& info) : Napi::ObjectWrap<Smartcard>(info){
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();

    if (length != 0) {
        Napi::TypeError::New(env, "No arguments were expected").ThrowAsJavaScriptException();
    }

    this->candy = new SmartcardClass();
}

Napi::Value Smartcard::write(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int length = info.Length();

    if (length != 2) {
        Napi::TypeError::New(env, "Oi. I expected two arguments of type ArrayBuffer and Number.").ThrowAsJavaScriptException();
    }

    if (!info[0].IsTypedArray()) {
        Napi::TypeError::New(env, "ArrayBuffer not given as argument 1.").ThrowAsJavaScriptException();
    }

    if (!info[1].IsNumber()) {
        Napi::TypeError::New(env, "Number not given as argument 2.").ThrowAsJavaScriptException();
    }

    Napi::Uint8Array data = info[0].As<Napi::Uint8Array>();

    Napi::Number dataSize = info[1].As<Napi::Number>();
    
    bool success = this->candy->write(data.Data(), (ULONG)dataSize.Uint32Value());

    return Napi::Boolean::New(env, success);
}

Napi::Value Smartcard::read(const Napi::CallbackInfo& info) {
    return Napi::ArrayBuffer::New(
        info.Env(),
        this->candy->read(),
        1024*64,
        [](Napi::Env, void* finalizeData) {
            delete[] (BYTE*)finalizeData;
        }
    );
}

Napi::Value Smartcard::reset(const Napi::CallbackInfo& info) {
    return Napi::Boolean::New(
        info.Env(),
        this->candy->reset()
    );
}

SmartcardClass* Smartcard::GetInternalInstance() {
    return this->candy;
}
