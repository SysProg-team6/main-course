#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <vector>

using namespace std;

template <typename T>

class Repository
{
public:
    virtual vector<T> findAll() = 0;
    virtual T find(int id) = 0;
    virtual void insert(T item) = 0;
    virtual void update(T item) = 0;
    virtual void remove(T item) = 0;

private:

};

#endif // REPOSITORY_H
