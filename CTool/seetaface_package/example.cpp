#include"seeta_own.h"
#include<Windows.h>

using namespace std;
using namespace cv;
using namespace seeta_pacakge;
void test1()
{
	Mat m = imread("E:/source/test.jpg");

	facedector_init();
	facelandmarker_init();
	facerecognizer_init();

	SeetaImageData sid = mat_to_seetaImageData(m);
	SeetaFaceInfoArray sfia = detect(sid);
	sort(sfia);
	if (sfia.data <= 0)
	{
		cout << "未检测到脸";
		system("pause");
	}
	vector<SeetaPointF> spf = mark(sid, sfia.data[0].pos);

	rectangle(m, Rect(sfia.data[0].pos.x, sfia.data[0].pos.y, sfia.data[0].pos.width, sfia.data[0].pos.height), Scalar(0, 0, 255));
	for (int i = 0; i < 5; i++)
	{
		circle(m, Point(spf.at(i).x, spf.at(i).y), 5, Scalar(0, 255, 0));
	}
	imshow("1", m);

	float* feature = extract_feature(sid, spf);


	Mat m2 = imread("E:/source/test2.jpg");
	SeetaImageData sid2 = mat_to_seetaImageData(m2);
	SeetaFaceInfoArray sfia2 = detect(sid2);
	sort(sfia2);
	vector<SeetaPointF> spf2 = mark(sid2, sfia2.data[0].pos);


	float* feature2 = extract_feature(sid2, spf2);
	cout << "大小" << facerecognizer->GetExtractFeatureSize();
	std::cout << "相似度" << facerecognizer->CalculateSimilarity(feature, feature2) << std::endl;
	for (int j = 0; j < 2048; j++)
		std::cout << j << "...." << feature2[j] << std::endl;


	float* f = new float[1024];
	for (int o = 0; o < 1024; o++)
		f[o] = feature[o];

	std::cout << "2相似度" << compare(f, feature2);
	waitKey(0);
}
void test2()
{
	facedector_init();
	facelandmarker_init();
	eyestatedector_init();

	VideoCapture videocapture(0);
	Mat mat;
	while (videocapture.isOpened())
	{
		videocapture.read(mat);
		flip(mat, mat,1);
		SeetaImageData sid=mat_to_seetaImageData(mat);
		SeetaFaceInfoArray sfia=detect(sid);
		sort(sfia);
		vector<SeetaPointF> spf  =mark(sid, sfia.data[0].pos);
		int* eye=eye_state(sid, spf);
		cout << "左眼:" << eye[0] << EYE_STATE_STR[eye[0]]
			<< "   "<< "右眼:" << eye[1] << EYE_STATE_STR[eye[1]]<<std::endl;
		imshow("1", mat);
		waitKey(1);

	}
}
void test3()
{
	facedector_init();
	facelandmarker_init();
	eyestatedector_init();
	facerecognizer_init();

	Mat ori = imread("E:/source/test2.jpg");
	SeetaImageData sid_ori = mat_to_seetaImageData(ori);
	SeetaFaceInfoArray sfia_ori = detect(sid_ori);
	sort(sfia_ori);
	vector<SeetaPointF> spf2=mark(sid_ori, sfia_ori.data[0].pos);
	float* ori_ss = extract_feature(sid_ori, spf2);

	VideoCapture videocapture(0);
	Mat mat;
	while (videocapture.isOpened())
	{
		videocapture.read(mat);
		flip(mat, mat, 1);
		SeetaImageData sid = mat_to_seetaImageData(mat);
		SeetaFaceInfoArray sfia = detect(sid);
		sort(sfia);
		vector<SeetaPointF> spf = mark(sid, sfia.data[0].pos);
		float* curr=extract_feature(sid, spf);
		std::cout << compare(curr, ori_ss) << std::endl;
		imshow("1", mat);
		waitKey(1);


	}
}
void test4()
{
	facedector_init();
	facelandmarker_init();
	eyestatedector_init();
	facerecognizer_init();
	faceantspoofing_init();
	VideoCapture videocapture(0);
	Mat mat;
	while (videocapture.isOpened())
	{
		videocapture.read(mat);
		flip(mat, mat, 1);
		SeetaImageData sid = mat_to_seetaImageData(mat);
		SeetaFaceInfoArray sfia = detect(sid);
		sort(sfia);
		vector<SeetaPointF> spf = mark(sid, sfia.data[0].pos);

		int status=predict(sid, sfia.data[0].pos, spf,1);
		cout << status << SPOOF_STATE_STR[status] << std::endl;
		imshow("1", mat);
		waitKey(1);
	}

}
void test5()
{
	facedector_init();
	facelandmarker_init();
	eyestatedector_init();
	facerecognizer_init();
	faceantspoofing_init();
	
	VideoCapture videocapture(0);
	facetracker_init(videocapture.get(CAP_PROP_FRAME_WIDTH),videocapture.get(CAP_PROP_FRAME_HEIGHT));
	Mat mat;
	while (videocapture.isOpened())
	{
		videocapture.read(mat);
		flip(mat, mat, 1);
		SeetaImageData sid = mat_to_seetaImageData(mat);
		auto tra=tracker(sid);
		for (int i = 0; i < tra.size(); i++)
		{
			SeetaTrackingFaceInfo id=tra.at(i);
			rectangle(mat, Rect(id.pos.x, id.pos.y, id.pos.width, id.pos.height), Scalar(255, 0, 0));
			putText(mat, to_string(id.PID), Point(id.pos.x, id.pos.y), FONT_HERSHEY_SIMPLEX, 1, Scalar(255, 23, 0), 4, 8);
		}
		imshow("1", mat);
		waitKey(1);

	}
}
void test6()
{
	facedector_init();
	facelandmarker_init();
	eyestatedector_init();
	facerecognizer_init();
	faceantspoofing_init();
	qualityrelu_init(NoMask);
	VideoCapture videocapture(0);
	Mat mat;
	while (videocapture.isOpened())
	{
		videocapture.read(mat);
		flip(mat, mat, 1);
		SeetaImageData sid = mat_to_seetaImageData(mat);
		SeetaFaceInfoArray sfia = detect(sid);
		sort(sfia);
		vector<SeetaPointF> spf = mark(sid, sfia.data[0].pos);
		imshow("1", mat);
		waitKey(1);
		int status=plot_quality(sid, sfia.data[0].pos, spf);
		std::cout << level_string[status] << std::endl;
	}
}
int main()
{
	test6();
}


