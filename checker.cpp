#include "testlib.h"
#include <iostream>
#include <string>

using namespace std;

const int MOD = 998244353;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // Read input data (if needed for complex checking)
    // Usually, testlib provides input, answer, and output files.

    // Read jury answer and contestant output (answers for q queries)
    int n = inf.readInt();
    inf.readEoln();
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = inf.readInt();
    }
    int q = inf.readInt();
    inf.readEoln();

    for (int i = 0; i < q; i++) {
        long long juryAns = ouf.readLong();
        long long userAns = ans.readLong();

        if (juryAns != userAns) {
            // cout << "Answer mismatch at query " << i + 1 << ": jury = " << juryAns << ", found = " << userAns << endl;
            quitf(_wa, "Answer mismatch at query %d: jury = %lld, found = %lld", i + 1, juryAns, userAns);
            // return 0;
        }
    }

    quitf(_ok, "All answers match!");
}
