#include <bits/stdc++.h>
#include <future>
using namespace std;
using namespace chrono; // Add this to fix milliseconds reference

// Global variable to signal thread interruption
atomic<bool> should_stop(false);

// Helper class to redirect stdin/stdout
class IORedirector
{
    stringstream input, output;
    streambuf *old_cin, *old_cout;

public:
    IORedirector(const string &in) : input(in)
    {
        old_cin = cin.rdbuf(input.rdbuf());
        old_cout = cout.rdbuf(output.rdbuf());
    }

    ~IORedirector()
    {
        cin.rdbuf(old_cin);
        cout.rdbuf(old_cout);
    }

    string get_output()
    {
        return output.str();
    }
};

const int mod = 998244353;
// Dummy brute force solution - replace with actual brute force logic
string solve_brute_force(const string &input_str)
{
    // Simulate reading from stdin and writing to stdout
    IORedirector redirector(input_str);

    // This is where you put the actual brute force implementation
    // It can use cin/cout as normal
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int q; cin >> q;
    while (q--)
    {
        int l, r, x;
        cin >> l >> r >> x;
        l--;
        r--;
        int count_multiple = 0;
        for (int i = l; i <= r; i++)
        {
            if (a[i] % x == 0)
            {
                count_multiple++;
            }
        }
        int others = r - l + 1 - count_multiple;
        long long power_two = 1;
        while (others > 0)
        {
            power_two *= 2;
            power_two %= mod;
            others--;
        }
        long long ans = power_two * (count_multiple + 1);
        ans %= mod;
        ans += mod - 1; // To handle the case subset is empty
        ans %= mod;
        cout << ans << '\n';
    }
    return redirector.get_output();
}

const int N = 1e5 + 5; 
int spf[N];

void sieve()
{
    for (int i = 2; i < N; i++)
    {
        if (spf[i] == 0)
        {
            for (int j = i; j < N; j += i)
            {
                if (spf[j] == 0)
                {
                    spf[j] = i;
                }
            }
        }
    }
}

vector<int> get_divisors(int x)
{
    vector<int> divisors;
    vector<pair<int, int>> prime_factors;
    while (x > 1)
    {
        int prime_factor = spf[x];
        int count = 0;
        while (x % prime_factor == 0)
        {
            x /= prime_factor;
            count++;    
        }
        prime_factors.push_back({prime_factor, count});
    }
    divisors.push_back(1); // 1 is a divisor of every number
    for(auto &[p, c] : prime_factors)
    {
        vector<int> current_divisors = divisors;
        for(int d:divisors)
        {
            int cur_num = d;
            for(int i = 1; i <= c; i++)
            {
                cur_num *= p;
                current_divisors.push_back(cur_num);
            }
        }
        divisors = current_divisors;
    }

    return divisors;
}

vector<int>multiple_of[N];

// Dummy optimal solution - replace with actual optimal logic
string solve_optimal(const string &input_str)
{
    // Simulate reading from stdin and writing to stdout
    IORedirector redirector(input_str);

    // This is where you put the actual optimal implementation
    // It can use cin/cout as normal
    
   

    //  cout << "hello\n";
    // return redirector.get_output();
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> power2(n + 1, 1);
    for (int i = 1; i <= n; i++)
    {
        power2[i] = (1LL * power2[i - 1] * 2) % mod;
    }
    // cerr<< "Hello" << endl;

    //  cout << "hello\n";
    // return redirector.get_output();

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        if(a[i] <= 0 || a[i] >= N) cerr << a[i] << endl;
        // assert(a[i] >= 1 && a[i] < N);
        auto divisors = get_divisors(a[i]);
        for (int d : divisors)
        {
            assert(d < N);
            multiple_of[d].push_back(i + 1); // Store 1-based index
        }
    }
    // cerr << "hello1" << endl;
    // return redirector.get_output();
    int q; cin >> q;
    while (q--)
    {
        int l, r, x;
        cin >> l >> r >> x;
        auto itr = upper_bound(multiple_of[x].begin(), multiple_of[x].end(), r);
        auto itr1 = lower_bound(multiple_of[x].begin(), multiple_of[x].end(), l);
        int count_multiple = itr - itr1;
        int others = r - l + 1 - count_multiple;
        long long power_two = power2[others];
        long long ans = power_two * (count_multiple + 1);
        ans %= mod;
        ans += mod - 1; // To handle the case subset is empty
        ans %= mod;
        cout << ans << '\n';
    }

    for(int i = 0; i < N; i++) 
        multiple_of[i].clear();

    return redirector.get_output();
}

