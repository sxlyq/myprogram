#ifndef LOCATION_H
#define LOCATION_H


class Location
{
public:
    Location(int r, int c);
    bool operator==(const Location & loc);
    int getRow() const;

    int getCol() const;

    void setRow(int value);

    void setCol(int value);

private:
    int row, col;
};

#endif // LOCATION_H
