/*
 *   Copyright 2011 by Alexandre Mendes <alex.mendes1988@gmail.com>
 *   Copyright 2011 by Bertrand Pages <pages.bertrand@gmail.com>
 *   Copyright 2011 by Guillaume Hormiere <hormiere.guillaume@gmail.com>
 *   Copyright 2011 by Nicolas Noullet <nicolas.noullet@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details
 *
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef MESSAGE_H
#define MESSAGE_H
class ThreadWithMessages;
#include "ThreadWithMessages.h"

/**
 * @brief Représente un message.
 */
class Message
{
public:
    /**
     * @brief Représente le type du message.
     */
    enum TypeMessage {

        /**
         * @brief Envoyé par un tram vers un feu pour demander le passage.
         */
        TramToLightRequest,
        /**
         * @brief Envoyé par un feu vers un tram pour signifier qu'il doit s'arréter.
         */
        LightToTramStop,
        /**
         * @brief Envoyé par un feu vers un tram pour signifier qu'il peut passer.
         */
        LightToTramCross,
        /**
         * @brief Envoyé par un tram vers un feu pour signifier le passage.
         */
        IsCrossed,
        /**
         * @brief Envoyé par un feu vers le feu qui le précède pour signifier que le tram est passé.
         */
        IsFree,
        /**
         * @brief Envoyé par un tram vers un feu pour signifier que les portes sont fermées.
         */
        DoorsClosed,
        /**
         * @brief Envoyé par un tram vers un feu station pour signifier qu'il est arrété.
         */
        IsStopped,
        /**
         * @brief Envoyé par un feu station vers un tram pour signifier qu'il doit gérer l'arrêt en station.
         */
        ManageStationStop,
        /**
         * @brief Envoyé par un tram à ses passagers pour leur indiquer l'arrêt à une station.
         */
        ReachingStation,
        /**
         * @brief Envoyé par un tram aux personnes attendant à la station pour leur indiquer son arrivée.
         */
        TramIncoming,
        /**
         * @brief Envoyé par une personne au tram pour lui indiquer qu'elle monte dedans.
         */
        EnterTram,
        /**
         * @brief Envoyé par une personne au tram pour lui indiquer qu'elle le quitte.
         */
        QuitTram,
        /**
         * @brief Envoyé par une personne à une borne d'achat pour acheter un ticket.
         */
        BuyTicket,
        /**
         * @brief Envoyé par une borne d'achat à une personne pour lui indiquer que le ticket est acheté.
         */
        TicketBought,
        /**
         * @brief Envoyé par une personne à un composteur pour composter un ticket.
         */
        PunchTicket,
        /**
         * @brief Envoyé par un composteur à une personne pour lui indiquer que le ticket est composté..
         */
        TicketPunched
    };
    /**
     * @brief Construit un message.
     * @param Emetteur du message
     * @param Type du message
     */
    Message(ThreadWithMessages*, TypeMessage);
    /**
    * @brief Construit un message.
    * @param Emetteur du message
    * @param Type du message
    * @param Contenu du message
    */
   Message(ThreadWithMessages*, TypeMessage, void *);
    /**
     * @brief Détruit un message.
     */
    virtual ~Message(){}
    /**
     * @brief Retourne l'émetteur du message.
     * @return L'émetteur du message
     */
    ThreadWithMessages * sender();
    /**
     * @brief Change l'émetteur du message.
     * @param L'émetteur du message
     */
    void setSender(ThreadWithMessages*);
    /**
     * @brief Retourne le type du message.
     * @return Type du message.
     */
    TypeMessage type();
    /**
     * @brief Retourne le contenu du message.
     * @return Le contenu du message
     */
    void* content() {return this->m_content;}
private:
    ThreadWithMessages * m_sender;
    TypeMessage m_type;
    void * m_content;
    Message(){}
};

#endif // MESSAGE_H
