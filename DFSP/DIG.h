#pragma once
void Swap_random_between(vector<vector<int>>& Seq) // swap two neighbor jobs
{
	vector<vector<int>>tempSeq;
	tempSeq = Seq;
	bool flag = true;

	int  Fpt1, Fpt2;
	do
	{
		Fpt1 = rand() % Seq.size();
		Fpt2 = rand() % Seq.size();
	} while (Fpt1 == Fpt2);


	while (flag == true)
	{
		flag = false;

		//随机找到两个工厂

		int FinalEC;
		for (int i = 0; i < tempSeq[Fpt1].size(); i++)
		{
			int Job = tempSeq[Fpt1][i];
			int SelFac = 0;
			int BestPos = 0;
			FinalEC = Job_ToSwap_BestFactory_Bestposition(Fpt1, i, Job, tempSeq, SelFac, BestPos);
			if (FinalEC < GetFspan(Seq))
			{
				flag = true;
				Seq = tempSeq;
			}
			else {
				tempSeq = Seq;
			}

		}

	}
	if (GetFspan(tempSeq) < GetFspan(Seq))
	{
		Seq = tempSeq;
	}
}

void SwapJobs_random_betweenTwoFac(vector<vector<int>>& Seq) // swap two neighbor jobs
{
	vector<vector<int>>tempSeq;
	tempSeq = Seq;

	int maxvalue = -1;
	int maxFac = -1;
	for (int i = 0; i < gFactory; i++)
	{
		if (maxvalue < GetFspan(Seq[i]))
		{
			maxvalue = GetFspan(Seq[i]);
			maxFac = i;
		}
	}

	int Fpt1;
	do
	{
		Fpt1 = rand() % gFactory;

	} while (Fpt1 == maxFac);

	int FinalEC;

	for (int i = 0; i < gJobs * gJobs; i++)
	{
		int r1 = rand() % Seq[maxFac].size();
		int r2 = rand() % Seq[Fpt1].size();
		swap(tempSeq[maxFac][r1], tempSeq[Fpt1][r2]);

		FinalEC = GetFspan(tempSeq);
		if (FinalEC < GetFspan(Seq))
		{
			Seq = tempSeq;
		}
		else {
			tempSeq = Seq;
		}

	}


	if (GetFspan(tempSeq) < GetFspan(Seq))
	{
		Seq = tempSeq;
	}

}

void SwapJobs_random_betweenTwoFac02(vector<vector<int>>& Seq) // swap two neighbor jobs
{
	vector<vector<int>>tempSeq;
	tempSeq = Seq;

	int Fpt1, Fpt2;
	do
	{
		Fpt1 = rand() % gFactory;
		Fpt2 = rand() % gFactory;
	} while (Fpt1 == Fpt2);

	int FinalEC;

	for (int i = 0; i < gJobs * gJobs; i++)
	{
		int r1 = rand() % Seq[Fpt1].size();
		int r2 = rand() % Seq[Fpt2].size();
		swap(tempSeq[Fpt2][r2], tempSeq[Fpt1][r1]);

		FinalEC = GetFspan(tempSeq);
		if (FinalEC < GetFspan(Seq))
		{
			Seq = tempSeq;
		}
		else {
			tempSeq = Seq;
		}

	}


	if (GetFspan(tempSeq) < GetFspan(Seq))
	{
		Seq = tempSeq;
	}

}

//内部阻塞工件交换策略1
void Swap_Block_01(vector<int>& Seq, vector<int> blockingJobs, vector<int> blockingJobsPos)
{
	vector<int> tempSeq = Seq;
	vector<int> tempblockingJobs = blockingJobs;
	int BestValueSofar = GetFspan(Seq);
	bool flag = true;
	while (flag == true)
	{
		flag = false;
		for (int i = 0; i < blockingJobsPos.size(); ++i)
		{
			for (int j = 0; j < blockingJobsPos.size(); ++j)
			{
				if (tempSeq[blockingJobsPos[i]] != tempSeq[blockingJobsPos[j]])
				{
					int temp = tempSeq[blockingJobsPos[i]];
					tempSeq[blockingJobsPos[i]] = tempSeq[blockingJobsPos[j]];
					tempSeq[blockingJobsPos[j]] = temp;

					int tempEC = GetFspan(tempSeq);
					if (tempEC < BestValueSofar)
					{
						Seq = tempSeq;
						BestValueSofar = tempEC;
						flag = true;
					}
					else {
						tempSeq = Seq;

					}
				}
			}
		}
	}
}

