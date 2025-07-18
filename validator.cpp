#include "testlib.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(1, 100000, "a_i");
        if (i < n-1) inf.readSpace();
        else inf.readEoln();
    }

    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    for (int i = 0; i < q; i++) {
        int l = inf.readInt(1, n, "l");
        inf.readSpace();
        int r = inf.readInt(1, n, "r");
        inf.readSpace();
        int x = inf.readInt(1, 100000, "x");
        inf.readEoln();

        ensure(l <= r);  // l must be <= r
    }

    inf.readEof();
    return 0;
}
