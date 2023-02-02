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

void startRecord(string URL, int n) {
	VideoCapture cap(URL);
	if (!cap.isOpened()) {
		return;
	}

	string VideoPath = "C:\\Users\\yehch\\Videos\\";
	int frame_width = cap.get(CAP_PROP_FRAME_WIDTH);
	int frame_height = cap.get(CAP_PROP_FRAME_HEIGHT);
	double fps = cap.get(CAP_PROP_FPS);

	VideoWriter video(VideoPath + "record" + to_string(n) + ".mp4", cv::VideoWriter::fourcc('X', 'V', 'I', 'D'), fps, Size(frame_width, frame_height));

	Mat frame;
	int total_frame = (int)fps * 35;
	int cnt_frame = 0;
	while (cnt_frame < total_frame) {
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

void Input::recordVideo(int n) {
	thread t(startRecord, this->rtmpURL, n);
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

extern "C" __declspec(dllexport) void recordVideo(Input * input, int n) {
	input->recordVideo(n);
	return;
}