//内部阻塞工件交换策略2
void Swap_Block_02(vector<int>& Seq, vector<int> blockingJobs, vector<int> blockingJobsPos)
{
	vector<int> tempSeq = Seq;
	vector<int> tempblockingJobs = blockingJobs;
	int BestValueSofar = GetFspan(Seq);
	bool flag = true;
	while (flag == true)
	{
		flag = false;
		for (int i = 0; i < blockingJobsPos.size(); ++i)
		{
			for (int j = 0; j < blockingJobsPos.size(); ++j)
			{
				if (tempSeq[blockingJobsPos[i]] != tempSeq[blockingJobsPos[j]])
				{
					int temp = tempSeq[blockingJobsPos[i]];
					tempSeq[blockingJobsPos[i]] = tempSeq[blockingJobsPos[j]];
					tempSeq[blockingJobsPos[j]] = temp;

					int tempEC = GetFspan(tempSeq);
					if (tempEC < BestValueSofar)
					{
						vector<int> Seq02 = tempSeq;
						tempSeq = Seq;
						Seq = Seq02;
						BestValueSofar = tempEC;
						flag = true;
					}
					else {
						tempSeq = Seq;
					}
				}
			}
		}
	}
}


//跨工厂阻塞工件交换策略3
void Swap_Block_03(vector<vector<int>>& Seq, vector<vector<int>> blockingJobs, vector<vector<int>> blockingJobsPos)
{
	//随机找到两个工厂
	int  Fpt1, Fpt2;
	do
	{
		Fpt1 = rand() % Seq.size();
		Fpt2 = rand() % Seq.size();
	} while (Fpt1 == Fpt2);

	vector<vector<int>> tempSeq = Seq;

	int BestValueSofar = GetFspan(Seq);

	for (int i = 0; i < blockingJobsPos[Fpt1].size(); ++i)
	{
		for (int j = 0; j < blockingJobsPos[Fpt2].size(); ++j)
		{

			int temp = tempSeq[Fpt1][blockingJobsPos[Fpt1][i]];
			tempSeq[Fpt1][blockingJobsPos[Fpt1][i]] = tempSeq[Fpt2][blockingJobsPos[Fpt2][j]];
			tempSeq[Fpt2][blockingJobsPos[Fpt2][j]] = temp;

			int tempEC = GetFspan(tempSeq);
			if (tempEC < BestValueSofar)
			{
				Seq = tempSeq;
				BestValueSofar = tempEC;

			}
			else {
				tempSeq = Seq;
			}

		}
	}
}


//跨工厂阻塞工件交换策略4
void Swap_Block_04(vector<vector<int>>& Seq, vector<vector<int>> blockingJobs, vector<vector<int>> blockingJobsPos)
{
	//随机找到两个工厂
	int  Fpt1, Fpt2;
	do
	{
		Fpt1 = rand() % Seq.size();
		Fpt2 = rand() % Seq.size();
	} while (Fpt1 == Fpt2);

	vector<vector<int>> tempSeq = Seq;

	int BestValueSofar = GetFspan(Seq);

	for (int i = 0; i < blockingJobsPos[Fpt1].size(); ++i)
	{
		for (int j = 0; j < blockingJobsPos[Fpt2].size(); ++j)
		{

			int temp = tempSeq[Fpt1][blockingJobsPos[Fpt1][i]];
			tempSeq[Fpt1][blockingJobsPos[Fpt1][i]] = tempSeq[Fpt2][blockingJobsPos[Fpt2][j]];
			tempSeq[Fpt2][blockingJobsPos[Fpt2][j]] = temp;

			int tempEC = GetFspan(tempSeq);
			if (tempEC < BestValueSofar)
			{
				vector<vector<int>> Seq02 = tempSeq;
				tempSeq = Seq;
				Seq = Seq02;
				BestValueSofar = tempEC;

			}
			else {
				tempSeq = Seq;
			}

		}
	}
}


