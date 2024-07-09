#include "compare.hpp"

CompareFiles::CompareFiles(const fs::path& _p1, const fs::path& _p2) : p1(_p1), p2(_p2), common(""){
	this->compare();
}; 

// recursively go through each directory to find all possible reg files
std::vector<fs::path> get_paths(const std::string& s)
{
	std::vector<fs::path> all_files; // container for all discoverable reg files

	fs::path directory(s);
		
	for(auto entry : fs::directory_iterator(directory))
    {
	    if(entry.is_regular_file() && entry.path().filename() != ".DS_Store")
	    {
	    	all_files.push_back(entry.path());
	    }

	    if(entry.is_directory())
	    {
	    	auto located_files = get_paths(entry.path().string());
	        all_files.insert(all_files.end(), located_files.begin(), located_files.end()); 
	    }
	}
	
    return all_files; 
}

// stats function
void CompareFiles::show_stats() const
{
	std::cout << "Pair: " << p1.string() << ", " << p2.string() << '\n';

	std::cout << "Common subsequence length: " << common.size() << '\n'; 

	std::cout << "Overlap: " << common << '\n'; 
}


// calculate all subsets of r = 2 given some n # of files 
std::vector<CompareFiles> get_pairs(const std::vector<fs::path>& paths)
{
	std::vector<CompareFiles> all_pairings; 

	for(int i = 0; i < paths.size(); ++i)
	{
		for(int j = i + 1; j < paths.size(); ++j)
		{
			CompareFiles pair(paths[i], paths[j]);
			all_pairings.push_back(pair);
		}	 
	}

	return all_pairings; 
}

void CompareFiles::compare()
{

	std::ifstream path1(p1, std::ios::ate), path2(p2, std::ios::ate); // read in paths pairwise

	int pos_end_1 = path1.tellg(), pos_end_2 = path2.tellg();		// set file lengths

	std::string text1(pos_end_1, ' '), text2(pos_end_2, ' ');		// make empty strings

	path1.seekg(0);
	path1.read(&text1[0], pos_end_1); 
	text1 = '\0' + text1; 
	path2.seekg(0);
	path2.read(&text2[0], pos_end_2);
	text2 = '\0' + text2;
	path1.close();
	path2.close();

	// create a matrix of booleans that store where the 
	// the characters match
	
	std::vector<std::vector<bool>> matches(text2.size(), std::vector<bool> (text1.size(), 0));

	for(int i = 0; i < text2.size(); ++i)
	{
		for(int j = 0; j < text1.size(); ++j)
		{
			if(text2[i] == text1[j])
			{
				matches[i][j] = 1;
			}
		}
	}
	
    
    
    // create a matrix of ints of the same size as matches
   	std::vector<std::vector<int>> count(text2.size(), std::vector<int> (text1.size(), 0));

   	for (int i = 1; i < text2.size(); ++i)
   	{
   		for(int j = 1; j < text1.size(); ++j)
   		{
   			if(matches[i][j])
   			{
   				count[i][j] = 1 + count[i-1][j-1];
   			}
   			else
   			{
   				count[i][j] = std::max(count[i][j-1], count[i-1][j]);
   			}
   		}
   		
   	}
   
	

	//back track
    int i = text2.size()-1;
    int j = text1.size()-1;

    while(count[i][j] > 0)
    {
    	if(matches[i][j])
    	{
    		common = text2[i] + common;
    		i = i - 1;
    		j = j - 1;
    	}
    	else if(count[i][j-1] > count[i-1][j])
    	{
    		j = j - 1;
    	}
    	else
    	{
    		i = i - 1; 
    	}

    }
   
}
