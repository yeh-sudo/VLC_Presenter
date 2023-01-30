#include "pch.h"
#include "MyDll.h"
#include "opencv2/opencv.hpp"
#include <string>

using namespace std;
using namespace cv;

Input::Input(unsigned char* URL, int len) {
	for (int i = 0; i < len; i++) {
		this->rtmpURL += (char)URL[i];
	}
	this->len = len;
}

int Input::getURLLen() {
	return this->len;
}

void Input::openURL() {
	VideoCapture cap(this->rtmpURL);
	if (!cap.isOpened()) {
		return;
	}

	Mat frame;
	while (true) {
		bool ret = cap.read(frame);
		if (!ret) {
			break;
		}
		imshow("live", frame);

		if (waitKey(1) == 'q') {
			break;
		}
	}
}

extern "C" __declspec(dllexport) void* Create(unsigned char* URL, int len) {
	return (void*) new Input(URL, len);
}

extern "C" __declspec(dllexport) int getURLLen(Input *input) {
	return input->getURLLen();
}

extern "C" __declspec(dllexport) void openURL(Input *input) {
	input->openURL();
	return;
}