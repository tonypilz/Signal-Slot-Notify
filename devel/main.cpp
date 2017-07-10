#include <iostream>

#include <testing/TestMain.h>

#include <CompilerExplorerRunMethod.h>

#include <CodeExampleMain.h>


//todo: disable c++2011 in qtcreator project settings


int main()
{
    main_();
    run(5);
    sisl::test::TestMain{};
    return 0;
}
