#ifndef CONTAINER_H
#define CONTAINER_H

#include <QList>
#include "ThreadWithMessages.h"
class Person;

/**
 * @brief Représente un conteneur de Person.
 * @see Person
 */
class Container : public ThreadWithMessages
{
public:
    /**
     * @brief Construit un conteneur de Person.
     */
    Container();
    /**
     * @brief Detruit un conteneur de Person.
     */
    virtual ~Container();
    /**
     * @brief Retourne la liste des Person contenues dans le conteneur.
     * @return la liste des Person contenues dans le conteneur
     */
    QList<Person*> persons();
    /**
     * @brief Fait entrer une personne dans le conteneur.
     * @param la personne à ajouter au conteneur
     */
    void enter(Person*);
    /**
     * @brief Fait sortir une personne dans le conteneur.
     * @param la personne à faire sortir du conteneur
     */
    void quit(Person*);
private:
    QList<Person*> m_persons;
    pthread_mutex_t m_mutexContainer;
};

#endif // CONTAINER_H
