#include <Multiplicative.h>
#include <iostream>

using namespace std;

int main()
{
	int w,x,y,z;
	cout << "Enter min value: ";
	cin >> w; 
	cout << "Enter max value: ";
	cin >> x;
	cout << "Enter seed: ";
	cin >> y;
	cout << "Enter multiplier: ";
	cin >> z;

	SSPRNG::multRandom rng(w,x,y,z);

	for(int i = 0; i < 100; i++)
	{
		cout << rng.nextInt() << " ";
	}
	cout << "\n";

	return(1);
}