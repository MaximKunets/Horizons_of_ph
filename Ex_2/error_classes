#include <iostream>
#include <vector>
#include <fstream>
#include <new>
using namespace std;

class Errors {
protected:
    string type_error;
public:
    ~Errors() {}
    virtual string perr() = 0{
    }
};

class ErrNew:public Errors{
public:
    ~ErrNew() {}
    ErrNew() : Errors() {
        type_error = "Memory isn’t allocated";
    }
    virtual string perr() {
       return type_error;
    }   
};

class CurErr : public Errors {
public:
    ~CurErr() {}
    CurErr() : Errors(){
        type_error = "Error. Courant number > 1";
    }
    virtual string perr() {
        return type_error;
    }
};

class Scheme {
protected:
    vector <double>* before;
    vector <double>* now;
    int const p_N;
    int const p_T;
    double p_t;
public:
    Scheme(int p_N, int p_T, double p_t) : p_N(p_N), p_T(p_T), p_t(p_t) {
        before = new vector<double>;
        now = new vector<double>;
    }

    double c = 1;
    int N = p_N;
    int T = p_T;
    double t = p_t;
    double h = 1 / double(N);

    ~Scheme(){
        free(before);
        free(now);
    }

    void check_CurNumber() {
        if (t * c / h > 1)
            throw CurErr();
    }

    void* operator new (size_t size, const nothrow_t& nth) {
        Scheme* a = (Scheme*)malloc(size);
        if (!a) {
            throw ErrNew();
        }
        return a;
    }

    void operator delete (void* p) {
        free(p);
    }
};

class CIR : public Scheme {
public:
    CIR(int p_N, int p_T, double t) : Scheme(p_N, p_T, t) {}
    ~CIR() {}

    void process(vector <double> init_cond) {
        *now = init_cond;

        for (int i = 0; i < T;++i) {
            *before = *now;
            (*now).clear();
            double new_u;
            new_u = 0;
            (*now).push_back(new_u);
            for (int j = 1; j < N;++j) {
                new_u = (*before)[j] - c * t / h * ((*before)[j] - (*before)[j - 1]);
                (*now).push_back(new_u);
            }
        }
    }

    void now_cond() {
        ofstream fin;
        fin.open("CIR.txt");
        fin << "U(x,T)-x" << endl;
        for (int i = 0; i < N;++i) {
            if ((*now)[i] < 0.0001) {
                fin << 0 << "-" << i * h << endl;
            } else {
                fin << (*now)[i] << "-" << i * h << endl;
            }
        }
    }
};

class LW : public Scheme {
public:
    LW(int p_N, int p_T, double t) : Scheme(p_N, p_T, t) {}
    ~LW() {}

    void process(vector <double> init_cond) {
        (*now) = init_cond;

        for (int i = 0; i < T;++i) {
            (*before) = (*now);
            (*now).clear();
            double new_u;
            new_u = 0;
            (*now).push_back(new_u);
            for (int j = 1; j < N - 1;++j) {
                new_u = (*before)[j] - c * t / 2 / h * ((*before)[j + 1] - (*before)[j - 1]) + c * c * t * t / 2 / h / h * ((*before)[j + 1] - 2 * (*before)[j] + (*before)[j - 1]);
                (*now).push_back(new_u);
            }
            new_u = (*before)[N - 1] - c * t / 2 / h * (0 - (*before)[N - 2]) + c * c * t * t / 2 / h / h * (0 - 2 * (*before)[N - 1] + (*before)[N - 2]);
            (*now).push_back(new_u);
        }
    }

    void now_cond() {
        ofstream fin;
        fin.open("LW.txt");
        fin << "U(x,T)_x" << endl;
        for (int i = 0; i < N;++i) {
            if ((*now)[i] < 0.0001 && (*now)[i]> -0.0001) {
                fin << 0 << "_" << i * h << endl;
            } else {
                fin << (*now)[i] << "_" << i * h << endl;
            }
        }
    }
};



int main()
{

    int N;
    int T;
    double t, t_2;
    cout << "N:";
    cin >> N;
    cout << "T:";
    cin >> T;
    cout << "t:";
    cin >> t;
    //cout << "t_2:";
    //cin >> t_2; 
    try {
        CIR* cir;
        cir = new(nothrow) CIR(N, T, t);
        LW* lw;
        lw = new(nothrow) LW(N, T, t);

        (*cir).check_CurNumber();
        (*lw).check_CurNumber();
        vector<double>init_cond;
        for (int i = 0;i < N;++i) {
            if ((0.2 * N <= i) and (i <= 0.4 * N)) {
                init_cond.push_back(1);
            } else {
                init_cond.push_back(0);
            }
        }
        (*cir).process(init_cond);
        (*cir).now_cond();
        (*lw).process(init_cond);
        (*lw).now_cond();

        delete (cir);
        delete (lw);
    }
    catch (CurErr e) {
        cout << e.perr();
    }
    catch (ErrNew x) {
        cout << x.perr();
        return 1;
    }
    return 0;
}