//随机选个工厂，然后交换里面的工件
void Swap_Inner(vector<int> Seq)
{
	vector<int>tempSeq;
	vector<int> tempSeq02;
	tempSeq = Seq;

	int FinalEC;
	for (int i = 0; i < tempSeq.size(); i++)
	{
		int temp;
		tempSeq02 = tempSeq;

		for (int j = 0; j < tempSeq02.size(); j++)
		{
			temp = tempSeq02[i];
			tempSeq02[i] = tempSeq02[j];
			tempSeq02[j] = temp;
			if (GetFspan(tempSeq02) < GetFspan(tempSeq))
			{
				tempSeq = tempSeq02;
			}
		}

	}

	if (GetFspan(tempSeq) < GetFspan(Seq))
	{
		Seq = tempSeq;
	}
}

void NSwap(vector <int>& p)
{
	//Find two distinct elements randomly;
	for (int i = 0; i < gJobs * gJobs; ++i)
	{
		vector <int> p1(p.size(), 0);
		p1 = p;
		int  pt1, pt2;
		do
		{
			pt1 = rand() % p.size();
			pt2 = rand() % p.size();
		} while (pt1 == pt2);

		swap(p1[pt1], p1[pt2]);
		if (GetFspan(p1) < GetFspan(p))
		{
			p = p1;
		}
	}

}

//针对一特定工厂，进行交换操作
void Swap_Block_Inner_ToSomeFactory_01(vector<int>& Seq)
{
	vector<int>tempSeq;
	tempSeq = Seq;
	int FinalEC;
	bool flag = true;
	while (flag == true)
	{
		flag = false;
		for (int i = 0; i < tempSeq.size(); i++)
		{
			int temp;
			int pos;
			vector<int>tempSeq02;
			tempSeq02 = tempSeq;

			int minvalue = GetFspan(tempSeq);

			for (int j = 0; j < tempSeq.size(); j++)
			{
				temp = tempSeq02[i];
				tempSeq02[i] = tempSeq02[j];
				tempSeq02[j] = temp;
				int minEC = GetFspan(tempSeq02);
				if (minEC < minvalue)
				{
					minvalue = minEC;
					pos = j;
				}
				tempSeq02 = tempSeq;
			}
			if (minvalue < GetFspan(tempSeq))
			{
				temp = tempSeq[i];
				tempSeq[i] = tempSeq[pos];
				tempSeq[pos] = temp;
				flag = true;
			}

		}
	}
	if (GetFspan(tempSeq) < GetFspan(Seq))
	{
		Seq = tempSeq;
	}
}

//针对一特定工厂，进行交换操作
void Swap_Block_Inner_ToSomeFactory_02(vector<int>& Seq)
{
	vector<int>tempSeq;
	tempSeq = Seq;
	int FinalEC;
	bool flag = true;
	while (flag == true)
	{
		flag = false;
		for (int i = 0; i < tempSeq.size(); i++)
		{
			int temp;
			int pos;
			vector<int>tempSeq02;
			tempSeq02 = tempSeq;

			int minvalue = GetFspan(tempSeq);

			for (int j = 0; j < tempSeq.size(); j++)
			{
				if (i != j)
				{
					temp = tempSeq02[i];
					tempSeq02[i] = tempSeq02[j];
					tempSeq02[j] = temp;
					int minEC = GetFspan(tempSeq02);
					if (minEC < minvalue)
					{
						minvalue = minEC;
						tempSeq = tempSeq02;
						flag = true;
					}
				}

			}

		}
	}
	if (GetFspan(tempSeq) < GetFspan(Seq))
	{
		Seq = tempSeq;
	}
}

