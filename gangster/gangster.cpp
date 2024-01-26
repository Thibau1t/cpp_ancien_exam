#include "gangster.hpp"

/* PERSONNE */
Personne::Personne(const std::string & n) : _nom(n) { } 

std::string Personne::getNom() const {
    return _nom;
}

void Personne::setNom(const std::string & n) {
    _nom = n;
}

bool Personne::equals(const Personne & p) const {
    return _nom == p._nom;
}

void Personne::setPersonne(const Personne & p) {
    _nom = p._nom;
}


/* GANGSTER */

int Gangster::NBGANGSTER = 1;

Gangster::Gangster(int influence) : _id(NBGANGSTER), _influence(influence) {
    ++ NBGANGSTER;
}

int Gangster::getId() const {
    return _id;
}

int Gangster::getInfluence() const {
    return _influence;
}

Personne Gangster::getPersonne() const {
    if (this->getNom() == "") throw InconnuException();
    else return (*this);
}


bool Gangster::operator<(const Gangster & o) const {
    if (this->getInfluence() <  o.getInfluence()) return true;
    if (this->getInfluence() == o.getInfluence()) return (this->getId() > o.getId());
    return false;
}


/* Chef */

Chef::Chef() : _influenceChef(1) {}

Chef::~Chef() {
    // for (auto elt : _vectGangster) delete elt;
}

int Chef::getInfluence() const {
    return _influenceChef;
}

void Chef::commande(Gangster * g) {
    if (_influenceChef == 1) _influenceChef +=10;
    else _influenceChef += g->getInfluence();

    _vectGangster.push_back(g);
}

void Chef::commande(Chef * c) {
    if (_influenceChef == 1) _influenceChef +=9;
    _influenceChef += c->_influenceChef;


    for (auto elt : c->_vectGangster){
        _vectGangster.push_back(elt);
    }
}

/* FAMILLE */

Famille::Famille() {}

Famille::~Famille() {
    for (auto elt : _vectGangster_f) delete elt;
}

void Famille::ajouter(Gangster * g) {
    _vectGangster_f.push_back(g);
}


void Famille::listePersonnes(std::ostream & os) {
    std::sort(_vectGangster_f.begin(), _vectGangster_f.end(), 
               [](Gangster *gangster1, Gangster *gangster2){return gangster1->getNom() < gangster2->getNom();});
    
    bool first = true;
    for (auto it : _vectGangster_f) {
        if (it->getNom() != "") {
            if (!first)  os << ", ";
            else first = false;
            os << it->getNom();
        }
    }
}

void Famille::listeMembres(std::ostream & os) {
    
    std::sort(_vectGangster_f.begin(), _vectGangster_f.end(), FoncteurInf());
    std::reverse(_vectGangster_f.begin(), _vectGangster_f.end());
    
    bool first = true;
    for (auto it : _vectGangster_f) {
        if (!first)  os << " ";
        else first = false;
        os << it->getId();
    }
}

std::ostream & operator<<(std::ostream & os, Famille & f) {
    f.listePersonnes(os);
    return os;
}

/* FONCTEUR INF */


bool FoncteurInf::operator()(const Gangster * g1, const Gangster * g2) const {
    if (g1->getInfluence() <  g2->getInfluence()) return true;
    if (g1->getInfluence() == g2->getInfluence()) return g1->getId() > g2->getId();
    return false;
}
