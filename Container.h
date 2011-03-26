#ifndef CONTAINER_H
#define CONTAINER_H

#include <QList>

class Person;

class Container
{
public:
    Container();
    virtual ~Container();
    QList<Person*> persons() const {return this->m_persons;}
    void enter(Person*);
    void quit(Person*);
private:
    QList<Person*> m_persons;
};

#endif // CONTAINER_H
