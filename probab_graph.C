double get_probab(const char *fname)
{
	TFile *input = new TFile(fname, "read");
	TTree *sec_part_tree = (TTree*)input->Get("Second_particle");
	if (!sec_part_tree)
	{
		cout << "tree wasnt read, error" << endl;
		return 0;
	}

	int entries = sec_part_tree->GetEntries();
	//cout << "entries: " << entries << endl;

	int over;
	sec_part_tree->SetBranchAddress("Over", &over);
	int sum = 0;

	for (int i=0; i < entries; i++)
	{
		sec_part_tree->GetEntry(i);
		sum += over;
	}

	double probab = 100. * (double)sum / (double)entries;

	//cout << "sum = " << sum << ", sum/entries * 100 = " << probab << endl; 

	return probab;
}


void probab_graph()
{
	const char *fname[14] = {"0.4MeV.root", "0.5MeV.root", "0.6MeV.root", "0.8MeV.root", "1.2MeV.root", 
									"1.5MeV.root", "2MeV.root", "3MeV.root", "5MeV.root", "7MeV.root",
									 "10MeV.root", "20MeV.root", "30MeV.root", "100MeV.root"};
	double probabs[14];
	for (int i =0; i<14; i++)
	{
		probabs[i] = get_probab(fname[i]);	
	}

	for (int i =0; i<14; i++)
	{
		cout << probabs[i] << endl;	
	}
	
	double energies[14] = {0.4, 0.5, 0.6, 0.8, 1.2, 1.5, 2, 3, 5, 7, 10, 20, 30, 100};

	TGraph *gr = new TGraph(14, energies, probabs);
	TCanvas *c1 = new TCanvas();
	c1->SetLogy();
	c1->SetLogx();
	gr->SetMarkerColor(4);
   gr->SetMarkerSize(1.5);
   gr->SetMarkerStyle(21);
	gr->GetXaxis()->SetTitle("primary kinetic energy");
   gr->GetYaxis()->SetTitle("avalanche probability %");

	gr->Draw("ACP");
	   TText *t22 = new TText(0.5,0.07,"1.5kV/cm");
   t22->SetTextSize(0.04);
   t22->Draw();
	return;
}