#include "TGFRunAction.hh"

TGFRunAction::TGFRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->SetNtupleMerging(true);
	man->CreateNtuple("Second_particle", "Second_particle");
	man->CreateNtupleIColumn("Count");
	man->CreateNtupleIColumn("Over");
	man->FinishNtuple(0);

	man->CreateNtuple("electron_steps_info", "e_steps_info");
	man->CreateNtupleDColumn("kin_E");
	man->CreateNtupleDColumn("x");
	man->CreateNtupleDColumn("y");
	man->CreateNtupleDColumn("z");
	man->CreateNtupleDColumn("t");
	man->FinishNtuple(1);

	man->CreateNtuple("positron_steps_info", "e_steps_info");
	man->CreateNtupleDColumn("kin_E");
	man->CreateNtupleDColumn("x");
	man->CreateNtupleDColumn("y");
	man->CreateNtupleDColumn("z");
	man->CreateNtupleDColumn("t");
	man->FinishNtuple(2);

	man->CreateNtuple("photon_steps_info", "photon_steps_info");
	man->CreateNtupleDColumn("kin_E");
	man->CreateNtupleDColumn("x");
	man->CreateNtupleDColumn("y");
	man->CreateNtupleDColumn("z");
	man->CreateNtupleDColumn("t");
	man->FinishNtuple(3);

}

TGFRunAction::~TGFRunAction()
{

}


void TGFRunAction::BeginOfRunAction(const G4Run* run)
{
    G4AnalysisManager* man = G4AnalysisManager::Instance();
	G4int runID = run->GetRunID();
	std::stringstream strRunID;
	strRunID << runID;
	man->OpenFile("output" + strRunID.str() + ".root");
}

void TGFRunAction::EndOfRunAction(const G4Run*)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
	man->Write();
	man->CloseFile();
}



