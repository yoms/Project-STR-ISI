#ifndef PORTE_H
#define PORTE_H

class Porte
{
public:
    Porte();
    void ouvrir();
    void fermer();
    enum Etat {
        OUVERT = 0,
        FERME,
        BLOQUE
    };
    Etat etat();
private:
    Etat m_etat;
};

#endif // PORTE_H
