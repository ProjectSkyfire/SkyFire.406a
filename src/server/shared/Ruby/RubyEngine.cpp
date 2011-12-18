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
    define_global_function("method_missing", &method_missing, (Arg("method"), Arg("args") = Qnil, Arg("block") = Qnil)); /// Define this here so we avoid crashes, Comma operator YAY!
    call_function<VALUE>(Qnil, "test1");
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