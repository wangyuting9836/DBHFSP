#pragma once
int Mutation(vector<vector<int>>&Seq)
{
	int Fac1 = -1;
	int Fac2 = -1;
	do
	{
		Fac1 = rand() % Seq.size();
		Fac2 = rand() % Seq.size();
	} while (Fac1 == Fac2);

	int JobPt1 = rand() % Seq[Fac1].size();
	int JobPt2 = rand() % Seq[Fac2].size();

	int TempJob = Seq[Fac2][JobPt2];
	Seq[Fac2][JobPt2] = Seq[Fac1][JobPt1];
	Seq[Fac1][JobPt1] = TempJob;

	int FinalMakeSpan = GetFspan(Seq);
	return FinalMakeSpan;
}

int RLS(vector<vector<int>>RefSeq, vector<vector<int>>&Seq,int &k)
{
	vector<int>ReferSeq;
	ReferSeq.clear();
	for (int i = 0; i < RefSeq.size(); i++)
	{
		for (int j = 0; j < RefSeq[i].size(); j++)
			ReferSeq.push_back(RefSeq[i][j]);
	}
    
	int Span = GetFspan(Seq);
	int Cnt = 0;
	while (Cnt < ReferSeq.size())
	{
		vector<vector<int>>TempSeq = Seq;
		int TempSpan = Span;

		int Job = ReferSeq[k];
		for (int f = 0; f < TempSeq.size(); f++)
		{
			for (int j = 0; j < TempSeq[f].size(); j++)
			{
				if (TempSeq[f][j] == Job)
					TempSeq[f].erase(TempSeq[f].begin() + j);
			}
		}

		TempSpan = Job_To_BestFactory_Bestposition(Job, TempSeq);
		if (TempSpan < Span)
		{
			Span = TempSpan;
			Seq = TempSeq;
			Cnt = 0;
		}
		else
			Cnt++;
		k++;
		if (k >= ReferSeq.size())
			k = 0;
	}
	return Span;
}

void PopulationUpdate(vector<vector<int>>Individual,int SpanofIndividual, int Flag,int NumIndi,vector<vector<vector<int>>>&Population, vector<int>&PopMakeSpan)
{
	if (Flag == 1)
	{
		Population.clear();
		PopMakeSpan.clear();
	}

	Population.push_back(Individual);
	PopMakeSpan.push_back(SpanofIndividual);

	while (Population.size() > NumIndi)
	{
		int TempPopMakeSpan = INT_MIN;
		int WorstIndi = -1;
		for (int i = 0; i < PopMakeSpan.size(); i++)
		{
			if (PopMakeSpan[i]>TempPopMakeSpan)
			{
				TempPopMakeSpan = PopMakeSpan[i];
				WorstIndi = i;
			}
		}
		Population.erase(Population.begin() + WorstIndi);
		PopMakeSpan.erase(PopMakeSpan.begin() + WorstIndi);
	}	
}

int EA(long TimeLimit, int NumIndi)
{
	long InitTime = GetElapsedProcessTime();

	int k = 0;
	int Flag = 0;

	vector<vector<vector<int>>>Population;
	Population.resize(NumIndi);

	vector<int>PopMakeSpan;
	PopMakeSpan.resize(NumIndi);

	PopMakeSpan[0] = NEH_Speedup(Population[0]);

	for (int Indi = 1; Indi < Population.size(); Indi++)
		PopMakeSpan[Indi] = NEH_RAN(Population[Indi]);

	int BestIndividual = -1;
	int TempPopMakeSpan = INT_MAX;
	for (int Indi = 0; Indi < Population.size(); Indi++)
	{
		if (PopMakeSpan[Indi] < TempPopMakeSpan)
		{
			BestIndividual = Indi;
			TempPopMakeSpan = PopMakeSpan[Indi];
		}
	}

	vector<vector<int>>TempBestIndividual = Population[BestIndividual];
	int TempBestPopMakeSpan = RLS(TempBestIndividual, TempBestIndividual, k);

	if (TempBestPopMakeSpan < PopMakeSpan[BestIndividual])
	{
		PopMakeSpan[BestIndividual] = TempBestPopMakeSpan;
		Population[BestIndividual] = TempBestIndividual;
		Flag = 1;
	}

	PopulationUpdate(TempBestIndividual, TempBestPopMakeSpan, Flag, NumIndi, Population, PopMakeSpan);

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		Flag = 0;

		BestIndividual = -1;
		TempPopMakeSpan = INT_MAX;
		for (int Indi = 0; Indi < Population.size(); Indi++)
		{
			if (PopMakeSpan[Indi] < TempPopMakeSpan)
			{
				BestIndividual = Indi;
				TempPopMakeSpan = PopMakeSpan[Indi];
			}
		}

		int RandIndiPt = rand() % Population.size();
		vector<vector<int>>TempRandIndi = Population[RandIndiPt];
		int TempMakeSpan = Mutation(TempRandIndi);
		if (TempMakeSpan < PopMakeSpan[BestIndividual])
		{
			PopMakeSpan[BestIndividual] = TempMakeSpan;
			Population[BestIndividual] = TempRandIndi;
		}
		TempMakeSpan = RLS(Population[BestIndividual], TempRandIndi, k);
		if (TempMakeSpan < PopMakeSpan[BestIndividual])
		{
			PopMakeSpan[BestIndividual] = TempMakeSpan;
			Population[BestIndividual] = TempRandIndi;
			Flag = 1;
		}

		PopulationUpdate(TempRandIndi, TempMakeSpan, Flag, NumIndi, Population, PopMakeSpan);
	}
	for (int Indi = 0; Indi < Population.size(); Indi++)
		CheckChrom(Population[Indi], PopMakeSpan[Indi]);

	return *min_element(PopMakeSpan.begin(), PopMakeSpan.end());
}

