#ifndef __deviant_hpp__
#define __deviant_hpp__

#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
// completer la liste suivant vos besoins

enum class TYPE { PERSONNE, DEVIANT };

class Cite; 

// Utiliser une des versions de Cite
// #define CITE Cite::getCite()
extern Cite CITE;


class Individu{
  protected :
    int _id;
    static int COMPTEUR;
    TYPE _type;

  public :
    Individu();
    virtual ~Individu(){}

    static int getCompteur();
    static void decrementCompteur();
    int getId() const;
    virtual TYPE getType() const;
    
    virtual void afficher(std::ostream &) const;

    friend std::ostream &  operator<<(std::ostream &, const Individu &);

};

class Personne : public Individu{
  private :
    std::string _nom;

  public :
    Personne(const std::string & n="inconnu");
    ~Personne();

    const std::string & getNom() const;
    TYPE getType() const override;

    void setNom(const std::string &);

    void afficher(std::ostream &) const override;

    friend std::ostream &  operator<<(std::ostream &, const Personne &);
};

class IllegalException : public std::exception {

    public :
        const char * what() {return "illegal exception"; }
};


class Cite {
private :
    std::vector<Personne *> _personnes;

public :
    ~Cite();

    int size() const;

    void addPersonne(Personne *);
    void removePersonne(const Personne *);
};

class Deviant : public Individu {
  private :
    std::string _obs;

  public :
    Deviant(const Personne &, const std::string & o="");

    std::string getObs() const;
    TYPE getType() const override;


    void setObs(const std::string &);

    bool operator<(const Deviant &) const;

    bool operator>(const Deviant &) const;
};


class Covid {
  private :
    std::vector <Deviant *> _deviants;

  public :

    void push(Deviant &);

    void pop();

    Deviant & top() const;
};


#endif
