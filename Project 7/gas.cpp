//
//  gas.cpp
//  gas
//
//  Created by Nikhil Isukapalli on 12/6/20.
//

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in a city
const int MAXCOLS = 30;               // max number of columns in a city
const int MAXFLATULANS = 120;         // max number of Flatulans allowed

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class City;  // This is needed to let the compiler know that City is a
             // type name, since it's mentioned in the Flatulan declaration.

class Flatulan
{
  public:
        // Constructor
    Flatulan(City* cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();
    bool possiblyGetConverted();

  private:
    City* m_city;
    int   m_row;
    int   m_col;
};

class Player
{
  public:
        // Constructor
    Player(City *cp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;

        // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();

  private:
    City* m_city;
    int   m_row;
    int   m_col;
    int   m_age;
      // TODO: You'll probably find that a player object needs an additional
      //       data member to support your implementation of the behavior
      //       affected by the player's being blasted with gas.
    int m_health;
};

class City
{
  public:
        // Constructor/destructor
    City(int nRows, int nCols);
    ~City();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    bool    isPlayerAt(int r, int c) const;
    int     flatulanCount() const;
    int     nFlatulansAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;

        // Mutators
    bool  addFlatulan(int r, int c);
    bool  addPlayer(int r, int c);
    void  preachToFlatulansAroundPlayer();
    void  moveFlatulans();

  private:
    int       m_rows;
    int       m_cols;
    Player  * m_player;
    Flatulan* m_flatulans[MAXFLATULANS];
    int       m_nFlatulans;

      // Helper functions
    bool isInBounds(int r, int c) const;
};

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();

        // Mutators
    void play();

