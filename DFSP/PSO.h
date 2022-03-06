#pragma once

void GetIncreasingOrder(vector<float>Position, vector<int>& Order)   //按升序排列
{
	Order.clear();

	vector<vector<float>>Order_List;
	Order_List.resize(Position.size());
	for (int i = 0; i < Order_List.size(); i++)
		Order_List[i].resize(2);

	for (int i = 0; i < Order_List.size(); i++)
	{
		Order_List[i][0] = i;
		Order_List[i][1] = Position[i];
	}

	sort(Order_List.begin(), Order_List.end(), [](vector<float> t1, vector<float> t2)
		{
			return (t1[1] < t2[1]);
		});

	for (int i = 0; i < Order_List.size(); i++)
		Order.push_back(Order_List[i][0]);
}

int SPV(vector<float>Position,vector<vector<int>>&Seq)
{
	Seq.resize(gFactory);
	for (int f = 0; f < Seq.size(); f++)
		Seq[f].clear();

	vector<int>JobSeq;
	JobSeq.clear();
	for (int i = 0; i < gJobs; i++)
		JobSeq.push_back(i);

	vector<int>Order;
	GetIncreasingOrder(Position, Order);

	for (int f = 0; f < Seq.size(); f++)
		Seq[f].push_back(JobSeq[Order[f]]);

	vector<int>SpanSeq;
	SpanSeq.resize(Seq.size());

	for (int f = 0; f < SpanSeq.size(); f++)
		SpanSeq[f] = GetFspan(Seq[f]);

	for (int i = Seq.size(); i < Order.size(); i++)
	{
		int TempSpan = INT_MAX;
		int FacwithMinSpan = -1;
		for (int f = 0; f < SpanSeq.size(); f++)
		{
			if (SpanSeq[f] < TempSpan)
			{
				TempSpan = SpanSeq[f];
				FacwithMinSpan = f;
			}
		}
		SpanSeq[FacwithMinSpan] = Job_To_SomeFactory_Bestposition(JobSeq[Order[i]], Seq[FacwithMinSpan]);
	}
	int Span = *max_element(SpanSeq.begin(), SpanSeq.end());	
	return Span;
}

void UpdateVelocity(float c1, float c2, vector<float>& Velocity,vector<float>Position, vector<float>PersonalBestPos, vector<float>GlobalBestPos)
{
	default_random_engine e(rand());
	uniform_real_distribution<float>u(0, 1.0);
	float randnum1 = u(e);
	float randnum2 = u(e);

	for (int i = 0; i < Velocity.size(); i++)
		Velocity[i] = Velocity[i] + c1 * randnum1 * (PersonalBestPos[i] - Position[i]) + c2 * randnum2 * (GlobalBestPos[i] - Position[i]);
}

void UpdatePosition(vector<float>&Position,vector<float>Velocity)
{
	for (int i = 0; i < Position.size(); i++)
		Position[i] = Position[i] + Velocity[i];
}

