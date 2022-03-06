#pragma once
#include "NEH.h"
int NEH2_en(vector<vector<int>>&Sol)
{
	Sol.clear();
	Sol.resize(gFactory);

	vector<int>FullPermutation;
	FullPermutation.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		FullPermutation[j] = j;
	NEHInit(FullPermutation); //做完此操作后工件序列按加工时间降序排列

	int FinalEC = 0;
	for (int i = 0; i < FullPermutation.size(); i++)
	{
		int Job = FullPermutation[i];
		int SelFac = 0;
		int BestPos = 0;
		FinalEC = Job_To_BestFactory_Bestposition(Job, Sol, SelFac, BestPos);
		if (Sol[SelFac].size()>1)
		{
			if (BestPos==0)
			{
				int RetryJob = Sol[SelFac][BestPos + 1];
				Sol[SelFac].erase(Sol[SelFac].begin() + BestPos + 1);
				Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
			}
			else if (BestPos == (Sol[SelFac].size() - 1))
			{
				int RetryJob = Sol[SelFac][BestPos - 1];
				Sol[SelFac].erase(Sol[SelFac].begin() + BestPos - 1);
				Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
			}
			else
			{
				int RandNum = rand() % 2;
				if (RandNum == 0)
				{
					int RetryJob = Sol[SelFac][BestPos + 1];
					Sol[SelFac].erase(Sol[SelFac].begin() + BestPos + 1);
					Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
				}
				else
				{
					int RetryJob = Sol[SelFac][BestPos - 1];
					Sol[SelFac].erase(Sol[SelFac].begin() + BestPos - 1);
					Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
				}
			}
		}
	}
	FinalEC = GetFspan(Sol);
	return FinalEC;
}

int NEH2_In(vector<vector<int>>& Sol)
{
	Sol.clear();
	Sol.resize(gFactory);

	vector<int>FullPermutation;
	FullPermutation.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		FullPermutation[j] = j;
	NEHInit02(FullPermutation); //做完此操作后工件序列按加工时间升序排列

	int FinalEC = 0;
	for (int i = 0; i < FullPermutation.size(); i++)
	{
		int Job = FullPermutation[i];
		int SelFac = 0;
		int BestPos = 0;
		FinalEC = Job_To_BestFactory_Bestposition(Job, Sol, SelFac, BestPos);
		if (Sol[SelFac].size() > 1)
		{
			if (BestPos == 0)
			{
				int RetryJob = Sol[SelFac][BestPos + 1];
				Sol[SelFac].erase(Sol[SelFac].begin() + BestPos + 1);
				Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
			}
			else if (BestPos == (Sol[SelFac].size() - 1))
			{
				int RetryJob = Sol[SelFac][BestPos - 1];
				Sol[SelFac].erase(Sol[SelFac].begin() + BestPos - 1);
				Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
			}
			else
			{
				int RandNum = rand() % 2;
				if (RandNum == 0)
				{
					int RetryJob = Sol[SelFac][BestPos + 1];
					Sol[SelFac].erase(Sol[SelFac].begin() + BestPos + 1);
					Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
				}
				else
				{
					int RetryJob = Sol[SelFac][BestPos - 1];
					Sol[SelFac].erase(Sol[SelFac].begin() + BestPos - 1);
					Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
				}
			}
		}
	}
	FinalEC = GetFspan(Sol);
	return FinalEC;
}

int NEH_Normal(vector<vector<int>>& Sol)
{
	Sol.clear();
	Sol.resize(gFactory);

	vector<int>FullPermutation;
	FullPermutation.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		FullPermutation[j] = j;
	NEHInit(FullPermutation); //做完此操作后工件序列按加工时间降序排列

	int FinalEC = 0;
	for (int i = 0; i < FullPermutation.size(); i++)
	{
		int Job = FullPermutation[i];
		int SelFac = 0;
		int BestPos = 0;
		FinalEC = Job_To_BestFactory_Bestposition(Job, Sol, SelFac, BestPos);
		if (Sol[SelFac].size() > 1)
		{
			if (BestPos == 0)
			{
				int RetryJob = Sol[SelFac][BestPos + 1];
				Sol[SelFac].erase(Sol[SelFac].begin() + BestPos + 1);
				Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
			}
			else if (BestPos == (Sol[SelFac].size() - 1))
			{
				int RetryJob = Sol[SelFac][BestPos - 1];
				Sol[SelFac].erase(Sol[SelFac].begin() + BestPos - 1);
				Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
			}
			else
			{
				int RandNum = rand() % 2;
				if (RandNum == 0)
				{
					int RetryJob = Sol[SelFac][BestPos + 1];
					Sol[SelFac].erase(Sol[SelFac].begin() + BestPos + 1);
					Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
				}
				else
				{
					int RetryJob = Sol[SelFac][BestPos - 1];
					Sol[SelFac].erase(Sol[SelFac].begin() + BestPos - 1);
					Job_To_SomeFactory_Bestposition(RetryJob, Sol[SelFac]);
				}
			}
		}
	}
	FinalEC = GetFspan(Sol);
	return FinalEC;
}

