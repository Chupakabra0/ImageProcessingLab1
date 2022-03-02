#include "MainHeader.hpp"

std::unique_ptr<argparse::ArgumentParser> InitMain(const int argc, char** argv) {
    cv::utils::logging::setLogLevel(cv::utils::logging::LogLevel::LOG_LEVEL_SILENT);
    
    auto parser = std::make_unique<argparse::ArgumentParser>();
    parser->add_argument("-f", "--filepath")
        .required().help("specify the input image file");
    
    try {
        parser->parse_args(argc, argv);
    }
    catch (const std::exception& err) {
        throw err;
    }

    return parser;
}

int GetImageColorDepth(const cv::Mat& mat) {
    switch (mat.depth()) {
        case CV_8U: case CV_8S: {
            return 8; // 8 bit unsigned/signed
        }
        case CV_16U: case CV_16S: case CV_16F: {
            return 16; // 16 bit unsigned/signed/float
        }
        case CV_32S: case CV_32F: {
            return 32;// 32 bit signed/float
        }
        case CV_64F: {
            return 64; // 64 bit double
        }
        default: {
            throw std::runtime_error("Unknown color depth");
        }
    }
}

int main(const int argc, char** argv) {
    try {
        auto parser = InitMain(argc, argv);

        const auto filePath = parser->get<std::string>("-f");
        auto mat = make_unique<cv::Mat>(cv::imread(filePath, cv::ImreadModes::IMREAD_ANYDEPTH | cv::ImreadModes::IMREAD_ANYCOLOR));

        // bmp only
        //auto file = std::make_unique<std::fstream>(filePath, std::ios::binary | std::ios::in);
        //if (file->good()) {
        //    auto* noc = new char[2];
        //    file->seekg(0x1C, std::ios::beg);
        //    file->read(noc, 2);
        //    auto numColors = std::unique_ptr<unsigned char>(reinterpret_cast<unsigned char*>(noc));

        //    std::cout << (int)*numColors << std::endl;
        //}

        cout << std::format("Height: {}\n", mat->rows);
        cout << std::format("Width: {}\n", mat->cols);
        cout << std::format("Size: {}\n", mat->rows * mat->cols);
        cout << std::format("Depth per channel: {}\n", GetImageColorDepth(*mat));
        cout << std::format("Channels: {}\n", mat->channels());

        cout << std::string(35, '-') << std::endl;

        for (auto row = 0; row < mat->rows; ++row) {
            for (auto col = mat->cols - 35; col < mat->cols; ++col) {
                mat->ptr(row, col)[0] = 255; // Blue
                mat->ptr(row, col)[1] = 0;   // Green
                mat->ptr(row, col)[2] = 0;   // Red
            }
        }

        cv::imshow(filePath, *mat);
        cv::waitKey(0);
        cv::imwrite(std::format("mod_{}", filePath), *mat);

        return EXIT_SUCCESS;
    }
    catch (const std::exception& exception) {
        std::cerr << exception.what() << std::endl;
        return EXIT_FAILURE;
    }
}
