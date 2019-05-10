#include <napi.h>
#include "SmartcardClass.h"

class Smartcard : public Napi::ObjectWrap<Smartcard> {
    public:
        static Napi::Object Init(Napi::Env, Napi::Object exports);
        Smartcard(const Napi::CallbackInfo& info);
        SmartcardClass* GetInternalInstance();
    
    private:
        static Napi::FunctionReference constructor;
        Napi::Value read(const Napi::CallbackInfo& info);
        Napi::Value write(const Napi::CallbackInfo& info);
        Napi::Value reset(const Napi::CallbackInfo& info);
        SmartcardClass* candy;

};