void Solution_Improvement(long TimeLimit,long InitialTime,int Iter,int &Span,vector<vector<int>>&Seq, vector<float>& Position, vector<float>&Velocity)
{
	vector<vector<int>>BestSeq = Seq;
	int BestSpan = Span;
	vector<float>BestPosition = Position;
	vector<float>BestVelocity = Velocity;

	int Counter = 0;
	while (Counter < Iter)
	{
		if (GetElapsedProcessTime() - InitialTime > TimeLimit)
		{
			Counter = Iter;
			break;
		}
		//adjacent pairwise interchange scheme
		int RandFac = rand() % Seq.size();
		int StartPoint = rand() % Seq[RandFac].size();
		if (StartPoint == Seq[RandFac].size() - 1)
		{
			int FrontJob = Seq[RandFac][StartPoint - 1];
			int AfterJob = Seq[RandFac][StartPoint];

			Seq[RandFac][StartPoint - 1] = AfterJob;
			Seq[RandFac][StartPoint] = FrontJob;

			float TempPos = Position[AfterJob];
			Position[AfterJob] = Position[FrontJob];
			Position[FrontJob] = TempPos;

			float TempVelocity = Velocity[AfterJob];
			Velocity[AfterJob] = Velocity[FrontJob];
			Velocity[FrontJob] = TempVelocity;
		}
		else
		{
			int FrontJob = Seq[RandFac][StartPoint];
			int AfterJob = Seq[RandFac][StartPoint + 1];

			Seq[RandFac][StartPoint] = AfterJob;
			Seq[RandFac][StartPoint + 1] = FrontJob;

			float TempPos = Position[AfterJob];
			Position[AfterJob] = Position[FrontJob];
			Position[FrontJob] = TempPos;

			float TempVelocity = Velocity[AfterJob];
			Velocity[AfterJob] = Velocity[FrontJob];
			Velocity[FrontJob] = TempVelocity;
		}

		//find two distinct elements randomly;
/*		int Job1, Job2, JobPt1, JobPt2, FacPt1, FacPt2;
		do {
			FacPt1 = rand() % Seq.size();
			FacPt2 = rand() % Seq.size();
			JobPt1 = rand() % Seq[FacPt1].size();
			JobPt2 = rand() % Seq[FacPt2].size();
			Job1 = Seq[FacPt1][JobPt1];
			Job2 = Seq[FacPt2][JobPt2];
		} while (Job1 == Job2);

		//swap
		Seq[FacPt1][JobPt1] = Job2;
		Seq[FacPt2][JobPt2] = Job1;

		float TempPos = Position[Job1];
		Position[Job1] = Position[Job2];
		Position[Job2] = TempPos;

		float TempVelocity = Velocity[Job1];
		Velocity[Job1] = Velocity[Job2];
		Velocity[Job2] = TempVelocity;*/

		Span = GetFspan(Seq);
		if (Span < BestSpan)
		{
			BestSpan = Span;
			BestSeq = Seq;
			BestPosition = Position;
			BestVelocity = Velocity;
			Counter = 0;
		}
		else
		{
			Span = BestSpan;
			Seq = BestSeq;
			Position = BestPosition;
			Velocity = BestVelocity;
			Counter++;
		}
	}
	Span = BestSpan;
	Seq = BestSeq;
	Position = BestPosition;
	Velocity = BestVelocity;
}

int PSO(long TimeLimit, int Psize,int Iter, float c1, float c2)
{
	long InitTime = GetElapsedProcessTime();

	//初始化
	vector<vector<vector<int>>>Population;
	Population.resize(Psize);

	vector<int>PopSpan;
	PopSpan.resize(Psize, 0);

	PopSpan[0] = DSPT(Population[0]);
	PopSpan[1] = DNEH(Population[1]);

	vector<vector<float>>PopPosition;
	PopPosition.resize(Psize);
	for (int i = 0; i < PopPosition.size(); i++)
	{
		for (int j = 0; j < gJobs; j++)
		{
			default_random_engine e(rand());
			uniform_real_distribution<float>u(0, 1.0);
			float randnum = u(e);
			PopPosition[i].push_back(randnum);
		}
	}

	for (int i = 2; i < Psize; i++)
		PopSpan[i] = SPV(PopPosition[i], Population[i]);

	vector<vector<float>>PopVelocity;
	PopVelocity.resize(Psize);
	for (int i = 0; i < PopVelocity.size(); i++)
	{
		for (int j = 0; j < gJobs; j++)
		{
			default_random_engine e(rand());
			uniform_real_distribution<float>u(0, 1.0);
			float randnum = u(e);
			PopVelocity[i].push_back(randnum);
		}
	}

	vector<vector<vector<int>>>PersonalBestPop = Population;
	vector<int>PersonalBestPopSpan = PopSpan;
	vector<vector<float>>PersonalBestPopPosition = PopPosition;
	vector<vector<float>>PersonalBestPopVelocity = PopVelocity;

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		int BestIndiPt = -1;
		int SpanofBestIndi = INT_MAX;
		for (int i = 0; i < PopSpan.size(); i++)
		{
			if (PopSpan[i] < SpanofBestIndi)
			{
				SpanofBestIndi = PopSpan[i];
				BestIndiPt = i;
			}
		}
		vector<vector<int>>GlobalBestIndi = Population[BestIndiPt];
		vector<float>GlobalBestPosition = PopPosition[BestIndiPt];
		vector<float>GlobalBestVelocity = PopVelocity[BestIndiPt];

		for (int i = 0; i < Population.size(); i++)
		{
			if (GetElapsedProcessTime() - InitTime > TimeLimit)
				break;

			UpdateVelocity(c1, c2, PopVelocity[i], PopPosition[i], PersonalBestPopPosition[i], GlobalBestPosition);
			UpdatePosition(PopPosition[i], PopVelocity[i]);
			PopSpan[i] = SPV(PopPosition[i], Population[i]);
			Solution_Improvement(TimeLimit, InitTime,Iter, PopSpan[i], Population[i], PopPosition[i], PopVelocity[i]);

			if (PopSpan[i] < PersonalBestPopSpan[i])
			{
				PersonalBestPopSpan[i] = PopSpan[i];
				PersonalBestPop[i] = Population[i];
				PersonalBestPopPosition[i] = PopPosition[i];
				PersonalBestPopVelocity[i] = PopVelocity[i];
			}
		}
	}
	//for (int i = 0; i < PersonalBestPop.size(); i++)
	//	CheckChrom(PersonalBestPop[i], PersonalBestPopSpan[i]);
	int total = INT_MAX;
	for (int i = 0; i < PersonalBestPop.size(); i++)
	{
		if (GetFspan(PersonalBestPop[i])< total)
		{
			total = GetFspan(PersonalBestPop[i]);
		}
	}
	return total;/**min_element(PersonalBestPopSpan.begin(), PersonalBestPopSpan.end());*/
}


