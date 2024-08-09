#include "TGFActionInitialization.hh"

TGFActionInitialization::TGFActionInitialization()
{}

TGFActionInitialization::~TGFActionInitialization()
{}


void TGFActionInitialization::SetPrimaryParticleEnergy(G4double PrimaryParticleEnergy)
{
	fPrimaryParticleEnergy = PrimaryParticleEnergy;
	G4cout << G4endl << "fPrimaryParticleEnergy in TGFActionInitialization was set to " << fPrimaryParticleEnergy << G4endl << G4endl;
}



void TGFActionInitialization::BuildForMaster() const
{
    TGFRunAction* runAction = new TGFRunAction();
    SetUserAction(runAction);

}

void TGFActionInitialization::Build() const
{
	TGFPrimaryGenerator* generator = new TGFPrimaryGenerator();
	generator->SetPrimaryEnergy(fPrimaryParticleEnergy);
	SetUserAction(generator);

	TGFRunAction* runAction = new TGFRunAction();
	SetUserAction(runAction);

	TGFEventAction* eventAction = new TGFEventAction(runAction);
	SetUserAction(eventAction);

	TGFSteppingAction* steppingAction = new TGFSteppingAction(eventAction);
    SetUserAction(steppingAction);
}


