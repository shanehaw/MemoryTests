#include "CreateMemoryDocUseCaseTests.h"
#include "MainWindowTests.h"

int main(int argc, char * argv[])
{
    int status = 0;

    {
        CreateMemoryDocUseCaseTests t1;
        status |= QTest::qExec(&t1, argc, argv);
    }

    {
        MainWindowTests t2;
        status |= QTest::qExec(&t2, argc, argv);
    }

    return status;
}
