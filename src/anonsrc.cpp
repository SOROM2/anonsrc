#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

// take an infile stream and read it into a vector of string
std::vector<std::string> openFile(std::ifstream& file)
{
    std::string line;
    std::vector<std::string> fileContent;

    while (std::getline(file, line)) {
        fileContent.emplace_back(line);
    }

    return fileContent;
}

void WriteColor(std::ostream& os, bool on) {
    int out;
    if (on) {
        out = 1;
    } else {
        out = 0;
    }

    os << out << " "
       << out << " "
       << out << "\n";
}

int main(int argc, char* argv[])
{
    // cli args
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <source file>\n";
        return 1;
    }

    std::ifstream file(argv[1]);

    // file doesn't open
    if (!file) {
        std::cerr << "Error opening file: " << argv[1] << "\n";
        return 1;
    }

    std::cerr << "Loading file...\n";

    std::vector<std::string> fileContents = openFile(file);

    unsigned int maxLineLen = 0;
    unsigned int lineLen;

    std::cerr << "Getting widest line...\n";

    // get line of longest length
    for (std::string& s : fileContents) {
        lineLen = s.length();
        if (lineLen > maxLineLen) {
            maxLineLen = lineLen;
        }
    }

    std::cerr << "Resolution: " << fileContents.size() << "x" << maxLineLen << "\n";
    std::cerr << "Pixel count: " << fileContents.size() * maxLineLen << "\n";
    std::cerr << "Drawing image...\n";

    // header of the ppm file
    std::ostringstream contentStream;
    contentStream << "P3\n" << maxLineLen << " " << fileContents.size() << "\n1\n";

    // write ppm file with on of off pixels
    unsigned int rightPad;
    for (std::string& s : fileContents) {
        rightPad = maxLineLen - s.length();
        for (char& c : s) {
            switch (c) {
                case ' ':
                case '\t':
                    WriteColor(contentStream, false);
                    break;
                default:
                    WriteColor(contentStream, true);
                    break;
            }
        }

        // pad the width
        for (; rightPad != 0; --rightPad) {
            WriteColor(contentStream, false);
        }
    }

    std::cerr << "Writing out the image...\n";
    // write the content out
    std::cout << contentStream.str();
    return 0;
}
