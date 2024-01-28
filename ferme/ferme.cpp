#include "ferme.hpp"

/* Produit */

Produit::Produit(const std::string & n) : _nom(n) {}

const std::string & Produit::getNom() const { return _nom;}

bool Produit::isEqual(const Produit & o) const { return _nom == o._nom; }

bool operator==(const Produit & p1, const Produit &p2) {
    return p1.isEqual(p2);
}

std::ostream & operator<<(std::ostream & os, const Produit & p) {
    os << p._nom;
    return os;
}

/* Animal */

int Animal::COMPTEUR=0;

Animal::Animal(const std::string & n) : _surnom(n), _malade(false) {
    ++ COMPTEUR;
    _type = "Animal";
}

Animal::~Animal() {
    // -- COMPTEUR;
}

Animal::Animal(const Animal & o) {
    _surnom = o._surnom;
    _malade = o._malade;
    ++ COMPTEUR;

} 

const std::string & Animal::getNom() const {
    return _surnom;
}


const std::string & Animal::getType() const {
    return _type;
}


void Animal::setMalade(bool b) {
    _malade = b;
}

Produit Animal::produire() const {
    if (_malade) throw PeutPasProduireException();
    else return Produit("rien");
}

int Animal::getCompteur() {return COMPTEUR;}

Animal & Animal::operator=(const Animal & o) {
    if (this != &o) {
        _surnom = o._surnom;
        _malade = o._malade;
        ++ COMPTEUR;
    }
    return *this;
}

/* Vache */

Vache::Vache(const std::string & n) : Animal(n) {
    _type = "Vache";
 }

void Vache::meugler(std::ostream & os) const{
    os << "la vache " << _surnom << " meugle";
}


Produit Vache::produire() const {
    if (_malade) throw PeutPasProduireException();
    else return Produit("lait");
}

void Vache::communiquer(std::ostream & os) const {
    meugler(os);
}

/* Poule */

Poule::Poule(const std::string & n) : Animal(n) {
    _type = "Poule";
 }

void Poule::glousser(std::ostream & os) const{
    os << "la poule " << _surnom << " glousse";
}

Produit Poule::produire() const {
    if (_malade) throw PeutPasProduireException();
    else return Produit("oeuf");
}

void Poule::communiquer(std::ostream & os) const {
    glousser(os);
}


/* Ferme */

Ferme::~Ferme() {
    for (auto elt : _animaux) delete elt;
}

int Ferme::size() const { return _animaux.size() ;}

void Ferme::acheter(Animal * a) {
    _animaux.push_back(a);
}


bool Comparer(const Animal* a, const Animal* b) {
    if (a->getType() == b->getType()) {
        return a->getNom() < b->getNom();
    }
    return a->getType() < b->getType();
}



void Ferme::nourrirAnimaux(std::ostream & os) {

    std::sort(_animaux.begin(), _animaux.end(), Comparer);
    
    for (auto elt : _animaux)  {
        elt->communiquer(os);
        os << std::endl;
    }
}

Animal * Ferme::vendre(const std::string & n) {
    for(auto it = _animaux.begin(); it < _animaux.end(); ++it) {
        if ((*it)->getNom() == n) {
            Animal * tmp = *it;
            _animaux.erase(it);
            return tmp;
        }
    }
    return nullptr;
}