#pragma warning(disable:4996)
#include <iostream>
#include <filesystem>
#include <windows.h>
#include <string>

using namespace std;
using namespace std::filesystem;

// количество копий до перезаписи
const int NUMBER_OF_OVERWRITES = 30;
// путь папки, которую нужно копировать
path path_from = { R"(D:\thrash\example)" };
// путь папки, в которую нужно копировать
string path_to_ = { R"(D:\thrash\hereTest)" };
// название папки с копиями
string name_of_directory = { R"(backup)" };



int main()
{    
    ShowWindow(GetConsoleWindow(), SW_HIDE); // работа программы в фоновом режиме

    for (int i = 0; i < NUMBER_OF_OVERWRITES; i++)
    {      
        path path_to = path_to_ + "\\" + name_of_directory + "_" + to_string(i);                
        if (!exists(path_to))
        {
            create_directories(path_to);
            copy(path_from, path_to, copy_options::recursive);
            exit(5);
        }            

    }    

    file_time_type arr[NUMBER_OF_OVERWRITES];
    for (int i = 0; i < NUMBER_OF_OVERWRITES; i++)
    {
        path path_to = path_to_ + "\\" + name_of_directory + "_" + to_string(i);
        arr[i] = last_write_time(path_to);
    }
    path path_to = path_to_ + "\\" + name_of_directory + "_" + "0";
    file_time_type min_Backup = last_write_time(path_to);
    for (int i = 0; i < NUMBER_OF_OVERWRITES; i++)
    {
        if (arr[i] < min_Backup)
        {
            min_Backup = arr[i];
        }
    }
    int elem_for_overwrite;
    for (int i = 0; i < NUMBER_OF_OVERWRITES; i++)
    {
        if (arr[i] == min_Backup)
        {
            elem_for_overwrite = i;
        }
    }
    path_to = path_to_ + "\\" + name_of_directory + "_" + to_string(elem_for_overwrite);
    remove_all(path_to);
    copy(path_from, path_to, copy_options::recursive);
    
    return 0;
}