#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <regex>
#include <stdexcept>

// ========================================
// GLOBALS
// ========================================
bool printDebug = false;
std::string sProcess = "[PROCESS]: ";

// ========================================
// DATA
// ========================================

struct Character {
    std::string name;
    int id;
};
    
class NameReplacer {
  private:
    std::vector<Character> names;

    std::string getFirstName(const std::string& name) {
        std::string fullName = name;
        std::stringstream ss(fullName);
        std::string firstName;

        ss >> firstName;

        return firstName;
    }

  public:
    bool loadCharacters(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Could not open file: " << filename << std::endl;
            return false;
        }

        std::string line;
        int i = 1;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                names.push_back({.name = line, .id = i});
                i++;
            }
        }

        file.close();

        std::cout << sProcess << "Loaded '" << names.size() << "' names" << std::endl;
        return true;
    }

    void printCharacters() {
        if (names.size() == 0) {
            throw std::runtime_error("Character names not initialized! Try again after initializing");
        }

        std::cout << "========================================" << std::endl;
        std::cout << "Character mapping" << std::endl;
        for (auto character : names) {
            std::cout << "[Character " << character.id << "]";
            std::cout << " <- " << character.name << std::endl;
        }
        std::cout << "========================================" << std::endl;       
    }

    bool replaceNames(const std::string& inputFile, const std::string& outputFile) {
        std::ifstream inFile(inputFile);
        if (!inFile.is_open()) {
            std::cerr << "Error: Could not open " << inputFile << " for reading" << std::endl;
            return false;
        }

        std::ofstream outFile(outputFile);
        if (!outFile.is_open()) {
            inFile.close();
            std::cerr << "Error: Could not open " << outputFile << " for writing" << std::endl;
            return false;           
        }

        std::string line;
        int lineNo = 1;
        int replacements = 0;
        printDebug && std::cout << "========================================" << std::endl;
        while (std::getline(inFile, line)) {
            std::string lineout = line;

     
            for (auto character : names) {
                std::string fullName = character.name;
                std::string firstName = getFirstName(character.name);

                size_t pos = line.find(fullName);
                std::string replacementString = "[Character " + std::to_string(character.id) + "]";
                if (pos != std::string::npos) {
                    printDebug && std::cout << lineNo << "] " << line.substr(pos, fullName.length()) << " <- " << replacementString << std::endl;
                    line.replace(pos, fullName.length(), replacementString);
                    lineout = line;
                    replacements++;
                }

                pos = line.find(firstName);
                if (pos != std::string::npos) {
                    printDebug && std::cout << lineNo << "] " << line.substr(pos, firstName.length()) << " <- " << replacementString << std::endl;
                    line.replace(pos, firstName.length(), replacementString);
                    lineout = line;

                    replacements++;
                }
            }

            // [REPLACEMENT COMPLETE]
            outFile << lineout << std::endl;
            lineNo++;
        }
        printDebug && std::cout << "========================================" << std::endl;
        inFile.close();
        outFile.close();
        
        std::cout << sProcess << "Replaced '" << replacements << "' occurences" << std::endl;
        return true;
    }
};
    
int main(int argc, char* argv[]) {
    if (argc != 4) {
        std::cerr << "Correct usage: " << argv[0] << " <character_path> <input_path> <output_path>" << std::endl;
        return 1;
    }
    
    std::string characterFile = argv[1];
    std::string inputFile     = argv[2];
    std::string outputFile    = argv[3];

    NameReplacer replacer;
    if (!replacer.loadCharacters(characterFile)) {
        std::cerr << "Error: Could not load characters" << std::endl;
        return 1;
    }
    
    // replacer.printCharacters();

    if (!replacer.replaceNames(inputFile, outputFile)) {
        std::cerr << "Error: Could not replace names in " << inputFile << std::endl;
        return 1;
    }
    
    std::cout << sProcess << "Completed replacement" << std::endl;
    return 0;
}
