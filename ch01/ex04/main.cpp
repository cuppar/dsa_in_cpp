#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>

std::ofstream outputFile{"output"};

void handleInclude(const std::string_view filename)
{
    std::ifstream inputFile{filename.data()};

    for (std::string line; std::getline(inputFile, line);)
    {
        if (line.find("#include") != std::string::npos)
        {
            auto start{line.find('<')};

            if (start == std::string::npos)
                throw std::runtime_error("except '<' in #include");

            auto end{line.find('>')};

            if (end == std::string::npos)
                throw std::runtime_error("except '>' in #include");

            std::string includeFilename{line.substr(start + 1, end - start - 1)};
            std::cout << "includeFilename: " << includeFilename << '\n';
            handleInclude(includeFilename);
        }

        else
            outputFile << line << '\n';
    }
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Need a filename arg\n";
        std::exit(1);
    }

    std::string filename{argv[1]};
    handleInclude(filename);
    return 0;
}
