#ifndef FILEINPUT_H
#define FILEINPUT_H

#include <string>
#include <regex>

#include "tools/cpp/runfiles/runfiles.h"

namespace utils
{

    std::string extractDate(const std::string& input_path)
    {
        // Regular expression to match dates in the format YYYY/MM/
        std::regex date_regex(R"((\d{4}/\d{2}/))");  // e.g., 2023/01/
        std::smatch match;

        // Search for the first match of the date pattern in the input string
        if (std::regex_search(input_path, match, date_regex)) {
            // Return the matched date string (first match)
            return match.str(0);
        }

        // If no date is found, return an empty string
        return "";
    }

    std::string getInputFilePath(const std::string& argv, const std::string& filename)
    {
        // Initialize the runfiles library
        std::string error;
        std::unique_ptr<bazel::tools::cpp::runfiles::Runfiles> runfiles(
            bazel::tools::cpp::runfiles::Runfiles::Create(argv, &error));
        if (!runfiles) {
            std::cerr << "Error initializing runfiles: " << error << "\n";
            return "";
        }

        std::string date = extractDate(argv);

        // Use Bazel's Rlocation to find the file inside the runfiles directory
        return runfiles->Rlocation("__main__/" + date + filename);
    }

}  // namespace utils

#endif  // FILEINPUT_H
