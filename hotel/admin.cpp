#include "admin.h"

Admin::Admin(const std::string& user, const std::string& pass) : username(user), password(pass) {}

bool Admin::authenticate(const std::string& user, const std::string& pass) {
    return (username == user && password == pass);
}