void Destruction(vector<vector<int>>&Seq,vector<int>&DesJobSeq, int PLen)
{
	DesJobSeq.clear();

	vector<int>FactorySpan(Seq.size(), 0);
	for (int f = 0; f < Seq.size(); f++)
		FactorySpan[f] = GetFspan(Seq[f]);

	int CriticalFacPt = -1;
	int TempFacSpan = INT_MIN;
	for (int i = 0; i < FactorySpan.size(); i++)
	{
		if (FactorySpan[i]>TempFacSpan)
		{
			TempFacSpan = FactorySpan[i];
			CriticalFacPt = i;
		}
	}

	for (int i = 0; i < PLen / 2; i++)
	{
		int Pt = rand() % Seq[CriticalFacPt].size();
		DesJobSeq.push_back(Seq[CriticalFacPt][Pt]);
		Seq[CriticalFacPt].erase(Seq[CriticalFacPt].begin() + Pt);
	}

	while (DesJobSeq.size()<PLen)
	{
		int Fpt = rand() % Seq.size();
		if ((Seq[Fpt].size() > 1) && (Fpt != CriticalFacPt))
		{
			int pt = rand() % Seq[Fpt].size();
			DesJobSeq.push_back(Seq[Fpt][pt]);
			Seq[Fpt].erase(Seq[Fpt].begin() + pt);
		}
	}
}

int Construction(vector<vector<int>>&Seq, vector<int>DesJobSeq)
{
	for (int i = 0; i < DesJobSeq.size(); i++)
	{
		int Job = DesJobSeq[i];
		int SelFac = 0;
		int BestPos = 0;
		Job_To_BestFactory_Bestposition(Job, Seq, SelFac, BestPos);

		if (Seq[SelFac].size()>1)
		{
			if (BestPos == 0)
			{
				int RetryJob = Seq[SelFac][BestPos + 1];
				Seq[SelFac].erase(Seq[SelFac].begin() + BestPos + 1);
				Job_To_SomeFactory_Bestposition(RetryJob, Seq[SelFac]);
			}
			else if (BestPos == (Seq[SelFac].size() - 1))
			{
				int RetryJob = Seq[SelFac][BestPos - 1];
				Seq[SelFac].erase(Seq[SelFac].begin() + BestPos - 1);
				Job_To_SomeFactory_Bestposition(RetryJob, Seq[SelFac]);
			}
			else
			{
				int RandNum = rand() % 2;
				if (RandNum == 0)
				{
					int RetryJob = Seq[SelFac][BestPos + 1];
					Seq[SelFac].erase(Seq[SelFac].begin() + BestPos + 1);
					Job_To_SomeFactory_Bestposition(RetryJob, Seq[SelFac]);
				}
				else
				{
					int RetryJob = Seq[SelFac][BestPos - 1];
					Seq[SelFac].erase(Seq[SelFac].begin() + BestPos - 1);
					Job_To_SomeFactory_Bestposition(RetryJob, Seq[SelFac]);
				}
			}
		}
	}
	int FinalEC = GetFspan(Seq);
	return FinalEC;
}

int LS_3(vector<vector<int>>&Seq)
{
	vector<int>FactorySpan(Seq.size(), 0);
	for (int f = 0; f < Seq.size(); f++)
		FactorySpan[f] = GetFspan(Seq[f]);

	int CriticalFacPt = -1;
	int TempFacSpan = INT_MIN;
	for (int i = 0; i < FactorySpan.size(); i++)
	{
		if (FactorySpan[i]>TempFacSpan)
		{
			TempFacSpan = FactorySpan[i];
			CriticalFacPt = i;
		}
	}

	int Counter = 0;
	vector<int>TempCriticalFacSeq = Seq[CriticalFacPt];
	while (Counter < Seq[CriticalFacPt].size())
	{
		int total = 0;
		for (int i = 0; i < Seq.size(); ++i)
		{
			total += FactorySpan[i];
		}
		int MakeSpan = total;/* *max_element(FactorySpan.begin(), FactorySpan.end());*/
		int RandNum = rand() % TempCriticalFacSeq.size();
		int Job = TempCriticalFacSeq[RandNum];
		TempCriticalFacSeq.erase(TempCriticalFacSeq.begin() + RandNum);
		vector<vector<int>>TempSeq = Seq;


		int SelFac = 0;
		int BestPos = 0;
		int Pos = -1;

		for (int i = 0; i < Seq[CriticalFacPt].size(); i++)
		{
			if (Seq[CriticalFacPt][i] == Job)
			{
				Pos = i;
				Seq[CriticalFacPt].erase(Seq[CriticalFacPt].begin() + i);
				break;
			}
		}
		int TempMakeSpan = Job_To_BestFactory_Bestposition(Job, Seq, SelFac, BestPos);
		if (TempMakeSpan >= MakeSpan)
		{
			Seq = TempSeq;
			Counter++;
		}			
		else
		{
			FactorySpan[CriticalFacPt] = GetFspan(Seq[CriticalFacPt]);
			FactorySpan[SelFac] = GetFspan(Seq[SelFac]);
			TempFacSpan = INT_MIN;
			for (int i = 0; i < FactorySpan.size(); i++)
			{
				if (FactorySpan[i]>TempFacSpan)
				{
					TempFacSpan = FactorySpan[i];
					CriticalFacPt = i;
				}
			}
			TempCriticalFacSeq = Seq[CriticalFacPt];
			Counter = 0;
		}			
	}
	int FinalMakespan = GetFspan(Seq);
	return FinalMakespan;
}

