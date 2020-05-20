#pragma once
#include<opencv2/opencv.hpp>
#include<memory>
#include<iostream>

#include<seeta/FaceDetector.h>//���������
#include<seeta/FaceLandmarker.h>//�ؼ�����ȡ
#include<seeta/Common/Struct.h>
#include<seeta/FaceRecognizer.h>//����ʶ��
#include<seeta/EyeStateDetector.h>//�۾�״̬
#include<seeta/FaceAntiSpoofing.h>//������
#include<seeta/FaceTracker.h>//����׷��

#include<seeta/QualityOfBrightness.h>//��������,�ж���������ֵ�Ƕ�����,�������������LOW,0,1,2
#include<seeta/QualityOfClarity.h>//����������
#include<seeta/QualityOfIntegrity.h>//��������������,�ж������Ƿ���ȫ��������ͷ
#include<seeta/QualityOfPose.h>//��̬����,ͨ������5������ֵ���ж���̬�Ƿ�Ϊ���档
#include<seeta/QualityOfResolution.h>//�ֱ�������
#include<seeta/QualityStructure.h>

//===============================����
namespace seeta {
	class QualityOfNoMask : public QualityRule {
	public:
		QualityOfNoMask() {
			m_marker = std::make_shared<seeta::FaceLandmarker>(ModelSetting("./model/face_landmarker_mask_pts5.csta"));
		}
		QualityResult check(const SeetaImageData &image, const SeetaRect &face, const SeetaPointF *points, int32_t N) override {
			auto mask_points = m_marker->mark_v2(image, face);
			int mask_count = 0;
			for (auto point : mask_points) {
				if (point.mask) mask_count++;
			}
			QualityResult result;
			if (mask_count > 0) {
				return { QualityLevel::LOW, 1 - float(mask_count) / mask_points.size() };
			}
			else {
				return { QualityLevel::HIGH, 1 };
			}
		}
	private:
		std::shared_ptr<seeta::FaceLandmarker> m_marker;
	};
}



/*
ʹ���κ�һ��ģ�Ͷ�һ��Ҫ��ʼ��,��������Ϊһ���յļ����
*/
namespace seeta_pacakge {
	//========/============================================
#define  Brightness 0
#define  Clarity 1
#define  Integrity 2
#define  Pose 3
#define Resolution 4
#define NoMask 5

//======================================================================================================��ż������ַ
	seeta::FaceLandmarker *facelandmarker;
	seeta::FaceDetector *facedector;
	seeta::FaceRecognizer *facerecognizer;
	seeta::EyeStateDetector *eyestatedector;
	seeta::FaceAntiSpoofing *faceantspoofing;
	seeta::FaceTracker *facetracker;
	seeta::QualityRule *qualityrelu;


	//======================================================================================================
	const char* FaceDector_path = "./model/face_detector.csta";//�������ģ��
	const char* FaceLandmarker_path = "./model/face_landmarker_pts5.csta";//�����ģ��
	const char* FaceRecognizer_path = "./model/face_recognizer.csta";//��������ƥ��ͶԱ�ģ��
	const char* EyeStateDetector_path = "./model/eye_state.csta";//�۾�״̬���ģ��
	const char* fasfirst_path = "./model/fas_first.csta";//�ֲ�����
	const char* fassecond_path = "./model/fas_second.csta";//ȫ�ֻ���
	const char* face_landmarker_mask_pts5_path = "./model/face_landmarker_mask_pts5.ctsa";
	//===============================================================================================================����ʶ���=
	void facerecognizer_init()
	{
		seeta::ModelSetting setting;
		setting.append(FaceRecognizer_path);
		facerecognizer = new seeta::FaceRecognizer(setting);

	}
	
	//��ȡͼƬ������
	float* extract_feature(const SeetaImageData& simg, std::vector<SeetaPointF> faces)
	{
		if (facerecognizer == NULL)
		{
			std::cout << "dont init facerecongizer";
			throw 1;
		}
		SeetaPointF points[5];
		for (int i = 0; i < 5; i++)
		{
			points[i] = faces.at(i);
			//	std::cout << points[i].x << "," << points[i].y << std::endl;
		}
		float* feature = new float[facerecognizer->GetExtractFeatureSize()];
		facerecognizer->Extract(simg, points, feature);
		return feature;

	}
//�Ƚ����������ж��Ƿ�����
	float compare(float* feature1, float* feature2)
	{
		return facerecognizer->CalculateSimilarity(feature1, feature2);
	}





	//====================================================================================������������ȡ��===================
	void facelandmarker_init()
	{
		seeta::ModelSetting setting;
		setting.append(FaceLandmarker_path);
		facelandmarker = new seeta::FaceLandmarker(setting);
	}


//��ȡͼ����������������
	std::vector<SeetaPointF> mark(const SeetaImageData& image, const SeetaRect& face)
	{
		if (facelandmarker == NULL)
		{
			std::cout << "dont init facelandmarker";
			throw 1;
		}
		return facelandmarker->mark(image, face);
		//�����⵽��5������ѭ������Ϊ���������ġ��������ġ��Ǽ⡢����Ǻ�����ǡ�
	}
	//==================================================================================================�������(base)======

