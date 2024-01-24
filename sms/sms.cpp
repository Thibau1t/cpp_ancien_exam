#include "sms.hpp"
 

/* TELEPHONE */
Telephone::Telephone(std::string num ) : _numero(num), _r(nullptr), _nbMessages(0) {

}

Telephone::Telephone(std::string num, Reseau *r) : _numero(num), _r(r), _nbMessages(0) {

}

const std::string & Telephone::getNumero() const {
    return _numero;
}

void Telephone::setNumero(const std::string & num) {
    _numero = num;
}


bool Telephone::operator<(const Telephone & t) const {
    return  _numero < t._numero;
}


Reseau * Telephone::getReseau() const {
    return _r;
}

int Telephone::getNbMessages() const {
    return _nbMessages;
}
/* RESEAU */

Reseau::Reseau() { }

void Reseau::ajouter(std::string nv) {
    _telephones.push_back(Telephone(nv, this));

    std::sort(_telephones.begin(), _telephones.end());
}

std::string Reseau::lister() {
    std::string res = "";

    for (auto tel : _telephones) {
        res += tel.getNumero() + "\n";
    }

    return res;
}

Telephone & Reseau::trouveTel(std::string s) {
    auto it = _telephones.begin();
    
    while(it != _telephones.end() && it->getNumero() != s) ++it;

    //if (it == _telephones.end()) throw std::invalid_argument("mauvais numero");
    if (it == _telephones.end()) throw MauvaisNumero();
    return *it;
}

void Telephone::textoter(std::string num, std::string texte) {
    try {
        SMS s(_numero, num, "");
        s.setTexte(texte);
        ++ _nbMessages;

        Telephone& dest = _r->trouveTel(num);

        ++ dest._nbMessages;
    }
    catch (std::exception & e) {

    }
}

void Telephone::mmser(std::string num, MMS * mms) {
    try {
        ++ _nbMessages;

        mms->setDe(_numero);
        Telephone& dest = _r->trouveTel(num);

        mms->setA(dest._numero);
        ++ dest._nbMessages;
    }
    catch (std::exception & e) {

    }
}

/* MESSAGE */

int Message::CLE = 0; 

Message::Message(std::string & exp, std::string & dest, std::string & date) : 
                _expediteur(exp), _destinataire(dest), _date(date), _id(CLE) {
    ++ CLE;
}

Message::~Message() {}

int Message::getCle() {
    return CLE;
}

int Message::getId() const {
    return _id;
}

/* SMS */

SMS::SMS(std::string exp, std::string dest, std::string date) : Message(exp, dest, date) { }

std::string SMS::getTexte() {
    return _texte;
}

void SMS::setTexte(std::string texte) {
    if (texte.size() > 160) throw std::invalid_argument("LE texte doit être inférieu à 160 caracrères.");
    _texte = texte;
}

std::string SMS::afficher() {
    return _texte;
}