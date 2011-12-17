#include "RubyEngine.h"

void RubyEngine::Initialize()
{
    if(running)
        return;

    RUBY_INIT_STACK;
#ifdef _WIN32
    int argc = 1;
    char** argv = { NULL };
    NtInitialize(&argc, &argv);
#endif
    ruby_init();
    if(!require("./all.rb"))
    {
        sLog->outString("Error occurred when loading all.rb, please make sure that the file exists");
        return;
    }
    running = true;
    rb_define_method(rb_mKernel, "method_missing", method_missing, -1); /// Define this here so we avoid crashes
    call_function<void>(Qnil, "test1");
    sLog->outString("Ruby engine initialized correctly");
}

void RubyEngine::Finalize()
{
    ruby_finalize();
    running = false;
}

RubyEngine::RubyEngine()
{
    running = false;
    //Initialize();
}

RubyEngine::~RubyEngine()
{
    if(running)
        Finalize();
}