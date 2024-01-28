#ifndef ferme__hpp
#define ferme__hpp

#include <iostream>
#include <exception>
#include <vector>
#include <iterator>
#include <algorithm>

class Produit {
  private :
    std::string _nom;

  public :
    Produit(const std::string &);

    const std::string & getNom() const;

    bool isEqual(const Produit &) const;

    friend bool operator==(const Produit &, const Produit &);

    friend std::ostream & operator<<(std::ostream &, const Produit &);
};

class PeutPasProduireException : public std::exception {
  public :
    const char * what() const noexcept { return "peut_pas_produire"; }
};

class Communiquer {
  public :
    virtual ~Communiquer() {}
    virtual void communiquer(std::ostream & os) const=0;
};


class Animal : public Communiquer {
  protected :
    std::string _surnom;
    bool _malade;
    std::string _type;
    static int COMPTEUR; 

  public : 
    Animal(const std::string &);
    virtual ~Animal();
    Animal(const Animal &);

    // sert a rien ;)
    Animal & operator=(const Animal &);

    const std::string & getNom() const;
    const std::string & getType() const;
    static int getCompteur();

    void setMalade(bool);

    virtual Produit produire() const;
};

class Vache : public Animal {
  public :
    Vache(const std::string & n);

    void meugler(std::ostream &) const;

    Produit produire() const override;

    void communiquer(std::ostream & os) const;
};

class Poule : public Animal {
  public :
    Poule(const std::string & n);

    void glousser(std::ostream &) const;

    Produit produire() const override;

    void communiquer(std::ostream & os) const; 
};

class Ferme {
  private :
    std::vector <Animal *> _animaux ;

  public :

    ~Ferme();
    
    int size() const;

    void acheter(Animal *);

    void nourrirAnimaux(std::ostream &);

    Animal * vendre(const std::string &);
};

#endif
