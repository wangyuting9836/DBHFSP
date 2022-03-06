#include <Windows.h>
#include <cstdlib>
#include <climits>
#include <vector>
#include <vector>
#include<iomanip>
#include <iostream>
#include <fstream>
#include <sstream>
#include<random>
#pragma warning(disable:4996)

using namespace std;
#include "com.h"
#include "IG.h"
#include "EA.h"
#include "DDE.h"
#include "PSO.h"
#include "MN_IG.h"
#include "DIG.h"

#define _CRT_SECURE_NO_WARNINGS

void main()
{
	for (int Counter = 2; Counter < 3; Counter++)
	{
		int CPU = 10;

		int Psize = 20;
		float Mcoefficien = 0.0;
		float Crossovercoefficient = 0.1;
		float Selectcoefficient = 0.0;
		int Iter = 4000;

		cout << "Test_CPU=" << CPU << endl;
		cout << "算法从左到右依次为：DIG, DDE, EA, MN_IG, IG, DPSO " << endl;

		vector<vector<int>> SpanFactory_IG;
		SpanFactory_IG.resize(270);
		for (int ins = 0; ins < SpanFactory_IG.size(); ins++)
			SpanFactory_IG[ins].resize(30, 0);

		vector<vector<int>> SpanFactory_PSO;
		SpanFactory_PSO.resize(270);
		for (int ins = 0; ins < SpanFactory_PSO.size(); ins++)
			SpanFactory_PSO[ins].resize(30, 0);

		vector<vector<int>> SpanFactory_DDE;
		SpanFactory_DDE.resize(270);
		for (int ins = 0; ins < SpanFactory_DDE.size(); ins++)
			SpanFactory_DDE[ins].resize(30, 0);

		vector<vector<int>> SpanFactory_EA;
		SpanFactory_EA.resize(270);
		for (int ins = 0; ins < SpanFactory_EA.size(); ins++)
			SpanFactory_EA[ins].resize(30, 0);

		vector<vector<int>> SpanFactory_MN_IG;
		SpanFactory_MN_IG.resize(270);
		for (int ins = 0; ins < SpanFactory_MN_IG.size(); ins++)
			SpanFactory_MN_IG[ins].resize(30, 0);

		vector<vector<int>> SpanFactory_DIG;
		SpanFactory_DIG.resize(270);
		for (int ins = 0; ins < SpanFactory_DIG.size(); ins++)
			SpanFactory_DIG[ins].resize(30, 0);

		string FileDirectory = "Result\\"; //
		ostringstream str;
		str << "Test_Algorithms_cpu=" << CPU << ".txt"; //不同的算法
		ofstream ofile;
		ofile.open(FileDirectory + str.str());

		char fileName1[30];
		FILE* f1;
		sprintf(fileName1, "RPI_H.txt");
		f1 = fopen(fileName1, "a+");


		for (int Ins = 0; Ins < 90; Ins++)
		{
			Read(Ins);
			cout << "工件：" << gJobs << " 阶段：" << InStage << " 工厂：" << gFactory << endl;

			long TimeLimit = CPU * gJobs * InStage;
			double min_EA = INT_MAX;
			double min_DDE = INT_MAX;
			double min_IG = INT_MAX;
			double min_PSO = INT_MAX;
			double min_MN_IG = INT_MAX;
			double min_DIG = INT_MAX;
			double min_span = INT_MAX;

			vector<double> RPI;
			RPI.resize(12);

			ofile << "Jobs:" << gJobs << " factory:" << gFactory << " Stage:" << InStage << "\n";
			ofile << "从左到右算法依次为：" << " DIG," << " DDE," << " EA," << " MN_IG" << " IG," << " DPSO";
			ofile << "\n";

			for (int i = 0; i < 20; i++) //每个测试用例执行20遍
			{
				srand(i + 100 + Ins);

				SpanFactory_DIG[Ins][i] = DIG(TimeLimit, 7, Mcoefficien, 0.5, 0.8, 0.5);

				ofile << SpanFactory_DIG[Ins][i] << "\t";

				if (SpanFactory_DIG[Ins][i] < min_DIG)
					min_DIG = SpanFactory_DIG[Ins][i];

				if (min_DIG < min_span)
					min_span = min_DIG;
			}

			ofile << "\n";

			for (int i = 0; i < 20; i++) //每个测试用例执行20遍
			{
				srand(i + 100 + Ins);

				SpanFactory_DDE[Ins][i] = DDE(TimeLimit, Psize, Mcoefficien, Crossovercoefficient, Selectcoefficient,
				                              Iter);
				ofile << SpanFactory_DDE[Ins][i] << "\t";

				if (SpanFactory_DDE[Ins][i] < min_DDE)
					min_DDE = SpanFactory_DDE[Ins][i];
				if (min_DDE < min_span)
					min_span = min_DDE;
			}

			ofile << "\n";

			for (int i = 0; i < 20; i++) //每个测试用例执行20遍
			{
				srand(i + 100 + Ins);

				SpanFactory_EA[Ins][i] = EA(TimeLimit, Psize);
				ofile << SpanFactory_EA[Ins][i] << "\t";

				if (SpanFactory_EA[Ins][i] < min_EA)
					min_EA = SpanFactory_EA[Ins][i];
				if (min_EA < min_span)
					min_span = min_EA;
			}

			ofile << "\n";

			for (int i = 0; i < 20; i++) //每个测试用例执行20遍
			{
				srand(i + 100 + Ins);
				SpanFactory_MN_IG[Ins][i] = MN_IG_Compared(TimeLimit, 1, Mcoefficien);
				ofile << SpanFactory_MN_IG[Ins][i] << "\t";
				if (SpanFactory_MN_IG[Ins][i] < min_MN_IG)
					min_MN_IG = SpanFactory_MN_IG[Ins][i];
				if (min_MN_IG < min_span)
					min_span = min_MN_IG;
			}

			ofile << "\n";

			for (int i = 0; i < 20; i++) //每个测试用例执行20遍
			{
				srand(i + 100 + Ins);
				SpanFactory_IG[Ins][i] = IG_Compared(TimeLimit, 1, Mcoefficien);

				ofile << SpanFactory_IG[Ins][i] << "\t";

				if (SpanFactory_IG[Ins][i] < min_IG)
					min_IG = SpanFactory_IG[Ins][i];
				if (min_IG < min_span)
					min_span = min_IG;
			}

			ofile << "\n";

			for (int i = 0; i < 20; i++) //每个测试用例执行5遍
			{
				srand(i + 100 + Ins);
				SpanFactory_PSO[Ins][i] = PSO(TimeLimit, 50, 200, 1.1, 1.1);

				ofile << SpanFactory_PSO[Ins][i] << "\t";

				if (SpanFactory_PSO[Ins][i] < min_PSO)
					min_PSO = SpanFactory_PSO[Ins][i];
				if (min_PSO < min_span)
					min_span = min_PSO;
			}

			fprintf(f1, "%d * %d * %d\n", gJobs, InStage, gFactory);
			RPI[0] = (min_DIG - min_span) / min_span * 100;
			fprintf(f1, "%lf", RPI[0]);
			fprintf(f1, "\t");
			RPI[1] = (min_DDE - min_span) / min_span * 100;
			fprintf(f1, "%lf", RPI[1]);
			fprintf(f1, "\t");
			RPI[2] = (min_EA - min_span) / min_span * 100;
			fprintf(f1, "%lf", RPI[2]);
			fprintf(f1, "\t");
			RPI[3] = (min_MN_IG - min_span) / min_span * 100;
			fprintf(f1, "%lf", RPI[3]);
			fprintf(f1, "\t");
			RPI[4] = (min_IG - min_span) / min_span * 100;
			fprintf(f1, "%lf", RPI[4]);
			fprintf(f1, "\t");
			RPI[5] = (min_PSO - min_span) / min_span * 100;
			fprintf(f1, "%lf", RPI[5]);
			fprintf(f1, "\t");

			fprintf(f1, "\n");

			cout << RPI[0] << "\t" << RPI[1] << "\t" << RPI[2] << "\t" << RPI[3] << "\t" << RPI[4] << "\t" << RPI[5] <<
				endl;
			cout << endl;
			ofile << endl;
		}
		fclose(f1);
		ofile.close();
	}
}
