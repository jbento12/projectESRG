#ifndef EXERCISE_H_
#define EXERCISE_H_

#include <iostream>
#include <stdint.h>

using namespace std;


class Exercise
{
public:
    Exercise();
    ~Exercise();

    bool setName(const string& name);
    bool setPath(const string& path);

    string getName();
    string getPath();

private:
    string name;
    string path;
    int32_t id;
};







#endif //EXERCISE_H_
