#include "TGFSteppingAction.hh"


TGFSteppingAction::TGFSteppingAction(TGFEventAction* eventAction)
{
	fEventAction = eventAction;
}

TGFSteppingAction::~TGFSteppingAction()
{}

void TGFSteppingAction::UserSteppingAction(const G4Step *aStep)
{
	G4Track* track = aStep->GetTrack();
	


	const G4ParticleDefinition* particleDefinition = track->GetParticleDefinition();
	const G4String& particlename = particleDefinition->GetParticleName();	

	G4int CurrentStepNumber = track->GetCurrentStepNumber();
	G4int track_id = track->GetTrackID();

	if (track_id != 1)
	{
		track->SetTrackStatus(fStopAndKill);
		return;
	}

	if (true)  // CurrentStepNumber == 1
	{	
		G4cout << G4endl << G4endl << "CurrentStepNumber: " << CurrentStepNumber << ", name: " << particlename << ", id: " << track_id << G4endl << G4endl;
	}
}