int PSO_Curve(long TimeLimit, int Psize, int Iter, float c1, float c2,int LocalValue, long LocalTime, int No)
{
	long InitTime = GetElapsedProcessTime();

	//初始化
	vector<vector<vector<int>>>Population;
	Population.resize(Psize);

	vector<int>PopSpan;
	PopSpan.resize(Psize, 0);

	PopSpan[0] = DSPT(Population[0]);
	PopSpan[1] = DNEH(Population[1]);

	vector<vector<float>>PopPosition;
	PopPosition.resize(Psize);
	for (int i = 0; i < PopPosition.size(); i++)
	{
		for (int j = 0; j < gJobs; j++)
		{
			default_random_engine e(rand());
			uniform_real_distribution<float>u(0, 1.0);
			float randnum = u(e);
			PopPosition[i].push_back(randnum);
		}
	}

	for (int i = 2; i < Psize; i++)
		PopSpan[i] = SPV(PopPosition[i], Population[i]);

	vector<vector<float>>PopVelocity;
	PopVelocity.resize(Psize);
	for (int i = 0; i < PopVelocity.size(); i++)
	{
		for (int j = 0; j < gJobs; j++)
		{
			default_random_engine e(rand());
			uniform_real_distribution<float>u(0, 1.0);
			float randnum = u(e);
			PopVelocity[i].push_back(randnum);
		}
	}

	vector<vector<vector<int>>>PersonalBestPop = Population;
	vector<int>PersonalBestPopSpan = PopSpan;
	vector<vector<float>>PersonalBestPopPosition = PopPosition;
	vector<vector<float>>PersonalBestPopVelocity = PopVelocity;

	//建立一个txt文件
	ostringstream str;
	str << "Test_PSO_Curve_Ins=" << No << ".txt";                //
	ofstream ofile;
	ofile.open(str.str());

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		int BestIndiPt = -1;
		int SpanofBestIndi = INT_MAX;
		for (int i = 0; i < PopSpan.size(); i++)
		{
			if (PopSpan[i] < SpanofBestIndi)
			{
				SpanofBestIndi = PopSpan[i];
				BestIndiPt = i;
			}
		}
		vector<vector<int>>GlobalBestIndi = Population[BestIndiPt];
		vector<float>GlobalBestPosition = PopPosition[BestIndiPt];
		vector<float>GlobalBestVelocity = PopVelocity[BestIndiPt];

		for (int i = 0; i < Population.size(); i++)
		{
			if (GetElapsedProcessTime() - InitTime > TimeLimit)
				break;

			UpdateVelocity(c1, c2, PopVelocity[i], PopPosition[i], PersonalBestPopPosition[i], GlobalBestPosition);
			UpdatePosition(PopPosition[i], PopVelocity[i]);
			PopSpan[i] = SPV(PopPosition[i], Population[i]);
			Solution_Improvement(TimeLimit, InitTime, Iter, PopSpan[i], Population[i], PopPosition[i], PopVelocity[i]);

			if (PopSpan[i] < PersonalBestPopSpan[i])
			{
				PersonalBestPopSpan[i] = PopSpan[i];
				PersonalBestPop[i] = Population[i];
				PersonalBestPopPosition[i] = PopPosition[i];
				PersonalBestPopVelocity[i] = PopVelocity[i];
			}
		}

		int total = INT_MAX;
		for (int i = 0; i < PersonalBestPop.size(); i++)
		{
			if (GetFspan(PersonalBestPop[i]) < total)
			{
				total = GetFspan(PersonalBestPop[i]);
			}
		}
		LocalValue = total;                             //
		LocalTime = GetElapsedProcessTime() - InitTime;         //
		ofile << LocalTime << "\t" << LocalValue << "\t" << endl;
	}
	ofile.close();
	//for (int i = 0; i < PersonalBestPop.size(); i++)
	//	CheckChrom(PersonalBestPop[i], PersonalBestPopSpan[i]);
	int total = INT_MAX;
	for (int i = 0; i < PersonalBestPop.size(); i++)
	{
		if (GetFspan(PersonalBestPop[i]) < total)
		{
			total = GetFspan(PersonalBestPop[i]);
		}
	}
	return total;/**min_element(PersonalBestPopSpan.begin(), PersonalBestPopSpan.end());*/
}

