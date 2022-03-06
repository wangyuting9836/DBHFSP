#pragma once
//Generate a job sequence in ascending order
void GetAscendingOrder(vector<int>&JobAscendingOrder)
{
	JobAscendingOrder.clear();
	JobAscendingOrder.resize(gJobs);
	Pair* ch = new Pair[gJobs];
	for (int j = 0; j < gJobs; j++)
	{
		ch[j].dim = j;
		ch[j].value = 0;
		for (int m = 0; m < InStage; m++)
			ch[j].value += pTime[j][m];
	}

	sort(ch, ch + gJobs, PairLess());
	for (int j = 0; j < gJobs; j++)
		JobAscendingOrder[j] = ch[j].dim;
	delete[]ch;
}

//Generate a job sequence in non-increasing order
void GetNonIncreasingOrder(vector<int>& NonIncreasingOrder)
{
	NonIncreasingOrder.clear();
	NonIncreasingOrder.resize(gJobs);
	Pair* ch = new Pair[gJobs];
	for (int j = 0; j < gJobs; j++)
	{
		ch[j].dim = j;
		ch[j].value = 0;
		for (int m = 0; m < InStage; m++)
			ch[j].value += pTime[j][m];
	}

	sort(ch, ch + gJobs, PairGreater());
	for (int j = 0; j < gJobs; j++)
		NonIncreasingOrder[j] = ch[j].dim;
	delete[]ch;
}

int DSPT(vector<vector<int>>&Seq)
{
	Seq.resize(gFactory);
	for (int i = 0; i < Seq.size(); i++)
		Seq[i].clear();

	vector<int>JobAscendingOrder;
	GetAscendingOrder(JobAscendingOrder);

	int Counter = 0;
	for (int f = 0; f < Seq.size(); f++)
	{
		Seq[f].push_back(JobAscendingOrder[f]);
		Counter = f;
	}

	while (Counter < gJobs-1)
	{
		Counter = Counter + 1;
		vector<vector<int>>TempSeq = Seq;
		int FacPt = -1;
		int LocalSpan = INT_MAX;
		for (int f = 0; f < TempSeq.size(); f++)
		{
			TempSeq[f].push_back(JobAscendingOrder[Counter]);
			int TempSpan = GetFspan(TempSeq);
			if (TempSpan < LocalSpan)
			{
				LocalSpan = TempSpan;
				FacPt = f;
			}
			TempSeq = Seq;
		}
		Seq[FacPt].push_back(JobAscendingOrder[Counter]);
	}
	int Span = GetFspan(Seq);
	return Span;
}

int DNEH(vector<vector<int>>& Seq)
{
	Seq.resize(gFactory);
	for (int i = 0; i < Seq.size(); i++)
		Seq[i].clear();

	vector<int>NonIncreasingOrder;
	GetNonIncreasingOrder(NonIncreasingOrder);

	int Counter = 0;
	for (int f = 0; f < Seq.size(); f++)
	{
		Seq[f].push_back(NonIncreasingOrder[f]);
		Counter = f;
	}

	int Span = GetFspan(Seq);
	while (Counter < gJobs - 1)
	{
		Counter = Counter + 1;
		Span = Job_To_BestFactory_Bestposition(NonIncreasingOrder[Counter], Seq);

	}
	return Span;
}

int GetARandomIndividual(vector<vector<int>>& Seq)
{
	Seq.resize(gFactory);
	for (int f = 0; f < Seq.size(); f++)
		Seq[f].clear();

	vector<int>JobSeq;
	JobSeq.clear();
	for (int j = 0; j < gJobs; j++)
		JobSeq.push_back(j);

	random_shuffle(JobSeq.begin(), JobSeq.end());

	vector<int>CutPoint;
	CutPoint.resize(Seq.size() - 1, 0);

	int Counter = 0;
	while (Counter< CutPoint.size())
	{
		bool Flag = false;
		int Point = rand() % (JobSeq.size() - 2) + 1;
		for (int i = 0; i < CutPoint.size(); i++)
		{
			if (Point == CutPoint[i])
			{
				Flag = true;
				break;
			}
		}
		if (Flag == false)
		{
			CutPoint[Counter] = Point;
			Counter++;
		}
	}
	sort(CutPoint.begin(), CutPoint.end());
	for (int f = 0; f < Seq.size(); f++)
	{
		if (f == 0)
		{
			for (int i = 0; i < CutPoint[0]; i++)
				Seq[f].push_back(JobSeq[i]);
		}
		else if (f == Seq.size() - 1)
		{
			for (int i = CutPoint[CutPoint.size() - 1]; i < JobSeq.size(); i++)
				Seq[f].push_back(JobSeq[i]);
		}
		else
		{
			for (int i = CutPoint[f - 1]; i < CutPoint[f]; i++)
				Seq[f].push_back(JobSeq[i]);
		}
	}

	int Span = GetFspan(Seq);
	return Span;
}

