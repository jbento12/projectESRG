#ifndef USER_H__
#define USER_H__




#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <QString>
#include "training.h"
#include "exercise.h"


#define USER_E_NAME_INVAL -1
#define USER_E_NAME_EXISTS -2


using namespace std;




class User
{
public:
    User();
    ~User();

    bool setWeight(float weight);
    bool setHeight(float height);

    void setId(int32_t id){this->userId = id;};
    void setName(const string& name);
    void setUsername(const string& username);
    void setPassword(const string& password){this->password = password;};

    string getName();
    string getUsername();

    static bool checkLogin(const string& username, const string& password, User*& user);

    Training toPlay;

    //list of exercise list
    Training newModel;
    vector<Training> userTrainingList;
    int32_t addNewModel(const string);
    void addExerciseToNewModel(Exercise& exercise);
    void populateUserTrainingList();
    //bool checkLoginFromDB(const string& username, const string& pass);

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
    static bool addUserToUserListFromDatabase(const User& user);
    static void populateUserList();
    static void printUserList();


    static uint32_t userIDcount;
private:
    static vector<User> UserList;

};










#endif//USER_H__