int PSO_Test(int No)                         //
{
	int PsizeArray[] = { 10,20,30,40,50,100,150,200,250,300 };              //    
	int IterArray[] = { 500,1000,1500,2000,2500,3000,3500,4000,5000 };       //

	float c1 = 0.5;
	float c2 = 0.5;

	int Temp = No;
	int Psize = PsizeArray[Temp /9];        //
	Temp = Temp % 9;
	int Iter = IterArray[Temp];               //

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
			int Span = PSO(TimeLimit, Psize, Iter, c1, c2);

			cout << "\t" << ins << "\t" << gJobs << "\t" << gMachine << "\t" << Span << "\t" << (GetElapsedProcessTime() - start) / 1000.0 << endl;
			MakeSpanArray[ins][rep] = Span;
		}
	}
	string FileDirectory = "DPFSPTestInstance\\PSOTestResult\\";         //
	ostringstream str;
	str << "PSO_" << No << ".txt";                //
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

void PSO_Calibration(int Parts, int PartNo)       //
{
	srand(1994);
	vector <int> NoArray;
	for (int i = 0; i < 10 * 9; i++)      //
		NoArray.push_back(i);
	random_shuffle(NoArray.begin(), NoArray.end());

	int div = NoArray.size() / Parts;
	int Start = PartNo * div;
	int End = min(Start + div, NoArray.size());

	for (int i = Start; i < End; i++)
		PSO_Test(NoArray[i]);           //
}

void GetFinaltext_PSO()               //
{
	const int TotalIns = 20, Reps = 10, Confs = 10 * 9;       //
	int SpanArray[TotalIns][Confs * Reps];
	string Dir = "DPFSPTestInstance\\PSOTestResult\\";         //
	for (int i = 0; i < Confs; i++)
	{
		ostringstream outstr;
		outstr << i;
		string FName = Dir + "PSO_";                          //
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

	int PsizeArray[] = { 10,20,30,40,50,100,150,200,250,300 };              //    
	int IterArray[] = { 500,1000,1500,2000,2500,3000,3500,4000,5000 };       //

	string FileDirectory = "DPFSPTestInstance\\PSOTestResult\\";          //
	ostringstream str;
	str << "Cal_PSO" << ".txt";               //
	ofstream ofile;
	ofile.open(FileDirectory + str.str());

	ofile << "Ins\t";
	ofile << "Psize\t";             //
	ofile << "Iter\t";              //
	ofile << "Span\t";
	ofile << "RPI \t" << endl;

	for (int Ins = 0; Ins < TotalIns; Ins++)
	{
		for (int No = 0; No < Confs * Reps; No++)
		{
			//algorithmic parameters
			int Conf = No / Reps;
			int Psize = PsizeArray[Conf /9];      //
			Conf = Conf % 9;                     //
			int Iter = IterArray[Conf];

			ofile << Ins << "\t";
			ofile << Psize << "\t";        //
			ofile << Iter << "\t";         //
			ofile << SpanArray[Ins][No] << "\t";
			double RPD = (SpanArray[Ins][No] - minSpanArray[Ins]) * 100.0 / minSpanArray[Ins];
			ofile << RPD << endl;
		}
	}
	ofile.close();
}
