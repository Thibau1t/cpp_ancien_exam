#include "marvel.hpp"

/* PERSONNE */
// var static
Personne Personne::INCONNU = {"Inconnu", "Inconnu", Personne::INDETERMINE};

Personne::Personne(std::string prenom, std::string nom, Personne::Genre genre) :
        _prenom(prenom), _nom(nom), _genre(genre) {}


std::string Personne::getNom() const {
    return _nom;
}

std::string Personne::getPrenom() const {
    return _prenom;
}


Personne::Genre Personne::getGenre() const {
    return _genre;
}


std::ostream & Personne::afficher(std::ostream & os){
    os << _prenom << " " << _nom << " [";
    if (_genre == HOMME)             os << "HOMME";
    else if (_genre == FEMME)        os << "FEMME";
    else if (_genre == INDETERMINE)  os << "INDETERMINE";
    os << "]";

    return os;
}

bool Personne::operator==(const Personne & o) const{
    return (_nom == o._nom && _prenom == _prenom && _genre==o._genre);
}


std::ostream & Personne::operator<<(std::ostream & os) const{
    os << _prenom << " " << _nom << " [";
    if (_genre == HOMME)             os << "HOMME";
    else if (_genre == FEMME)        os << "FEMME";
    else if (_genre == INDETERMINE)  os << "INDETERMINE";
    os << "]";

    return os;
}

std::ostream & operator<<(std::ostream & os, const Personne & personne) {
    os << personne.getNom() << " " << personne.getPrenom() << " [";
    if (personne.getGenre() == Personne::HOMME)
        os << "HOMME";
    else if (personne.getGenre() == Personne::FEMME)
        os << "FEMME";
    else if (personne.getGenre() == Personne::INDETERMINE)
        os << "INDETERMINE";
    os << "]";
    return os;
}


void Personne::setNom(std::string n) {
    _nom = n;
}

void Personne::getPrenom(std::string p) {
    _prenom = p;
}

void Personne::getGenre(Personne::Genre g) {
    _genre = g;
}


/* SUPER */

Super::Super(std::string nomh, Personne p) : Personne(p),  _nom_hero(nomh), _anonyme(true), _sommeNiveau(0), _vector_capa(){

}

Super::~Super() {
    
    for (auto elt : _vector_capa)  {
        if (elt != nullptr) 
            delete elt;
    }
    
}

std::string Super::getNom() const {
    return _nom_hero;
}

int Super::getNiveau() {
    return _sommeNiveau;
}

int Super::getSommeNiveau() const {
    return _sommeNiveau;
}

void Super::setIdentite(const Personne & p) {
    _nom = p.getNom();
    _prenom = p.getPrenom();
    _genre = p.getGenre();
    _anonyme = true;
    
}

void Super::setNom(const std::string & n) {
    _nom_hero = n;
    
}

Personne & Super::getIdentite() {
    if (_anonyme == true ) throw AnonymeException();
    return *this;
}


bool Super::estAnonyme() const{
    return _anonyme;
}

void Super::enregistrer() {
    _anonyme = false;
}

void Super::ajouter(Capacite * c) {
    _vector_capa.push_back(c);
    _sommeNiveau += c->getNiveau();
}

Super::Super(const Super &other) : 
    Personne(other), _nom_hero(other._nom_hero), _anonyme(other._anonyme), _sommeNiveau(other._sommeNiveau), _vector_capa() {
    for (auto elt : other._vector_capa) {
        if (elt != nullptr) {
            // Perform a deep copy by creating new instances of the elements
            _vector_capa.push_back(elt->clone());
        } else {
            _vector_capa.push_back(nullptr);
        }
    }
}

// Dans la classe Super
Super& Super::operator=(const Super &other) {
    if (this != &other) {
        // Effacez les anciennes ressources
        for (auto elt : _vector_capa) {
            delete elt;
        }
        _vector_capa.clear();

        // Copiez les données de l'autre objet
        Personne::operator=(other);
        _nom_hero = other._nom_hero;
        _anonyme = other._anonyme;
        _sommeNiveau = other._sommeNiveau;

        // Effectuez une copie profonde des objets Capacite
        for (auto elt : other._vector_capa) {
            if (elt != nullptr) {
                _vector_capa.push_back(elt->clone());
            } else {
                _vector_capa.push_back(nullptr);
            }
        }
    }
    return *this;
}


/* CAPACITE */

Capacite::Capacite(std::string nom, int niveau) : _nom(nom), _niveau(niveau) {}

Capacite::~Capacite() {

}

void Capacite::utiliser(std::ostream & s) {
    s << _nom << " [" << _niveau << "]";
}

int Capacite::getNiveau() {
    return _niveau;
}

std::string Capacite::getNom() const{
    return _nom;
}

/* PHYSIQUE */

Physique::Physique(std::string nom, int niveau) : Capacite(nom, niveau) {}

void Physique::exercer(std::ostream & s) {
    s << _nom << " [" << _niveau << "]";
}

void Physique::utiliser(std::ostream & s) {
    this->exercer(s);
}

/* PSYCHIQUE */

Psychique::Psychique(std::string nom, int niveau) : Capacite(nom, niveau) {}

void Psychique::penser(std::ostream & s) {
     s << _nom << " [" << _niveau << "]";
}

void Psychique::utiliser(std::ostream & s) {
    this->penser(s);
}

/* MATERIEL */
Materiel::Materiel(std::string nom, int niveau) : Capacite(nom, niveau) {}

void Materiel::actionner(std::ostream & s) {
    s << _nom << " [" << _niveau << "] en action";
}

void Materiel::utiliser(std::ostream & s) {
    this->actionner(s);
}


/* EQUIPE */
Equipe::Equipe(const std::string & n) : _nom_eq(n), _niv_eq(0) { }

Equipe::~Equipe() {
    for (auto elt : _vector_super) {
        delete elt;
    }
}

int Equipe::getNombre() const {
    return _vector_super.size();
}

int Equipe::getNiveau() const {
    return _niv_eq;
}

void Equipe::ajouter(Super * s) {
    _vector_super.push_back(s);
    _niv_eq += s->getNiveau();
}


