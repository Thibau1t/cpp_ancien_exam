// NOM    :  VILLEPREUX Thibault
// PRENOM :

#ifndef __gangster_hpp__
#define __gangster_hpp__

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

class Chef;


class Personne {
protected:
    std::string _nom;
public : 
    Personne(const std::string & n="");
    ~Personne() {}

    std::string getNom() const;
    void setNom(const std::string &);
    void setPersonne(const Personne &);

    bool equals(const Personne &) const;

    
};
const Personne INCONNU = {"INCONNU"}; 


class Gangster: public Personne {
protected :
    int _id;
    int _influence;
    static int NBGANGSTER;

public :
    Gangster(int influence=1);
    virtual ~Gangster() {}

    int getId() const;
    virtual int getInfluence() const;
    Personne getPersonne() const;

    bool operator<(const Gangster &) const;
};

class Chef : public Gangster {
private :
    int _influenceChef;
    std::vector<Gangster *> _vectGangster;

public :
    Chef();
    ~Chef();
    
    int getInfluence() const override;

    void commande(Gangster *);
    void commande(Chef *);

};

class InconnuException : public std::exception {
public :
    InconnuException() {};
    const char * what() {return "personnalite inconnue";}
};


class Famille {
private :
    std::vector <Gangster *> _vectGangster_f;

public :
    Famille();
    ~Famille();

    void ajouter(Gangster *);
    void listePersonnes(std::ostream & os);
    void listeMembres(std::ostream & os);

    friend std::ostream & operator<<(std::ostream & os, Famille &);
};

class FoncteurInf {
public :
    FoncteurInf() {}

    bool operator()(const Gangster * g1, const Gangster * g2) const;



};


#endif
