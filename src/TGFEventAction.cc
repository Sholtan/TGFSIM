#include "TGFEventAction.hh"

TGFEventAction::TGFEventAction(TGFRunAction*)
{
}
TGFEventAction::~TGFEventAction()
{}

void TGFEventAction::BeginOfEventAction(const G4Event*)
{
	fCount =0;
}

void TGFEventAction::EndOfEventAction(const G4Event* ev)
{
	G4AnalysisManager* man = G4AnalysisManager::Instance();
    man->FillNtupleIColumn(0, 0, fCount);
    man->FillNtupleIColumn(0, 1, fCount>10000);
	man->AddNtupleRow(0);
}