	void facedector_init()
	{
		seeta::ModelSetting setting;
		setting.append(FaceDector_path);
		facedector = new seeta::FaceDetector(setting);
	}
	//����������ŵ�������
	SeetaFaceInfoArray detect(const SeetaImageData &image)
	{
		if (facedector == NULL)
		{
			std::cout << "dont init facedector";
			throw 1;
		}
		return facedector->detect(image);
	}
//��������С������������
	void sort(SeetaFaceInfoArray face_sfia)
	{
		int m = face_sfia.size;
		std::vector<SeetaFaceInfo> faces(m);
		for (int i = 0; i < face_sfia.size; i++)
		{
			faces.at(i) = face_sfia.data[i];
		}
		std::partial_sort(faces.begin(), faces.begin() + 1, faces.end(), [](SeetaFaceInfo a, SeetaFaceInfo b) {
			return a.pos.width > b.pos.width;
		});
		for (int i = 0; i < face_sfia.size; i++)
		{
			face_sfia.data[i] = faces.at(i);
		}
	}


	//==========================================================�۲�������ȡ

	const char *EYE_STATE_STR[] = { "close", "open", "random", "unknown" };

	void eyestatedector_init()
	{
		seeta::ModelSetting setting;
		setting.append(EyeStateDetector_path);
		eyestatedector = new seeta::EyeStateDetector(setting);
	}

	int* eye_state(const SeetaImageData &img, const std::vector<SeetaPointF> &points)
	{

		if (eyestatedector == NULL)
		{
			std::cout << "eyestatedector dont init";
			throw 1;
		}
		seeta::EyeStateDetector::EYE_STATE left_eye, right_eye;
		int status[2];
		eyestatedector->Detect(img, points.data(), left_eye, right_eye);
		status[0] = left_eye;
		status[1] = right_eye;
		return status;
	}
	//==============================������==================================================================
	const char *SPOOF_STATE_STR[] = { "real face",
	"spoof face",
	"unknown",
	"judging" };



	//0�ֲ�
	//1ȫ��
	//2�ֲ�+ȫ��
	void faceantspoofing_init(int version = 0)
	{
		seeta::ModelSetting setting;
		switch (version)
		{
		case 0:
			setting.append(fasfirst_path);
			break;
		case 1:
			setting.append(fassecond_path);
			break;
		case 2:
			setting.append(fasfirst_path);
			setting.append(fassecond_path);
			break;
		default:
			std::cout << "version input error";
			throw 2;
		}

		faceantspoofing = new seeta::FaceAntiSpoofing(setting);
	}

	int predict(const SeetaImageData &image,
		const SeetaRect &face,
		std::vector<SeetaPointF> v_points,
		int way = 0)//�����0Ϊ��֡ʶ��,1Ϊ��֡ʶ��
	{

		if (faceantspoofing == NULL)
		{
			std::cout << "faceantspoofing dont init";
			throw 1;
		}

		SeetaPointF points[5];
		for (int i = 0; i < 5; i++)
		{
			points[i] = v_points.at(i);

		}

		int status;
		switch (way)
		{
		case 0:
			status = faceantspoofing->Predict(image, face, points);
			break;
		case 1:
			status = faceantspoofing->PredictVideo(image, face, points);
			break;
		default:
			std::cout << "way input error";
			throw 2;

		}
		auto status1 = faceantspoofing->PredictVideo(image, face, points);
		switch (status1) {
		case seeta::FaceAntiSpoofing::REAL:
			std::cout << "��ʵ����" << std::endl; break;
		case seeta::FaceAntiSpoofing::SPOOF:
			std::cout << "��������" << std::endl; break;
		case seeta::FaceAntiSpoofing::FUZZY:
			std::cout << "�޷��ж�" << std::endl; break;
		case seeta::FaceAntiSpoofing::DETECTING:
			std::cout << "���ڼ��" << std::endl; break;
		}
		return status;
	}

	void reset_video() {
		faceantspoofing->ResetVideo();
	}
	void set_frame(int32_t number)
	{
		faceantspoofing->SetVideoFrameCount(number);//Ĭ����10;

	}

	//=======================================================================================================
	SeetaImageData mat_to_seetaImageData(cv::Mat& m)
	{
		SeetaImageData* sid = new SeetaImageData();
		sid->data = m.data;
		sid->channels = m.channels();
		sid->height = m.rows;
		sid->width = m.cols;
		return *sid;

	}
	//=======================================����׷��=====================================
	void facetracker_init(int width, int height)
	{
		seeta::ModelSetting setting;
		setting.append(FaceDector_path);
		facetracker = new seeta::FaceTracker(setting, width, height);
	}

	std::vector<SeetaTrackingFaceInfo> tracker(const SeetaImageData &image)
	{
		if (facetracker == NULL)
		{
			std::cout << "facetracker dont init";
			throw 1;
		}
		SeetaTrackingFaceInfoArray cfaces = facetracker->Track(image);
		std::vector<SeetaTrackingFaceInfo> faces(cfaces.data, cfaces.data + cfaces.size);
		return faces;
	}
	//========================��������==================================================
	void qualityrelu_init(int choose)
	{
		switch (choose)
		{
		case Brightness: qualityrelu = new seeta::QualityOfBrightness();//����
		case Clarity: qualityrelu = new seeta::QualityOfClarity();//������
		case Integrity:qualityrelu = new seeta::QualityOfIntegrity();//������
		case Pose:qualityrelu = new seeta::QualityOfPose();//��̬
		case Resolution: qualityrelu = new seeta::QualityOfResolution();//�ֱ���
		case NoMask:qualityrelu = new seeta::QualityOfNoMask();
		}
	}
	const char *level_string[] = { "LOW", "MEDIUM", "HIGH" };
	int plot_quality(const SeetaImageData &image,
		const SeetaRect &face,
		const std::vector < SeetaPointF>& points)
	{
		seeta::QualityResult result = qualityrelu->check(image, face, points.data(), int(points.size()));
		return result.level;
	}
}