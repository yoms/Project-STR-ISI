#include "Container.h"
#include "Person.h"
#include <QDebug>

Container::Container(): ThreadWithMessages()
{
    pthread_mutex_init(&m_mutexContainer, NULL);
}

Container::~Container()
{
    while(m_persons.size()) {
        Person * p = m_persons.takeFirst();
        delete p;
    }
}

void Container::quit(Person * p)
{
    pthread_mutex_lock(&m_mutexContainer);
    m_persons.removeAll(p);
    pthread_mutex_unlock(&m_mutexContainer);
}

void Container::enter(Person * p)
{
    pthread_mutex_lock(&m_mutexContainer);
    m_persons.append(p);
    pthread_mutex_unlock(&m_mutexContainer);
}
QList<Person*> Container::persons()
{
    pthread_mutex_lock(&m_mutexContainer);
    QList<Person*> retour = this->m_persons;
    pthread_mutex_unlock(&m_mutexContainer);
    return retour;
}
