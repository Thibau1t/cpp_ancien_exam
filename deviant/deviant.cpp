#include <algorithm>

#include "deviant.hpp"


/* Personne */
Personne::Personne(const std::string & n) : _nom(n) {
    _type = TYPE::PERSONNE;
    CITE.addPersonne(this);
}

Personne::~Personne() {
    CITE.removePersonne(this);
    Individu::decrementCompteur();
}

const std::string & Personne::getNom() const {
    return _nom;
}

TYPE Personne::getType() const {
    return _type;
}


void Personne::setNom(const std::string & n) {
    _nom = n;
}

void Personne::afficher(std::ostream & os) const {
    os << _nom << " " << _id;
}

std::ostream &  operator<<(std::ostream & os, const Personne & p) {
    os << p._nom << " " << p._id;
    return os;
}

/* Individu */

int Individu::COMPTEUR=0;

Individu::Individu() : _id(COMPTEUR + 1) {
    ++ COMPTEUR;
    _type = TYPE::DEVIANT; // change si besoin
}

int Individu::getCompteur() {return COMPTEUR;}
void Individu::decrementCompteur() {--COMPTEUR;}

int Individu::getId() const {return _id;}

TYPE Individu::getType() const {
    throw IllegalException();
}

void Individu::afficher(std::ostream & os) const {
    os << _id;
}

std::ostream &  operator<<(std::ostream & os, const Individu & i) {
    os << i._id;
    return os;
}

/* Cite */

Cite::~Cite() {

}

int Cite::size() const{
    return _personnes.size();
}

/*
Cite & getCite() {
    return CITE;
}
*/

void Cite::addPersonne(Personne * p) {
    _personnes.push_back(p);
}

void Cite::removePersonne(const Personne* p) {
    auto it = std::find(_personnes.begin(), _personnes.end(), p);

    if (it != _personnes.end()) {
        _personnes.erase(it);
    }
}


/* Deviant */

Deviant::Deviant(const Personne & p, const std::string & o) : _obs(o) {
    CITE.removePersonne(&p);
    _id = p.getId();
    _type = TYPE::DEVIANT;
}

std::string Deviant::getObs() const {
    return _obs;
}

void Deviant::setObs(const std::string & o) {
    _obs = o;
}

bool Deviant::operator<(const Deviant & o) const {
    return _obs < o._obs;
}

bool Deviant::operator>(const Deviant & o) const {
    return _obs > o._obs;
}
TYPE Deviant::getType() const {
    return _type;
}


/* Covid */

void Covid::push(Deviant & d) {
    _deviants.push_back(&d);
    std::sort(_deviants.begin(), _deviants.end(), 
              [] (Deviant * d1, Deviant * d2) {return d1->getObs() < d2->getObs(); });
}

void Covid::pop() {
    _deviants.pop_back();
}
Deviant & Covid::top() const {
    return *_deviants.back();
}