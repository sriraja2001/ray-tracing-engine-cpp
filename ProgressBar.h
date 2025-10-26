#ifndef RAY_TRACER_PROGRESSBAR_H
#define RAY_TRACER_PROGRESSBAR_H

#include <iostream>
#include <iomanip>

using namespace std;

class ProgressBar {
private:
    int total;

public:
    explicit ProgressBar(const int total) : total(total) {}

    void update(const int current) const {
        const double progress = static_cast<double>(current) / static_cast<double>(total);
        cout << "\r" << setprecision(1) << fixed << (progress * 100.0) << "% ";
        cout.flush();
    }

    void finish() const {
        cout << "\nRender complete!" << endl;
    }
};

#endif //RAY_TRACER_PROGRESSBAR_H