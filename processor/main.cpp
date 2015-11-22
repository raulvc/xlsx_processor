#include <iostream>
#include "Manager.h"

using namespace std;

int main(int argc, char * argv[]) {
    Manager manager(argc, argv);
    manager.start();
    return 0;
}