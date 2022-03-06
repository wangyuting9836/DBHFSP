#pragma once

#include <numeric>

// -------------for ordering----------
typedef struct
{
	int dim;
	int value;
} Pair;

class PairGreater {
public:
	bool operator () (Pair a, Pair b)
	{
		return a.value>b.value;
	}
};

class PairLess {
public:
	bool operator () (Pair a, Pair b)
	{
		return a.value<b.value;
	}
};
//-------------end ----------------

int gJobs, gMachine, gFactory, InStage;
vector <vector<int>> pTime;
vector <vector<vector<int>>> pSetupTime;
vector<int> pMachines;  
vector<vector<int>> IdleTime; 
vector<vector<int>> BlockTime; 
vector<vector<int>> IdleConsumption; //IdleConsumption(i,j) the idle-energy consumption per unit time of the machine j at stage i
vector<vector<int>> BlockConsumption; //BlockConsumption(i,j) the  blocking consumption of the machine j at stage i per unit time
vector<vector<int>> pTimeConsumption; //IdleConsumption(i,j) the  Idle consumption of the machine j at stage i per unit time

//获取时间函数
long GetElapsedProcessTime()
{
	FILETIME createTime;
	FILETIME exitTime;
	FILETIME kernelTime;
	FILETIME userTime;

	if (GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, &kernelTime, &userTime) != 0)
	{
		//  Returns total user time.
		SYSTEMTIME userSystemTime;
		if (FileTimeToSystemTime(&userTime, &userSystemTime) != -1)
			return (userSystemTime.wDay - 1) * 24 * 3600 * 1000
			+ userSystemTime.wHour * 3600 * 1000 +
			userSystemTime.wMinute * 60 * 1000 +
			userSystemTime.wSecond * 1000 +
			userSystemTime.wMilliseconds;
		else
			return 0;
	}
	else
		return 0;
}

//void GenerateInstances(int Factor_SetupTime, int NO)       //  随机产生一个例子
//{
//	pTime.resize(gJobs);
//	for (int j = 0; j < gJobs; j++)
//		pTime[j].resize(InStage);
//
//	/*pSetupTime.resize(InStage);
//	for (int m = 0; m < InStage; m++)
//	{
//		pSetupTime[m].resize(gJobs);
//		for (int j = 0; j < gJobs; j++)
//		{
//			pSetupTime[m][j].resize(gJobs);
//		}
//	}*/
//
//	for (int j = 0; j < gJobs; j++){
//		for (int i = 0; i < InStage; i++)
//			pTime[j][i] = 1 + rand() % 30;
//	}
//
//	pMachines.resize(InStage);
//	for (int i = 0; i < InStage; i++)
//	{
//		pMachines[i] = 1 + rand() % 3;  //range of machines [1-3]
//
//	}
//
//	pTimeConsumption.resize(InStage);
//	for (int k = 0; k < InStage; k++)
//	{
//		pTimeConsumption[k].resize(pMachines[k]);
//	}
//
//	for (int i = 0; i < InStage; i++)
//	{
//		pTimeConsumption[i][0] = 3 + rand() % 3;  //[3-5]
//		for (int j = 0; j < pMachines[i]; j++)
//		{
//			pTimeConsumption[i][j] = pTimeConsumption[i][0];
//
//		}
//	}
//
//	BlockTime.resize(InStage);
//	for (int k = 0; k < InStage; k++)
//	{
//		BlockTime[k].resize(pMachines[k]);
//	}
//
//	BlockConsumption.resize(InStage);
//	for (int k = 0; k < InStage; k++)
//	{
//		BlockConsumption[k].resize(pMachines[k]);
//	}
//
//	for (int k = 0; k < InStage; k++)
//	{
//		BlockConsumption[k][0] = 5 + rand() % 3;  //[5-7]
//		for (int i = 0; i < pMachines[k]; i++)
//		{
//			BlockConsumption[k][i] = BlockConsumption[k][0];  //[5-7]
//		}
//	}
//
//	IdleTime.resize(InStage);
//	for (int k = 0; k < InStage; k++)
//	{
//		IdleTime[k].resize(pMachines[k]);
//	}
//
//	IdleConsumption.resize(InStage);
//	for (int k = 0; k < InStage; k++)
//	{
//		IdleConsumption[k].resize(pMachines[k]);
//	}
//
//	for (int k = 0; k < InStage; k++)
//	{
//		IdleConsumption[k][0] = 1 + rand() % 3;  //[1-3]
//		for (int i = 0; i < pMachines[k]; i++)
//		{
//			IdleConsumption[k][i] = IdleConsumption[k][0];  //[1-3]
//		}
//	}
//
//	/*for (int m = 0; m < InStage; m++)
//	{
//		for (int j = 0; j < gJobs; j++)
//		{
//			for (int i = 0; i < gJobs; i++)
//				pSetupTime[m][j][i] = (1 + rand() % 99) * Factor_SetupTime / 100;
//		}
//	}*/
//
//	char FName[100] = "D_PRO_SETUP_", Buf[100] = "";
//	_itoa_s(NO, Buf, 10);
//	strcat_s(FName, Buf);
//	strcat_s(FName, ".txt");
//
//	ofstream ofile;
//	ofile.open(FName);
//	ofile << gJobs << "\t" << InStage << "\t" << gFactory << endl;
//	for (int j = 0; j < gJobs; j++)
//	{
//		for (int i = 0; i < InStage; i++)
//		{
//			ofile << pTime[j][i] << "\t";
//		}
//
//		ofile << endl;
//	}
//	/*for (int m = 0; m < InStage; m++)
//	{
//		for (int j = 0; j < gJobs; j++)
//		{
//			for (int i = 0; i < gJobs; i++)
//			{
//				ofile << pSetupTime[m][j][i] << "\t";
//			}
//			ofile << endl;
//		}
//		ofile << endl;
//	}*/
//	ofile.close();
//}

void Read(int NO)
{
	
	string FileDirectory = "RunInstance\\";
	char FName[100] = "D_PRO_SETUP_", Buf[100] = "";
	_itoa_s(NO, Buf, 10); //itoa_s是将整数转换成字符串的函数,10表示十进制
	strcat_s(FName, Buf); 
	strcat_s(FName, ".txt");
	string RunFileName = FileDirectory + FName;

	ifstream ifile;
	ifile.open(RunFileName);
	ifile >> gJobs >> InStage >> gFactory;
	//	cout << gJobs << gMachine << gFactory << endl;

	pTime.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		pTime[j].resize(InStage);

	//pSetupTime.resize(InStage);
	//for (int m = 0; m < InStage; m++)
	//{
	//	pSetupTime[m].resize(gJobs);
	//	for (int j = 0; j < gJobs; j++)
	//		pSetupTime[m][j].resize(gJobs);
	//}

	
	

	for (int i = 0; i < gJobs; i++)
	{
		for (int j = 0; j < InStage; j++)
		{
			pTime[i][j] = 1 + rand() % 99;  //[1-99]

		}
	}

	//for (int j = 0; j < gJobs; j++)
	//{
	//	for (int i = 0; i < InStage; i++)
	//	{
	//		/*int value;
	//		ifile >> value;
	//		pTime[j][i] = value;*/
	//		cout << pTime[j][i] << "\t";
	//	}
	//	cout << endl;
	//}

	pMachines.resize(InStage);
	for (int i = 0; i < InStage; i++)
	{
		pMachines[i] = 1 + rand() % 5;  //range of machines 

	}

	//pTimeConsumption.resize(InStage);
	//for (int k = 0; k < InStage; k++)
	//{
	//	pTimeConsumption[k].resize(pMachines[k]);
	//}

	//for (int i = 0; i < InStage; i++)
	//{
	//	pTimeConsumption[i][0] = 5 + rand() % 3;  //[5-7]
	//	for (int j = 0; j < pMachines[i]; j++)
	//	{
	//		pTimeConsumption[i][j] = pTimeConsumption[i][0];

	//	}
	//}

	

	IdleTime.resize(InStage);
	for (int k = 0; k < InStage; k++)
	{
		IdleTime[k].resize(pMachines[k]);
	}

	//IdleConsumption.resize(InStage);
	//for (int k = 0; k < InStage; k++)
	//{
	//	IdleConsumption[k].resize(pMachines[k]);
	//}

	//for (int k = 0; k < InStage; k++)
	//{
	//	IdleConsumption[k][0] = 1 + rand() % 2;  //[1-2]
	//	for (int i = 0; i < pMachines[k]; i++)
	//	{
	//		IdleConsumption[k][i] = IdleConsumption[k][0];  //[1-2]
	//	}
	//}


	BlockTime.resize(InStage);
	for (int k = 0; k < InStage; k++)
	{
		BlockTime[k].resize(pMachines[k]);
	}

	//BlockConsumption.resize(InStage);
	//for (int k = 0; k < InStage; k++)
	//{
	//	BlockConsumption[k].resize(pMachines[k]);
	//}

	//for (int k = 0; k < InStage; k++)
	//{
	//	BlockConsumption[k][0] = 3 + rand() % 2;  //[3-4]
	//	for (int i = 0; i < pMachines[k]; i++)
	//	{
	//		BlockConsumption[k][i] = BlockConsumption[k][0];  //[3-4]
	//	}
	//}
	//	cout << endl;
	//for (int m = 0; m < InStage; m++)
	//{
	//	for (int j = 0; j < gJobs; j++)
	//	{
	//		for (int i = 0; i < gJobs; i++)
	//		{
	//			int value;
	//			ifile >> value;
	//			pSetupTime[m][j][i] = value;
	//			//		cout << pSetupTime[m][j][i] << "\t";
	//		}
	//		//	cout << endl;
	//	}
	//	//	cout << endl;
	//}
	ifile.close();
}

