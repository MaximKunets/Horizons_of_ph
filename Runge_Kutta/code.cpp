#include <iostream>
#include <vector>
#include <fstream>
#include <array>
using namespace std;

float function(float x, float y) {
	return x * x - y * y;//x * x - 2 * y;
}

class Solver {
protected:
	float y;
	float x;
    vector <float> solution;
	float step = 0.01;
};


class Euler: public Solver {
public:
	~Euler() {}

	void Solve(float (*f)(float, float), int n,float x_0, float y_0) {
		solution.push_back(y_0);
		y = y_0 + step * f(x_0, y_0);
		solution.push_back(y);
		for (int i = 2; i < n; i++) {
			y = solution[i - 1] + step * f(step * (i - 1) + x_0, solution[i - 1]);
			solution.push_back(y);
		}
	}

	void unload(int n, float x_0) {
		ofstream fin;
		fin.open("Euler.txt");
		fin << "x_y" << endl;
		for (int i = 0; i < n;++i) {
			x = x_0 + i * step;
			if (abs(x) > 0.0001 && abs(solution[i]) > 0.0001) {
				fin << x_0 + i * step << "_" << solution[i] << endl;
			} else {
				if (abs(x) < 0.0001 && abs(solution[i]) < 0.0001) {
					fin << 0 << "_" << 0 << endl;
				} else {
					if (abs(x) < 0.0001) {
						fin << 0 << "_" << solution[i] << endl;
					}
					if (abs(solution[i]) < 0.0001) {
						fin << x << "_" << 0 << endl;
					}
				}
			}
		}
	}

};

class Upgraded_Euler : public Solver {
public:
	~Upgraded_Euler() {}

	void Solve(float (*f)(float, float), int n, float x_0, float y_0) {
		solution.push_back(y_0);
		y = y_0 + step / 2 * f(x_0, y_0);
		solution.push_back(y);
		y = y_0 + step * f(x_0 + step / 2, solution[1]);
		solution.push_back(y);
		for (int i = 3; i < 2*n; i+=2) {
			y = solution[i - 1] + step / 2 * f(step * (i - 1) / 2 + x_0, solution[i - 1]);
			solution.push_back(y);
			y = solution[i - 1] + step * f(step * (i - 1) / 2 + x_0 + step / 2, solution[i]);
			solution.push_back(y);
		}
	}

	void unload(int n, float x_0) {
		ofstream fin;
		fin.open("Upgraded_Euler.txt");
		fin << "x_y" << endl;
		for (int i = 0; i < 2 * n;i += 2) {
			x = x_0 + i * (step / 2);
			if (abs(x) > 0.0001 && abs(solution[i]) > 0.0001) {
				fin << x << "_" << solution[i] << endl;
			} else {
				if (abs(x) < 0.0001 && abs(solution[i]) < 0.0001) {
					fin << 0 << "_" << 0 << endl;
				} else {
					if (abs(x) < 0.0001) {
						fin << 0 << "_" << solution[i] << endl;
					}
					if (abs(solution[i]) < 0.0001) {
						fin << x << "_" << 0 << endl;
					}
				}
			}
		}
	}

};

class Runge_Kutta : public Solver {
private:
	array<double, 4> k;
public:
	~Runge_Kutta() {}
	void Solve(float (*f)(float, float), int n, float x_0, float y_0) {
		solution.push_back(y_0);
		for (int i = 1;i < n + 1;++i) {
			k[0] = f(x_0 + step * i, solution[i - 1]);
			k[1] = f(x_0 + step * i + step / 2, solution[i - 1] + k[0] * step / 2);
			k[2] = f(x_0 + step * i + step / 2, solution[i - 1] + k[1] * step / 2);
			k[3] = f(x_0 + step * i + step, solution[i - 1] + k[0] * step);
			y = solution[i - 1] + step / 6 * (k[0] + 2 * k[1] + 2 * k[2] + k[3]);
			solution.push_back(y);
		}
	}

	void unload(int n, float x_0) {
		ofstream fin;
		fin.open("Runge_Kutta.txt");
		fin << "x_y" << endl;
		for (int i = 0; i < n + 1;++i) {
			x = x_0 + i * step;
			if (abs(x) > 0.0001 && abs(solution[i]) > 0.0001) {
				fin << x << "_" << solution[i] << endl;
			} else {
				if (abs(x) < 0.0001 && abs(solution[i]) < 0.0001) {
					fin << 0 << "_" << 0 << endl;
				} else {
					if (abs(x) < 0.0001) {
						fin << 0 << "_" << solution[i] << endl;
					}
					if (abs(solution[i]) < 0.0001) {
						fin << x << "_" << 0 << endl;
					}
				}
			}
		}
	}

};


int main()
{
	Euler ans_1;
	Upgraded_Euler ans_2;
	Runge_Kutta ans_3;
	float x_0 = -2, y_0 = 3;
	int n = 1001;

	ans_1.Solve(function, n, x_0, y_0);
	ans_1.unload(n, x_0);
	ans_2.Solve(function, n, x_0, y_0);
	ans_2.unload(n, x_0);
	ans_3.Solve(function, n, x_0, y_0);
	ans_3.unload(n, x_0);

}
