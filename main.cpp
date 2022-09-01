#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <set>
#include <map>
#include <regex>
std::set<std::string> files;

void getFilesInDir(std::filesystem::path path)
{
    int i = 0;
    std::ifstream csdFile;
    for (auto &v : std::filesystem::directory_iterator(path))
    {
        //

        if (v.is_directory())
        {
            // getFilesInDir(v);
            /* code */
        }
        else
        {
            // if (v.path().extension().string() == ".json" || v.path().extension().string() == ".png")
            if (v.path().extension().string() == ".csd")
            {
                csdFile.open(v.path().filename().string());
                std::string fileName = v.path().filename().string();
                // std::cout << fileName << std::endl;

                std::string line;
                std::smatch matches;
                std::regex rgx("/([a-zA-Z0-9_]+\\.(?:png|jpg)).*");
                if (csdFile.is_open())
                {
                    while (getline(csdFile, line))
                    {
                        if (std::regex_search(line, matches, rgx))
                        {
                            for (size_t i = 1; i < matches.size(); ++i)
                            {
                                std::cout << matches[i].str() << std::endl;
                                files.insert(matches[i].str());
                            }
                        }

                        // if (std::regex_match(line, std::regex(".*(\\.png).*")))
                        //     std::cout << line << std::endl;
                    }
                    csdFile.close();
                }

                // files.insert(fileName);
                // i++;
                // std::string extensionName = v.path().extension().string();
                // std::cout << "extensionName= " << extensionName << std::endl;
            }
        }
    }
    std::cout << i << std::endl;
}
int main(int argc, char const *argv[])
{
    
    // getFilesInDir();
    std::map<std::string, bool> allImages;
    for (auto &log : std::filesystem::directory_iterator(std::filesystem::current_path()))
    {
        if (log.is_regular_file() && log.path().filename().string() == "allFiles.txt")
        {
            /* code */
            std::ifstream allFile;
            allFile.open(log.path());
            std::string line;
            // int i = 0;
            if (allFile.is_open())
            {
                while (getline(allFile, line))
                {
                    // i++;
                    allImages.insert(std::make_pair(line, false));
                    // std::cout << line << std::endl;
                    // if (std::regex_match(line, std::regex(".*(\\.png).*")))
                    //     std::cout << line << std::endl;
                }
                allFile.close();
                // std::cout << i << std::endl;
            }
        }
    }

    std::map<std::string, bool>::iterator it;
    for (auto &log : std::filesystem::directory_iterator(std::filesystem::current_path()))
    {
        if (log.is_regular_file() && (log.path().filename().string() == "allImageInCsd.txt" || log.path().filename().string() == "usingImages.txt"))
        {
            /* code */
            std::ifstream uesedFiles;
            uesedFiles.open(log.path());
            std::string line;
            // int i = 0;
            if (uesedFiles.is_open())
            {
                while (getline(uesedFiles, line))
                {
                    // i++;
                    it = allImages.find(line);
                    if (it != allImages.end())
                    {
                        it->second = true;
                        /* code */
                    }

                    // allImages.insert(std::make_pair(line, false));
                    // std::cout << line << std::endl;
                    // if (std::regex_match(line, std::regex(".*(\\.png).*")))
                    //     std::cout << line << std::endl;
                }
                uesedFiles.close();
                // std::cout << i << std::endl;
            }
        }
    }

    // std::cout << allImages.size() << std::endl;
    std::ofstream unUsingImages;
    unUsingImages.open("unUsedImages.txt", std::ios::out);
    for (auto &image : allImages)
    {
        if (!image.second)
        {
            unUsingImages << image.first << std::endl;
        }
    }
    unUsingImages.close();
    return 0;
}
