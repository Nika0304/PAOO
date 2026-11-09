#ifndef HOME_FOR_SALE_H
#define HOME_FOR_SALE_H

#include <string>

// Item 6: interzic functiile generate de compilator pe care nu le vreau
// o casa e unica, deci o copie nu are sens

// varianta C++11: = delete
class HomeForSale
{
public:
    HomeForSale() = default;  // l-am declarat pentru ca, odata ce declar un copy constructor, nu se mai genereaza
    explicit HomeForSale(const std::string& newAddress);

    HomeForSale(const HomeForSale&) = delete;
    HomeForSale& operator=(const HomeForSale&) = delete;

    const std::string& getAddress() const;

private:
    std::string address = "adresa necunoscuta";
};

// varianta C++98 din carte: declarate private si nedefinite
// din afara clasei da eroare de acces, iar din interior (membri sau friend) eroare la linking
class HomeForSale98
{
public:
    explicit HomeForSale98(const std::string& newAddress);

    const std::string& getAddress() const;

private:
    HomeForSale98(const HomeForSale98&);             // declarat, nedefinit
    HomeForSale98& operator=(const HomeForSale98&);  // declarat, nedefinit

    std::string address;
};

// alta varianta din carte: clasa de baza care nu poate fi copiata
class Uncopyable
{
protected:
    Uncopyable()
    {
    }
    ~Uncopyable()
    {
    }

private:
    Uncopyable(const Uncopyable&);             // declarat, nedefinit
    Uncopyable& operator=(const Uncopyable&);  // declarat, nedefinit
};

// nu scriu nimic despre copiere, dar compilatorul nu poate genera copierea
// pentru ca ar trebui sa copieze baza Uncopyable, iar aceea e privata
class Account : private Uncopyable
{
public:
    explicit Account(double newBalance);

    double getBalance() const;

private:
    double balance;
};

#endif
