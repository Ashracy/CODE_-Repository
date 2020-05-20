#pragma once
#include<opencv2/opencv.hpp>
#include<memory>
#include<iostream>

#include<seeta/FaceDetector.h>//人脸检测器
#include<seeta/FaceLandmarker.h>//关键点提取
#include<seeta/Common/Struct.h>
#include<seeta/FaceRecognizer.h>//人脸识别
#include<seeta/EyeStateDetector.h>//眼睛状态
#include<seeta/FaceAntiSpoofing.h>//活体检测
#include<seeta/FaceTracker.h>//人脸追踪

#include<seeta/QualityOfBrightness.h>//亮度评估,判断人脸亮度值是都正常,过量或过暗评价LOW,0,1,2
#include<seeta/QualityOfClarity.h>//清晰度评估
#include<seeta/QualityOfIntegrity.h>//人脸完整度评估,判断人脸是否完全进入摄像头
#include<seeta/QualityOfPose.h>//姿态评估,通过人脸5点坐标值来判断姿态是否为正面。
#include<seeta/QualityOfResolution.h>//分辨率评估
#include<seeta/QualityStructure.h>

//===============================补充
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
使用任何一个模型都一定要初始化,否则它会为一个空的检测器
*/
namespace seeta_pacakge {
	//========/============================================
#define  Brightness 0
#define  Clarity 1
#define  Integrity 2
#define  Pose 3
#define Resolution 4
#define NoMask 5

//======================================================================================================存放检测器地址
	seeta::FaceLandmarker *facelandmarker;
	seeta::FaceDetector *facedector;
	seeta::FaceRecognizer *facerecognizer;
	seeta::EyeStateDetector *eyestatedector;
	seeta::FaceAntiSpoofing *faceantspoofing;
	seeta::FaceTracker *facetracker;
	seeta::QualityRule *qualityrelu;


	//======================================================================================================
	const char* FaceDector_path = "./model/face_detector.csta";//人脸检测模型
	const char* FaceLandmarker_path = "./model/face_landmarker_pts5.csta";//五点检测模型
	const char* FaceRecognizer_path = "./model/face_recognizer.csta";//人脸特征匹配和对比模型
	const char* EyeStateDetector_path = "./model/eye_state.csta";//眼睛状态检测模型
	const char* fasfirst_path = "./model/fas_first.csta";//局部活体
	const char* fassecond_path = "./model/fas_second.csta";//全局活体
	const char* face_landmarker_mask_pts5_path = "./model/face_landmarker_mask_pts5.ctsa";
	//===============================================================================================================人脸识别块=
	void facerecognizer_init()
	{
		seeta::ModelSetting setting;
		setting.append(FaceRecognizer_path);
		facerecognizer = new seeta::FaceRecognizer(setting);

	}
	
	//获取图片中特征
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
//比较两个特征判断是否相似
	float compare(float* feature1, float* feature2)
	{
		return facerecognizer->CalculateSimilarity(feature1, feature2);
	}





	//====================================================================================人脸特征点提取块===================
	void facelandmarker_init()
	{
		seeta::ModelSetting setting;
		setting.append(FaceLandmarker_path);
		facelandmarker = new seeta::FaceLandmarker(setting);
	}


//提取图像中人脸的特征点
	std::vector<SeetaPointF> mark(const SeetaImageData& image, const SeetaRect& face)
	{
		if (facelandmarker == NULL)
		{
			std::cout << "dont init facelandmarker";
			throw 1;
		}
		return facelandmarker->mark(image, face);
		//这里检测到的5点坐标循序依次为，左眼中心、右眼中心、鼻尖、左嘴角和右嘴角。
	}
	//==================================================================================================人脸检测(base)======

	void facedector_init()
	{
		seeta::ModelSetting setting;
		setting.append(FaceDector_path);
		facedector = new seeta::FaceDetector(setting);
	}
	//检测人脸并放到数组中
	SeetaFaceInfoArray detect(const SeetaImageData &image)
	{
		if (facedector == NULL)
		{
			std::cout << "dont init facedector";
			throw 1;
		}
		return facedector->detect(image);
	}
//按人脸大小排列人脸数组
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


	//==========================================================眼部特征提取

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
	//==============================活体检测==================================================================
	const char *SPOOF_STATE_STR[] = { "real face",
	"spoof face",
	"unknown",
	"judging" };



	//0局部
	//1全局
	//2局部+全局
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
		int way = 0)//如果是0为单帧识别,1为多帧识别
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
			std::cout << "真实人脸" << std::endl; break;
		case seeta::FaceAntiSpoofing::SPOOF:
			std::cout << "攻击人脸" << std::endl; break;
		case seeta::FaceAntiSpoofing::FUZZY:
			std::cout << "无法判断" << std::endl; break;
		case seeta::FaceAntiSpoofing::DETECTING:
			std::cout << "正在检测" << std::endl; break;
		}
		return status;
	}

	void reset_video() {
		faceantspoofing->ResetVideo();
	}
	void set_frame(int32_t number)
	{
		faceantspoofing->SetVideoFrameCount(number);//默认是10;

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
	//=======================================人脸追踪=====================================
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
	//========================质量评估==================================================
	void qualityrelu_init(int choose)
	{
		switch (choose)
		{
		case Brightness: qualityrelu = new seeta::QualityOfBrightness();//亮度
		case Clarity: qualityrelu = new seeta::QualityOfClarity();//清晰度
		case Integrity:qualityrelu = new seeta::QualityOfIntegrity();//完整度
		case Pose:qualityrelu = new seeta::QualityOfPose();//姿态
		case Resolution: qualityrelu = new seeta::QualityOfResolution();//分辨率
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