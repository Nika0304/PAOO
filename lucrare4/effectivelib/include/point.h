#ifndef POINT_H
#define POINT_H

// Item 4: punct fara constructor si fara valori initiale
// x si y nu primesc nicio valoare cand obiectul e creat fara ()
struct BadPoint
{
    int x;
    int y;
};

// punct cu constructori care initializeaza tot in lista de initializare
class GoodPoint
{
public:
    GoodPoint();
    GoodPoint(int px, int py);

    int getX() const;
    int getY() const;

private:
    int x;
    int y;
};

#endif