int DDE_Mutation_Operator(float Mcoefficien,vector<vector<int>>&Seq) //Mcoefficien=mutation coefficient.
{
	vector<int>YA;
	YA.resize(gJobs);
	for (int i = 0; i < gJobs; i++)
		YA[i] = i;
	vector<int>YB = YA;

	random_shuffle(YA.begin(), YA.end());
	random_shuffle(YB.begin(), YB.end());

	vector<int>ErrorBetweenYAandYB;  //deta=YA-YB;
	ErrorBetweenYAandYB.resize(YA.size());
	for (int i = 0; i < ErrorBetweenYAandYB.size(); i++)
	{
		if (YA[i] == YB[i])
			ErrorBetweenYAandYB[i] = 0;
		else
			ErrorBetweenYAandYB[i] = YA[i];
	}

	vector<int>IntermediateVaraiblesObtainedbyMcoefficien;    //Fai=Mcoefficien*deta;
	IntermediateVaraiblesObtainedbyMcoefficien.resize(YA.size());
	for (int i = 0; i < IntermediateVaraiblesObtainedbyMcoefficien.size(); i++)
	{
		default_random_engine e(rand());
		uniform_real_distribution<float>u(0, 1.0);
		float randnum = u(e);
		if (randnum < Mcoefficien)
			IntermediateVaraiblesObtainedbyMcoefficien[i] = ErrorBetweenYAandYB[i];
		else
			IntermediateVaraiblesObtainedbyMcoefficien[i] = 0;
	}

	int Counter = 0;
	while (Counter < IntermediateVaraiblesObtainedbyMcoefficien.size())
	{
		vector<int>TSeq;
		TSeq.clear();
		for (int f = 0; f < Seq.size(); f++)
		{
			for (int i = 0; i < Seq[f].size(); i++)
				TSeq.push_back(Seq[f][i]);
		}

		if (IntermediateVaraiblesObtainedbyMcoefficien[Counter] != 0)
		{
			default_random_engine e(rand());
			uniform_real_distribution<float>u(0, 1.0);
			float randnum = u(e);

			if (randnum < 0.5)  //Swapping
			{
				int TempJob1 = TSeq[Counter];
				int TempJob2 = IntermediateVaraiblesObtainedbyMcoefficien[Counter];

				int Fac1 = -1;
				int Pos1 = -1;
				int Fac2 = -1;
				int Pos2 = -1;

				bool Flag1 = false;
				bool Flag2 = false;

				for (int f = 0; f < Seq.size(); f++)
				{
					for (int i = 0; i < Seq[f].size(); i++)
					{
						if (Seq[f][i] == TempJob1)
						{
							Fac1 = f;
							Pos1 = i;
							Flag1 = true;
						}
						if (Seq[f][i] == TempJob2)
						{
							Fac2 = f;
							Pos2 = i;
							Flag2 = true;
						}
					}
					if (Flag1 == true && Flag2 == true)
						break;
				}
				Seq[Fac1][Pos1] = TempJob2;
				Seq[Fac2][Pos2] = TempJob1;
			}
			else    //Inserting
			{
				int TempJob1 = TSeq[Counter];
				int TempJob2 = IntermediateVaraiblesObtainedbyMcoefficien[Counter];

				if (TempJob1 != TempJob2)
				{
					for (int f = 0; f < Seq.size(); f++)
					{
						bool Flag = false;
						for (int i = 0; i < Seq[f].size(); i++)
						{
							if (Seq[f][i] == TempJob1)
							{
								Seq[f].erase(Seq[f].begin() + i);
								Flag = true;
								break;
							}
						}
						if (Flag == true)
							break;
					}

					int Fac = -1;
					int Pos = -1;

					for (int f = 0; f < Seq.size(); f++)
					{
						bool Flag = false;
						for (int i = 0; i < Seq[f].size(); i++)
						{
							if (Seq[f][i] == TempJob2)
							{
								Fac = f;
								Pos = i;
								Flag = true;
								break;
							}
						}
						if (Flag == true)
							break;
					}
					Seq[Fac].insert(Seq[Fac].begin() + Pos + 1, TempJob1);
				}
			}
			Counter++;
		}
		else
			Counter++;
	}
	int Span = GetFspan(Seq);
	return Span;
}

