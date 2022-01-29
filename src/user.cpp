#include "user.h"
#include "poseClassification.h"

#include <QString>

uint32_t User::userIDcount = 0;
vector<User> User::UserList;


User::User()
{

}

User::~User()
{

}


bool User::setWeight(float weight)
{
    this->weight = weight;
    return true;
}

bool User::setHeight(float height)
{
    this->height = height;
    return true;
}

void User::setName(const string& name)
{
    this->name = name;
}


void User::setUsername(const string& username)
{
    this->username = username;
}


string User::getName()
{
    return this->name;
}

string User::getUsername()
{
    return this->username;
}


bool User::checkLogin(const string& username, const string& pass, User*& user)
{
    QString user_aux1;
    QString user_aux2;
    QString pass_aux1;
    QString pass_aux2;

         user_aux1 = QString::fromStdString(username);
         pass_aux1 = QString::fromStdString(pass);

    for(uint32_t i = 0; i < User::UserList.size(); i++)
    {
        user_aux2 = QString::fromStdString(User::UserList[i].username);
        pass_aux2 = QString::fromStdString(User::UserList[i].password);

        if(username == User::UserList[i].username && pass == User::UserList[i].password)
        {
            user = &User::UserList[i];  //passar a referencia do User
            return true;
        }
    }
    user = NULL;
    return false;   //could not find username and password matching
}




void User::addExerciseToNewModel(Exercise& exercise)
{
    for(int32_t i = 0; i < newModel.exerciseList.size(); i++)
    {
        if(exercise.getId() == newModel.exerciseList[i].getId())
        return;
    }
    this->newModel.exerciseList.push_back(exercise);
}


int32_t User::addNewModel(const string name)
{
    if(name == "")
        return USER_ERR_TRAIN_NAME_INVAL;

    for(int32_t i = 0; i < userTrainingList.size(); i++)
    {
        if(userTrainingList[i].getName() == name)
        {
            return USER_ERR_TRAIN_NAME_EXISTS;
        }
    }
    newModel.setName(name);
    userTrainingList.push_back(newModel);
    return 0;
}

void User::populateUserTrainingList()
{

}

int32_t User::setToPlayTraining(const string& name)
{
    for(int32_t i = 0; i < this->userTrainingList.size(); i++)  //search for the training based on name
    {
        if(userTrainingList[i].getName() == name)
        {
            this->toPlay = userTrainingList[i];
            return 0;
        }
    }
    return USER_ERR_TRAIN_NAME_INVAL;
}

// --------------------- Used to populate -------------------------------
bool User::addUserToUserList(User& user)
{
    user.userId = User::userIDcount;
    User::userIDcount++;
    User::UserList.push_back(user);
    return true;
}

bool User::addUserToUserListFromDatabase(const User& user)
{
    User::UserList.push_back(user);
    return true;
}


void User::printUserList()
{
    cout << "Comecar a imprimer os users " << endl;
    for(uint32_t i = 0; i < User::UserList.size(); i++)
    {
        cout << User::UserList[i].name << endl;
        cout << User::UserList[i].username << endl;
        cout << User::UserList[i].userId   << endl << endl;
    }
}
