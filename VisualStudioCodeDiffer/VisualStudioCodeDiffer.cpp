#include <iostream>
#include <string>

#include "windows.h"
#include "shellapi.h"

constexpr const char* vscode_path =
  "\"C:\\Users\\ltisbecker\\AppData\\Local\\Programs\\Microsoft VS "
  "Code\\Code.exe\"";

int main(int argc, const char* argv[])
{
  if (argc != 3)
  {
    std::cout
      << "Invalid number of arguments\n"
      << "Expecting 2 arguments. The fully qualified paths to the files to "
         "compare\n"
      << "Alternatively you can call VSCode yourself with [path_to_vscode] "
         "--diff [first_file_path] [second_file_path]\n";
    system("pause");
    return 0;
  }

  std::string params = "--diff ";
  params += argv[1];
  params += " ";
  params += argv[2];

  auto result = (int)ShellExecuteA(
    nullptr, nullptr, vscode_path, params.c_str(), nullptr, SW_SHOWMAXIMIZED);

  if (result < 32)
  {
    std::cout << "Tried calling: " << vscode_path << " " << params << "\n";
    std::cout << "Start failed with error code: " << result << "\n";
    system("pause");
  }

  return 0;
}