void ChangeOrder(vector<int>JobSet, vector<int>& TSeq, vector<int>& TSeqfromMutation)
{
	vector<int>JobinSeq;
	JobinSeq.clear();
	vector<int>JobinSeqfromMutation = JobinSeq;

	for (int i = 0; i < JobSet.size(); i++)
		JobinSeq.push_back(TSeq[JobSet[i]]);

	for (int i = 0; i < TSeqfromMutation.size(); i++)
	{
		for (int j = 0; j < JobinSeq.size(); j++)
		{
			if (TSeqfromMutation[i] == JobinSeq[j])
			{
				JobinSeqfromMutation.push_back(TSeqfromMutation[i]);
				break;
			}
		}
	}

	for (int i = 0; i < JobSet.size(); i++)
		TSeq[JobSet[i]] = JobinSeqfromMutation[i];
}

int DDE_Crossover_Operator(float Crossovercoefficient,vector<vector<int>>&Seq,vector<vector<int>>&SeqfromMutation)
{   
	vector<int>TSeq;
	TSeq.clear();
	vector<int>TSeqfromMutation = TSeq;

	for (int f = 0; f < Seq.size(); f++)
	{
		for (int i = 0; i < Seq[f].size(); i++)
			TSeq.push_back(Seq[f][i]);
	}

	for (int f = 0; f < SeqfromMutation.size(); f++)
	{
		for (int i = 0; i < SeqfromMutation[f].size(); i++)
			TSeqfromMutation.push_back(SeqfromMutation[f][i]);
	}

	vector<int>JobSet;
	JobSet.clear();

	for (int j = 0; j < gJobs; j++)
	{
		default_random_engine e(rand());
		uniform_real_distribution<float>u(0, 1.0);
		float randnum = u(e);
		if (randnum >= Crossovercoefficient)
			JobSet.push_back(j);
	}

	vector<int>TempTSeq = TSeq;
	vector<int>TempTSeqfromMutation = TSeqfromMutation;
	ChangeOrder(JobSet, TempTSeq, TempTSeqfromMutation);
	vector<vector<int>>TempSeq1 = Seq;

	int Counter = 0;
	for (int f = 0; f < TempSeq1.size(); f++)
	{
		for (int i = 0; i < TempSeq1[f].size(); i++)
		{
			TempSeq1[f][i] = TempTSeq[Counter];
			Counter++;
		}			
	}

	TempTSeq = TSeq;
	TempTSeqfromMutation = TSeqfromMutation;
	ChangeOrder(JobSet, TempTSeqfromMutation, TempTSeq);
	vector<vector<int>>TempSeq2 = Seq;

	Counter = 0;
	for (int f = 0; f < TempSeq2.size(); f++)
	{
		for (int i = 0; i < TempSeq2[f].size(); i++)
		{
			TempSeq2[f][i] = TempTSeqfromMutation[Counter];
			Counter++;
		}
	}

	int TempSpan1 = GetFspan(TempSeq1);
	int TempSpan2 = GetFspan(TempSeq2);
	int Span = TempSpan1;
	if (TempSpan1 <= TempSpan2)
	{
		Seq = TempSeq1;
		Span = TempSpan1;		
	}
	else
	{
		Seq = TempSeq2;
		Span = TempSpan2;
	}
	return 	Span;
}

