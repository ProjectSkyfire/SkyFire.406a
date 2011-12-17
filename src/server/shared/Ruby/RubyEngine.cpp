#include "RubyEngine.h"

void RubyEngine::Initialize()
{
    if(running)
        return;

    RUBY_INIT_STACK;
#ifdef _WIN32
    int argc = 0;
    char** argv = NULL;
    NtInitialize(&argc, &argv);
#endif
    ruby_init();
    int status = 0;
    rb_protect(rb_require, rb_str_new2("./all.rb"), &status);
    if(status)
    {
        sLog->outString("Could not load Ruby file 'all.rb' please make sure it exists");
        return;
    }
    running = true;
    call_function<void>(Qnil, "test1");
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