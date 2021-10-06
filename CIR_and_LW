#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


class Scheme {
protected:
    vector <double> before;
    vector <double> now;
    int const p_N;
    int const p_T;
public:
    Scheme(int p_N, int p_T): p_N(p_N), p_T(p_T) {}
    double c = 1;
    int N = p_N;
    int T = p_T;
    double h = 1 / double(N);
    double t = 0.01 * h / c;
};

class CIR: public Scheme {
private:
    
public:
    CIR(int p_N, int p_T) : Scheme(p_N, p_T) {}

    void process(vector <double> init_cond) {
        now = init_cond;

        for (int i = 0; i < T;++i) {
            before = now;
            now.clear();
            double new_u;
            new_u = 0;
            now.push_back(new_u);
            for (int j = 1; j < N;++j) {
                new_u = before[j] - c * t / h * (before[j] - before[j - 1]);
                now.push_back(new_u);
            }
        }
    }

    void now_cond() {
        ofstream fin;
        fin.open("CIR.txt");
        fin << "U(x,T)-x" << endl;
        for (int i = 0; i < N;++i) {
            if (now[i] < 0.0001) { // это нужно, чтобы убрать из записи в файл числа по типу 2e-300, т к они почти 0, а как считывать их на питоне я пока не понял
                fin << 0 << "-" << i * h << endl;
            }else{
                fin << now[i] << "-" << i * h << endl;
                cout << now[i];
            }
        }
    }
};

class LW : public Scheme {
private:

public:
    LW(int p_N, int p_T) : Scheme(p_N, p_T) {}

    void process(vector <double> init_cond) {
        now = init_cond;

        for (int i = 0; i < T;++i) {
            before = now;
            now.clear();
            double new_u;
            new_u = 0;
            now.push_back(new_u);
            for (int j = 1; j < N - 1;++j) {
                new_u = before[j] - c * t / 2 / h * (before[j + 1] - before[j - 1]) + c * c * t * t / 2 / h / h * (before[j + 1] - 2 * before[j] + before[j - 1]);
                now.push_back(new_u);
            }
            new_u = before[N-1] - c * t / 2 / h * (0 - before[N - 2]) + c * c * t * t / 2 / h / h * (0 - 2 * before[N-1] + before[N - 2]);
            now.push_back(new_u);
        }
    }

    void now_cond() {
        ofstream fin;
        fin.open("LW.txt");
        fin << "U(x,T)_x" << endl;
        for (int i = 0; i < N ;++i) {
            if (now[i] < 0.0001 && now[i]> -0.0001) {
                fin << 0 << "_" << i * h << endl;
            } else {
                fin << now[i] << "_" << i * h << endl;
            }
        }
    }
};

int main()
{
    int N;
    int T;
    cout << "N:";
    cin >> N;
    cout << "T:";
    cin >> T;
    CIR cir(N, T);
    LW lw(N, T);

    vector<double>init_cond;
    for (int i = 0;i < N;++i) {
        if ((0.2 * N <= i) and (i <= 0.4 * N)) {
            init_cond.push_back(1);
        } else {
            init_cond.push_back(0);
        }
    }
    //cir.process(init_cond);
    //cir.now_cond();
    lw.process(init_cond);
    lw.now_cond();
}