void GetInstances_TaiE(int &Jobs, int &Machines, int &Factories, vector<vector<int>> &PTime, vector<vector<vector<int>>> &PSetupTime, string FileName)
{
	//Get instance file name and upper bound
	ifstream infile;
	infile.open(FileName);
	if (!infile)
	{
		cout << "open instance file is error!\t" << FileName;
		exit(0);
	}

	infile >> Jobs >> InStage >> Factories;
	PTime.resize(Jobs);
	for (int j = 0; j < Jobs; j++)
		PTime[j].resize(InStage);

	/*PSetupTime.resize(Machines);
	for (int m = 0; m < Machines; m++)
	{
		PSetupTime[m].resize(Jobs);
		for (int j = 0; j < Jobs; j++)
		{
			PSetupTime[m][j].resize(Jobs);
		}
	}*/
	pMachines.resize(InStage);
	for (int i = 0; i < InStage; i++)
	{
		pMachines[i] = 1 + rand() % 5;  //range of machines 

	}

	//pTimeConsumption.resize(InStage);
	//for (int k = 0; k < InStage; k++)
	//{
	//	pTimeConsumption[k].resize(pMachines[k]);
	//}

	//for (int i = 0; i < InStage; i++)
	//{
	//	pTimeConsumption[i][0] = 5 + rand() % 3;  //[5-7]
	//	for (int j = 0; j < pMachines[i]; j++)
	//	{
	//		pTimeConsumption[i][j] = pTimeConsumption[i][0];

	//	}
	//}



	IdleTime.resize(InStage);
	for (int k = 0; k < InStage; k++)
	{
		IdleTime[k].resize(pMachines[k]);
	}

	//IdleConsumption.resize(InStage);
	//for (int k = 0; k < InStage; k++)
	//{
	//	IdleConsumption[k].resize(pMachines[k]);
	//}

	//for (int k = 0; k < InStage; k++)
	//{
	//	IdleConsumption[k][0] = 1 + rand() % 2;  //[1-2]
	//	for (int i = 0; i < pMachines[k]; i++)
	//	{
	//		IdleConsumption[k][i] = IdleConsumption[k][0];  //[1-2]
	//	}
	//}


	BlockTime.resize(InStage);
	for (int k = 0; k < InStage; k++)
	{
		BlockTime[k].resize(pMachines[k]);
	}

	//BlockConsumption.resize(InStage);
	//for (int k = 0; k < InStage; k++)
	//{
	//	BlockConsumption[k].resize(pMachines[k]);
	//}

	//for (int k = 0; k < InStage; k++)
	//{
	//	BlockConsumption[k][0] = 3 + rand() % 2;  //[3-4]
	//	for (int i = 0; i < pMachines[k]; i++)
	//	{
	//		BlockConsumption[k][i] = BlockConsumption[k][0];  //[3-4]
	//	}
	//}
	//for (int m = 0; m < InStage; m++)
	//{
	//	for (int j = 0; j < Jobs; j++)
	//	{
	//		for (int i = 0; i < Jobs; i++)
	//		{
	//			int value;
	//			infile >> value;
	//			PSetupTime[m][j][i] = value;
	//		}
	//	}
	//}
	infile.close();
}

//void GetTestInstance(string FileName)
//{
//	//Get instance file name and upper bound
//	ifstream infile;
//	infile.open(FileName);
//	if (!infile)
//	{
//		cout << "open instance file is error!\t" << FileName;
//		exit(0);
//	}
//	infile >> gJobs >> InStage >> gFactory;
//	vector <vector <int>> pTime(gJobs);
//	for (int j = 0; j < gJobs; j++)
//		pTime[j].resize(InStage);
//
//	/*vector <vector<vector<int>>> pSetupTime(gMachine);
//	for (int m = 0; m < gMachine; m++)
//	{
//		pSetupTime[m].resize(gJobs);
//		for (int j = 0; j < gJobs; j++)
//		{
//			pSetupTime[m][j].resize(gJobs);
//		}
//	}*/
//	for (int j = 0; j < gJobs; j++)
//	{
//		for (int i = 0; i < InStage; i++)
//		{
//			int value;
//			infile >> value;
//			pTime[j][i] = value;
//		}
//	}
//
//	pMachines.resize(InStage);
//	for (int i = 0; i < InStage; i++)
//	{
//		pMachines[i] = 1 + rand() % 3;  //range of machines [1-3]
//
//	}
//
//	pTimeConsumption.resize(InStage);
//	for (int k = 0; k < InStage; k++)
//	{
//		pTimeConsumption[k].resize(pMachines[k]);
//	}
//
//	for (int i = 0; i < InStage; i++)
//	{
//		pTimeConsumption[i][0] = 3 + rand() % 3;  //[3-5]
//		for (int j = 0; j < pMachines[i]; j++)
//		{
//			pTimeConsumption[i][j] = pTimeConsumption[i][0];
//
//		}
//	}
//
//	BlockTime.resize(InStage);
//	for (int k = 0; k < InStage; k++)
//	{
//		BlockTime[k].resize(pMachines[k]);
//	}
//
//	BlockConsumption.resize(InStage);
//	for (int k = 0; k < InStage; k++)
//	{
//		BlockConsumption[k].resize(pMachines[k]);
//	}
//
//	for (int k = 0; k < InStage; k++)
//	{
//		BlockConsumption[k][0] = 5 + rand() % 3;  //[5-7]
//		for (int i = 0; i < pMachines[k]; i++)
//		{
//			BlockConsumption[k][i] = BlockConsumption[k][0];  //[5-7]
//		}
//	}
//
//	IdleTime.resize(InStage);
//	for (int k = 0; k < InStage; k++)
//	{
//		IdleTime[k].resize(pMachines[k]);
//	}
//
//	IdleConsumption.resize(InStage);
//	for (int k = 0; k < InStage; k++)
//	{
//		IdleConsumption[k].resize(pMachines[k]);
//	}
//
//	for (int k = 0; k < InStage; k++)
//	{
//		IdleConsumption[k][0] = 1 + rand() % 3;  //[1-3]
//		for (int i = 0; i < pMachines[k]; i++)
//		{
//			IdleConsumption[k][i] = IdleConsumption[k][0];  //[1-3]
//		}
//	}
//	/*for (int m = 0; m < InStage; m++)
//	{
//		for (int j = 0; j < gJobs; j++)
//		{
//			for (int i = 0; i < gJobs; i++)
//			{
//				int value;
//				infile >> value;
//				pSetupTime[m][j][i] = value;
//			}
//		}
//	}*/
//	infile.close();
//}

double GetTemperature(double Tem)
{
	double Temperature = 0;
	for (int j = 0; j<gJobs; j++)
	{
		for (int m = 0; m< InStage; m++)
			Temperature += pTime[j][m];
	}
	Temperature /= gJobs* InStage * 10.0;
	Temperature *= Tem;
	return Temperature;
}

double GetTemperature02(double Tem)
{
	double Temperature = 0;
	int totalPtime = 0;
	for (int j = 0; j < gJobs; ++j)
	{
		for (int k = 0; k < InStage; ++k)
		{
			totalPtime += pTime[j][k];
		}
	}
	Temperature = (totalPtime / 10.0 * gJobs * InStage) * 0.40;
	return Temperature;
}


int GetFspan(vector<int> Seq)
{
	int Makespan = 0;
	if (Seq.size() == 0)
		Makespan = 0;
	else
	{
		/*vector<int> mIdleTime(gMachine, 0);
		vector<vector<int>>	jCTime(Seq.size());
		for (int j = 0; j < jCTime.size(); j++)
			jCTime[j].resize(gMachine, 0);

		int Job = Seq[0];
		jCTime[0][0] = mIdleTime[0] + pSetupTime[0][Job][Job] + pTime[Job][0];
		for (int i = 1; i < gMachine; i++)
			jCTime[0][i] = max(mIdleTime[i] + pSetupTime[i][Job][Job], jCTime[0][i - 1]) + pTime[Job][i];
		mIdleTime = jCTime[0];

		for (int j = 1; j < Seq.size(); j++)
		{
			int PreJob = Seq[j - 1];
			int Job = Seq[j];
			jCTime[j][0] = mIdleTime[0] + pSetupTime[0][PreJob][Job] + pTime[Job][0];
			for (int i = 1; i < gMachine; i++)
				jCTime[j][i] = max(mIdleTime[i] + pSetupTime[i][PreJob][Job], jCTime[j][i - 1]) + pTime[Job][i];
			mIdleTime = jCTime[j];
		}

		Span = jCTime[Seq.size() - 1][gMachine - 1];*/
		vector<vector<int>> STime, CTime, BlockingStartTime;
		vector<vector<int>> mIdleTime;   //机器开始空闲的时间

	/*	int pTimeTotalConsumption = 0;
		int BlockTotalConsumption = 0;
        int IdleTotalConsumption = 0;*/

		mIdleTime.resize(InStage);

		for (int k = 0; k < InStage; k++)
		{
			mIdleTime[k].resize(pMachines[k]);

		}


		//all machines are availale at 0  其实可以不用要 默认都为0
		for (int k = 0; k < InStage; k++)
		{
			for (int i = 0; i < pMachines[k]; i++)
			{
				mIdleTime[k][i] = 0;
			}
		}

		BlockTime = mIdleTime;
		IdleTime = mIdleTime;
		

	/*	for (int i = 0; i < Seq.size(); i++)
		{
			for (int j = 0; j < InStage; j++)
			{
				pTimeTotalConsumption = pTimeTotalConsumption + pTime[Seq[i]][j] * pTimeConsumption[j][0];

			}
		}*/


		STime.resize(InStage);
		
		for (int k = 0; k < InStage; k++)
		{
			STime[k].resize(gJobs);
		}
		for (int i = 0; i < InStage; ++i)
		{
			for (int j = 0; j < gJobs; ++j) {
				
				STime[i][j] = 0;

			}
		}

		CTime = STime;
		BlockingStartTime = STime;

		int mpt1 = INT_MAX;

		for (int j = 0; j < Seq.size(); ++j)
		{
			for (int k = 0; k < InStage; ++k)
			{
				//Select a machine
				int mpt, minIdle = INT_MAX;

				//选出最先空闲机器
				for (int i = 0; i < pMachines[k]; i++)
				{
					if (mIdleTime[k][i] < minIdle)
					{
						minIdle = mIdleTime[k][i];
						mpt = i;
					}

				}

				//第1阶段机器开始的时间

				if (k == 0) { STime[k][Seq[j]] = minIdle; mpt1 = mpt; }

				//其他阶段
				else {
					STime[k][Seq[j]] = max(minIdle, CTime[k - 1][Seq[j]]);

					if (minIdle >= CTime[k - 1][Seq[j]])
					{
						BlockTime[k - 1][mpt1] = minIdle - CTime[k - 1][Seq[j]];
						BlockingStartTime[k - 1][Seq[j]] = CTime[k - 1][Seq[j]];
						/*BlockTotalConsumption += BlockTime[k - 1][mpt1] * BlockConsumption[k - 1][mpt1];*/
					}

					else if (minIdle < CTime[k - 1][Seq[j]])
					{
						IdleTime[k][mpt] = CTime[k - 1][Seq[j]] - minIdle;
						/*IdleTotalConsumption += IdleTime[k][mpt] * IdleConsumption[k][mpt];*/
					}
					
					CTime[k - 1][Seq[j]] = STime[k][Seq[j]];
					mIdleTime[k - 1][mpt1] = CTime[k - 1][Seq[j]];
					mpt1 = mpt;
				}
				CTime[k][Seq[j]] = STime[k][Seq[j]] + pTime[Seq[j]][k];
				mIdleTime[k][mpt] = CTime[k][Seq[j]];

			}

		}
		
		/*Makespan = pTimeTotalConsumption + IdleTotalConsumption + BlockTotalConsumption;*/
		Makespan = CTime[InStage - 1][Seq[0]];
		for (int j = 1; j < Seq.size(); ++j)
		{
			if (CTime[InStage - 1][Seq[j]] > Makespan)
			{
				Makespan = CTime[InStage - 1][Seq[j]];
			}
		}
		
	}
	
	return Makespan;
}

void GetFspan01(vector<int> Seq, int f)
{
	int TotalConsumption = 0;
	if (Seq.size() == 0)
		TotalConsumption = 0;
	else
	{
		/*vector<int> mIdleTime(gMachine, 0);
		vector<vector<int>>	jCTime(Seq.size());
		for (int j = 0; j < jCTime.size(); j++)
			jCTime[j].resize(gMachine, 0);

		int Job = Seq[0];
		jCTime[0][0] = mIdleTime[0] + pSetupTime[0][Job][Job] + pTime[Job][0];
		for (int i = 1; i < gMachine; i++)
			jCTime[0][i] = max(mIdleTime[i] + pSetupTime[i][Job][Job], jCTime[0][i - 1]) + pTime[Job][i];
		mIdleTime = jCTime[0];

		for (int j = 1; j < Seq.size(); j++)
		{
			int PreJob = Seq[j - 1];
			int Job = Seq[j];
			jCTime[j][0] = mIdleTime[0] + pSetupTime[0][PreJob][Job] + pTime[Job][0];
			for (int i = 1; i < gMachine; i++)
				jCTime[j][i] = max(mIdleTime[i] + pSetupTime[i][PreJob][Job], jCTime[j][i - 1]) + pTime[Job][i];
			mIdleTime = jCTime[j];
		}

		Span = jCTime[Seq.size() - 1][gMachine - 1];*/
		vector<vector<int>> STime, CTime,BlockingStartTime;
		vector<vector<int>> mIdleTime;   //机器开始空闲的时间
		vector<vector<int>> RecordMachine; //记录机器编号
		RecordMachine.resize(InStage);
		mIdleTime.resize(InStage);

		int pTimeTotalConsumption = 0;
		int BlockTotalConsumption = 0;

		int IdleTotalConsumption = 0;

		for (int k = 0; k < InStage; k++)
		{
			mIdleTime[k].resize(pMachines[k]);

		}

		for (int k = 0; k < InStage; k++)
		{
			RecordMachine[k].resize(gJobs);

		}
		//all machines are availale at 0  其实可以不用要 默认都为0
		for (int k = 0; k < InStage; k++)
		{
			for (int i = 0; i < pMachines[k]; i++)
			{
				mIdleTime[k][i] = 0;
			}
		}

		for (int k = 0; k < InStage; k++)
		{
			for (int i = 0; i < Seq.size(); i++)
			{
				RecordMachine[k][i] = 0;
			}
		}

		BlockTime = mIdleTime;
		IdleTime = mIdleTime;


		for (int i = 0; i < Seq.size(); i++)
		{
			for (int j = 0; j < InStage; j++)
			{
				pTimeTotalConsumption = pTimeTotalConsumption + pTime[i][j] * pTimeConsumption[j][0];

			}
		}


		STime.resize(InStage);

		for (int k = 0; k < InStage; k++)
		{
			STime[k].resize(gJobs);
		}
		for (int i = 0; i < InStage; ++i)
		{
			for (int j = 0; j < gJobs; ++j) {
				STime[i][j] = 0;

			}
		}

		CTime = STime;
		BlockingStartTime = STime;

		int mpt1 = INT_MAX;

		for (int j = 0; j < Seq.size(); ++j)
		{
			for (int k = 0; k < InStage; ++k)
			{
				//Select a machine
				int mpt, minIdle = INT_MAX;

				//选出最先空闲机器
				for (int i = 0; i < pMachines[k]; i++)
				{
					if (mIdleTime[k][i] < minIdle)
					{
						minIdle = mIdleTime[k][i];
						mpt = i;
					}

				}

				//第1阶段机器开始的时间
				//if (Seq[j] == -1)break;//IG算法用到判断

				if (k == 0) { STime[k][Seq[j]] = minIdle; mpt1 = mpt; RecordMachine[k][Seq[j]] = mpt;}

				//其他阶段
				else {
					STime[k][Seq[j]] = max(minIdle, CTime[k - 1][Seq[j]]);

					if (minIdle >= CTime[k - 1][Seq[j]])
					{
						BlockTime[k - 1][mpt1] = minIdle - CTime[k - 1][Seq[j]];
						BlockingStartTime[k - 1][Seq[j]] = CTime[k - 1][Seq[j]];
						BlockTotalConsumption += BlockTime[k - 1][mpt1] * BlockConsumption[k - 1][mpt1];
						RecordMachine[k][Seq[j]] = mpt1;
					}

					else if (minIdle < CTime[k - 1][Seq[j]])
					{
						IdleTime[k][mpt] = CTime[k - 1][Seq[j]] - minIdle;

						IdleTotalConsumption += IdleTime[k][mpt] * IdleConsumption[k][mpt];
						RecordMachine[k][Seq[j]] = mpt;
					}
					
					CTime[k - 1][Seq[j]] = STime[k][Seq[j]];
					mIdleTime[k - 1][mpt1] = CTime[k - 1][Seq[j]];
					mpt1 = mpt;
					RecordMachine[k][Seq[j]] = mpt1;
				}
				CTime[k][Seq[j]] = STime[k][Seq[j]] + pTime[Seq[j]][k];
				mIdleTime[k][mpt] = CTime[k][Seq[j]];
				RecordMachine[k][Seq[j]] = mpt;
			}



		}
		
		//flowshopGantt
		char fileName1[30];
		FILE* f3;
		sprintf(fileName1, "IG_BLOCK_Gantt.txt");
		f3 = fopen(fileName1, "a+");

		fprintf(f3, "工厂编号:");
		fprintf(f3, "%d \n", f);
		for (int j = 0; j < Seq.size(); ++j)
		{
			for (int k = 0; k < InStage; ++k)
			{
				fprintf(f3, "工件编号:");
				fprintf(f3, "%d ", Seq[j]);
				fprintf(f3, "阶段编号:");
				fprintf(f3, "%d ", k);
				fprintf(f3, "机器编号:");
				fprintf(f3, "%d ", RecordMachine[k][Seq[j]]);
				fprintf(f3, "开始时间:");
				fprintf(f3, "%d ", STime[k][Seq[j]]);
				fprintf(f3, "结束时间:");
				fprintf(f3, "%d ", CTime[k][Seq[j]]);
				fprintf(f3, "机器开始阻塞时间:");
				fprintf(f3, "%d ", BlockingStartTime[k][Seq[j]]);
				fprintf(f3, "\n");
			}
			fprintf(f3, "\n");


		}
		fclose(f3);
	
		int TotalConsumption = 0;

		TotalConsumption = pTimeTotalConsumption + IdleTotalConsumption + BlockTotalConsumption;
		/*return TotalConsumption;*/

	}


}

int GetFspan_block(vector<int> Seq, vector<int> &blockingJobs, vector<int>& blockingJobsPos)
{

	int TotalConsumption = 0;
	if (Seq.size() == 0)
		TotalConsumption = 0;
	else
	{
		
		vector<vector<int>> STime, CTime, BlockingStartTime;
		vector<vector<int>> mIdleTime;   //机器开始空闲的时间

		int pTimeTotalConsumption = 0;
		int BlockTotalConsumption = 0;
		int IdleTotalConsumption = 0;

		mIdleTime.resize(InStage);

		for (int k = 0; k < InStage; k++)
		{
			mIdleTime[k].resize(pMachines[k]);

		}


		//all machines are availale at 0  其实可以不用要 默认都为0
		for (int k = 0; k < InStage; k++)
		{
			for (int i = 0; i < pMachines[k]; i++)
			{
				mIdleTime[k][i] = 0;
			}
		}

		BlockTime = mIdleTime;
		IdleTime = mIdleTime;


		for (int i = 0; i < Seq.size(); i++)
		{
			for (int j = 0; j < InStage; j++)
			{
				pTimeTotalConsumption = pTimeTotalConsumption + pTime[Seq[i]][j] * pTimeConsumption[j][0];

			}
		}


		STime.resize(InStage);

		for (int k = 0; k < InStage; k++)
		{
			STime[k].resize(gJobs);
		}
		for (int i = 0; i < InStage; ++i)
		{
			for (int j = 0; j < gJobs; ++j) {

				STime[i][j] = 0;

			}
		}

		CTime = STime;
		BlockingStartTime = STime;

		int blockPos = 0;

		int mpt1 = INT_MAX;

		for (int j = 0; j < Seq.size(); ++j)
		{
			for (int k = 0; k < InStage; ++k)
			{
				//Select a machine
				int mpt, minIdle = INT_MAX;

				//选出最先空闲机器
				for (int i = 0; i < pMachines[k]; i++)
				{
					if (mIdleTime[k][i] < minIdle)
					{
						minIdle = mIdleTime[k][i];
						mpt = i;
					}

				}

				//第1阶段机器开始的时间

				if (k == 0) 
				{ 
					STime[k][Seq[j]] = minIdle; mpt1 = mpt;
					
				  				
				}

				//其他阶段
				else {
					STime[k][Seq[j]] = max(minIdle, CTime[k - 1][Seq[j]]);

					if (minIdle > CTime[k - 1][Seq[j]])
					{
						BlockTime[k - 1][mpt1] = minIdle - CTime[k - 1][Seq[j]];
						BlockingStartTime[k - 1][Seq[j]] = CTime[k - 1][Seq[j]];
						BlockTotalConsumption += BlockTime[k - 1][mpt1] * BlockConsumption[k - 1][mpt1];
						
						if (k == 1) {
							blockingJobs.insert(blockingJobs.begin() + blockPos, Seq[j]);
							blockingJobsPos.insert(blockingJobsPos.begin() + blockPos, j);
							blockPos++;
								
						}
						
					}

					else if (minIdle < CTime[k - 1][Seq[j]])
					{
						IdleTime[k][mpt] = CTime[k - 1][Seq[j]] - minIdle;

						IdleTotalConsumption += IdleTime[k][mpt] * IdleConsumption[k][mpt];
					}
					
					CTime[k - 1][Seq[j]] = STime[k][Seq[j]];
					mIdleTime[k - 1][mpt1] = CTime[k - 1][Seq[j]];
					mpt1 = mpt;
				}
				CTime[k][Seq[j]] = STime[k][Seq[j]] + pTime[Seq[j]][k];
				mIdleTime[k][mpt] = CTime[k][Seq[j]];

			}

		}

		TotalConsumption = pTimeTotalConsumption + IdleTotalConsumption + BlockTotalConsumption;
	}

	return TotalConsumption;
}

int GetFspan(vector<vector<int>> Sol)
{
	int TMakespan = 0;
	for (int f = 0; f < Sol.size(); f++)
	{
		int Makespan = GetFspan(Sol[f]);
		if (Makespan > TMakespan)
		{
			TMakespan = Makespan;
		}
	}
	return TMakespan;
}


void GetFspan01(vector<vector<int>> Sol)
{
	
	for (int f = 0; f < Sol.size(); f++)
	{
		GetFspan01(Sol[f],f);   
	}
	
}

//void GetFseq(vector<vector<int>> Sol)
//{
//	
//	for (int f = 0; f < Sol.size(); f++)
//	{
//		GetFseq01(Sol[f]);
//
//	}
//}
//
//void GetFseq01(vector<int> Seq)
//{
//	
//	for (int i = 0; i < Seq.size(); ++i)
//	{
//		
//	}
//
//}




void CheckChrom(vector <int>p, int Span = -1)
{
	vector <bool> bExist(p.size(), false);
	for (int i = 0; i<p.size(); i++)
	{
		bExist[p[i]] = true;
	}

	for (int i = 0; i<p.size(); i++)
	{
		if (!bExist[i]) printf("/nchrom is error!/n");
	}

	if (Span>0)
	{
		int TempSpan = GetFspan(p);
		if (TempSpan != Span)
			printf("\nChrom is Error!");
	}
}

void CheckChrom(vector<vector <int>> Sol, int Span = -1)
{
	vector <bool> bExist(gJobs, false);

	for (int f = 0; f < Sol.size(); f++)
	{
		for (int j = 0; j < Sol[f].size(); j++)
			bExist[Sol[f][j]] = true;
	}

	for (int i = 0; i<bExist.size(); i++)
	{
		if (!bExist[i]) printf("/nchrom is error! Job %d is lost", i);
	}

	if (Span>0)
	{
		int TempSpan = GetFspan(Sol);
		if (TempSpan != Span)
			printf("\n Span is Error! %d,%d", TempSpan, Span);
	}
}

//int GetEij(vector<int>Seq, vector<vector<int>>&Eij)
//{
//	//vector<int> mIdleTime(gMachine, 0);
//	Eij.clear();
//	Eij.resize(Seq.size());
//	for (int j = 0; j < Eij.size(); j++)
//		Eij[j].resize(InStage, 0);  ////
//
//	//int Job = Seq[0];
//	//Eij[0][0] = mIdleTime[0] + pSetupTime[0][Job][Job] + pTime[Job][0];
//	//for (int i = 1; i < gMachine; i++)
//	//	Eij[0][i] = max(mIdleTime[i] + pSetupTime[i][Job][Job], Eij[0][i - 1]) + pTime[Job][i];
//	//mIdleTime = Eij[0];
//
//	//for (int j = 1; j < Seq.size(); j++)
//	//{
//	//	int PreJob = Seq[j - 1];
//	//	int Job = Seq[j];
//	//	Eij[j][0] = mIdleTime[0] + pSetupTime[0][PreJob][Job] + pTime[Job][0];
//	//	for (int i = 1; i < gMachine; i++)
//	//		Eij[j][i] = max(mIdleTime[i] + pSetupTime[i][PreJob][Job], Eij[j][i - 1]) + pTime[Job][i];
//	//	mIdleTime = Eij[j];
//	//}
//	//return	Eij[Seq.size() - 1][gMachine - 1];
//	vector<vector<int>> STime, CTime;
//	vector<vector<int>> mIdleTime;   //机器开始空闲的时间
//
//	mIdleTime.resize(InStage);
//
//	//int pTimeTotalConsumption = 0;
//	//int BlockTotalConsumption = 0;
//
//	//int IdleTotalConsumption = 0;
//
//	for (int k = 0; k < InStage; k++)
//	{
//		mIdleTime[k].resize(pMachines[k]);
//
//	}
//
//
//	//all machines are availale at 0  其实可以不用要 默认都为0
//	for (int k = 0; k < InStage; k++)
//	{
//		for (int i = 0; i < pMachines[k]; i++)
//		{
//			mIdleTime[k][i] = 0;
//		}
//	}
//
//
//
//	BlockTime = mIdleTime;
//	IdleTime = mIdleTime;
//	
//	STime.resize(InStage);
//
//	for (int k = 0; k < InStage; k++)
//	{
//		STime[k].resize(gJobs);
//	}
//	for (int i = 0; i < InStage; ++i)
//	{
//		for (int j = 0; j < gJobs; ++j) {
//			STime[i][j] = 0;
//
//		}
//	}
//
//	CTime = STime;
//
//	for (int j = 0; j < Seq.size(); ++j)
//	{
//		for (int i = 0; i < InStage; ++i)
//		{
//			Eij[j][i] = 0;
//		}
//	}
//
//	int mpt1 = INT_MAX;
//
//	for (int j = 0; j < Seq.size(); ++j)
//	{
//		for (int k = 0; k < InStage; ++k)
//		{
//			//Select a machine
//			int mpt, minIdle = INT_MAX;
//
//			//选出最先空闲机器
//			for (int i = 0; i < pMachines[k]; i++)
//			{
//				if (mIdleTime[k][i] < minIdle)
//				{
//					minIdle = mIdleTime[k][i];
//					mpt = i;
//				}
//
//			}
//
//			//第1阶段机器开始的时间
//			//if (Seq[j] == -1)break;//IG算法用到判断
//
//			if (k == 0) { STime[k][Seq[j]] = minIdle; mpt1 = mpt; }
//
//			//其他阶段
//			else {
//				STime[k][Seq[j]] = max(minIdle, Eij[Seq[j]][k - 1]);
//
//				if (minIdle >= Eij[Seq[j]][k - 1])
//				{
//					BlockTime[k - 1][mpt1] = minIdle - Eij[Seq[j]][k - 1];
//					
//					//BlockTotalConsumption += BlockTime[k - 1][mpt1] * BlockConsumption[k - 1][mpt1];
//				}
//
//				else if (minIdle < CTime[k - 1][Seq[j]])
//				{
//					IdleTime[k][mpt] = CTime[k - 1][Seq[j]] - minIdle;
//
//				}
//
//				CTime[k - 1][Seq[j]] = STime[k][Seq[j]];
//				mIdleTime[k - 1][mpt1] = CTime[k - 1][Seq[j]];
//				mpt1 = mpt;
//			}
//			CTime[k][Seq[j]] = STime[k][Seq[j]] + pTime[k][Seq[j]];
//			mIdleTime[k][mpt] = CTime[k][Seq[j]];
//
//		}
//
//
//
//	}
//
//	int TF = -1;
//	for (int i = 0; i < Seq.size(); i++)
//	{
//		if (CTime[InStage - 1][i] > TF)
//		{
//			TF = CTime[InStage - 1][i];
//		}
//	}
//	TF;
//	return TF;
//
//}
//
//int GetQij(vector<int>Seq, vector<vector<int>>&Qij)
//{
//	Qij.clear();
//	Qij.resize(Seq.size());
//	for (int j = 0; j < Qij.size(); j++)
//		Qij[j].resize(gMachine, 0);  ////
//
//	//最后一个工件的求法
//	int xx = Seq.size() - 1;
//	int CurJob = Seq[xx];
//	Qij[xx][gMachine - 1] = pTime[CurJob][gMachine - 1];
//	for (int m = gMachine - 2; m >= 0; m--)
//		Qij[xx][m] = Qij[xx][m + 1] + pTime[CurJob][m];
//
//	//other jobs
//	for (int j = Seq.size() - 2; j >= 0; j--)
//	{
//		int CurJob = Seq[j];
//		int NextJob = Seq[j + 1];
//		Qij[j][gMachine - 1] = Qij[j + 1][gMachine - 1] + pSetupTime[gMachine - 1][CurJob][NextJob] + pTime[CurJob][gMachine - 1];
//		for (int m = gMachine - 2; m >= 0; m--)
//			Qij[j][m] = max(Qij[j][m + 1], Qij[j + 1][m] + pSetupTime[m][CurJob][NextJob]) + pTime[CurJob][m];
//	}
//
//	//第一个工件的求法
//	CurJob = Seq[0];
//	vector<int> Qij_Job0(gMachine, 0);
//	for (int m = gMachine - 1; m >= 0; m--)
//		Qij_Job0[m] = Qij[0][m] + pSetupTime[m][CurJob][CurJob];
//
//	int Span = 0;
//	for (int m = 0; m < gMachine; m++)
//	if (Span < Qij_Job0[m])
//		Span = Qij_Job0[m];
//	return Span;
//}

//为某个工件Job找到最好的插入位置
int FindBestInsertionPositon(int &BestPos, int Job, vector<int>&Seq)
{
	int minEC = INT_MAX;
	vector<int>Fij;
	Fij.resize(Seq.size() + 1,0);

	for (int i = 0; i < Seq.size(); ++i)
	{
		Fij[i] = Seq[i];
	}
	
	for (int Pos = 0; Pos < Fij.size(); Pos++)
	{
		
		int TEC = 0;
		if (Pos == (Fij.size() - 1))
		{
			Fij[Pos] = Job;
		}
		else
		{
			for (int j = Fij.size() - 2; j >= Pos; --j)
			{
				Fij[j + 1] = Fij[j];
			}
			Fij[Pos] = Job;
		}

		TEC = GetFspan(Fij);
		//if (Pos == Seq.size())
		//{
		//	int PreJob = Seq[Pos - 1];
		//	Fij[Pos][0] = Eij[Pos - 1][0] + pSetupTime[0][PreJob][Job] + pTime[Job][0];
		//	for (int m = 1; m < gMachine; m++)
		//		Fij[Pos][m] = max(Eij[Pos - 1][m] + pSetupTime[m][PreJob][Job], Fij[Pos][m - 1]) + pTime[Job][m];

		//	TSpan = Fij[Pos][gMachine - 1];
		//}
		//else if (Pos == 0)
		//{
		//	int NextJob = Seq[Pos];                        //
		//	Fij[Pos][0] = pSetupTime[0][Job][Job] + pTime[Job][0];
		//	for (int m = 1; m < gMachine; m++)
		//		Fij[Pos][m] = max(Fij[Pos][m - 1], pSetupTime[m][Job][Job]) + pTime[Job][m];
		//	TSpan = Qij[Pos][0] + Fij[Pos][0] + pSetupTime[0][Job][NextJob];                 //
		//	for (int m = 1; m < gMachine; m++)
		//	{
		//		int t = Qij[Pos][m] + Fij[Pos][m] + pSetupTime[m][Job][NextJob];            //
		//		if (t>TSpan) TSpan = t;
		//	}
		//}
		//else
		//{
		//	int PreJob = Seq[Pos - 1];
		//	Fij[Pos][0] = Eij[Pos - 1][0] + pSetupTime[0][PreJob][Job] + pTime[Job][0];
		//	for (int m = 1; m < gMachine; m++)
		//		Fij[Pos][m] = max(Eij[Pos - 1][m] + pSetupTime[m][PreJob][Job], Fij[Pos][m - 1]) + pTime[Job][m];

		//	int NextJob = Seq[Pos];         //
		//	TSpan = Qij[Pos][0] + Fij[Pos][0] + pSetupTime[0][Job][NextJob];             //
		//	for (int m = 1; m < gMachine; m++)
		//	{
		//		int t = Qij[Pos][m] + pSetupTime[m][Job][NextJob] + Fij[Pos][m];   //这里好像不行，当m=gMachine-1的时候，m+1是取不到值的
		//		if (t>TSpan) TSpan = t;        //将上面的  Qij[Pos][m + 1]改为Qij[Pos][m -1]
		//	}
		//}
		if (TEC < minEC)
		{
			minEC = TEC;
			BestPos = Pos;
		}

		Fij.clear();
		for (int i = 0; i < Seq.size(); ++i)
		{
			Fij[i] = Seq[i];
		}
	}

	return minEC;
}


int FindBestSwapPositon(int& BestPos, int Job, vector<int> Seq)
{
	int minEC = GetFspan(Seq);
	vector<int>Fij;
	Fij.resize(Seq.size(), 0);

	for (int i = 0; i < Seq.size(); ++i)
	{
		Fij[i] = Seq[i];
	}
	int temp;
	for (int Pos = 0; Pos < Fij.size(); Pos++)
	{
		int TEC = 0;
		int tempJob = Job;

		
		temp = Fij[Pos];
		Fij[Pos] = tempJob;
		tempJob = temp;
		

		TEC = GetFspan(Fij);
	
		if (TEC < minEC)
		{
			minEC = TEC;
			BestPos = Pos;
		}

		Fij.clear();
		for (int i = 0; i < Seq.size(); ++i)
		{
			Fij[i] = Seq[i];
		}
	}

	return minEC;
}

// 一个工件在某个工厂找到最好得位置
int Job_To_SomeFactory_Bestposition(int Job, vector<int>&Seq)   /////
{
	int minEC = 0, BestPos = -1;
	if (Seq.size() == 0)
	{
		for (int m = 0; m < InStage; m++)
			minEC = 0; /** pTimeConsumption[m][0]*/
		BestPos = 0;
	}
	else
	{
	/*	GetQij(Seq, pQij);
		GetEij(Seq, pEij);*/
		minEC = FindBestInsertionPositon(BestPos, Job, Seq);
	}

	//将工件插入最好的位置
	Seq.insert(Seq.begin() + BestPos, Job);
	int EC = GetFspan(Seq);

	return EC;
}

int Job_To_SomeFactory_Bestposition(int Job, int &BestPos, vector<int>&Seq)
{
	/*vector<vector<int>>pEij;
	pEij.resize(Seq.size());
	for (int j = 0; j < Seq.size(); j++)
	{
		pEij[j].resize(gMachine);
		for (int m = 0; m < gMachine; m++)
			pEij[j][m] = 0;
	}

	vector<vector<int>>pQij;
	pQij.resize(Seq.size());
	for (int j = 0; j < Seq.size(); j++)
	{
		pQij[j].resize(gMachine);
		for (int m = 0; m < gMachine; m++)
			pQij[j][m] = 0;
	}*/

	int minEC = INT_MAX;
	if (Seq.size() == 0)
	{
		for (int m = 0; m < InStage; m++)
			minEC += pTime[Job][m] * pTimeConsumption[m][0];
		BestPos = 0;
	}
	else
	{
		/*GetQij(Seq, pQij);
		GetEij(Seq, pEij);*/
		minEC = FindBestInsertionPositon(BestPos, Job, Seq);
	}

	//将工件插入最好的位置
	Seq.insert(Seq.begin() + BestPos, Job);
	int EC = minEC;

	return EC;
}

//一个工件在所有的工厂里找到最好的工厂最好的位置
int Job_To_BestFactory_Bestposition(int Job, vector<vector<int>>&Sol)
{
	//先将每个工厂的EC都初始化为0
	vector<int>FactorySpan;
	FactorySpan.resize(Sol.size(), 0);    //

	for (int f = 0; f < Sol.size(); f++)     //
		FactorySpan[f] = GetFspan(Sol[f]);     //

	//初始化pEij，pQij，EijFlag几个数组
	/*vector<vector<vector<int>>>pEij(gFactory), pQij;
	for (int fac = 0; fac < gFactory; fac++)
	{
		pEij[fac].resize(Sol[fac].size());
		for (int j = 0; j < Sol[fac].size(); j++)
		{
			pEij[fac][j].resize(InStage);
			for (int m = 0; m < InStage; m++)
				pEij[fac][j][m] = 0;
		}
	}
	pQij = pEij;*/

	vector<bool>EijFlag;
	EijFlag.resize(gFactory);
	for (int fac = 0; fac < gFactory; fac++)
		EijFlag[fac] = false;

	vector<int>minPTime;
	minPTime.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
	{
		int TempminPTime = INT_MAX;
		for (int m = 0; m < InStage; m++)
		{
			if (pTime[j][m] < TempminPTime)
				TempminPTime = pTime[j][m];
		}
		minPTime[j] = TempminPTime;
	}

	//Test the job at all the factories, and select the best position
	int SelFac = 0, minTSpan = INT_MAX, BestPos = -1;
	for (int fac = 0; fac < gFactory; fac++)
	{
		if (Sol[fac].size() == 0)
		{
			minTSpan = 0;
			for (int m = 0; m < InStage; m++)
				minTSpan += pTime[Job][m] /** pTimeConsumption[m][0]*/;
			BestPos = 0;
			SelFac = fac;
			break;
		}
		if (!(FactorySpan[fac] + minPTime[Job] < minTSpan))  //minPTime[Job]为工件Job的最小处理时间
			continue;
		if (!EijFlag[fac])
		{
			/*GetQij(Sol[fac], pQij[fac]);
			GetEij(Sol[fac], pEij[fac]);*/
			EijFlag[fac] = true;
		}

		int TempSpan = 0, TempPos = -1;      //////
		TempSpan = FindBestInsertionPositon(TempPos, Job, Sol[fac]);
		if (TempSpan < minTSpan)
		{
			minTSpan = TempSpan;
			BestPos = TempPos;
			SelFac = fac;
		}
	}

	//将工件插入最好的位置
	Sol[SelFac].insert(Sol[SelFac].begin() + BestPos, Job);
	FactorySpan[SelFac] = minTSpan;
	EijFlag[SelFac] = false;

	int total = 0;
	for (int i = 0; i < Sol.size(); ++i)
	{
		total += FactorySpan[i];
	}
	return total;/**max_element(FactorySpan.begin(), FactorySpan.end());*/
}

int Job_To_BestFactory_Bestposition(int Job, vector<vector<int>>&Sol, int &SelFac, int &BestPos)
{
	//先将每个工厂的EC都初始化为0
	vector<int>FactorySpan;
	FactorySpan.resize(Sol.size(), 0);    //

	for (int f = 0; f < Sol.size(); f++)     //
		FactorySpan[f] = GetFspan(Sol[f]);   //

	//初始化pEij，pQij，EijFlag几个数组
	//vector<vector<vector<int>>>pEij(gFactory), pQij;
	//for (int fac = 0; fac < gFactory; fac++)
	//{
	//	pEij[fac].resize(Sol[fac].size());
	//	for (int j = 0; j < Sol[fac].size(); j++)
	//	{
	//		pEij[fac][j].resize(gMachine);
	//		for (int m = 0; m < gMachine; m++)
	//			pEij[fac][j][m] = 0;
	//	}
	//}
	//pQij = pEij;

	vector<bool>EijFlag;
	EijFlag.resize(gFactory);
	for (int fac = 0; fac < gFactory; fac++)
		EijFlag[fac] = false;

	vector<int>minPTime;
	minPTime.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
	{
		int TempminPTime = INT_MAX;
		for (int m = 0; m < InStage; m++)
		{
			if (pTime[j][m] < TempminPTime)
				TempminPTime = pTime[j][m];
		}
		minPTime[j] = TempminPTime;
	}

	//Test the job at all the factories, and select the best position
	int  minEC = INT_MAX;
	for (int fac = 0; fac < gFactory; fac++)
	{
		if (Sol[fac].size() == 0)
		{
			minEC = 0;
			for (int m = 0; m < InStage; m++)
				minEC += pTime[Job][m] /** pTimeConsumption[m][0]*/;
			BestPos = 0;
			SelFac = fac;
			break;
		}
		//if (!(FactorySpan[fac] + minPTime[Job] < minTSpan))  //minPTime[Job]为工件Job的最小处理时间
		//	continue;
		if (!EijFlag[fac])
		{
			/*GetQij(Sol[fac], pQij[fac]);
			GetEij(Sol[fac], pEij[fac]);*/
			EijFlag[fac] = true;
		}

		int TempEC = 0, TempPos = -1;      //////
		TempEC = FindBestInsertionPositon(TempPos, Job, Sol[fac]);
		if (TempEC < minEC)
		{
			minEC = TempEC;
			BestPos = TempPos;
			SelFac = fac;
		}
	}

	//将工件插入最好的位置
	Sol[SelFac].insert(Sol[SelFac].begin() + BestPos, Job);
	FactorySpan[SelFac] = GetFspan(Sol);
	EijFlag[SelFac] = false;
	int total = 0;
	for (int i = 0; i < Sol.size(); ++i)
	{
		total += FactorySpan[i];
	}
	return total;
}


int Job_ToSwap_BestFactory_Bestposition(int maxFac, int i, int Job, vector<vector<int>>& Sol, int& SelFac, int& BestPos)
{
	//先将每个工厂的EC都初始化为0
	vector<int>FactorySpan;
	FactorySpan.resize(Sol.size(), 0);    //

	for (int f = 0; f < Sol.size(); f++)     //
		FactorySpan[f] = GetFspan(Sol[f]);   //

	//初始化pEij，pQij，EijFlag几个数组
	//vector<vector<vector<int>>>pEij(gFactory), pQij;
	//for (int fac = 0; fac < gFactory; fac++)
	//{
	//	pEij[fac].resize(Sol[fac].size());
	//	for (int j = 0; j < Sol[fac].size(); j++)
	//	{
	//		pEij[fac][j].resize(gMachine);
	//		for (int m = 0; m < gMachine; m++)
	//			pEij[fac][j][m] = 0;
	//	}
	//}
	//pQij = pEij;

	vector<bool>EijFlag;
	EijFlag.resize(gFactory);
	for (int fac = 0; fac < gFactory; fac++)
		EijFlag[fac] = false;

	
	int  minEC = INT_MAX;
	for (int fac = 0; fac < gFactory; fac++)
	{
		if (fac != maxFac)
		{
			if (Sol[fac].size() == 0)
			{
				minEC = 0;
				for (int m = 0; m < InStage; m++)
					minEC += pTime[Job][m] /** pTimeConsumption[m][0]*/;
				BestPos = 0;
				SelFac = fac;
				break;
			}
			//if (!(FactorySpan[fac] + minPTime[Job] < minTSpan))  //minPTime[Job]为工件Job的最小处理时间
			//	continue;
			if (!EijFlag[fac])
			{
				/*GetQij(Sol[fac], pQij[fac]);
				GetEij(Sol[fac], pEij[fac]);*/
				EijFlag[fac] = true;
			}

			int TempEC = 0, TempPos = -1;      //////
			TempEC = FindBestSwapPositon(TempPos, Job, Sol[fac]);
			if (TempEC < minEC)
			{
				minEC = TempEC;
				BestPos = TempPos;
				SelFac = fac;
			}
	    }
		
	}

	//交换工件
	if (BestPos != -1)
	{
		Sol[maxFac][i] = Sol[SelFac][BestPos];
		Sol[SelFac][BestPos] = Job;
		FactorySpan[SelFac] = GetFspan(Sol);
		EijFlag[SelFac] = false;
	}
	
	int total = 0;
	for (int i = 0; i < Sol.size(); ++i)
	{
		total += FactorySpan[i];
	}
	return total;
}
////为一个Block找到最好的插入位置
//int FindBestInsertionPositon_for_Block(int &BestPos, vector<int>Block, vector<int>&Seq)
//{
//	int minEC = INT_MAX;
//	vector<int>Fij;
//	Fij.resize(Seq.size() + 1, 0);
//	
//	return minTSpan;
//}
//
////将一个Block插入到某个工厂的最好的位置
//int Block_To_SomeFactory_Bestposition(vector<int>Block, int &BestPos, vector<int>&Seq)
//{
//	vector<vector<int>>pEij(Seq.size()), pQij;
//	for (int j = 0; j < Seq.size(); j++)
//	{
//		pEij[j].resize(gMachine);
//		for (int m = 0; m < gMachine; m++)
//			pEij[j][m] = 0;
//	}
//	pQij = pEij;
//
//	int minTSpan = INT_MAX;
//	if (Seq.size() == 0)
//	{
//		minTSpan = GetFspan(Block);
//		BestPos = 0;
//	}
//	else
//	{
//		minTSpan = FindBestInsertionPositon_for_Block(BestPos, Block, Seq, pEij, pQij);
//	}
//
//	//将Block中的工件插入最好的位置
//	Seq.insert(Seq.begin() + BestPos, Block.begin(), Block.end());
//	return minTSpan;
//}
//
////一个Block在所有的工厂里找到最好的工厂最好的位置
//int Block_To_BestFactory_Bestposition(vector<int>Block, vector<vector<int>>&Sol)
//{
//	//先将每个工厂的makespan都初始化为0
//	vector<int>FactorySpan(gFactory, 0);
//	for (int f = 0; f < Sol.size(); f++)
//		FactorySpan[f] = GetFspan(Sol[f]);
//
//	//建立一个数组保存最原始的拿掉Block的Sol
//	vector<vector<int>>TempSol = Sol;
//
//	//初始化pEij，pQij，EijFlag几个数组
//	vector<vector<vector<int>>> pEij(gFactory), pQij;
//	for (int fac = 0; fac < gFactory; fac++)
//	{
//		pEij[fac].resize(Sol[fac].size());
//		for (int j = 0; j < Sol[fac].size(); j++)
//		{
//			pEij[fac][j].resize(gMachine);
//			for (int m = 0; m < gMachine; m++)
//				pEij[fac][j][m] = 0;
//		}
//	}
//	pQij = pEij;
//
//	vector<bool> EijFlag(gFactory, false);
//
//	//Test the Block at all the factories, and select the best position
//	int SelFac = 0, minTSpan = INT_MAX, BestPos = -1;
//	for (int fac = 0; fac < gFactory; fac++)
//	{
//		if (Sol[fac].size() == 0)
//		{
//			minTSpan = GetFspan(Block);
//			BestPos = 0;
//			SelFac = fac;
//			break;
//		}
//
//		if (!EijFlag[fac])
//		{
//			GetQij(Sol[fac], pQij[fac]);
//			GetEij(Sol[fac], pEij[fac]);
//			EijFlag[fac] = true;
//		}
//
//		int TempSpan = 0, TempPos = -1;
//		TempSpan = FindBestInsertionPositon_for_Block(TempPos, Block, Sol[fac], pEij[fac], pQij[fac]);
//		if (TempSpan < minTSpan)
//		{
//			minTSpan = TempSpan;
//			BestPos = TempPos;
//			SelFac = fac;
//		}
//	}
//
//	Sol = TempSol;   //
//
//	//将Block插入最好的位置
//	Sol[SelFac].insert(Sol[SelFac].begin() + BestPos, Block.begin(), Block.end());
//	FactorySpan[SelFac] = minTSpan;
//	return *max_element(FactorySpan.begin(), FactorySpan.end());
//}
//
////一个Block在所有的工厂里找到最好的工厂最好的位置
//int Block_To_BestFactory_Bestposition(vector<int>Block, vector<vector<int>>&Sol, int &SelFac)
//{
//	//先将每个工厂的makespan都初始化为0
//	vector<int>FactorySpan(gFactory, 0);
//	for (int f = 0; f < Sol.size(); f++)
//		FactorySpan[f] = GetFspan(Sol[f]);
//
//	//建立一个数组保存最原始的拿掉Block的Sol
//	vector<vector<int>>TempSol = Sol;
//
//	//初始化pEij，pQij，EijFlag几个数组
//	vector<vector<vector<int>>> pEij(gFactory), pQij;
//	for (int fac = 0; fac < gFactory; fac++)
//	{
//		pEij[fac].resize(Sol[fac].size());
//		for (int j = 0; j < Sol[fac].size(); j++)
//		{
//			pEij[fac][j].resize(gMachine);
//			for (int m = 0; m < gMachine; m++)
//				pEij[fac][j][m] = 0;
//		}
//	}
//	pQij = pEij;
//
//	vector<bool> EijFlag(gFactory, false);
//
//	//Test the Block at all the factories, and select the best position
//	int minTSpan = INT_MAX, BestPos = -1;
//	for (int fac = 0; fac < gFactory; fac++)
//	{
//		if (Sol[fac].size() == 0)
//		{
//			minTSpan = GetFspan(Block);
//			BestPos = 0;
//			SelFac = fac;
//			break;
//		}
//
//		if (!EijFlag[fac])
//		{
//			
//			EijFlag[fac] = true;
//		}
//
//		int TempSpan = 0, TempPos = -1;
//
//		TempSpan = FindBestInsertionPositon_for_Block(TempPos, Block, Sol[fac], pEij[fac], pQij[fac]);
//		if (TempSpan < minTSpan)
//		{
//			minTSpan = TempSpan;
//			BestPos = TempPos;
//			SelFac = fac;
//		}
//	}
//
//	Sol = TempSol;
//	//将Block插入最好的位置
//	Sol[SelFac].insert(Sol[SelFac].begin() + BestPos, Block.begin(), Block.end());
//	FactorySpan[SelFac] = minTSpan;
//	return *max_element(FactorySpan.begin(), FactorySpan.end());
//}

void GetSpan_Gantt(vector<vector<int>> Seq, int NO)
{
	char FName[100] = "Gantt", Buf[100] = "";
	_itoa_s(NO, Buf, 10);
	strcat_s(FName, Buf);
	strcat_s(FName, ".m");
	ofstream ofile;
	ofile.open(FName);

	for (int f = 0; f < gFactory; f++)
	{
		vector<int> mIdleTime(gMachine, 0);
		vector<vector<int>>jCTime(Seq[f].size());
		for (int j = 0; j < jCTime.size(); j++)
			jCTime[j].resize(gMachine, 0);

		int Job = Seq[f][0];
		jCTime[0][0] = mIdleTime[0] + pSetupTime[0][Job][Job] + pTime[Job][0];

		for (int i = 1; i < gMachine; i++){
			jCTime[0][i] = max(mIdleTime[i] + pSetupTime[i][Job][Job], jCTime[0][i - 1]) + pTime[Job][i];
		}
		mIdleTime = jCTime[0];
		for (int j = 1; j < Seq[f].size(); j++)
		{
			int PreJob = Seq[f][j - 1];
			int Job = Seq[f][j];
			jCTime[j][0] = mIdleTime[0] + pSetupTime[0][PreJob][Job] + pTime[Job][0];
			for (int i = 1; i < gMachine; i++)
			{
				jCTime[j][i] = max(mIdleTime[i] + pSetupTime[i][PreJob][Job], jCTime[j][i - 1]) + pTime[Job][i];
			}
			mIdleTime = jCTime[j];
		}

		for (int j = 0; j < Seq[f].size(); j++)
		{
			if (j == 0)
			{
				int Job = Seq[f][j];
				for (int m = 0; m < gMachine; m++)
				{
					int x = 0;
					int w = pSetupTime[m][Job][Job];
					int y = (f * (gMachine + 1) + m) * 15;
					float h = 10;

					ofile << "rectangle('Position', [";
					ofile << x << "\t";
					ofile << y << "\t";
					ofile << w << "\t";
					ofile << h;
					ofile << "],'FaceColor', [0 .5 .5]);";
					ofile << "text(" << x + w / 2 << "," << y + 5 << "," << "'" << Job << "');";
					ofile << endl;
				}
			}
			else
			{
				int PreJob = Seq[f][j - 1];
				int Job = Seq[f][j];

				for (int m = 0; m < gMachine; m++)
				{
					int x = jCTime[j - 1][m];
					int w = pSetupTime[m][PreJob][Job];
					int y = (f * (gMachine + 1) + m) * 15;
					float h = 10;

					ofile << "rectangle('Position', [";
					ofile << x << "\t";
					ofile << y << "\t";
					ofile << w << "\t";
					ofile << h;
					ofile << "],'FaceColor', [0 .5 .5]);";

					ofile << "text(" << x + w / 2 << "," << y + 5 << "," << "'" << Job << "');";
					ofile << endl;
				}
			}
		}
		//the Gantt chart of pTime
		for (int j = 0; j <Seq[f].size(); j++)
		{
			int Job = Seq[f][j];
			for (int m = 0; m < gMachine; m++)
			{
				int x = jCTime[j][m] - pTime[Job][m];  //
				int w = pTime[Job][m];                 //
				int y = (f * (gMachine + 1) + m) * 15;
				float h = 10;

				ofile << "rectangle('Position', [";
				ofile << x << "\t";
				ofile << y << "\t";
				ofile << w << "\t";
				ofile << h;
				ofile << "]);";
				ofile << "text(" << x + w / 2 << "," << y + 5 << "," << "'" << Job << "');";
				ofile << endl;
			}
		}
	}
	ofile << endl;
	ofile.close();
}

//工厂外部插入
void Exter_Factory_Insert(vector<vector<int>>&Seq)
{
	//随机找到两个工厂
	int  MaxFpt, MinFpt;
	do
	{
		MaxFpt = rand() % Seq.size();
		MinFpt = rand() % Seq.size();
	} while (MaxFpt == MinFpt);

	//选出完工时间最大的那个工厂
	int MaxFactorySpan = GetFspan(Seq[MaxFpt]);
	int MinFactorySpan = GetFspan(Seq[MinFpt]);

	int TempSpan = MaxFactorySpan;
	int TempFpt = MaxFpt;

	if (MaxFactorySpan < MinFactorySpan)
	{
		MaxFactorySpan = MinFactorySpan;
		MaxFpt = MinFpt;
		MinFactorySpan = TempSpan;
		MinFpt = TempFpt;
	}

	//在完工时间大的工厂随机选出一个工件
	vector<int>MinTempSeq = Seq[MinFpt];
	int pt = rand() % Seq[MaxFpt].size();
	int Job = Seq[MaxFpt][pt];

	//将随机取得的工件重新插入到另外一个工厂的最佳位置
	int TempBetterSpan = Job_To_SomeFactory_Bestposition(Job, Seq[MinFpt]);
	if (TempBetterSpan < MaxFactorySpan)
		Seq[MaxFpt].erase(Seq[MaxFpt].begin() + pt);
	else
		Seq[MinFpt] = MinTempSeq;
}

//工厂外部交换
void Exter_Factory_Swap(vector<vector<int>>&Seq)
{
	//随机找到两个工厂
	int  MaxFpt, MinFpt;
	do
	{
		MaxFpt = rand() % Seq.size();
		MinFpt = rand() % Seq.size();
	} while (MaxFpt == MinFpt);


	int MaxTempSpan = GetFspan(Seq[MaxFpt]);
	int MinTempSpan = GetFspan(Seq[MinFpt]);
	vector<int>MaxTempSeq = Seq[MaxFpt];
	vector<int>MinTempSeq = Seq[MinFpt];

	int MaxFacSpan = 0;
	if (MinTempSpan < MaxTempSpan)
		MaxFacSpan = MaxTempSpan;
	else
		MaxFacSpan = MinTempSpan;

	vector<vector<int>>TempSeq = Seq;

	//在两个工厂中各选出一个工件
	int MaxJobpt, MinJobpt;
	int MaxTempJob, MinTempJob;

	MaxJobpt = rand() % Seq[MaxFpt].size();
	MinJobpt = rand() % Seq[MinFpt].size();

	MaxTempJob = Seq[MaxFpt][MaxJobpt];
	MinTempJob = Seq[MinFpt][MinJobpt];

	//交换选出的两个工件
	Seq[MaxFpt].erase(Seq[MaxFpt].begin() + MaxJobpt);
	Seq[MinFpt].erase(Seq[MinFpt].begin() + MinJobpt);

	Seq[MaxFpt].insert(Seq[MaxFpt].begin() + MaxJobpt, MinTempJob);
	Seq[MinFpt].insert(Seq[MinFpt].begin() + MinJobpt, MaxTempJob);

	//判断新的解是否被接受，这里的接受准则有一点疑问
	int NewMaxTempSpan = GetFspan(Seq[MaxFpt]);
	int NewMinTempSpan = GetFspan(Seq[MinFpt]);
	int NewMaxFacSpan = 0;
	if (NewMinTempSpan < NewMaxTempSpan)
		NewMaxFacSpan = NewMaxTempSpan;
	else
		NewMaxFacSpan = NewMinTempSpan;

	if (NewMaxFacSpan>MaxFacSpan)
	{
		Seq[MaxFpt] = MaxTempSeq;
		Seq[MinFpt] = MinTempSeq;
	}
}