int DDE_Local_Search(vector<vector<int>>& Seq)  //Iter=γ
{
	int Counter = 0;
	vector<int>SpanSeq;
	SpanSeq.resize(Seq.size());
	for (int f = 0; f < Seq.size(); f++)
		SpanSeq[f] = GetFspan(Seq[f]);

	int Span = GetFspan(Seq);
	while (Counter < 3)
	{
		int CriticalFac = -1;
		int CriticalSpan = INT_MIN;
		for (int f = 0; f < SpanSeq.size(); f++)
		{
			if (SpanSeq[f] > CriticalSpan)
			{
				CriticalSpan = SpanSeq[f];
				CriticalFac = f;
			}
		}

		int RandFac = -1;
		do
		{
			RandFac = rand() % Seq.size();
		} while (CriticalFac == RandFac);
		Counter++;

		vector<vector<int>>TempSeq = Seq;
		vector<int>TempSpanSeq = SpanSeq;

		if (Counter == 1)   //ICFI_Move
		{
			int JobAPt = rand() % TempSeq[CriticalFac].size();
			int JobA = TempSeq[CriticalFac][JobAPt];

			TempSeq[CriticalFac].erase(TempSeq[CriticalFac].begin() + JobAPt);
			TempSpanSeq[CriticalFac] = Job_To_SomeFactory_Bestposition(JobA, TempSeq[CriticalFac]);
		}
		else if (Counter == 2)   //ECFI_Move
		{
			int JobAPt = rand() % TempSeq[CriticalFac].size();
			int JobA = TempSeq[CriticalFac][JobAPt];
			TempSeq[CriticalFac].erase(TempSeq[CriticalFac].begin() + JobAPt);
			TempSpanSeq[CriticalFac] = GetFspan(TempSeq[CriticalFac]);
			TempSpanSeq[RandFac] = Job_To_SomeFactory_Bestposition(JobA, TempSeq[RandFac]);
		}
		else if (Counter == 3)    //ECFS_Move
		{
			int JobAPt = rand() % TempSeq[CriticalFac].size();
			int JobA = TempSeq[CriticalFac][JobAPt];

			int JobBPt = rand() % TempSeq[RandFac].size();
			int JobB = TempSeq[RandFac][JobBPt];

			TempSeq[CriticalFac][JobAPt] = JobB;
			TempSeq[RandFac][JobBPt] = JobA;

			TempSpanSeq[CriticalFac] = GetFspan(TempSeq[CriticalFac]);
			TempSpanSeq[RandFac] = GetFspan(TempSeq[RandFac]);
		}

		int TempSpan = 0;
		for (int i = 0; i < TempSeq.size(); ++i)
		{
		    TempSpan +=  GetFspan(TempSeq[i]);/* *max_element(TempSpanSeq.begin(), TempSpanSeq.end());*/
		}
		if (TempSpan < Span)
		{
			Span = TempSpan;
			//SpanSeq = TempSpanSeq;
			Seq = TempSeq;
		}
	}
	return Span;
}

int DDE_Selection_Operator(float Selectcoefficient,int SpanofXi,int SpanofUi,vector<vector<int>>&Seq,vector<vector<int>>SeqFromCrossover)
{
	int Span = SpanofXi;
	float RE = (SpanofUi - SpanofXi) / SpanofXi;

	default_random_engine e(rand());
	uniform_real_distribution<float>u(0, 1.0);
	float randnum = u(e);

	float ComparedNum = Selectcoefficient - RE;
	if ((RE < 0) || (randnum < max(ComparedNum, 0)))
	{
		Seq = SeqFromCrossover;
		Span = SpanofUi;
	}
	return Span;
}

