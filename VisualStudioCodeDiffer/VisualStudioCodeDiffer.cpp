#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>

#include "windows.h"
#include "shellapi.h"
#include "processenv.h"

constexpr const char* vs_code_path_default =
  "%localappdata%\\Programs\\Microsoft VS Code\\Code.exe";
constexpr const char* settings_file_name = "vs_code_path.txt";

std::string get_vs_code_path()
{
  std::fstream settings_file(settings_file_name);
  std::string vs_code_path;
  std::getline(settings_file, vs_code_path);

  if (!vs_code_path.empty())
  {
    return vs_code_path;
  }

  char vs_code_path_expanded[MAX_PATH];
  ExpandEnvironmentStringsA(
    vs_code_path_default, vs_code_path_expanded, MAX_PATH);
  return vs_code_path_expanded;
}

int main(int argc, const char* argv[])
{
  if (argc != 3)
  {
    std::cout
      << "Invalid number of arguments\n"
      << "Expecting 2 arguments. The fully qualified paths to the files to "
         "compare\n"
      << "Alternatively you can call VS Code yourself with [path_to_vs_code] "
         "--diff [first_file_path] [second_file_path]\n";
    system("pause");
    return 0;
  }

  auto vs_code_path = get_vs_code_path();
  if (!std::filesystem::exists(vs_code_path))
  {
    std::cout
      << "Unable to determine path to VS Code executable\nTried to find "
         "VS Code in "
      << vs_code_path_default
      << "\nIf VS Code is installed in a different directory, provide a "
         "file called "
      << settings_file_name << " that contains the path to VS Code.";
    system("pause");
    return 0;
  }

  std::string params = "-n --diff ";
  params += argv[1];
  params += " ";
  params += argv[2];

  auto result = (int)ShellExecuteA(nullptr,
    nullptr,
    vs_code_path.c_str(),
    params.c_str(),
    nullptr,
    SW_SHOWMAXIMIZED);

  if (result < 32)
  {
    std::cout << "Tried calling: " << vs_code_path << " " << params << "\n";
    std::cout << "Start failed with error code: " << result << "\n";
    system("pause");
  }

  return 0;
}