#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

#define FILE_NAME "data/file.csv"

struct UserInfo {
    int uid;
    std::string name;
    std::string password;
};

std::vector<UserInfo> get_infos(const std::string& filename);
bool check_in_file(string name);
bool login(string name, string password);
void register_user(string name, string password);
void change_password(string name, string password);
void delete_user(string name);