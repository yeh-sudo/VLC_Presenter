#include <string>
using namespace std;

class Input {
	string rtmpURL;
	int len;
public:
	Input(unsigned char* URL, int len);
	int getURLLen();
	void openURL();
	void recordVideo();
};