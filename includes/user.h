#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>

#include "exercise.h"
using namespace std;

class User
{
public:
    User();
    ~User();

    bool setWeight(float weight);
    bool setHeight(float height);

    void setName(const string& name);
    void setUsername(const string& username);

    string getName();
    string getUsername();

    static bool checkLogin(const string& username, const string& password, User*& user);

    //list of User's "bought" exercise list
    vector<Exercise> userExercisesList;
    void addExercise(Exercise& exercise);

private:
    string name;
    string username;
    string password;
    float weight;
    float height;
    int32_t userId;






//populate with Users
public:
    static bool addUserToUserList(User& user);
    static void populateUserList();
    static void printUserList();


private:
    static vector<User> UserList;
    static uint32_t userIDcount;
};










#endif  //USER_H_
