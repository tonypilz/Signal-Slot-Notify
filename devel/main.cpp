#include <iostream>

#include <testing/TestMain.h>

#include <CompilerExplorerRunMethod.h>


//todo: disable c++2011 in qtcreator project settings


int main()
{
    run(5);
    sisl::test::TestMain{};
    return 0;
}
