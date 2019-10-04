#include <iostream>
#include <conio.h>
#include <time.h>

struct Size
{
    unsigned int x;
    unsigned int y;
};

class Frame
{
    private:
    char* characters = NULL;
    char** table = NULL;
    Size tableSize;
    unsigned int numberOfChar;

    public:
    int fillTable()
    {
        if (table != NULL && characters != NULL)
            for (int iy = 0; iy < tableSize.y; ++iy)
                for (int ix = 0; ix < tableSize.x; ++ix)
                    table[iy][ix] = characters[rand()%(numberOfChar)];
        else return 1;
        return 0;
    }

    int showTable() const
    {
        if (table != NULL)
            for (int iy = 0; iy < tableSize.y; ++iy)
            {
                for (int ix = 0; ix < tableSize.x; ++ix)
                    std::cout << table[iy][ix];
                std::cout << "\n";
            }
        else return 1;
        return 0;
    }

    char* getCharacters() const
    {
        return characters;
    }

    unsigned getNumberOfChar() const
    {
        return numberOfChar;
    }

    Size getTableSize() const
    {
        return tableSize;
    }

    char*& operator[](unsigned i) const
        {   return table[i];    }

    Frame(const std::string& _characters, const Size _tableSize = {10, 5}) : tableSize(_tableSize)
    {        
        table = new char*[tableSize.y];
        for (int i = 0; i < tableSize.y; ++i)
            table[i] = new char[tableSize.x];

        numberOfChar = _characters.size();
        
        characters = new char[numberOfChar];

        //powtorki
        unsigned p = 0;
        bool bp = false;
        for (int i = 0; i < numberOfChar; ++i)
        {
            for (int j = 0; j < i; ++j)
                if (_characters[i] == _characters[j])
                {
                    bp = true;
                    ++p;
                    break;
                }
            if (!bp) 
                characters[i - p] = _characters[i];
            bp = false;
        }
        numberOfChar -= p;
    }

    ~Frame()
    {
        if (characters != NULL)
        {
            delete[] characters;
            characters = NULL;
        }

        if (table != NULL)
        {
            for (int i = 0; i < tableSize.y; ++i)
                delete[] table[i];
            delete[] table;
            table = NULL;
        }
    }
};

class Histogram
{
    private:
        const Frame& frame;
        unsigned* sumOfChar = NULL;
        char* characters = NULL;
        unsigned numberOfChar = 0;        

    public:
        int calcHistogram()
        {
            if (&frame == NULL) return 1;
            numberOfChar = frame.getNumberOfChar();
            sumOfChar = new unsigned[numberOfChar];
            for (int i = 0; i < numberOfChar; ++i) sumOfChar[i] = 0;
            characters = frame.getCharacters();
            const Size _tableSize = frame.getTableSize();
            for (int y = 0; y < _tableSize.y; ++y)
                for (int x = 0; x < _tableSize.x; ++x)
                    for (int i = 0; i < numberOfChar; ++i)
                        if (frame[y][x] == characters[i])
                        {
                            ++sumOfChar[i];
                            break;
                        }
            return 0;
        }

        void showHistogram() const
        {
            for (int i = 0; i < numberOfChar; ++i)
            {
                std::cout << characters[i] << ":";
                for (int x = 1; x <= sumOfChar[i]; ++x)
                    std::cout << '=';
                std::cout << '\n';
            }
        }
        Histogram(const Frame& _frame) : frame(_frame) {}
};

int main()
{
    srand(time(NULL));
    std::string table = "@#%&*";
    Size size;

    std::cout << "Znaki podaj: ";
    std::cin >> table;
    std::cout << "Podaj rozmiar tabeli x i y: ";
    std::cin >> size.x >> size.y;
    
    Frame frame(table, size);
    
    if (frame.fillTable() != 0)
        return 1;
    frame.showTable();

    Histogram histogram(frame);
    histogram.calcHistogram();
    histogram.showHistogram();

    getch();
    return 0;
}