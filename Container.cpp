#include "Container.h"

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
    m_persons.removeAt(m_persons.indexOf(p));
}

void Container::enter(Person * p)
{
    m_persons.append(p);
}