int IG_Compared(long TimeLimit, int PLen, double Tem)
{
	long InitTime = GetElapsedProcessTime();
	vector<vector<int>>Seq;
	int Span = NEH2_en(Seq);
	Span = LS_3(Seq);

	vector<vector<int>>BestSeqSofar = Seq;
	int BestValueSofar = Span;
	double Temperature = GetTemperature(Tem);

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		vector<vector<int>>TempSeq = Seq;
		int TempSpan = Span;

		vector<int>DesJobSeq;
		Destruction(TempSeq, DesJobSeq, PLen);
		Construction(TempSeq, DesJobSeq);
		TempSpan = LS_3(TempSeq);

		if (TempSpan < Span)
		{
			Span = TempSpan;
			Seq = TempSeq;

			if (Span < BestValueSofar)
			{
				BestValueSofar = Span;
				BestSeqSofar = Seq;
			}
		}
		else
		{
			double  t = exp((Span - TempSpan) / Temperature);            //改过的模拟退火
			if (rand() < int(RAND_MAX*t))
			{
				Span = TempSpan;
				Seq = TempSeq;
			}
		}
	}
	CheckChrom(BestSeqSofar, BestValueSofar);
	//GetFspan01(BestSeqSofar);
	return BestValueSofar;
}

void IG_Compared_Run(int CPU, int Ins)
{
	int Plen = 1;
	double Tem = 0.0;

	const int Reps = 5;
	vector<int> TValueArray(Reps);

	Read(Ins);
	long TimeLimit = CPU * gMachine*gJobs;
	for (int rep = 0; rep < Reps; rep++)
	{
		long start = ::GetElapsedProcessTime();
		srand(Ins * 100 + rep);
		int TValue = IG_Compared(TimeLimit, Plen, Tem);

		cout << "\t" << Ins << "\t" << gFactory << "\t" << gJobs << "\t" << gMachine << "\t" << TValue << "\t" << (::GetElapsedProcessTime() - start) / 1000.0 << endl;
		TValueArray[rep] = TValue;
	}

	ostringstream str;
	str << "IGCompared_" << CPU << "_" << Ins << ".txt";
	ofstream ofile;
	ofile.open(str.str());

	for (int rep = 0; rep < Reps; rep++)
	{
		ofile << TValueArray[rep] << "\t";
	}
	ofile.close();
}

int IG_Compared_Curve(long TimeLimit, int PLen, double Tem, int LocalValue, long LocalTime, int No)
{
	long InitTime = GetElapsedProcessTime();
	vector<vector<int>>Seq;
	int Span = NEH2_en(Seq);
	Span = LS_3(Seq);

	vector<vector<int>>BestSeqSofar = Seq;
	int BestValueSofar = Span;
	double Temperature = GetTemperature(Tem);

	//建立一个txt文件
	ostringstream str;
	str << "Test_IGA_Curve_Ins=" << No << ".txt";                //
	ofstream ofile;
	ofile.open(str.str());

	//输出初始解以及初始时间
	LocalValue = BestValueSofar;                             //
	LocalTime = GetElapsedProcessTime() - InitTime;         //
	ofile << LocalTime << "\t" << LocalValue << "\t" << endl;

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		vector<vector<int>>TempSeq = Seq;
		int TempSpan = Span;

		vector<int>DesJobSeq;
		Destruction(TempSeq, DesJobSeq, PLen);
		Construction(TempSeq, DesJobSeq);
		TempSpan = LS_3(TempSeq);

		if (TempSpan < Span)
		{
			Span = TempSpan;
			Seq = TempSeq;

			if (Span < BestValueSofar)
			{
				BestValueSofar = Span;
				BestSeqSofar = Seq;
			}
		}
		else
		{
			double  t = exp((Span - TempSpan) / Temperature);            //改过的模拟退火
			if (rand() < int(RAND_MAX*t))
			{
				Span = TempSpan;
				Seq = TempSeq;
			}
		}

		LocalValue = BestValueSofar;                             //
		LocalTime = GetElapsedProcessTime() - InitTime;         //
		ofile << LocalTime << "\t" << LocalValue << "\t" << endl;
	}
	ofile.close();

	CheckChrom(BestSeqSofar, BestValueSofar);
	return BestValueSofar;
}