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
    require("./all.rb");
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