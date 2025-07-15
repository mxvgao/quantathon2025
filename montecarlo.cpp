#include <random>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iostream>
using namespace std;

int main(){
    const int N = 2250;
    const int S = 100000000;

    random_device rd;
    mt19937_64 gen(rd());
    uniform_real_distribution<double> dist(0.0, 1.0);

    vector<double> u(S);
    for(int i = 0; i < S; ++i) u[i] = dist(gen);
    sort(u.begin(), u.end());

    vector<double> V_cur(S, 0.0), V_new(S), prefix(S+1);
    vector<double> thresholds(N+1);
    double EV_start = 0.0;

    for(int n = N; n >= 1; --n){
        prefix[0] = 0.0;
        for(int i = 0; i < S; ++i) prefix[i+1] = prefix[i] + V_cur[i];

        // int thresh_idx = -1;
        for(int i = 0; i < S; ++i){
            double ev_now = double(n - 1) / n - u[i];
            double cont = ((i + 1) * V_cur[i] + (prefix[S] - prefix[i + 1])) / S;
            double F = ev_now + cont;
            V_new[i] = (F > 0.0 ? F : 0.0);
            // if(F >= 0.0) thresh_idx = i;
        }

        // thresholds[n] = (thresh_idx >= 0 ? u[thresh_idx] : 0.0);
        if(n == 1) EV_start = prefix[S] / S;
        swap(V_cur, V_new);
    }

    cout << "Expected total gain: " << EV_start << "\n\n";
    return 0;
}