//找到能耗最大的工厂，与其他工厂工件交换位置
void Swap_Block_between(vector<vector<int>>& Seq) // swap two neighbor jobs
{
	vector<vector<int>>tempSeq;
	tempSeq = Seq;

	int maxvalue = -1;
	int maxFac = -1;
	for (int i = 0; i < Seq.size(); i++)
	{
		if (maxvalue < GetFspan(Seq[i]))
		{
			maxvalue = GetFspan(Seq[i]);
			maxFac = i;
		}
	}

	int FinalEC;
	for (int i = 0; i < tempSeq[maxFac].size(); i++)
	{
		int Job = tempSeq[maxFac][i];
		int SelFac = 0;
		int BestPos = 0;
		FinalEC = Job_ToSwap_BestFactory_Bestposition(maxFac, i, Job, tempSeq, SelFac, BestPos);
		if (FinalEC < GetFspan(Seq))
		{
			Seq = tempSeq;
		}
		else {
			tempSeq = Seq;
		}

	}

	if (GetFspan(tempSeq) < GetFspan(Seq))
	{
		Seq = tempSeq;
	}
}


void Destruction_To_someFactory(vector<int>& Seq, vector<int>& DesJobSeq, int PLen)
{
	DesJobSeq.clear();
	while (DesJobSeq.size() < PLen)
	{
		if (Seq.size() > 1)
		{
			int pt = rand() % Seq.size();
			DesJobSeq.push_back(Seq[pt]);
			Seq.erase(Seq.begin() + pt);
		}
	}
}

void Construction_To_someFactory(vector<int>& Seq, vector<int>& DesJobSeq)
{
	for (int i = 0; i < DesJobSeq.size(); i++)
	{
		int Job = DesJobSeq[i];
		int BestPos = 0;
		Job_To_SomeFactory_Bestposition(Job, Seq);
	}
}

//double Compute_fitness_Multifactory(vector<vector<int>> Sol, vector<double>&fitness)
//{
//	fitness.clear();
//	for (int i = 0; i < Sol.size(); ++i)
//	{
//		fitness[i] = 1.0 / GetFspan(Sol[i]);
//	}
//}
//
//double Compute_fitness_Singlefactory(vector<int> Sol, vector<double>& fitness, int i)
//{	
//	fitness[i] = 1.0 / GetFspan(Sol);	
//}
//
//void SortAccordingfitness(vector<int>& factory, vector<double>& fitness)
//{
//	Pair* ch = new Pair[factory.size()];
//	for (int j = 0; j < factory.size(); j++)
//	{
//		ch[j].dim = factory[j];
//		ch[j].value = fitness[j];
//	}
//	sort(ch, ch + factory.size(), PairGreater());
//	for (int j = 0; j < factory.size(); j++)
//	{
//		factory[j] = ch[j].dim;
//		fitness[j] = ch[j].value;
//	}
//		
//	delete[]ch;
//}

//void QTableUpdate(vector<vector<double>>& QTable,int strategies, double learnrate, double discountrate, vector<double>fitnessold, vector<double>fitnessnew,int action, vector<int>& factory,vector<int>restore_r)
//{
//
//	for (int i = 0; i < gFactory; ++i)
//	{
//		QTable[factory[i]][restore_r[i]] = (1 - learnrate)* QTable[factory[i]][restore_r[i]] + learnrate*((fitnessnew[i]- fitnessold[i])+ discountrate*(MaxQTableStrategyValue(QTable, strategies, factory[i], action)));	
//	}
//}
//
//void QTableUpdate_SARSA(vector<vector<double>>& QTable, int strategies, double learnrate, double discountrate, vector<double>fitnessold, vector<double>fitnessnew, int action, vector<int>& Individualnum, vector<int>restore_r)
//{
//
//	for (int i = 0; i < gFactory; ++i)
//	{
//		QTable[Individualnum[i]][restore_r[i]] = (1 - learnrate) * QTable[Individualnum[i]][restore_r[i]] + learnrate * ((fitnessnew[i] - fitnessold[i]) + discountrate * (QTableStrategyValue(QTable, strategies, Individualnum[i], action, )));
//	}
//}