int DDE(long TimeLimit,int Psize, float Mcoefficien, float Crossovercoefficient,float Selectcoefficient,int Iter)  //Iter=γ
{
	long InitTime = GetElapsedProcessTime();
	//初始化
	vector<vector<vector<int>>>Population;
	Population.resize(Psize);
	vector<int>PopSpan;
	PopSpan.resize(Psize);

	PopSpan[0] = DSPT(Population[0]);
	PopSpan[1] = DNEH(Population[1]);

	for (int i = 2; i < Population.size(); i++)
		PopSpan[i] = GetARandomIndividual(Population[i]);

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		//找到最好的个体和一个随机个体//Local_Search
		int BestIndividual = -1;
		int TempPopSpan = INT_MAX;
		for (int i = 0; i < PopSpan.size(); i++)
		{
			if (PopSpan[i] < TempPopSpan)
			{
				TempPopSpan = PopSpan[i];
				BestIndividual = i;
			}
		}

		int RandIndividual = -1;
		do {
			RandIndividual = rand() % Population.size();
		} while (RandIndividual == BestIndividual);

		for (int iterations = 0; iterations < Iter * gJobs; iterations++)
		{
			if (GetElapsedProcessTime() - InitTime > TimeLimit)
				break;

			PopSpan[BestIndividual] = DDE_Local_Search(Population[BestIndividual]);
			PopSpan[RandIndividual] = DDE_Local_Search(Population[RandIndividual]);
		}

		vector<int>PopSeq;
		PopSeq.clear();
		for (int i = 0; i < Population.size(); i++)
			PopSeq.push_back(i);

		while ((PopSeq.size() > 0)&&(GetElapsedProcessTime() - InitTime < TimeLimit))
		{				
			int IndividualPt = rand() % PopSeq.size();
			int Individual = PopSeq[IndividualPt];
			PopSeq.erase(PopSeq.begin() + IndividualPt);

			vector<vector<int>>SeqFromMutation = Population[Individual];
			int SpanFromMutation = DDE_Mutation_Operator(Mcoefficien, SeqFromMutation);


			vector<vector<int>>SeqFromCrossover = Population[Individual];
			int SpanFromCrossover = DDE_Crossover_Operator(Crossovercoefficient, SeqFromCrossover, SeqFromMutation);

			PopSpan[Individual] = DDE_Selection_Operator(Selectcoefficient, PopSpan[Individual], SpanFromCrossover, Population[Individual], SeqFromCrossover);
		}
	}

	/*for (int i = 0; i < Population.size(); i++)
		CheckChrom(Population[i], PopSpan[i]);

	return *min_element(PopSpan.begin(), PopSpan.end());	*/
	int minimum = INT_MAX;
	for (int i = 0; i < Population.size(); i++)
	{
		int BestIndividual = GetFspan(Population[i]);/*FindBestIndividual(PE);*/
		if (BestIndividual < minimum)
		{
			minimum = BestIndividual;
		}
	}

	return minimum;
}

int DDE_Curve(long TimeLimit, int Psize, float Mcoefficien, float Crossovercoefficient, float Selectcoefficient, int Iter, int LocalValue, long LocalTime, int NO)  //Iter=γ
{
	long InitTime = GetElapsedProcessTime();
	//初始化
	vector<vector<vector<int>>>Population;
	Population.resize(Psize);
	vector<int>PopSpan;
	PopSpan.resize(Psize);

	PopSpan[0] = DSPT(Population[0]);
	PopSpan[1] = DNEH(Population[1]);

	for (int i = 2; i < Population.size(); i++)
		PopSpan[i] = GetARandomIndividual(Population[i]);

	//建立一个txt文件
	ostringstream str;
	str << "Test_DDE_Curve_Ins=" << NO << ".txt";                //
	ofstream ofile;
	ofile.open(str.str());

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		//找到最好的个体和一个随机个体//Local_Search
		int BestIndividual = -1;
		int TempPopSpan = INT_MAX;
		for (int i = 0; i < PopSpan.size(); i++)
		{
			if (PopSpan[i] < TempPopSpan)
			{
				TempPopSpan = PopSpan[i];
				BestIndividual = i;
			}
		}
		LocalValue = TempPopSpan;                             //
		LocalTime = GetElapsedProcessTime() - InitTime;         //
		ofile << LocalTime << "\t" << LocalValue << "\t" << endl;
		int RandIndividual = -1;
		do {
			RandIndividual = rand() % Population.size();
		} while (RandIndividual == BestIndividual);

		for (int iterations = 0; iterations < Iter * gJobs; iterations++)
		{
			if (GetElapsedProcessTime() - InitTime > TimeLimit)
				break;

			PopSpan[BestIndividual] = DDE_Local_Search(Population[BestIndividual]);
			PopSpan[RandIndividual] = DDE_Local_Search(Population[RandIndividual]);
		}

		vector<int>PopSeq;
		PopSeq.clear();
		for (int i = 0; i < Population.size(); i++)
			PopSeq.push_back(i);

		/*while ((PopSeq.size() > 0) && (GetElapsedProcessTime() - InitTime < TimeLimit))
		{*/
			int IndividualPt = rand() % PopSeq.size();
			int Individual = PopSeq[IndividualPt];
			PopSeq.erase(PopSeq.begin() + IndividualPt);

			vector<vector<int>>SeqFromMutation = Population[Individual];
			int SpanFromMutation = DDE_Mutation_Operator(Mcoefficien, SeqFromMutation);


			vector<vector<int>>SeqFromCrossover = Population[Individual];
			int SpanFromCrossover = DDE_Crossover_Operator(Crossovercoefficient, SeqFromCrossover, SeqFromMutation);

			PopSpan[Individual] = DDE_Selection_Operator(Selectcoefficient, PopSpan[Individual], SpanFromCrossover, Population[Individual], SeqFromCrossover);
		
			int minimum01 = INT_MAX;
			for (int i = 0; i < Population.size(); i++)
			{
				int BestIndividual01 = GetFspan(Population[i]);/*FindBestIndividual(PE);*/
				if (BestIndividual01 < minimum01)
				{
					minimum01 = BestIndividual01;
				}
			}
			LocalValue = minimum01;                             //
			LocalTime = GetElapsedProcessTime() - InitTime;         //
			ofile << LocalTime << "\t" << LocalValue << "\t" << endl;
		//}

	
	}
	ofile.close();
	/*for (int i = 0; i < Population.size(); i++)
		CheckChrom(Population[i], PopSpan[i]);

	return *min_element(PopSpan.begin(), PopSpan.end());	*/
	int minimum = INT_MAX;
	for (int i = 0; i < Population.size(); i++)
	{
		int BestIndividual = GetFspan(Population[i]);/*FindBestIndividual(PE);*/
		if (BestIndividual < minimum)
		{
			minimum = BestIndividual;
		}
	}

	return minimum;
}

int DDE_Test(int No)                         //
{
	float McoefficientArray[] = { 0.0, 0.5, 0.7, 1.0 };              //    
	float CrossovercoefficientArray[] = { 0.0, 0.5, 0.7, 1.0 };       //
	float SelectcoefficientArray[] = { 0.0, 0.5, 0.7, 1.0 };       //
	int IterArray[] = { 10,50,100,150 };

	int Psize = 20;
	int Temp = No;
	float Mcoefficient = McoefficientArray[Temp / (4 * 4 * 4)];        //
	Temp = Temp % (4 * 4 * 4);
	float Crossovercoefficient = CrossovercoefficientArray[Temp / (4 * 4)];               //
	Temp = Temp % (4 * 4);
	float Selectcoefficient = SelectcoefficientArray[Temp / 4];                   //
	Temp = Temp % 4;
	int Iter = IterArray[Temp];

	const int TotaltestIns = 20, Reps = 10;
	vector<vector<int>>MakeSpanArray;
	MakeSpanArray.resize(TotaltestIns);
	for (int i = 0; i < MakeSpanArray.size(); i++)
		MakeSpanArray[i].resize(Reps, 0);

	for (int ins = 0; ins < TotaltestIns; ins++)
	{
		string FileName = "DPFSPTestInstance\\TestFiles.txt", FileDirectory = "DPFSPTestInstance\\";
		ifstream ifile;
		ifile.open(FileName);
		string TestFileName;
		for (int xx = 0; xx <= ins; xx++)
			ifile >> TestFileName;
		ifile.close();
		TestFileName = FileDirectory + TestFileName;
		GetInstances_TaiE(gJobs, gMachine, gFactory, pTime, pSetupTime, TestFileName);

		long TimeLimit = 5 * gJobs * gMachine;      //
		for (int rep = 0; rep < Reps; rep++)
		{
			long start = GetElapsedProcessTime();
			srand(ins * 100 + rep);              //
			int Span = DDE(TimeLimit,Psize,Mcoefficient,Crossovercoefficient,Selectcoefficient,Iter);

			cout << "\t" << ins << "\t" << gJobs << "\t" << gMachine << "\t" << Span << "\t" << (GetElapsedProcessTime() - start) / 1000.0 << endl;
			MakeSpanArray[ins][rep] = Span;
		}
	}
	string FileDirectory = "DPFSPTestInstance\\DDETestResult\\";         //
	ostringstream str;
	str << "DDE_" << No << ".txt";                //
	ofstream ofile;
	ofile.open(FileDirectory + str.str());
	for (int ins = 0; ins < TotaltestIns; ins++)
	{
		for (int rep = 0; rep < Reps; rep++)
		{
			ofile << setw(8) << MakeSpanArray[ins][rep];
		}
		ofile << endl;
	}
	ofile.close();
	return 0;
}