  private:
    City* m_city;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Flatulan implementation
///////////////////////////////////////////////////////////////////////////

Flatulan::Flatulan(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** A Flatulan must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "***** Flatulan created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
}

int Flatulan::row() const
{
    return m_row;
}

int Flatulan::col() const
{
    // TODO: TRIVIAL:  Return the column the Flatulan is at.
    return m_col;
}

void Flatulan::move()
{
      // Attempt to move in a random direction; if it can't move, don't move.
      // If the player is there, don't move.
    int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
    // TODO:  Move in the appropriate direction if allowed
    switch (dir) {
        case UP:
            if (!(m_city->player()->row() == m_row-1 &&
                m_city->player()->col() == m_col)) {
                
                m_city->determineNewPosition(m_row, m_col, dir);
            }
            break;
        case DOWN:
            if (!(m_city->player()->row() == m_row+1 &&
                m_city->player()->col() == m_col)) {
                
                m_city->determineNewPosition(m_row, m_col, dir);
            }
            break;
        case LEFT:
            if (!(m_city->player()->row() == m_row &&
                m_city->player()->col() == m_col-1)) {
                
                m_city->determineNewPosition(m_row, m_col, dir);
            }
            break;
        case RIGHT:
            if (!(m_city->player()->row() == m_row &&
                m_city->player()->col() == m_col+1)) {
                
                m_city->determineNewPosition(m_row, m_col, dir);
            }
            break;
        default:
            break;
    }
}

bool Flatulan::possiblyGetConverted()  // return true if converted
{
      // Be converted with 2/3 probability
    // TODO:
    int num = randInt(1, 3);
    if (num == 1 || num == 2) {
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** The player must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_health = 12;
}

int Player::row() const
{
    // TODO: TRIVIAL:  Return the row the player is at.
    return m_row;
}

int Player::col() const
{
    // TODO: TRIVIAL:  Return the column the player is at.
    return m_col;
}

int Player::age() const
{
    // TODO: TRIVIAL:  Return the player's age.
    return m_age;
}

int Player::health() const
{
    // TODO: TRIVIAL:  Return the player's health status.
    return m_health;
}

bool Player::isPassedOut() const
{
    // TODO: TRIVIAL:  Return whether the player is passed out.
    if (health() <= 0) {
        return true;
    }
    return false;
}

void Player::preach()
{
    m_age++;
    m_city->preachToFlatulansAroundPlayer();
}

void Player::move(int dir)
{
    m_age++;
      // TODO:  If there is a grid position in the indicated direction that is
      //        adjacent to the player and vacant, move the player there;
      //        otherwise, don't move.
    switch (dir) {
        case UP:
            if (m_city->nFlatulansAt(row()-1, col()) == 0) {
                m_city->determineNewPosition(m_row, m_col, dir);
            }
            break;
        case DOWN:
            if (m_city->nFlatulansAt(row()+1, col()) == 0) {
                m_city->determineNewPosition(m_row, m_col, dir);
            }
            break;
        case LEFT:
            if (m_city->nFlatulansAt(row(), col()-1) == 0) {
                m_city->determineNewPosition(m_row, m_col, dir);
            }
            break;
        case RIGHT:
            if (m_city->nFlatulansAt(row(), col()+1) == 0) {
                m_city->determineNewPosition(m_row, m_col, dir);
            }
            break;
        default:
            break;
    }
}

void Player::getGassed()
{
    // TODO: TRIVIAL
    m_health--;
}

///////////////////////////////////////////////////////////////////////////
//  City implementations
///////////////////////////////////////////////////////////////////////////

City::City(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** City created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nFlatulans = 0;
}

City::~City()
{
    // TODO:  Delete the player and all remaining dynamically allocated Flatulans.
    delete m_player;
    for (int i = 0; i < m_nFlatulans; i++)
        delete m_flatulans[i];
}

int City::rows() const
{
    // TODO: TRIVIAL:  Return the number of rows in the city.
    return m_rows;
}

int City::cols() const
{
    // TODO: TRIVIAL:  Return the number of columns in the city.
    return m_cols;
}

Player* City::player() const
{
    return m_player;
}

bool City::isPlayerAt(int r, int c) const
{
    // TODO:  Return true if the player is at row r, column c, otherwise false.
    if (player()->row() == r) {
        if (player()->col() == c) {
            return true;
        }
    }
    return false;
}

int City::flatulanCount() const
{
    return m_nFlatulans;
}

int City::nFlatulansAt(int r, int c) const
{
    // TODO:  Return the number of Flatulans at row r, column c.
    int count = 0;
    for (int i = 0; i < m_nFlatulans; i++) {
        if (m_flatulans[i]->row() == r && m_flatulans[i]->col() == c) {
            count++;
        }
    }
    return count;
}

bool City::determineNewPosition(int& r, int& c, int dir) const
{
      // TODO:  If a move from row r, column c, one step in direction dir
      //        would go off the edge of the city, leave r and c unchanged and
      //        return false.  Otherwise, set r or c so that row r, column c,
      //        is now the new position resulting from the proposed move, and
      //        return true.
    switch (dir)
    {
      case UP:
        // TODO:  Implement the behavior if dir is UP.
            if (isInBounds(r-1, c)) {
                r--;
                return true;
            }
            break;
      case DOWN:
            if (isInBounds(r+1, c)) {
                r++;
                return true;
            }
            break;
      case LEFT:
            if (isInBounds(r, c-1)) {
                c--;
                return true;
            }
            break;
      case RIGHT:
        // TODO:  Implement the other directions.
            if (isInBounds(r, c+1)) {
                c++;
                return true;
            }
            break;
      default:
            return false;
    }
    return true;
}

void City::display() const
{
      // Position (row,col) in the city coordinate system is represented in
      // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
        // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';

        // Indicate each Flatulan's position
    // TODO:  If one Flatulan is at some grid point, set the char to 'F'.
    //        If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    for (r = 1; r <= m_rows; r++) {
        for (c = 1; c <= m_cols; c++) {
            if (nFlatulansAt(r, c) == 1) {
                grid[r-1][c-1] = 'F';
            }
            if (nFlatulansAt(r, c) == 2) {
                grid[r-1][c-1] = '2';
            }
            if (nFlatulansAt(r, c) == 3) {
                grid[r-1][c-1] = '3';
            }
            if (nFlatulansAt(r, c) == 4) {
                grid[r-1][c-1] = '4';
            }
            if (nFlatulansAt(r, c) == 5) {
                grid[r-1][c-1] = '5';
            }
            if (nFlatulansAt(r, c) == 6) {
                grid[r-1][c-1] = '6';
            }
            if (nFlatulansAt(r, c) == 7) {
                grid[r-1][c-1] = '7';
            }
            if (nFlatulansAt(r, c) == 8) {
                grid[r-1][c-1] = '8';
            }
            if (nFlatulansAt(r, c) >= 9) {
                grid[r-1][c-1] = '9';
            }
        }
    }

        // Indicate player's position
    if (m_player != nullptr)
    {
          // Set the char to '@', unless there's also a Flatulan there
          // (which should never happen), in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }

        // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

        // Write message, Flatulan, and player info
    cout << "There are " << m_nFlatulans << " unconverted Flatulans remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isPassedOut())
            cout << "The player has passed out." << endl;
        else
            cout << "The player's health level is " << m_player->health() << endl;
    }
}

bool City::addFlatulan(int r, int c)
{
    if (! isInBounds(r, c))
        return false;

      // Don't add a Flatulan on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;

      // If there are MAXFLATULANS unconverted Flatulans, return false.
      // Otherwise, dynamically allocate a new Flatulan at coordinates (r,c).
      // Save the pointer to the newly allocated Flatulan and return true.

      // Your function must work as specified in the preceding paragraph even
      // in this scenario (which won't occur in this game):  MAXFLATULANS
      // Flatulans are added, then some are converted, then more are added.

      // TODO:  Implement this.
    m_flatulans[m_nFlatulans] = new Flatulan(this, r, c);
    m_nFlatulans++;
    return true;
}

bool City::addPlayer(int r, int c)
{
    if (! isInBounds(r, c))
        return false;

      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Don't add a player on a spot with a Flatulan
    if (nFlatulansAt(r, c) > 0)
        return false;

      // Dynamically allocate a new Player and add it to the city
    m_player = new Player(this, r, c);
    return true;
}

void City::preachToFlatulansAroundPlayer()
{
      // Preach to Flatulans orthogonally or diagonally adjacent to player.
      // If a Flatulan is converted, destroy it and remove it from the city,
      // since we have no further need to display it or have it interact with
      // the player.

      // TODO:  Implement this.
    int i = 0;
    while (i < m_nFlatulans) {
        if ((m_flatulans[i]->row() == player()->row() ||
            m_flatulans[i]->row() == player()->row()-1 ||
            m_flatulans[i]->row() == player()->row()+1) &&
            (m_flatulans[i]->col() == player()->col() ||
            m_flatulans[i]->col() == player()->col()-1 ||
            m_flatulans[i]->col() == player()->col()+1) &&
            m_flatulans[i]->possiblyGetConverted()) {
            
            delete m_flatulans[i];
            m_flatulans[i] = m_flatulans[m_nFlatulans-1];
            m_nFlatulans--;
        }
        else {
            i++;
        }
    }
}

void City::moveFlatulans()
{
    for (int k = 0; k < m_nFlatulans; k++)
    {
      // TODO:  Have the k-th Flatulan in the city make one move.
      //        If that move results in that Flatulan being orthogonally
      //        adjacent to the player, the player suffers a gas blast.
        m_flatulans[k]->move();
        if (m_flatulans[k]->row() == player()->row()) {
            if (m_flatulans[k]->col()-1 == player()->col() ||
                m_flatulans[k]->col()+1 == player()->col()) {
                
                player()->getGassed();
            }
        }
        else if (m_flatulans[k]->col() == player()->col()) {
            if (m_flatulans[k]->row()-1 == player()->row() ||
                m_flatulans[k]->row()+1 == player()->row()) {
                
                player()->getGassed();
            }
        }
    }
}

bool City::isInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nFlatulans)
{
    if (nFlatulans < 0)
    {
        cout << "***** Cannot create Game with negative number of Flatulans!" << endl;
        exit(1);
    }
    if (nFlatulans > MAXFLATULANS)
    {
        cout << "***** Trying to create Game with " << nFlatulans
             << " Flatulans; only " << MAXFLATULANS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nFlatulans > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the Flatulans!" << endl;
        exit(1);
    }

        // Create city
    m_city = new City(rows, cols);

        // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_city->addPlayer(rPlayer, cPlayer);

      // Populate with Flatulans
    while (nFlatulans > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
          // Don't put a Flatulan where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_city->addFlatulan(r, c);
        nFlatulans--;
    }
}

Game::~Game()
{
    delete m_city;
}

void Game::play()
{
    m_city->display();
    Player* p = m_city->player();
    if (p == nullptr)
        return;

    while ( ! p->isPassedOut()  &&  m_city->flatulanCount() > 0)
    {
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)  // player preaches
            p->preach();
        else
        {
            switch (action[0])
            {
              default:   // if bad move, nobody moves
                cout << '\a' << endl;  // beep
                continue;
              case 'q':
                return;
              case 'u':
              case 'd':
              case 'l':
              case 'r':
                p->move(decodeDirection(action[0]));
                break;
            }
        }
        m_city->moveFlatulans();
        m_city->display();
    }
    if (p->isPassedOut())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
      case 'u':  return UP;
      case 'd':  return DOWN;
      case 'l':  return LEFT;
      case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

  // Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
      // Create a game
      // Use this instead to create a mini-game:   Game g(3, 4, 2);
    Game g(7, 8, 25);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif
