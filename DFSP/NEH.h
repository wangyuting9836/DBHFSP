//NEH.h
void NEHInit(vector<int>&JobSeq)
{
	JobSeq.clear();
	JobSeq.resize(gJobs);
	Pair *ch = new Pair[gJobs];
	for (int j = 0; j < gJobs; j++)
	{
		ch[j].dim = j;
		ch[j].value = 0;
		for (int m = 0; m < InStage; m++)
			ch[j].value += pTime[j][m];
	}

	sort(ch, ch + gJobs, PairGreater());
	for (int j = 0; j < gJobs; j++)
		JobSeq[j] = ch[j].dim;
	delete[]ch;
}

void NEHInit02(vector<int>& JobSeq)
{
	JobSeq.clear();
	JobSeq.resize(gJobs);
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
		JobSeq[j] = ch[j].dim;
	delete[]ch;
}

int NEH_Speedup(vector<vector<int>>&Sol)
{
	Sol.clear();
	Sol.resize(gFactory);

	vector<int>FullPermutation;
	FullPermutation.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		FullPermutation[j] = j;
	NEHInit(FullPermutation);

	int FinalMakespan = 0;
	for (int j = 0; j < FullPermutation.size(); j++)
	{
		int Job = FullPermutation[j];
		FinalMakespan = Job_To_BestFactory_Bestposition(Job, Sol);
	}
	return 	FinalMakespan;
}

int NEH_RAN(vector<vector<int>>&Seq)
{
	Seq.clear();
	Seq.resize(gFactory);

	vector<int>FullPermutation;
	FullPermutation.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		FullPermutation[j] = j;

	srand(GetElapsedProcessTime());
	random_shuffle(FullPermutation.begin(), FullPermutation.end());

	int FinalMakespan = 0;
	for (int j = 0; j < FullPermutation.size(); j++)
	{
		int Job = FullPermutation[j];
		FinalMakespan = Job_To_BestFactory_Bestposition(Job, Seq);
	}
	return 	FinalMakespan;
}

int NEH2(vector<vector<int>>&Sol)
{
	Sol.clear();
	Sol.resize(gFactory);

	vector<int>FullPermutation;
	FullPermutation.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		FullPermutation[j] = j;
	NEHInit(FullPermutation);

	for (int f = 0; f < Sol.size(); f++)
		Sol[f].push_back(FullPermutation[f]);

	int FinalSpan = 0;
	for (int i = Sol.size(); i < FullPermutation.size(); i++)
	{
		int Job = FullPermutation[i];
		FinalSpan = Job_To_BestFactory_Bestposition(Job, Sol);
	}
	return FinalSpan;
}

int NEH2_Rand(vector<vector<int>>&Sol)
{
	Sol.clear();
	Sol.resize(gFactory);

	vector<int>FullPermutation;
	FullPermutation.resize(gJobs);
	for (int j = 0; j < gJobs; j++)
		FullPermutation[j] = j;
	random_shuffle(FullPermutation.begin(), FullPermutation.end());

	for (int f = 0; f < Sol.size(); f++)
		Sol[f].push_back(FullPermutation[f]);

	int FinalSpan = 0;
	for (int i = Sol.size(); i < FullPermutation.size(); i++)
	{
		int Job = FullPermutation[i];
		FinalSpan = Job_To_BestFactory_Bestposition(Job, Sol);
	}
	return FinalSpan;
}
