#include<opencv2/opencv.hpp>
#include<stdio.h>
#include<iostream>
#include<string>
#include<thread>
#include<ctime>
#include<mmstream.h>
#pragma comment(lib,"winmm.lib")
#define debug 0


using namespace cv;
using namespace std;
#include<vector>





class preperties
{
private:
	FILE *file;
	string filedata;
	vector<string> alldata;


public:
	map<string, string> datamap;
	vector<string> section;
	preperties(const char * filepath)
	{
		 int err=fopen_s(&file,filepath, "r");
		if (err)
		{
			printf("ini not exists");
			while (1)
			{
				system("pause");
			}

		}
		#define MAX_LINE 1024
		char buf[MAX_LINE];
		while (fgets(buf, MAX_LINE, file) != NULL)
		{
			filedata += buf;
		}
		//cout << filedata;
		vector<string> temp_vec;
		SplitString(filedata, alldata, "\n");
	
	
		for (int i = 0; i < alldata.size(); i++)
		{
			
			string tem_str = alldata.at(i);
			if (tem_str.find("=") != string::npos)
			{
				SplitString(alldata.at(i), temp_vec, "=");
				datamap[temp_vec.at(0)] = temp_vec.at(1);
				cout << temp_vec[0] << "  " << datamap[temp_vec.at(0)] << endl;
			}
			else
			{
				section.push_back(alldata.at(i));
				cout << alldata.at(i) << endl;
			}
		}
	
		fclose(file);
	

	}

	void SplitString(const string& s, vector<string>& v, const string& c)
		 {
		v.clear();
		     string::size_type pos1, pos2;
		    pos2 = s.find(c);
		     pos1 = 0;
		     while (string::npos != pos2)
			     {
			        v.push_back(s.substr(pos1, pos2 - pos1));
			
				         pos1 = pos2 + c.size();
			       pos2 = s.find(c, pos1);
			    }
		    if (pos1 != s.length())
			        v.push_back(s.substr(pos1));
	 }
	
};


class MSS
{
public:
	deque<Mat> matlist;
	long total;
	int fps;
	int col_w;
	int row_h;

}
;

MSS* video_demo(string filepath);
vector<string>* transfor(MSS* mss);
void play_vedio(vector<string>* data,MSS* mss);
map<string, string> datamap;
void thread_run();
bool is_load = true;

int main()
{



	preperties p("config.ini");
	 datamap = p.datamap;
	 system("python create.py");



	cout << "preperies read success\n"<<"enter any key to start";
	system("pause");
	system("cls");

	string path=datamap["movie_path"];
	
	MSS* mss=video_demo(path);
	
	
	vector<string>* data=transfor(mss);

	play_vedio(data,mss);
	

	
	system("pause");
	return 0;
}



MSS* video_demo(string filepath)
{
	
	VideoCapture capture= cv::VideoCapture(filepath);
	int fps = capture.get(CV_CAP_PROP_FPS);
	 long len = capture.get(CV_CAP_PROP_FRAME_COUNT);
#if debug:
	 cout <<"fps:"<< fps << endl;
	 cout << "len:"<<len<<endl;
#endif
	MSS* mss=new MSS();
	Mat temp_mat;
	
	mss->fps = fps;
	mss->total = len-2;

	int i = 0;
	cout << "wait to read the vedio....... rate:" <<(i*1.0/mss->total)*100<<"%"<< endl;
	float rate;
	while (i<mss->total)
	{	
		i++;
		if (i % 100 == 0)
		{
			system("cls");
			cout << "wait to read the vedio....... rate:" << (i*1.0 / mss->total) * 100 << "%" << endl;
		}
		capture.read(temp_mat);
		mss->col_w=temp_mat.cols;
		mss->row_h=temp_mat.rows;

		if (temp_mat.cols > temp_mat.rows)
		{
			rate = temp_mat.cols *(1.0)/ 150;
		}
		else {
			rate = temp_mat.rows*(1.0) / 50;
		}


	
		cv::resize(temp_mat, temp_mat, Size(atoi(datamap["W"].c_str()),atoi(datamap["H"].c_str())));


		mss->matlist.push_back(temp_mat);
	}
	system("cls");
#if debug
	cout << "col_width:" << mss->col_w << endl;
	cout << "row_heigt:" << mss->row_h << endl;
#endif
	cout << "read suceess ! ! !" << endl;
	return mss;

}

