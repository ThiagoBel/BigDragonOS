#include <iostream>
#include "lib/bdLIB.h"
using namespace std;

int main()
{
    bd::send_notification("test: hello!");
    bd::pause();
    return 0;
}