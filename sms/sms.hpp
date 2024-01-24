#ifndef __SMS
#define __SMS

#include <iostream>
#include <vector>
#include <algorithm>


class Reseau ;
class Message;
class MMS;

class Telephone {
private :
    std::string _numero;
    Reseau * _r;
    int _nbMessages;

public :
    Telephone(std::string num = "");
    Telephone(std::string num, Reseau * r);

    const std::string & getNumero() const;
    Reseau * getReseau() const; 
    int getNbMessages() const;

    void setNumero(const std::string &);

    void textoter(std::string, std::string); 
    void mmser(std::string, MMS *);

    bool operator<(const Telephone & t) const;
};


class MauvaisNumero : public std::invalid_argument {
public:
    MauvaisNumero() : std::invalid_argument("mauvais numero") {}
};


class Reseau {
private :
    std::vector <Telephone> _telephones;

public :
    Reseau();
    void ajouter(std::string);
    std::string lister();

    Telephone & trouveTel(std::string);
};


class Message {

protected :
    std::string _expediteur;
    std::string _destinataire;
    std::string _date;

    const int _id;

private :
    static int CLE;

public :
    Message(std::string &, std::string &, std::string &);
    virtual ~Message();

    virtual std::string afficher()=0;

    static int getCle();
    int getId() const ;
};

class SMS : public Message {
protected :
    std::string _texte;
public :
    SMS(std::string, std::string, std::string);
    
    void setTexte(std::string);
    std::string getTexte();
    std::string afficher() override ;
};


class Media {
private :

public :
    virtual ~Media() {};    

    virtual std::string afficher() const = 0;
};

class Image : public Media {
public:
    std::string afficher() const override {
        return "[[image]]";
    }
};

class Son : public Media {
public:
    std::string afficher() const override {
        return "[[son]]";
    }
};

class Video : public Media {
public:
    std::string afficher() const override {
        return "[[video]]";
    }
};

class MMS : public SMS {
private :
    std::vector <Media *> _m;
    std::string _de;
    std::string _a;
public : 
    MMS(std::string e, std::string d, std::string date) : SMS(e, d, date) {
    }

    ~MMS() {
        for (auto elt : _m) {
            delete elt;
        }
    }

    void joindre(Media *m) {
        _m.push_back(m);
    }

    std::string afficher() override {
        std::string res = _texte;
        for (auto elt : _m) {
            res += (elt ? elt->afficher() : "");
        }
        return res;
    }

    void setDe(std::string de) {
        _de = de;
    }

    void setA(std::string a) {
        _a = a;
    }

    std::string getDe() {
        return _de;
    }

    std::string getA() {
        return _a;
    }
};
#endif

