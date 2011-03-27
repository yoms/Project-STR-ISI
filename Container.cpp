#include "Container.h"
#include "Person.h"

Container::Container()
{

}

Container::~Container()
{
    while(m_persons.size()){
        Person * p = m_persons.takeFirst();
        delete p;
    }
}

void Container::quit(Person * p)
{
    m_persons.removeAll(p);
}

void Container::enter(Person * p)
{
    m_persons.append(p);
}
