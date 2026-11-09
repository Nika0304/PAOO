#include "home_for_sale.h"

HomeForSale::HomeForSale(const std::string& newAddress) : address(newAddress)
{
}

const std::string& HomeForSale::getAddress() const
{
    return address;
}

HomeForSale98::HomeForSale98(const std::string& newAddress) : address(newAddress)
{
}

const std::string& HomeForSale98::getAddress() const
{
    return address;
}

Account::Account(double newBalance) : balance(newBalance)
{
}

double Account::getBalance() const
{
    return balance;
}
