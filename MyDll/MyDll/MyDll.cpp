#include "pch.h"
#include "MyDll.h"
#include "opencv2/opencv.hpp"
#include <string>
#include <ctime>
#include <thread>

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
	cap.release();

	destroyAllWindows();
}

void startRecord(string URL) {
	VideoCapture cap(URL);
	if (!cap.isOpened()) {
		return;
	}

	string VideoPath = "C:\\Users\\yehch\\Videos\\";
	int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);

	VideoWriter video(VideoPath + "record.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(frame_width, frame_height));

	Mat frame;
	int cnt_frame = 0;
	while (cnt_frame < 3000000) {
		bool ret = cap.read(frame);
		if (!ret) {
			break;
		}
		video.write(frame);
		cnt_frame++;
	}
	cap.release();
	video.release();
	return;
}

void Input::recordVideo() {
	thread t(startRecord, this->rtmpURL);
	t.detach();
	return;
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

extern "C" __declspec(dllexport) void recordVideo(Input * input) {
	input->recordVideo();
	return;
}