// Function to find the next available test case number
int find_next_file_number()
{
    int next_num = 1;
    while (true)
    {
        string filename = "test_cases/" + to_string(next_num) + ".in";
        ifstream file(filename);
        if (!file.good())
        {
            return next_num;
        }
        next_num++;
    }
}

// Function to run a solution (either brute force or optimal) and write output
void run_solution(const string &input_file, const string &output_file, bool use_optimal, int test_num, int file_num)
{
    cout << "Test " << setw(2) << test_num << " (files: " << setw(3) << file_num << ".in/out): ";
    cout.flush();

    // Read input file content
    ifstream fin(input_file);
    stringstream buffer;
    buffer << fin.rdbuf();
    string input_str = buffer.str();
    fin.close();

    // Solve using appropriate method
    string result;
    if (use_optimal)
    {
        result = solve_optimal(input_str);
        cout << "[optimal]" << endl;
    }
    else
    {
        // Try brute force with timeout
        auto future = async(launch::async, solve_optimal, input_str);
        auto status = future.wait_for(seconds(1));

        if (status == future_status::timeout)
        {
            cout << "[timeout -> optimal]" << endl;
            result = solve_optimal(input_str);
        }
        else
        {
            result = future.get();
            cout << "[brute force]" << endl;
        }
    }

    // Write output
    ofstream fout(output_file);
    fout << result;
    fout.close();
}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
// Function to generate a test case
void generate_test_case(int test_num, int file_num)
{
    // Create input file
    string input_file = "test_cases/" + to_string(file_num) + ".in";
    ofstream fin(input_file);

    // Generate random test data
    int N_high = 1e5;
    int V_high = 1e5;
    int n = (rng() % N_high) + 1;
    vector<int> a(n);
    for (int i = 0; i < n; ++i)
    {
        a[i] = (rng() % V_high) + 1;
    }

    fin << n << '\n';
    for (int i = 0; i < n; ++i)
    {
        fin << a[i] << " \n"[i == n - 1];
    }
    int q = rng() % N_high + 1; // Random number of queries
    fin << q << '\n';
    for (int i = 0; i < q; ++i)
    {
        int l = rng() % n + 1;
        int r = rng() % n + 1;
        if (l > r) swap(l, r);
        int x = rng() % V_high + 1; // Random value for the query
        fin << l << " " << r << " " << x << '\n';
    }
    fin.close();

    // Generate output using brute force first, falling back to optimal if needed
    string output_file = "test_cases/" + to_string(file_num) + ".out";
    run_solution(input_file, output_file, false, test_num, file_num);
}

int main(int argc, char *argv[])
{
    srand(time(0)); // Initialize random seed
     sieve(); // Precompute smallest prime factors
    // Create test_cases directory if it doesn't exist
    // system("mkdir -p test_cases");

    int start_file_num = find_next_file_number();
    int num_tests = 25;

    cout << "Generating " << num_tests << " test cases starting from file number " << start_file_num << endl;
    cout << "--------------------------------------------------------------------------------" << endl;

    // Generate test cases
    for (int test_num = 1; test_num <= num_tests; test_num++)
    {
        int file_num = start_file_num + test_num - 1;
        generate_test_case(test_num, file_num);
    }

    cout << "--------------------------------------------------------------------------------" << endl;
    cout << "Test generation complete! Generated " << num_tests << " test cases." << endl;
    return 0;
}