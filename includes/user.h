#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <stdint.h>

using namespace std;

class User
{
public:
    User();
    ~User();

    bool setWeight(float weight);
    bool setHeight(float height);
private:
    string name;
    string username;
    float weight;
    float height;
    int32_t userId;
};










#endif  //USER_H_