//工厂内部交换
void Inter_Factory_Swap(vector<vector<int>>&Seq)
{
	//随机选取一个工厂

	int Fpt = rand() % Seq.size();
	int TempSpan = GetFspan(Seq[Fpt]);
	vector<int>TempSeq = Seq[Fpt];

	//在选取的工厂中随机选取两个工件
	int Jobpt1, Jobpt2;
	do
	{
		Jobpt1 = rand() % Seq[Fpt].size();
		Jobpt2 = rand() % Seq[Fpt].size();
	} while (Jobpt1 == Jobpt2);

	//交换两个工件的位置
	int TempJob = Seq[Fpt][Jobpt1];
	Seq[Fpt][Jobpt1] = Seq[Fpt][Jobpt2];
	Seq[Fpt][Jobpt2] = TempJob;

	//判断是否接受新的解
	int TempSpan1 = GetFspan(Seq[Fpt]);
	if (TempSpan1 > TempSpan)
		Seq[Fpt] = TempSeq;
}

//关键工厂外部插入
void Exter_CriticalFactory_Insert(vector<vector<int>>&Seq)
{
	
	//找到关键工厂
	int MaxFactorySpan = 0;
	int CriticalFactory = 0;
	for (int f = 0; f <Seq.size(); f++)
	{
		int TempSpan = GetFspan(Seq[f]);
		if (MaxFactorySpan < TempSpan)
		{
			MaxFactorySpan = TempSpan;
			CriticalFactory = f;
		}
	}

	//随机选取一个不同于关键工厂的工厂
	int Fpt;
	do
	{
		Fpt = rand() % Seq.size();
	} while (Fpt == CriticalFactory);

	vector<int>TempSeq = Seq[Fpt];

	//在关键工厂中随机选取一个工件
	int Jobpt = rand() % Seq[CriticalFactory].size();
	int Job = Seq[CriticalFactory][Jobpt];

	//将选择出的工件插入到另一个工厂的所有位置，并选择出一个最佳排列
	int TempSeqSpan = Job_To_SomeFactory_Bestposition(Job, Seq[Fpt]);
	if (TempSeqSpan < MaxFactorySpan)
		Seq[CriticalFactory].erase(Seq[CriticalFactory].begin() + Jobpt);
	else
		Seq[Fpt] = TempSeq;

}

//关键工厂外部交换  
void Exter_CriticalFactory_Swap(vector<vector<int>>&Seq)
{
	vector<vector<int>>TempSeq = Seq;

	//找到关键工厂
	int TempSpan = 0;
	int CriticalFactory = 0;
	for (int f = 0; f <Seq.size(); f++)
	{
		int TempSpan1 = GetFspan(Seq[f]);
		if (TempSpan < TempSpan1)
		{
			TempSpan = TempSpan1;
			CriticalFactory = f;
		}
	}

	//随机选取一个不同于关键工厂的工厂
	int Fpt;
	do
	{
		Fpt = rand() % Seq.size();
	} while (Fpt == CriticalFactory);

	//在关键工厂和被选取的工厂中各随机选取一个工件
	int CriticalJobpt, Jobpt;
	int CriticalJob, Job;

	CriticalJobpt = rand() % Seq[CriticalFactory].size();
	Jobpt = rand() % Seq[Fpt].size();
	CriticalJob = Seq[CriticalFactory][CriticalJobpt];
	Job = Seq[Fpt][Jobpt];

	//交换两个工厂的工件
	Seq[CriticalFactory].erase(Seq[CriticalFactory].begin() + CriticalJobpt);
	Seq[Fpt].erase(Seq[Fpt].begin() + Jobpt);

	Seq[CriticalFactory].insert(Seq[CriticalFactory].begin() + CriticalJobpt, Job);
	Seq[Fpt].insert(Seq[Fpt].begin() + Jobpt, CriticalJob);

	//判断是否接受新的解
	int NewCriticalTempSpan = GetFspan(Seq[CriticalFactory]);
	int NewTempSpan = GetFspan(Seq[Fpt]);
	int NewFacTempSpan;
	if (NewTempSpan < NewCriticalTempSpan)
		NewFacTempSpan = NewCriticalTempSpan;
	else
		NewFacTempSpan = NewTempSpan;

	if (NewFacTempSpan > TempSpan)
		Seq = TempSeq;
}

//关键工厂内部交换
void Inter_CriticalFactory_Swap(vector<vector<int>>&Seq)
{
	//找到关键工厂
	int TempSpan = 0;
	int CriticalFactory = 0;
	for (int f = 0; f <Seq.size(); f++)
	{
		int TempSpan1 = GetFspan(Seq[f]);
		if (TempSpan < TempSpan1)
		{
			TempSpan = TempSpan1;
			CriticalFactory = f;
		}
	}

	vector<int>TempSeq = Seq[CriticalFactory];

	//在关键工厂中随机选取两个不同的工件
	int Jobpt1, Jobpt2;
	do
	{
		Jobpt1 = rand() % Seq[CriticalFactory].size();
		Jobpt2 = rand() % Seq[CriticalFactory].size();
	} while (Jobpt1 == Jobpt2);

	//交换两个工件的位置
	int TempJob = Seq[CriticalFactory][Jobpt1];
	Seq[CriticalFactory][Jobpt1] = Seq[CriticalFactory][Jobpt2];
	Seq[CriticalFactory][Jobpt2] = TempJob;

	//判断是否接受新的解
	int TempSpan1 = GetFspan(Seq[CriticalFactory]);
	if (TempSpan1 < TempSpan)
	{
		TempSpan = TempSpan1;
		TempSeq = Seq[CriticalFactory];
	}
	Seq[CriticalFactory] = TempSeq;
}

//  RPI显示
void GetOverallRDI(vector<vector<double>> RDI, vector<double> &OverallRDI)
{
	OverallRDI.clear();
	OverallRDI.resize(RDI.size());
	for (int Alg = 0; Alg < RDI.size(); Alg++)
		OverallRDI[Alg] = accumulate(RDI[Alg].begin(), RDI[Alg].end(), 0.0) / RDI[Alg].size();
}

void GetRDI(vector<vector<int>> Value, vector<vector<double>> &RDI)
{
	RDI.clear();
	RDI.resize(Value.size());                          // Value这个二维数组，每一行就是表示的一种算法，列就是表示该算法的一个算例，所以在本问题里，就应该有15列
	for (int Alg = 0; Alg < Value.size(); Alg++)
		RDI[Alg].resize(Value[0].size());

	int minVal = INT_MAX;                     // minVal这个数组里面暂时装的就是每一个算法里面的最小值                 

	for (int Alg = 0; Alg < Value.size(); Alg++)       // Value.size()其实就是有多少种算法
	{
		for (int Ins = 0; Ins < Value[Alg].size(); Ins++)
		{
			if (Value[Alg][Ins] < minVal)
				minVal = Value[Alg][Ins];
		}
	}

	for (int Alg = 0; Alg < Value.size(); Alg++)
		RDI[Alg].resize(Value[0].size());

	for (int Alg = 0; Alg < Value.size(); Alg++)
	{
		for (int Ins = 0; Ins < Value[Alg].size(); Ins++)
		{
			RDI[Alg][Ins] = 100.00*  (Value[Alg][Ins] - minVal) / minVal;
		}
	}
}

//读出文件FName里面的所有的目标值//本论文中就是每个例子执行5遍的目标值//
void ReadCalFile(string FName, int Instances, int Reps, vector<vector<int>> &Results)
{
	Results.clear();
	Results.resize(Instances);
	for (int j = 0; j < Instances; j++)
		Results[j].resize(Reps);
	ifstream ifile;
	ifile.open(FName);
	for (int i = 0; i<Instances; i++)
	for (int j = 0; j < Reps; j++)
		ifile >> Results[i][j];
	ifile.close();
}

void ReadAverageRPI(string FName, int NumAlg,int NumInstance, vector<vector<double>>&Result)
{
	Result.clear();
	Result.resize(NumAlg);
	for (int i = 0; i < Result.size(); i++)
		Result[i].resize(NumInstance);

	ifstream ifile;
	ifile.open(FName);
	if (!ifile)
	{
		cout << "File is not existed!" << endl;
		exit(0);
	}
	else
	{
		for (int j = 0; j < NumInstance; j++)
		for (int i = 0; i < NumAlg; i++)
			ifile >> Result[i][j];
		ifile.close();
	}
}

//初始化
//随机生成一个解
//按makespan进行初始化
void InitialPopulation(vector<vector<int>>&Seq)
{
	vector<int>InitialJob;
	InitialJob.resize(gJobs);
	for (int i = 0; i < gJobs; i++)
		InitialJob[i] = i;

	srand(GetElapsedProcessTime());
	random_shuffle(InitialJob.begin(), InitialJob.end());

	for (int f = 0; f < gFactory; f++)
		Seq[f].clear();

	for (int f = 0; f < gFactory; f++)
		Seq[f].push_back(InitialJob[f]);

	for (int i = gFactory; i < gJobs; i++)
	{
		vector<int>TempSpan;
		TempSpan.resize(gFactory, 0);
		int TempBest = INT_MAX;
		int BestFpt = -1;

		//找到能耗最小的工厂			
		for (int k = 0; k < gFactory; k++)
		{
			TempSpan[k] = GetFspan(Seq[k]);
			if (TempSpan[k] < TempBest)
			{
				BestFpt = k;
				TempBest = TempSpan[k];
			}
		}
		Seq[BestFpt].push_back(InitialJob[i]);
	}
}

//随机进行初始化
int InitialPopulation_Ram(vector<vector<int>>&Seq)
{
	vector<int>InitialFactory_Job;
	InitialFactory_Job.clear();

	vector<int>InitialJob;
	InitialJob.resize(gJobs);
	for (int i = 0; i < gJobs; i++)
		InitialJob[i] = i;

	int TempFactory;
	for (int i = 0; i < gJobs; i++)
	{
		TempFactory = rand() % gFactory;
		InitialFactory_Job.push_back(TempFactory);
	}
	random_shuffle(InitialJob.begin(), InitialJob.end());

	for (int f = 0; f < gFactory; f++)
		Seq[f].clear();

	for (int i = 0; i < gJobs; i++)
		Seq[InitialFactory_Job[i]].push_back(InitialJob[i]);

	int Span = GetFspan(Seq);
	return Span;
}