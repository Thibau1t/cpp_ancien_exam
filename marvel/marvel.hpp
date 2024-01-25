#ifndef marvel__hpp
#define marvel__hpp

#include <iostream>
#include <cstring>
#include <exception>
#include <vector>
#include <iterator>
#include <algorithm>



class Capacite;

class Personne {

public:
    enum Genre {HOMME, FEMME, INDETERMINE};

    Personne(std::string="", std::string="", Personne::Genre = INDETERMINE);
    virtual ~Personne() {}

    std::string getNom() const;
    std::string getPrenom() const;
    Personne::Genre getGenre() const;

    std::ostream & afficher(std::ostream &);

    static Personne INCONNU;

    bool operator==(const Personne &) const;
    std::ostream & operator<<(std::ostream & os) const;

    friend std::ostream & operator<<(std::ostream & os, const Personne & personne);


    virtual void setNom(std::string);
    void getPrenom(std::string);
    void getGenre(Personne::Genre);
 
    

protected :
    std::string _prenom;
    std::string _nom;
    Personne::Genre _genre; 

};


class Super : public Personne{
private :
    std::string _nom_hero;
    bool _anonyme;
    int _sommeNiveau;
    std::vector <Capacite *> _vector_capa;

public :
    Super(std::string, Personne);
    ~Super();
    Super(const Super &other);

    std::string getNom() const;
    Personne & getIdentite();
    int getNiveau();
    int getSommeNiveau() const;
    bool estAnonyme() const;

    void setIdentite(const Personne &);
    void setNom(const std::string &);

    void enregistrer();

    void ajouter(Capacite *);

    Super& operator=(const Super &other);
};

class AnonymeException : public std::exception {
public :
    AnonymeException() : std::exception() {}

    const char * what() {
        return "identite anonyme";
    }
};


class Capacite {
protected :
    std::string _nom;
    int _niveau;


public :
    Capacite(std::string, int);
    virtual ~Capacite();

    virtual void utiliser(std::ostream &);

    virtual void abstract() const =0;

    int getNiveau();
    std::string getNom() const;

    virtual Capacite* clone() const = 0;
};


class Physique  :public Capacite {
public :
    Physique(std::string, int);

    void abstract () const override{};

    void exercer(std::ostream &);
    void utiliser(std::ostream &) override;

    virtual Physique* clone() const override {
        return new Physique(*this);
    }
};


class Psychique  :public Capacite {
public :
    Psychique(std::string, int);


    void abstract () const override{};

    void penser(std::ostream &);
    void utiliser(std::ostream &) override;

    virtual Psychique* clone() const override {
        return new Psychique(*this);
    }
};


class Materiel  :public Capacite {
public :
    Materiel(std::string, int);

    void abstract () const override{};

    void actionner(std::ostream &);
    void utiliser(std::ostream &) override;

    virtual Materiel* clone() const override {
        return new Materiel(*this);
    }
};


class Equipe {
private :
    std::string _nom_eq;
    int _niv_eq;
    std::vector<Super *> _vector_super;

public :
    Equipe(const std::string &);
    ~Equipe();

    int getNombre() const;
    int getNiveau() const;

    void ajouter(Super *);
};


#endif
 