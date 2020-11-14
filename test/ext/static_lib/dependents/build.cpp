#include "cxx_exec/ext/static_lib"
#include "cxx_exec/environment.hpp"
#include "cxx_exec/ext/static_lib_accessor.hpp"
#include "cxx_exec/cxx_exec.hpp"

string_view name() { return "main"; }
vector<path> sources() { return { "main.cpp" }; }

using namespace environment;

on_startup configure() {
    before_build = ([&](gcc_like_driver::command_builder& cc) {

        change_dir("dependency", [&]() {
            
            execute(
                cxx_exec::command_builder{"build.cpp"}.output("dep").compile_only(true)
            );

            static_lib_accessor {
                load_shared_library("dep")
            }.build();
        });

    });
}