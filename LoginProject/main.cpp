#include "functions.hpp"

int main()
{
    std::string name;
    std::cout << "Enter your name: ";
    std::cin >> name;
    if (check_in_file(name)){
        string pw;
        std::cout << "Enter your password: ";
        std::cin >> pw;
        bool correct = login(name, pw);
        if (correct) {
            std::cout << "Login successful." << std::endl;
            std::cout << "Welcome, " << name << std::endl;
            std::cout << "What service you want, " << name << " ?" << std::endl;
            std::cout << "1. Change password" << std::endl;
            std::cout << "2. Delete account" << std::endl;
            std::cout << "3. Exit" << std::endl;
            int choice;
            std::cout << "Enter your choice: ";
            std::cin >> choice;
            if (choice == 1) {
                std::string password;
                std::cout << "Enter your new password: ";
                std::cin >> password;
                change_password(name, password);
            } else if (choice == 2){
                delete_user(name);
            } else { 
                std::cout << "Bye!" << std::endl;
            }
        } else {
            std::cout << "Wrong password." << std::endl;
        }
        
    } else {
        std::cout << "You are not registered." << std::endl;
        char choice;
        std::cout << "Do you want to register? (y/n): ";
        std::cin >> choice;
        if (choice == 'y'){
            std::string password;
            std::cout << "Enter your password: ";
            std::cin >> password;
            register_user(name, password);
        } else {
            std::cout << "Bye!" << std::endl;
        }
    }
    return 0;
}
