#ifndef RUBY_ENGINE_H
#define RUBY_ENGINE_H

#include <ace/Singleton.h>
#include "ruby.h"
#include "Common.h"

template <typename T>
struct is_void
{
    static const bool value = false;
};

template <>
struct is_void<void>
{
    static const bool value = true;
};


template<typename T>
VALUE to_ruby(T& t)
{
    return INT2NUM(42);
}
    
template<typename T>
T from_ruby(VALUE val)
{
    return T(0);
}

class RubyEngine
{
public:
    RubyEngine();
    ~RubyEngine();
    void Initialize();
    void Finalize();
    template<typename T>
    VALUE Wrap(T& t) { return VALUE(to_ruby(t)); }
    
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
    
    void require(const char* str)
    {
        rb_require_safe(rb_str_new2(str), rb_safe_level());
    }
    
    VALUE protected_call_function(VALUE self, ID mid, ...)
    {
        // ToDo: Implement rb_protect here
        VALUE* argv;
        va_list ap;
        
        va_start(ap, mid);
        int i = 0;
        VALUE current = va_arg(ap, VALUE);
        
        while(current) {
            argv[i] = current;
            current = va_arg(ap, VALUE);
            ++i;
        }
        
        va_end(ap);
        
        // Use a little hack here
        VALUE* data;
        data[0] = self;
        data[1] = (VALUE)(i); // here, 'i' is the total length of the array, due to one extra increment made in the last iteration
        data[2] = (VALUE)(mid);
        data[3] = (VALUE)(argv);
        
        int status = 0;
        VALUE res = rb_protect(protected_call0, (VALUE)(data), &status);
        if(status)
        {
            sLog->outString("An error occurred when executing a Ruby statement");
            return Qnil;
        }
        return res; 
    }
    
    template<typename Ret>
    Ret call_function(VALUE self, std::string name)
    {
        VALUE res = protected_call_function(self, rb_intern(name.c_str()));
        if(!is_void<Ret>::value)
            return from_ruby<Ret>(res);
    }

    template<typename Ret, typename Arg1>
    Ret call_function(VALUE self, std::string name, Arg1& a1)
    {
        VALUE res = protected_call_function(self, rb_intern(name.c_str()), Wrap(a1));
        if(!is_void<Ret>::value)
            return from_ruby<Ret>(res);
    }
   
    // , typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
    // , Arg2& a2, Arg3& a3 = Arg3(NULL), Arg4& a4 = Arg4(NULL), Arg5& a5 = Arg5(NULL), Arg6& a6 = Arg6(NULL), Arg7& a7 = Arg7(NULL), Arg8& a8 = Arg8(NULL), Arg9& a9 = Arg9(NULL), Arg10& a10 = Arg10(NULL))
private:
    bool running;
    friend class ACE_Singleton<RubyEngine, ACE_Thread_Mutex>;
};

#define sRubyEngine ACE_Singleton<RubyEngine, ACE_Thread_Mutex>::instance()
#endif