#include "pch.h"
#include "MyDll.h"
#include "opencv2/opencv.hpp"
#include <string>

using namespace std;
using namespace cv;

Input::Input(char* URL, int len) {
	this->rtmpURL = URL;
	this->len = len;
}

int Input::getURLLen() {
	return this->len;
}

void Input::openURL() {
	string url(this->rtmpURL);

	VideoCapture cap(url);
	if (!cap.isOpened()) {
		this->len = 100;
		return;
	}

	Mat frame;
	while (true) {
		bool ret = cap.read(frame);
		if (!ret) {
			return;
		}
		imshow("live", frame);

		if (waitKey(1) == 'q') {
			break;
		}
	}
}

extern "C" __declspec(dllexport) void* Create(char* URL, int len) {
	return (void*) new Input(URL, len);
}

extern "C" __declspec(dllexport) int getURLLen(Input *input) {
	return input->getURLLen();
}

extern "C" __declspec(dllexport) void openURL(Input *input) {
	input->openURL();
	return;
}