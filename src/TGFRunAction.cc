#include "TGFRunAction.hh"

TGFRunAction::TGFRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    man->SetNtupleMerging(true);
	man->CreateNtuple("Second_particle", "Second_particle");
	man->CreateNtupleIColumn("Count");
	man->CreateNtupleIColumn("Over");
	man->FinishNtuple(0);
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