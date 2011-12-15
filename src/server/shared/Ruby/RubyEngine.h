#ifndef RUBY_ENGINE_H
#define RUBY_ENGINE_H

#include "ruby.h"

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
    friend class ACE_Singleton<RubyEngine, ACE_Thread_Mutex>;
public:
    RubyEngine();
    ~RubyEngine();
    void Initialize();
    void Finalize();
    template<typename T>
    VALUE Wrap(T& t) { return VALUE(to_ruby(t)); }
    
    template<typename Ret>
    Ret call_function(VALUE self, std::string name)
    {
        VALUE res = rb_funcall(self, rb_intern(name.c_str()), 0);
        if(!is_void<Ret>::value)
            return from_ruby<Ret>(res);
    }

    template<typename Ret, typename Arg1>
    Ret call_function(VALUE self, std::string name, Arg1& a1)
    {
        VALUE res = rb_funcall(self, rb_intern(name.c_str()), 1, Wrap(a1));
        if(!is_void<Ret>::value)
            return from_ruby<Ret>(res);
    }
   
    // , typename Arg2, typename Arg3, typename Arg4, typename Arg5, typename Arg6, typename Arg7, typename Arg8, typename Arg9, typename Arg10>
    // , Arg2& a2, Arg3& a3 = Arg3(NULL), Arg4& a4 = Arg4(NULL), Arg5& a5 = Arg5(NULL), Arg6& a6 = Arg6(NULL), Arg7& a7 = Arg7(NULL), Arg8& a8 = Arg8(NULL), Arg9& a9 = Arg9(NULL), Arg10& a10 = Arg10(NULL))
private:
    bool running;
};

#define sRubyEngine ACE_Singleton<RubyEngine, ACE_Thread_Mutex>::instance()
#endif