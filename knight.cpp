//
// knight.cpp : by devej
//

#include <stdio.h>


const int HEIGHT = 4;
const int WIDTH = 5;
long SequenceCount = 0;


char Keypad[HEIGHT][WIDTH] = {
	{'A', 'B', 'C', 'D', 'E'},
	{'F', 'G', 'H', 'I', 'J'},
	{'K', 'L', 'M', 'N', 'O'},
	{' ', '1', '2', '3', ' '}
};


bool Vowels[HEIGHT][WIDTH] = {
	{1, 0, 0, 0, 1},
	{0, 0, 0, 1, 0},
	{0, 0, 0, 0, 1},
	{0, 0, 0, 0, 0}
};


struct Sequence
{
	Sequence() : length(0), vcount(0) {}

	int length;
	int vcount;
};


struct Point
{
	Point( int yval, int xval ): y(yval), x(xval) {}

	int y;
	int x;
};



void PrintKeyPad()
{
	for( int y = 0; y < HEIGHT; ++y )
	{
		for( int x = 0; x < WIDTH; ++x )
		{
			printf( "%c", Keypad[y][x] );
		}
		printf( "\n" );
	}
	printf ("\n" );
}



bool IsValidLocation( const int y, const int x )
{
	if( (y >= 0) && (y < HEIGHT) ) {
		if( (x >= 0) && (x < WIDTH) ) {
			if( ' ' != Keypad[y][x] ) {		// skip empty cells
				return true;
			}
		}
	}

	return false;
}



void FindAllMovesFrom( Point& p, Sequence seq  )
{
	++seq.length;
	seq.vcount += Vowels[p.y][p.x];

	if( seq.vcount > 2 ) {
		return;  // too many vowels, return w/out counting
	}

	if( seq.length == 10 ) {
		++SequenceCount;
		return;
	}


	// There are eight posssibe moves for a knight centered in a 5x5
	// grid.  I could write this testing in a loop, but it's probably
	// quicker to just write it unrolled, testing each possibility
	// and recording the results.  It also looks like more readable
	// code to me.

	// clockwise, starting from the north, or 12

	// 1
	if( IsValidLocation( p.y + 2, p.x + 1 ) ) {
		FindAllMovesFrom( Point( p.y+2, p.x+1 ), seq );
	}

	// 2
	if( IsValidLocation( p.y + 1, p.x + 2 ) ) {
		FindAllMovesFrom( Point( p.y+1, p.x+2 ), seq );
	}

	// 3
	if( IsValidLocation( p.y - 1, p.x + 2 ) ) {
		FindAllMovesFrom( Point( p.y-1, p.x+2 ), seq );
	}

	// 4
	if( IsValidLocation( p.y - 2, p.x + 1 ) ) {
		FindAllMovesFrom( Point( p.y-2, p.x+1 ), seq );
	}

	// 5
	if( IsValidLocation( p.y - 2, p.x - 1 ) ) {
		FindAllMovesFrom( Point( p.y-2, p.x-1 ), seq );
	}

	// 6
	if( IsValidLocation( p.y - 1, p.x - 2 ) ) {
		FindAllMovesFrom( Point( p.y-1, p.x-2 ), seq );
	}

	// 7
	if( IsValidLocation( p.y + 1, p.x - 2 ) ) {
		FindAllMovesFrom( Point( p.y+1, p.x-2 ), seq );
	}

	// 8
	if( IsValidLocation( p.y + 2, p.x - 1 ) ) {
		FindAllMovesFrom( Point( p.y+2, p.x-1 ), seq );
	}
}


int main( int argc, char* argv[] )
{
	//PrintKeyPad();

	// walk the Keypad array
	for( int y = 0; y < HEIGHT; ++y )
	{
		for( int x = 0; x < WIDTH; ++x )
		{
			// skip empty cells
			if( ' ' == Keypad[y][x] )
				continue;

			Sequence seq;
			FindAllMovesFrom( Point(y, x), seq );
		}
	}


	printf( "Found %d 10-key sequences with a 2 vowel limit\n", SequenceCount );

	return 0;
}
