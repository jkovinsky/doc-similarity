#include <fstream>
#include "compare.hpp"


int main(int argc, const char* argv[]) {

    

    int total_argc = argc - 1; // number of terminal cmmd args should not include '\hw1' since 
                              // we assume it is the base case 0 

    // check for 0, 2, or more command line arguments

    if(total_argc == 0 || total_argc >= 2){
        std::cout << "To use this program correctly, one should type...\n./plagiarism-checker-main [directory] containing directories each of which contains text files" << '\n'; 
    }
    else
    {
        // check if user input is a directorty within parent folder

        fs::path directory(argv[1]);

        fs::directory_entry input(directory);

        if(input.is_directory())
        {
            std::vector<fs::path> paths = get_paths(argv[1]); 

            std::vector<CompareFiles> pairs = get_pairs(paths);

            // show stats for each pairwise comparison

            for(int i = 0; i < pairs.size(); ++i)
            {
                pairs[i].show_stats();
                std::cout << '\n'; 
            }
        }


    }
    

    return 0;
}
