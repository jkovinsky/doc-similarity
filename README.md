# plagiarism-checker

**Description**: The following script uses features from the `<filesystem>` library, which was introduced in `C++17`, along with a standard algorithm detecting the [longest common subsequence](https://en.wikipedia.org/wiki/Longest_common_subsequence) between two strings. 

**Usage**: When running with command line, the user will specify the name of a directory. Within that directory there will be multiple folders of unspecified letters. Within each of those folders will be files of unspecified letters. The program will perform a pairwise comparison of all the files and then print the results with a measure of overalp to the console. These text files contain short descriptions about dolphins generated by ChatGPT. 

**Using Terminal**:
- cd into `plagiarism-checker-main`
- type `make` to verify the program compiles
- type `./plagiarism-checker-main Test` to make a pairwise comparison of text files located in the `Test` folder