vector<string>* transfor(MSS* mss)
{
	system("cls");

	
	int i = 0;

	while (i < mss->total)
	{
		cv::cvtColor(mss->matlist.at(i), mss->matlist.at(i), cv::COLOR_BGR2GRAY);
		
		cv::GaussianBlur(mss->matlist.at(i), mss->matlist.at(i), Size(0,0), atof(datamap["ratio"].c_str()));
		
		
		
		cv::Canny(mss->matlist.at(i), mss->matlist.at(i), 12,21);
		
		
		i++;
		if (i % 50 == 0)
		{
			system("cls");
			cout << "read suceess ! ! !\nstart deal datas! ! !\n" << (i*1.0 / mss->total) * 100 << "%" << endl;
		
		}
	}
	
	
//	imshow("5", mss->matlist.at(900));
//	cout << mss->matlist.at(900).rows << " " << mss->matlist.at(900).cols;
	//waitKey(2000);
	vector<string>* data = new vector<string>(mss->total);
	//cout << data->size()<<endl<<mss->row_h<<" "<<mss->col_w<<endl;
	uchar a=mss->matlist.at(0).at<uchar>(0, 0);
	//cout << (int)a;
	//system("pause");

	//system("cls");
	//cout << "¿ªÊ¼¼ÆËã";
	//system("pause");
	for (int j = 0; j < mss->total; j++)
	{
		
		for (int m = 0; m < atoi(datamap["H"].c_str()); m++)
		{
			for (int n = 0; n < atoi(datamap["W"].c_str()); n++)
			{
			
				if (mss->matlist.at(j).at<uchar>(m, n) == 0)
				{
					data->at(j) += datamap["1"];
				}
				else
				{
					data->at(j) += datamap["0"];
				}
			}
			data->at(j) += "\n";
		}
	}

	system("cls");
	cout << "deal datas success ! ! !\nplease Maximize your cmd window and enter any key to start play the vedio";
	system("pause");
	return data;
	
}

void play_vedio(vector<string>* data,MSS* mss)
{
	system("cls");
	

	


	thread t(thread_run);
	t.detach();
	clock_t start = clock();

	/*
	if (1000 / mss->fps > atof(datamap["delay_time"].c_str()))
	{
		for (int i = 0; i < data->size(); i++)
		{

			cout << data->at(i);
			waitKey(1000 / mss->fps - atof(datamap["delay_time"].c_str()));
			system("cls");
		}
	}
	else
	{
		
			for (int i = 0; i < data->size(); i++)
			{

				cout << data->at(i);
				system("cls");
			}
	}
	*/
	/*
	if (1000 / mss->fps > atof(datamap["delay_time"].c_str()))
	{
		for (int i = 0; i < data->size(); i++)
		{

			cout << data->at(i);
		//	waitKey(1000 / mss->fps - atof(datamap["delay_time"].c_str()));
			system("cls");
		}
	}
	*/
	float delay_time=atof(datamap["delay_time"].c_str());
	
	if (delay_time == 0)
	{
		
		for (long i = 0; i < data->size(); i++)
		{
			cout << data->at(i);
			waitKey(1000 / mss->fps);
			system("cls");
		}
	}
	else
	{
		
		
		float rate=delay_time *1.0/ 100;
		long lim = rate * mss->total;
		
		for (long i = 0; i < lim; i++)
		{
			cout << data->at(long(i/rate));
			system("cls");
		}
	}

#if debug

	cout <<"delay_time" <<(clock() - start)*1.0/mss->total;
#endif
	cout << "end!!! enter any key to quit";
}





void thread_run()
{
	PlaySound("temp.wav", NULL, SND_ASYNC | SND_NODEFAULT);
	
}