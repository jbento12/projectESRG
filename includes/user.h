#ifndef user__H
#define user__H

#include <string>
#include <pthread.h>

using namespace std;

class user
{
    string user_id;
    string user_name;
    int user_weight;
    int user_age;

    public:

    user();
    ~user();
    
};









#endif