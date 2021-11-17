#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int sign(double x) {
    int s;
    x > 0 ? s = 1 : s = -1;
    return s;
}

double minmod(double x, double y) {
    return (min(abs(x), abs(y)) * sign(x));
}

double MC(double x, double y) {
    return min(min(abs((x + y) / 2), 2 * abs(x)), 2 * abs(y)) * sign(x);
}

double superbee(double x, double y) {
    return max(min(2 * abs(x), abs(y)), min(abs(x), 2 * abs(y)));
}

double van_leer(double x, double y) {
    return 2 * x * y / (x + y);
}

class damp_TVD {
protected:
    vector <double> init;
    vector <double> before;
    vector <double> now;
    int N;                  // кол-во шагов по координате
    int T;                  // кол-во шагов по времени
    double h;               // шаг по координате
    double t;               // шаг по времени
    double c = 100;         // скорость
    double cour_numb;       // число куранта
public:
    damp_TVD(int p_N, int p_T) : N(p_N), T(p_T) {
        h = 10 / double(N);
        t = 0.5 * h / c;
        cour_numb = c * t / h;
    }
};

class TVD: public damp_TVD {
public:
    TVD(int p_N, int p_T, string type) : damp_TVD(p_N, p_T) { //  type может принимать значения "1" или "exp"
        for (int i = -N / 2;i < N / 2;++i) {
            if (i * h < -3 || i * h > 3) {
                init.push_back(0);
            } else {
                type == "exp" ? init.push_back(exp(-i * i * h * h / 2) - exp(-9 / 2)) : init.push_back(1);
            }
        }
    }

    void now_cond() {
        ofstream fin("TVD.txt", ios::app);
        //fin.open("TVD.txt");
        //fin << "F(x)_x" << endl;
        for (int i = 0; i < N;++i) {
            if (now[i] < 0.0001 && now[i]> -0.0001) {
                fin << 0 << " " << (i - N / 2) * h << endl;
            } else {
                fin << now[i] << " " << (i - N / 2) * h << endl;
            }
        }
    }

    void process(double(*limiter)(double x, double y)) {
        now = init;
        now_cond();
        for (int j = 1; j < T;++j) {
            if (j == T - 1) {
                int y = 0;
            }
            before = now;
            now.clear();
            double new_u = before[0] - cour_numb * before[0];
            now.push_back(new_u);
            new_u = before[1] - cour_numb * (before[1] - before[0]);
            now.push_back(new_u);
            for (int i = 2;i < N-1;++i) {
                double x1 = before[i + 1] - before[i];
                double x2 = before[i] - before[i - 1];
                double x3 = before[i - 1] - before[i - 2];
                new_u = before[i] - cour_numb * (before[i] - before[i - 1]) - cour_numb * (1 - cour_numb) / 2 * (limiter(x1, x2) - limiter(x2, x3));
                now.push_back(new_u);
            }
            new_u = before[N - 1] - cour_numb * (before[N - 1] - before[N - 2]);
            now.push_back(new_u);
            now_cond();
        }
        //now_cond();
    }
};
int main()
{
    int N = 500;
    int T = 250;
    int c;
    cout << "Choose the limiter:" << endl << "1 - minmode" << endl << "2 - MC" << endl << "3 - superbee" << endl << "4 - van Leer" << endl;
    cin >> c;
    ofstream fin("TVD.txt");
    //fin << "F(x) x" << endl;
    /*TVD func1(N, T, "x");
    switch (c) {
    case 1:
        func1.process(minmod);
        break;
    case 2:
        func1.process(MC);
        break;
    case 3:
        func1.process(superbee);
        break;
    case 4:
        func1.process(van_leer);
        break;
    }*/
    TVD func2(N, T, "exp");
    switch (c) {
    case 1: 
        func2.process(minmod);
        break;
    case 2:
        func2.process(MC);
        break;
    case 3:
        func2.process(superbee);
        break;
    case 4:
        func2.process(van_leer);
        break;
    }
    fin.close();

}
