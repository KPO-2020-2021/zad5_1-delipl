#define DOCTEST_CONFIG_NO_UNPREFIXED_OPTIONS
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"
#include "config.hpp"
bool DISPLAY = false; 

class dt_removed {
    std::vector<const char*> vec;
public:
    dt_removed(const char** argv_in) {
        for(; *argv_in; ++argv_in)
            if(strncmp(*argv_in, "--dt-", strlen("--dt-")) != 0)
                vec.push_back(*argv_in);
        vec.push_back(NULL);
    }

    int          argc() { return static_cast<int>(vec.size()) - 1; }
    const char** argv() { return &vec[0]; } // Note: non-const char **:
};

int program(int argc, const char** argv);

int main(int argc, const char** argv) {
    doctest::Context context(argc, argv);

    dt_removed args(argv);
    int app_result = program(args.argc(), args.argv());

    int test_result = context.run(); // run queries, or run tests unless --no-run
     if(context.shouldExit()) // honor query flags and --exit
        return test_result;
    return test_result + app_result; // combine the 2 results
}

int program(int argc, const char** argv) {
    printf("Program: %d arguments received:\n", argc - 1);
    while(*++argv){
        printf("'%s'\n", *argv);
        if(strcmp(*argv, "-x") == 0){
            printf("Ustawiam na prawidę!\n");
            DISPLAY = true;
        }
            
    }
        
    return EXIT_SUCCESS;
}