#include "functions.hpp"
#include <iostream>

std::vector<UserInfo> get_infos(const std::string& filename) {
    std::ifstream file(FILE_NAME);

    if (!file.is_open()) {
        std::cerr << "Error opening the CSV file." << std::endl;
        // You might want to return an error code or throw an exception here.
        return {};
    }

    std::vector<UserInfo> user_infos;
    std::string line;

    std::getline(file, line); // Skip the header row.
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string uid_str, name, password;

        #include <string> // Add this line

        if (std::getline(ss, uid_str, ',') &&
            std::getline(ss, name, ',') &&
            std::getline(ss, password, ',')) {
            UserInfo user_info;
            try {
                user_info.uid = stoi(uid_str);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error converting UID to integer: " << e.what() << std::endl;
                // Handle the error or skip this entry
                continue;
            }
            user_info.name = name;
            user_info.password = password;
            user_infos.push_back(user_info);
        }
    }

    return user_infos;
}

bool check_in_file(string name){
    vector<UserInfo> users = get_infos(FILE_NAME);
    for (UserInfo user : users){
        if (user.name == name){
            return true;
        }
    }
    return false;
}

void register_user(string name, string password){
    vector<UserInfo> users = get_infos(FILE_NAME);
    int uid = users.size() + 1;
    UserInfo user;
    user.uid = uid;
    user.name = name;
    user.password = password;
    users.push_back(user);
    ofstream file(FILE_NAME);
    file << "uid,name,password" << endl;
    for (UserInfo user : users){
        file << user.uid << "," << user.name << "," << user.password << endl;
    }
    file.close();
    cout << "User registered." << endl;
}

void change_password(string name, string password){
    vector<UserInfo> users = get_infos(FILE_NAME);
    for (UserInfo& user : users){
        if (user.name == name){
            user.password = password;
        }
    }
    ofstream file(FILE_NAME);
    file << "uid,name,password" << endl;
    for (UserInfo user : users){
        file << user.uid << "," << user.name << "," << user.password << endl;
    }
    file.close();
    cout << "Password changed." << endl;
}

void delete_user(string name){
    vector<UserInfo> users = get_infos(FILE_NAME);
    for (int i = 0; i < users.size(); i++){
        if (users[i].name == name){
            users.erase(users.begin() + i);
        }
    }
    ofstream file(FILE_NAME);
    file << "uid,name,password" << endl;
    for (UserInfo user : users){
        file << user.uid << "," << user.name << "," << user.password << endl;
    }
    file.close();
    cout << "User deleted." << endl;
}

bool login(string name, string password){
    vector<UserInfo> users = get_infos(FILE_NAME);
    for (UserInfo user : users){
        if (user.name == name && user.password == password){
            return true;
        }
    }
    return false;
}