void EA_Run(int CPU, int Ins)
{
	int NumIndi = 2;
	const int Reps = 5;
	vector<int> TValueArray(Reps);

	Read(Ins);
	long TimeLimit = CPU * gMachine*gJobs;
	for (int rep = 0; rep < Reps; rep++)
	{
		long start = ::GetElapsedProcessTime();
		srand(Ins * 100 + rep);
		int TValue = EA(TimeLimit, NumIndi);

		cout << "\t" << Ins << "\t" << gFactory << "\t" << gJobs << "\t" << gMachine << "\t" << TValue << "\t" << (::GetElapsedProcessTime() - start) / 1000.0 << endl;
		TValueArray[rep] = TValue;
	}

	ostringstream str;
	str << "EA_" << CPU << "_" << Ins << ".txt";
	ofstream ofile;
	ofile.open(str.str());

	for (int rep = 0; rep < Reps; rep++)
	{
		ofile << TValueArray[rep] << "\t";
	}
	ofile.close();
}

int EA_Curve(long TimeLimit, int NumIndi, int LocalValue, long LocalTime, int No)
{
	long InitTime = GetElapsedProcessTime();

	int k = 0;
	int Flag = 0;

	vector<vector<vector<int>>>Population;
	Population.resize(NumIndi);

	vector<int>PopMakeSpan;
	PopMakeSpan.resize(NumIndi);

	PopMakeSpan[0] = NEH_Speedup(Population[0]);

	for (int Indi = 1; Indi < Population.size(); Indi++)
		PopMakeSpan[Indi] = NEH_RAN(Population[Indi]);

	int BestIndividual = -1;
	int TempPopMakeSpan = INT_MAX;
	for (int Indi = 0; Indi < Population.size(); Indi++)
	{
		if (PopMakeSpan[Indi] < TempPopMakeSpan)
		{
			BestIndividual = Indi;
			TempPopMakeSpan = PopMakeSpan[Indi];
		}
	}

	vector<vector<int>>TempBestIndividual = Population[BestIndividual];
	int TempBestPopMakeSpan = RLS(TempBestIndividual, TempBestIndividual, k);

	if (TempBestPopMakeSpan < PopMakeSpan[BestIndividual])
	{
		PopMakeSpan[BestIndividual] = TempBestPopMakeSpan;
		Population[BestIndividual] = TempBestIndividual;
		Flag = 1;
	}

	PopulationUpdate(TempBestIndividual, TempBestPopMakeSpan, Flag, NumIndi, Population, PopMakeSpan);

	//建立一个txt文件
	ostringstream str;
	str << "EA_Curve" << No << ".txt";                //
	ofstream ofile;
	ofile.open(str.str());

	//输出初始解以及初始时间
	LocalValue = *min_element(PopMakeSpan.begin(), PopMakeSpan.end());                             //
	LocalTime = GetElapsedProcessTime() - InitTime;         //
	ofile << LocalTime << "\t" << LocalValue << "\t" << endl;

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		Flag = 0;

		BestIndividual = -1;
		TempPopMakeSpan = INT_MAX;
		for (int Indi = 0; Indi < Population.size(); Indi++)
		{
			if (PopMakeSpan[Indi] < TempPopMakeSpan)
			{
				BestIndividual = Indi;
				TempPopMakeSpan = PopMakeSpan[Indi];
			}
		}

		int RandIndiPt = rand() % Population.size();
		vector<vector<int>>TempRandIndi = Population[RandIndiPt];
		int TempMakeSpan = Mutation(TempRandIndi);
		if (TempMakeSpan < PopMakeSpan[BestIndividual])
		{
			PopMakeSpan[BestIndividual] = TempMakeSpan;
			Population[BestIndividual] = TempRandIndi;
		}
		TempMakeSpan = RLS(Population[BestIndividual], TempRandIndi, k);
		if (TempMakeSpan < PopMakeSpan[BestIndividual])
		{
			PopMakeSpan[BestIndividual] = TempMakeSpan;
			Population[BestIndividual] = TempRandIndi;
			Flag = 1;
		}

		PopulationUpdate(TempRandIndi, TempMakeSpan, Flag, NumIndi, Population, PopMakeSpan);

		LocalValue = *min_element(PopMakeSpan.begin(), PopMakeSpan.end());                          //
		LocalTime = GetElapsedProcessTime() - InitTime;         //
		ofile << LocalTime << "\t" << LocalValue << "\t" << endl;
	}
	for (int Indi = 0; Indi < Population.size(); Indi++)
		CheckChrom(Population[Indi], PopMakeSpan[Indi]);

	return *min_element(PopMakeSpan.begin(), PopMakeSpan.end());
}