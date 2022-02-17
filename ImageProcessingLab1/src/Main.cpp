#include "MainHeader.hpp"

int main(const int argc, char** argv) {
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);

    auto mat = make_unique<cv::Mat>(cv::imread("img.jpg"));

    cout << std::format("Height: {}\n", mat->rows);
    cout << std::format("Width: {}\n", mat->cols);
    cout << std::format("Size: {}\n", mat->rows * mat->cols);
    cout << std::format("Depth: {}\n", mat->depth());
    cout << std::format("Channels: {}\n", mat->channels());
    cout << std::format("Type: {}\n", mat->type());

    cout << std::string(35, '-') << std::endl;

    for (auto row = 0; row < mat->rows; ++row) {
        for (auto col = mat->cols - 1; col >= mat->cols - 35; --col) {
            mat->ptr(row, col)[0] = 255;
            mat->ptr(row, col)[1] = 0;
            mat->ptr(row, col)[2] = 0;
        }
    }

    cv::imshow("TEST!", *mat);
    cv::waitKey(0);
    cv::imwrite("result.jpg", *mat);

    return EXIT_SUCCESS;
}