void DDE_Calibration(int Parts, int PartNo)       //
{
	srand(1994);
	vector <int> NoArray;
	for (int i = 0; i < 4 * 4 * 4 * 4; i++)      //
		NoArray.push_back(i);
	random_shuffle(NoArray.begin(), NoArray.end());

	int div = NoArray.size() / Parts;
	int Start = PartNo * div;
	int End = min(Start + div, NoArray.size());

	for (int i = Start; i < End; i++)
		DDE_Test(NoArray[i]);           //
}

void GetFinaltext_DDE()               //
{
	const int TotalIns = 20, Reps = 10, Confs = 4 * 4 * 4 * 4;       //
	int SpanArray[TotalIns][Confs * Reps];
	string Dir = "DPFSPTestInstance\\DDETestResult\\";         //
	for (int i = 0; i < Confs; i++)
	{
		ostringstream outstr;
		outstr << i;
		string FName = Dir + "DDE_";                          //
		FName = FName + outstr.str() + ".txt";
		ifstream ifile;
		ifile.open(FName);
		if (!ifile)
		{
			cout << "File is not existed!" << endl;
			exit(0);
		}
		for (int Ins = 0; Ins < TotalIns; Ins++)
		{
			for (int Rep = 0; Rep < Reps; Rep++)
			{
				ifile >> SpanArray[Ins][i * Reps + Rep];
			}
		}
		ifile.close();
	}
	int minSpanArray[TotalIns];
	for (int Ins = 0; Ins < TotalIns; Ins++)
	{
		minSpanArray[Ins] = INT_MAX;
		for (int i = 0; i < Confs * Reps; i++)
		{
			if (SpanArray[Ins][i] < minSpanArray[Ins])
			{
				minSpanArray[Ins] = SpanArray[Ins][i];
			}
		}
	}

	float McoefficientArray[] = { 0.0, 0.5, 0.7, 1.0 };              //    
	float CrossovercoefficientArray[] = { 0.0, 0.5, 0.7, 1.0 };       //
	float SelectcoefficientArray[] = { 0.0, 0.5, 0.7, 1.0 };       //
	int IterArray[] = { 10,50,100,150 };

	string FileDirectory = "DPFSPTestInstance\\DDETestResult\\";          //
	ostringstream str;
	str << "Cal_DDE" << ".txt";               //
	ofstream ofile;
	ofile.open(FileDirectory + str.str());

	ofile << "Ins\t";
	ofile << "Mcoefficient\t";             //
	ofile << "Crossovercoefficient\t";             //
	ofile << "Selectcoefficient\t";             //
	ofile << "Iter\t";             //
	ofile << "Span\t";
	ofile << "RPI \t" << endl;

	for (int Ins = 0; Ins < TotalIns; Ins++)
	{
		for (int No = 0; No < Confs * Reps; No++)
		{
			//algorithmic parameters
			int Conf = No / Reps;
			float Mcoefficient = McoefficientArray[Conf / (4 * 4 * 4)];      //
			Conf = Conf % (4 * 4 * 4);                     //
			float Crossovercoefficient = CrossovercoefficientArray[Conf / (4 * 4)];
			Conf = Conf % (4 * 4);
			float Selectcoefficient = SelectcoefficientArray[Conf /4];
			Conf = Conf % 4;
			int Iter = IterArray[Conf];        //

			ofile << Ins << "\t";
			ofile << Mcoefficient << "\t";        //
			ofile << Crossovercoefficient << "\t";         //
			ofile << Selectcoefficient << "\t";         //
			ofile << Iter << "\t";         //
			ofile << SpanArray[Ins][No] << "\t";
			double RPD = (SpanArray[Ins][No] - minSpanArray[Ins]) * 100.0 / minSpanArray[Ins];
			ofile << RPD << endl;
		}
	}
	ofile.close();
}