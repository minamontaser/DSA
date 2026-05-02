
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

#define ll long long
#define ld long double

inline void set_fast_io() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
}

int main() {
	set_fast_io();

	ld x0, y0, x1, y1;
	cout << "(x0, y0), (x1, y1): ";
	cin >> x0 >> y0 >> x1 >> y1;

	ld dx = x1 - x0;
	ld dy = y1 - y0;

	cout << fixed << setprecision(2);

	// Line information
	cout << "Start Point: (" << x0 << ", " << y0 << ")\n";
	cout << "End Point  : (" << x1 << ", " << y1 << ")\n";
	cout << "dx = " << dx << ", dy = " << dy << "\n";

	// Slope
	if (dx != 0)
		cout << "Slope (m)  : " << dy / dx << "\n";
	else
		cout << "Slope (m)  : Infinite (Vertical Line)\n";

	// Number of steps
	ll steps = static_cast<ll>(max(abs(dx), abs(dy)));
	cout << "Steps      : " << steps << "\n";

	// Increments
	ld xInc = dx / steps;
	ld yInc = dy / steps;

	cout << "xIncrement : " << xInc << "\n";
	cout << "yIncrement : " << yInc << "\n\n";

	cout << "Generated DDA Points:\n";
	cout << "Step\tX\tY\tRounded(X,Y)\n";

	ld x = x0;
	ld y = y0;

	for (size_t i = 0; i <= steps; i++) {
		cout << i << "\t"
			<< x << "\t"
			<< y << "\t("
			<< round(x) << ", "
			<< round(y) << ")\n";

		x += xInc;
		y += yInc;
	}

	return 0;
}