void StrategiesSet_Selection(int r, vector<int>& Seq, int Plen, vector<int> blockingJobs, vector<int> blockingJobsPos)
{
	if (r == 0)
	{
		vector<int>DesJobSeq;
		Destruction_To_someFactory(Seq, DesJobSeq, Plen);
		Construction_To_someFactory(Seq, DesJobSeq);
	}
	else if (r == 1)
	{
		Swap_Block_01(Seq, blockingJobs, blockingJobsPos);
	}
	else if (r == 2)
	{
		Swap_Block_02(Seq, blockingJobs, blockingJobsPos);
	}
	else if (r == 3)
	{
		Swap_Block_Inner_ToSomeFactory_01(Seq);
	}
	else {
		Swap_Block_Inner_ToSomeFactory_02(Seq);
	}

}

int NEH_BLOCK(vector<vector<int>>& Sol, vector<int> Seq)
{
	Sol.clear();
	Sol.resize(gFactory);

	int FinalEC = 0;
	for (int i = 0; i < Seq.size(); i++)
	{
		int Job = Seq[i];
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

int DIG(long TimeLimit, int PLen, double Tem, double learnrate, double discountrate, double actionselectrate)
{

	long InitTime = GetElapsedProcessTime();

	vector<vector<int>>Seq;
	vector<vector<int>>Seq2;

	int EC = NEH2_In(Seq);
	int EC2 = NEH2_In(Seq2);


	vector<vector<int>>BestSeqSofar;
	int BestValueSofar;

	if (GetFspan(Seq) < GetFspan(Seq2))
	{
		BestSeqSofar = Seq;
		BestValueSofar = EC;
	}
	else
	{
		BestSeqSofar = Seq2;
		BestValueSofar = EC2;
	}

	int iter = 1;

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		vector<vector<int>>TempSeq = Seq;
		vector<vector<int>>TempSeq2 = Seq2;

		int TempEC = EC;
		int TempEC2 = EC2;

		SwapJobs_random_betweenTwoFac(TempSeq);
		SwapJobs_random_betweenTwoFac02(TempSeq2);


		for (int i = 0; i < gFactory; ++i)
		{
			vector<int>DesJobSeq1, tempJobSeq1;
			tempJobSeq1 = TempSeq[i];

			Destruction_To_someFactory(tempJobSeq1, DesJobSeq1, 2);
			Construction_To_someFactory(tempJobSeq1, DesJobSeq1);

			if (GetFspan(tempJobSeq1) < GetFspan(Seq))
			{
				TempSeq[i] = tempJobSeq1;
			}

			vector<int>DesJobSeq2, tempJobSeq2;
			tempJobSeq2 = TempSeq2[i];

			Destruction_To_someFactory(tempJobSeq2, DesJobSeq2, 2);
			Construction_To_someFactory(tempJobSeq2, DesJobSeq2);

			if (GetFspan(tempJobSeq2) < GetFspan(Seq))
			{
				TempSeq2[i] = tempJobSeq2;
			}

			int r1 = rand() % 2;

			if (r1 == 0)
			{
				NSwap(TempSeq[i]);
			}
			else if (r1 == 1)
			{
				Swap_Inner(TempSeq[i]);
			}

			int r2 = rand() % 2;

			if (r2 == 0)
			{
				NSwap(TempSeq2[i]);
			}
			else if (r1 == 1)
			{
				Swap_Inner(TempSeq2[i]);
			}


			TempEC = GetFspan(TempSeq[i]);
			TempEC2 = GetFspan(TempSeq2[i]);

			if (TempEC2 > TempEC)
			{
				TempSeq2 = TempSeq;
			}

			else {
				TempSeq = TempSeq2;
			}

		}


		TempEC = GetFspan(TempSeq);
		TempEC2 = GetFspan(TempSeq2);

		if (TempEC2 > TempEC)
		{
			if (TempEC < EC)
			{
				EC = TempEC;
				Seq = TempSeq;

				if (EC < BestValueSofar)
				{
					BestValueSofar = EC;
					BestSeqSofar = Seq;
				}
			}
		}

		else {
			EC = TempEC2;
			Seq = TempSeq2;

			if (EC < BestValueSofar)
			{
				BestValueSofar = EC;
				BestSeqSofar = Seq;
			}
		}


	}
	CheckChrom(BestSeqSofar, BestValueSofar);

	return BestValueSofar;
}

int DIG_Curve(long TimeLimit,  int LocalValue, long LocalTime, int No)
{

	long InitTime = GetElapsedProcessTime();

	vector<vector<int>>Seq;
	vector<vector<int>>Seq2;

	int EC = NEH2_In(Seq);
	int EC2 = NEH2_In(Seq2);


	vector<vector<int>>BestSeqSofar;
	int BestValueSofar;

	if (GetFspan(Seq) < GetFspan(Seq2))
	{
		BestSeqSofar = Seq;
		BestValueSofar = EC;
	}
	else
	{
		BestSeqSofar = Seq2;
		BestValueSofar = EC2;
	}

	int iter = 1;

	//建立一个txt文件
	ostringstream str;
	str << "Test_IG_BLOCK_Curve_Ins=" << No << ".txt";                //
	ofstream ofile;
	ofile.open(str.str());

	
	//输出初始解以及初始时间
	LocalValue = BestValueSofar;                             //
	LocalTime = GetElapsedProcessTime() - InitTime;         //
	ofile << LocalTime << "\t" << LocalValue << "\t" << endl;

	while (GetElapsedProcessTime() - InitTime < TimeLimit)
	{
		vector<vector<int>>TempSeq = Seq;
		vector<vector<int>>TempSeq2 = Seq2;

		int TempEC = EC;
		int TempEC2 = EC2;

		SwapJobs_random_betweenTwoFac(TempSeq);
		SwapJobs_random_betweenTwoFac02(TempSeq2);


		for (int i = 0; i < gFactory; ++i)
		{
			vector<int>DesJobSeq1, tempJobSeq1;
			tempJobSeq1 = TempSeq[i];

			Destruction_To_someFactory(tempJobSeq1, DesJobSeq1, 2);
			Construction_To_someFactory(tempJobSeq1, DesJobSeq1);

			if (GetFspan(tempJobSeq1) < GetFspan(Seq))
			{
				TempSeq[i] = tempJobSeq1;
			}

			vector<int>DesJobSeq2, tempJobSeq2;
			tempJobSeq2 = TempSeq2[i];

			Destruction_To_someFactory(tempJobSeq2, DesJobSeq2, 2);
			Construction_To_someFactory(tempJobSeq2, DesJobSeq2);

			if (GetFspan(tempJobSeq2) < GetFspan(Seq))
			{
				TempSeq2[i] = tempJobSeq2;
			}

			int r1 = rand() % 2;

			if (r1 == 0)
			{
				NSwap(TempSeq[i]);
			}
			else if (r1 == 1)
			{
				Swap_Inner(TempSeq[i]);
			}

			int r2 = rand() % 2;

			if (r2 == 0)
			{
				NSwap(TempSeq2[i]);
			}
			else if (r1 == 1)
			{
				Swap_Inner(TempSeq2[i]);
			}


			TempEC = GetFspan(TempSeq[i]);
			TempEC2 = GetFspan(TempSeq2[i]);

			if (TempEC2 > TempEC)
			{
				TempSeq2 = TempSeq;
			}

			else {
				TempSeq = TempSeq2;
			}

		}


		TempEC = GetFspan(TempSeq);
		TempEC2 = GetFspan(TempSeq2);

		if (TempEC2 > TempEC)
		{
			if (TempEC < EC)
			{
				EC = TempEC;
				Seq = TempSeq;

				if (EC < BestValueSofar)
				{
					BestValueSofar = EC;
					BestSeqSofar = Seq;
				}
			}
		}

		else {
			EC = TempEC2;
			Seq = TempSeq2;

			if (EC < BestValueSofar)
			{
				BestValueSofar = EC;
				BestSeqSofar = Seq;
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