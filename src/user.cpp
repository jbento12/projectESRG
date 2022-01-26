#include "user.h"
#include "poseClassification.h"



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

    for(uint32_t i = 0; i < User::UserList.size(); i++)
    {
        if(username == User::UserList[i].username && pass == User::UserList[i].password)
        {
            user = &User::UserList[i];  //passar a referencia do User
            return true;
        }
    }
    user = NULL;
    return false;   //could not find username and password matching
}



void User::addExercise(const Exercise& exercise)
{
    this->userExercisesList.push_back(exercise);
}








// --------------------- Used to populate -------------------------------
bool User::addUserToUserList(User& user)
{
    user.userId = User::userIDcount;
    User::userIDcount++;
    User::UserList.push_back(user);
    return true;
}


void User::populateUserList()
{
    //----------- Just a dummy populate (for now (testing)) -----------
    User aux;

    aux.setName("Luca");
    aux.setUsername("");
    aux.password = "";
    addUserToUserList(aux);

    aux.setName("Valete");
    aux.setUsername("val");
    aux.password = "vare";
    addUserToUserList(aux);

    aux.setName("vanessa");
    aux.setUsername("van");
    aux.password = "ola";
    addUserToUserList(aux);
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
