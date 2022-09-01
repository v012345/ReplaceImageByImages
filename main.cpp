#include <fstream>
#include <iostream>
#include <filesystem>
#include <string>
#include <set>
#include <map>
#include <regex>
std::map<std::string, bool> unUsedImages;
std::ifstream files("unUsedImages.txt");
std::ofstream targetImage;
void getFilesInDir(std::filesystem::path path)
{
    for (auto &v : std::filesystem::directory_iterator(path))
    {
        //

        if (v.is_directory())
        {
            getFilesInDir(v);
            /* code */
        }
        else
        {
            if (!(v.path().filename().string() == "a_read_point_to_replace_image_that_unused.png" ||
                  v.path().filename().string() == "a_read_point_to_replace_image_that_unused.jpg"))
            {
                if (v.path().extension().string() == ".png" or v.path().extension().string() == ".jpg")
                {
                    if (unUsedImages.find(v.path().filename().string()) != unUsedImages.end())
                    {
                        targetImage.open(v.path(), std::ios::binary);
                        if (targetImage.is_open())
                        {
                            if (v.path().extension().string() == ".png")
                            {
                                std::ifstream png("a_read_point_to_replace_image_that_unused.png", std::ios::binary);

                                targetImage << png.rdbuf();
                                png.close();
                            }
                            else
                            {
                                std::ifstream jpg("a_read_point_to_replace_image_that_unused.jpg", std::ios::binary);
                                targetImage << jpg.rdbuf();
                                jpg.close();
                            }
                            targetImage.close();
                        }

                        /* code */
                    }

                    // std::cout << v.path().filename().string() << std::endl;
                }
            }

            // // if (v.path().extension().string() == ".json" || v.path().extension().string() == ".png")
            // if (v.path().extension().string() == ".csd")
            // {
            // csdFile.open(v.path().filename().string());
            // std::string fileName = v.path().filename().string();
            // // std::cout << fileName << std::endl;

            // std::string line;
            // std::smatch matches;
            // std::regex rgx("/([a-zA-Z0-9_]+\\.(?:png|jpg)).*");
            // if (csdFile.is_open())
            // {
            //     while (getline(csdFile, line))
            //     {
            //         if (std::regex_search(line, matches, rgx))
            //         {
            //             for (size_t i = 1; i < matches.size(); ++i)
            //             {
            //                 std::cout << matches[i].str() << std::endl;
            //                 // files.insert(matches[i].str());
            //             }
            //         }

            //         // if (std::regex_match(line, std::regex(".*(\\.png).*")))
            //         //     std::cout << line << std::endl;
            //     }
            //     csdFile.close();
            // }

            // files.insert(fileName);
            // i++;
            // std::string extensionName = v.path().extension().string();
            // std::cout << "extensionName= " << extensionName << std::endl;
            // }
        }
    }
}
int main(int argc, char const *argv[])
{
    if (!files.is_open())
    {
        std::cout << "miss unUsedImages.txt" << std::endl;
        return 0;
    }
    std::string line = "";
    while (getline(files, line))
    {
        unUsedImages.insert(std::make_pair(line, true));
    }
    files.close();

    // if (!png.is_open() or !jpg.is_open())
    // {
    //     std::cout << "miss red point" << std::endl;
    //     return 0;
    // }
    getFilesInDir(std::filesystem::current_path());
    // std::map<std::string, bool> allImages;
    // for (auto &log : std::filesystem::directory_iterator(std::filesystem::current_path()))
    // {
    //     if (log.is_regular_file() && log.path().filename().string() == "allFiles.txt")
    //     {
    //         /* code */
    //         std::ifstream allFile;
    //         allFile.open(log.path());
    //         std::string line;
    //         // int i = 0;
    //         if (allFile.is_open())
    //         {
    //             while (getline(allFile, line))
    //             {
    //                 // i++;
    //                 allImages.insert(std::make_pair(line, false));
    //                 // std::cout << line << std::endl;
    //                 // if (std::regex_match(line, std::regex(".*(\\.png).*")))
    //                 //     std::cout << line << std::endl;
    //             }
    //             allFile.close();
    //             // std::cout << i << std::endl;
    //         }
    //     }
    // }

    // std::map<std::string, bool>::iterator it;
    // for (auto &log : std::filesystem::directory_iterator(std::filesystem::current_path()))
    // {
    //     if (log.is_regular_file() && (log.path().filename().string() == "allImageInCsd.txt" || log.path().filename().string() == "usingImages.txt"))
    //     {
    //         /* code */
    //         std::ifstream uesedFiles;
    //         uesedFiles.open(log.path());
    //         std::string line;
    //         // int i = 0;
    //         if (uesedFiles.is_open())
    //         {
    //             while (getline(uesedFiles, line))
    //             {
    //                 // i++;
    //                 it = allImages.find(line);
    //                 if (it != allImages.end())
    //                 {
    //                     it->second = true;
    //                     /* code */
    //                 }

    //                 // allImages.insert(std::make_pair(line, false));
    //                 // std::cout << line << std::endl;
    //                 // if (std::regex_match(line, std::regex(".*(\\.png).*")))
    //                 //     std::cout << line << std::endl;
    //             }
    //             uesedFiles.close();
    //             // std::cout << i << std::endl;
    //         }
    //     }
    // }

    // // std::cout << allImages.size() << std::endl;
    // std::ofstream unUsingImages;
    // unUsingImages.open("unUsedImages.txt", std::ios::out);
    // for (auto &image : allImages)
    // {
    //     if (!image.second)
    //     {
    //         unUsingImages << image.first << std::endl;
    //     }
    // }
    // unUsingImages.close();
    return 0;
}
