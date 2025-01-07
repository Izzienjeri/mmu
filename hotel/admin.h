#ifndef ADMIN_H
#define ADMIN_H

#include <string>

class Admin {
public:
    std::string username;
    std::string password;

    Admin(const std::string& user, const std::string& pass);
    bool authenticate(const std::string& user, const std::string& pass);
};

#endif
