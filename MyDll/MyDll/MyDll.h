#include <string>
using namespace std;

class Input {
	char* rtmpURL;
	int len;
public:
	Input(char* URL, int len);
	int getURLLen();
	void openURL();
};