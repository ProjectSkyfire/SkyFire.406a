#ifndef RUBY_ENGINE_H
#define RUBY_ENGINE_H

#include <ace/Singleton.h>
#include "ruby.h"
#include "Common.h"
#include "rice/Class.hpp"
#include "rice/global_function.hpp"
#include "Object.h"
#include "ByteBuffer.h"
#include "rice/Enum.hpp"
#include "rice/Director.hpp"
#include "ScriptMgr.h"
#include "rice/Data_Type.hpp"
#include "rice/Constructor.hpp"

template<typename T>
struct is_void
{
    static const bool value = false;
};

template<>
struct is_void<void>
{
    static const bool value = true;
};

template<typename T>
struct is_value
{
    static const bool value = false;
};

template<>
struct is_value<VALUE>
{
    static const bool value = true;
};

class ServerScriptDirector : public ServerScript, public Rice::Director 
{
public:
    ServerScriptDirector(Rice::Object self, std::string name) : ServerScript(name.c_str()), Director(self)
    { 
        sLog->outString("Initialized ServerScriptDirector with name %s", name.c_str());
    }
    
    void default_OnNetworkStart()
    {
        ServerScript::OnNetworkStart();
    }
    
    virtual void OnNetworkStart()
    {
        getSelf().call("OnNetworkStart");
    }
    
    void default_OnNetworkStop()
    {
        ServerScript::OnNetworkStop();
    }
    
    virtual void OnNetworkStop()
    {
        getSelf().call("OnNetworkStop");
    }
};

class RubyEngine
{
public:
    RubyEngine();
    ~RubyEngine();
    void Initialize();
    void Finalize();
    template<typename T>
    VALUE Wrap(T& t) { return VALUE(to_ruby(t)); }
    void SetupRuby();
    
    static VALUE method_missing(VALUE method, VALUE args = Qnil, VALUE block = Qnil)
    {
        sLog->outString("Tried to call unexistant ruby kernel method %s", from_ruby<std::string>(method));
    }
    
    static void AddSC(std::string name)
    {
        script_adders.push_back(name);
    }
    
    void PrintError(int error)
    {
        if(!error)
            return;
        rb_eval_string_protect("if (e = $!) then STDERR.puts(\"#{e.class}:"
        "#{e.message}\", e.backtrace.map {|s| \"\tfrom #{s}\" }) end", &error);
    }
    
    // Must be static because of the hidden 'this' pointer
    static VALUE protected_call0(VALUE data) // Deepest level of abstraction (lol?)
    {
        VALUE* real_data = (VALUE*)(data);
        VALUE self = real_data[0];
        int argc = (int)(real_data[1]);
        ID mid = (ID)(real_data[2]);
        
        VALUE* argv = (VALUE*)(real_data[3]);
        
        return rb_funcall2(self, mid, argc, argv);
    }
    
    static VALUE require_prot(VALUE str)
    {
        rb_require((const char*)str);
        return Qnil;
    }
    
    bool require(const char* str)
    {
        int status;
        rb_protect(require_prot, (VALUE)str, &status);
        PrintError(status);
        if(status)
            return false;
        
        return true;
    }
    
    VALUE protected_call_function(VALUE self, ID mid, int num, ...)
    {
        // ToDo: Implement rb_protect here
        VALUE* argv;
        va_list ap;
        
        va_start(ap, num);
        int i;
        
        for(i = 0; i < num; ++i)
            argv[i] = va_arg(ap, VALUE);
        
        va_end(ap);
        
        // Use a little hack here
        VALUE* data;
        data[0] = self;
        data[1] = (VALUE)(num);
        data[2] = (VALUE)(mid);
        data[3] = (VALUE)(argv);
        
        int status;
        VALUE res = rb_protect(protected_call0, (VALUE)(data), &status);
        if(status)
        {
            sLog->outString("Caught an unhandled Ruby exception! \n");
            PrintError(status);
            return Qnil;
        }
        return res; 
    }
    
    template<typename Ret>
    Ret call_function(VALUE self, std::string name)
    {
        VALUE res = protected_call_function(self, rb_intern(name.c_str()), 0);
        if(!is_value<Ret>::value)
            return from_ruby<Ret>(res);
        else
            return res;
    }

    template<typename Ret, typename Arg1>
    Ret call_function(VALUE self, std::string name, Arg1& a1)
    {
        VALUE res = protected_call_function(self, rb_intern(name.c_str()), 1, Wrap(a1));
        if(!is_value<Ret>::value)
            return from_ruby<Ret>(res);
        else
            return res;
    }
   
    // , typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
    // , Arg2& a2, Arg3& a3 = Arg3(NULL), Arg4& a4 = Arg4(NULL), Arg5& a5 = Arg5(NULL), Arg6& a6 = Arg6(NULL), Arg7& a7 = Arg7(NULL), Arg8& a8 = Arg8(NULL), Arg9& a9 = Arg9(NULL), Arg10& a10 = Arg10(NULL))
private:
    bool running;
    friend class ACE_Singleton<RubyEngine, ACE_Thread_Mutex>;
};

#define sRubyEngine ACE_Singleton<RubyEngine, ACE_Thread_Mutex>::instance()

std::list<std::string> script_adders;
void CallRubyAddSC();
#endif